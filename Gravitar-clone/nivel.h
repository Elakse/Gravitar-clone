#ifndef NIVEL_H
#define NIVEL_H

typedef enum { INICIO, NIVEL1, NIVEL2, NIVEL3, NIVEL4, NIVEL5 } nivel_enum_t;

typedef struct nivel nivel_t;

nivel_t* nivel_crear(nivel_enum_t nivel_enum, lista_t *figuras);

#endif