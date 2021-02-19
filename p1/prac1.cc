#include <iostream>
#include <vector>
#include <cstdlib>
#include <string.h>
 
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

int FindTask(string borrar,int pos,Project toDoList){
 int resultado = -1;
 for(unsigned i = 0;i < toDoList.lists[pos].tasks.size();i++){
   if (toDoList.lists[pos].tasks[i].name == borrar){
     resultado = i;
   }
  
 }
 return resultado;
}

int FindList(string name, Project toDoList){
 unsigned num=-1;
   do{
       if(name.empty() == true){
           error(ERR_EMPTY);
       }
   }while(name.empty() == true);
   for(unsigned i=0;i < toDoList.lists.size();i++){
     if(toDoList.lists[i].name == name){
       num = i;
     }
   }
 return num;
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
   string nombre = "";
  
   do{
       cout << "Entrer project name: ";
       getline(cin,nombre);
   if(nombre.empty()){
       error(ERR_EMPTY);
   }
   }while(nombre.empty());
 toDoList.name = nombre;
 cout << "Enter project description: ";
 getline(cin,toDoList.description);
}
void addList(Project &toDoList){
   List nuevo;
   nuevo.name = "";
   //Mira si la lista esta vacia
   do{
     cout << "Enter list name :";
     getline(cin,nuevo.name);
     if(nuevo.name.empty() == true){
       error(ERR_EMPTY);
     }
   }while(nuevo.name.empty() == true);
     //Mira si la lista estaba anteriormente
     if(FindList(nuevo.name, toDoList) !=  -1){
       error(ERR_LIST_NAME);
     }else{
       toDoList.lists.push_back(nuevo);
      }
}
void deleteList(Project &toDoList){
 string borrar = "";
 unsigned num;
 do{
     cout << "Enter list name: ";
     getline(cin,borrar);//Introduce el nombre
     if(borrar.empty() == true)
     error(ERR_EMPTY);//Si no se introduce nada entonces salta el error
 }while(borrar.empty() == true);
 num = FindList(borrar, toDoList);//Encuentra la posición de la lista en el vector
 toDoList.lists.erase(toDoList.lists.begin()+num);//Borra la posición encontrada en el vector
}
void addTask(Project &toDoList){
 string lista = "";
 int num;
 Task nueva;
 bool centinela = false;
 do{
   cout << "Enter list name: ";
   getline(cin, lista);
   if(lista.empty() ==  true)
     error(ERR_EMPTY);
 }while(lista.size() == 0);
 num=FindList(lista, toDoList);
 if(num != -1){
   cout << "Enter task name: ";
   getline(cin,nueva.name);
   cout << "Enter deadline: ";
   cin >> nueva.deadline.day;
   cin.get();
   cin >> nueva.deadline.month;
   cin.get();
   cin >> nueva.deadline.year;
   if ((nueva.deadline.year>2100 || nueva.deadline.year<1900)){
     error(ERR_DATE);
   }
   switch (nueva.deadline.month){
   case 1 :
   case 3 :
   case 7 :
   case 8 :
   case 10:
   case 12:
   if(nueva.deadline.day<0 || nueva.deadline.day>31){
     error(ERR_DATE);
     centinela = true;
   }
     break;
   case 2:
   if((nueva.deadline.year%100 == 0 && nueva.deadline.year%400 == 0) || (nueva.deadline.year%100 != 0 && nueva.deadline.year%4 == 0)){
   if (nueva.deadline.day<0 || nueva.deadline.day > 29){
     error(ERR_DATE);
     centinela = true;
   }
   }else{
         if (nueva.deadline.day<0 || nueva.deadline.day > 28){
     error(ERR_DATE);
     centinela = true;
         }
   }
     break;
   case 4 :
   case 5 :
   case 6 :
   case 9 :
   case 11:
   if (nueva.deadline.day<0 || nueva.deadline.day > 30){
     error(ERR_DATE);
     centinela = true;
   }
     break;
   default:
     error(ERR_DATE);
     centinela = true;
     break;
   }
   if(centinela==false){
     cout << "Enter expected time: ";
     cin >> nueva.time;
     if(nueva.time < 1 || nueva.time > 180){
       error(ERR_TIME);
     }else{
     nueva.isDone = false;
     toDoList.lists[num].tasks.push_back(nueva);
     }
   }
   }else{
   error(ERR_LIST_NAME);
 }
}
void deleteTask(Project &toDoList){
 string borrar;
 int Lpos;
 int Tpos;
 do{
   cout << "Enter list name: ";
   getline(cin,borrar);
   if(borrar.empty()){
     error(ERR_EMPTY);
   }
 }while (borrar.empty());
 Lpos=FindList(borrar,toDoList);
 if(Lpos == -1){
   error(ERR_LIST_NAME);
 }else{
   cout << "Enter task name: ";
   getline(cin, borrar);
   Tpos=FindTask(borrar, Lpos, toDoList);
   if (Tpos == -1)
   {
     error(ERR_TASK_NAME);
   }else{
     toDoList.lists[Lpos].tasks.erase(toDoList.lists[Lpos].tasks.begin()+Tpos);
   }
  
 }
}
void toggleTask(Project &toDoList){
 string cambiar;
 int Lpos = -1;
 int Tpos = -1;
 do{
   cout << "Enter list name: ";
   getline(cin,cambiar);
   if(cambiar.empty()){
     error(ERR_EMPTY);
   }
 }while (cambiar.empty());
 Lpos=FindList(cambiar, toDoList);
 if(Lpos == -1){
   error(ERR_LIST_NAME);
 }else{
   cout << "Enter task name: ";
   getline(cin, cambiar);
   Tpos = FindTask(cambiar, Lpos, toDoList);
   if(Tpos == -1){
     error(ERR_TASK_NAME);
   }else{
     toDoList.lists[Lpos].tasks[Tpos].isDone  == true;
   }
 }
}
void report(const Project &toDoList){
 int hecho = 0;
 int numhecho = 0;
 int nohecho = 0;
 int numnohecho = 0;
 int fpotencial = 0;
 int furg = 0;
 string nombre ="";
 Date prioritario;
 prioritario.year = 2100;
 prioritario.month = 12;
 prioritario.day = 30;
   cout << "Name: " << toDoList.name << endl;
   if(toDoList.description != "")
   cout << "Description: " << toDoList.description << endl;
   for(unsigned i=0; i < toDoList.lists.size();i++){
       cout << toDoList.lists[i].name << endl;
       for (unsigned j = 0; j < toDoList.lists[i].tasks.size();j++){
           cout << "[";
           if(toDoList.lists[i].tasks[j].isDone == true){
             cout << "X";
             hecho = hecho + toDoList.lists[i].tasks[j].time;
             numhecho++;
           }else{
             cout << " ";
             nohecho = nohecho + toDoList.lists[i].tasks[j].time;
             numnohecho++;
 
           }
           fpotencial = toDoList.lists[i].tasks[j].deadline.year*10000+
           toDoList.lists[i].tasks[j].deadline.month*100+
           toDoList.lists[i].tasks[j].deadline.day;
           if(fpotencial > furg){
             furg = fpotencial;
             prioritario = toDoList.lists[i].tasks[j].deadline;
             nombre = toDoList.lists[i].tasks[j].name;
           }           
           cout << "] (" << toDoList.lists[i].tasks[j].time << ") "
           << toDoList.lists[i].tasks[j].deadline.year << "-"
           << toDoList.lists[i].tasks[j].deadline.month
           << toDoList.lists[i].tasks[j].deadline.day
           << " : " << toDoList.lists[i].tasks[j].name << endl;
       }
   }
   cout << "Total left: " << numnohecho << " (" << nohecho << "minutes)" << endl;
   cout << "Total done: " << numhecho << " (" << hecho << "minutes)" << endl;
   if(numnohecho>0)
   cout << "Highest priority: " << nombre << " ("
   << prioritario.year << "-" << prioritario.month << "-"
   << prioritario.day << ")";
  
}
 
 
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
     case 'q': break;
     default: error(ERR_OPTION);
   }
 }while(option!='q');
  return 0;   
}
//9 horas
 
 
 
