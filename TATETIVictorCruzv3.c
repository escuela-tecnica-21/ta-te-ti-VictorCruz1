#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define vacio 32
#define fichaX 88
#define fichaO 79

/*Declaracion de Rutinas*/
void tableroInicial(char tablero[]);
void mostrarTablero(char tablero[]);
int TurnoJugador(char tablero[]);
int TurnoMaquina(char tablero[]);
void mostrarTitulo();
void mostrarGanador(int ganador);
void mostrarEmpate();
void mensajeFinal();
void verInterfazJugador();
int eleccionJugador();
int eleccionMaquina(char tablero[]);
int buscarFicha(char tablero[], int ficha);
int buscarFichaEnTira(char tablero[], int tira, int ficha);
int verificarficha(int posicion, char tablero[], int ficha);
int buscarTiraLibre(char tablero[], int ficha, int a, int b, int c, int cantFichas, int cantVacio);
void colocarEleccion(int posicion, char tablero[], int ficha);
int detectarEstadoJuego(char tablero[], int ficha);
int detectarVictoria(char tablero[], int ficha);
int detectarEmpate(char tablero[]);
int contador(char tablero[], int ficha, int a, int b, int c);

/*Victorias*/
int const tiras[][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

void main()
{
	int juego=1, posicion=0;//posicion de ficha
	char tablero[9];

	srand (time(NULL));//aleatoriedad
	tableroInicial(tablero);

	while(juego==1)
	{
		//Jugador
		posicion=TurnoJugador(tablero);
		colocarEleccion(posicion, tablero, fichaX);

		juego=detectarEstadoJuego(tablero, fichaX);

		//Maquina
		if(juego==1)
		{
			posicion=TurnoMaquina(tablero);
			colocarEleccion(posicion, tablero, fichaO);

			juego=detectarEstadoJuego(tablero, fichaO);
		}
	}
	if(juego!=0)
	{
		mostrarGanador(juego);
	}
	else
	{
		mostrarEmpate();
	}
	mostrarTablero(tablero);
	mensajeFinal();
};

/*Definicion de Rutinas*/

void tableroInicial(char tablero[])//pone tablero vacio
{
	for(int i=0; i<9; i++)
	{
		tablero[i]=vacio;
	}
};

int TurnoJugador(char tablero[])
{
	int posicion=0;
	do{
		mostrarTitulo();
		mostrarTablero(tablero);
		posicion=eleccionJugador();
		system("cls");//borra pantalla
	}while(verificarficha(posicion, tablero, vacio)==0);
	return posicion;
};

int TurnoMaquina(char tablero[])
{
	int posicion=0;
	do{
		mostrarTitulo();
		mostrarTablero(tablero);
		posicion=eleccionMaquina(tablero);
		system("cls");//borra pantalla
	}while(verificarficha(posicion, tablero, vacio)==0);
	return posicion;
};

void mostrarTablero(char tablero[])
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			printf("|%c", tablero[i*3+j]);
		}
		printf("|\n");
	}
};

void mostrarTitulo()
{
	printf("Ta-Te-Ti\n");
};

void mostrarGanador(int ganador)
{
	printf("**%c Gana**\n", ganador);
};

void mostrarEmpate()
{
	printf("**Empate**\n");
};

void mensajeFinal()
{
	int caracter=0;
	printf("Ingrese cualquier caracter para finalizar:");
	scanf("%d", &caracter);
};

