
#include "Record.h"
using namespace std;
//Constructor
Record::Record(int ye, string regionName, string sub_regName, string animalName, int farmNum, int animals)
{
  year = ye;
  region = regionName;
  sub_region = sub_regName;
  animalType = animalName;
  totalFarms = farmNum;
  numAnimals= animals;
}

// Destructor
Record::~Record()
{
  //
}

//Getters
int Record::getYear() const { return year; }
string Record::getRegion() const { return region; }
string Record::getSub_Region() const { return sub_region; }
string Record::getAnimal() const { return animalType; }
int Record::getTotalAnimals() const { return numAnimals; }
int Record::getTotalFarms() const { return totalFarms; }

