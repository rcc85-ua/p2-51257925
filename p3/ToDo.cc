#include "ToDo.h"
#include "project.h"
#include "Util.h"
#include <string.h>

static const int nextId= 1;

ToDo::ToDo(string name){
    this->name = name;
}

string ToDo::getName(){
    return name;
}

int ToDo::getPosProject(string name){
    int resultado = -1;

    for(unsigned i=0; i< projects.size(); i++){
        if(projects[i]->getName() = name)
            resultado = i;
    }
    return resultado;
}

int ToDo::getPosProject(int id){
    int resultado = -1;

    for(unsigned i=0; i< projects.size(); i++){
        if(projects[i]->getId())
            resultado = i;
    }
    return resultado;
}

bool ToDo::setName(string name){
    bool resultado = false;

    if(name.empty(){
        throw ERR_EMPTY;

    }else{
        this-> name = name;
        resultado = true;
    }

    return resultado;
}

void ToDo::addProject(Project *project){

    for(unsigned i = 0; i < projects.size(); i++{
        if(projects[i].name == project*.name){
            throw ERR_POJECT_NAME;
        }
    }
    project->id = nextId;
    nextId++;
    projects.push_back(project*); //asterisco mirar(no se si esta bien o no u.u)
}

void ToDo::deleteProject(int id){
    int borrar = -1;
    int id;
    if(id == 0){
        os << "Enter project id: " << endl;
        is >> id;
    }
    for(unsigned i = 0; i < projects.size();i++){
        if(this-> id == LProjects.projects[i].id){
            borrar = i;
        }
    }
    if(borrar != -1){
        projects.erase(projects.begin()+borrar);
    }else{
        throw ERR_ID
    }
}

ostream operator<< (stream &os, ToDo &ToDo){
}