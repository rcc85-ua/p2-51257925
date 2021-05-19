    #include <string.h>
    #include <sstream>
    #include "project.h"
    #include "List.h"
    #include "Task.h"
    #include "Util.h"

    Project(string name, string description = ""){
        this->name = name;
        this->description = description;
    }

    int getId(){
        return id;
    }

    string getName(){
        return name;
    }
    string getDescription(){
        return description;
    }
    int getPosList(string name){
        int resultado = -1

        for(unsigned i = 0; i < lists.size(); i++){
            if(this->lists[i].name = name){
                resultado = this-> id;
            }
        }
        return resultado;
    }
    bool setId(int id){
        bool resultado = false;

        if(id>=0){
            this-> id= id;
            resultado = true;
        }else{
            throw ERR_ID;
        }
        return resultado;
    }
    bool setName(string name){
        bool resultado = false;
        if(name.empty()){
            throw ERR_EMPTY;
        }else{
            this-> name = name;
            resultado = true;
        }
        return resultado;
    }

    void setDescription(string description){
        this-> description = description;
    }
    void edit(string name ="", string description=""){
        if(name.empty()){
            do{
                cout << "Enter project name: ";
                cin >> name;
            }while(name.empty());
        }
        if(description.empty()){
            do{
                cout << "Enter project description: ";
                cin >> description;
            }while(description.empty());
            this-> name = name;
            this-> description = description;
        }

    }
    void addList(string name=""){}
    void deleteList(string name=""){}
    void addTaskToList(string name=""){}
    void deleteTaskFromList(string name=""){}
    void toggleTaskFromList(string name=""){}
    void menu(){}
    string summary()  {}