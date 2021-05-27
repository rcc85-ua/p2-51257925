//DNI:51257925X    Nombre:Rayane Chelihi Chelouche
#include "ToDo.h"

int ToDo::nextId = 1;

ToDo::ToDo(string name){
    if(!name.empty())
        this->name = name;
    else
        throw ERR_EMPTY;
}

string ToDo::getName() const{
    return name;
}

int ToDo::getPosProject(string name) const{
    int resultado = -1;

    for(unsigned i=0; i< projects.size(); i++){
        if(projects[i]->getName() == name)
            resultado = i;
    }
    return resultado;
}

int ToDo::getPosProject(int id)const {
    int resultado = -1;

    for(unsigned i=0; i< projects.size(); i++){
        if(projects[i]->getId() == id)
            resultado = i;
    }
    return resultado;
}

bool ToDo::setName(string name){
    bool resultado = false;

    if(name.empty()){
        Util::error(ERR_EMPTY);

    }else{
        this-> name = name;
        resultado = true;
    }

    return resultado;
}

void ToDo::addProject(Project *project){
    int i=getPosProject(project->getName());
        if(i!=-1){
            throw ERR_PROJECT_NAME;
        }
    project->setId(nextId);
    nextId++;
    projects.push_back(project); //asterisco mirar(no se si esta bien o no u.u)
}

void ToDo::deleteProject(int id){
    int borrar = -1;
    if(id== 0){
        cout << "Enter project id: " << endl;
        cin >> id;
    }
    for(unsigned i = 0; i < projects.size();i++){
        if(id == projects[i]->getId()){
            borrar = i;
        }
    }
    if(borrar != -1){
        projects.erase(projects.begin()+borrar);
    }else{
        Util::error(ERR_ID);
    }
}
void ToDo::setProjectDescription(string name, string description){
    int id2=-1;
    
    for(unsigned i=0; i< projects.size(); i++){
        if(name == projects[i]->getName()){
            id2 = i;
        }
    }
    if(id2 !=-1)
    projects[id2]->setDescription(description);
    else
    Util::error(ERR_ID);
}
//Comprueba que el proyecto existe
int ToDo::CompMenu( int id)
{
    int resultado = -1;

    for (unsigned i = 0; i < projects.size(); i++)
    {
        if (projects[i]->getId() == id)
        {
            resultado = i;
        }
    }
    return resultado;
}
/*Busca un proyecto con el identificador pasado como parámetro ymuestra el menú de edición usando
 el métodomenudeProject.
  Si el parámetro se omite, o vale0,se le pedirá al usuario que introduzca el identificador
   del proyecto con el mensaje “Enter projectid:”, igual que se hacía en la opciónProject menude laPráctica 2. Si no hay ningún proyecto coneseidmostrará el errorERR_IDy no se hará nada más*/

void ToDo::projectMenu(int id){
    int Pos;
    if(id == 0){
        cout << "Enter project  id: ";
        cin >> id;
        cin.get();
        Pos = CompMenu(id);
        if (Pos == -1)
        {
            Util::error(ERR_ID);
        }
        else
        {
            projects[Pos]->menu();
        }
    }
}
ostream& operator<<(ostream &os,const ToDo &ToDo){
    for(unsigned i=0; i < ToDo.projects.size(); i++){
        os << ToDo.projects[i]->summary() << endl;
    }
    return os;
}