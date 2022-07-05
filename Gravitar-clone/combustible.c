#include "combustible.h"

struct combustible {
	double pos[2];
	double ang;
	estadio_t nivel;
};

combustible_t* combustible_crear(estadio_t nivel, double posx, double posy, double ang) {
	combustible_t* combustible = malloc(sizeof(combustible_t));
	if (combustible == NULL) return NULL;
	combustible->pos[0] = posx;
	combustible->pos[1] = posy;
	combustible->ang = ang;
	combustible->nivel = nivel;
	return combustible;
}

void combustible_destruir(combustible_t* combustible) {
	free(combustible);
}

double combustible_get_posx(combustible_t* combustible) {
	return combustible->pos[0];
}
double combustible_get_posy(combustible_t* combustible) {
	return combustible->pos[1];
}
double combustible_get_ang(combustible_t* combustible) {
	return combustible->ang;
}
estadio_t combustible_get_nivel(combustible_t* combustible) {
	return combustible->nivel;
}

void combustible_set_pos(combustible_t* combustible, double posx, double posy) {
	combustible->pos[0] = posx;
	combustible->pos[1] = posy;
}
void combustible_set_ang(combustible_t* combustible, double ang) {
	combustible->ang = ang;
}
void combustible_set_nivel(combustible_t* combustible, estadio_t nivel) {
	combustible->nivel = nivel;
}