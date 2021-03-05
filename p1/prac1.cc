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
void mostrar(Task task);
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
 
        if(nombre.empty() == true){
            error(ERR_EMPTY);//Si no se introduce nada entonces error
        }
          
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

void contadornX(int &notHecho, int &numnotHecho, Project toDoList, int i, int j){
   notHecho = notHecho + toDoList.lists[i].tasks[j].time;
   numnotHecho++;
}

void contadorX(int &tHecho,int &numHecho,Project toDoList, int i, int j){
   tHecho = tHecho + toDoList.lists[i].tasks[j].time;
   numHecho++;
}

void Imprimidor(int furg , Project toDoList, int i, int j, bool &centinela, Date &prioritario, string &nombre,int &numnotHecho, int &notHecho, int &numHecho, int &tHecho){
    cout << "[";
    //Si esta tHecho imprimira una X
    if(toDoList.lists[i].tasks[j].isDone == true){
        cout << "X";
        contadorX(tHecho, numHecho, toDoList, i, j);
        //Si no esta tHecho simplemente imprimirá un espacio
    }else{
        cout << " ";
        contadornX(notHecho, numnotHecho, toDoList, i, j);

        //Imprime la informacion del las fechas.        
        cout << "] (" << toDoList.lists[i].tasks[j].time << ") "
        << toDoList.lists[i].tasks[j].deadline.year << "-"
        << toDoList.lists[i].tasks[j].deadline.month << "-"
        << toDoList.lists[i].tasks[j].deadline.day
        << " : " << toDoList.lists[i].tasks[j].name << endl;
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
    int num = 0;
  
    borrar = CompLista();
    num = FindList(borrar, toDoList);//Encuentra la posición de la lista en el vector
     
    if(num == -1){
        error(ERR_LIST_NAME);
 
    }else{
        toDoList.lists.erase(toDoList.lists.begin()+num);//Borra la posición encontrada en el vector
    }
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
    bool centinela = false;
    borrar = CompLista();
    Lpos=FindList(borrar,toDoList);

    if(Lpos == -1){
        error(ERR_LIST_NAME);
    }else{
  
        cout << "Enter task name: ";
        getline(cin, borrar);

        for(unsigned i = 0; i <= toDoList.lists[Lpos].tasks.size();i++){
            if(toDoList.lists[Lpos].tasks[i].name == borrar){

                centinela = true;
                toDoList.lists[Lpos].tasks.erase(toDoList.lists[Lpos].tasks.begin()+i);
            }
        }
        if(centinela == false){
            error(ERR_TASK_NAME);
        }
    }
}
void toggleTask(Project &toDoList){
    string cambiar;
    int Lpos = -1;

    bool centinela = false;
    cambiar = CompLista();
    Lpos=FindList(cambiar, toDoList);
    
    if(Lpos == -1){
       error(ERR_LIST_NAME);
  
    }else{
        cout << "Enter task name: ";
        getline(cin, cambiar);
        
            for(unsigned i = 0;i < toDoList.lists[Lpos].tasks.size();i++){
                if (toDoList.lists[Lpos].tasks[i].name == cambiar){
                    centinela = true;
                    toDoList.lists[Lpos].tasks[i].isDone  = true;

                }
            }
            if(centinela == false){
                error(ERR_TASK_NAME);
            }
    }
}
 
Task comparador(Task urgente, Task potencial){
    int fUrg;
    int fPot;
    Task resultado = urgente;
  
    fUrg = convertidor(urgente.deadline);
    fPot = convertidor(potencial.deadline);
 
    if(fUrg > fPot){
        resultado = potencial;
    } else  if(fUrg < fPot){
       resultado = urgente;
    } else {
       resultado = urgente;
    }
 
   return resultado;
}
 
void report(const Project &toDoList){

    //Imprime el nombre del proyecto
    int tHechas = 0, tNoHechas = 0 , hechas = 0, noHechas = 0;
    int centinela = 0;
    Task urgente;
 
 
    cout << "Name: " << toDoList.name << endl;
    if(toDoList.description != ""){
        cout << "Description: " << toDoList.description << endl;
    }
  
    for(unsigned i = 0; i< toDoList.lists.size();i++){
        cout << toDoList.lists[i].name << endl;
        for(unsigned j = 0; j< toDoList.lists[i].tasks.size();j++){
            if(toDoList.lists[i].tasks[j].isDone == false){
                mostrar(toDoList.lists[i].tasks[j]);
                tNoHechas += toDoList.lists[i].tasks[j].time;
                noHechas ++;
    
                if(centinela == 0){
                    urgente = toDoList.lists[i].tasks[j];
                    centinela++;
                }else{
                    urgente = comparador(urgente,toDoList.lists[i].tasks[j]);
                }
            }
       }
        for(unsigned k = 0; k< toDoList.lists[i].tasks.size();k++){
            if(toDoList.lists[i].tasks[k].isDone == true){
                mostrar(toDoList.lists[i].tasks[k]);
                tHechas += toDoList.lists[i].tasks[k].time;
                hechas ++;
            }
        }
    }
 
   cout << "Total left: " << noHechas << " (" << tNoHechas << " minutes)" << endl;
   cout << "Total done: " << hechas << " (" << tHechas << " minutes)" << endl;
   if(noHechas != 0){
       cout << "Highest priority: " << urgente.name << " (" << urgente.deadline.year << "-" << urgente.deadline.month << "-" << urgente.deadline.day << ")" << endl;
   }
}
 
 
void mostrar(Task task){
   if(task.isDone){
       cout << "[X] (" ;
   }else{
       cout << "[ ] (" ;
   }
   cout << task.time << ") " << task.deadline.year << "-" << task.deadline.month << "-" << task.deadline.day << " : " << task.name << endl;
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
//16 horas
 
 
 
