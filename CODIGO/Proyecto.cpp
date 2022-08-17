#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cctype>
#include <windows.h>
#include <sstream>
#include <vector>

//Se define que se va a utilizar el namespace "std"
using namespace std;

//HELPERS:

//Se declara el archivo que va a servir para loguear la info
ofstream file;

//METODOS DE PARA LOGUEAR INFO

//Este metodo retorna un puntero char el cual contiene la fecha del momento para poder hacer logging and auditing
char* get_time() {
    //Tiempo actual de la computadora que ejecuta el programa
   time_t now = time(0);
   //Convierte ese valor a un puntero *char
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

/*****************************************
***************ESTRUCTURAS:***************
*****************************************/

//Se declara la estructura para la secondaria de doctores
struct nodoDoctores{
    string nombreDoc;
    char especialidad;
    int codigo;
    nodoDoctores *sig;
};

//Se declara la estructura para la lista principal de doctores
struct nodoEspecia{
    char especialidad;
    nodoEspecia *sig;
    nodoDoctores *doc;
};
//Se declara la estructura para lista de usuarios
struct nodoUsers{
    string nombre;
    int codigo;
    char tipo; // “E” = estándar o “A” =administrador
    string user;
    string contra;
    bool activo;
    nodoUsers *sig;
};
//Se declara la estructura para los pacientes
struct nodoPacientes{
    string nombre;
    int cedula;
    int celular; 
    string sintomas;
    string fechaIngreso;
    int provincia;
    nodoPacientes *sig;
};
//Estructura principal de pacientes
struct nodoProvincia{
    int provincia;
    nodoProvincia *sig;
    nodoPacientes *paciente;
};
//Se crea un typo de estructura tipo nodo para poder usarla en el código
typedef struct nodoEspecia *lista;
typedef struct nodoUsers *listaUsers;
typedef struct nodoDoctores *listaDocs;
typedef struct nodoProvincia *listaProvincias;
typedef struct nodoPacientes *listaPacientes;


/****************************************************
***************METODOS PARA EL LOGIN*****************
*****************************************************/

//Metodo que retorna un booleano que verifica si un usuario se puede loguear o no
bool login(listaUsers &cab, string user, string password){
    //Se crea un aux local para recorrer la lista y se iguala a la lista que recibe como parámetro
    listaUsers aux=cab;
    //Se establece la variable bool que va a determinar si el login es posible
    bool validation=false;
    //Variable para determinar porqué falla el login
    int log=0;
    //Logging
    char* fechaActual= get_time();
    //While que recorre la lista
    while(aux!=NULL){
        //Si no entra al if, significa que el user no existe
        log=1;
        //Verifica si el usuario existe en la lista
        if(aux->user==user){
            //Si no entra al if, significa que la contraseñia está mala
            log=2;
            //Verifica si la contraseña hace match al de la lista
            if(aux->contra==password){
                //Si no entra al if, significa que el user está desactivado
                log=3;
                //Verifica si el usuario está activo
                if(aux->activo==true){
                    log=4;
                    //Solo si se validan esas tres condiciones, retorna un true
                    validation=true;
                    cout<< "LOGGED AS " << aux->nombre<< endl;
                    file<<fechaActual<<"AND LOGGED AS " << aux->nombre<< endl;
                }
            }
        }
        //Recorre la lista
        aux=aux->sig;
    }
    //En base la variable log, se puede determinar el error
    file<<fechaActual<<"CHECKED CREDENTIALS and: " ;
    switch(log){
        case 1:
        file<<fechaActual<<"INVALID USER: " << user << endl;
        break;
        
        case 2:
        file<<fechaActual<<"INVALID PASSWORD: "<< password << endl;
        break;

        case 3:
        file<<fechaActual<<"USER IS DISABLED: " << user<< endl;
        break;

        case 4:
        file<<fechaActual<<user<<" IS ABLE TO LOGIN" << endl;
        break;
    }    

    return validation;
}

//Metodo que retorna un booleano que verifica si un usuario es admin o no
bool checkIfAdmin(listaUsers &cab, string user){
    //“E” = estándar o “A” =administrador
    //Se crea un aux local para recorrer la lista y se iguala a la lista que recibe como parámetro
    listaUsers aux=cab;
    //Variable que se va a retorna para verificar si es admin
    bool admin=false;
    char* fechaActual= get_time();
    //Recorre la lista siempre y cuando sea diferente al usuario que recibe como parámetro
    while(aux->user!=user){
        aux=aux->sig;
    }
    //Si contiene una "A" significa que es admin por lo que la variable bool es true
    if(aux->tipo=='A'){
        admin=true;
    }
    file<<fechaActual<<"CHECKED IF " << user << " IS ADMIN AND IT IS: "<< admin<<endl;
    return admin;
}

//METODOS DE LA LISTA DE USUARIOS LOGIN

//Metodo para crear el nodo del user que se utiliza para loguearse al sistema
nodoUsers *crearNodoUser(listaUsers &cab, string nombre, int codigo, char tipo, string user, string contra, bool activo){
    
    char* fechaActual= get_time();
    nodoUsers *nuevo_nodo= new (struct nodoUsers);
    nuevo_nodo->nombre=nombre;
    nuevo_nodo->codigo=codigo;
    nuevo_nodo->tipo=tipo;
    nuevo_nodo->user=user;
    nuevo_nodo->contra=contra;
    nuevo_nodo->activo=activo;
    nuevo_nodo->sig=NULL;
    return nuevo_nodo;
    file<<fechaActual<<"NODO USER CREADO" << endl;
}
//Se crea una lista simple
void crearListaUserLogging(listaUsers &cab, string nombre, int codigo, char tipo, string user, string contra, bool activo){
    nodoUsers *nuevo_nodo= crearNodoUser(cab,  nombre,  codigo,  tipo,  user,  contra,activo);
    char* fechaActual= get_time();
    if(cab==NULL){
        cab=nuevo_nodo;
    }
    else{
        nuevo_nodo->sig=cab;
        cab=nuevo_nodo;
        file<<fechaActual<<"CREATED USER: "<< user<<endl;
    }
}
//Método para borrar un usuario de la lista para login
void borrarUserLogin(listaUsers &cab, string userToDelete){

    //Se crean dos nodos para aux para poder unir la lista resultante y encontrar el nodo a eliminar
    nodoUsers *aux; //Nodo a eliminar
    nodoUsers *aux2; //Nodo que sirva para unir la lista
    char* fechaActual= get_time(); //logging
    
    //Se valida la lista que no sea nula
    if(cab != NULL){    
    aux2=NULL;
    //Se iguala el aux a borrar con la lista que se recibe como parametro
    aux=cab;
    }

    //Se recorre la lista siempre y cuando no sea NULL ni el identificador único a eliminar
    while((aux!=NULL) && (aux->user!=userToDelete)){
            //Se coloca el aux2 en la posición actual del aux
            aux2=aux;
            //Y se mueve aux, indirectamente aux2 es el anterior de aux
            aux=aux->sig;
    }
    //logging
    file<<fechaActual<<"DELETED USER: "<< aux->user<<endl;
    cout<<"DELETED USER: "<< aux->user<<endl;
    system("pause");
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
//Método para crear los usuarios por defecto para loguearse
void crearAdminAndUserDefault(listaUsers &cab){
    /*Admin: Joseph Granados, 1, A, totto, Testing123!, true -  Sebastian Cheng, 2, A, scheng, Testing123!, true - Dummy Admin, 3, A, dummy, Testing123!, false
      Users: Joseph Granados, 4, E, tottoU, Testing123!, true -  Sebastian Cheng, 5, E, schengg, Testing123!, true - Dummy Admin, 6, E, dummyU, Testing123!, false*/
    char* fechaActual= get_time();
    file<<fechaActual<<" ADDED DEFAULT ADMIN/STANDARD USERS"<< endl;
    crearListaUserLogging(cab, "Joseph Granados", 1, 'A', "totto", "Testing123!", true);
    crearListaUserLogging(cab, "Sebastian Cheng", 2, 'A', "scheng", "Testing123!", true);
    crearListaUserLogging(cab, "Dummy Admin", 3, 'A', "dummy", "Testing123!", false);
    crearListaUserLogging(cab, "Joseph Granados", 4, 'E', "tottoU", "Testing123!", true);
    crearListaUserLogging(cab, "Sebastian Cheng", 5, 'E', "schengg", "Testing123!", true);
    crearListaUserLogging(cab, "Dummy User", 6, 'E', "dummyU", "Testing123!", false);
}
//Método que muestra los usuarios de la lista de login
void mostrarUsers(listaUsers cab){
    //Aux local para recorrer la lista
    listaUsers auxRecorrer;
    //Se verifica si la lista está vacía
    if(cab==NULL){
        cout<<"LISTA VACÍA" << endl;
    }
    else{
        //Se iguala la lista local a la que recibe como parámetro
        auxRecorrer=cab;
        //Recorre la lista siempre y cuando no sea NULL y me imprime el contenido
        while(auxRecorrer!=NULL){
            cout<<"NOMBRE: " <<auxRecorrer->nombre << endl;
            cout<<"CODIGO: " <<auxRecorrer->codigo<< endl;
            cout<<"USUARIO: " << auxRecorrer->user<< endl;
            cout<<"ESTADO: " <<auxRecorrer->activo<<endl;
            cout<<" <----------> "<< endl;
            auxRecorrer=auxRecorrer->sig;
        }
    }
    char* fechaActual= get_time();
    file<<fechaActual<<" SHOWED LISTA &: "<< &cab<< endl;
}
//Método que retorna un bool y verifica si la contraseña cumple los requisitos
bool validationPassword (string password){
   	char* fechaActual= get_time();
    //Variable bools que dictamina si es valida la password o no
    bool validation=false,validationE=false,validationC=false;
    //Variable con el tamaño del string password y variable i para el while
    int lenght= password.length(),i=0,j=0;
    //Declara un array con el tamaño +1 ya que si no faltaría el último char
    char char_array[lenght+1];
    //Arreglos con los requisitos
    char nums[]={'1','2','3','4','5','6','7','8','9','0'};
    char especialChar[]={'!','#','$','%'};
    //Copia el string password al arreglo de char
    strcpy(char_array, password.c_str());
    //Verifica que la contraseña sea mayor a 8 chars
    if(lenght<8){
        validation=false;
        file<<fechaActual<<"PASSWORD IS SHORTER THAN 8" << endl;
    }
    else{
        //Recorre el array de chars con la contraseña
        while(i<lenght){
                //Verifica si tiene un num o char especial
        		if (char_array[i] == nums[0] || char_array[i] == nums[1] || char_array[i] == nums[2] || char_array[i] == nums[3] || char_array[i] == nums[4] || char_array[i] == nums[5] || char_array[i] == nums[6] || char_array[i] == nums[7] || char_array[i] == nums[8] || char_array[i] == nums[9] || char_array[i] == nums[10]
				|| char_array[i]== especialChar[0]|| char_array[i]== especialChar[1] || char_array[i]== especialChar[2] || char_array[i]== especialChar[3] || char_array[i]== especialChar[0]|| char_array[i]== especialChar[1] || char_array[i]== especialChar[2] || char_array[i]== especialChar[3]){
                        validationE=true;
			}
			
        i++;
        }
        //Verifica si hay un char con mayus en el array
        while (j<lenght){
            if(isupper(char_array[j])){
                validationC=true;
            }
            j++;
        }

    }
    //Cheque los booleanos y solo si ambos son true significa que la contraseña cumple los requisitos
    if(validationE==true && validationC==true){
        validation=true;
    }
    else{
        validation=false;
    }

    if(validationE==false){
        file<<fechaActual<<"PASSWORD DOES NOT HAVE NUMBERS OR SPECIAL CHARS" << endl;
    }
    else if(validationC==false){
        file<<fechaActual<<"PASSWORD DOES NOT HAVE CAPITAL LETTERS" << endl;
    }

    file<<fechaActual<<"CHECKED PASSWORD REQUIREMENTS AND PASSWORD: "<< validation << endl;
    return validation;
}
//Método que sirve para actualizar un nombre de un user para loguearse
void actualizarNombre(listaUsers &cab, string user, string nombreNuevo){
    char* fechaActual= get_time(); //logging
    //Lista local para recorrer la lista
    listaUsers aux;
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE A NAME: " << &cab<<endl;
    }
    else{
        //Se iguala la lista a la lista que recibe como parámetro
        aux=cab;
        //Recorre la lista siempre y cuando sea diferente a NULL y el usuario en esa posición sea diferente al usuario que recibe como parámetro
        while((aux!=NULL) && (aux->user!=user)){
         aux=aux->sig;
        }
        file<<fechaActual<<"NOMBRE UPDATED FROM: "<< aux->nombre << " TO " << nombreNuevo <<endl;
        //Se actualiza el nombre
        aux->nombre=nombreNuevo;

    }
}
//Método para actualizar la contra de un user para loguearse
void actualizarContra(listaUsers &cab, string user, string contraNuevo){
    char* fechaActual= get_time(); //logging
    //Lista local para recorrer la lista
    listaUsers aux;
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE A PASSWORD: " << &cab<<endl;
    }
    else{
        //Se iguala la lista a la lista que recibe como parámetro
        aux=cab;
        //Recorre la lista siempre y cuando sea diferente a NULL y el usuario en esa posición sea diferente al usuario que recibe como parámetro
        while((aux!=NULL) && (aux->user!=user)){
         aux=aux->sig;
        }
        file<<fechaActual<<"PASSWORD UPDATED FROM: "<< aux->contra << " TO " << contraNuevo <<endl;
        //Se actualiza la contraseña
        aux->contra=contraNuevo;

    }
}
//Método para actualizar el estado de un user para loguearse
void actualizarEstado(listaUsers &cab, string user, bool estado){
    char* fechaActual= get_time(); //logging
    //Lista local para recorrer la lista
    listaUsers aux;
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE A ESTADO: " << &cab<<endl;
    }
    else{
        //Se iguala la lista a la lista que recibe como parámetro
        aux=cab;
        //Recorre la lista siempre y cuando sea diferente a NULL y el usuario en esa posición sea diferente al usuario que recibe como parámetro
        while((aux!=NULL) && (aux->user!=user)){
         aux=aux->sig;
        }
        file<<fechaActual<<"PASSWORD UPDATED FROM: "<< aux->activo << " TO " << estado <<endl;
        aux->activo=estado;

    }
}

