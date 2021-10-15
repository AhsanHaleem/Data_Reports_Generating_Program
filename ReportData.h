#ifndef REPORTDATA_H
#define REPORTDATA_H
#include <string>
#include <iomanip>
#include <vector>
#include "CompareBehavior.h"
#include <iostream>

template <class T>
class ReportData
{
  template <class V>
  friend ostream& operator << (ostream&, const ReportData<V>&);
  

  public:
    ReportData(CompareBehavior<T>*);
    ~ReportData();
    void add(T, string);


  private:
    template <class V>
    class ReportRow
    {

      public:
        V key;                        // key for report row (float) (2.1-regional percentage)
        string row;                   // long string of report row
        ReportRow(V keyT, string rowS): key(keyT), row(rowS) {};

    };
    vector<ReportRow<T>> reportRows;
    CompareBehavior<T> *rowB;

};
using namespace std;
template <class T>
ReportData<T>::ReportData(CompareBehavior<T>* behavior)
{
  rowB = behavior;
}

template <class T>
ReportData<T>::~ReportData()
{
  // WHAT do I need here
   delete rowB;
  
}

template <class T>
void ReportData<T>::add(T key, string row)
{
  typename vector<ReportRow<T>>::iterator ptr;
  ReportRow<T> r = ReportRow<T>(key,row);
  for (ptr = reportRows.begin(); ptr < reportRows.end(); ++ptr) {
    if (rowB->compare(key, ptr->key)) {
      reportRows.insert(ptr,r);
      return;
    }
  }
  reportRows.insert(ptr,r);
}

template <class V>
ostream& operator << (ostream& output, const ReportData<V>& data)
{
  
  for (int i = 0; i < data.reportRows.size(); ++i) {
    output << data.reportRows[i].row << endl;
  }
  return output;
}

#endif
