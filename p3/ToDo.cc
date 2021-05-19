#include "ToDo.h"
#include "project.h"
#include "Util.h"
#include <string.h>


ToDo::ToDo(string nombre){
    strcpy(name, nombre);

}

string getName(){
    return name;
}
int getPosproject(string name){
    int resultado = -1;

    for(unsigned i=0; i< ToDo.projects.size(); i++){
        if(ToDo.projects.name = name){
            resultado = i;
        }
    }
}
int getPosproject(int id){
    int resultado = -1;
    string name;

    for(unsigned i=0; i< projects.size(); i++){
        name = ToDo.projects[i].name;
        if(ToDo.projects.name = name){
            resultado = i;
        }
    }
    return i;
}

bool setName(string name){
    bool resultado = false;

    if(name.empty(){
        throw ERR_EMPTY;

    }else{
        this-> name = name;
        resultado = true;
    }

    return resultado;
}

void addProject(Project *project){
    Project project;

    for(unsigned i = 0; i < projects.size(); i++{
        if(projects[i].name == project*.name){
            trow ERR_POJECT_NAME;
        }
    }
    this-> project = project*;
    project.id = nextId;
    nextId++;
    projects.push_back(this->project);
}

void deleteProject(int id){
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