/************************************************************
***************METODOS PARA LA LISTA DE PACIENTES************
************************************************************/

nodoProvincia *crearNodoPacientes(listaProvincias &cab, int provincia){
    char* fechaActual= get_time();
    nodoProvincia *nuevo_nodo= new (struct nodoProvincia);
    nuevo_nodo->provincia=provincia;
    nuevo_nodo->sig=NULL;
    nuevo_nodo->paciente=NULL;
    return nuevo_nodo;
    file<<fechaActual<<"NODO PROVINCIA CREADO" << endl;
}
nodoPacientes *crearNodoPacientes(string nombre, int cedula, int celular, string sintomas, string fechaIngreso,int provincia){
    char* fechaActual= get_time();
    nodoPacientes *nuevo_nodo= new (struct nodoPacientes);
    nuevo_nodo->nombre=nombre;
    nuevo_nodo->cedula=cedula;
    nuevo_nodo->celular=celular;
    nuevo_nodo->sintomas=sintomas;
    nuevo_nodo->fechaIngreso=fechaIngreso;
    nuevo_nodo->provincia=provincia;
    nuevo_nodo->sig=NULL;
    return nuevo_nodo;
    file<<fechaActual<<"NODO PACIENTE CREADO" << endl;
}
void crearListaPrincipalPacientes(listaProvincias &cab, int provincia){
    nodoProvincia *nuevo_nodo= crearNodoPacientes(cab, provincia);
    if(cab==NULL){
        cab=nuevo_nodo;
    }
    else{
        nuevo_nodo->sig=cab;
        cab=nuevo_nodo;
    }
}
void agregarPaciente(listaProvincias &cab, string nombre, int cedula, int celular, string sintomas, string fechaIngreso, int provincia){
    listaProvincias aux;
    nodoPacientes *aux1;
    nodoPacientes *nuevo= crearNodoPacientes(nombre,cedula,celular,sintomas,fechaIngreso,provincia);
    char* fechaActual= get_time();
    if(cab==NULL){
        cout<<"LISTA VACIA"<< endl;
        file<<fechaActual<<"LISTA &: "<< cab  << " VACIA" << endl;
    } 
    else{
        aux=cab;
        while(aux!=NULL){
            if(aux->provincia==provincia){
                if(aux->paciente==NULL){
                    aux->paciente=nuevo;
                }
                else{
                    aux1=aux->paciente;
                    while(aux1->sig!=NULL){
                        aux1=aux1->sig;
                    }
                    aux1->sig=nuevo;
                }
                aux1=NULL;
            }
            aux=aux->sig;
        }
    }
    file<<fechaActual<<"ADDED PACIENTE: "<< cedula << endl;
}

