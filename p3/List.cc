#include "List.h"
#include <string.h>
#include "Util.h"
#include "Task.h"

    List::List(string name){
        if(name.empty()){
        throw ERR_EMPTY;
        }
        this->name = name;
    }
    string getName(){
        return name;
    }
    
    vector<Tasks> getTasks(){
        return tasks;
    }
    
    unsigned getNumTasks(){
        return tasks.size();
    }
    
    unsigned getNumDone(){
        int num =0;
        for(unsigned i = 0; i< tasks)
    }
    
    int getTimeTasks(){
        int sumatorio = 0;
        
        for(unsigned i=0; i< tasks.size(); i++){
            sumatorio =+ tasks[i].getTime();
        }
        return sumatorio;
    }
    
    int getTimeDone(){
        int sumatorio = 0;

        for(unsigned i = 0; i < tasks.size(); i++){
            if(tasks[i].isDone){
                sumatorio =+ tasks[i].getTime();
            }
        }
        return sumatorio;
    }
    
    int getPosTask(string name){
        int pos = -1;
        for(unsigned i = 0; i < tasks.size(); i++){
            if(name == this -> tasks[i].name){
                pos = i;
            }
        }
        if(pos == -1){
            throw ERR_ID;
        }
    }
    
    bool setName(string name){
        this->name=name;
    }
    
    void addTask(const Task &Task){

        this-> tasks.push_back(Task);
    }
    
    bool deleteTask(string name){}
        int pos=-1;
        bool result = false;

        for(unsigned i=0; i< this-> tasks.size(); i++){
            if(this-> tasks[i].name == name){
                this-> tasks.erase(this-> tasks.begin() + i);
                result = true;
            }
            if(pos == -1){
                throw ERR_TASK_NAME;
            }
            return result;
    }
    
    bool toggleTask(string nombre){
        bool cent = false;

        for(unsigned i=0; i< this-> tasks.size(); i++){
            if(this-> tasks[i].name == name){
                if(this-> tasks[i].isDone){
                    this->tasks[i].isDone = false;
                    cent = true;
                }else{
                    this->tasks[i].isDone = true;
                    cent = true;
                }
            }
        }
        return cent;
    }
    
    ostream operator<<(ostream &os, List &List){
        os << this-> name << endl;
        for(unsigned i=0; i< this->tasks.size();i++){
            if(!tasks[i].isDone){
                operator<<(cout, Task);
            }
        }
        for(unsigned j=0; j< this-> tasks.size(); j++){
            if(task[i].isDone){
                operator<<(cout, Task);
            }
        }
    }