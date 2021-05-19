#include "Task.h"

Task::Task(string name){
    this->name = name;
    deadline.day = 1;
    deadline.month = 1;
    deadline.year = 2000;
    //deadline = {1, 1, 2000};
    time = 1;
    isDone = false;
}

string Task::getName(){
    return name;
}

int Task::getTime(){
    return time;
}

bool Task::getIsDone(){
    return isDone;
}

Date Task::getDeadline(){
    return deadline;
}

void Task::setName(string name){
    this->name = name;
}

bool Task::CompDeadLine(Date fecha){
    bool centinela = false;
    if ((fecha.year>2100 || fecha.year<2000)){
        error(ERR_DATE);
        centinela = true;
    }
    else{
        switch (fecha.month){
            case 1 :
            case 3 :
            case 5 :
            case 7 :
            case 8 :
            case 10:
            case 12:
                if(fecha.day<0 || fecha.day>31){
                    error(ERR_DATE);

                    centinela = true;
                }
                break;

            case 2:
                if((fecha.year%100 == 0 && fecha.year%400 == 0) || (fecha.year%100 != 0 && fecha.year%4 == 0)){
                    if (fecha.day<0 || fecha.day > 29){
                        error(ERR_DATE);
                        centinela = true;
                    }
                }else{
                    if (fecha.day<0 || fecha.day > 28){
                        error(ERR_DATE);
                        centinela = true;
                    }
                }
                break;

            case 4 :
            case 6 :
            case 9 :
            case 11:
                if (fecha.day<0 || fecha.day > 30){
                    error(ERR_DATE);

                    centinela = true;
                }
                break;

            default:
                error(ERR_DATE);

                centinela = true;
                break;
       }
    }

    return centinela;
}

void Task::setDeadline(string deadline){
    Date fecha;
    bool ok = true;
    stringstream buffer(deadline);

    buffer >> fecha.day;
    buffer.get();
    buffer >> fecha.month;
    buffer.get();
    buffer >> fecha.year;
    ok = CompDeadLine(fecha);
    if(ok)
        this->deadline = fecha;
    else
        Util::error(ERR_DATE);
}

void Task::setTime(int time){
    if(time < 1 || time > 180)
        Util::error(ERR_TIME);
    else
        this->time = time;

void Task::toggle(){
    isDone = !isDone;
}

ostream operator<<(ostream &os, Task &task){
    Date fecha;
    
    os << "[";
    if(task.getIsDone()){
        os << "X";
    }else{
        os << " ";
    }
    os << "] (" << task.getTime() << ") ";
    fecha = task.getDeadline();
    os << fecha.year << "-" << fecha.month << "-" << fecha.day << " : " << task.getName();
    return os;
}