void crearNodosProvinciasDefault(listaProvincias &cab){
    char* fechaActual= get_time();
    file<<fechaActual<<"CREATED PROVINCIAS"<<endl;
    crearListaPrincipalPacientes(cab,1);
    crearListaPrincipalPacientes(cab,2);
    crearListaPrincipalPacientes(cab,3);
    crearListaPrincipalPacientes(cab,4);
    crearListaPrincipalPacientes(cab,5);
    crearListaPrincipalPacientes(cab,6);
    crearListaPrincipalPacientes(cab,7);
}

void crearPacientesEjemplo(listaProvincias &cab){
    char* fechaActual= get_time();
    file<<fechaActual<<"CREATED PACIENTES EJEMPLO"<<endl;
    agregarPaciente(cab,"JOSEPH GRANADOS",118320862,605050505, "FIEBRE", "2020/09/15", 1);
    agregarPaciente(cab,"JOSEPH GRANADOS",1183208622,605050505, "FIEBRE", "2020/09/15", 1);
    agregarPaciente(cab,"ASSASAS GRANADOS",2183252,6085505, "FIEBRE", "2021/09/15", 2);
    agregarPaciente(cab,"FDFD GRANADOS",318320862,605050505, "FIEBRE", "2020/09/25", 3);
    agregarPaciente(cab,"DFFDFD GRANADOS",418320862,601150505, "FIEBRE", "2027/09/15", 4);
    agregarPaciente(cab,"FDFD GRANADOS",52323232,1111111, "FIEBRE", "2025/09/15", 5);
}

void mostrar(listaProvincias cab){
    system("cls"); 
    listaProvincias auxRecorrer;
    nodoPacientes *aux2;
    char* fechaActual= get_time();
    if(cab==NULL){
        cout<<"LISTA NULL" << endl;
    }
    else{
        auxRecorrer=cab;
        while(auxRecorrer!=NULL){
            cout<< "+------------------------+"<<endl;
            cout<<"Provincia: "<< auxRecorrer->provincia << "\n ";
            cout<< "+------------------------+"<<endl;
                if(auxRecorrer->paciente==NULL){
                    cout<< "************************"<<endl;
                    cout<<"NINGUN PACIENTE EN ESTA PROVINCIA"<<endl;
                    file<<fechaActual<<" NO HAY PACIENTES EN PROVINCIA: "<< auxRecorrer->provincia<< endl;
                }
                else{
                    aux2=auxRecorrer->paciente;
                    while(aux2!=NULL){
                        cout<< "************************"<<endl;
                        cout<<"NOMBRE: "<< aux2->nombre << endl;
                        cout<<"CEDULA: "<< aux2->cedula << endl;
                        cout<<"CELULAR: " << aux2->celular <<endl;
                        cout<<"SINTOMAS: " << aux2->sintomas <<endl;
                        cout<<"Fecha De Ingreso: " << aux2->fechaIngreso <<endl;
                        cout<< "************************"<<endl;
                        aux2=aux2->sig;
                    }
                }

            auxRecorrer=auxRecorrer->sig;
        }
    }
    file<<fechaActual<<" SHOWED LISTA &: "<< &cab<< endl;
}

