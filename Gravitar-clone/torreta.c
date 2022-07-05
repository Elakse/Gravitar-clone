#include "torreta.h"

struct torreta {
	double pos[2];
	double ang;
	bool disparando; //ser� true si la ultima vez que la torreta intent� disparar, dispar�, volver� a su estado false si no lo hizo
	figura_t* torreta_fig;
	figura_t* disparando_fig;
};

torreta_t* torreta_crear(double posx, double posy, double ang, figura_t* fig_base, figura_t* fig_disparando) {
	torreta_t* torreta = malloc(sizeof(torreta_t));
	if (torreta == NULL) return NULL;
	torreta->pos[0] = posx;
	torreta->pos[1] = posy;
	torreta->ang = ang;
	torreta->torreta_fig = fig_base;
	torreta->disparando_fig = fig_disparando;
	torreta->disparando = false;
	return torreta;
}
void torreta_destruir(torreta_t* torreta, figura_t** fig_base, figura_t** fig_disparando) {
	if (fig_base != NULL) *fig_base = torreta->torreta_fig;
	if (fig_disparando != NULL) *fig_disparando = torreta->disparando_fig;
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

bool torreta_dibujar(torreta_t* torreta, double tras_x, double tras_y, double centro_escala, double escala, SDL_Renderer* renderer) {
	figura_t* fig_a_dibujar;
	if (torreta->disparando)
		fig_a_dibujar = torreta->disparando_fig;
	else
		fig_a_dibujar = torreta->torreta_fig;
	if (!figura_dibujar(fig_a_dibujar, torreta->pos[0] * escala + tras_x, torreta->pos[1] * escala + tras_y, torreta->ang, centro_escala, escala, renderer))
		return false;
	return true;
}

void torreta_set_pos(torreta_t* torreta, double posx, double posy) {
	torreta->pos[0] = posx;
	torreta->pos[1] = posy;
}
void torreta_set_ang(torreta_t* torreta, double ang) {
	torreta->ang = ang;
}


bala_t* torreta_dispara(torreta_t* torreta, double ang, double rango, size_t chances, double vel) {
	int factor;
	while ((factor = -100 + rand() % 201) == 0);
	double ang_final = ang + rango / factor;
	if (rand() % 100 < (chances - 1)) {
		bala_t* bala = bala_crear(torreta->pos[0], torreta->pos[1], vel, ang_final, false);
		torreta->disparando = true;
		return bala;
	}
	else
		torreta->disparando = false;
		return NULL;
	
}

double torreta_distancia_a_punto(torreta_t* torreta, double px, double py) {
	figura_t* figura = figura_clonar(torreta->torreta_fig);
	if (figura == NULL) return -1;
	figura_trasladar(figura, torreta->pos[0], torreta->pos[1]);
	double distancia = figura_distancia_a_punto(figura, px, py);
	figura_destruir(figura);
	return distancia;
}