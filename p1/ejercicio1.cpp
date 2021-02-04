#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Date{
  int day;
  int month;
  int year;
};

struct Task{
  string name;
  Date deadline;
  bool isDone;
  int time;
};

struct List{
  string name;
  vector<Task> tasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME
};

void error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty string" << endl;
      break;
    case ERR_LIST_NAME:
      cout << "ERROR: wrong list name" << endl;
      break;
    case ERR_TASK_NAME:
      cout << "ERROR: wrong task name" << endl;
      break;
    case ERR_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_TIME:
      cout << "ERROR: wrong expected time" << endl;
  }
}

void showMainMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void editProject(Project &toDoList){
    string nombre;
    
    do{
        cout << "Entrer project name: ";
        getline(cin,nombre);
    if(nombre.size() == 0){
        error(ERR_EMPTY);
    }
    }while(nombre.size() == 0);
        toDoList.name = nombre;
        cout << "Enter project description: ";
        cin >> toDoList.description;
}

void addList(Project &toDoList){
    List nuevo;
    bool esta = false;
    do{
        cout << "Enter list name :";
        getline(cin,nuevo.name);
        if(nuevo.name.empty() == true){
            error(ERR_EMPTY);
        }
    }while(nuevo.name.empty() == true);
        for(int i=0;i < toDoList.name.size();i++){
            if(toDoList.lists[i].name == nuevo.name)
                esta = true;
        }
        if(esta ==  true){
            error(ERR_LIST_NAME);
        }else{
            toDoList.lists.push_back(nuevo);
        }
}

void deleteList(Project &toDoList){
    string borrar;

    do{
        cout << "Enter list name: ";
        cin >> borrar;
        if(borrar.size() == 0){
            error(ERR_EMPTY);
        }
    }while(borrar.size() == 0);
}

void addTask(Project &toDoList){
}

void deleteTask(Project &toDoList){
}

void toggleTask(Project &toDoList){
}

void report(const Project &toDoList){
}

//Función de prueba
/*
void mostrar(Project toDoList){
    for(int i=0; i < toDoList.lists.size();i++){
        cout << "La Lista: " << toDoList.lists[i].name << endl;
        for (int j = 0; j < toDoList.lists[i].tasks.size();j++){
            cout << "   La Task: ";
            cout << toDoList.lists[i].tasks[j].name << endl;

        }
    }
}
*/
int main(){
  Project toDoList;
  toDoList.id=1;
  char option;
  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': editProject(toDoList);
                break;
      case '2': addList(toDoList);
                break;
      case '3': deleteList(toDoList);
                break;
      case '4': addTask(toDoList);
                break;
      case '5': deleteTask(toDoList);
                break;
      case '6': toggleTask(toDoList);
                break;
      case '7': report(toDoList);
                break;
      /*FUNCION DE PRUEBA
      case '8': mostrar(toDoList);
                break;
      */
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}
//2 horas