vector <int> guessProvincia(int cedula)
{
    char* fechaActual= get_time();
    vector <int> resultArray;
    while (true)
    {
    resultArray.insert(resultArray.begin(), cedula%10);
    cedula /= 10;
    if(cedula == 0)
        return resultArray;
    }
    file<<fechaActual<<"FOUND THE PROVINCIA" <<resultArray[0] << endl;
}
    
int findProvincia(listaProvincias &cab, int cedulaa){
    listaProvincias aux=cab;
    nodoPacientes *aux2;
    int provincia;
    while(aux!=NULL){
        aux2=aux->paciente;
        while(aux2!=NULL){
            if(aux2->cedula==cedulaa){
                provincia=aux2->provincia;
            }
            aux2=aux2->sig;
        }
        aux=aux->sig;
    }
    char* fechaActual= get_time();
    file<<fechaActual<<"FOUND THE PROVINCIA OF: "<< cedulaa << " - "<< provincia <<endl;
    return provincia;
}

void borrarPaciente(listaProvincias &cab, int cedulaa){
    listaProvincias aux=cab;
    nodoPacientes *aux2;
    nodoPacientes *aux3;
    char* fechaActual= get_time();
    int provinciaa= findProvincia(aux,cedulaa);
    while(aux!=NULL){
        if(aux->provincia==provinciaa){
            aux2=aux->paciente;
            while(aux2!=NULL){
                if(aux2->cedula==cedulaa){
                    aux3->sig=aux2->sig;
                    aux2->sig=NULL;
                    file<<fechaActual<<"DELETED PACIENTE :"<< aux2->cedula <<endl;
                    cout<<"PACIENTE :" <<aux2->cedula <<" BORRADO" <<endl;
                    delete(aux2);
                }
                aux3=aux2;
                aux2=aux2->sig;
            }
        }
        aux=aux->sig;
    }
}

void actualizarNombrePaciente(listaProvincias &cab, int cedula, string nombreNuevo){
    char* fechaActual= get_time(); //logging
    //Lista local para recorrer la lista
    listaProvincias aux=cab;
    nodoPacientes *aux2;
    int provinciaa= findProvincia(aux,cedula);
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE A NAME: " << &cab<<endl;
    }
    else{
        //Se iguala la lista a la lista que recibe como parámetro
        aux=cab;
        //Recorre la lista siempre y cuando sea diferente a NULL 
        while(aux!=NULL){
            if(aux->provincia==provinciaa){
                aux2=aux->paciente;
                while(aux2!=NULL && aux2->cedula!=cedula){
                    aux2=aux2->sig;
                }
            }
         aux=aux->sig;
        }
        file<<fechaActual<<"NOMBRE UPDATED FROM: "<< aux2->nombre << " TO " << nombreNuevo <<endl;
        //Se actualiza el nombre
        aux2->nombre=nombreNuevo;
    }
}

void actualizarCelPaciente(listaProvincias &cab, int cedula, int celNuevo){
    char* fechaActual= get_time(); //logging
    //Lista local para recorrer la lista
    listaProvincias aux=cab;
    nodoPacientes *aux2;
    int provinciaa= findProvincia(aux,cedula);
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE A NAME: " << &cab<<endl;
    }
    else{
        //Se iguala la lista a la lista que recibe como parámetro
        aux=cab;
        //Recorre la lista siempre y cuando sea diferente a NULL 
        while(aux!=NULL){
            if(aux->provincia==provinciaa){
                aux2=aux->paciente;
                while(aux2!=NULL && aux2->cedula!=cedula){
                    aux2=aux2->sig;
                }
            }
         aux=aux->sig;
        }
        file<<fechaActual<<"CELULAR UPDATED FROM: "<< aux2->celular << " TO " << celNuevo <<endl;
        //Se actualiza el cel
        aux2->celular=celNuevo;
    }
}

void actualizarSintomasPaciente(listaProvincias &cab, int cedula, string sintomasNuevo){
    char* fechaActual= get_time(); //logging
    //Lista local para recorrer la lista
    listaProvincias aux=cab;
    nodoPacientes *aux2;
    int provinciaa= findProvincia(aux,cedula);
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE A NAME: " << &cab<<endl;
    }
    else{
        //Se iguala la lista a la lista que recibe como parámetro
        aux=cab;
        //Recorre la lista siempre y cuando sea diferente a NULL 
        while(aux!=NULL){
            if(aux->provincia==provinciaa){
                aux2=aux->paciente;
                while(aux2!=NULL && aux2->cedula!=cedula){
                    aux2=aux2->sig;
                }
            }
         aux=aux->sig;
        }
        file<<fechaActual<<"SINTOMAS UPDATED FROM: "<< aux2->sintomas << " TO " << sintomasNuevo <<endl;
        //Se actualiza los sintomas
        aux2->sintomas=sintomasNuevo;
    }
}

void actualizarFechaPaciente(listaProvincias &cab, int cedula, string fechaNuevo){
    char* fechaActual= get_time(); //logging
    //Lista local para recorrer la lista
    listaProvincias aux=cab;
    nodoPacientes *aux2;
    int provinciaa= findProvincia(aux,cedula);
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE A NAME: " << &cab<<endl;
    }
    else{
        //Se iguala la lista a la lista que recibe como parámetro
        aux=cab;
        //Recorre la lista siempre y cuando sea diferente a NULL 
        while(aux!=NULL){
            if(aux->provincia==provinciaa){
                aux2=aux->paciente;
                while(aux2!=NULL && aux2->cedula!=cedula){
                    aux2=aux2->sig;
                }
            }
         aux=aux->sig;
        }
        file<<fechaActual<<"Fecha UPDATED FROM: "<< aux2->fechaIngreso << " TO " << fechaNuevo <<endl;
        //Se actualiza el Fecha
        aux2->fechaIngreso=fechaNuevo;
    }
}

void actualizarProvinciaPaciente(listaProvincias &cab, int cedula, int provinciaNuevo){
    char* fechaActual= get_time(); //logging
    //Lista local para recorrer la lista
    listaProvincias aux=cab;
    nodoPacientes *aux2;
    int provinciaa= findProvincia(aux,cedula);
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE A NAME: " << &cab<<endl;
    }
    else{
        //Se iguala la lista a la lista que recibe como parámetro
        aux=cab;
        //Recorre la lista siempre y cuando sea diferente a NULL 
        while(aux!=NULL){
            if(aux->provincia==provinciaa){
                aux2=aux->paciente;
                while(aux2!=NULL && aux2->cedula!=cedula){
                    aux2=aux2->sig;
                }
            }
         aux=aux->sig;
        }
        file<<fechaActual<<"Provincia UPDATED FROM: "<< aux2->provincia << " TO " << provinciaNuevo <<endl;
        //Se actualiza la provincia
        aux2->provincia=provinciaNuevo;
    }
}

