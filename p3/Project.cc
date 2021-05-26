
    #include "Project.h"


    Project::Project(string name, string description){
        this->name = name;
        this->description = description;
    }

    int Project::getId()const{
        return id;
    }

    string Project::getName()const{
        return name;
    }
    string Project::getDescription()const{
        return description;
    }
    int Project::getPosList(string name)const{
        int resultado = -1;
        for(unsigned i = 0; i < lists.size(); i++){
            if(lists[i].getName() == name){
                resultado = i;
            }
        }
        return resultado;
    }
    bool Project::setId(int id){
        bool resultado = false;

        if(id>=0){
            this-> id= id;
            resultado = true;
        }else{
            Util::error(ERR_ID);
        }
        return resultado;
    }
    bool Project::setName(string name){
        bool resultado = false;
        if(name.empty()){
            Util::error(ERR_EMPTY);
        }else{
            this-> name = name;
            resultado = true;
        }
        return resultado;
    }

    void Project::setDescription(string description){
        this-> description = description;
    }
void Project::edit(string name, string description){
    if(name.empty()){
        do{
            cout << "Enter project name: ";
            getline(cin, name);
            if(name.empty())
                Util::error(ERR_EMPTY);
        }while(name.empty());
    }
    if(description.empty()){
        cout << "Enter project description: ";
        getline(cin, description);
    }
    this-> name = name;
    this-> description = description;

}


    /*Añade una nueva lista con el nombre pasado como parámetro alproyecto. 
    El parámetro puede omitirse (o ser la cadena vacía), en cuyo caso se pedirá al usuario queintroduzca el nombre de la lista
    con el mensaje habitual (Enter list name:). 
    El comportamientode este método, en cuanto a mensajes, errores y comprobaciones, es igual a la opciónAdd 
    listdelaPráctica 2*/
string CompLista(){
    string nombre;
    do{
        cout << "Enter list name: ";
        getline(cin,nombre);//Introduce el nombre
 
        if(nombre.empty()){
            Util::error(ERR_EMPTY);//Si no se introduce nada entonces error
        }
          
    }while(nombre.empty());

    return nombre;
}
void Project::addList(string name){
    if(name.empty()){
        name = CompLista();
    }
    //Mira si la lista estaba anteriormente
    if(getPosList(name) !=  -1){
        Util::error(ERR_LIST_NAME);
    }else{
        List nuevo(name);
        lists.push_back(nuevo);
    }
}
/*Borra la lista con nombre del proyecto,
 es decir, la elimina del vector lists.
  Si el parámetro pasado se omite
  usuario que introduzca el nombre de la lista con el mensaje habitual.
   El comportamiento del método, encuanto a mensajes, errores y comprobaciones, es igual a la opciónDelete listde laPráctica 2*/

void Project::deleteList(string name){
    string borrar = "";
    int num = 0;
    if(name.empty())
    borrar = CompLista();
    else
    borrar=name;
    num = getPosList(borrar);//Encuentra la posición de la lista en el vector
     
    if(num == -1){
        Util::error(ERR_LIST_NAME);
 
    }else{
        lists.erase(lists.begin()+num);//Borra la posición encontrada en el vector
    }
}

/* Añade una nueva tarea a una lista con nombrenamedelproyecto
. El parámetro puede omitirse (o ser la cadena vacía),
 en cuyo caso se pedirá al usuarioque introduzca el nombre de la lista con el mensaje habitual
 . Si el nombre es correcto se pedirá alusuario el nombre de la tarea, la fecha de finalización y el tiempo estimado,
  se creará la tarea y seañadirá a la lista. 
  Se usarán los mismos mensajes y se emitirán los mismos errores que en la opciónAdd taskde laPráctica 2*/
bool CompDeadLine(Task nueva){
    bool centinela = false;
    Date sfecha=nueva.getDeadline();

    if (( sfecha.year>2100 ||  sfecha.year<2000)){
        Util::error(ERR_DATE);
        centinela = true;
    }
    else{
        switch ( sfecha.month){
            case 1 :
            case 3 :
            case 5 :
            case 7 :
            case 8 :
            case 10:
            case 12:
                if( sfecha.day<0 ||  sfecha.day>31){
                    Util::error(ERR_DATE);

                    centinela = true;
                }
                break;

            case 2:
                if(( sfecha.year%100 == 0 &&  sfecha.year%400 == 0) || ( sfecha.year%100 != 0 &&  sfecha.year%4 == 0)){
                    if ( sfecha.day<0 ||  sfecha.day > 29){
                        Util::error(ERR_DATE);
                        centinela = true;
                    }
                }else{
                    if ( sfecha.day<0 ||  sfecha.day > 28){
                        Util::error(ERR_DATE);
                        centinela = true;
                    }
                }
                break;

            case 4 :
            case 6 :
            case 9 :
            case 11:
                if ( sfecha.day<0 ||  sfecha.day > 30){
                    Util::error(ERR_DATE);

                    centinela = true;
                }
                break;

            default:
                Util::error(ERR_DATE);

                centinela = true;
                break;
       }
    }

    return centinela;
}
void Project::addTaskToList(string name){
    int num;
    int tiempo;
    string recogedor;
    string Tname;

    if(name.empty())
        name = CompLista();

    num=getPosList(name);
    
    if(num != -1){
        cout << "Enter task name: ";
        getline(cin,Tname);
        Task nueva(Tname);
      
        cout << "Enter deadline: ";
        getline(cin, recogedor);
        if(nueva.setDeadline(recogedor)){
            cout << "Enter expected time: ";
            cin >> tiempo;
            cin.get();
 
            if(nueva.setTime(tiempo)){
                lists[num].addTask(nueva);
            }
        }
    }else{
        Util::error(ERR_LIST_NAME);
    }
}
/*Borra una o más tareas de la lista con el nombrepasado como parámetro.
El parámetro puede omitirse (o ser la cadena vacía), en cuyo caso se pediráal usuario que introduzca el
 nombre de la lista con el mensaje habitual. 
 El comportamiento de estemétodo, en cuanto a mensajes, errores y comprobaciones,
  es igual a la opciónDelete taskde laPráctica 2*/
