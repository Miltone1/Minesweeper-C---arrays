#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

//variables globales
const int filas = 9;
const int columnas = 9;
bool explocion = false;
char matriz1[filas][columnas];
char bomba_escondida[filas][columnas];
int matriz_completa = 0;
int total_celdas = filas*columnas;
int contador_malas = 0;
int contador_buenas = 0;
string nombre;
//funciones
void instrucciones();
void mina(char mundo[][columnas], int cantidad_minas);
//void integrarmina();
void crearmatriz(char mundo[][columnas]);
void integrarmatriz(char mundo[][columnas]);
void movimiento();
char revelar_mina(int, int);
void marcador();
time_t now;
time_t cataclismo;

	


//cout<< ctime(&now);
//cout<< diff << endl;
//cout<< end << endl;


int main(){
	string linea;
	string puntaje;
	int opcion;
	//medidor de tiempo
	
	
	//time_t diff = difftime(now,cataclismo);
	//int menets= diff/60;
	//int secundos= diff%60;
	
	//para que se guarde
	
	int menets = 0;
	int secundos = 0;
	
	instrucciones();
	cout<<"Escribe tu nombre para la tabla de puntuacion: ";
	cin>>nombre;
	cout<<"Elije una opcion: \n";
	cout<<"1. Jugar buscaminas 2. Tablero de punteo\n";
	cin>>opcion;
	
	switch(opcion){
	case 1:{
		//int menets = 0;
		//int secundos = 0;
		
		now = time(nullptr); 
		srand(time(0));
		crearmatriz(matriz1);
		mina(bomba_escondida, 3);
	
		do{
			cout<<endl;
			integrarmatriz(matriz1);
			movimiento();
			matriz_completa = 0;
		}while(explocion!=true&& matriz_completa <total_celdas);
	
	
		cataclismo = time(nullptr); 
		
		
		time_t diff = difftime(cataclismo, now);
		menets = diff / 60;
		secundos = diff % 60;

		if(explocion==true){
			cout<<"Explotaste en mil pedacitos.\n";
			cout<<"Volviendote a armar...\n";
			cout<<"No encontramos tu nariz, lo siento. :(\n";
		}
		if(matriz_completa==total_celdas){
			cout<<"QUE!?\n USASTE HACKS O QUE!?\n";
			cout<<"A la otra no hagas trampa.\n";
			cout<<"Muy bien, creo, te estaremos vigilando...\n";
		}
		break;
	}
		
	case 2:
	{
		
		ifstream tablerodepunteo2("Historial de la partida.txt");
			if(tablerodepunteo2.is_open()){
				while(getline (tablerodepunteo2, linea)){
			 		puntaje=puntaje+linea+"\n";
			 }
			tablerodepunteo2.close();
			}
			if(puntaje == ""){
				cout<<"Nada guardado, aun.";
			}else{
				cout<<puntaje;
			}
			
		break;
	}
}
		ofstream tablerodepunteo("Historial de la partida.txt", ios::app);
			if(tablerodepunteo.is_open()){
			tablerodepunteo<<"Nombre         Movimientos    Minas        Tiempo"<<endl<<nombre<<"                "<<contador_buenas<<"            "<<contador_malas<<"        "<<menets<<":"<<secundos<<endl<<puntaje;
			tablerodepunteo.close();
			}
	
	cin.ignore();
	cout<<"\nPresiona enter para que pueda descansar..."<<endl;
	cin.ignore();
	
	
	return 0;
}


void instrucciones(){
	cout<<"#########################\n";
	cout<<"#Bienvenido a buscaminas#\n";
	cout<<"#########################\n"<<endl;
	
}
void crearmatriz(char mundo[filas][columnas]){
	cout<<"Expandiendo el campo y colocando las minas...";
	for(int i = 0; i< filas; i++){
		for(int j=0; j< columnas; j++){
			mundo[i][j] = '#';
			
		}
		cout<<endl;
	}
}
void integrarmatriz(char matriz1[filas][columnas]){
	cout<<"  ";
	for(int j = 0; j < columnas; j++){
		cout<< j+1 << " ";
	}
	cout<<endl;
	for(int i = 0; i < filas; i++){
		cout<<i+1<<" ";
		for(int j=0;j< columnas; j++ ){
			cout<<matriz1[i][j]<<" ";
		}
		cout<<endl;
	}
}
void movimiento(){
	

		
	int izq_dere=0,arri_abaj=0;
	
	
	cout<<"\nTe mueves con el primer numero a la derecha o izquierda y con el segundo arriba o abajo: \n";
	
	cin>>izq_dere;
	cin>>arri_abaj;
	
	cataclismo = time(nullptr);
	
	time_t diff = difftime(cataclismo,now);
	int menets= diff / 60;
	int secundos= diff % 60;
	cout<<"Tiempo transcurrido: \n"<<menets<<" minutos, "<<secundos<<" segundos.\n";
	if(izq_dere > 0){
		contador_buenas+=1;
	}
	izq_dere -= 1;
	arri_abaj -= 1;
	if(izq_dere>filas || izq_dere<0 ||arri_abaj>=columnas||arri_abaj<0 ){
		cout<<"Nononono, esa coordenada no existe.\n Intenta con numeros en el rango establecido.\n Gracias.\n"<<endl;
		
		return;
	}
	if(bomba_escondida[izq_dere][arri_abaj]== 'x'){
		explocion = true;
		contador_malas+=1;
	}
	else{
		matriz1[izq_dere][arri_abaj] = revelar_mina(izq_dere,arri_abaj);
	}
}
char revelar_mina(int izq_dere, int arri_abaj){
	int revelar_mina = 0;
	int contador_minas = 0;
	if (izq_dere + 1 < filas && bomba_escondida[izq_dere + 1][arri_abaj] == 'x') contador_minas++;
    if (izq_dere - 1 >= 0 && bomba_escondida[izq_dere - 1][arri_abaj] == 'x') contador_minas++;
    if (arri_abaj + 1 < columnas && bomba_escondida[izq_dere][arri_abaj + 1] == 'x') contador_minas++;
    if (arri_abaj - 1 >= 0 && bomba_escondida[izq_dere][arri_abaj - 1] == 'x') contador_minas++;
    
    if (izq_dere + 1 < filas && arri_abaj - 1 >= 0 && bomba_escondida[izq_dere + 1][arri_abaj - 1] == 'x') contador_minas++;
    if (izq_dere + 1 < filas && arri_abaj + 1 < columnas && bomba_escondida[izq_dere + 1][arri_abaj + 1] == 'x') contador_minas++;
    if (izq_dere - 1 >= 0 && arri_abaj + 1 < columnas && bomba_escondida[izq_dere - 1][arri_abaj + 1] == 'x') contador_minas++;
    if (izq_dere - 1 >= 0 && arri_abaj - 1 >= 0 && bomba_escondida[izq_dere - 1][arri_abaj - 1] == 'x') contador_minas++;
    return '0'+contador_minas;
}

void mina(char mundo[][columnas], int cantidad_minas)
{
    int nminas = 0;
	
    while (nminas < cantidad_minas)
    {
        int f = rand() % filas;
        int c = rand() % columnas;

        if (mundo[f][c] != 'x')
        {
            mundo[f][c] = 'x';
            nminas++;
        }
    }
}


