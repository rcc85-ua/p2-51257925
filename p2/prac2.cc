//DNI: 51257925X CHELIHI CHELOUCHE, RAYANE
#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <vector>
#include <cstdlib>
#include <string.h>
#include <fstream>
using namespace std;

const int KMAXNAME = 20;
const int KMAXDESC = 40;


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

struct BinToDo{
    char name[KMAXNAME];
    unsigned numProjects;
};

struct BinProject{
    char name [KMAXNAME];
    char description [KMAXDESC];
    unsigned numLists;
};
 
struct BinList{
    char name[KMAXNAME];
    unsigned numTasks;
};

struct BinTask{
    char name[KMAXNAME];
    Date deadline;
    bool isDone;
    int time;
};

struct ToDo{
    int nextId;
    string name;
    vector<Project> projects;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME,
  ERR_ID,
  ERR_PROJECT_NAME,
  ERR_FILE,
  ERR_ARGS
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
      break;
    case ERR_ID:
      cout << "ERROR: wrong project id" << endl;
      break;
    case ERR_PROJECT_NAME:
      cout << "ERROR: wrong project name" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
  }
}

/*Comprueba que El nombre introducido no esta vacio*/
string CompLista(){
    string nombre;
  
    do{
        cout << "Enter list name: ";
        getline(cin,nombre);//Introduce el nombre
 
        if(nombre.empty()){
            error(ERR_EMPTY);//Si no se introduce nada entonces error
        }
          
    }while(nombre.empty());

    return nombre;
}

int FindProject(ToDo LProject, string nombre){
    int resultado = -1;
    for(unsigned i=0; i<LProject.projects.size(); i++){
        if(LProject.projects[i].name == nombre){
            resultado = i;
        }
    }
    return resultado;
}

