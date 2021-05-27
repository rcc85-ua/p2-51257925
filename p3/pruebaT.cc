#include <iostream>
#include "Task.h"
#include "List.h"
int main(){
    string name="prueba";
    //Task Tarea(name);
    Task Tarea2("prueba 2");
    Tarea2.setDeadline("04/02/2019");
    Tarea2.setTime(80);
    //Tarea.toggle();
    List Lista("Lista de prueba");
    Date fecha={01,8,2020};
    //Tarea.setDeadline("01/08/2020");
  //  Tarea.setTime(45);
    //Lista.addTask(Tarea);
    Lista.addTask(Tarea2);
    cout << Lista.getNumTasks() << endl;
    cout << Lista << endl;
    return 0;
    }