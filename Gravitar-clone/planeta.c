#include "fisica.h"
#include <string.h>
#include "planeta.h"
#include "escritura.h"
#include "config.h"

struct planeta {
	double pos[2];
	double pos_tp[2];
	estadio_t estadio;
	figura_t* fig;
	size_t puntaje;
};

planeta_t* planeta_crear(double posx, double posy, double posx_tp, double posy_tp, size_t puntaje, estadio_t nivel, figura_t* planeta_fig) {
	planeta_t* planeta = malloc(sizeof(planeta_t));
	if (planeta == NULL) return NULL;
	planeta->pos[0] = posx; planeta->pos[1] = posy;
	planeta->pos_tp[0] = posx_tp; planeta->pos_tp[1] = posy_tp;
	planeta->estadio = nivel;
	planeta->fig = planeta_fig;
	planeta->puntaje = puntaje;
	return planeta;
}

void planeta_destruir(planeta_t* planeta, figura_t** figura) {
	if (figura != NULL) *figura = planeta->fig;
	free(planeta);
}

void planeta_destruir_no_ref(planeta_t* planeta) {
	planeta_destruir(planeta, NULL);
}

estadio_t planeta_get_estadio(planeta_t* planeta) {
	return planeta->estadio;
}

figura_t* planeta_get_fig(planeta_t* planeta) {
	return planeta->fig;
}

double planeta_get_posx(planeta_t* planeta) {
	return planeta->pos[0];
}

double planeta_get_posy(planeta_t* planeta) {
	return planeta->pos[1];
}

double planeta_get_posx_tp(planeta_t* planeta) {
	return planeta->pos_tp[0];
}

double planeta_get_posy_tp(planeta_t* planeta) {
	return planeta->pos_tp[1];
}

size_t planeta_get_puntaje(planeta_t* planeta) {
	return planeta->puntaje;
}

double planeta_distancia_a_punto(planeta_t* planeta, double px, double py) {
	figura_t* figura = figura_clonar(planeta->fig);
	if (figura == NULL) return -1;
	figura_trasladar(figura, planeta->pos[0], planeta->pos[1]);
	double distancia = figura_distancia_a_punto(figura, px, py);
	figura_destruir(figura);
	return distancia;
}



//DIBUJO

bool planeta_dibujar(planeta_t* planeta, double tras_x, double tras_y, double centro_escala, double escala, SDL_Renderer* renderer) {
	if (!figura_dibujar(planeta->fig, planeta->pos[0] * escala + tras_x, planeta->pos[1] * escala + tras_y, 0, centro_escala, escala, renderer))
		return false;
	char buffer[20];
	dibujar_texto(_itoa(planeta_get_puntaje(planeta), buffer, 10), planeta->pos[0] * escala + tras_x - 60, planeta->pos[1] * escala + tras_y + 10, 1.5, 0, 1, 1, VENTANA_ALTO, renderer);
	return true;
}