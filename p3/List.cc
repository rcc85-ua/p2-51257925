#include "List.h"

List::List(string name){
    if(name.empty()){
        throw ERR_EMPTY;
    }
    this->name = name;
}
string List::getName()const {
    return name; 
}

vector<Task> List::getTasks()const {
    return tasks;
}
//Devuelve el numero de tareas de esa list
unsigned List::getNumTasks()const {
    return tasks.size();
}

unsigned List::getNumDone()const {
    unsigned num = 0;
    for(unsigned i=0; i< tasks.size(); i++){
        if(tasks[i].getIsDone())
            num++;
    }
    return num;
}

int List::getTimeTasks()const {
    int total = 0;
    
    for(unsigned i=0; i< tasks.size(); i++){
        total += tasks[i].getTime();
    }
    return total;
}

int List::getTimeDone()const {
    int sumatorio = 0;

    for(unsigned i = 0; i < tasks.size(); i++){
        if(tasks[i].getIsDone()){
            sumatorio += tasks[i].getTime();
        }
    }
    return sumatorio;
}

int List::getPosTask(string name)const {
    int pos = -1;
    for(unsigned i = 0; i < tasks.size(); i++){
        if(name == tasks[i].getName()){
            pos = i;
        }
    }
    return pos;
}

bool List::setName(string name){
    bool resultado = true;
    if(!name.empty()){
        this->name = name;
    }else{
        Util::error(ERR_EMPTY);
        resultado = false;
    }
    return resultado;
}

void List::addTask(const Task &task){
    tasks.push_back(task);
}

bool List::deleteTask(string name){
    bool found = false;

    for(unsigned i=0; i< tasks.size(); i++){
        if(tasks[i].getName() == name){
            tasks.erase(tasks.begin() + i);
            i--;
            found = true;
        }
    }
    if(!found){
        Util::error(ERR_TASK_NAME);
    }
    return found;
}

bool List::toggleTask(string name){
    bool found = false;

    for(unsigned i=0; i< tasks.size(); i++){
        if(tasks[i].getName() == name){
            tasks[i].toggle();
            found = true;
        }
    }
    if(!found){
        Util::error(ERR_TASK_NAME);
    }
    return found;
}

ostream& operator<<(ostream &os, const List &list){
    os << list.name << endl;
    for(unsigned i=0; i< list.tasks.size();i++){
        if(!list.tasks[i].getIsDone()){
            os << list.tasks[i] << endl;
        }
    }
    for(unsigned i=0; i< list.tasks.size();i++){
        if(list.tasks[i].getIsDone()){
            os << list.tasks[i] << endl;
        }
    }
    return os;
}