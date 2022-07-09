#include "nivel.h"
#include "lista.h"
#include "torreta.h"
#include "combustible.h"
#include "config.h"
#include "fisica.h"
#include "bala.h"
#include "reactor.h"
#include <stdbool.h>
#include "planeta.h"

struct nivel {
    lista_t* torretas;
    lista_t* combustibles;
    lista_t* balas;
    lista_t* planetas;
    lista_t* reactores;
    figura_t* figura;
    bool es_asteroide;
    size_t duracion_balas;
    size_t puntaje;         //Puntaje que se obtiene al vencer el nivel
};

nivel_t* nivel_crear(figura_t *figura, size_t duracion_de_balas, size_t puntaje) {
    nivel_t* nivel = malloc(sizeof(nivel_t));
    if (nivel == NULL) return NULL;
    nivel->torretas = lista_crear();
    nivel->combustibles = lista_crear();
    nivel->balas = lista_crear();
    nivel->planetas = lista_crear();
    nivel->reactores = lista_crear();
    nivel->figura = figura;
    nivel->duracion_balas = duracion_de_balas;
    nivel->puntaje = puntaje;
    nivel->es_asteroide = 0;
	return nivel;
}

void nivel_set_asteroide(nivel_t *nivel, bool es_asteroide) {
    nivel->es_asteroide = es_asteroide;
}

bool nivel_es_asteroide(nivel_t *nivel) {
    return nivel->es_asteroide;
}

void nivel_planeta_destruir(nivel_t* nivel, estadio_t estadio) {
    lista_iter_t* iter_p = lista_iter_crear(nivel->planetas);
    while (!lista_iter_al_final(iter_p)) {
        planeta_t* planeta = lista_iter_ver_actual(iter_p);
        if (planeta_get_estadio(planeta) == estadio) {
            planeta_destruir_no_ref(lista_iter_borrar(iter_p));
            break;
        }
        lista_iter_avanzar(iter_p);
    }
    lista_iter_destruir(iter_p);
}

planeta_t* nivel_planeta_por_estadio(nivel_t* nivel, estadio_t estadio) {
    lista_iter_t* iter_p = lista_iter_crear(nivel->planetas);
    while (!lista_iter_al_final(iter_p)) {
        planeta_t* planeta = lista_iter_ver_actual(iter_p);
        if (planeta_get_estadio(planeta) == estadio) {
            lista_iter_destruir(iter_p);
            return planeta;
        }
        lista_iter_avanzar(iter_p);
    }
    lista_iter_destruir(iter_p);
}

void nivel_destruir(nivel_t* nivel, figura_t** figura) {
    if (figura != NULL) *figura = nivel->figura;
    lista_destruir(nivel->torretas, torreta_destruir_no_ref);
    lista_destruir(nivel->combustibles, combustible_destruir_no_ref);
    lista_destruir(nivel->balas, bala_destruir_no_ref);
    lista_destruir(nivel->planetas, planeta_destruir_no_ref);
    lista_destruir(nivel->reactores, reactor_destruir_no_ref);
    free(nivel);
}

//SETTERS

bool nivel_agregar_torreta(nivel_t *nivel, double posx, double posy, double ang, figura_t * fig_base, figura_t* fig_disparando) {
    return lista_insertar_ultimo(nivel->torretas, torreta_crear(posx, posy, ang, fig_base, fig_disparando));
}

bool nivel_agregar_combustible(nivel_t *nivel, double posx, double posy, double ang, figura_t * figura) {
    return lista_insertar_ultimo(nivel->combustibles, combustible_crear(posx, posy, ang, figura));
}

bool nivel_agregar_bala(nivel_t* nivel, double posx, double posy, double vel, double ang, bool jugador, figura_t* fig_bala) {
    return lista_insertar_ultimo(nivel->balas, bala_crear(posx, posy, vel, ang, nivel->duracion_balas, jugador, fig_bala));
}

bool nivel_agregar_planeta(nivel_t* nivel, double posx, double posy, double posx_tp, double posy_tp, size_t puntaje, estadio_t estad, figura_t* fig_planeta) {
    return lista_insertar_ultimo(nivel->planetas, planeta_crear(posx, posy, posx_tp, posy_tp, puntaje, estad, fig_planeta));
}

bool nivel_agregar_reactor(nivel_t* nivel, double posx, double posy, double ang, size_t tiempo, figura_t* fig_react) {
    return lista_insertar_ultimo(nivel->reactores, reactor_crear(posx, posy, ang, tiempo, fig_react));
}

