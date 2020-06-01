#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Declaracion de Rutinas*/
void tableroInicial (char tablero[]);
int fichaVacia();
int fichaJugador();
int fichaMaquina();
void mostrarTablero (char tablero[]);
void mostrarTitulo();
void cargando();
void verInterfazJugador();
int eleccionJugador();
int eleccionMaquina(char tablero[]);
int verificarEleccion(int posicion, char tablero[]);
void colocarEleccion(int posicion, char tablero[], int letra);
int detectarEstadoPartida(char tablero[]);
int volverAJugar();

/*Declaracion subRutinas*/
int buscarFicha(char tablero[], int ficha);
int verificarEleccion0a8(int posicion);
int verificarEspacioDisponible(int posicion, char tablero[]);
int detectarLineaVertical(char tablero[], int posicion);
int detectarLineaHorizontal(char tablero[], int posicion);
int detectarLineaDiagonalIzq(char tablero[]);
int detectarLineaDiagonalDer(char tablero[]);
void mostrarVictoria(char tablero[], int i);

//Codigo Principal
void main()
{
	int juego=1, partida=1, posicion=0, ficha=0;
	char tablero[9];

	srand (time(NULL));
	while(juego==1)
	{
		partida=1;
		tableroInicial(tablero);
		while(partida==1)
		{
			do//Turno de la Maquina()
			{
				cargando();
				mostrarTablero(tablero);
				ficha=fichaMaquina();
				posicion=eleccionMaquina(tablero);
				system("cls");//borra pantalla
			}while(verificarEleccion(posicion, tablero)==1);
			colocarEleccion(posicion, tablero, ficha);
			partida=detectarEstadoPartida(tablero);
			if(partida!=1)
			{
				break;
			}
			do//Turno del Jugador
			{
				mostrarTitulo();
				mostrarTablero(tablero);
				ficha=fichaJugador();
				verInterfazJugador();
				posicion=eleccionJugador();
				system("cls");//borra pantalla
			}while(verificarEleccion(posicion, tablero)==1);
			colocarEleccion(posicion, tablero, ficha);
			partida=detectarEstadoPartida(tablero);
		}
		mostrarTitulo();
		mostrarTablero(tablero);
		printf("Fin del Juego\n");
		juego=volverAJugar();
		system("cls");
	}
};

/*Definicion de Rutinas*/
void tableroInicial (char tablero[])
{
	for(int i=0; i<9; i++)
	{
		tablero[i]=fichaVacia();
	}
};

int fichaVacia()
{
	return 32;//espacio vacio
};

int fichaJugador()
{
	return 88;//letra X
};

int fichaMaquina()
{
	return 79;//letra O
};

void mostrarTablero (char tablero[])
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

void cargando()
{
	printf("Cargando...\n");
};

void verInterfazJugador()
{
	printf("**Turno del Jugador**\n");
	printf("Posicion:");
};

int eleccionJugador()
{
	int posicion;
	scanf("%d", &posicion);
	posicion-=1;
	return posicion;
};

int eleccionMaquina(char tablero[])
{
	int posicion;
	//elige donde colocar segun sus fichas ya colocadas
	posicion=buscarFicha(tablero, fichaMaquina());
	if(posicion!=10)
	{
		if(posicion==0 || posicion==3 || posicion==6)//columna izq tateti
		{
			switch(detectarLineaHorizontal(tablero, posicion))
			{
				case 0:
					posicion=posicion+1;
					break;
				case 1:
					posicion=posicion+2;
					break;
			}
		}
		if(posicion==1 || posicion==2)//fila arriba (menos el primero)
		{
			switch(detectarLineaVertical(tablero, posicion))
			{
				case 0:
					posicion=posicion+3;
					break;
				case 1:
					posicion=posicion+6;
					break;
			}
		}
		//ve si el lugar que selecciono esta libre
		if(verificarEspacioDisponible(posicion, tablero)==1)
		{
			return posicion;
		}
	}
	//En caso de no poder determinar una posicion con estas reglas
	posicion=rand() % 9;//0-8
	return posicion;
};

int buscarFicha(char tablero[], int ficha)
{
	int i;
	for(int i=0; i<9; i++)
	{
		if(tablero[i]==ficha)
		{
			return i;
		}
	}
	return 10;
};

int verificarEleccion(int posicion, char tablero[])
{
	int verificacion=0;
	verificacion=verificarEleccion0a8(posicion);
	verificacion+=verificarEspacioDisponible(posicion, tablero);
	if(verificacion==2)//si ambas verificaciones dan positivo
	{
		return 0;
	}
	printf("ERROR:");
	return 1;
};

int verificarEleccion0a8(int posicion)
{
	if(posicion<0 || posicion>8)
	{
		return 0;
	}
	return 1;
};

int verificarEspacioDisponible(int posicion, char tablero[])
{
	if(tablero[posicion]==fichaVacia())
	{
		return 1;
	}
	return 0;
};

void colocarEleccion(int posicion, char tablero[], int ficha)
{
	tablero[posicion]=ficha;
};

int detectarEstadoPartida(char tablero[])
{
	int i;
	for(i=0;i<3;i++)
	{
		if(detectarLineaVertical(tablero, i)==2)
		{
			mostrarVictoria(tablero, i);
			return 2;
		}
	}
	for(i=0;i<9;i=i+3)
	{
		if(detectarLineaHorizontal(tablero, i)==2)
		{
			mostrarVictoria(tablero, i);
			return 2;
		}
	}
	if(detectarLineaDiagonalIzq(tablero)==2)
	{
		mostrarVictoria(tablero, 4);//medio
		return 2;
	}
	if(detectarLineaDiagonalDer(tablero)==2)
	{
		mostrarVictoria(tablero, 4);//medio
		return 2;
	}
	for(i=0;i<9;i++)
	{
		if(verificarEspacioDisponible(i, tablero)==1)
		{
			return 1;
		}
	}

	printf("Nadie Gana:");
	return 2;
};

int detectarLineaVertical(char tablero[], int posicion)
{
	if(tablero[posicion]!=fichaVacia())
	{
		if(tablero[posicion]==tablero[posicion+3])
		{
			if(tablero[posicion+3]==tablero[posicion+6])
			{
				return 2;
			}
			return 1;
		}
	}
	return 0;
};

int detectarLineaHorizontal(char tablero[], int posicion)
{
	if(tablero[posicion]!=fichaVacia())
	{
		if(tablero[posicion]==tablero[posicion+1])
		{
			if(tablero[posicion+1]==tablero[posicion+2])
			{
				return 2;
			}
			return 1;
		}
	}
	return 0;
};

int detectarLineaDiagonalIzq(char tablero[])
{
	if(tablero[4]!=fichaVacia())
	{
		if(tablero[0]==tablero[4] && tablero[4]==tablero[8])
		{
			return 2;
		}
	}
	return 0;
};

int detectarLineaDiagonalDer(char tablero[])
{
	if(tablero[4]!=fichaVacia())
	{
		if(tablero[2]==tablero[4] && tablero[4]==tablero[6])
		{
			return 2;
		}
	}
	return 0;
};

void mostrarVictoria(char tablero[], int i)
{
	printf("%c Gana:", tablero[i]);
};

int volverAJugar()
{
	int juego;
	printf("Volver a Jugar?(1=si, 0=no):");
	scanf("%d", &juego);
	return juego;
};