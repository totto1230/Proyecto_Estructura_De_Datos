#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ctime>

//Se define que se va a utilizar el namespace "std"
using namespace std;
//Se declara el archivo que va a servir para loguear la info
ofstream file;

//Se declara la estructura para lista principal
struct nodo{
    char especialidad;
    nodo *sig;
};
//Se crea un typo de estructura tipo nodo para poder usarla en el código
typedef struct nodo *lista;

/**************************************************************
 ***************Metodos para loguear informacion***************
 ***************************************************************/

//Este metodo retorna un puntero char el cual contiene la fecha del momento para poder hacer logging and auditing
char* get_time() {
	   // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);
   return dt;
}

void logging(){
	//ofstream file;
	file.open("logs.txt",ios::out);
	char* fechaActual= get_time();
	if(file.fail()){
		cout<<"ERROR WHILE LOGGING, CONTACT JOSEPH OR SEBASTIAN FOR FURTHER HELP!"<< endl;	
		exit(1);
	}
	file<<fechaActual<<"Sistema Cargado"<< endl;
}

/********************************************************************************************
 ***************METODOS CREAR LISTA PRINCIPAL - ESPECIALIDADES MEDICAS - ADMIN***************
 ********************************************************************************************/

//Este método crea un Nodo el cual recibe de parametro una cabeza de tipo lista 
nodo *crearNodoDocs(lista &cab, char especialidad){
    char* fechaActual= get_time();
    nodo *nuevo_nodo= new (struct nodo);
    nuevo_nodo->especialidad=especialidad;
    nuevo_nodo->sig=NULL;
    return nuevo_nodo;
    file<<fechaActual<<"NODO CREADO" << endl;
}

void crearListaPrincipalDocs(lista &cab, char especialidad){
    nodo *nuevo_nodo= crearNodoDocs(cab, especialidad);
    if(cab==NULL){
        cab=nuevo_nodo;
    }
    else{
        nuevo_nodo->sig=cab;
        cab=nuevo_nodo;
    }

}

void crearNodosListaPrincipalDefaultEspecialidades(lista &cab){
    /*  Especialidades by default:
        C=Cardiologia
        D=Dermatologia
        O=Oftalmología
        N=Neurología
        P=Pediatría
        U=Urología
        R=Reumatología
    */
    char* fechaActual= get_time();
    file<<fechaActual<<" ADDED DEFAULT ESPECIALIDADES"<< endl;
    crearListaPrincipalDocs(cab,'R');   
    crearListaPrincipalDocs(cab,'U');
    crearListaPrincipalDocs(cab,'P');
    crearListaPrincipalDocs(cab,'N');
    crearListaPrincipalDocs(cab,'O');
    crearListaPrincipalDocs(cab,'D');
    crearListaPrincipalDocs(cab,'C');
}


void mostrar(lista cab){
    lista auxRecorrer;
    if(cab==NULL){
        cout<<"LISTA NULL" << endl;
    }
    else{
        auxRecorrer=cab;
        while(auxRecorrer!=NULL){
            cout<< auxRecorrer->especialidad << " ----------> ";
            auxRecorrer=auxRecorrer->sig;
        }
    }
    char* fechaActual= get_time();
    file<<fechaActual<<" SHOWED LISTA &: "<< &cab<< endl;
}

//Método que borra una especialidad, recibe una lista y el identificador único a eliminar
void borrarEspecialidad(lista &cab, char identificador){
    //Se crean dos nodos para aux para poder unir la lista resultante y encontrar el nodo a eliminar
    nodo *aux; //Nodo a eliminar
    nodo *aux2; //Nodo que sirva para unir la lista
    char* fechaActual= get_time(); //logging
    
    //Se valida la lista que no sea nula
    if(cab != NULL){    
    aux2=NULL;
    //Se iguala el aux a borrar con la lista que se recibe como parametro
    aux=cab;
    }

    //Se recorre la lista siempre y cuando no sea NULL ni el identificador único a eliminar
    while((aux!=NULL) && (aux->especialidad!=identificador)){
            //Se coloca el aux2 en la posición actual del aux
            aux2=aux;
            //Y se mueve aux, indirectamente aux2 es el anterior de aux
            aux=aux->sig;
    }
    //logging
    file<<fechaActual<<"DELETED ESPECIALIDAD: "<< aux->especialidad<<endl;
    if( aux2==NULL){
        cab=cab->sig;
        //Se borra el nodo aux
        delete(aux);
    }
    else{
        //Se une la lista antes de borrarla para evitar que quede aux2 apuntando a un NULL
        aux2->sig=aux->sig;
        //Se borra el nodo aux
        delete (aux);
    }
 }    


