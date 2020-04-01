#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>

//Variables globales
int VectorPosiciones[9], PosicionElegida=0, TipoPieza=1, TipoAdvertencia=0;
int PosicionTableroX=15, PosicionTableroY=1, posicionEnTableroX=0, posicionEnTableroY=0;

void main()
{
    int i;//variable auxiliar

    //cambia la "semilla" al momento de usar rand() por la de la hora (para simular aleatoriedad)
    srand (time(NULL));

    //Titulo
    textcolor(YELLOW);
    printf("TA-TE-TI");
    textcolor(LIGHTGRAY);

    //Inicializar Vector de posiciones en el tablero
    for(i=0;i<9;i++)
    {
        VectorPosiciones[i]=0;
    }

    //Creacion del TABLERO
    lineaHorizontal(PosicionTableroX,PosicionTableroY+1);
    lineaHorizontal(PosicionTableroX,PosicionTableroY+3);
    lineaVertical(PosicionTableroX+2,PosicionTableroY);
    lineaVertical(PosicionTableroX+5,PosicionTableroY);

    //INTERACCION DEL USUARIO y MAQUINA CON EL JUEGO
    do
    {
        //Jugador
        TipoPieza=1;
        InterfazUsuario(1,7);
        colocarPieza();

        if(Victoria()>0)
        {
            break;
        }

        if(TableroLleno()!=1)
        {
            break;
        }

        //Maquina
        TipoPieza=2;
        EleccionMaquina();
        colocarPieza();

        if(Victoria()>0)
        {
            break;
        }

    }while(TableroLleno()==1);

    MostrarGanador(1,10);
}
//CREACION DEL TABLERO---------------------------------------------------------
//Crea lineas verticales
void lineaVertical(int x, int y)
{
    int i;
    for(i=0;i<5;i++)
    {
        gotoxy(x,y+i);
        printf("%c", 124);
    }
};

//Crea lineas horizontales
void lineaHorizontal(int x, int y)
{
    gotoxy(x,y);
    int i;
    for(i=0;i<8;i++)
    {
        printf("%c", 45);
    }
};
//-----------------------------------------------------------------------------

//INTERACCION DEL USUARIO------------------------------------------------------
//Interfas que usara el usuario para elegir una posicion
void InterfazUsuario(int x, int y)
{
    textcolor(YELLOW);
    gotoxy(x,y);    printf("                             ");
    gotoxy(x,y);    printf("Ingrese posicion a jugar: _  ");
    textcolor(LIGHTGRAY);

    do
    {
        gotoxy(x+26,y); printf("   ");  gotoxy(x+26,y);
        scanf("%d", &PosicionElegida); PosicionElegida=PosicionElegida-1;
        ControlAlmacenamiento();
        advertencia();

    }while(TipoAdvertencia!=0);
};

//advertencia de error
void advertencia()
{
    textcolor(LIGHTRED);
    if(TipoAdvertencia==0)
    {
        printf("                          ");
    }
    if(TipoAdvertencia==1)
    {
        printf("ERROR: Espacio Ocupado    ");
    }
    if(TipoAdvertencia==2)
    {
        printf("ERROR: Espacio Inexistente");
    }
    textcolor(LIGHTGRAY);
};

//Coloca la pieza seleccionada en el tablero de juego
void colocarPieza()
{
    //88=X 48=0
    int pieza;
    switch(TipoPieza)
    {
        case 1: pieza=48;   break;
        case 2: pieza=88;   break;
    }
    NumAPosicion();
    posicionEnTableroX=(posicionEnTableroX*3)+PosicionTableroX;
    posicionEnTableroY=(posicionEnTableroY*2)+PosicionTableroY;

    gotoxy(posicionEnTableroX,posicionEnTableroY);
    printf("%c", pieza);
};

//cambia Numero elegido por una posicion usada en la visualizacion del Tablero
void NumAPosicion()
{
    posicionEnTableroX=PosicionElegida%3;
    posicionEnTableroY=PosicionElegida/3;
};

//Muestra el resultado de la partida una vez finalizada
void MostrarGanador(int x, int y)
{
    gotoxy(x,y);
    if(Victoria()==0)
    {
        printf("EMPATE\n");
    }
    if(Victoria()==1)
    {
        textcolor(LIGHTGREEN);
        printf("GANA EL JUGADOR\n");
    }
    if(Victoria()==2)
    {
        textcolor(LIGHTRED);
        printf("GANA LA MAQUINA\n");
    }
    textcolor(LIGHTGRAY);
};
//-----------------------------------------------------------------------------

//CONTROL PARA QUE LAS CONDICIONES DE JUEGO ESTEN SIEMPRE DADAS-----------------
//Control del almacenamiento en el vector (si algo se guarda o no)
void ControlAlmacenamiento()
{
    switch(verificadorPosicion(PosicionElegida))
    {
        case 0: VectorPosiciones[PosicionElegida]=TipoPieza;
                TipoAdvertencia=0; break;
        case 1: TipoAdvertencia=1; break;
        case 2: TipoAdvertencia=2; break;
    }
};

//verificador de posicion elegida (para saber si puede ocuparse)
int verificadorPosicion(int posicion)
{
    if(verificadorValor(PosicionElegida)==1)
    {
        if(VectorPosiciones[posicion]==0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 2;
    }
};

//verificador del valor entregado (para saber si es un numero valido)
int verificadorValor(int numero)
{
    if(numero<9 && numero>-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

//verifica todo el vector y sus posiciones ocupadas
int TableroLleno()
{
    int i=0, contador=0;
    for(i=0;i<9;i++)
    {
        if(VectorPosiciones[i]!=0)
        {
            contador+=1;
        }
    }

    if(contador==9)
    {
        return 0;
    }
    else
    {
        return 1;
    }
};

//INTERACCION DE LA MAQUINA----------------------------------------------------
void EleccionMaquina()
{
    do
    {
        PosicionElegida= rand() % 9;
        ControlAlmacenamiento();

    }while(TipoAdvertencia!=0);
};
//-----------------------------------------------------------------------------

//COMBINACIONES GANADORAS------------------------------------------------------
int Victoria()
{
    int i;
    for(i=0;i<3;i++)
    {
        if(VictoriaVertical(i)==1)
        {
            return TipoPieza;
        }
    }
    for(i=0;i<9;i=i+3)
    {
        if(VictoriaHorizontal(i)==1)
        {
            return TipoPieza;
        }
    }
    if(VictoriaDiagonal()==1)
    {
        return TipoPieza;
    }
    return 0;
};

int VictoriaVertical(int numero)
{
    if(VectorPosiciones[numero]==VectorPosiciones[numero+3] && VectorPosiciones[numero+3]==VectorPosiciones[numero+6] && VectorPosiciones[numero]!=0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

int VictoriaHorizontal(int numero)
{
    if(VectorPosiciones[numero]==VectorPosiciones[numero+1] && VectorPosiciones[numero+1]==VectorPosiciones[numero+2] && VectorPosiciones[numero]!=0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

int VictoriaDiagonal()
{
    if(VectorPosiciones[0]==VectorPosiciones[4] && VectorPosiciones[4]==VectorPosiciones[8] && VectorPosiciones[0]!=0)
    {
        return 1;
    }
    if(VectorPosiciones[2]==VectorPosiciones[4] && VectorPosiciones[4]==VectorPosiciones[6] && VectorPosiciones[2]!=0)
    {
        return 1;
    }
    return 0;
};
