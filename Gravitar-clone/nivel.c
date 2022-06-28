#include "nivel.h"
#include "lista.h"

struct nivel {
	lista_t *figuras;
	nivel_enum_t nivel_enum;
};

nivel_t* nivel_crear(nivel_enum_t nivel_enum, lista_t* 0'figuras) {
	nivel_t* nivel = malloc(sizeof(nivel_t));
	if (nivel == NULL) return NULL;
	nivel->nivel_enum = nivel_enum;
	nivel->figuras = figuras;
}