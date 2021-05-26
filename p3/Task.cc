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

string Task::getName()const {
    return name;
}

int Task::getTime()const {
    return time;
}

bool Task::getIsDone()const {
    return isDone;
}

Date Task::getDeadline()const{
    return deadline;
}

void Task::setName(string name){
    this->name = name;
}

bool Task::CompDeadLine(Date fecha){
    bool centinela = true;

    if ((fecha.year>2100 || fecha.year<2000)){
        centinela = false;
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
                if(fecha.day<1 || fecha.day>31){

                    centinela = false;
                }
                break;

            case 2:
                if((fecha.year%100 == 0 && fecha.year%400 == 0) || (fecha.year%100 != 0 && fecha.year%4 == 0)){
                    if (fecha.day<1 || fecha.day > 29){
                        centinela = false;
                    }
                }else{
                    if (fecha.day<1 || fecha.day > 28){
                        centinela = false;
                    }
                }
                break;

            case 4 :
            case 6 :
            case 9 :
            case 11:
                if (fecha.day<1 || fecha.day > 30){

                    centinela = false;
                }
                break;

            default:

                centinela = false;
                break;
       }
    }

    return centinela;
}

bool Task::setDeadline(string deadline){
    Date fecha;
    bool ok = true;
    stringstream buffer(deadline);
    bool resultado = false;

    buffer >> fecha.day;
    buffer.get();
    buffer >> fecha.month;
    buffer.get();
    buffer >> fecha.year;
    ok = CompDeadLine(fecha);
    if(ok){
        this->deadline = fecha;
        resultado= true;
    }else
        Util::error(ERR_DATE);
    return resultado;
}

bool Task::setTime(int time){
    bool resultado = false;

    if(time < 1 || time > 180)
        Util::error(ERR_TIME);
    else{
        this->time = time;
        resultado = true;
    }
    return resultado;
}
void Task::toggle(){
    isDone = !isDone;
}

ostream& operator<<(ostream &os,const Task &task){
    Date fecha;
    
    os << "[";
    if(task.isDone){
        os << "X";
    }else{
        os << " ";
    }
    os << "] (" << task.time << ") ";
    fecha = task.deadline;
    os << fecha.year << "-" << fecha.month << "-" << fecha.day << " : " << task.name;
    return os;
}

