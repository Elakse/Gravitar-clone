#include <SDL.h>
#include <stdbool.h>

#include "config.h"
#include "nave.h"
#include "polilinea.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    int dormir = 0;

    // BEGIN código del alumno
    // Mi nave:
    const float nave[][2] = {{8, 0}, {-1, 6}, {-4, 4}, {-4, 2}, {-2, 0}, {-4, -2}, {-4, -4}, {-1, -6}, {8, 0}};
    size_t nave_tam = 9;
    polilinea_t *poli = polilinea_crear(nave, nave_tam, color_crear(0,0,1));
    nave_t *jugador = nave_crear(3, 1000, INICIO, "Nave");
    nave_setear_pos(jugador, VENTANA_ANCHO/2, VENTANA_ALTO/2);
    nave_setear_ang_nave(jugador, NAVE_ANGULO_INICIAL);
    nave_setear_ang_g(jugador, 3*PI/2);

    // El chorro de la nave:
    //const float chorro[][2] = {{-4, 2}, {-8, 0}, {-4, -2}};
    //size_t chorro_tam = 3;

    bool chorro_prendido = false;
    bool gira_der = false;
    bool gira_izq = false;

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
                    case SDLK_UP:
                        // Prendemos el chorro:
                        chorro_prendido = true;
                        break;
                    case SDLK_DOWN:
                    case SDLK_RIGHT:
                        gira_der = true;
                        break;
                    case SDLK_LEFT:
                        gira_izq = true;
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Apagamos el chorro:
                        chorro_prendido = false;
                        break;
                    case SDLK_RIGHT:
                        gira_der = false;
                        break;
                    case SDLK_LEFT:
                        gira_izq = false;
                        break;
                }
            }
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        // BEGIN código del alumno
        if(chorro_prendido)
          nave_setear_a_thrust(jugador, NAVE_ACELERACION);
        else {
          nave_setear_a_thrust(jugador, 0);
        }
        if(gira_der && !gira_izq)
          nave_girar_der(jugador, NAVE_ROTACION_PASO);
        if(!gira_der && gira_izq)
          nave_girar_izq(jugador, NAVE_ROTACION_PASO);
        nave_mover(jugador, 1.0/JUEGO_FPS);
        // Dibujamos la nave escalada por f en el centro de la pantalla:
        polilinea_t *poli2 = polilinea_clonar(poli);
        rotar(poli2, nave_get_ang(jugador));
        trasladar(poli2, nave_get_posx(jugador), nave_get_posy(jugador));
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
        float x1, y1, x2, y2;
        for(int i = 0; i < polilinea_cantidad_puntos(poli2) - 1; i++) {
            polilinea_obtener_punto(poli2, i, &x1, &y1);
            polilinea_obtener_punto(poli2, i+1, &x2, &y2);
            SDL_RenderDrawLine(
                renderer,
                x1,
                (VENTANA_ALTO - y1),
                x2,
                (VENTANA_ALTO - y2)
            );
        }
        polilinea_destruir(poli2);
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
    polilinea_destruir(poli);
    free(jugador);
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
