#include "Task.h"
#include <string.h>
#include <sstream>

Task::Task(string name){
    this->name = name;
    deadline.day = 1;
    deadline.month = 1;
    deadline.year = 2000;
    time = 1;
    isDone = false;
}
string Task::getName(){
    return name;
}
int Task::getTime(){
    return time;
}
bool Task::getisDone(){
    return isDone;
}
Date Task::getDeadline(){
    return deadline;
}
void Task::setName(string name){
    this->name = name;
    }

void Task::setDeadline(string fechalim){
    stringstream buffer(fechalim);

    buffer >> day;
    buffer.get();
    buffer >> month;
    buffer.get();
    buffer >> year;
}

void Task::setTime(int tiempo){
    time = tiempo;
}
void Task::Toggle(){
    isDone = true;
}

ostream operator<<(ostream &os, Task &Task){
    Date fecha;

    os << "[";
    if(Task.getisDone() == true){
        os << "X";
    }else{
        os << " ";
    }
    os << "] (" << Task.getTime() << ") ";
    fecha = Task.getDeadline();
    os << fecha.year << "-" << fecha.month << "-" << fecha.day << " : " << Task.getName() << endl;
}

