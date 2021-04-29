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
    public:
    Task(string nombre);//Constructor
    string getName() const;
    Date getDeadline() const;
    bool getisDone() const;
    int getTime() const;
    void setName(string nombre);
    void setDeadline(string fechalim);
    void setTime(int tiempo);
    void Toggle();
    ostream& operator<<(ostream &os,const Task &task);


    protected:
    string name;
    Date deadline;
    bool isDone;
    int time;
}

#endif