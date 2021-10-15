#include <iostream>
#include <string>
using namespace std;

#include "Control.h"

Control::Control() {}

Control::~Control()
{
    for (int i = 0; i < reps.size(); ++i)
    {
        delete reps[i];
    }
}

void Control::launch()
{
    initReports();
    int c = 1;
    while (c != 0)
    {
        view.showMenu(c);
        if (c != 0)
        {
            reps[c - 1]->print();
        }
    }
    reps[0]->freeRecs();
}

void Control::initReports()
{
    ReportGenerator *r1 = new FirstReport();
    ReportGenerator *r2 = new SecondReport();
    ReportGenerator *r3 = new ThirdReport();
    r1->initRecs();
    reps.push_back(r1);
    reps.push_back(r2);
    reps.push_back(r3);
    for (int i = 0; i < reps.size(); ++i)
    {
        reps[i]->compute();
    }
}
