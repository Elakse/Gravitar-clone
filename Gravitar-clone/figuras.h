#ifndef FIGURAS_H
#define FIGURAS_H
#include <stdbool.h>
#include <stdlib.h>
#include "polilinea.h"
#include <stdio.h>
#include <SDL.h>

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

figura_t* figura_crear(bool inf, size_t cant, figura_tipo_t tipo, char* nombre);
figura_t* figura_leer(FILE* f);
polilinea_t** figura_obtener_polis(figura_t* figura);
bool figura_insertar_poli(figura_t *figura, polilinea_t* poli, size_t pos);
bool figura_remover_poli(figura_t *figura, size_t pos);
bool figura_set_cant_polis(figura_t *figura, size_t cant);
bool figura_comparar_nombres(figura_t *figura, char* nombre);
char* figura_obtener_nombre(figura_t *figura);
figura_tipo_t figura_obtener_tipo(figura_t *figura);
void figura_destruir(figura_t *figura);
//bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas);
void figura_dibujar(figura_t* figura, double pos_x, double pos_y, double ang, double escala, SDL_Renderer* renderer);


#endif