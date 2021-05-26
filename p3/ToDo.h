#ifndef _TODO_H_
#define _TODO_H_

#include <iostream>
#include <string.h>
#include "Project.h"

class ToDo{
    friend ostream& operator<<(ostream &os, const ToDo &ToDO);
    protected:
        static int nextId;
        vector <Project*> projects;
        string name;
        int CompMenu( int id);
    public:
        ToDo(string name);
        string getName() const;
        int getPosProject(string name) const;
        int getPosProject(int i) const;
        bool setName(string name);
        void addProject(Project* Project);
        void deleteProject(int id = 0);
        void setProjectDescription(string name, string description);
        void projectMenu(int id = 0);
};
#endif