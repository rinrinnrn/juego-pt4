#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define FILAS 10
#define COLUMNAS 19
#define TROFEOS_GANAR 10

enum Estado {
    MENU,
    JUGANDO,
    INSTRUCCIONES,
    SALIR
};

char mapa[FILAS][COLUMNAS+1] = {
"###################",
"#                 #",
"#  #####          #",
"#      #          #",
"#      #   #####  #",
"#          #      #",
"#          #      #",
"#   #####  #      #",
"#                 #",
"###################"
};

int trofeoX, trofeoY;

void generarTrofeo() {

    int x,y;

    do {

        x = rand()%COLUMNAS;
        y = rand()%FILAS;

    } while(mapa[y][x]=='#');

    trofeoX = x;
    trofeoY = y;
}

void dibujarMapa(int px,int py){

    for(int y=0;y<FILAS;y++){

        for(int x=0;x<COLUMNAS;x++){

            if(x==px && y==py)
                printf("P");

            else if(x==trofeoX && y==trofeoY)
                printf("T");

            else
                printf("%c",mapa[y][x]);
        }

        printf("\n");
    }
}

void mostrarHUD(int x,int y,char tecla,int choques,int trofeos){

    printf("\nHUD\n");
    printf("Posicion X:%d Y:%d\n",x,y);
    printf("Ultima tecla: %c\n",tecla);
    printf("Choques: %d\n",choques);
    printf("Trofeos: %d / %d\n",trofeos,TROFEOS_GANAR);
}

void menu(){

    system("cls");

    printf("===== LABERINTO =====\n");
    printf("1. Jugar\n");
    printf("2. Instrucciones\n");
    printf("3. Salir\n");
}

void instrucciones(){

    system("cls");

    printf("INSTRUCCIONES\n\n");
    printf("Mover con W A S D\n");
    printf("Captura los trofeos (T)\n");
    printf("Necesitas 10 para ganar\n");
    printf("Evita chocar con paredes (#)\n");

    printf("\nPresiona una tecla...");
    getch();
}

int confirmarSalida(){

    printf("\nSalir al menu? (S/N): ");

    char r = getch();

    if(r=='s'||r=='S')
        return 1;

    return 0;
}

int main(){

    srand(time(NULL));

    enum Estado estado = MENU;

    int jugadorX=1;
    int jugadorY=1;

    int choques=0;
    int trofeos=0;

    char tecla='-';

    generarTrofeo();

    while(estado!=SALIR){

        switch(estado){

        case MENU:

            menu();

            char op = getch();

            if(op=='1'){
                jugadorX=1;
                jugadorY=1;
                trofeos=0;
                choques=0;
                generarTrofeo();
                estado=JUGANDO;
            }

            else if(op=='2')
                estado=INSTRUCCIONES;

            else if(op=='3')
                estado=SALIR;

        break;

        case INSTRUCCIONES:

            instrucciones();
            estado=MENU;

        break;

        case JUGANDO:

            system("cls");

            dibujarMapa(jugadorX,jugadorY);
            mostrarHUD(jugadorX,jugadorY,tecla,choques,trofeos);

            printf("\nM = Menu");

            tecla=getch();

            int nuevaX=jugadorX;
            int nuevaY=jugadorY;

            if(tecla=='w'||tecla=='W') nuevaY--;
            else if(tecla=='s'||tecla=='S') nuevaY++;
            else if(tecla=='a'||tecla=='A') nuevaX--;
            else if(tecla=='d'||tecla=='D') nuevaX++;
            else if(tecla=='m'||tecla=='M'){

                if(confirmarSalida())
                    estado=MENU;

                break;
            }
            else{

                printf("\nComando no valido");
                getch();
                break;
            }

            if(mapa[nuevaY][nuevaX]=='#'){

                choques++;
                printf("\nChoque con pared!");
                getch();
            }
            else{

                jugadorX=nuevaX;
                jugadorY=nuevaY;
            }

            // Capturar trofeo
            if(jugadorX==trofeoX && jugadorY==trofeoY){

                trofeos++;

                if(trofeos>=TROFEOS_GANAR){

                    system("cls");
                    printf("GANASTE!\n");
                    printf("Recolectaste los 10 trofeos!\n");
                    printf("\nPresiona una tecla...");
                    getch();

                    estado=MENU;
                }
                else{

                    generarTrofeo();
                }
            }

        break;

        }

    }

    printf("\nGracias por jugar\n");

    return 0;
}