    //Para definir los limites del area del juego usando una matriz bidimensional

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h> // para _kbhit y _getch en Windows

#define WIDTH 40
#define HEIGHT 20

char areaJuego[HEIGHT][WIDTH];

void dibujarArea() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                printf("#");
            } else {
                printf("%c", areaJuego[i][j]);
            }
        }
        printf("\n");
    }
}

// Estructura de la serpiente
typedef struct {
    int x, y;
} Posicion;

typedef struct {
    Posicion segmentos[100];
    int longitud;
    char direccion;
} Serpiente;

Serpiente serpiente = {{{10, 10}, {10, 11}, {10, 12}}, 3, 'L'}; // L para izquierda

// Control del movimiento 
void cambiarDireccion(char input) {
    if (input == 'w' || input == 'W') serpiente.direccion = 'U'; // Up
    if (input == 's' || input == 'S') serpiente.direccion = 'D'; // Down
    if (input == 'a' || input == 'A') serpiente.direccion = 'L'; // Left
    if (input == 'd' || input == 'D') serpiente.direccion = 'R'; // Right
}

void moverSerpiente() {
    Posicion nuevaCabeza = serpiente.segmentos[0];

    if (serpiente.direccion == 'U') nuevaCabeza.x--;
    if (serpiente.direccion == 'D') nuevaCabeza.x++;
    if (serpiente.direccion == 'L') nuevaCabeza.y--;
    if (serpiente.direccion == 'R') nuevaCabeza.y++;

    for (int i = serpiente.longitud; i > 0; --i) {
        serpiente.segmentos[i] = serpiente.segmentos[i - 1];
    }
    serpiente.segmentos[0] = nuevaCabeza;
    if (serpiente.longitud < 100) serpiente.longitud++;
}

//Fruta aleatoria 
Posicion fruta;

void generarFruta() {
    srand(time(0));
    do {
        fruta.x = rand() % HEIGHT;
        fruta.y = rand() % WIDTH;
    } while (areaJuego[fruta.x][fruta.y] != ' ');
    areaJuego[fruta.x][fruta.y] = '*'; // '*' representa la fruta
}

// Actualizar y dibujar 
void actualizarArea() {
    // Limpiar el área de la serpiente
    for (int i = 0; i < serpiente.longitud; ++i) {
        areaJuego[serpiente.segmentos[i].x][serpiente.segmentos[i].y] = ' ';
    }

    // Dibujar la serpiente
    for (int i = 0; i < serpiente.longitud; ++i) {
        areaJuego[serpiente.segmentos[i].x][serpiente.segmentos[i].y] = 'O';
    }

    // Dibujar la fruta
    areaJuego[fruta.x][fruta.y] = '*';
}

// Bucle principal del juego 
int main() {
    generarFruta();
    while (1) {
        dibujarArea();
        if (_kbhit()) {
            char input = _getch(); // Leer la entrada del usuario
            cambiarDireccion(input);
        }
        moverSerpiente();
        actualizarArea();
        system("cls"); // Limpiar la consola (en Windows)
        _sleep(100); // Pausar un poco para ver el movimiento
    }
    return 0;
}


