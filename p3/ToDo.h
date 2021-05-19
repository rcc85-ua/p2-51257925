#ifndef _TODO_H_
#define _TODO_H_

#include <iostream>
#include <string.h>
#include "project.h"

class ToDo{
    protected:
    int nextId = 1;
    vector <project> projects;
    string name;
    public:
    ToDo(string nombre);
    string getName() const;
    int getPosProject(string nombre) const;
    int getPosProject(int i) const;
    bool setName(string name);
    void addProject(project Project*);
    void deleteProject(int id = 0);
    void setProjectDescription(string name, string project);
    void projectMenu(int id = 0);
    ostream operator<<(ostream &os, ToDo &ToDo);
}