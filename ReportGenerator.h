#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include "Record.h"
#include "Map.h"
#include "ReportData.h"
#include "CompareBehavior.h"

class ReportGenerator
{
    public:
      void freeRecs();
      static void initRecs();
      virtual void compute() = 0;
      virtual void print() = 0;
      virtual ~ReportGenerator();

    protected:
      static vector<Record*> indRec;
      static Map<int> yearCollec;
      static Map<string> regCollec;
      static Map<string> aniCollec;

};

class FirstReport : public ReportGenerator{
    public:
      FirstReport();
      ~FirstReport();
      void compute();
      void print();
      void formatData(string ,float);
    private:
      ReportData<float>* rows;
};

class SecondReport : public ReportGenerator{
  public:
      SecondReport();
      ~SecondReport();
      void compute();
      void print();
      void formatData(string ,float);
    private:
      ReportData<float>* rows;
};

class ThirdReport : public ReportGenerator{
  public:
      ThirdReport();
      ~ThirdReport();
      void compute();
      void print();
      void formatData(string ,int);
    private:
      ReportData<int>* rows;
};
#endif
