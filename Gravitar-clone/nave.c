#include<math.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<SDL.h>
#include "nave.h"
#include "config.h"

struct nave{
  double pos[2]; //pos[0] = x,  pos[1] = y
  double vel[2]; //vel[0] = vel en x,  vel[1] = vel en y
  double ang_nave;
  float a_thrust;
  double ang_g;
  size_t vidas;
  size_t fuel;
  nivel_t niv;
  char nombre_fig[20];
};

nave_t *nave_crear(size_t vidas, size_t fuel, nivel_t nivel, char *figura) {
  nave_t *nave = malloc(sizeof(nave_t));
  if(nave == NULL)
    return NULL;
  nave->pos[0]=0 ; nave->pos[1]=0;
  nave->vel[0]=0; nave->vel[1]=0;
  nave->ang_nave=0;
  nave->a_thrust=0;
  nave->ang_g=0;
  nave->vidas=vidas;
  nave->fuel=fuel;
  nave->niv=nivel;
  if(strlen(figura) > 19)
    return NULL;
  strcpy(nave->nombre_fig, figura);
  return nave;
}

void nave_destruir(nave_t *nave) {
  free(nave);
}

void nave_setear_pos(nave_t *nave, double px, double py) {
  nave->pos[0] = px;
  nave->pos[1] = py;
}

void nave_setear_vel(nave_t *nave, double vx, double vy) {
    nave_setear_vel_y(nave, vy);
    nave_setear_vel_x(nave, vx);
}

void nave_setear_vel_x(nave_t* nave, double vx) {
    nave->vel[0] = vx;
}

void nave_setear_vel_y(nave_t* nave, double vy) {
    nave->vel[1] = vy;
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

bool nave_cambiar_nombre_fig(nave_t *nave, char *nombre) {
  if(strlen(nombre) > 19)
    return false;
  strcpy(nave->nombre_fig, nombre);
  return true;
}

double nave_get_posx(nave_t *nave) {
  return nave->pos[0];
}

double nave_get_posy(nave_t *nave) {
  return nave->pos[1];
}

double nave_get_ang(nave_t *nave) {
  return nave->ang_nave;
}

double nave_get_vel_x(nave_t *nave) {
    return nave->vel[0];
}

double nave_get_vel_y(nave_t *nave) {
   return nave->vel[1];
}

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

double computar_velocidad(double vi, double a, double dt) {
  return dt*a+vi;
}

double computar_posicion(double pi, double vi, double dt) {
  return dt*vi+pi;
}

double com_x(double mod, double ang) {
  return mod*cos(ang);
}

double com_y(double mod, double ang) {
  return mod*sin(ang);
}

void nave_mover(nave_t *nave, double dt) {
  double ax = com_x(nave->a_thrust, nave->ang_nave) + com_x(G, nave->ang_g);
  double ay = com_y(nave->a_thrust, nave->ang_nave) + com_y(G, nave->ang_g);
  nave->vel[0] = computar_velocidad(nave->vel[0], ax, dt);
  nave->vel[1] = computar_velocidad(nave->vel[1], ay, dt);
  nave->pos[0] = computar_posicion(nave->pos[0], nave->vel[0], dt);
  nave->pos[1] = computar_posicion(nave->pos[1], nave->vel[1], dt);
}

void nave_dibujar(nave_t *nave, polilinea_t* poli, SDL_Renderer* renderer) {
    polilinea_t* poli2 = polilinea_clonar(poli);
    rotar(poli2, nave_get_ang(nave));
    trasladar(poli2, nave_get_posx(nave), nave_get_posy(nave));
    float x1, y1, x2, y2;
    for (int i = 0; i < polilinea_cantidad_puntos(poli2) - 1; i++) {
        polilinea_obtener_punto(poli2, i, &x1, &y1);
        polilinea_obtener_punto(poli2, i + 1, &x2, &y2);
        SDL_RenderDrawLine(
            renderer,
            x1,
            (VENTANA_ALTO - y1),
            x2,
            (VENTANA_ALTO - y2)
        );
    }
    free(poli2);
}