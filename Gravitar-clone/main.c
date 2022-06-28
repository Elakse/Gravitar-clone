#include <SDL.h>
#include <stdbool.h>
#include <string.h>

#include "config.h"
#include "nave.h"
#include "bala.h"
#include "polilinea.h"
#include "figuras.h"
#include "fisica.h"
#include "lista.h"

figura_t* figura_buscar_nombre(lista_t *figuras, char* nombre) {
    if (lista_esta_vacia(figuras)) return NULL;

    lista_iter_t *iter = lista_iter_crear(figuras);
    do {
        figura_t* figura = lista_iter_ver_actual(iter);
        if (!strcmp(figura_obtener_nombre(figura), nombre)) {
            free(iter);
            return figura;
        }
    } while (lista_iter_avanzar(iter));
    free(iter);
    return NULL;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    //SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    int dormir = 0;

    // BEGIN código del alumno
    // Mi nave:

    lista_t* balas = lista_crear();
    //bala_t* bala = NULL;

    FILE* f = fopen("figuras.bin", "rb");
    lista_t* figuras = lista_crear();
    figura_t* figura = figura_leer(f);
    while (figura != NULL) {
        lista_insertar_ultimo(figuras, figura);
        figura = figura_leer(f);
    }

    //const float bala_a[2][2] = {{0, 0}, {2, 0}};
    const float bala_a[5][2] = { {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {-1, -1} };
    polilinea_t* poli_bala = polilinea_crear(bala_a, 5, color_crear(1, 0, 0));

    nave_t *jugador = nave_crear(3, 1000, INICIO, "NAVE");
    if(jugador == NULL) return 1;
    nave_setear_pos(jugador, 388, 218);
    nave_setear_ang_nave(jugador, NAVE_ANGULO_INICIAL);
    nave_setear_ang_g(jugador, 3*PI/2);

    bool chorro_prendido = false;
    bool gira_der = false;
    bool gira_izq = false;
    bool dispara = false;
    bool escudo = false;

    // Queremos que todo se dibuje escalado por f:
    //float f = 10;
    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    // Prendemos el chorro:
                    chorro_prendido = true;
                    break;
                case SDLK_s:
                case SDLK_d:
                    gira_der = true;
                    break;
                case SDLK_a:
                    gira_izq = true;
                    break;
                case SDLK_SPACE:
                    dispara = true;
                    break;
                case SDLK_LSHIFT:
                    escudo = true;
                    break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    // Apagamos el chorro:
                    chorro_prendido = false;
                    break;
                case SDLK_s:
                case SDLK_d:
                    gira_der = false;
                    break;
                case SDLK_a:
                    gira_izq = false;
                    break;
                case SDLK_SPACE:
                    dispara = false;
                    break;
                case SDLK_LSHIFT:
                    escudo = false;
                    break;
                }
            }
            //END códigod el alumno
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        // BEGIN código del alumno

        if (chorro_prendido)
            nave_setear_a_thrust(jugador, NAVE_ACELERACION);
        else nave_setear_a_thrust(jugador, 0);

        if (gira_der && !gira_izq)
            nave_girar_der(jugador, NAVE_ROTACION_PASO);
        if (!gira_der && gira_izq)
            nave_girar_izq(jugador, NAVE_ROTACION_PASO);

        if (nave_get_posy(jugador) <= 5 || nave_get_posy(jugador) >= VENTANA_ALTO)
            nave_setear_vely(jugador, nave_get_vely(jugador) * -1);

        if (nave_get_posx(jugador) <= 5 || nave_get_posx(jugador) >= VENTANA_ANCHO)
            nave_setear_velx(jugador, nave_get_velx(jugador) * -1);

        if (nave_get_nivel(jugador) == INICIO) {
            nave_setear_ang_g(jugador, computar_angulo(nave_get_posx(jugador), nave_get_posy(jugador), 457, 364));
        }

        nave_mover(jugador, 1.0/JUEGO_FPS);

        if (dispara) {
            lista_insertar_ultimo(balas, bala_crear(jugador));
        }

        // Dibujamos la nave escalada por f en el centro de la pantalla:
        if (nave_get_nivel(jugador) == INICIO) {
            figura_dibujar(figura_buscar_nombre(figuras, "BASE"), 388, 218, 0, 1, renderer);
            figura_dibujar(figura_buscar_nombre(figuras, "ESTRELLA"), 457, 364, 0, 1, renderer);
            figura_dibujar(figura_buscar_nombre(figuras, "PLANETA1"), 663, 473, 0, 1, renderer);
            figura_dibujar(figura_buscar_nombre(figuras, "PLANETA2"), 671, 145, 0, 1, renderer);
            figura_dibujar(figura_buscar_nombre(figuras, "PLANETA3"), 110, 79, 0, 1, renderer);
            figura_dibujar(figura_buscar_nombre(figuras, "PLANETA4"), 204, 455, 0, 1, renderer);
            figura_dibujar(figura_buscar_nombre(figuras, "PLANETA5"), 111, 307, 0, 1, renderer);

            if (computar_distancia(nave_get_posx(jugador), nave_get_posy(jugador), 663, 473) < 20) {
                nave_setear_nivel(jugador, NIVEL1);
                nave_setear_pos(jugador, 300, 590);
                nave_setear_vel(jugador, 0, -20);
                nave_setear_ang_nave(jugador, PI * 1.5);
                nave_setear_ang_g(jugador, PI * 1.5);
            }
            if (computar_distancia(nave_get_posx(jugador), nave_get_posy(jugador), 671, 145) < 20) {
                nave_setear_nivel(jugador, NIVEL2);
                nave_setear_pos(jugador, 400, 590);
                nave_setear_vel(jugador, 0, -20);
                nave_setear_ang_nave(jugador, PI * 1.5);
                nave_setear_ang_g(jugador, PI * 1.5);
            }
            if (computar_distancia(nave_get_posx(jugador), nave_get_posy(jugador), 110, 79) < 20) {
                nave_setear_nivel(jugador, NIVEL3);
                nave_setear_pos(jugador, 400, 590);
                nave_setear_vel(jugador, 0, -20);;
                nave_setear_ang_nave(jugador, PI * 1.5);
                nave_setear_ang_g(jugador, PI * 1.5);
            }
            if (computar_distancia(nave_get_posx(jugador), nave_get_posy(jugador), 204, 455) < 20) {
                nave_setear_nivel(jugador, NIVEL4);
                nave_setear_pos(jugador, 400, 590);
                nave_setear_vel(jugador, 0, -20);
                nave_setear_ang_nave(jugador, PI * 1.5);
                nave_setear_ang_g(jugador, PI * 1.5);
            }
            if (computar_distancia(nave_get_posx(jugador), nave_get_posy(jugador), 111, 307) < 20) {
                nave_setear_nivel(jugador, NIVEL5);
                nave_setear_pos(jugador, 300, 590);
                nave_setear_vel(jugador, 0, -20);
                nave_setear_ang_nave(jugador, PI * 1.5);
                nave_setear_ang_g(jugador, PI * 1.5);
            }
        }

        //Entra en Nivel de reactor
        if (nave_get_nivel(jugador) == NIVEL5){
            if (nave_get_posy(jugador) >= VENTANA_ALTO) {
                nave_setear_nivel(jugador, INICIO);
                nave_setear_ang_nave(jugador, PI * 2);
                nave_setear_vel(jugador, 10, 0);
                nave_setear_pos(jugador, 150, 307);
            }
            if (nave_get_posy(jugador) <= 0)
                nave_setear_vely(jugador, nave_get_vely(jugador) * -1);
            if (nave_get_posx(jugador) <= 0 || nave_get_posx(jugador) >= VENTANA_ANCHO * 0.99)
                nave_setear_velx(jugador, nave_get_velx(jugador) * -1);

            figura_dibujar(figura_buscar_nombre(figuras, "NIVEL1R"), 25, 20, 0, 0.65, renderer);
            figura_dibujar(figura_buscar_nombre(figuras, "REACTOR"), 0, 0, 0, 0.65, renderer);
        }

        if (nave_get_nivel(jugador) == NIVEL2) {
            if (nave_get_posy(jugador) >= VENTANA_ALTO) {
                nave_setear_nivel(jugador, INICIO);
                nave_setear_ang_nave(jugador, PI);
                nave_setear_vel(jugador, -10, 0);
                nave_setear_pos(jugador, 645, 145);
            }

            if (nave_get_posy(jugador) <= 0)
                nave_setear_vely(jugador, nave_get_vely(jugador) * -1);
            if (nave_get_posx(jugador) <= 0 || nave_get_posx(jugador) >= VENTANA_ANCHO * 0.99)
                nave_setear_velx(jugador, nave_get_velx(jugador) * -1);

            figura_dibujar(figura_buscar_nombre(figuras, "NIVEL1SE"), 0, 0,  0, 1, renderer);
        }

        if (nave_get_nivel(jugador) == NIVEL1) {
            if (nave_get_posy(jugador) >= VENTANA_ALTO) {
                nave_setear_nivel(jugador, INICIO);
                nave_setear_pos(jugador, 645, 455);
                nave_setear_vel(jugador, -10, -10);
                nave_setear_ang_nave(jugador, PI + PI / 4);
            }

            if (nave_get_posy(jugador) <= 0)
                nave_setear_vely(jugador, nave_get_vely(jugador) * -1);
            if (nave_get_posx(jugador) <= 0 || nave_get_posx(jugador) >= VENTANA_ANCHO * 0.99)
                nave_setear_velx(jugador, nave_get_velx(jugador) * -1);

            figura_dibujar(figura_buscar_nombre(figuras, "NIVEL1NE"), 0, 0, 0, 1, renderer);
        }

        if (nave_get_nivel(jugador) == NIVEL3) {
            if (nave_get_posy(jugador) >= VENTANA_ALTO) {
                nave_setear_nivel(jugador, INICIO);
                nave_setear_pos(jugador, 130, 95);
                nave_setear_vel(jugador, 10, 10);
                nave_setear_ang_nave(jugador, PI / 4);
            }

            if (nave_get_posy(jugador) <= 0)
                nave_setear_vely(jugador, nave_get_vely(jugador) * -1);
            if (nave_get_posx(jugador) <= 0 || nave_get_posx(jugador) >= VENTANA_ANCHO * 0.99)
                nave_setear_velx(jugador, nave_get_velx(jugador) * -1);

            figura_dibujar(figura_buscar_nombre(figuras, "NIVEL1SW"), 0, 0, 0, 1, renderer);
        }

        if (nave_get_nivel(jugador) == NIVEL4) {
            if (nave_get_posy(jugador) >= VENTANA_ALTO) {
                nave_setear_nivel(jugador, INICIO);
                nave_setear_pos(jugador, 204, 435);
                nave_setear_vel(jugador, 0, -10);
                nave_setear_ang_nave(jugador, PI * 1.5);
            }

            if (nave_get_posy(jugador) <= 0)
                nave_setear_vely(jugador, nave_get_vely(jugador) * -1);
            if (nave_get_posx(jugador) <= 0 || nave_get_posx(jugador) >= VENTANA_ANCHO * 0.99)
                nave_setear_velx(jugador, nave_get_velx(jugador) * -1);

            figura_dibujar(figura_buscar_nombre(figuras, "NIVEL1NW"), 0, 0, 0, 1, renderer);
        }

         
        if (escudo) figura_dibujar(figura_buscar_nombre(figuras, "ESCUDO2"), nave_get_posx(jugador), nave_get_posy(jugador), nave_get_ang(jugador) + PI/2, 1, renderer);
        if (chorro_prendido) nave_cambiar_nombre_fig(jugador, "NAVE+CHORRO");
        else nave_cambiar_nombre_fig(jugador, "NAVE");
        figura_t* nave_fig_a_dibujar = figura_buscar_nombre(figuras, nave_get_nombre_fig(jugador));

        figura_dibujar(nave_fig_a_dibujar, nave_get_posx(jugador), nave_get_posy(jugador), nave_get_ang(jugador), 1, renderer);

        balas_mover(balas);

        // END código del alumno

        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);
        ticks = SDL_GetTicks();
        
    }

    // BEGIN código del alumno
    //polilinea_destruir(polis_nave[0]);
    //polilinea_destruir(polis_nave_chorro[1]);
    lista_destruir(figuras, figura_destruir);
    nave_destruir(jugador);
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