void actualizarEspecialidad(lista &cab, char identificador, char nuevo){
    char* fechaActual= get_time(); //logging
    lista aux;
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA: " << &cab<<endl;
    }
    else{
        aux=cab;
        while((aux!=NULL) && (aux->especialidad!=identificador)){
         aux=aux->sig;
        }
        file<<fechaActual<<"ESPECIALIDAD UPDATED FROM: "<< aux->especialidad << " TO " << nuevo <<endl;
        aux->especialidad=nuevo;

    }
}



void menuEspecialidades (){
    lista Lista=NULL;
    //Variables usada en el menu
    int opc,opc2;
    char especialidades,toDelete,fromUpdate,toUpdate;
    string nombreEspecialidad;
    logging();

    //login
    char* fechaActual= get_time();
    file<<fechaActual<<"ADMIN LOGGED SUCCESSFULLY TO MENUESPECIALIDADES"<<endl;
    crearNodosListaPrincipalDefaultEspecialidades(Lista);
    do{       
        system("cls"); 
        cout<<"Bienvenido Admin!, favor elegir alguna opcion"<< endl;
        cout<<" 1. Agregar Especialidades \n 2. Borrar Alguna Especialidad \n 3. Actualizar el nombre de alguna especialidad \n 4. Mostrar Lista Actual \n :";
        cin>>opc;
        switch(opc){
            case 1:
            system("cls");
            cout<<"HEMOS AGREGADO LAS ESPECIALIDADES POR DEFECTO DEL HOSPITAL, DESEA AGREGAR ALGUNA MAS? \n 1. Si 2. NO 3. VER CODIGO DE ESPECIALIDADES \n :";
            cin>>opc2;
                switch(opc2){
                    case 1:
                    system("cls");
                    cout<<"INGRESE EL NOMBRE DE LA ESPECIALIDAD "<< endl;
                    cin>>nombreEspecialidad;
                    cout<<"INGRESE UNA LETRA IDENTIFICADORA PARA LA ESPECIALIDAD NUEVA "<< endl;
                    cin>>especialidades;
                    crearListaPrincipalDocs(Lista,especialidades);   
                    file<<fechaActual<<" ADDED ESPECIALIDAD: "<< especialidades<<"="<<nombreEspecialidad<< endl;
                    system("pause");                    
                    break;

                    case 2:
                    system("cls");
                    cout<<"VOLVIENDO AL MENU DE ADMIN PRINCIPAL"<< endl;
                    system("pause");
                    break;

                    case 3:
                    system("cls");
                    cout<<"By default: \n C=Cardiologia \n D=Dermatologia \n O=Oftalmologia \n N=Neurologia \n P=Pediatria \n U=Urologia \n R=Reumatologia \nUser Added: \n "<< especialidades <<"=" <<nombreEspecialidad<< endl;
                    file<<fechaActual<<" PRINTED DESCRIPTIONS "<< endl;
                    system("pause");
                    break;
                }   
            break;

            case 2:
            system("cls");
            cout<<"ANTES DE CONTINUAR, ASEGURESE QUE ESTA MODIFICANDO LA LISTA CORRECTAMENTE YA QUE PODRIA AFECTAR EL FUNCIONAMIENTO DEL SISTEMA"<< endl;
            cout<<"Ingrese el identificador de la especialidad que quiere borrar"<< endl;
            cin>>toDelete;
            borrarEspecialidad(Lista,toDelete);
            break;

            case 3:
            system("cls");
            cout<<"!!!!!"<< endl;
            cout<<"ANTES DE CONTINUAR, ASEGURESE QUE ESTA MODIFICANDO LA LISTA CORRECTAMENTE YA QUE PODRIA AFECTAR EL FUNCIONAMIENTO DEL SISTEMA"<< endl;
            cout<<"!!!!!"<< endl;
            cout<<" "<< endl;
            cout<<"Ingrese el identificador de la especialidad que quiere modificar"<< endl;
            cin>>fromUpdate;
            cout<<"Ingrese el nuevo"<<endl;
            cin>>toUpdate;
            actualizarEspecialidad(Lista,fromUpdate,toUpdate);
            break;

            case 4:
            system("cls");
            mostrar(Lista);
            system("pause");
            break;      
        }
    }while(opc!=5);
}

/***********************************************************************************************
 ***************FIN METODOS CREAR LISTA PRINCIPAL - ESPECIALIDADES MEDICAS - ADMIN***************
 ************************************************************************************************/


int main(){
    menuEspecialidades();
    char* fechaActual= get_time();
    file<<fechaActual<<"PROGRAM FINISHED"<<endl;
    file.close();
}