void nivel_randomizar_disparos(void) {
    torreta_randomizar_disparos();
}

//GETTERS


bool nivel_es_inf(nivel_t* nivel) {
    if (nivel->figura == NULL) return false;
    return figura_es_inf(nivel->figura);
}

double nivel_get_ancho(nivel_t* nivel) {
    if (nivel->figura == NULL) return -1;
    return figura_obtener_ancho(nivel->figura);
}

double nivel_get_alto(nivel_t* nivel) {
    if (nivel->figura == NULL) return -1;
    return figura_obtener_alto(nivel->figura);
}

void nivel_get_max_min(nivel_t* nivel, double* x_max, double* y_max, double* x_min, double* y_min) {
    if (nivel->figura != NULL) {
        if (x_max != NULL) *x_max = figura_obtener_x_max(nivel->figura);
        if (y_max != NULL) *y_max = figura_obtener_y_max(nivel->figura);
        if (x_min != NULL) *x_min = figura_obtener_x_min(nivel->figura);
        if (y_min != NULL) *y_min = figura_obtener_y_min(nivel->figura);
    }
}

bool nivel_tiene_torretas(nivel_t* nivel) {
    return !lista_esta_vacia(nivel->torretas);
}

bool nivel_tiene_planetas(nivel_t* nivel) {
    return !lista_esta_vacia(nivel->planetas);
}

bool nivel_tiene_reactores(nivel_t* nivel) {
    return !lista_esta_vacia(nivel->reactores);
}

bool nivel_tiene_combustibles(nivel_t* nivel) {
    return !lista_esta_vacia(nivel->combustibles);
}

bool nivel_tiene_balas(nivel_t* nivel) {
    return !lista_esta_vacia(nivel->balas);
}

figura_t* nivel_get_figura(nivel_t* nivel) {
    return nivel->figura;
}

bool nivel_vencido(nivel_t* nivel, nave_t* nave) {
    if (!nivel_tiene_torretas(nivel) && !nivel_tiene_reactores(nivel)) {
        if (nave != NULL) nave_sumar_puntos(nave, nivel->puntaje);
        return true;
    }
    return false;
}

size_t nivel_get_conteo_reactor(nivel_t* nivel) {
    lista_iter_t* iter = lista_iter_crear(nivel->reactores);
    reactor_t* r = lista_iter_ver_actual(iter);
    size_t contador = reactor_get_contador(r);
    lista_iter_avanzar(iter);
    while (!lista_iter_al_final(iter)) {
        r = lista_iter_ver_actual(iter);
        size_t aux = reactor_get_contador(r);
        if (aux < contador) {
            contador = aux;
        }
        lista_iter_avanzar(iter);
    }
    return contador;
}

//INTERACCIONES Y ACTUALIZACIONES

void nivel_nave_salir_planeta(nave_t* nave, double posx, double posy, nivel_t* nivel, estadio_t estadio_entrada) {
    double angulo = computar_angulo(planeta_get_posx(nave), planeta_get_posy(nave), posx, posy);
    planeta_t* planeta = nivel_planeta_por_estadio(nivel, nave_get_estadio(nave));
    nave_setear_pos(nave, planeta_get_posx(planeta) + com_x(DISTANCIA_SALIR_PLANETA, angulo), planeta_get_posy(planeta) + com_y(DISTANCIA_SALIR_PLANETA, angulo));
    nave_setear_estadio(nave, estadio_entrada);
    nave_setear_vel(nave, com_x(VELOCIDAD_SALIR_PLANETA, angulo), com_y(VELOCIDAD_SALIR_PLANETA, angulo));
    nave_setear_ang_nave(nave, angulo);
}

