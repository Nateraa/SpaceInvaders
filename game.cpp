#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

string getFileContents (ifstream&);

class SpaceInvaders{
	
	int dificultad = 0;
    int x = 1;
    int y = 13;
    bool game_running = true;
    int vidas = 3;
    int puntos = 0;
    int aleatorio = 0;
    int tiempo = 0;
	int ye[16];
    int xe[16];

    char mapa[16][70] = {
    "|---------------------------------------------------------------|",
    "|                                                               |",
    "|                                                               |",
    "|                                                               |",
    "|                                                               |",
    "|                                                               |",
    "|                                                               |",
    "|                                                               |",
    "|                                                               |",
    "|                                                               |",
    "|                                                               |",
    "|                                                               |",
    "|                                                               |",
    "|^                                                              |",
    "|                                                               |",
    "|---------------------------------------------------------------|",
    };

    public: 
    SpaceInvaders(){
	srand(time(NULL));
        //Orden de ejecución
        system("clear");
        figlet();
        instrucciones();
    	dificultad = Dificultad();
		for (int i = 0; i < dificultad; i++)
		{
			xe[i] = 1 + rand() % (63 - 1);
			ye[i] = - rand() % (dificultad*2 - 1);
			
		}
		

        system("clear");
        figlet();
        playground();


    }

    void figlet(){
        
    // --| Printeamos figlet |--
    ifstream Reader ("figlet.txt");         
    string Art = getFileContents (Reader);     
    cout << Art;        
    Reader.close ();             
    }

    void instrucciones(){
    cout << "|---------------------------------------------------------------|" << endl; 
    cout << "|                Bienvenidos a SpaceInvaders                    |" << endl; 
    cout << "|     En este videojuego eres una nave cuya finalidad no te     |" << endl; 
    cout << "|            tienes que chocar con los meteoritos               |" << endl; 
    cout << "|---------------------------------------------------------------|" << endl; 
    }

    int Dificultad(){
    
    // --| Dificultad del juego |--
    cout << endl << "--| Seleccione su dificultad del juego |--" << endl;
    cout << "[*] Dificultad 1 -> facil" << endl;
    cout << "[*] Dificultad 2 -> medio" << endl;
    cout << "[*] Dificultad 3 -> dificil" << endl << endl << endl;    
    cout << "[*] Su dificultad (1 - 3) -> "; cin >> dificultad;

    switch (dificultad)
    {
    case 1:
        cout << "[*] Has elegido la dificultad Facil" << endl;
		dificultad = 5;
        sleep(1);
    break;
    case 2:
        cout << "[*] Has elegido la dificultad media" << endl;
		dificultad = 10;
        sleep(1);
    break;
    case 3:
        cout << "[*] Has elegido la dificultad dificil" << endl;
		dificultad = 15;
        sleep(1);
    break;
    
    default: 
        cout << "[*] No has seleccionado una dificultad correcta" << endl;
        cout << "[*] Vuelva a ejecutarlo, saliendo ..." << endl;
        sleep(1);
        exit(EXIT_FAILURE);
    break;
    }
	return dificultad;
    }

    void marcadores(){
    
    cout << "|-----------------------------|";                 cout << "    |----------------------------|" << endl; 
    cout << "|       Vidas restantes:      |";                 cout << "    |       Puntos ganados:      |" << endl;
    cout << "               "  <<vidas<< "               ";    cout << "                  "  <<puntos<< "              "<< endl;
    cout << "|-----------------------------|";                 cout << "    |----------------------------|" << endl;

    //tests debug
    cout << endl;
    cout << "[*] INFO: " << " | X: " << x; cout << " | Y: " << y << " | Dificultad: " << dificultad << " | Tiempo: " << tiempo << " | Aleatorio: " << xe << endl << endl;

    }

    void playground(){
        
    while (game_running == true)
    {
    
    //Cabecera
    system("clear");
    figlet();
    marcadores();

    if (vidas == 0){
        game_running = false;
    }

    //Ponemos el mapa en pantalla
    for (int display = 0; display < 16; display++)
    { 
    cout << mapa[display] << endl;
    }

    // Asignación de puntos y vidas
	for (int i = 0; i < dificultad; i++)
	{
    if (ye[i] + 1 == 13)
    {
        if (x == xe[i])
        {
            vidas = vidas - 1;
			mapa[ye[i]][xe[i]] = ' ';
			ye[i] = 1;
			xe[i] = 1 + rand() % (63 - 1);
			mapa[ye[i]][xe[i]] = '*';
			
        } else if (x != xe[i]){
            puntos = puntos + 10;
        }
    }
	}

	tiempo = tiempo + 1; sleep(1);
    
        // Detectar movimientos
        if (kbhit()){
            switch (getch())
            {   
                case 65:{
                case 97:{   //(A/a) - izquierda
                    int x2 = x-1;
                    if (mapa[y][x2] == ' '){
                        mapa[y][x] = ' ';
                        x--;
                        mapa[y][x] = '^';
                    }}}
                break;
                break;

                case 68:{
                case 100:{  //(D/d) - derecha
                    int x2 = x+1;
                    if (mapa[y][x2] == ' '){
                        mapa[y][x] = ' ';
                        x++;
                        mapa[y][x] = '^';
                    }}}
                break;
                break;
            }
        }

    // Printeo de meteoritos dependiendo de la dificultad elegida
	for (int i = 0; i < dificultad; i++)
	{
    if (ye[i] < 0){
	ye[i]++;
	}else if (ye[i] == 0)
	{
	ye[i]++;
	mapa[ye[i]][xe[i]] = '*';
	}
	else if (mapa[ye[i] + 1][xe[i]] == ' '){
    mapa[ye[i]][xe[i]] = ' ';
    mapa[ye[i] + 1][xe[i]] = '*';
	ye[i] ++;
    } else if (mapa[ye[i] + 1][xe[i]] == '-'){
    mapa[ye[i]][xe[i]] = ' ';
	ye[i] = 1;
	xe[i] = 1 + rand() % (63 - 1);
	mapa[ye[i]][xe[i]] = '*';
    }
	}
	
	
    }
    finaldeljuego();
    }

    int finaldeljuego(){
        system("clear");

        cout << "|---------------------------------------------------------------|" << endl; 
        cout << "                  !!!!!!! FIN DEL JUEGO !!!!!!!                  " << endl; 
        cout << "|---------------------------------------------------------------|" << endl;

        cout << "|---------------------------------------------------------------|" << endl; 
        cout << "                   HAS TERMINADO CON "<< puntos << " PUNTOS " << "                 " << endl; 
        cout << "|---------------------------------------------------------------|" << endl;

        return EXIT_FAILURE;

    }

};

// Ejecutamos todo el código
int main(){SpaceInvaders execute;}
string getFileContents (ifstream& File)
{
    string Lines = "";    
    if (File){
	while (File.good ()){
	    string TempLine;            
	    getline (File , TempLine);       
	    TempLine += "\n";                  
	    Lines += TempLine;}
	return Lines;}
    else{
	return "No se ha podido printear el figlet";}
}

