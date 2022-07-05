#include "nivel.h"
#include "lista.h"
#include "figuras.h"
#include "torreta.h"
#include "combustible.h"
#include "nave.h"
#include "config.h"
#include "fisica.h"
#include "bala.h"
#include "reactor.h"
#include <stdbool.h>

struct nivel {
    lista_t* torretas;
    lista_t* combustibles;
    lista_t* balas;
    lista_t* planetas;
    lista_t* reactores;
    figura_t* figura;
    size_t duracion_balas;
};

nivel_t* nivel_crear(figura_t *figura, size_t duracion_de_balas) {
    nivel_t* nivel = malloc(sizeof(nivel_t));
    if (nivel == NULL) return NULL;
    nivel->torretas = lista_crear();
    nivel->combustibles = lista_crear();
    nivel->balas = lista_crear();
    nivel->planetas = lista_crear();
    nivel->reactores = lista_crear();
    nivel->figura = figura;
    nivel->duracion_balas = duracion_de_balas;
	return nivel;
}

bool nivel_agregar_torreta(nivel_t *nivel, double posx, double posy, double ang, figura_t * fig_base, figura_t* fig_disparando) {
    return lista_insertar_ultimo(nivel->torretas, torreta_crear(posx, posy, ang, fig_base, fig_disparando));
}

bool nivel_agregar_combustible(nivel_t *nivel, double posx, double posy, double ang, figura_t * figura) {
    return lista_insertar_ultimo(nivel->combustibles, combustible_crear(posx, posy, ang, figura));
}

bool nivel_agregar_bala(nivel_t* nivel, double posx, double posy, double vel, double ang, bool jugador, figura_t* fig_bala) {
    return lista_insertar_ultimo(nivel->balas, bala_crear(posx, posy, vel, ang, nivel->duracion_balas, jugador, fig_bala));
}

bool nivel_agregar_planeta(nivel_t* nivel, double posx, double posy, double posx_tp, double posy_tp, enum estadio estad, figura_t* fig_planeta) {
    return lista_insertar_ultimo(nivel->balas, planeta_crear(posx, posy, posx_tp, posy_tp, estad, fig_planeta));
}

bool nivel_agregar_reactor(nivel_t* nivel, double posx, double posy, double ang, size_t tiempo, figura_t* fig_react) {
    return lista_insertar_ultimo(nivel->reactores, reactor_crear(posx, posy, ang, tiempo, fig_react));
}

bool nivel_nave_dispara(nivel_t* nivel, struct nave* nave, double vel, figura_t* fig_bala) {
    return lista_insertar_ultimo(nivel->balas, nave_dispara(nave, vel, nivel->duracion_balas, fig_bala));
}