bool nivel_nave_accede_planetas(nivel_t* nivel, nave_t* nave) {
    lista_iter_t* iter = lista_iter_crear(nivel->planetas);
    while (!lista_iter_al_final(iter)) {
        planeta_t* p = lista_iter_ver_actual(iter);
        if (planeta_distancia_a_punto(p, nave_get_posx(nave), nave_get_posy(nave)) < DISTANCIA_COLISION) {
            nave_setear_estadio(nave, planeta_get_estadio(p));
            nave_setear_pos(nave, planeta_get_posx_tp(p), planeta_get_posy_tp(p));
            return true;
            break;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return false;
}

bool nivel_nave_dispara(nivel_t* nivel, nave_t* nave, double vel, figura_t* fig_bala) {
    return lista_insertar_ultimo(nivel->balas, nave_dispara(nave, vel, nivel->duracion_balas, fig_bala));
}

bool nivel_nave_disparada(nivel_t* nivel, nave_t* nave) {
    lista_iter_t* iter = lista_iter_crear(nivel->balas);
    while (!lista_iter_al_final(iter)) {
        bala_t* b = lista_iter_ver_actual(iter);
        if (!bala_es_de_jugador(b) && nave_distancia_a_punto(nave, bala_get_posx(b), bala_get_posy(b)) < DISTANCIA_COLISION) {
            bala_destruir_no_ref(lista_iter_borrar(iter));
            lista_iter_destruir(iter);
            return true;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return false;
}

size_t nivel_nave_recoge_combustible(nivel_t* nivel, nave_t* nave) {
    size_t recogidos = 0;
    lista_iter_t* iter = lista_iter_crear(nivel->combustibles);
    while (!lista_iter_al_final(iter)) {
        bala_t* c = lista_iter_ver_actual(iter);
        if (nave_distancia_a_punto(nave, combustible_get_posx(c), combustible_get_posy(c)) < DISTANCIA_RECOLECCION) {
            combustible_destruir_no_ref(lista_iter_borrar(iter));
            recogidos++;
            continue;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return recogidos;
}

bool nivel_torretas_disparan_a_nave(nivel_t* nivel, nave_t* nave, double abanico, size_t chances, double rango, double vel, figura_t* fig_bala) {
    lista_iter_t* iter = lista_iter_crear(nivel->torretas);
    double x_nav = nave_get_posx(nave);
    double y_nav = nave_get_posy(nave);
    while (!lista_iter_al_final(iter)) {
        torreta_t* t = lista_iter_ver_actual(iter);
        double ang = computar_angulo(torreta_get_posx(t), torreta_get_posy(t), x_nav, y_nav);
        bala_t* bala = NULL;
        if(torreta_distancia_a_punto(t, x_nav, y_nav) < rango) 
            bala = torreta_dispara(t, ang, abanico, chances, vel, nivel->duracion_balas, fig_bala);
        if (bala != NULL)
            if (!lista_insertar_ultimo(nivel->balas, bala)) {
                lista_iter_destruir(iter);
                return false;
            }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return true;
}

size_t nivel_torretas_disparadas(nivel_t* nivel) {
    size_t disparadas = 0;
    lista_iter_t* iter_t = lista_iter_crear(nivel->torretas);
    while (!lista_iter_al_final(iter_t)) {
        bool torreta_destruida = false;
        torreta_t* t = lista_iter_ver_actual(iter_t);
        lista_iter_t* iter_b = lista_iter_crear(nivel->balas);
        while (!lista_iter_al_final(iter_b)) {
            bala_t* b = lista_iter_ver_actual(iter_b);
            if (bala_es_de_jugador(b) && torreta_distancia_a_punto(t, bala_get_posx(b), bala_get_posy(b)) < DISTANCIA_COLISION) {
                torreta_destruida = true;
                torreta_destruir_no_ref(lista_iter_borrar(iter_t));
                bala_destruir_no_ref(lista_iter_borrar(iter_b));
                disparadas++;
                break;
            }
            lista_iter_avanzar(iter_b);
        }
        lista_iter_destruir(iter_b);
        if (!torreta_destruida) lista_iter_avanzar(iter_t);
    } 
    lista_iter_destruir(iter_t);
    return disparadas;
}

void nivel_balas_actualizar(nivel_t* nivel, double dt) {
    lista_iter_t* iter = lista_iter_crear(nivel->balas);
    while (!lista_iter_al_final(iter)) {
        bala_t* b = lista_iter_ver_actual(iter);
        if (!bala_actualizar(b, dt)) {
            bala_destruir_no_ref(lista_iter_borrar(iter));
            continue;
        }
        if (nivel->figura != NULL && figura_distancia_a_punto(nivel->figura, bala_get_posx(b), bala_get_posy(b)) < DISTANCIA_COLISION) {
            bala_destruir_no_ref(lista_iter_borrar(iter));
            continue;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

void nivel_balas_trasladar(nivel_t* nivel, double dx, double dy) {
    lista_iter_t* iter = lista_iter_crear(nivel->balas);
    while (!lista_iter_al_final(iter)) {
        bala_t* b = lista_iter_ver_actual(iter);
        bala_set_pos(b, bala_get_posx(b) + dx, bala_get_posy(b) + dy);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

void nivel_balas_vaciar(nivel_t* nivel) {
    lista_destruir(nivel->balas, bala_destruir_no_ref);
    nivel->balas = lista_crear();
}

size_t nivel_reactores_actualizar(nivel_t* nivel) {
    size_t reactores_cero = 0;
    lista_iter_t* iter = lista_iter_crear(nivel->reactores);
    while (!lista_iter_al_final(iter)) {
        reactor_t* r = lista_iter_ver_actual(iter);
        if (!reactor_actualizar(r)) {
            reactor_reiniciar(r);
            reactores_cero++;
        }
        lista_iter_avanzar(iter);
    }
    return reactores_cero;
}

size_t nivel_reactores_disparados(nivel_t* nivel) {
    size_t disparados = 0;
    lista_iter_t* iter_r = lista_iter_crear(nivel->reactores);
    while (!lista_iter_al_final(iter_r)) {
        bool reactor_destruido = false;
        reactor_t* r = lista_iter_ver_actual(iter_r);
        lista_iter_t* iter_b = lista_iter_crear(nivel->balas);
        while (!lista_iter_al_final(iter_b)) {
            bala_t* b = lista_iter_ver_actual(iter_b);
            if (bala_es_de_jugador(b) && reactor_distancia_a_punto(r, bala_get_posx(b), bala_get_posy(b)) < DISTANCIA_COLISION) {
                reactor_destruido = true;
                reactor_destruir_no_ref(lista_iter_borrar(iter_r));
                bala_destruir_no_ref(lista_iter_borrar(iter_b));
                disparados++;
                break;
            }
            lista_iter_avanzar(iter_b);
        }
        lista_iter_destruir(iter_b);
        if (!reactor_destruido) lista_iter_avanzar(iter_r);
    }
    lista_iter_destruir(iter_r);
    return disparados;
}



//DIBUJO

void nivel_dibujar(nivel_t* nivel, double centro, double escala, double ventana_ancho, SDL_Renderer* renderer) {
    double traslado = -centro;
    double ancho = 0;
    if (nivel->figura != NULL) {
        ancho = figura_obtener_ancho(nivel->figura);
        if (nivel_es_inf(nivel)) {
            traslado = -centro + ventana_ancho / 2;
            figura_dibujar(nivel->figura, traslado, 0, 0, centro, escala, renderer);
            figura_dibujar(nivel->figura, -ancho * escala + traslado, 0, 0, centro, escala, renderer);
            figura_dibujar(nivel->figura, ancho * escala + traslado, 0, 0, centro, escala, renderer);
        }
        else {
            figura_dibujar(nivel->figura, traslado, 0, 0, centro, escala, renderer);
        }
    }
    lista_iter_t* iter_b = lista_iter_crear(nivel->balas);
    while (!lista_iter_al_final(iter_b)) {
        bala_dibujar(lista_iter_ver_actual(iter_b), traslado, 0, centro, escala, renderer);
        lista_iter_avanzar(iter_b);
    }
    lista_iter_t* iter_t = lista_iter_crear(nivel->torretas);
    while (!lista_iter_al_final(iter_t)) {
        torreta_dibujar(lista_iter_ver_actual(iter_t), traslado, 0, centro, escala, renderer);
        lista_iter_avanzar(iter_t);
    }
    lista_iter_t* iter_p = lista_iter_crear(nivel->planetas);
    while (!lista_iter_al_final(iter_p)) {
        planeta_dibujar(lista_iter_ver_actual(iter_p), traslado, 0, centro, escala, renderer);
        lista_iter_avanzar(iter_p);
    }
    lista_iter_t* iter_c = lista_iter_crear(nivel->combustibles);
    while (!lista_iter_al_final(iter_c)) {
        combustible_dibujar(lista_iter_ver_actual(iter_c), traslado, 0, centro, escala, renderer);
        lista_iter_avanzar(iter_c);
    }
    lista_iter_t* iter_r = lista_iter_crear(nivel->reactores);
    while (!lista_iter_al_final(iter_r)) {
        reactor_dibujar(lista_iter_ver_actual(iter_r), traslado, 0, centro, escala, renderer);
        lista_iter_avanzar(iter_r);
    }
    
    
    lista_iter_destruir(iter_b);
    lista_iter_destruir(iter_t);
    lista_iter_destruir(iter_p);
    lista_iter_destruir(iter_r);
    lista_iter_destruir(iter_c);
}



