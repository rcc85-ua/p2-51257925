#ifndef _PROJECT_H_
#define _PROJECT_H_

#include <iostream>
#include <string.h>
#include <vector>
#include "Task.h"
class List{
    protected:
    string name;
    vector <Task> tasks;
    public:
    List(string nombre);
    string getName() const;
    vector<Tasks> getTasks() const;
    unsigned getNumTasks() const;
    unsigned getNumDone() const;
    int getTimeTasks() const;
    int getTimeDone() const;
    int getPosTask(string name) const;
    bool setName(string nombre);
    void addTask(const Task &Task);
    bool deleteTask(string nombre);
    bool toggleTask(string nombre);
    ostream operator<<(ostream &os, List &List);

}
#endif