/*******************************************************************
***************METODO PARA LA LISTA DE ESPECIALIDADES***************
*******************************************************************/

//Este método crea un Nodo de Especialidades el cual recibe de parametro una cabeza de tipo lista 
nodoEspecia *crearNodoDocs(lista &cab, char especialidad){
    char* fechaActual= get_time();
    nodoEspecia *nuevo_nodo= new (struct nodoEspecia);
    nuevo_nodo->especialidad=especialidad;
    nuevo_nodo->sig=NULL;
    nuevo_nodo->doc=NULL;
    return nuevo_nodo;
    file<<fechaActual<<"NODO ESPECIALIDAD CREADO" << endl;
}
nodoDoctores *crearNodoDoctores(string nombre , char especialidad, int codigo){
    char* fechaActual= get_time();
    nodoDoctores *nuevo_nodo= new (struct nodoDoctores);
    nuevo_nodo->nombreDoc=nombre;
    nuevo_nodo->especialidad=especialidad;
    nuevo_nodo->codigo=codigo;
    nuevo_nodo->sig=NULL;
    return nuevo_nodo;
    file<<fechaActual<<"NODO DOCTOR CREADO" << endl;
}
void crearListaPrincipalDocs(lista &cab, char especialidad){
    nodoEspecia *nuevo_nodo= crearNodoDocs(cab, especialidad);
    if(cab==NULL){
        cab=nuevo_nodo;
    }
    else{
        nuevo_nodo->sig=cab;
        cab=nuevo_nodo;
    }

}
void agregarDocs(lista &cab, string nombre , char especialidad, int codigo){
    lista aux;
    nodoDoctores *aux1;
    nodoDoctores *nuevo= crearNodoDoctores(nombre,especialidad,codigo);
    char* fechaActual= get_time();
    if(cab==NULL){
        cout<<"LISTA VACIA"<< endl;
        file<<fechaActual<<"LISTA &: "<< cab  << " VACIA" << endl;
    } 
    else{
        aux=cab;
        while(aux!=NULL){
            if(aux->especialidad==toupper(especialidad)){
                if(aux->doc==NULL){
                    aux->doc=nuevo;
                }
                else{
                    aux1=aux->doc;
                    while(aux1->sig!=NULL){
                        aux1=aux1->sig;
                    }
                    aux1->sig=nuevo;
                }
                aux1=NULL;
            }
            aux=aux->sig;
        }
    }
    file<<fechaActual<<"ADDED DOC: "<< codigo << endl;
}
void crearNodosListaSecundariaDefault(lista &cab){
    /*Doctores de ejemplo:
        "Julian Jimenez", 'C' , 1
        "Pepe Gomez", 'D', 2
        "Julian Granados", 'C' , 5
        "Doctor Mentiras", 'N', 3
    */
    char* fechaActual= get_time();
    file<<fechaActual<<"ADDED TEST DOCS"<<endl;
    agregarDocs(cab,"Julian Jimenez", 'C' , 41);
    agregarDocs(cab,"Julian Granados", 'C' , 5);
    agregarDocs(cab,"Pepe Gomez", 'D', 2);
    agregarDocs(cab,"Doctor Mentiras", 'N', 3);
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
    nodoDoctores *aux2;
    int total=0;
    char* fechaActual= get_time();
    if(cab==NULL){
        cout<<"LISTA NULL" << endl;
    }
    else{
        auxRecorrer=cab;
        while(auxRecorrer!=NULL){
            
            cout<<"ESPECIALIDAD: "<< auxRecorrer->especialidad << "\n ";
                if(auxRecorrer->doc==NULL){
                    cout<<"NINGUN DOCTOR EN ESTA ESPECIALIDAD"<<endl;
                    cout<< "************************"<<endl;
                    file<<fechaActual<<" NO DOCTORES EN ESPECIALIDAD: "<< auxRecorrer->especialidad<< endl;
                }
                else{
                    aux2=auxRecorrer->doc;
                    while(aux2!=NULL){
                        cout<< "************************"<<endl;
                        cout<<"DOCTOR: "<< aux2->nombreDoc << endl;
                        cout<<"Especialidad Del Doctor: "<< aux2->especialidad << endl;
                        cout<<"CODIGO: " << aux2->codigo <<endl;
                        total=total+1;
                        cout<<"TOTAL DOCTORES: " << total << endl;
                        aux2=aux2->sig;
                    }
                }

            auxRecorrer=auxRecorrer->sig;
        }
    }
    file<<fechaActual<<" SHOWED LISTA &: "<< &cab<< endl;
}

int totalD(lista cab){
    lista auxRecorrer;
    nodoDoctores *aux2;
    int total=0;
    char* fechaActual= get_time();
    if(cab==NULL){
        cout<<"LISTA NULL" << endl;
    }
    else{
        auxRecorrer=cab;
        while(auxRecorrer!=NULL){

            cout<<"ESPECIALIDAD: "<< auxRecorrer->especialidad << "\n ";
                if(auxRecorrer->doc==NULL){
                    cout<<"VACIA"<<endl;
                }
                else{
                    aux2=auxRecorrer->doc;
                    while(aux2!=NULL){
                        total=total+1;
                        aux2=aux2->sig;
                    }
                }

            auxRecorrer=auxRecorrer->sig;
        }
    }
    return total;
}

