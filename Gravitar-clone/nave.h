#ifndef NAVE_H
#define NAVE_H

#include "polilinea.h"

typedef enum{INICIO, NIVEL1, NIVEL2, NIVEL3, NIVEL4, NIVEL5} nivel_t;
typedef struct nave nave_t;

nave_t *crear_nave(size_t vidas, size_t fuel, nivel_t nivel, char *figura);

//SETTERS

void setear_pos(nave_t *nave, double px, double py);
void setear_vel(nave_t *nave, double vx, double vy);
void setear_ang_nave(nave_t *nave, double ang);
void setear_a_thrust(nave_t *nave, float a);
void setear_ang_g(nave_t *nave, double ang);
void setear_a_grav(nave_t *nave, float a);
bool cambiar_nombre_fig(nave_t *nave, char *nombre);

//GETTERS

double get_posx(nave_t *nave);
double get_posy(nave_t *nave);


//MOVIMIENTO

void girar_nave_der(nave_t *nave, double ang);
void girar_nave_izq(nave_t *nave, double ang);
void mover_nave(nave_t *nave, double dt);

#endif
