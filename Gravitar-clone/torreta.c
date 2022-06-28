#include "torreta.h"

struct torreta {
	double pos[2];
	double ang;
	nivel_t nivel;
};

torreta_t* torreta_crear(nivel_t nivel, double posx, double posy, double ang) {
	torreta_t* torreta = malloc(sizeof(torreta_t));
	if (torreta == NULL) return NULL;
	torreta->pos[0] = posx;
	torreta->pos[1] = posy;
	torreta->ang = ang;
	torreta->nivel = nivel;
}
void torreta_destruir(torreta_t* torreta) {
	free(torreta);
}

double torreta_get_posx(torreta_t* torreta) {
	return torreta->pos[0];
}
double torreta_get_posy(torreta_t* torreta) {
	return torreta->pos[1];
}
double torreta_get_ang(torreta_t* torreta) {
	return torreta->ang;
}
nivel_t torreta_get_nivel(torreta_t* torreta) {
	return torreta->nivel;
}

void torreta_set_pos(torreta_t* torreta, double posx, double posy) {
	torreta->pos[0] = posx;
	torreta->pos[1] = posy;
}
void torreta_set_ang(torreta_t* torreta, double ang) {
	torreta->ang = ang;
}
void torreta_set_nivel(torreta_t* torreta, nivel_t nivel) {
	torreta->nivel = nivel;
}