//Método que borra una especialidad, recibe una lista y el identificador único a eliminar
void borrarEspecialidad(lista &cab, char identificador){

    //Se crean dos nodos para aux para poder unir la lista resultante y encontrar el nodo a eliminar
    nodoEspecia *aux; //Nodo a eliminar
    nodoEspecia *aux2; //Nodo que sirva para unir la lista
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
    cout<<"DELETED ESPECIALIDAD: "<< aux->especialidad<<endl;
    system("pause");
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
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE ESPECIALIDAD: " << &cab<<endl;
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
int generarCodigo(){
    char* fechaActual= get_time(); //logging
    int codigo= rand()% (0-1000);
    file<<fechaActual<<"Generated codigo: " << codigo <<endl;
    return codigo;
}

bool validarCodigo(int codigo, lista cab){
    char* fechaActual= get_time(); //logging
    lista aux;
    nodoDoctores *aux2;
    bool validation=true;
    aux=cab;
    while(aux!=NULL){
        aux2=aux->doc;
        while(aux2!=NULL){
            if(aux2->codigo==codigo){
                validation=false;
            }
            aux2=aux2->sig;
        }
        aux=aux->sig;
    }
    file<<fechaActual<<"Validated if codigo: " << codigo  << " is unique and it is : " << validation<<endl;
    return validation;
}
char buscarEspecialidad(lista &cab, int identificador){
    lista aux=cab;
    nodoDoctores *aux2;
    char especialidad;
    while(aux!=NULL){
        aux2=aux->doc;
        while(aux2!=NULL){
            if(aux2->codigo==identificador){
                especialidad=aux2->especialidad;
            }
            aux2=aux2->sig;
        }
        aux=aux->sig;
    }
    char* fechaActual= get_time();
    file<<fechaActual<<"FOUND THE ESPECIALIDAD OF: "<< identificador << " - "<< especialidad <<endl;
    return especialidad;
}

bool canIDelete(lista &cab,char especialidad){
    lista aux=cab;
    nodoDoctores *aux2;
    bool validation=false;
    while(aux!=NULL){
        if(aux->especialidad==especialidad){
            if(aux->doc==NULL){
                validation=true;
            }
        }
        aux=aux->sig;
    }
    char* fechaActual= get_time();
    file<<fechaActual<<"VERIFIED IF "<< especialidad << " can be deleted and :" << validation<<endl;
    return validation;
}

void borrarDoctor(lista &cab, int identificador){
    lista aux=cab;
    nodoDoctores *aux2;
    nodoDoctores *aux3;
    char* fechaActual= get_time();
    char especialidad= buscarEspecialidad(aux, identificador);
    while(aux!=NULL){
        if(aux->especialidad==especialidad){
            aux2=aux->doc;
            while(aux2!=NULL){
                if(aux2->codigo==identificador){
                    aux3->sig=aux2->sig;
                    aux2->sig=NULL;
                    file<<fechaActual<<"DELETED DOCTOR :"<< aux2->codigo <<endl;
                    delete(aux2);
                }
                aux3=aux2;
                aux2=aux2->sig;
            }
        }
        aux=aux->sig;
    }
}

//TO_DO
void borrarTodosLosDoctores(){

}


//METODOS USADOS PARA PRESENTAR MENUS AL USER/ADMIN
void menuDoctores(lista listaEspecialidades){
    lista Lista=listaEspecialidades;
    int opc,codigo, toDelete;
    string nombre;
    bool unico;
    char especialidad;
    char* fechaActual= get_time();
    file<<fechaActual<<"ADMIN SELECTED MENU DOCTORES "<< endl;
    system("cls"); 
    cout<<"BIENVENIDO AL MENU DE ADMINISTRACION DE DOCTORES!"<< endl;
    do{
        system("cls"); 
        cout<<"Seleccione alguna opcion: \n 1. Agregar un nuevo doctor \n 2. Eliminar algun doctor \n 3. Mostrar Lista \n 4. Volver al menu anterior \n:";
        cin>>opc;
        switch(opc){
            case 1:
            file<<fechaActual<<"ADMIN SELECTED AGREGAR UN NUEVO DOCTOR "<< endl;
            system("cls"); 
            cout<< "INGRESE EL NOMBRE: "<< endl;
            cin>>nombre;
            cout<< "INGRESE LA ESPECIALIDAD: "<< endl;
            cin>> especialidad;
            codigo=generarCodigo();
            unico=validarCodigo(codigo, Lista);
            if(unico){
                cout<<"El codigo creado para el doctor : "<< nombre << " es " << codigo << endl;
                agregarDocs(Lista, nombre,especialidad,codigo);
                system("pause");
            }
            else{
                while(!unico){
                    codigo=generarCodigo();
                    unico=validarCodigo(codigo, Lista);
                }
                cout<<"El codigo creado para el doctor : "<< nombre << " es " << codigo << endl;
                agregarDocs(Lista, nombre,especialidad,codigo);
                system("pause");
            }
            cout<<" DOCTOR AGREGADO" <<endl;
            system("pause");
            break;

            case 2:
                system("cls");
                file<<fechaActual<<"ADMIN SELECTED ELIMINAR A DOCTOR "<< endl;
                cout<<"Ingrese el codigo del doctor que desea borrar: " << endl;
                cin>>toDelete;
                borrarDoctor(Lista,toDelete);
                system("pause");
            break;

            case 3:
                system("cls");
                file<<fechaActual<<"ADMIN SELECTED MOSTRAR LISTA"<< endl;
                mostrar(Lista);
                system("pause");
            break;
        }

    }while(opc!=4);
}
void menuEspecialidades (lista &Listaa){
    lista Lista=Listaa;
    //Variables usada en el menu
    int opc,opc2,opc3,i=0,total;
    char especialidades,toDelete,fromUpdate,toUpdate;
    string nombreEspecialidad;
    bool check;
    char* fechaActual= get_time();
    file<<fechaActual<<"ADMIN SELECTED MENUESPECIALIDADES"<<endl;
    do{       
        system("cls"); 
        cout<<"Bienvenido Admin al menu de especialidades medicas! Elija alguna opcion: "<< endl;
        cout<<" 1. Agregar Especialidades \n 2. Borrar Alguna Especialidad \n 3. Actualizar el nombre de alguna especialidad \n 4. Mostrar Lista Actual \n 5. Administrar Doctores \n 6. Salir\n:";
        cin>>opc;
        switch(opc){
            case 1:
                system("cls");
                file<<fechaActual<<"ADMIN SELECTED AGREGAR ESPECIALIDAD "<< endl;
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
                        //TO_DO
                        cout<<"By default: \n C=Cardiologia \n D=Dermatologia \n O=Oftalmologia \n N=Neurologia \n P=Pediatria \n U=Urologia \n R=Reumatologia \nUser Added: \n "<< especialidades<<"="<<nombreEspecialidad<<endl;
                        file<<fechaActual<<" PRINTED DESCRIPTIONS "<< endl;
                        system("pause");
                        break;
                    }   
            break;

            case 2:
                system("cls");
                file<<fechaActual<<"ADMIN SELECTED BORRAR ALGUNA ESPECIALIDAD "<< endl;
                cout<<"ANTES DE CONTINUAR, ASEGURESE QUE ESTA MODIFICANDO LA LISTA CORRECTAMENTE YA QUE PODRIA AFECTAR EL FUNCIONAMIENTO DEL SISTEMA"<< endl;
                cout<<"Ingrese el identificador de la especialidad que quiere borrar"<< endl;
                cin>>toDelete;
                check=canIDelete(Lista,toDelete);
                if(check){
                    file<<fechaActual<<" Checked if "<< toDelete << " can be deleted and confirmed."<< endl;
                    borrarEspecialidad(Lista,toDelete);
                    system("pause");
                }
                else{
                    file<<fechaActual<<" Checked if "<< toDelete << " can be deleted and rejected."<< endl;
                    cout<<"La especialidad no puede ser borrada porque hay doctores en la misma"<<endl;
                    system("pause");
                }
            break;

            case 3:
                system("cls");
                file<<fechaActual<<"ADMIN SELECTED ACTUALIZAR ESPECIALIDAD "<< endl;
                cout<<"!!!!!"<< endl;
                cout<<"ANTES DE CONTINUAR, ASEGURESE QUE ESTA MODIFICANDO LA LISTA CORRECTAMENTE YA QUE PODRIA AFECTAR EL FUNCIONAMIENTO DEL SISTEMA"<< endl;
                cout<<"!!!!!"<< endl;
                cout<<" "<< endl;
                cout<<"Ingrese el identificador de la especialidad que quiere modificar"<< endl;
                cin>>fromUpdate;
                cout<<"Ingrese el nuevo"<<endl;
                cin>>toUpdate;
                actualizarEspecialidad(Lista,fromUpdate,toUpdate);
                system("pause");
            break;

            case 4:
                system("cls");
                file<<fechaActual<<"ADMIN SELECTED MOSTRAR LISTA "<< endl;
                mostrar(Lista);
                system("pause");
            break;      

            case 5:
                system("cls");
                file<<fechaActual<<"ADMIN SELECTED MENU DOCTORES "<< endl;
                menuDoctores(Lista);
                system("pause");
            break;
        }
    }while(opc!=6);
}
void menuUsers(listaUsers &listaU){
    listaUsers Lista=listaU;
    //Variables usada en el menu
    char* fechaActual= get_time();
    int opc,opc2,codigo,opc3,opc4;
    string nombre,user,contra,userT,passwordT,toDelete,toUpdate,newName;
    char tipo; 
    bool activo,confirmationLogin,passwordValidation,newState;
    file<<fechaActual<<"ADMIN SELECTED MENU USERS"<<endl;
    cout<<"BIENVENIDO AL MENU DE USER DE LOGIN"<<endl;
    do{
        system("cls"); 
        cout<<"Elija alguna opcion: "<< endl;
        cout<<" 1. Agregar Users \n 2. Borrar Algun User \n 3. Actualizar algun user <CHECK> \n 4. Mostrar Lista Actual De Users \n :";
        cin>>opc;
        switch(opc){
            case 1:
                file<<fechaActual<<"ADMIN SELECTED MENU DOCTORES "<< endl;
                system("cls");
                cout<<"HEMOS AGREGADO LOS USUARIOS POR DEFECTO DEL HOSPITAL, DESEA AGREGAR ALGUNO MAS? \n 1. Si 2. NO \n";
                cin>>opc2;
                switch(opc2){
                        case 1:
                                cout<<"Ingrese el nombre: "<< endl;
                                cin>> nombre;
                                cout<<"Ingrese el user: " << endl;
                                cin>> user;
                                cout<<"Ingrese el codigo identificador: " << endl;
                                cin>> codigo;
                                cout<< "Ingrese el tipo de user ('E' = estandar o 'A' =administrador)"<<endl;
                                cin>> tipo;
                                cout<<"Ingrese el password" << endl;
                                cin>>contra;
                                passwordValidation=validationPassword(contra);
                                if(passwordValidation){
                                    cout<<"LA CONTRASENIA CUMPLE REQUISITOS"<< endl;
                                    system("pause");
                                }
                                else{
                                    cout<<"LA CONTRASENIA NO CUMPLE REQUISITOS, VOLVIENDO AL MENU PRINCIPAL"<< endl;
                                    system("pause");
                                    break;
                                }
                                cout<<"Ingrese el estado: 1. Activo 2. Inactivo" << endl;
                                cin>>activo;

                                crearListaUserLogging(Lista,  nombre,  codigo,  tipo,  user,  contra,activo);
                                cout<<"DESEA PROBAR SI LAS CREDENCIALES DEL USUARIO NUEVO SIRVEN? 1. Si 2. No \n" << endl;
                                cin>> opc3;
                                if(opc3==1){
                                    cout<< "USER: ";
                                    cin>>userT;
                                    cout<<"PASSWORD: ";
                                    cin>>passwordT;
                                    confirmationLogin=login(Lista,userT, passwordT);
                                        if(confirmationLogin){
                                            cout<<"El user funciona para loguearse"<<endl;
                                            file<<fechaActual<<"TESTED LOGIN FOR NEW USER: "<< user<<endl;
                                            system("pause");
                                        }
                                        else{
                                            cout<<"LAS CREDENCIALES FALLAN, REVISE EL USUARIO"<< endl;
                                            file<<fechaActual<<"TESTED LOGIN FOR NEW USER: "<< user << "AND FAILED"<<endl;
                                            system("pause");
                                        }
                                }
                            break;
                        case 2:
                                system("cls");
                                cout<<"VOLVIENDO AL MENU DE ADMIN PRINCIPAL"<< endl;
                                system("pause");
                                break;
                    }
            break;
            case 2:
                system("cls");
                cout<<"ANTES DE CONTINUAR, ASEGURESE QUE ESTA MODIFICANDO LA LISTA CORRECTAMENTE YA QUE PODRIA AFECTAR EL FUNCIONAMIENTO DEL SISTEMA"<< endl;
                cout<<"Ingrese el usuario que quiere borrar"<< endl;
                cin>>toDelete;
                borrarUserLogin(Lista,toDelete);
            break;
            
            case 3:
                system("cls");
                cout<<"ANTES DE CONTINUAR, ASEGURESE QUE ESTA MODIFICANDO LA LISTA CORRECTAMENTE YA QUE PODRIA AFECTAR EL FUNCIONAMIENTO DEL SISTEMA"<< endl;
                cout<<"Ingrese el user al que quiere realizarle una actualizacion\n:";
                cin>>toUpdate;
                system("cls");
                cout<<"Que desea actualizar? \n 1. Nombre \n 2. Password \n 3. Estado (True o False)\n 4. Salir\n:";
                cin>>opc4;
                switch(opc4){
                    case 1:
                        system("cls");
                        cout<<"Ingrese Nombre Nuevo"<< endl;
                        cin>>newName;
                        actualizarNombre(Lista,toUpdate,newName);
                    break;
                    case 2:
                        system("cls");
                        cout<<"Ingrese Contrasenia Nueva"<< endl;
                        cin>>newName;
                        actualizarContra(Lista,toUpdate,newName);
                    break;
                    case 3:
                        system("cls");
                        cout<<"Ingrese el nuevo estado"<< endl;
                        actualizarEstado(Lista,toUpdate,newState);
                    break;
                }
            break;
            case 4:
                system("cls"); 
                mostrarUsers(Lista);
                system("pause");
            break;
        }

    }while(opc!=5);
}
void menuPacientes(listaProvincias &listaPA){
    system("cls"); 
    char* fechaActual= get_time();
    listaProvincias listaP=listaPA;
    int opc,cedula,celular,to_delete,to_update,opc2,nuevo_cel,nuevaProvincia;
    vector <int> provincia;
    string nombre,sintomas,fechaIngreso,nuevoNombre,nuevoSintomas,nuevoFecha;
    do{
    system("cls"); 
    cout<<"Bienvenido al menu de pacientes y citas! Favor elegir una opción \n 1. Agregar un paciente \n 2. Eliminar un paciente \n 3. Actualizar un paciente \n 4. Mostrar Pacientes \n 5. Administrar Citas \n 6. Salir \n:" ;
    cin>>opc;
    switch(opc){
        case 1:
        system("cls"); 
        cout<<"Ha seleccionado agregar un nuevo paciente, favor ingrese los datos del mismo. \n Nombre:" <<endl;
        cin>>nombre;
        cout<<"Cedula : \n";
        cin>>cedula;
        cout<<"Celular: \n";
        cin>>celular;
        cout<<"Sintomas: \n";
        cin>>sintomas;
        cout<<"Fecha de Ingreso: \n";
        cin>>fechaIngreso;
        provincia= guessProvincia(cedula);
        agregarPaciente(listaP,nombre,cedula,celular, sintomas, fechaIngreso, provincia[0]);
        cout<<"Agregado paciente: " << nombre<< endl;
        system("pause");
        break;

        case 2:
        system("cls"); 
        cout<<"Ha seleccionado eliminar un paciente, ingrese el numero de cedula del mismo \n";
        cin>>to_delete;
        borrarPaciente(listaP,to_delete);
        system("pause");
        break;

        case 3:
        system("cls"); 
        cout<<"Ha seleccionado actualizar los datos de un paciente, ingrese el numero de cedula del mismo \n";
        cin>>to_update;
        cout<<" Que desea modificar? \n 1. Nombre \n 2. Celular \n 3. Sintomas \n 4. Fecha Ingreso \n 5. Provincia \n :";
        cin>>opc2;
        switch(opc2){
            case 1:
            system("cls"); 
            cout<<"Nuevo nombre: "<< endl;
            cin>>nuevoNombre;
            actualizarNombrePaciente(listaP,to_update,nuevoNombre);
            break;

            case 2:
            system("cls"); 
            cout<<"Nuevo cel: "<< endl;
            cin>>nuevo_cel;
            actualizarCelPaciente(listaP,to_update,nuevo_cel);
            system("pause");
            break;

            case 3:
            system("cls"); 
            cout<<"Nuevos sintomas: "<< endl;
            cin>>nuevoSintomas;
            actualizarSintomasPaciente(listaP,to_update,nuevoSintomas);
            break;

            case 4:
            system("cls"); 
            cout<<"Nueva fecha: "<< endl;
            cin>>nuevoFecha;
            actualizarFechaPaciente(listaP,to_update,nuevoFecha);
            break;

            case 5:
            system("cls"); 
            cout<<"Nueva provincia: "<< endl;
            cin>>nuevaProvincia;
            actualizarProvinciaPaciente(listaP,to_update,nuevaProvincia);
            break;

        }

        system("pause");
        break;

        case 4:
        mostrar(listaP);
        system("pause");
        break;
    }
    }while(opc!=6);
}

