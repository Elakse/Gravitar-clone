#include "nivel.h"
#include "lista.h"
#include "figuras.h"
#include "nave.h"
#include "config.h"
#include "fisica.h"

struct nivel {
	lista_t *figuras;
	nivel_enum_t nivel_enum;
};

nivel_t* nivel_crear(nivel_enum_t nivel_enum) {
	nivel_t* nivel = malloc(sizeof(nivel_t));
	if (nivel == NULL) return NULL;
	nivel->nivel_enum = nivel_enum;
	nivel->figuras = lista_crear();
	return nivel;
}

void nivel_tickear(nivel_t *nivel, nave_t *nave, double escala, double centro, SDL_Renderer *renderer) {
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

                if (nave_get_posy(nave) <= 0)
                    nave_setear_vely(nave, nave_get_vely(nave) * -1);
                if (nave_get_posx(nave) <= 0 || nave_get_posx(nave) >= VENTANA_ANCHO * 0.99)
                    nave_setear_velx(nave, nave_get_velx(nave) * -1);
                break;
            }
        case NIVEL2:{
                if (nave_get_posy(nave) >= VENTANA_ALTO) {
                    nave_setear_nivel(nave, INICIO);
                    nave_setear_ang_nave(nave, PI);
                    nave_setear_vel(nave, -10, 0);
                    nave_setear_pos(nave, 645, 145);
                }

                if (nave_get_posy(nave) <= 0)
                    nave_setear_vely(nave, nave_get_vely(nave) * -1);
                if (nave_get_posx(nave) <= 0 || nave_get_posx(nave) >= VENTANA_ANCHO * 0.99)
                    nave_setear_velx(nave, nave_get_velx(nave) * -1);
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

                if (nave_get_posy(nave) <= 0)
                    nave_setear_vely(nave, nave_get_vely(nave) * -1);
                if (nave_get_posx(nave) <= 0 || nave_get_posx(nave) >= VENTANA_ANCHO * 0.99)
                    nave_setear_velx(nave, nave_get_velx(nave) * -1);
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

                /*figura_t* nivel = figura_buscar_nombre(figuras, "NIVEL1R");
                polilinea_t** polis = figura_obtener_polis(nivel);
                polilinea_t *poli2 = polilinea_clonar(polis[0]);
                polilinea_escalar(poli2, 0.65);
                polilinea_trasladar(poli2, 25, 20);
                if (distancia_punto_a_polilinea(poli2, nave_get_posx(jugador), nave_get_posy(jugador)) < 5) {
                    nave_setear_ang_nave(jugador, PI/4);
                    nave_setear_vel(jugador, 0, 0);
                    nave_setear_nivel(jugador, INICIO);
                    nave_setear_pos(jugador, 388, 218);
                    nave_restar_vida(jugador);
                    if (nave_get_vidas(jugador) == 0) break;
                }*/
                break;
            }
    }
    nivel_dibujar(nivel, escala, centro, renderer);
}

void nivel_dibujar(nivel_t* nivel, double escala, double centro, SDL_Renderer* renderer) {
    if (lista_esta_vacia(nivel->figuras)) return NULL;

    lista_iter_t* iter = lista_iter_crear(nivel->figuras);
    do {
        figura_render_t* figura_render = lista_iter_ver_actual(iter);
        figura_render_dibujar(figura_render, escala, centro, renderer);
        lista_iter_avanzar(iter);
    } while (!lista_iter_al_final(iter));
    lista_iter_destruir(iter);
    return NULL;
}

bool nivel_insertar_figura(nivel_t* nivel, figura_t* figura, double posx, double posy, double ang, double escala) {
    figura_render_t* figura_render = figura_render_crear(figura, posx, posy, ang, escala);
    if (figura_render == NULL) return false;
    return lista_insertar_ultimo(nivel->figuras, figura_render);
}

void nivel_destruir(nivel_t* nivel) {
	lista_destruir(nivel->figuras, figura_render_destruir);
	free(nivel);
}