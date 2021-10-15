#ifndef RECORD_H
#define RECORD_H
#include <string>
class Record
{
  public:
    Record(int = 0, std::string = "", std::string = "", std::string = "", int = 0, int = 0);
    ~Record();
    int getYear() const;
    std::string getRegion() const;
    std::string getSub_Region() const;
    std::string getAnimal() const;
    int getTotalAnimals() const;
    int getTotalFarms() const;
  

  private:
    int year;
    std::string region;        // province or territory or Canada
    std::string sub_region;    // sub-region inside the region
    std::string animalType;    // name of the type of animal
    int totalFarms; // Total number of farm 
    int numAnimals;    // Number of specific farm animals

};
#endif
