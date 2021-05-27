#ifndef _PROJECT_H_
#define _PROJECT_H_

#include <iostream>
#include "List.h"
using namespace std;

class Project{
    friend ostream& operator<<(ostream &os,const Project &project);
    protected:
        int id;
        string name;
        string description;
        vector <List> lists;
        int FindList(string name);
        bool CompDeadline(Task nueva);
        bool comparador(Date urgente, Date potencial);
    
    public:
        
        Project(string name, string description = "");
        int  getId() const;
        string  getName() const;
        string  getDescription() const;
        int  getPosList(string name) const;
        bool  setId(int id);
        bool  setName(string name);
        void  setDescription(string description);
        void  edit(string name ="", string description="");
        void  addList(string name="");
        void  deleteList(string name="");
        void  addTaskToList(string name="");
        void  deleteTaskFromList(string name="");
        void  toggleTaskFromList(string name="");
        void  menu();
        string  summary() const;
};
#endif 