bool nivel_torretas_disparan_a_nave(nivel_t* nivel, struct nave* nave, double rango, size_t chances, double vel, figura_t* fig_bala) {
    lista_iter_t* iter = lista_iter_crear(nivel->torretas);
    while (!lista_iter_al_final(iter)) {
        torreta_t* t = lista_iter_ver_actual(iter);
        double ang = computar_angulo(torreta_get_posx(t), torreta_get_posy(t), nave_get_posx(nave), nave_get_posy(nave));
        bala_t* bala = torreta_dispara(t, ang, rango, chances, vel, nivel->duracion_balas, fig_bala);
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

bool nivel_nave_disparada(nivel_t* nivel, struct nave* nave) {
    lista_iter_t* iter = lista_iter_crear(nivel->balas);
    while (!lista_iter_al_final(iter)) {
        bala_t* b = lista_iter_ver_actual(iter);
        if (!bala_es_de_jugador(b) && nave_distancia_a_punto(nave, bala_get_posx(b), bala_get_posy(b)) < DISTANCIA_COLISION) {
            bala_destruir(lista_iter_borrar(iter), NULL);
            lista_iter_destruir(iter);
            return true;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return false;
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
                torreta_destruir(lista_iter_borrar(iter_t), NULL, NULL);
                bala_destruir(lista_iter_borrar(iter_b), NULL);
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
            bala_destruir(lista_iter_borrar(iter), NULL);
            continue;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

void nivel_dibujar(nivel_t* nivel, double centro, double escala, double ventana_ancho, SDL_Renderer* renderer) {
    lista_iter_t* iter_b = lista_iter_crear(nivel->balas);
    while (!lista_iter_al_final(iter_b)) {
        bala_dibujar(lista_iter_ver_actual(iter_b), -centro + ventana_ancho / 2, 0, centro, escala, renderer);
        lista_iter_avanzar(iter_b);
    }
    lista_iter_t* iter_t = lista_iter_crear(nivel->torretas);
    while (!lista_iter_al_final(iter_t)) {
        torreta_dibujar(lista_iter_ver_actual(iter_t), -centro + ventana_ancho / 2, 0, centro, escala, renderer);
        lista_iter_avanzar(iter_t);
    }
    double ancho = figura_obtener_ancho(nivel->figura);
    figura_dibujar(nivel->figura, -centro + ventana_ancho / 2, 0, 0, centro, escala, renderer);
    figura_dibujar(nivel->figura, -ancho * escala - centro + ventana_ancho / 2, 0, 0, centro, escala, renderer);
    figura_dibujar(nivel->figura, ancho * escala - centro + ventana_ancho / 2, 0, 0, centro, escala, renderer);
    lista_iter_destruir(iter_b);
    lista_iter_destruir(iter_t);
}







/*void nivel_tickear(nivel_t* nivel, nave_t* nave, double escala, double centro, SDL_Renderer* renderer) {
    switch (nivel->nivel_enum) {
        case INICIO:{
            if (nave_get_posy(nave) <= 5 || nave_get_posy(nave) >= VENTANA_ALTO)
                nave_setear_vely(nave, nave_get_vely(nave) * -1);
            if (nave_get_posx(nave) <= 5 || nave_get_posx(nave) >= VENTANA_ANCHO)
                nave_setear_velx(nave, nave_get_velx(nave) * -1);

            nave_setear_ang_g(nave, computar_angulo(nave_get_posx(nave), nave_get_posy(nave), 457, 364));

            if (computar_distancia(nave_get_posx(nave), nave_get_posy(nave), 663, 473) < 20) {
                nave_setear_nivel(nave, NIVEL1);
                nave_setear_pos(nave, 300, 590);
                nave_setear_vel(nave, 0, -20);
                nave_setear_ang_nave(nave, PI * 1.5);
                nave_setear_ang_g(nave, PI * 1.5);
            }
            if (computar_distancia(nave_get_posx(nave), nave_get_posy(nave), 671, 145) < 20) {
                nave_setear_nivel(nave, NIVEL2);
                nave_setear_pos(nave, 400, 590);
                nave_setear_vel(nave, 0, -20);
                nave_setear_ang_nave(nave, PI * 1.5);
                nave_setear_ang_g(nave, PI * 1.5);
            }
            if (computar_distancia(nave_get_posx(nave), nave_get_posy(nave), 110, 79) < 20) {
                nave_setear_nivel(nave, NIVEL3);
                nave_setear_pos(nave, 400, 590);
                nave_setear_vel(nave, 0, -20);;
                nave_setear_ang_nave(nave, PI * 1.5);
                nave_setear_ang_g(nave, PI * 1.5);
            }
            if (computar_distancia(nave_get_posx(nave), nave_get_posy(nave), 204, 455) < 20) {
                nave_setear_nivel(nave, NIVEL4);
                nave_setear_pos(nave, 400, 590);
                nave_setear_vel(nave, 0, -20);
                nave_setear_ang_nave(nave, PI * 1.5);
                nave_setear_ang_g(nave, PI * 1.5);
            }
            if (computar_distancia(nave_get_posx(nave), nave_get_posy(nave), 111, 307) < 20) {
                nave_setear_nivel(nave, NIVEL5);
                nave_setear_pos(nave, 300, 590);
                nave_setear_vel(nave, 0, -20);
                nave_setear_ang_nave(nave, PI * 1.5);
                nave_setear_ang_g(nave, PI * 1.5);
            }
            if (computar_distancia(nave_get_posx(nave), nave_get_posy(nave), 457, 364) < 20) {
                nave_setear_pos(nave, 388, 218);
                nave_setear_vel(nave, 0, 0);
                nave_setear_ang_nave(nave, PI / 4);
                nave_restar_vida(nave);
            }
            break;
        }
        case NIVEL1:{
                if (nave_get_posy(nave) >= VENTANA_ALTO) {
                    nave_setear_nivel(nave, INICIO);
                    nave_setear_pos(nave, 645, 455);
                    nave_setear_vel(nave, -10, -10);
                    nave_setear_ang_nave(nave, PI + PI / 4);
                }

                if (nave_get_posy(nave) > VENTANA_ALTO * MARGEN_ALTURA)
                    escala = VENTANA_ALTO * MARGEN_ALTURA / nave_get_posy(nave);
                if (escala < ESCALA_MINIMA)
                    escala = ESCALA_MINIMA;
                if ((nave_get_posx(nave) - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = nave_get_posx(nave) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
                else if ((nave_get_posx(nave) - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = nave_get_posx(nave) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

                break;
            }
        case NIVEL2:{
                if (nave_get_posy(nave) >= VENTANA_ALTO) {
                    nave_setear_nivel(nave, INICIO);
                    nave_setear_ang_nave(nave, PI);
                    nave_setear_vel(nave, -10, 0);
                    nave_setear_pos(nave, 645, 145);
                }
                
                if (nave_get_posy(nave) > VENTANA_ALTO * MARGEN_ALTURA)
                    escala = VENTANA_ALTO * MARGEN_ALTURA / nave_get_posy(nave);
                if (escala < ESCALA_MINIMA)
                    escala = ESCALA_MINIMA;
                if ((nave_get_posx(nave) - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = nave_get_posx(nave) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
                else if ((nave_get_posx(nave) - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = nave_get_posx(nave) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

                break;
            }
        case NIVEL3:{
                if (nave_get_posy(nave) >= VENTANA_ALTO) {
                    nave_setear_nivel(nave, INICIO);
                    nave_setear_pos(nave, 130, 95);
                    nave_setear_vel(nave, 10, 10);
                    nave_setear_ang_nave(nave, PI / 4);
                }

                if (nave_get_posy(nave) > VENTANA_ALTO * MARGEN_ALTURA)
                    escala = VENTANA_ALTO * MARGEN_ALTURA / nave_get_posy(nave);
                if (escala < ESCALA_MINIMA)
                    escala = ESCALA_MINIMA;

                if ((nave_get_posx(nave) - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = nave_get_posx(nave) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
                else if ((nave_get_posx(nave) - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = nave_get_posx(nave) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

                break;
            }
        case NIVEL4:{
                if (nave_get_posy(nave) >= VENTANA_ALTO) {
                    nave_setear_nivel(nave, INICIO);
                    nave_setear_pos(nave, 204, 435);
                    nave_setear_vel(nave, 0, -10);
                    nave_setear_ang_nave(nave, PI * 1.5);
                }

                if (nave_get_posy(nave) > VENTANA_ALTO * MARGEN_ALTURA)
                    escala = VENTANA_ALTO * MARGEN_ALTURA / nave_get_posy(nave);
                if (escala < ESCALA_MINIMA)
                    escala = ESCALA_MINIMA;
                if ((nave_get_posx(nave) - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = nave_get_posx(nave) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
                else if ((nave_get_posx(nave) - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = nave_get_posx(nave) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

                break;
            }
        case NIVEL5:{
                if (nave_get_posy(nave) >= VENTANA_ALTO) {
                    nave_setear_nivel(nave, INICIO);
                    nave_setear_ang_nave(nave, PI * 2);
                    nave_setear_vel(nave, 10, 0);
                    nave_setear_pos(nave, 150, 307);
                }
                if (nave_get_posy(nave) <= 0)
                    nave_setear_vely(nave, nave_get_vely(nave) * -1);
                if (nave_get_posx(nave) <= 0 || nave_get_posx(nave) >= VENTANA_ANCHO * 0.99)
                    nave_setear_velx(nave, nave_get_velx(nave) * -1);

                if (nave_get_posy(nave) > VENTANA_ALTO * MARGEN_ALTURA)
                    escala = VENTANA_ALTO * MARGEN_ALTURA / nave_get_posy(nave);
                if (escala < ESCALA_MINIMA)
                    escala = ESCALA_MINIMA;
                if ((nave_get_posx(nave) - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = nave_get_posx(nave) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
                else if ((nave_get_posx(nave) - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = nave_get_posx(nave) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

                break;
            }
    }
    //Fijate que aca abajo si pones escala en 1 y centro en 0 (osea todo fijo), se dibuja todo bien alineado en casi todos los niveles menos el que es tipo un asteroide.
    nivel_dibujar(nivel, escala, 0, renderer); //El 0 ese tendria que ser "centro" pero lo pongo asi pq no anda y asi no me mueve nada
}*/

/*void nivel_dibujar(nivel_t* nivel, double escala, double centro, SDL_Renderer* renderer) {
    if (lista_esta_vacia(nivel->figuras)) return;

    lista_iter_t* iter = lista_iter_crear(nivel->figuras);
    do {
        figura_render_t* figura_render = lista_iter_ver_actual(iter);
        figura_render_dibujar(figura_render, escala, centro, renderer);
        lista_iter_avanzar(iter);
    } while (!lista_iter_al_final(iter));
    lista_iter_destruir(iter);
    return;
}*/

/*void nivel_dibujar(nivel_t* nivel, double escala, double centro, SDL_Renderer* renderer) {
    if (!lista_esta_vacia(nivel->torretas)) {
        lista_iter_t* iter = lista_iter_crear(nivel->torretas);
        do {
            torreta_t* torreta = lista_iter_ver_actual(iter);
            torreta_dibujar(torreta, escala, centro, renderer);
            lista_iter_avanzar(iter);
        } while (!lista_iter_al_final(iter));
        lista_iter_destruir(iter);
    }

    if (!lista_esta_vacia(nivel->combustibles)) {
        lista_iter_t* iter = lista_iter_crear(nivel->torretas);
        do {
            torreta_t* torreta = lista_iter_ver_actual(iter);
            torreta_dibujar(torreta, renderer);
            lista_iter_avanzar(iter);
        } while (!lista_iter_al_final(iter));
        lista_iter_destruir(iter);
    }
}*/

void nivel_destruir(nivel_t* nivel) {
	lista_destruir(nivel->torretas, torreta_destruir);
    lista_destruir(nivel->combustibles, combustible_destruir);
    lista_destruir(nivel->balas, bala_destruir);
	free(nivel);
}