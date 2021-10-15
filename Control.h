#ifndef CONTROL_H
#define CONTROL_H
#include "View.h"
#include "ReportGenerator.h"

class Control
{
public:
    Control();
    ~Control();
    void launch();

private:
    View view;
    vector<ReportGenerator *> reps;
    void initReports();
};

#endif
