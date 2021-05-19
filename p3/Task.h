#ifndef _TASK_H_
#define _TASK_H_

#include <iostream>
#include <string.h>

struct Date{
    int day;
    int month;
    int year;
}


class Task{
    protected:
    string name;
    Date deadline;
    bool isDone;
    int time;

    public:
    Task(string name);//Constructor
    string getName() const;
    Date getDeadline() const;
    bool getisDone() const;
    int getTime() const;
    void setName(string name);
    void setDeadline(string fechalim);
    void setTime(int tiempo);
    void Toggle();
    ostream operator<<(ostream &os, Task &Task);
}


#endif