int FindProjectid(ToDo LProject, int id){
    int resultado = -1;
    for(unsigned i= 0; i<LProject.projects.size();i++){
        if(LProject.projects[i].id == id){
            resultado = i;
        }
    }
    return resultado;
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
int num=-1;
//Comprueba que el nombre introducido no esta vacio
for(unsigned i=0;i < toDoList.lists.size();i++){
  if(toDoList.lists[i].name == name){
    num = i;
  }
}
return num;
}
/*Hace las comprobaciones pertinentes de la fecha introducida en la deadline*/
bool CompDeadLine(Task nueva){
    bool centinela = false;
    if ((nueva.deadline.year>2100 || nueva.deadline.year<2000)){
        error(ERR_DATE);
        centinela = true;
    }
    else{
        switch (nueva.deadline.month){
            case 1 :
            case 3 :
            case 5 :
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

    return centinela;
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
    << "b- Back to main menu" << endl
    << "Option: ";
}
/*Cambia el nombre del proyecto*/
void editProject(Project &toDoList){
    string nombre = "";
 
    do{
        cout << "Enter project name: ";
        getline(cin,nombre);//Introduce el nombre
      
        if(nombre.empty())
            error(ERR_EMPTY);//Si no se introduce nada entonces error
    
    }while(nombre.empty());
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
    //bool centinela = false;
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
        cin.ignore();

        if(!CompDeadLine(nueva)){
            cout << "Enter expected time: ";
            cin >> nueva.time;
            cin.ignore();
            //cout << nueva.time << endl;
 
            if(nueva.time < 1 || nueva.time > 180){
                error(ERR_TIME);
 
            }else{
                nueva.isDone = false;
                toDoList.lists[num].tasks.push_back(nueva);
                //cout << "añadido" << endl;
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

        for(unsigned i = 0; i < toDoList.lists[Lpos].tasks.size();i++){
            if(toDoList.lists[Lpos].tasks[i].name == borrar){

                centinela = true;
                toDoList.lists[Lpos].tasks.erase(toDoList.lists[Lpos].tasks.begin()+i);
                --i;
            }
        }
        if(!centinela){
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
                    toDoList.lists[Lpos].tasks[i].isDone = !toDoList.lists[Lpos].tasks[i].isDone;

                }
            }
            if(!centinela){
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
//AQUI DECLARARÉ LAS COSAS DE LA PRACTICA 2

/*************************************************
********** FUNCIONES PRACTICA 2 *******************
**************************************************/
//Imprime el menu nuevo
void recogerdato(ifstream &fichero,Task Tnuevo,List Lnuevo){
char hecho;
bool verification;

    //Nombre del task
    getline(fichero, Tnuevo.name, '|');
    cout << "Nombre: " << Tnuevo.name << endl;
    //Fecha del task
    fichero >> Tnuevo.deadline.day;
    cout << "Dia: " << Tnuevo.deadline.day << endl;
    fichero.get();
    fichero >> Tnuevo.deadline.month;
    cout << "Mes: " << Tnuevo.deadline.month << endl;
    fichero.get();
    fichero >> Tnuevo.deadline.year;
    cout << "Año: " << Tnuevo.deadline.year << endl;
    fichero.get();
    if(!CompDeadLine(Tnuevo)){
        fichero >> hecho;
        cout << "Toggle?" << hecho << endl;
        error(ERR_DATE);
        verification = true;
    }
    //Tiempo del Task
    fichero >> Tnuevo.time;
    cout << "Tiempos" << Tnuevo.time << endl;
    fichero.get();
    //Si la fecha no es correcta
  
    //Si el tiempo no es correcto
    if(Tnuevo.time<1 && Tnuevo.time>180 && !verification){
        error(ERR_TIME);
        verification = true;
    }
    if(hecho == 'T'){
        Tnuevo.isDone = true;
    }
    if(hecho != 'F'){
        Tnuevo.isDone = false;
    }
    fichero.get();
    //Incluye los datos
    //Si ha habido fallos
    if(verification){
        Lnuevo.tasks.push_back(Tnuevo);
    }
}

void importdatos(ifstream &fichero,ToDo &Lprojects){
    char tipo;
    char primero;
    int pos;
    string Tnombre;
    Project Pnuevo;//Guarda los proyectos del fichero
    Task Tnuevo;//Guarda las tasks del fichero
    List Lnuevo;//Guarda las listas del fichero
    char papelera;

    fichero >> tipo;
    switch (tipo){
    //Empieza un nuevo proyecto
    case '<':
        break;
    //Nombre del proyecto
    case '#':
        //Guarda nombre del proyecto
        getline(fichero, Pnuevo.name);
        cout << "Nombre de Proyecto: " << Pnuevo.name << endl;
        break;
    //Descripción del proyecto
    case '*': 
        //Guarda descripcion del proyecto
        getline(fichero, Pnuevo.description);
        cout << "Descripción: " << Pnuevo.description << endl;
        fichero.get();
        break;
    //Nombre de una lista y sus tareas
    case '@': 
        //Guarda el nombre de la list
        getline(fichero, Lnuevo.name);
        Pnuevo.lists.push_back(Lnuevo);
        fichero.get();
        break;
    //Termina el proyecto
    case '>': 
        cout << "Fin de todo" << endl;
        if(FindProject(Lprojects, Pnuevo.name) == -1){
        Pnuevo.id=Lprojects.nextId;
        Lprojects.nextId++;
        Lprojects.projects.push_back(Pnuevo);
        }
        fichero.get();
        break;
    case '\n':
        break;
    default: 
        if(tipo > 'A' && tipo < 'z')
        recogerdato(fichero, Tnuevo, Lnuevo);
    }
}


void NewMenu(){
cout << "1- Project menu" << endl
    << "2- Add project" << endl
    << "3- Delete project"  << endl
    << "4- Import projects" << endl
    << "5- Export projects" << endl
    << "6- Load data" << endl
    << "7- Save data" << endl
    <<"8- Summary" << endl
    << "q- Quit" << endl
    << "Option: ";
}

//Imprime El menu antiguo
Project OldMenu(Project &Proyecto){
char option;

do{
    showMainMenu();
    cin >> option;
    cin.get();
    switch(option){
        case '1': editProject(Proyecto);
            break;
        case '2': addList(Proyecto);
            break;
        case '3': deleteList(Proyecto);
            break;
        case '4': addTask(Proyecto);
            break;
        case '5': deleteTask(Proyecto);
           break;
        case '6': toggleTask(Proyecto);
            break;
        case '7': report(Proyecto);
            break;
        case 'b': 
        break;
    }
}while(option!='b');
return Proyecto;
}

//Comprueba que el proyecto existe
int CompMenu(ToDo Proyectos,int id){
    int resultado = -1;

    for(unsigned i=0; i < Proyectos.projects.size(); i++){
        if (Proyectos.projects[i].id == id){
            resultado = i;         
        }
        
    }
    return resultado;
}

void ProjectMenu(ToDo Proyectos){
    int id, Pos;
    
    cout << "Enter project id: ";
    cin >> id;
    cin.get();
    Pos = CompMenu(Proyectos, id);
    if(Pos == -1){
        error(ERR_ID);
    }else{
        Proyectos.projects[Pos]=OldMenu(Proyectos.projects[Pos]);
    }
}
string compProjectEmpty(){
    string proyecto;
    do{
        cout << "Enter project name:  ";
        getline(cin,proyecto);
        if(proyecto.empty()){
            error(ERR_EMPTY);
        }
    }while(proyecto.empty());
return proyecto;
}

bool compProjectRepeat(ToDo Proyectos,string Posible){
    bool resultado = false;

    for(unsigned i = 0; i < Proyectos.projects.size();i++){
        if(Proyectos.projects[i].name == Posible){
            resultado = true;
        }
    }
    return resultado;
}
void addProject(ToDo &LProjects){
    Project nuevo;

    nuevo.name = compProjectEmpty();
    if(compProjectRepeat(LProjects, nuevo.name)){
        error(ERR_PROJECT_NAME);
    }else{
        cout << "Enter project description: ";
        getline(cin, nuevo.description);
        nuevo.id = LProjects.nextId;
        LProjects.projects.push_back(nuevo);
        LProjects.nextId++;
    }
    
}
//Busca un proyecto con la misma id que la introducida
int Compid(ToDo LProjects,int borrar){
    int pos = -1;
    for(unsigned i = 0; i < LProjects.projects.size();i++){
        if(borrar == LProjects.projects[i].id){
            pos = i;
        }
    }
    return pos;
}

void deleteProject(ToDo &LProjects){
    int borrar;
    
    cout << "Enter project id: ";
    cin >> borrar;
    borrar = Compid(LProjects, borrar);
    if(borrar != -1){
            LProjects.projects.erase(LProjects.projects.begin()+borrar);
    }else{
            error(ERR_ID);
    }
}


void importProject(ToDo &Lprojects){
    ifstream fichero;
    string nombre;
    bool checker = false;
    
    cout << "Enter filename: ";
    getline(cin, nombre);
    fichero.open(nombre.c_str());
    if(fichero.is_open()){

        while (!checker){
            checker = fichero.eof();
            importdatos(fichero,Lprojects);
        }
    }else{
    error(ERR_FILE);
    }
    fichero.close();
}
void exportaficheros(ofstream &fichero, ToDo LProjects){    
    for(unsigned i=0;i<LProjects.projects.size();i++){
        fichero << "<" << endl;
        fichero << "#" << LProjects.projects[i].name << endl;
        if(!LProjects.projects[i].description.empty()){
            fichero << "*" << LProjects.projects[i].description << endl;
        }
        for(unsigned j=0; j< LProjects.projects[i].lists.size();j++){
            fichero << "@" << LProjects.projects[i].lists[j].name << endl;
            for(unsigned k = 0; k < LProjects.projects[i].lists[j].tasks.size();k++){
                fichero << LProjects.projects[i].lists[j].tasks[k].name << "|"
                << LProjects.projects[i].lists[j].tasks[k].deadline.day << "/"
                << LProjects.projects[i].lists[j].tasks[k].deadline.month << "/"
                << LProjects.projects[i].lists[j].tasks[k].deadline.year << "|";
                if(LProjects.projects[i].lists[j].tasks[k].isDone){
                    fichero << "T";
                }else{
                    fichero << "F";
                }
                fichero << "|" << LProjects.projects[i].lists[j].tasks[k].time << endl;
            }
        }
    }
}
void imprimidorTask(Task tarea, ofstream &fichero){
    fichero << tarea.name << "|" << tarea.deadline.day << "/" << tarea.deadline.month << "/" << tarea.deadline.year << "|";
    if(tarea.isDone){
        fichero << "T";
    }else{
        fichero << "F";
    }
    fichero << "|" << tarea.time << endl;
}
void exportafichero(ofstream &fichero, ToDo proyecto,int pos){
    fichero << "<" << endl;
    fichero << "#" << proyecto.projects[pos].name << endl;
    if(!proyecto.projects[pos].description.empty()){
        fichero << "*" << proyecto.projects[pos].description << endl;
    }
    for(unsigned i=0; i < proyecto.projects[pos].lists.size();i++){
        fichero << "@" << proyecto.projects[pos].lists[i].name << endl;
        for(unsigned j = 0; j < proyecto.projects[pos].lists[i].tasks.size();j++){
            imprimidorTask(proyecto.projects[pos].lists[i].tasks[j], fichero);
        }
        fichero << ">" << endl;
    }
}
void exportProject(ToDo Lprojects){
    char resp;
    int id;
    int pos;
    string nombre;
    ofstream fichero;
    do{
    cout << "Save all projects [Y/N]?: ";
    cin >> resp;
    }while(resp != 'Y' && resp != 'y' && resp != 'N' && resp != 'n');
    switch(resp){
        case 'N':
        case 'n':
        cout << "Enter project id: ";
        cin >> id;
        cin.get();
        pos = FindProjectid(Lprojects, id );
        if(pos != -1){
            cout << "Enter filename: ";
            getline(cin, nombre);
            fichero.open(nombre.c_str());
            if(fichero.is_open()){
                exportafichero(fichero, Lprojects, pos);
                fichero.close();
            }else{
                error(ERR_FILE);
            }
        }else{
            error(ERR_ID);
        }
        break;
        case 'Y':
        case 'y':
            cout << "Enter filename: ";
            cin.get();
            getline(cin, nombre);
            fichero.open(nombre.c_str());
            if(fichero.is_open()){
                for(unsigned i=0; i< Lprojects.projects.size();i++){
                    exportafichero(fichero, Lprojects, i);
                }
            }
            break;
    }
}

void loadData(){

}

void saveData(){

}


void sumador(Project proyecto,int total,int hechos){
    total = 0;
    hechos = 0;
    for(unsigned i=0; i<proyecto.lists.size();i++){
        for(unsigned j=0; j<proyecto.lists[i].tasks.size();j++){
            if(proyecto.lists[i].tasks[j].isDone){
                hechos++;
            }
            total++;
        }
    }
}

void Summary(ToDo &LProjects){
    int total = 0, hechos = 0;

    for(unsigned i=0; i < LProjects.projects.size();i++){
        sumador(LProjects.projects[i], total, hechos);
        cout << "(" << LProjects.projects[i].id << ") " << LProjects.projects[i].name << "[" << hechos << "/" << total << "]" << endl;
    }
}

int main(){
ToDo LProjects;
Project toDoList;
toDoList.id=1;
char option;

LProjects.nextId = 1;

do{
    NewMenu();
    cin >> option;
    cin.get();
    switch(option){
        case '1': ProjectMenu(LProjects);
            break;
        case '2': addProject(LProjects);
            break;
        case '3': deleteProject(LProjects);
            break;
        case '4': importProject(LProjects);
            break;
        case '5': exportProject(LProjects);
            break;
        case '6': loadData();
            break;
        case '7': saveData();
            break;
        case '8': Summary(LProjects);
            break;
        case 'q':
            break;
        default:
            error(ERR_OPTION);
            break;
    }
}while (option != 'q');

return 0;
}
 
//4 horas