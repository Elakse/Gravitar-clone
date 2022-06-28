#include <stdio.h>
#include <stdbool.h>
#include "bala.h"
#include "nave.h"
#include "fisica.h"
#include "config.h"
#include "lista.h"

struct bala {
	double pos[2]; //pos[0] = x,  pos[1] = y
	double vel; //vel[0] = vel en x,  vel[1] = vel en y
	double ang;
	nivel_t nivel;
	bool jugador;
	size_t contador;
};

bala_t* bala_crear(nave_t *nave) {
	bala_t* bala = malloc(sizeof(bala_t));
	if (bala == NULL) return NULL;
	bala->pos[0] = nave_get_posx(nave);
	bala->pos[1] = nave_get_posy(nave);
	bala->vel = nave_get_vel(nave) + BALA_VELOCIDAD;
	bala->ang = nave_get_ang(nave);
	bala->nivel = nave_get_nivel(nave);
	bala->contador = 400;
	return bala;
}
void bala_destruir(bala_t* bala) {
	free(bala);
}

double bala_get_ang(bala_t *bala) {
	return bala->ang;
}
double bala_get_posx(bala_t *bala) {
	return bala->pos[0];
}
double bala_get_posy(bala_t *bala) {
	return bala->pos[1];
}
double bala_get_vel(bala_t* bala) {
	return bala->vel;
}
double bala_get_velx(bala_t *bala) {
	return com_x(bala->vel, bala->ang);
}
double bala_get_vely(bala_t* bala) {
	return com_y(bala->vel, bala->ang);
}
nivel_t bala_get_nivel(bala_t* bala) {
	return bala->nivel;
}
bool bala_es_de_jugador(bala_t* bala) {
	return bala->jugador;
}

void bala_set_pos(bala_t* bala, double posx, double posy) {
	bala->pos[0] = posx;
	bala->pos[1] = posy;
}
void bala_set_vel(bala_t* bala, double vel) {
	bala->vel = vel;
}
void bala_set_nivel(bala_t* bala, nivel_t nivel) {
	bala->nivel = nivel;
}
void bala_setear_ang(bala_t *bala, double ang) {
	bala->ang = ang;
}

void bala_mover(bala_t *bala, double dt) {
	bala->pos[0] = computar_posicion(bala->pos[0], com_x(bala->vel, bala->ang), dt);
	bala->pos[1] = computar_posicion(bala->pos[1], com_y(bala->vel, bala->ang), dt);
}

void balas_mover(lista_t *balas) {
	if (lista_esta_vacia(balas)) return;
	lista_iter_t *iter = lista_iter_crear(balas);
	bala_t* bala;
	do {
		bala = lista_iter_ver_actual(iter);
		bala_mover(bala, 1.0/JUEGO_FPS);
	} while (lista_iter_avanzar(iter));
	free(iter);
}