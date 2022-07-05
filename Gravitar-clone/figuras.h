#ifndef FIGURAS_H
#define FIGURAS_H
#include <stdbool.h>
#include <stdlib.h>
#include "polilinea.h"
#include <stdio.h>
#include <SDL.h>

struct figura;
typedef struct figura figura_t;

typedef enum {
	ICONO,
	NIVEL,
	SPRITE,
	PLANETA,
	BASE,
	COMBUSTIBLE,
	TORRETA,
	REACTOR,
} figura_tipo_t;


//CREACION Y DESTRUCCION
figura_t* figura_crear(bool inf, figura_tipo_t tipo, char* nombre);
void figura_destruir(figura_t* figura);

//LECTURA
figura_t* figura_leer(FILE* f);
static bool leer_encabezado_figura(FILE* f, char nombre[], figura_tipo_t* tipo, bool* infinito, size_t* cantidad_polilineas);

//GETTERS
polilinea_t** figura_obtener_polis(figura_t* figura);
bool figura_comparar_nombres(figura_t* figura, char* nombre);
bool figura_es_inf(figura_t* figura);
char* figura_obtener_nombre(figura_t* figura);
figura_tipo_t figura_obtener_tipo(figura_t* figura);
double figura_obtener_x_max(figura_t* figura);
double figura_obtener_y_max(figura_t* figura);
double figura_obtener_x_min(figura_t* figura);
double figura_obtener_y_min(figura_t* figura);
double figura_obtener_alto(figura_t* figura);
double figura_obtener_ancho(figura_t* figura);

//SETTERS
bool figura_agregar_poli(figura_t* figura, polilinea_t* poli);
bool figura_set_cant_polis(figura_t *figura, size_t cant);

//MOVIMIENTOS Y DISTANCIAS
void figura_trasladar(figura_t* figura, float dx, float dy);
void figura_rotar(figura_t* figura, double rad);
void figura_escalar(figura_t* figura, double escala);
double figura_distancia_a_punto(figura_t* figura, double px, double py);

//MEMORIA
figura_t* figura_clonar(figura_t* figura);

//DIBUJADO
bool figura_dibujar(figura_t* figura, double dx, double dy, double ang, double centro, double escala, SDL_Renderer* renderer);

#endif