void menuPrincipal(){
    logging();
    listaUsers listaU=NULL;
    listaProvincias listaP=NULL;
    lista Lista=NULL;
    char* fechaActual= get_time();
    crearAdminAndUserDefault(listaU);
    crearNodosProvinciasDefault(listaP);
    crearPacientesEjemplo(listaP);
    crearNodosListaPrincipalDefaultEspecialidades(Lista);
    crearNodosListaSecundariaDefault(Lista);
    string user, password;
    bool confirmationLogin,confirmationAdmin;
    system("cls"); 
    cout<<"BIENVENIDO!, FAVOR INGRESAR SU USER Y PASSWORD" << endl;
    cout<< "USER: ";
    cin>>user;
    //Comandos de Windows para esconder el input de la contraseña desde devc++
    /*HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));*/
    cout<<"PASSWORD: ";
    cin>>password;
    confirmationLogin=login(listaU,user, password);

    if(confirmationLogin){

        confirmationAdmin=checkIfAdmin(listaU,user);    

        if(confirmationAdmin){
            file<<fechaActual<<"LOGGED SUCCESSFULLY AS ADMIN" << endl;
            system("cls"); 
            int opc;
            cout<<"Bienvenido Admin!, favor elegir alguna opcion"<< endl;
            cout<<" 1. Administrar Usuarios de Login  2. Administrar Doctores Y Especialidades 3. Administrar Pacientes 4. Salir" << endl;
            cout<<"POR SEGURIDAD, UNA VEZ SELECCIONADA UNA INTERFAZ DE ADMINISTRACION TENDRA QUE LOGUEARSE OTRA VEZ PARA CAMBIAR LA MISMA"<< endl;
            cout<<": ";
            cin>>opc;
            switch(opc){
                case 1:
                menuUsers(listaU);
                break;
                case 2:
                menuEspecialidades(Lista);
                break;
                case 3:
                menuPacientes(listaP);
                break;
            }
        }
        else{
            file<<fechaActual<<"LOGGED SUCCESSFULLY AS USER" << endl;
            system("cls"); 
            int opc;
            cout<<"Bienvenido Usuario!, favor elegir alguna opcion"<< endl;
            cout<<" 1. Administrar Pacientes 2. Salir" << endl;
            cout<<"POR SEGURIDAD, UNA VEZ SELECCIONADA UNA INTERFAZ DE ADMINISTRACION TENDRA QUE LOGUEARSE OTRA VEZ PARA CAMBIAR LA MISMA"<< endl;
            cout<<": ";
            cin>>opc;
            switch(opc){
                case 1:
                menuPacientes(listaP);
                break;
                case 2:
                cout<<"SALIENDO";
                break;
            }
        }
    }
    else{
        cout<<"LOGIN FAILED, CHECK EITHER If YOUR USER/PASSWORD IS INCORRECT OR YOUR USER IS DISABLED"<<endl;
        file<<fechaActual<<"LOGIN FAILED" << endl;
    }
}

//MAIN
int main(){
    menuPrincipal();
    char* fechaActual= get_time();
    file<<fechaActual<<"PROGRAM FINISHED"<<endl;
    file.close();
}