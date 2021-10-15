#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Record.h"
#include "Map.h"
#include "ReportData.h"
#include "CompareBehavior.h"
#include "ReportGenerator.h"

using namespace std;

//initialize static members
vector<Record*>ReportGenerator::indRec;
Map<int> ReportGenerator::yearCollec;
Map<string> ReportGenerator::regCollec;
Map<string> ReportGenerator::aniCollec;

void ReportGenerator::freeRecs(){
    for(int i=0;i<indRec.size();++i){
        delete indRec[i];
    }
}

ReportGenerator::~ReportGenerator(){}

void ReportGenerator::initRecs(){
    string datfile= "farms.dat";
    string reg,subReg,aniType;
    int year,numFarms,numAnimals;
    ifstream dataFile(datfile,ios::in);
    if(!dataFile){
        cout << "No file found, please check the path of the file"<<endl;
        exit(-1);
    }
    while(dataFile >> year >> reg >> subReg >> aniType >> numFarms >> numAnimals){
        Record *rec = new Record(year,reg,subReg,aniType,numFarms,numAnimals);
        indRec.push_back(rec);
        aniCollec.add(aniType,rec);
        yearCollec.add(year,rec);
        regCollec.add(reg,rec);
    }
}
FirstReport::FirstReport(){
    CompareBehavior<float>* cb = new DescBehavior<float>();
    rows = new ReportData<float>(cb);
}
void FirstReport::compute(){
    int year  = 2016;
    if(yearCollec[year] == NULL){
        cout << "no collection by that year found"<<endl;
        exit(-1);
    }
    int numFarmstotal = 0;
    vector<Record*> records = *yearCollec[year];
    vector<string> animals = *aniCollec.getKeys();
    vector<string> regions = *regCollec.getKeys();
    int totalFarmsByanimals[animals.size()] ={0};


    for(int i=0;i < records.size();++i){
        if(records[i]->getRegion() != "CAN" && records[i]->getSub_Region() == "All"){
            string ani = records[i]->getAnimal();
            numFarmstotal+= records[i]->getTotalFarms();
            string reg = records[i]->getRegion();
            for (int j=0;j<animals.size();++j){
                if(ani == animals[j]){
                    totalFarmsByanimals[j]+= records[i]->getTotalFarms();
                    break;
                }

            }
        }

    }
    float regionalFarms[animals.size()]={0};
    float regionalFarmsTotal = 0;
    for(int j=0;j<regions.size();++j){
        if(regions[j] != "CAN"){
            stringstream datastream;
            datastream << regions[j];
            if(regCollec[regions[j]] == NULL){exit(-1);}
            vector<Record*> regionRecs = *regCollec[regions[j]];
            for(int k=0;k<regionRecs.size();++k){
                if(regionRecs[k]->getYear() == 2016 && regionRecs[k]->getSub_Region() == "All"){
                    for(int m=0;m<animals.size();++m){
                        if(animals[m] == regionRecs[k]->getAnimal()){
                            regionalFarms[m]+=regionRecs[k]->getTotalFarms();
                            break;
                        }
                    }
                    regionalFarmsTotal+=regionRecs[k]->getTotalFarms();
                }
            }
            for(int h=0;h<animals.size();++h){
                datastream << "       " << setprecision(3) << setw(6) << ((totalFarmsByanimals[h] == 0) ? 0 :regionalFarms[h]/totalFarmsByanimals[h]*100);
                regionalFarms[h] = 0;
            }
            datastream << "    " <<setprecision(3) << regionalFarmsTotal/numFarmstotal *100;
            formatData(datastream.str(),regionalFarmsTotal/numFarmstotal *100);
            regionalFarmsTotal = 0;

        }
    }


}
void FirstReport::formatData(string s, float f){
   rows->add(f,s);
}
void FirstReport::print(){
    vector<string> a = *aniCollec.getKeys();
    for(int i=0;i< a.size();++i){
        cout <<"   " << a[i];
    }

    cout << "    Total"<< endl;
    cout << *rows;
}
FirstReport::~FirstReport(){
    delete rows;
}
SecondReport::SecondReport(){
    CompareBehavior<float>* cb = new AscBehavior<float>();
    rows = new ReportData<float>(cb);

}
SecondReport::~SecondReport(){
    delete rows;
}
void SecondReport::compute(){
    vector<Record*> recs = *regCollec["CAN"];
    vector<string> animals = *aniCollec.getKeys();
    float total2016 =0;
    float total2011 = 0;

    for(int i=0;i<recs.size();i++){
        int year = recs[i]->getYear();
        int tot = recs[i]->getTotalAnimals();
        if(year == 2016){
            total2016+=tot;
        }
        if(year == 2011){
            total2011+=tot;
        }
    }


    int totalin2016 = 0;
    int totalin2011 = 0;

    for(int i=0;i<animals.size();++i){
        if(aniCollec[animals[i]] == NULL){exit(-1);}
        vector<Record*> records = *aniCollec[animals[i]];
        stringstream datastream ;
        datastream <<setw(15) << animals[i];
        for(int j=0;j<records.size();++j){
            if(records[j]->getRegion() == "CAN"){
                int year = records[j]->getYear();
                int total = records[j]->getTotalAnimals();
                if(year == 2011){
                    totalin2011+= total;
                }
                if(year == 2016){
                    totalin2016 += total;
                }
            }
        }
        float val1 = totalin2011/total2011 * 100;
        float val2 = totalin2016/total2016 * 100;
        datastream << "  " << setprecision(3) << setw(3) <<setprecision(2)<< val1;
        datastream << "  " << setprecision(3) << setw(3) <<setprecision(2)<< val2;
        datastream << "  " << setprecision(3) << setw(2) <<setprecision(2)<< showpos<< val2 - val1;
        formatData(datastream.str(),val2-val1);
        totalin2011 = totalin2016 = 0;

    }

}
void SecondReport::print(){
    cout << "      Animals    2011  2016  change" << endl;
    cout << *rows;
}
void SecondReport::formatData(string s, float f){
    rows->add(f,s);
}
ThirdReport::~ThirdReport(){
    delete rows;
}
ThirdReport::ThirdReport(){
    CompareBehavior<int>* cb = new DescBehavior<int>();
    rows = new ReportData<int>(cb);
}
void ThirdReport::compute(){
    vector<string> regions = (*regCollec.getKeys());
    int maxHorses = 0;
    for(int i=0;i<regions.size();++i){
        if(regCollec[regions[i]] == NULL){exit(-1);}
        if(regions[i] != "CAN"){
            vector<Record*> records = *regCollec[regions[i]];
            string subRegion = "          ";
            stringstream datastream;
            for(int j=0;j<records.size();++j){
                if(records[j]->getAnimal() == "Horses-Ponies" && records[j]->getSub_Region() != "All" && records[j]->getYear() == 2016){
                    if(records[j]->getTotalAnimals() >= maxHorses){
                        maxHorses = records[j]->getTotalAnimals();
                        subRegion = records[j]->getSub_Region();
                    }
                }
            }
            datastream <<regions[i] << "    " << setw(30) <<subRegion <<"       "<< maxHorses;
            formatData(datastream.str(),maxHorses);
            maxHorses = 0;
        }

    }


}
void ThirdReport::formatData(string s,int f){
    rows->add(f,s);
}
void ThirdReport::print(){
    cout << "Regions            subRegions           Total Horses"<<endl;
    cout <<*rows;
}
