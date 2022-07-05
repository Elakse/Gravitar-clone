#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<SDL.h>
#include "nave.h"
#include "config.h"
#include "fisica.h"

struct nave{
  double pos[2]; //pos[0] = x,  pos[1] = y
  double vel[2]; //vel[0] = vel en x,  vel[1] = vel en y
  double ang_nave;
  double ang_g;
  float a_thrust;
  size_t vidas;
  size_t fuel;
  estadio_t estad;
  figura_t* nave_fig;
  figura_t* thrust_on_fig;
};

nave_t *nave_crear(size_t vidas, size_t fuel, estadio_t estadio, figura_t* fig_base, figura_t* fig_thruster_on) {
  nave_t *nave = malloc(sizeof(nave_t));
  if(nave == NULL) return NULL;
  nave->pos[0]=0 ; nave->pos[1]=0;
  nave->vel[0]=0; nave->vel[1]=0;
  nave->ang_nave = 0;
  nave->ang_g = 0;
  nave->a_thrust = 0;
  nave->vidas = vidas;
  nave->fuel = fuel;
  nave->estad = estadio;
  nave->nave_fig = fig_base;
  nave->thrust_on_fig = fig_thruster_on;

  return nave;
}

void nave_destruir(nave_t *nave, figura_t ** fig_base, figura_t ** fig_thruster_on) {
    if (fig_base != NULL) *fig_base = nave->nave_fig;
    if (fig_thruster_on != NULL) *fig_thruster_on = nave->thrust_on_fig;
    free(nave);
}

void nave_setear_vidas(nave_t *nave, size_t vidas) {
    nave->vidas = vidas;
}

void nave_restar_vida(nave_t* nave) {
    nave->vidas--;
}

void nave_sumar_vida(nave_t* nave) {
    nave->vidas++;
}

void nave_setear_pos(nave_t *nave, double px, double py) {
    nave->pos[0] = px;
    nave->pos[1] = py;
}

void nave_setear_vel(nave_t *nave, double vx, double vy) {
    nave_setear_vely(nave, vy);
    nave_setear_velx(nave, vx);
}

void nave_setear_velx(nave_t* nave, double vx) {
    nave->vel[0] = vx;
}

void nave_setear_vely(nave_t* nave, double vy) {
    nave->vel[1] = vy;
}

void nave_setear_estadio(nave_t* nave, estadio_t estadio) {
    nave->estad = estadio;
}

void nave_setear_ang_nave(nave_t *nave, double ang) {
    nave->ang_nave = ang;
}

void nave_setear_a_thrust(nave_t *nave, float a) {
    nave->a_thrust = a;
}

void nave_setear_ang_g(nave_t *nave, double ang) {
    nave->ang_g = ang;
}

double nave_get_posx(nave_t *nave) {
    return nave->pos[0];
}

double nave_get_posy(nave_t *nave) {
    return nave->pos[1];
}

size_t nave_get_vidas(nave_t *nave) {
    return nave->vidas;
}

estadio_t nave_get_estadio(nave_t* nave) {
    return nave->estad;
}

double nave_get_ang(nave_t *nave) {
    return nave->ang_nave;
}

double nave_get_velx(nave_t *nave) {
    return nave->vel[0];
}

double nave_get_vely(nave_t *nave) {
    return nave->vel[1];
}

double nave_get_vel(nave_t* nave) {
    return com_modulo(nave_get_velx(nave), nave_get_vely(nave));
}

//-----------------------------------------------------------------------ACCIONES--------------------------------------------------------------------------------------------

void nave_girar_der(nave_t *nave, double ang) {
    if(nave->ang_nave == 0) {
        nave_setear_ang_nave(nave, 2*PI);
        return;
    }
    nave->ang_nave-=ang;
}

void nave_girar_izq(nave_t *nave, double ang) {
    if(nave->ang_nave == 2*PI) {
        nave_setear_ang_nave(nave, 0);
        return;
    }
    nave->ang_nave+=ang;
}

void nave_mover(nave_t *nave, double dt) {
    double ax = com_x(nave->a_thrust, nave->ang_nave) + com_x(G, nave->ang_g);
    double ay = com_y(nave->a_thrust, nave->ang_nave) + com_y(G, nave->ang_g);
    nave->vel[0] = computar_velocidad(nave->vel[0], ax, dt);
    nave->vel[1] = computar_velocidad(nave->vel[1], ay, dt);
    nave->pos[0] = computar_posicion(nave->pos[0], nave->vel[0], dt);
    nave->pos[1] = computar_posicion(nave->pos[1], nave->vel[1], dt);
}

struct bala* nave_dispara(nave_t* nave, double vel, size_t duracion_disparo, figura_t* bala_fig) {
    bala_t* bala = bala_crear(nave->pos[0], nave->pos[1], vel, nave->ang_nave, duracion_disparo, true, bala_fig);
    if (bala == NULL) return NULL;
    bala_set_vel(bala, nave->vel[0] + bala_get_velx(bala), nave->vel[1] + bala_get_vely(bala));
    return bala;
}

//----------------------------------------------------------------------DISTANCIAS-------------------------------------------------------------------------------------------------

double nave_distancia_a_punto(nave_t* nave, double px, double py) {
    figura_t* figura = figura_clonar(nave->nave_fig);
    if (figura == NULL) return -1;
    figura_trasladar(figura, nave->pos[0], nave->pos[1]);
    double distancia = figura_distancia_a_punto(figura, px, py);
    figura_destruir(figura);
    return distancia;
}

//Por simplicidad aqu� tomamos distancia desde la posicion de la nave y no su figura
double nave_distancia_a_figura(nave_t* nave, figura_t* figura) {
    return figura_distancia_a_punto(figura, nave->pos[0], nave->pos[1]);
}


//----------------------------------------------------------------------DIBUJADO--------------------------------------------------------------------------

bool nave_dibujar(nave_t* nave, double tras_x, double tras_y, double centro_escala, double escala, SDL_Renderer* renderer) {
    figura_t* fig_a_dibujar;
    if (nave->a_thrust != 0)
        fig_a_dibujar = nave->thrust_on_fig;
    else
        fig_a_dibujar = nave->nave_fig;
    if (!figura_dibujar(fig_a_dibujar, nave->pos[0] * escala + tras_x, nave->pos[1] * escala + tras_y, nave->ang_nave, centro_escala, escala, renderer))
        return false;
    return true;
}