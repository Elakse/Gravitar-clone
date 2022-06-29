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
#include "torreta.h"
#include "combustible.h"
#include "nivel.h"

figura_t* figura_buscar_nombre(lista_t *figuras, char* nombre) {
    if (lista_esta_vacia(figuras)) return NULL;

    lista_iter_t *iter = lista_iter_crear(figuras);
    do {
        figura_t* figura = lista_iter_ver_actual(iter);
        if (!strcmp(figura_obtener_nombre(figura), nombre)) {
            lista_iter_destruir(iter);
            return figura;
        }
        lista_iter_avanzar(iter);
    } while (!lista_iter_al_final(iter));
    lista_iter_destruir(iter);
    return NULL;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    int dormir = 0;

    // BEGIN código del alumno
    // Mi nave:

    lista_t* balas = lista_crear();

    // Leemos todas las figuras y las metemos en una lista enlazada
    FILE* f = fopen("figuras.bin", "rb");
    lista_t* figuras = lista_crear();
    figura_t* figura = figura_leer(f);
    while (figura != NULL) {
        lista_insertar_ultimo(figuras, figura);
        figura = figura_leer(f);
    }

    // Creamos todos los niveles con sus figuras
    nivel_t* inicio = nivel_crear(INICIO);
    nivel_insertar_figura(inicio, figura_buscar_nombre(figuras, "BASE"), 388, 218, 0, 1);
    nivel_insertar_figura(inicio, figura_buscar_nombre(figuras, "ESTRELLA"), 457, 364, 0, 1);
    nivel_insertar_figura(inicio, figura_buscar_nombre(figuras, "PLANETA1"), 663, 473, 0, 1);
    nivel_insertar_figura(inicio, figura_buscar_nombre(figuras, "PLANETA2"), 671, 145, 0, 1);
    nivel_insertar_figura(inicio, figura_buscar_nombre(figuras, "PLANETA3"), 110, 79, 0, 1);
    nivel_insertar_figura(inicio, figura_buscar_nombre(figuras, "PLANETA4"), 204, 455, 0, 1);
    nivel_insertar_figura(inicio, figura_buscar_nombre(figuras, "PLANETA5"), 111, 307, 0, 1);

    nivel_t* nivel1 = nivel_crear(NIVEL1);
    nivel_insertar_figura(nivel1, figura_buscar_nombre(figuras, "NIVEL1NE"), 0, 0, 0, 1);
    nivel_insertar_figura(nivel1, figura_buscar_nombre(figuras, "TORRETA"), 916, 75, -0.66, 1);
    nivel_insertar_figura(nivel1, figura_buscar_nombre(figuras, "TORRETA"), 1425, 159, 0.66, 1);
    nivel_insertar_figura(nivel1, figura_buscar_nombre(figuras, "COMBUSTIBLE"), 1064, 13, 0, 1);
    nivel_insertar_figura(nivel1, figura_buscar_nombre(figuras, "COMBUSTIBLE"), 1685, 113, 0, 1);

    nivel_t* nivel2 = nivel_crear(NIVEL2);
    nivel_insertar_figura(nivel2, figura_buscar_nombre(figuras, "NIVEL1SE"), 0, 0, 0, 1);
    nivel_insertar_figura(nivel2, figura_buscar_nombre(figuras, "TORRETA"), 423, 195, -0.66, 1);
    nivel_insertar_figura(nivel2, figura_buscar_nombre(figuras, "TORRETA"), 806, 215, -0.33, 1);
    nivel_insertar_figura(nivel2, figura_buscar_nombre(figuras, "TORRETA"), 1254, 153, 0.66, 1);
    nivel_insertar_figura(nivel2, figura_buscar_nombre(figuras, "TORRETA"), 1587, 223, 2.23, 1);
    nivel_insertar_figura(nivel2, figura_buscar_nombre(figuras, "COMBUSTIBLE"), 482, 94, 0, 1);
    nivel_insertar_figura(nivel2, figura_buscar_nombre(figuras, "COMBUSTIBLE"), 1751, 247, 0, 1);

    nivel_t* nivel3 = nivel_crear(NIVEL3);
    nivel_insertar_figura(nivel3, figura_buscar_nombre(figuras, "NIVEL1SW"), 0, 0, 0, 1);
    nivel_insertar_figura(nivel3, figura_buscar_nombre(figuras, "TORRETA"), 70, 46, 0, 1);
    nivel_insertar_figura(nivel3, figura_buscar_nombre(figuras, "TORRETA"), 506, 12, 0, 1);
    nivel_insertar_figura(nivel3, figura_buscar_nombre(figuras, "TORRETA"), 952, 12, 0, 1);
    nivel_insertar_figura(nivel3, figura_buscar_nombre(figuras, "TORRETA"), 1385, 12, 0, 1);
    nivel_insertar_figura(nivel3, figura_buscar_nombre(figuras, "TORRETA"), 757, 210, 3.14, 1);
    nivel_insertar_figura(nivel3, figura_buscar_nombre(figuras, "TORRETA"), 1161, 210, 3.14, 1);
    nivel_insertar_figura(nivel3, figura_buscar_nombre(figuras, "COMBUSTIBLE"), 820, 46, 0, 1);
    nivel_insertar_figura(nivel3, figura_buscar_nombre(figuras, "COMBUSTIBLE"), 1196, 68, 0, 1);
    nivel_insertar_figura(nivel3, figura_buscar_nombre(figuras, "COMBUSTIBLE"), 1602, 46, 0, 1);

    nivel_t* nivel4 = nivel_crear(NIVEL4);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "NIVEL1NW"), 0, 0, 0, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "TORRETA"), 257, 440, 0.66, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "TORRETA"), 719, 674, 2.23, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "TORRETA"), 985, 565, 0, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "TORRETA"), 1125, 417, 3.8, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "TORRETA"), 862, 163, 3.8, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "TORRETA"), 626, 323, 2.23, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "TORRETA"), 505, 331, 3.8, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "TORRETA"), 378, 296, 2.23, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "COMBUSTIBLE"), 188, 429, 0, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "COMBUSTIBLE"), 667, 600, 0, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "COMBUSTIBLE"), 1054, 404, 3.14, 1);
    nivel_insertar_figura(nivel4, figura_buscar_nombre(figuras, "COMBUSTIBLE"), 574, 344, 3.14, 1);

    nivel_t* nivel5 = nivel_crear(NIVEL5);
    nivel_insertar_figura(nivel5, figura_buscar_nombre(figuras, "NIVEL1R"), 0, 0, 0, 1);
    nivel_insertar_figura(nivel5, figura_buscar_nombre(figuras, "REACTOR"), 815, 309, 0, 1);
    
    nivel_t* niveles[6] = { inicio, nivel1, nivel2, nivel3, nivel4, nivel5 };

    figura_t* nave = figura_buscar_nombre(figuras, "NAVE");
    figura_t* nave_chorro = figura_buscar_nombre(figuras, "NAVE+CHORRO");
    figura_t* escudo2 = figura_buscar_nombre(figuras, "ESCUDO2");
    figura_t* disparo = figura_buscar_nombre(figuras, "DISPARO");

    nave_t *jugador = nave_crear(3, JUEGO_COMBUSTIBLE_INICIAL, INICIO, "NAVE");
    if(jugador == NULL) return 1;
    nave_setear_pos(jugador, 388, 218);
    nave_setear_ang_nave(jugador, NAVE_ANGULO_INICIAL);
    nave_setear_ang_g(jugador, 3*PI/2);

    bool chorro_prendido = false;
    bool gira_der = false;
    bool gira_izq = false;
    bool dispara = false;
    bool escudo = false;
    size_t disparo_delay = 0;

    // Queremos que todo se dibuje escalado por "escala":
    double escala = 1;
    double centro = 0;

    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
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
                switch (event.key.keysym.sym) {
                case SDLK_w:
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
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

        // BEGIN código del alumno

        // Actualizacion de los valores de la nave en este tick
        if (chorro_prendido)
            nave_setear_a_thrust(jugador, NAVE_ACELERACION);
        else nave_setear_a_thrust(jugador, 0);
        if (gira_der && !gira_izq)
            nave_girar_der(jugador, NAVE_ROTACION_PASO);
        if (!gira_der && gira_izq)
            nave_girar_izq(jugador, NAVE_ROTACION_PASO);
        nave_mover(jugador, DT);

        // Valores de la nave en este tick
        double x_nav = nave_get_posx(jugador);
        double y_nav = nave_get_posy(jugador);
        double vel_nav = nave_get_vel(jugador);
        double x_vel_nav = nave_get_velx(jugador);
        double y_vel_nav = nave_get_vely(jugador);
        double ang_nav = nave_get_ang(jugador);
        nivel_enum_t nivel_nav = nave_get_nivel(jugador);

        // Actualizacion de todas las figuras del nivel (en el que está la nave) en este tick
        switch (nivel_nav) {
            case INICIO: {
                escala = 1;
                if (y_nav <= 5 || y_nav >= VENTANA_ALTO)
                    nave_setear_vely(jugador, y_vel_nav * -1);
                if (x_nav <= 5 || x_nav >= VENTANA_ANCHO)
                    nave_setear_velx(jugador, x_vel_nav * -1);

                nave_setear_ang_g(jugador, computar_angulo(x_nav, y_nav, 457, 364));

                if (computar_distancia(x_nav, y_nav, 663, 473) < 20) {
                    nave_setear_nivel(jugador, NIVEL1);
                    nave_setear_pos(jugador, 300, 590);
                    nave_setear_vel(jugador, 0, -20);
                    nave_setear_ang_nave(jugador, PI * 1.5);
                    nave_setear_ang_g(jugador, PI * 1.5);
                }
                if (computar_distancia(x_nav, y_nav, 671, 145) < 20) {
                    nave_setear_nivel(jugador, NIVEL2);
                    nave_setear_pos(jugador, 400, 590);
                    nave_setear_vel(jugador, 0, -20);
                    nave_setear_ang_nave(jugador, PI * 1.5);
                    nave_setear_ang_g(jugador, PI * 1.5);
                }
                if (computar_distancia(x_nav, y_nav, 110, 79) < 20) {
                    nave_setear_nivel(jugador, NIVEL3);
                    nave_setear_pos(jugador, 400, 590);
                    nave_setear_vel(jugador, 0, -20);;
                    nave_setear_ang_nave(jugador, PI * 1.5);
                    nave_setear_ang_g(jugador, PI * 1.5);
                }
                if (computar_distancia(x_nav, y_nav, 204, 455) < 20) {
                    nave_setear_nivel(jugador, NIVEL4);
                    nave_setear_pos(jugador, 400, 590);
                    nave_setear_vel(jugador, 0, -20);
                    nave_setear_ang_nave(jugador, PI * 1.5);
                    nave_setear_ang_g(jugador, PI * 1.5);
                }
                if (computar_distancia(x_nav, y_nav, 111, 307) < 20) {
                    nave_setear_nivel(jugador, NIVEL5);
                    nave_setear_pos(jugador, 300, 590);
                    nave_setear_vel(jugador, 0, -20);
                    nave_setear_ang_nave(jugador, PI * 1.5);
                    nave_setear_ang_g(jugador, PI * 1.5);
                }
                if (computar_distancia(x_nav, y_nav, 457, 364) < 20) {
                    nave_setear_pos(jugador, 388, 218);
                    nave_setear_vel(jugador, 0, 0);
                    nave_setear_ang_nave(jugador, PI / 4);
                    nave_restar_vida(jugador);
                }
                break;
            }
            case NIVEL1: {
                if (y_nav >= VENTANA_ALTO) {
                    nave_setear_nivel(jugador, INICIO);
                    nave_setear_pos(jugador, 645, 455);
                    nave_setear_vel(jugador, -10, -10);
                    nave_setear_ang_nave(jugador, PI + PI / 4);
                }

                if (x_nav > VENTANA_ALTO * MARGEN_ALTURA)
                    escala = VENTANA_ALTO * MARGEN_ALTURA / x_nav;
                if (escala < ESCALA_MINIMA)
                    escala = ESCALA_MINIMA;
                if ((x_nav - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
                else if ((x_nav - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

                break;
            }
            case NIVEL2: {
                if (y_nav >= VENTANA_ALTO) {
                    nave_setear_nivel(jugador, INICIO);
                    nave_setear_ang_nave(jugador, PI);
                    nave_setear_vel(jugador, -10, 0);
                    nave_setear_pos(jugador, 645, 145);
                }

                if (y_nav > VENTANA_ALTO * MARGEN_ALTURA)
                    escala = VENTANA_ALTO * MARGEN_ALTURA / y_nav;
                if (escala < ESCALA_MINIMA)
                    escala = ESCALA_MINIMA;
                if ((x_nav - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
                else if ((x_nav - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

                break;
            }
            case NIVEL3: {
                if (y_nav >= VENTANA_ALTO) {
                    nave_setear_nivel(jugador, INICIO);
                    nave_setear_pos(jugador, 130, 95);
                    nave_setear_vel(jugador, 10, 10);
                    nave_setear_ang_nave(jugador, PI / 4);
                }

                if (y_nav > VENTANA_ALTO * MARGEN_ALTURA)
                    escala = VENTANA_ALTO * MARGEN_ALTURA / y_nav;
                if (escala < ESCALA_MINIMA)
                    escala = ESCALA_MINIMA;

                if ((x_nav - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
                else if ((x_nav - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

                break;
            }
            case NIVEL4: {
                if (y_nav >= VENTANA_ALTO) {
                    nave_setear_nivel(jugador, INICIO);
                    nave_setear_pos(jugador, 204, 435);
                    nave_setear_vel(jugador, 0, -10);
                    nave_setear_ang_nave(jugador, PI * 1.5);
                }

                if (y_nav > VENTANA_ALTO * MARGEN_ALTURA)
                    escala = VENTANA_ALTO * MARGEN_ALTURA / y_nav;
                if (escala < ESCALA_MINIMA)
                    escala = ESCALA_MINIMA;
                if ((x_nav - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
                else if ((x_nav - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

                break;
            }
            case NIVEL5: {
                if (y_nav >= VENTANA_ALTO) {
                    nave_setear_nivel(jugador, INICIO);
                    nave_setear_ang_nave(jugador, PI * 2);
                    nave_setear_vel(jugador, 10, 0);
                    nave_setear_pos(jugador, 150, 307);
                }
                if (y_nav <= 0)
                    nave_setear_vely(jugador, y_vel_nav * -1);
                if (x_nav <= 0 || x_nav >= VENTANA_ANCHO * 0.99)
                    nave_setear_velx(jugador, x_vel_nav * -1);

                if (y_nav > VENTANA_ALTO * MARGEN_ALTURA)
                    escala = VENTANA_ALTO * MARGEN_ALTURA / y_nav;
                if (escala < ESCALA_MINIMA)
                    escala = ESCALA_MINIMA;
                if ((x_nav - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
                else if ((x_nav - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

                break;
            }
        }

        // Switch calculando valores de la nave en cada uso (MAL)
        /*switch (nave_get_nivel(jugador)) {
        case INICIO: {
            if (nave_get_posy(jugador) <= 5 || nave_get_posy(jugador) >= VENTANA_ALTO)
                nave_setear_vely(jugador, nave_get_vely(jugador) * -1);
            if (nave_get_posx(jugador) <= 5 || nave_get_posx(jugador) >= VENTANA_ANCHO)
                nave_setear_velx(jugador, nave_get_velx(jugador) * -1);

            nave_setear_ang_g(jugador, computar_angulo(nave_get_posx(jugador), nave_get_posy(jugador), 457, 364));

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
            if (computar_distancia(nave_get_posx(jugador), nave_get_posy(jugador), 457, 364) < 20) {
                nave_setear_pos(jugador, 388, 218);
                nave_setear_vel(jugador, 0, 0);
                nave_setear_ang_nave(jugador, PI / 4);
                nave_restar_vida(jugador);
            }
            break;
        }
        case NIVEL1: {
            if (nave_get_posy(jugador) >= VENTANA_ALTO) {
                nave_setear_nivel(jugador, INICIO);
                nave_setear_pos(jugador, 645, 455);
                nave_setear_vel(jugador, -10, -10);
                nave_setear_ang_nave(jugador, PI + PI / 4);
            }

            if (nave_get_posy(jugador) > VENTANA_ALTO * MARGEN_ALTURA)
                escala = VENTANA_ALTO * MARGEN_ALTURA / nave_get_posy(jugador);
            if (escala < ESCALA_MINIMA)
                escala = ESCALA_MINIMA;
            if ((nave_get_posx(jugador) - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                centro = nave_get_posx(jugador) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
            else if ((nave_get_posx(jugador) - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                centro = nave_get_posx(jugador) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

            break;
        }
        case NIVEL2: {
            if (nave_get_posy(jugador) >= VENTANA_ALTO) {
                nave_setear_nivel(jugador, INICIO);
                nave_setear_ang_nave(jugador, PI);
                nave_setear_vel(jugador, -10, 0);
                nave_setear_pos(jugador, 645, 145);
            }

            if (nave_get_posy(jugador) > VENTANA_ALTO * MARGEN_ALTURA)
                escala = VENTANA_ALTO * MARGEN_ALTURA / nave_get_posy(jugador);
            if (escala < ESCALA_MINIMA)
                escala = ESCALA_MINIMA;
            if ((nave_get_posx(jugador) - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                centro = nave_get_posx(jugador) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
            else if ((nave_get_posx(jugador) - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                centro = nave_get_posx(jugador) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

            break;
        }
        case NIVEL3: {
            if (nave_get_posy(jugador) >= VENTANA_ALTO) {
                nave_setear_nivel(jugador, INICIO);
                nave_setear_pos(jugador, 130, 95);
                nave_setear_vel(jugador, 10, 10);
                nave_setear_ang_nave(jugador, PI / 4);
            }

            if (nave_get_posy(jugador) > VENTANA_ALTO * MARGEN_ALTURA)
                escala = VENTANA_ALTO * MARGEN_ALTURA / nave_get_posy(jugador);
            if (escala < ESCALA_MINIMA)
                escala = ESCALA_MINIMA;

            if ((nave_get_posx(jugador) - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                centro = nave_get_posx(jugador) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
            else if ((nave_get_posx(jugador) - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                centro = nave_get_posx(jugador) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

            break;
        }
        case NIVEL4: {
            if (nave_get_posy(jugador) >= VENTANA_ALTO) {
                nave_setear_nivel(jugador, INICIO);
                nave_setear_pos(jugador, 204, 435);
                nave_setear_vel(jugador, 0, -10);
                nave_setear_ang_nave(jugador, PI * 1.5);
            }

            if (nave_get_posy(jugador) > VENTANA_ALTO * MARGEN_ALTURA)
                escala = VENTANA_ALTO * MARGEN_ALTURA / nave_get_posy(jugador);
            if (escala < ESCALA_MINIMA)
                escala = ESCALA_MINIMA;
            if ((nave_get_posx(jugador) - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                centro = nave_get_posx(jugador) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
            else if ((nave_get_posx(jugador) - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                centro = nave_get_posx(jugador) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

            break;
        }
        case NIVEL5: {
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

            if (nave_get_posy(jugador) > VENTANA_ALTO * MARGEN_ALTURA)
                escala = VENTANA_ALTO * MARGEN_ALTURA / nave_get_posy(jugador);
            if (escala < ESCALA_MINIMA)
                escala = ESCALA_MINIMA;
            if ((nave_get_posx(jugador) - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                centro = nave_get_posx(jugador) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
            else if ((nave_get_posx(jugador) - centro) * escala < VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                centro = nave_get_posx(jugador) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;

            break;
        }
        }*/

        // Verificamos si se tienen que crear balas
        if (dispara && disparo_delay == 0) {
            lista_insertar_ultimo(balas, bala_crear(x_nav, y_nav, BALA_VELOCIDAD + vel_nav, ang_nav, nivel_nav, true));
            disparo_delay = DISPARO_DELAY;
        }
        if (disparo_delay != 0) disparo_delay--;

        lista_iter_t* iter = lista_iter_crear(balas);
        while (!lista_iter_al_final(iter)) {
            bala_t* bala = lista_iter_ver_actual(iter);
            if (!bala_actualizar(bala, DT)) {
                bala_destruir(lista_iter_borrar(iter));
            }
            lista_iter_avanzar(iter);
        }
        lista_iter_destruir(iter);

        // Dibujamos todo (nivel con sus figuras, nave, escudo, chorro)

        /*if (chorro_prendido) nave_cambiar_nombre_fig(jugador, "NAVE+CHORRO");
        else nave_cambiar_nombre_fig(jugador, "NAVE");
        figura_t* nave_fig_a_dibujar = figura_buscar_nombre(figuras, nave_get_nombre_fig(jugador));*/
        nivel_dibujar(niveles[nivel_nav], escala, 0, renderer);
        if (escudo) figura_dibujar(escudo2, x_nav, y_nav, ang_nav + PI / 2, escala, renderer);
        if(!chorro_prendido) figura_dibujar(nave, x_nav, y_nav, ang_nav, escala, renderer);
        else figura_dibujar(nave_chorro, x_nav, y_nav, ang_nav, escala, renderer);

        for (lista_iter_t* iter = lista_iter_crear(balas); !lista_iter_al_final(iter); lista_iter_avanzar(iter)) {
            bala_t* bala = lista_iter_ver_actual(iter);
            figura_dibujar(disparo, bala_get_posx(bala), bala_get_posy(bala), 0, 1, renderer);
        }

        if (nave_get_vidas(jugador) == 0) break;

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
    lista_destruir(figuras, figura_destruir);
    nave_destruir(jugador);
    figura_destruir(figura);
    nivel_destruir(inicio);
    nivel_destruir(nivel1);
    nivel_destruir(nivel2);
    nivel_destruir(nivel3);
    nivel_destruir(nivel4);
    nivel_destruir(nivel5);
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
