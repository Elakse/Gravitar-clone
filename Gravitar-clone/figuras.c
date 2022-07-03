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

figura_t* figura_crear(bool inf, figura_tipo_t tipo, char* nombre) {
	figura_t* figura = malloc(sizeof(figura_t));
	if (figura == NULL) return NULL;

	figura->polis = NULL;
	figura->inf = inf;
	figura->cant = 0;
	figura->tipo = tipo;

	if (strlen(nombre) < 20) {
		strcpy(figura->nombre, nombre);
	}
	else {
		free(figura);
		return NULL;
	}
	return figura;
}

bool figura_agregar_poli(figura_t* figura, polilinea_t* poli) {
	polilinea_t** aux = realloc(figura->polis, sizeof(polilinea_t*) * (figura->cant + 1));
	if (aux == NULL) return false;
	figura->polis = aux;
	figura->polis[figura->cant] = polilinea_clonar(poli);
	if (figura->polis[figura->cant] == NULL) return NULL;
	figura->cant++;
	return true;
}

bool figura_set_cant_polis(figura_t* figura, size_t cant) {
	polilinea_t** aux = realloc(figura->polis, sizeof(polilinea_t*) * cant);
	if (aux == NULL) return false;
	figura->polis = aux;
	for (size_t i = figura->cant;i < cant; i++)
		figura->polis[i] = NULL;
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
	figura_t* figura = figura_crear(inf, tipo, nombre);
	for (size_t i = 0; i < cant; i++) {
		polilinea_t* poli = leer_polilinea(f);
		if (poli == NULL) {
			figura_destruir(figura);
			return NULL;
		}
		if (!figura_agregar_poli(figura, poli)) {
			figura_destruir(figura);
			polilinea_destruir(poli);
			return NULL;
		}
		polilinea_destruir(poli);
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

double figura_obtener_x_max(figura_t* figura) {
	double max = polilinea_obtener_x_max(figura->polis[0]);
	double aux;
	for (size_t i = 1; i < figura->cant; i++)
		if(figura->polis[i] != NULL)
			if ((aux = polilinea_obtener_x_max(figura->polis[i])) > max)
				max = aux;
	return max;
}

double figura_obtener_y_max(figura_t* figura) {
	double max = polilinea_obtener_y_max(figura->polis[0]);
	double aux;
	for (size_t i = 1; i < figura->cant; i++)
		if ((aux = polilinea_obtener_y_max(figura->polis[i])) > max)
			max = aux;
	return max;
}

double figura_obtener_x_min(figura_t* figura) {
	double min = polilinea_obtener_x_min(figura->polis[0]);
	double aux;
	for (size_t i = 1; i < figura->cant; i++)
		if ((aux = polilinea_obtener_x_min(figura->polis[i])) > min)
			min = aux;
	return min;
}

double figura_obtener_y_min(figura_t* figura) {
	double min = polilinea_obtener_y_min(figura->polis[0]);
	double aux;
	for (size_t i = 1; i < figura->cant; i++)
		if ((aux = polilinea_obtener_y_min(figura->polis[i])) > min)
			min = aux;
	return min;
}

double figura_obtener_ancho(figura_t* figura) {
	return fabs(figura_obtener_x_max(figura) - figura_obtener_x_min(figura));
}

double figura_obtener_alto(figura_t* figura) {
	return fabs(figura_obtener_y_max(figura) - figura_obtener_y_min(figura));
}

bool figura_es_inf(figura_t* figura) {
	return figura->inf;
}

void figura_dibujar(figura_t* figura, double pos_x, double pos_y, double ang, double escala, SDL_Renderer* renderer) {
	for (size_t i = 0; i < figura->cant; i++) {
		polilinea_dibujar(figura->polis[i], pos_x, pos_y, ang, escala, renderer);
	}
}

void figura_dibujar_escala_relativa(figura_t* figura, double pos_x, double pos_y, double ang, double centro, double escala, SDL_Renderer* renderer) {
	for (size_t i = 0; i < figura->cant; i++) {
		polilinea_dibujar_escala_relativa(figura->polis[i], pos_x, pos_y, ang, centro, escala, renderer);
	}
}
