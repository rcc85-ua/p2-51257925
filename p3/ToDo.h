#ifndef _TODO_H_
#define _TODO_H_

#include <iostream>
#include <string.h>
#include "project.h"

class ToDo{
    protected:
        static const int nextId;
        vector <Project*> projects;
        string name;
    public:
        ToDo(string name);
        string getName() const;
        int getPosProject(string name) const;
        int getPosProject(int i) const;
        bool setName(string name);
        void addProject(project Project*);
        void deleteProject(int id = 0);
        void setProjectDescription(string name, string project);
        void projectMenu(int id = 0);
        ostream operator<<(ostream &os, ToDo &ToDo);
}