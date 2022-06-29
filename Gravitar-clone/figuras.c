#include "figuras.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "polilinea.h"
#include <stdio.h>
#include "config.h"
	
struct figura {
	char nombre[20];
	bool inf;
	figura_tipo_t tipo;
	size_t cant;
	polilinea_t** polis;
};

struct figura_render {
	figura_t* figura;
	double posx;
	double posy;
	double ang;
	double escala;
};

figura_render_t* figura_render_crear(figura_t *figura, double posx, double posy, double ang, double escala) {
	figura_render_t* figura_render = malloc(sizeof(figura_render_t));
	if (figura_render == NULL) return NULL;
	figura_render->figura = figura;
	figura_render->posx = posx;
	figura_render->posy = posy;
	figura_render->ang = ang;
	figura_render->escala = escala;
	return figura_render;
}

void figura_render_destruir(figura_render_t* figura_render) {
	free(figura_render);
}

figura_t* figura_crear(bool inf, size_t cant, figura_tipo_t tipo, char* nombre) {
	figura_t* figura = malloc(sizeof(figura_t));
	if (figura == NULL) return NULL;

	figura->polis = malloc(sizeof(polilinea_t*) * cant);
	if (figura->polis == NULL) {
		free(figura);
		return NULL;
	}
	figura->inf = inf;
	figura->cant = cant;
	figura->tipo = tipo;

	if (strlen(nombre) < 20) {
		strcpy(figura->nombre, nombre);
	}
	else {
		free(figura->polis);
		free(figura);
		return NULL;
	}
	return figura;
}

figura_t* figura_clonar(figura_t* figura) {
	figura_t* clon = malloc(sizeof(figura_t));
	if (clon == NULL) return NULL;

	clon->polis = malloc(sizeof(polilinea_t*) * figura->cant);
	if (clon->polis == NULL) {
		free(clon);
		return NULL;
	}

	for(size_t i = 0; i < figura->cant; i++)
		clon->polis[i] = polilinea_clonar(figura->polis[i]);

	clon->inf = figura->inf;
	clon->cant = figura->cant;
	clon->tipo = figura->tipo;
	strcpy(clon->nombre, figura->nombre);
	return clon;
}

bool figura_insertar_poli(figura_t* figura, polilinea_t* poli, size_t pos) {
	if (pos >= figura->cant || pos < 0) return false;
	figura->polis[pos] = poli;
	return true;
}

bool figura_remover_poli(figura_t* figura, size_t pos) {
	if (pos >= figura->cant || pos < 0) return false;
	figura->polis[pos] = NULL;
	return true;
}

bool figura_set_cant_polis(figura_t* figura, size_t cant) {
	polilinea_t** aux = realloc(figura->polis, sizeof(polilinea_t*) * cant);
	if (aux == NULL) return false;
	figura->polis = aux;
	figura->cant = cant;
	return true;
}

bool figura_comparar_nombres(figura_t* figura, char* nombre) {
	return strcmp(figura->nombre, nombre) ? false : true;
}

void figura_destruir(figura_t* figura) {
	for (size_t i = 0; i < figura->cant; i++) {
		polilinea_destruir(figura->polis[i]);
	}
	free(figura->polis);
	free(figura);
}

static bool leer_encabezado_figura(FILE* f, char nombre[], figura_tipo_t* tipo, bool* infinito, size_t* cantidad_polilineas) {
	size_t nom_size, carac_size, cant_size;

	nom_size = fread(nombre, sizeof(char), 20, f);
	if (nom_size < 20) return false;

	uint8_t carac = 0;
	carac_size = fread(&carac, sizeof(char), 1, f);
	if (carac_size < 1) return false;

	uint16_t cant = 0;
	cant_size = fread(&cant, sizeof(uint16_t), 1, f);
	if (cant_size < 1) return false;

	*cantidad_polilineas = cant;
	*infinito = (carac & INFINITO);
	*tipo = ((carac >> 1) & TIPO);
	return 1;
}

figura_t* figura_leer(FILE* f) {
	bool inf;
	size_t cant;
	figura_tipo_t tipo;
	char nombre[20];
	if (!leer_encabezado_figura(f, nombre, &tipo, &inf, &cant)) return NULL;
	figura_t* figura = figura_crear(inf, cant, tipo, nombre);
	if(figura == NULL) return NULL;
	for (size_t i = 0; i < cant; i++) {
		polilinea_t* poli = leer_polilinea(f);
		if (poli == NULL) {
			figura_destruir(figura);
			return NULL;
		}
		figura_insertar_poli(figura, poli, i);
	}
	return figura;
}

figura_tipo_t figura_obtener_tipo(figura_t* figura) {
	return figura->tipo;
}

char* figura_obtener_nombre(figura_t* figura) {
	return figura->nombre;
}

polilinea_t** figura_obtener_polis(figura_t* figura){
	polilinea_t** polis = figura->polis;
	return polis;
}


//Esta es la funcion que deberia transladar y escalar todo al dibujarlo, No se como se haria pero estan las herramientas.
void figura_render_dibujar(figura_render_t* figura_render, double escala, double centro, SDL_Renderer* renderer) {
	figura_dibujar(figura_render->figura, figura_render->posx + centro, figura_render->posy, figura_render->ang, figura_render->escala * escala, renderer);
}

void figura_dibujar(figura_t* figura, double pos_x, double pos_y, double ang, double escala, SDL_Renderer* renderer) {
	for (size_t i = 0; i < figura->cant; i++) {
		polilinea_dibujar(figura->polis[i], pos_x, pos_y, ang, escala, renderer);
	}
}
