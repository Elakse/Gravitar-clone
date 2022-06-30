#include <stdio.h>
#include <stdbool.h>
#include "bala.h"
//#include "nave.h"
#include "fisica.h"
//#include "config.h"
//#include "lista.h"

struct bala {
	double pos[2]; //pos[0] = x,  pos[1] = y
	double vel[2]; //vel[0] = vel en x,  vel[1] = vel en y
	nivel_enum_t nivel;
	bool jugador;
	size_t contador;
};

bala_t* bala_crear(nivel_enum_t nivel, double posx, double posy, double vel, double ang, bool jugador) {
	bala_t* bala = malloc(sizeof(bala_t));
	if (bala == NULL) return NULL;
	bala->pos[0] = posx;
	bala->pos[1] = posy;
	bala->vel[0] = vel*cos(ang);
	bala->vel[1] = vel*sin(ang);
	bala->nivel = nivel;
	bala->contador = BALA_DURACION;
	return bala;
}
void bala_destruir(bala_t* bala) {
	free(bala);
}


double bala_get_posx(bala_t *bala) {
	return bala->pos[0];
}
double bala_get_posy(bala_t *bala) {
	return bala->pos[1];
}
double bala_get_velx(bala_t* bala) {
	return bala->vel[0];
}
double bala_get_vely(bala_t* bala) {
	return bala->vel[1];
}
nivel_enum_t bala_get_nivel(bala_t* bala) {
	return bala->nivel;
}
bool bala_es_de_jugador(bala_t* bala) {
	return bala->jugador;
}

void bala_set_pos(bala_t* bala, double posx, double posy) {
	bala->pos[0] = posx;
	bala->pos[1] = posy;
}
void bala_set_vel(bala_t* bala, double velx, double vely) {
	bala->vel[0] = velx;
	bala->vel[1] = vely;
}
void bala_set_nivel(bala_t* bala, nivel_enum_t nivel) {
	bala->nivel = nivel;
}

bool bala_actualizar(bala_t *bala, double dt) {
	if (bala->contador != 0) {
		bala->pos[0] = computar_posicion(bala->pos[0], bala->vel[0], dt);
		bala->pos[1] = computar_posicion(bala->pos[1], bala->vel[1], dt);
		bala->contador--;
		return true;
	}
	return false;
}

/*void balas_mover(lista_t* balas) {
	if (lista_esta_vacia(balas)) return;
	lista_iter_t *iter = lista_iter_crear(balas);
	bala_t* bala;
	do {
		bala = lista_iter_ver_actual(iter);
		bala_mover(bala, 1.0/JUEGO_FPS);
		lista_iter_avanzar(iter);
	} while (!lista_iter_al_final(iter));
	lista_iter_destruir(iter);
}*/