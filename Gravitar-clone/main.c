#include <SDL.h>
#include <stdbool.h>

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

    //lista_t* balas = lista_crear();
    bala_t* bala = NULL;

    FILE* f = fopen("figuras.bin", "rb");
    lista_t* figuras = lista_crear();
    figura_t* figura = figura_leer(f);
    while (figura != NULL) {
        lista_insertar_ultimo(figuras, figura);
        figura = figura_leer(f);
    }


    figura_t* nave = figura_buscar_nombre(figuras, "NAVE");
    figura_t* nave_chorro = figura_buscar_nombre(figuras, "NAVE+CHORRO");
    /*figura_t* nave_chorro = figura_leer(f);
    figura_t* f3 = figura_leer(f);
    figura_t* f4 = figura_leer(f);
    figura_t* f5 = figura_leer(f);
    figura_t* f6 = figura_leer(f);
    figura_t* f7 = figura_leer(f);
    figura_t* f8 = figura_leer(f);
    figura_t* f9 = figura_leer(f);
    figura_t* f10 = figura_leer(f);
    figura_t* f11 = figura_leer(f);
    figura_t* f12 = figura_leer(f);
    figura_t* nivel = figura_leer(f);
    figura_t* f14 = figura_leer(f);
    figura_t* f15 = figura_leer(f);*/
    polilinea_t** polis_nave = figura_obtener_polis(nave);
    polilinea_t** polis_nave_chorro = figura_obtener_polis(nave_chorro);
    //polilinea_t** polis_nivel = figura_obtener_polis(nivel);

    //const float bala_a[2][2] = {{0, 0}, {2, 0}};
    const float bala_a[5][2] = { {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {-1, -1} };
    polilinea_t* poli_bala = polilinea_crear(bala_a, 5, color_crear(1, 0, 0));

    nave_t *jugador = nave_crear(3, 1000, INICIO, "Nave");
    if(jugador == NULL) return 1;
    nave_setear_pos(jugador, VENTANA_ANCHO/2, VENTANA_ALTO/2);
    nave_setear_ang_nave(jugador, NAVE_ANGULO_INICIAL);
    nave_setear_ang_g(jugador, 3*PI/2);

    bool chorro_prendido = false;
    bool gira_der = false;
    bool gira_izq = false;
    bool dispara = false;

    // Queremos que todo se dibuje escalado por f:
    //float f = 10;
    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch(event.key.keysym.sym) {
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
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
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

        if(gira_der && !gira_izq)
            nave_girar_der(jugador, NAVE_ROTACION_PASO);
        if(!gira_der && gira_izq)
            nave_girar_izq(jugador, NAVE_ROTACION_PASO);

        if (nave_get_posy(jugador) <= 5 || nave_get_posy(jugador) >= VENTANA_ALTO)
            nave_setear_vely(jugador, nave_get_vely(jugador) * -1);

        if (nave_get_posx(jugador) <= 5 || nave_get_posx(jugador) >= VENTANA_ANCHO)
            nave_setear_velx(jugador, nave_get_velx(jugador) * -1);

        //if (distancia_punto_a_polilinea(polis_nivel[0], nave_get_posx(jugador), nave_get_posy(jugador)) < 5)

        nave_mover(jugador, 1.0/JUEGO_FPS);

        if (dispara) {
            bala = bala_crear(jugador);
        }

        // Dibujamos la nave escalada por f en el centro de la pantalla:

        /*SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
        polilinea_dibujar(polis_nivel[0], 0, 0, 0, renderer);*/

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
        polilinea_dibujar(polis_nave_chorro[0], nave_get_posx(jugador), nave_get_posy(jugador), nave_get_ang(jugador), renderer);

        if (chorro_prendido) {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
            polilinea_dibujar(polis_nave_chorro[1], nave_get_posx(jugador), nave_get_posy(jugador), nave_get_ang(jugador), renderer);
        }

        if (bala != NULL) {
            /*if (distancia_punto_a_polilinea(polis_nivel[0], nave_get_posx(bala), nave_get_posy(bala)) < 5) {
                bala_destruir(bala);
                bala = NULL;
            }
            else {*/
                bala_mover(bala, 1.0 / JUEGO_FPS);
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
                polilinea_dibujar(poli_bala, bala_get_posx(bala), bala_get_posy(bala), bala_get_ang(bala), renderer);
            //}
        }

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
    polilinea_destruir(polis_nave[0]);
    polilinea_destruir(polis_nave_chorro[1]);
    free(jugador);
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
