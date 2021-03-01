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
/*Comprueba que El nombre introducido no esta vacio*/
string CompLista(){
  string nombre;  
  do{
    cout << "Enter list name: ";
    getline(cin,nombre);//Introduce el nombre
    if(nombre.empty() == true)
      error(ERR_EMPTY);//Si no se introduce nada entonces error
  }while(nombre.empty() == true);

  return nombre;
}
/*Encuentra en una lista una Task*/
int FindTask(string borrar,int pos,Project toDoList){
  int resultado = -1;
  //Recorre todo el vector de Tareas de la lista de la posicion pos
  for(unsigned i = 0;i < toDoList.lists[pos].tasks.size();i++){
    if (toDoList.lists[pos].tasks[i].name == borrar){
      resultado = i;
    }
  }
return resultado;
}
/*Encuentra una Lista en el proyecto*/
int FindList(string name, Project toDoList){
  unsigned num=-1;
  //Comprueba que el nombre introducido no esta vacio

  for(unsigned i=0;i < toDoList.lists.size();i++){
    if(toDoList.lists[i].name == name){
      num = i;
    }
  }
return num;
}
/*Hace las comprobaciones pertinentes de la fecha introducida en la deadline*/
void CompDeadLine(bool &centinela,Task nueva){
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
}
int convertidor(Date fecha){
  int final = 0;
  final = fecha.year*10000+fecha.month*100+fecha.day;
  return final;
} 

void contadornX(int &nohecho, int &numnohecho, Project toDoList, int i, int j){
  nohecho = nohecho + toDoList.lists[i].tasks[j].time;
  numnohecho++;
}
void contadorX(int &hecho,int &numhecho,Project toDoList, int i, int j){
  hecho = hecho + toDoList.lists[i].tasks[j].time;
  numhecho++;
}
void Imprimidor(Project toDoList, int i, int j, bool &centinela, Date &prioritario, string &nombre,int &numnohecho, int &nohecho, int &numhecho, int &hecho){
          int fpotencial = 0, furg = 99999999;
          cout << "[";
          //Si esta hecho imprimira una X
          if(toDoList.lists[i].tasks[j].isDone == true){
            cout << "X";
            contadorX(hecho, numhecho, toDoList, i, j);
          //Si no esta hecho simplemente imprimirá un espacio
          }else{
            cout << " ";
            contadornX(nohecho, numnohecho, toDoList, i, j);

          //Convierte el el año,mes y dia en un un entero y lo almacena en potencial
          fpotencial = convertidor(toDoList.lists[i].tasks[j].deadline);
          //Si el potencial es el inferior se cambia a que es el mas urgente.
          
          if(fpotencial < furg){
            furg = fpotencial;
            centinela = true;
            prioritario = toDoList.lists[i].tasks[j].deadline;
            nombre = toDoList.lists[i].tasks[j].name;
          }
          }
          //Imprime la informacion del las fechas.          
          cout << "] (" << toDoList.lists[i].tasks[j].time << ") "
          << toDoList.lists[i].tasks[j].deadline.year << "-"
          << toDoList.lists[i].tasks[j].deadline.month << "-"
          << toDoList.lists[i].tasks[j].deadline.day
          << " : " << toDoList.lists[i].tasks[j].name << endl;
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

/*Cambia el nombre del proyecto*/
void editProject(Project &toDoList){
  string nombre = "";
  do{
    cout << "Enter project name: ";
    getline(cin,nombre);//Introduce el nombre
    if(nombre.empty() == true)
      error(ERR_EMPTY);//Si no se introduce nada entonces error
  }while(nombre.empty() == true);
toDoList.name = nombre;
cout << "Enter project description: ";
getline(cin,toDoList.description);
}

/*Añade una lista a un proyecto*/
void addList(Project &toDoList){
  List nuevo;
  nuevo.name = "";
  
    nuevo.name=CompLista();
    //Mira si la lista estaba anteriormente
    if(FindList(nuevo.name, toDoList) !=  -1){
      error(ERR_LIST_NAME);
    }else{
      toDoList.lists.push_back(nuevo);
    }
}
/*Borra una Lista de un proyeto*/
void deleteList(Project &toDoList){
string borrar = "";
unsigned num = 0;

borrar = CompLista();
num = FindList(borrar, toDoList);//Encuentra la posición de la lista en el vector
toDoList.lists.erase(toDoList.lists.begin()+num);//Borra la posición encontrada en el vector
}


/*Añade una tarea a una lista*/
void addTask(Project &toDoList){
string lista ="";
int num;
Task nueva;
bool centinela = false;
lista = CompLista();
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

  CompDeadLine(centinela, nueva);
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
/*Borra una task de una lista*/
void deleteTask(Project &toDoList){
string borrar;
int Lpos;
int Tpos;

borrar = CompLista();
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

cambiar = CompLista();
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
    toDoList.lists[Lpos].tasks[Tpos].isDone  = true;
  }
}
}
void report(const Project &toDoList){
int hecho = 0;
int numhecho = 0;
int nohecho = 0;
int numnohecho = 0;
bool centinela = false;
string nombre ="";
Date prioritario;
prioritario.year = 9999;
prioritario.month = 99;
prioritario.day = 99;

  cout << "Name: " << toDoList.name << endl;
  if(toDoList.description != "")
  cout << "Description: " << toDoList.description << endl;
  //Recorre el vector de listas
  for(unsigned i=0; i < toDoList.lists.size();i++){
      cout << toDoList.lists[i].name << endl;
      //Recorre el vector de tasks de list[i]
      for (unsigned j = 0; j < toDoList.lists[i].tasks.size();j++){
          Imprimidor(toDoList, i, j, centinela, prioritario, nombre, numnohecho, nohecho, numhecho, hecho);
      }
  }
  //Imprime la cantidad de tasks sin hacer
  cout << "Total left: " << numnohecho << " (" << nohecho << " minutes)" << endl;
  //Imprime la cantidad de tasks hechas
  cout << "Total done: " << numhecho << " (" << hecho << "minutes)" << endl;
  //Imprime la task con mayor prioridad
  if(numnohecho > 0){
  cout << "Highest priority: " << nombre << " ("
  << prioritario.year << "-" << prioritario.month << "-"
  << prioritario.day << ")" << endl;
  }
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
 
 
 
