#ifndef _TASK_H_
#define _TASK_H_

#include <iostream>
#include <sstream>
#include "Util.h"

struct Date{
    int day;
    int month;
    int year;
};


class Task{
    
    friend ostream& operator<<(ostream &os, Task &task);
    protected:
        string name;
        Date deadline;
        bool isDone;
        int time;
        bool CompDeadLine(Date fecha); //A lo mejor hay que ponerle const

    public:
        Task(string name); //Constructor
        string getName() const;
        Date getDeadline() const;
        bool getIsDone() const;
        int getTime() const;
        void setName(string name);
        bool setDeadline(string deadline);
        bool setTime(int time);
        void toggle();
    
};
#endif