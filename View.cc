#include "View.h"
using namespace std;


void View::showMenu(int& choice)
{
  cout << endl;
  cout << "      what would you like to do ?"<< endl;
  cout << "  (1) Percentage distribution of farms, by province in Year 2016" << endl;
  cout << "  (2) Percentage change of animals, by province from Year 2011 to 2016" << endl;
  cout << "  (3) Sub-region with highest number of horses, by province in Year 2016" << endl;
  cout << "  (0) Exit" << endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0)
    return;
  while (choice < 1 || choice > 3) {
    cout << "Enter your selection: ";
    cin >> choice;
  }

}



