#include "nivel.h"
#include "fisica.h"
#include <string.h>
#include "planeta.h"

struct planeta {
	double pos[2];
	nivel_enum_t nivel;
	char figura_nom[20];
};

planeta_t* planeta_crear(double posx, double posy, nivel_enum_t nivel, char * figura_nom) {
	planeta_t* planeta = malloc(sizeof(planeta_t));
	if (planeta == NULL) return NULL;
	if (strlen(figura_nom) > 19) return NULL;
	strcpy(planeta->figura_nom, figura_nom);
	planeta->pos[0] = posx;
	planeta->pos[1] = posy;
	planeta->nivel = nivel;
	return planeta;
}

void planeta_destruir(planeta_t* planeta) {
	free(planeta);
}

nivel_enum_t planeta_get_nivel(planeta_t* planeta) {
	return planeta->nivel;
}

char* planeta_get_figura_nom(planeta_t* planeta) {
	return planeta->figura_nom;
}

double planeta_get_posx(planeta_t* planeta) {
	return planeta->pos[0];
}

double planeta_get_posy(planeta_t* planeta) {
	return planeta->pos[1];
}

double planeta_distancia_a_punto(planeta_t* planeta, double x, double y) {
	return computar_distancia(planeta->pos[0], planeta->pos[1], x, y);
}