void Project::deleteTaskFromList(string name){
    int Lpos;
    string Tname;
    if(name.empty()){
        //Comprobamos que la lista no esta vacia
        name = CompLista();
    }
    //Obtenemos la posicion de la lista
    Lpos=getPosList(name);
    
    if(Lpos == -1){
        Util::error(ERR_LIST_NAME);
    }else{
        //Nos pone el nombre de la tarea
        cout << "Enter task name: ";
        getline(cin, Tname);
        lists[Lpos].deleteTask(Tname);

    }
}
void Project::toggleTaskFromList(string name){
    int Lpos = -1;

    if(name.empty()){
        name=CompLista();
    }

    Lpos=getPosList(name);
    
    if(Lpos == -1){
       Util::error(ERR_LIST_NAME);
  
    }else{
        cout << "Enter task name: ";
        getline(cin, name);
        lists[Lpos].toggleTask(name);
    }


}
/*Permite editar los datos del proyecto,
 como en la opciónProject menude la prác-tica anterior,
  mostrando el menú y gestionando las opciones.
   La única diferencia es que no deberáde mostrarse el mensaje solicitando
    el id del proyecto, sino directamente el menú.
     Las opciones deberán manejarse empleando los métodos descritos en este enunciado
      (por ejemplo, el métododeleteTaskFromListdescrito más arriba te va a permitir manejar la opciónDelete taskdel me-nú). En el caso de la funcionalidadReportdel menú, ésta es equivalente a la información quemuestra el operador de salidaoperator<<de la claseProject, tal y como se muestra más aba-jo. Para invocar dentro demenual operador de salida sobre el objetoProject, tendrás que hacercout << *this << endl;, donde*thishace referencia al propio objeto sobre el que se ha invocadoel métodomenu*/
void mostrar(Task task){
    Date fecha;
   if(task.getIsDone()){
       cout << "[X] (" ;
   }else{
       cout << "[ ] (" ;
   }
    fecha = task.getDeadline();

   cout << task.getTime() << ") " << fecha.year << "-" << fecha.month << "-" << fecha.day << " : " << task.getName() << endl;
}
void mainmenuMenu(){
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

bool comparador(Date urgente, Date potencial){
    return 10000*potencial.year + 100*potencial.month + potencial.day < 
            10000*urgente.year + 100*urgente.month + urgente.day;
}
void Project::menu(){
char option;
do{
    mainmenuMenu();
    cin >> option;
    cin.get();

    switch(option){
        case '1':  edit();
            break;
        case '2':  addList();

            break;
        case '3':  deleteList();
            break;
        case '4':   addTaskToList();

            break;
        case '5': deleteTaskFromList();
        
           break;
        case '6': toggleTaskFromList();
       
            break;
        case '7': cout << *this << endl;

    //Imprime el nombre del proyecto
    

            break;
        case 'b':   
        break;
        default:
            Util::error(ERR_OPTION);

    }
}while(option!='b');
}

string Project::summary()const {
    int suma=0, suma2=0;
    string final;
    stringstream resultado;
            for(unsigned i = 0; i< lists.size(); i++){
            suma += lists[i].getNumDone();
            suma2 += lists[i].getNumTasks();
        }
        resultado << "(" << getId() << ") " << getName() << " [" << suma << "/" << suma2 << "]";
        getline(resultado, final);
        return final;
}
ostream& operator<<(ostream &os,const Project &project){
    //Imprime el nombre del proyecto
    int tHechas = 0, tNoHechas = 0, hechas = 0, noHechas = 0;
    int centinela = 0;
    string Unombre;
    Date Ufecha;
    bool cambio;

    os << "Name: " << project.name << endl;
    if (project.description != "")
    {
        os << "Description: " << project.description << endl;
    }

    for (unsigned i = 0; i < project.lists.size(); i++)
    {
        os << project.lists[i] << endl;
        vector<Task> tasks = project.lists[i].getTasks();

        for (unsigned j = 0; j < tasks.size(); j++){
            if (!tasks[j].getIsDone()){
                //SUma el tiempo de las queno estan hechas
                tNoHechas += tasks[j].getTime();
                //Suma numero de hechas
                noHechas++;

                if (centinela == 0){
                    Task nueva(tasks[j].getName());
                    Unombre = tasks[j].getName();
                    Ufecha=tasks[j].getDeadline();
                    centinela++;
                }
                else{
                    cambio = comparador(Ufecha, tasks[j].getDeadline());
                    if(cambio){
                        Ufecha=tasks[j].getDeadline();
                        Unombre = tasks[j].getName();
                    }

                }
            }  
        }
        tHechas += project.lists[i].getTimeDone();
        hechas += project.lists[i].getNumDone() ; 

    }

    os << "Total left: " << noHechas << " (" << tNoHechas << " minutes)" << endl;
    os << "Total done: " << hechas << " (" << tHechas << " minutes)" << endl;
    if (noHechas != 0)
    {
        os << "Highest priority: " << Unombre << " (" << Ufecha.year << "-" << Ufecha.month << "-" << Ufecha.day << ")" << endl;
    }
    return os;
}

