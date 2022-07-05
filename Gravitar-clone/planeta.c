#include "nivel.h"
#include "fisica.h"
#include <string.h>
#include "planeta.h"

struct planeta {
	double pos[2];
	double pos_tp[2];
	estadio_t estadio;
	figura_t* fig;
};

planeta_t* planeta_crear(double posx, double posy, double posx_tp, double posy_tp, estadio_t nivel, figura_t* planeta_fig) {
	planeta_t* planeta = malloc(sizeof(planeta_t));
	if (planeta == NULL) return NULL;
	planeta->pos[0] = posx; planeta->pos[1] = posy;
	planeta->pos_tp[0] = posx_tp; planeta->pos_tp[1] = posy_tp;
	planeta->estadio = nivel;
	planeta->fig = planeta_fig;
	return planeta;
}

void planeta_destruir(planeta_t* planeta) {
	free(planeta);
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

double planeta_distancia_a_punto(planeta_t* planeta, double x, double y) {
	return computar_distancia(planeta->pos[0], planeta->pos[1], x, y);
}

//------------------------------------------------------------------------------DIBUJADO----------------------------------------------------------------------------------------

bool planeta_dibujar(planeta_t* planeta, double tras_x, double tras_y, double centro_escala, double escala, SDL_Renderer* renderer) {
	if (!figura_dibujar(planeta->fig, planeta->pos[0] * escala + tras_x, planeta->pos[1] * escala + tras_y, 0, centro_escala, escala, renderer))
		return false;
	return true;
}