int eleccionMaquina(char tablero[])//de la posicion para colocar la ficha
{
	int posicion=0, desicion=0;

	//Tiene un 50% de probabilidad de elegir al azar, asi evita ser invencible
	desicion=rand() % 9;//0-9
	if(desicion>4)
	{
		//decide la posicion de manera aleatoria
		posicion=rand() % 9;//0-8
		return posicion;
	}

	/*REGLAS de la Maquina*/
	//elige donde colocar sus fichas solo si ya coloco
	posicion=buscarFicha(tablero, fichaO);
	if(posicion!=10)//si ya tiene alguna ficha colocada
	{
		//Busca una posicion ganadora y si hay la concreta
		for(int i=0; i<8; i++)
		{
			if(buscarTiraLibre(tablero, fichaO, tiras[i][0], tiras[i][1], tiras[i][2], 2, 1)==1)
			{
				posicion=buscarFichaEnTira(tablero, i, vacio);
				return posicion;
			}
		}
		//Busca si puede bloquear victoria rival y lo hace
		for(int i=0; i<8; i++)
		{
			if(buscarTiraLibre(tablero, fichaX, tiras[i][0], tiras[i][1], tiras[i][2], 2, 1)==1)
			{
				posicion=buscarFichaEnTira(tablero, i, vacio);
				return posicion;
			}
		}//coloca ficha para crear una situacion ganadora (en caso de no ser bloqueada) para su siguiente turno
		for(int i=0; i<8; i++)
		{
			if(buscarTiraLibre(tablero, fichaO, tiras[i][0], tiras[i][1], tiras[i][2], 1, 2)==1)
			{
				posicion=buscarFichaEnTira(tablero, i, vacio);
				return posicion;
			}
		}
	}
	//En caso de no poder determinar una posicion con estas reglas, se decide por aleatoriedad
	posicion=rand() % 9;//0-8
	return posicion;
};

int buscarFicha(char tablero[], int ficha)//buscar determinada ficha en todo el tablero
{
	int i;
	for(int i=0; i<9; i++)
	{
		if(verificarficha(i, tablero, ficha)==ficha)
		{
			return i;
		}
	}
	return 10;
};

int buscarFichaEnTira(char tablero[], int tira, int ficha)//busca la ficha pero solo en una tira
{
	int posicion=0;
	for(int j=0; j<3; j++)
	{
		if(verificarficha(tiras[tira][j], tablero, ficha)==ficha)
		{
			posicion=tiras[tira][j];
			return posicion;
		}
	}
};

int verificarficha(int posicion, char tablero[], int ficha)//
{
	if(tablero[posicion]==ficha)
	{
		return ficha;
	}
	return 0;
};

//busca si la tira contiene la ficha especificada y vacio (cantidad a especificar) y no la ficha rival
int buscarTiraLibre(char tablero[], int ficha, int a, int b, int c, int cantFichas, int cantVacio)
{
	if((contador(tablero, ficha, a, b, c)==cantFichas) && (contador(tablero, vacio, a, b, c)==cantVacio))
	{
		return 1;
	}
	return 0;
};

int eleccionJugador()//de la posicion para colocar la ficha
{
	verInterfazJugador();
	int posicion;
	scanf("%d", &posicion);
	posicion-=1;
	return posicion;
};

void verInterfazJugador()
{
	printf("**Turno del Jugador**\n");
	printf("Posicion:");
};

void colocarEleccion(int posicion, char tablero[], int ficha)
{
	tablero[posicion]=ficha;
};

int detectarEstadoJuego(char tablero[], int ficha)//si hay Victoria, Empate o el juego aun continua
{
	if(detectarVictoria(tablero, ficha)>0)
	{
		return ficha;
	}
	if(detectarEmpate(tablero)==1)
	{
		return 0;
	}

	return 1;//la partida continua
};

int detectarVictoria(char tablero[], int ficha)//revisa todas las tiras ganadoras
{
	for(int i=0; i<8; i++)
	{
		if(contador(tablero, ficha, tiras[i][0], tiras[i][1], tiras[i][2])==3)//de repetirse 3 veces la ficha especificada es una victoria
		{
			return ficha;//se devuelve como valor a la ficha que gano
		}
	}
	return 0;
};

int detectarEmpate(char tablero[])//si no hay espacio para jugar por descarte es empate
{
	for(int i=0; i<9; i++)
	{
		if(verificarficha(i, tablero, vacio)==vacio)
		{
			return 0;
		}
	}
	return 1;
};

int contador(char tablero[], int ficha, int a, int b, int c)//suma 1 por cada vez que se repite la ficha en una tira
{
	int cuenta=0;

	if(tablero[a]==ficha)
	{
		cuenta++;
	}
	if(tablero[b]==ficha)
	{
		cuenta++;
	}
	if(tablero[c]==ficha)
	{
		cuenta++;
	}
	return cuenta;//y devuelve esa cantidad
};