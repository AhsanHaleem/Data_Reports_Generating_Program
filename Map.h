#ifndef MAP_H
#define MAP_H
#include "Record.h"
#include <string>

#include <vector>

template <class T>
class Map
{
  // template <class V>
  // friend ostream& operator << (ostream&, const Map<V>&);
  // template <class V>
  // friend istream& operator >> (istream&,Map<V>&);

  public:
    Map();
    ~Map();
    void add(T, Record*);
    int size();
    std::vector<T>* getKeys();
    std::vector<Record*>* operator[](T);



  private:
    std::vector<T> keys;
    std::vector<std::vector<Record*>> recordPtrs;

};
using namespace std;
template <class T>
Map<T>::Map()
{
  
}

template <class T>
Map<T>::~Map()
{

}

template <class T>
int Map<T>::size(){return keys.size();}

template <class T>
void Map<T>::add(T key, Record* record)
{
  bool found = false;
  for(int i=0;i<keys.size();++i){
    if(keys[i] == key){
      recordPtrs[i].push_back(record);
      found = true;
      break;
    }
  }
  if(keys.size() == 0 || !found){
    keys.push_back(key);
    vector<Record*> val;
    val.push_back(record);
    recordPtrs.push_back(val);
  }



}
template <class T>
vector<T>* Map<T>::getKeys(){
  return &keys;
}
template <class T>
vector<Record*>* Map<T>::operator[](T key){
  for(int i=0;i<keys.size();++i){
    if(key == keys[i]){
      return &recordPtrs[i];
    }
  }
  return NULL;
}
#endif
