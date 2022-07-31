#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cctype>

//Se define que se va a utilizar el namespace "std"
using namespace std;

//HELPERS:

//Se declara el archivo que va a servir para loguear la info
ofstream file;

//METODOS DE PARA LOGUEAR INFO

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

//ESTRUCTURAS:

//Se declara la estructura para la lista principal de doctores
struct nodo{
    char especialidad;
    nodo *sig;
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
//Se crea un typo de estructura tipo nodo para poder usarla en el código
typedef struct nodo *lista;
typedef struct nodoUsers *listaUsers;

//METODOS PARA EL LOGIN

bool login(listaUsers &cab, string user, string password){
    listaUsers aux=cab;
    bool validation=false;
    int log=0;
    char* fechaActual= get_time();
    while(aux!=NULL){
        log=1;
        if(aux->user==user){
            log=2;
            if(aux->contra==password){
                log=3;
                if(aux->activo==true){
                    log=4;
                    validation=true;
                    cout<< "LOGGED AS " << aux->nombre<< endl;
                    file<<fechaActual<<"AND LOGGED AS " << aux->nombre<< endl;
                }
            }
        }
        aux=aux->sig;
    }
    file<<fechaActual<<"CHECKED CREDENTIALS" << endl;
    
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

bool checkIfAdmin(listaUsers &cab, string user){
    //“E” = estándar o “A” =administrador
    listaUsers aux=cab;
    bool admin=false;
    char* fechaActual= get_time();
    
    while(aux->user!=user){
        aux=aux->sig;
    }

    if(aux->tipo=='A'){
        admin=true;
    }

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
void mostrarUsers(listaUsers cab){
    listaUsers auxRecorrer;
    if(cab==NULL){
        cout<<"LISTA NULL" << endl;
    }
    else{
        auxRecorrer=cab;
        while(auxRecorrer!=NULL){
            cout<<" <----------> "<< endl;
            cout<< auxRecorrer->nombre << "\n" <<auxRecorrer->codigo<< "\n" << auxRecorrer->user<< "\n" <<auxRecorrer->activo<< "\n <---------->";
            auxRecorrer=auxRecorrer->sig;
        }
    }
    char* fechaActual= get_time();
    file<<fechaActual<<" SHOWED LISTA &: "<< &cab<< endl;
}

bool validationPassword (string password){
   	char* fechaActual= get_time();
    bool validation=false;
    int lenght= password.length(),i=0;

    char char_array[lenght+1];
    char nums[]={'1','2','3','4','5','6','7','8','9','0'};
    char especialChar[]={'!','#','$','%'};

    strcpy(char_array, password.c_str());
    
    if(lenght<8){
        validation=false;
        file<<fechaActual<<"PASSWORD IS SHORTER THAN 8" << endl;
    }
    else{
        while(i<lenght){
                file<<fechaActual<<"PASSWORD DOES NOT HAVE NUMBERS OR SPECIAL CHARS" << endl;
        		if (char_array[i] == nums[0] || char_array[i] == nums[1] || char_array[i] == nums[2] || char_array[i] == nums[3] || char_array[i] == nums[4] || char_array[i] == nums[5] || char_array[i] == nums[6] || char_array[i] == nums[7] || char_array[i] == nums[8] || char_array[i] == nums[9] || char_array[i] == nums[10]
				|| char_array[i]== especialChar[0]|| char_array[i]== especialChar[1] || char_array[i]== especialChar[2] || char_array[i]== especialChar[3] || char_array[i]== especialChar[0]|| char_array[i]== especialChar[1] || char_array[i]== especialChar[2] || char_array[i]== especialChar[3]){
							validation=true;
			}
			
        i++;
        }
    }
    file<<fechaActual<<"CHECKED PASSWORD REQUIREMENTS" << endl;
    return validation;
}

void actualizarNombre(listaUsers &cab, string user, string nombreNuevo){
    char* fechaActual= get_time(); //logging
    listaUsers aux;
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE A NAME: " << &cab<<endl;
    }
    else{
        aux=cab;
        while((aux!=NULL) && (aux->user!=user)){
         aux=aux->sig;
        }
        file<<fechaActual<<"NOMBRE UPDATED FROM: "<< aux->nombre << " TO " << nombreNuevo <<endl;
        aux->nombre=nombreNuevo;

    }
}

void actualizarContra(listaUsers &cab, string user, string contraNuevo){
    char* fechaActual= get_time(); //logging
    listaUsers aux;
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE A NAME: " << &cab<<endl;
    }
    else{
        aux=cab;
        while((aux!=NULL) && (aux->user!=user)){
         aux=aux->sig;
        }
        file<<fechaActual<<"PASSWORD UPDATED FROM: "<< aux->contra << " TO " << contraNuevo <<endl;
        aux->contra=contraNuevo;

    }
}

void actualizarEstado(listaUsers &cab, string user, bool estado){
    char* fechaActual= get_time(); //logging
    listaUsers aux;
    if(cab== NULL){
        cout<<"ERROR, LISTA VACIA" << endl;
        file<<fechaActual<<"ERROR, LISTA VACIA WHILE TRYING TO UPDATE A NAME: " << &cab<<endl;
    }
    else{
        aux=cab;
        while((aux!=NULL) && (aux->user!=user)){
         aux=aux->sig;
        }
        file<<fechaActual<<"PASSWORD UPDATED FROM: "<< aux->activo << " TO " << estado <<endl;
        aux->activo=estado;

    }
}


//METODO PARA LA LISTA DE ESPECIALIDADES

//Este método crea un Nodo de Especialidades el cual recibe de parametro una cabeza de tipo lista 
nodo *crearNodoDocs(lista &cab, char especialidad){
    char* fechaActual= get_time();
    nodo *nuevo_nodo= new (struct nodo);
    nuevo_nodo->especialidad=especialidad;
    nuevo_nodo->sig=NULL;
    return nuevo_nodo;
    file<<fechaActual<<"NODO ESPECIALIDAD CREADO" << endl;
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

//METODOS USADOS PARA PRESENTAR MENUS AL USER/ADMIN

void menuEspecialidades (){
    lista Lista=NULL;
    //Variables usada en el menu
    int opc,opc2;
    char especialidades,toDelete,fromUpdate,toUpdate;
    string nombreEspecialidad;
    char* fechaActual= get_time();
    file<<fechaActual<<"ADMIN SELECTED MENUESPECIALIDADES"<<endl;
    crearNodosListaPrincipalDefaultEspecialidades(Lista);
    do{       
        system("cls"); 
        cout<<"Bienvenido Admin al menu de especialidades medicas! Elija alguna opcion: "<< endl;
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


void menuUsers(listaUsers listaU){
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

void menuPacientes(){

}

void menuCitas(){

}

void menuPrincipal(){
    logging();
    listaUsers listaU=NULL;
    char* fechaActual= get_time();
    crearAdminAndUserDefault(listaU);
    string user, password;
    bool confirmationLogin,confirmationAdmin;
    cout<<"BIENVENIDO!, FAVOR INGRESAR SU USER Y PASSWORD" << endl;
    cout<< "USER: ";
    cin>>user;
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
            cout<<" 1. Administrar Usuarios de Login  2. Administrar Doctores  3. Administrar Pacientes 4. Salir" << endl;
            cout<<"POR SEGURIDAD, UNA VEZ SELECCIONADA UNA INTERFAZ DE ADMINISTRACION TENDRA QUE LOGUEARSE OTRA VEZ PARA CAMBIAR LA MISMA"<< endl;
            cout<<": ";
            cin>>opc;
            switch(opc){
                case 1:
                menuUsers(listaU);
                break;
                case 2:
                menuEspecialidades();
                break;
                case 3:
                menuPacientes();
                break;
            }
        }
        else{
            file<<fechaActual<<"LOGGED SUCCESSFULLY AS USER" << endl;
            system("cls"); 
            int opc;
            cout<<"Bienvenido Usuario!, favor elegir alguna opcion"<< endl;
            cout<<" 1. Administrar Pacientes  2. Administrar Citas  3. Salir" << endl;
            cout<<"POR SEGURIDAD, UNA VEZ SELECCIONADA UNA INTERFAZ DE ADMINISTRACION TENDRA QUE LOGUEARSE OTRA VEZ PARA CAMBIAR LA MISMA"<< endl;
            cout<<": ";
            cin>>opc;
            switch(opc){
                case 1:
                menuPacientes();
                break;
                case 2:
                menuCitas();
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
