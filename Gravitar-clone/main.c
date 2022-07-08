#include <SDL.h>
#include <stdbool.h>
#include <string.h>

#include "config.h"
#include "nave.h"
#include "bala.h"
#include "figuras.h"
#include "fisica.h"
#include "lista.h"
#include "nivel.h"
#include "escritura.h"
#include "planeta.h"


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

    // Leemos todas las figuras y las metemos en una lista enlazada
    FILE* f = fopen("figuras.bin", "rb");
    lista_t* figuras = lista_crear();
    figura_t* figura = figura_leer(f);
    while (figura != NULL) {
        lista_insertar_ultimo(figuras, figura);
        figura = figura_leer(f);
    }
    fclose(f);

    // Buscamos las figuras que vamos a usar y las guardamos
    figura_t* nivel_fig[6] = {
        NULL,
        figura_buscar_nombre(figuras, "NIVEL1NE"),
        figura_buscar_nombre(figuras, "NIVEL1SE"),
        figura_buscar_nombre(figuras, "NIVEL1SW"),
        figura_buscar_nombre(figuras, "NIVEL1NW"),
        figura_buscar_nombre(figuras, "NIVEL1R")
    };

    figura_t* base_fig = figura_buscar_nombre(figuras, "BASE");
    figura_t* estrella_fig = figura_buscar_nombre(figuras, "ESTRELLA");
    figura_t* nave_fig = figura_buscar_nombre(figuras, "NAVE");
    figura_t* nave_chorro_fig = figura_buscar_nombre(figuras, "NAVE+CHORRO");
    figura_t* escudo_fig = figura_buscar_nombre(figuras, "ESCUDO");
    figura_t* escudo2_fig = figura_buscar_nombre(figuras, "ESCUDO2");
    figura_t* disparo_fig = figura_buscar_nombre(figuras, "DISPARO");
    figura_t* torreta_fig = figura_buscar_nombre(figuras, "TORRETA");
    figura_t* torreta_disparo_fig = figura_buscar_nombre(figuras, "TORRETA+DISPARO");
    figura_t* reactor_fig = figura_buscar_nombre(figuras, "REACTOR");
    figura_t* combustible_fig = figura_buscar_nombre(figuras, "COMBUSTIBLE");
    //figura_t* enemigo1_fig = figura_buscar_nombre(figuras, "ENEMIGO1");
    //figura_t* enemigo2_fig = figura_buscar_nombre(figuras, "ENEMIGO2");
    //figura_t* enemigo3_fig = figura_buscar_nombre(figuras, "ENEMIGO3");

    // Crea e inicializa los niveles anexandolos a la tabla de busqueda para poder relacionarlos con el estadio de la nave
    nivel_t* niveles[] = {
        [INICIO] = nivel_crear(NULL, 2000),
        [NIVEL1] = nivel_crear(nivel_fig[1], 2000),
        [NIVEL2] = nivel_crear(nivel_fig[2], 2000),
        [NIVEL3] = nivel_crear(nivel_fig[3], 2000),
        [NIVEL4] = nivel_crear(nivel_fig[4], 2000),
        [NIVEL5] = nivel_crear(nivel_fig[5], 2000),
    };

    nivel_randomizar_disparos();

    // Armamos los niveles agregandole los objetos que corresponden

    // INICIO
    nivel_agregar_planeta(niveles[INICIO], 663, 473, 1000, VENTANA_ALTO / ESCALA_MINIMA - 200, 2000, NIVEL1, figura_buscar_nombre(figuras, "PLANETA1"));
    nivel_agregar_planeta(niveles[INICIO], 671, 145, 1000, VENTANA_ALTO / ESCALA_MINIMA - 200, 4000, NIVEL2, figura_buscar_nombre(figuras, "PLANETA2"));
    nivel_agregar_planeta(niveles[INICIO], 110, 79, 900, VENTANA_ALTO / ESCALA_MINIMA - 200, 6000, NIVEL3, figura_buscar_nombre(figuras, "PLANETA3"));
    nivel_agregar_planeta(niveles[INICIO], 204, 455, 545, 746, 8000, NIVEL4, figura_buscar_nombre(figuras, "PLANETA4"));
    nivel_agregar_planeta(niveles[INICIO], 111, 307, 460, 700, 9000, NIVEL5, figura_buscar_nombre(figuras, "PLANETA5"));

    double x_base = 388; double y_base = 218;
    double x_est = 457; double y_est = 364;

    // NIVEL1
    nivel_agregar_torreta(niveles[NIVEL1], 916, 75, -0.66, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL1], 1425, 159, 0.66, torreta_fig, torreta_disparo_fig);
    nivel_agregar_combustible(niveles[NIVEL1], 1064, 13, 0, combustible_fig);
    nivel_agregar_combustible(niveles[NIVEL1], 1685, 113, 0, combustible_fig);

    // NIVEL2 
    nivel_agregar_combustible(niveles[NIVEL2], 482, 94, 0, combustible_fig);
    nivel_agregar_combustible(niveles[NIVEL2], 1751, 247, 0, combustible_fig);
    nivel_agregar_torreta(niveles[NIVEL2], 423, 195, -0.66, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL2], 806, 215, -0.33, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL2], 1254, 153, 0.66, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL2], 1587, 223, 2.23, torreta_fig, torreta_disparo_fig);

    // NIVEL3
    nivel_agregar_combustible(niveles[NIVEL3], 820, 46, 0, combustible_fig);
    nivel_agregar_combustible(niveles[NIVEL3], 1196, 68, 0, combustible_fig);
    nivel_agregar_combustible(niveles[NIVEL3], 1602, 46, 0, combustible_fig);
    nivel_agregar_torreta(niveles[NIVEL3], 70, 46, 0, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL3], 506, 12, 0, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL3], 952, 12, 0, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL3], 1385, 12, 0, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL3], 757, 210, 3.14, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL3], 1161, 210, 3.14, torreta_fig, torreta_disparo_fig);

    // NIVEL4
    nivel_set_asteroide(niveles[NIVEL4], true);
    nivel_agregar_combustible(niveles[NIVEL4], 188, 429, 0, combustible_fig);
    nivel_agregar_combustible(niveles[NIVEL4], 667, 600, 0, combustible_fig);
    nivel_agregar_combustible(niveles[NIVEL4], 1054, 404, 3.14, combustible_fig);
    nivel_agregar_combustible(niveles[NIVEL4], 574, 344, 3.14, combustible_fig);
    nivel_agregar_torreta(niveles[NIVEL4], 257, 440, 0.66, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL4], 719, 674, 2.23, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL4], 985, 565, 0, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL4], 1125, 417, 3.8, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL4], 862, 163, 3.8, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL4], 626, 323, 2.23, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL4], 505, 331, 3.8, torreta_fig, torreta_disparo_fig);
    nivel_agregar_torreta(niveles[NIVEL4], 378, 296, 2.23, torreta_fig, torreta_disparo_fig);

    // NIVEL5
    nivel_agregar_reactor(niveles[NIVEL5], 815, 309, 0, 2500, reactor_fig);

    // Crea la nave y sus condiciones iniciales
    nave_t* jugador = nave_crear(3, JUEGO_COMBUSTIBLE_INICIAL, 0, INICIO, nave_fig, nave_chorro_fig);
    if (jugador == NULL) return 1;
    nave_setear_pos(jugador, x_base, y_base);
    nave_setear_ang_nave(jugador, NAVE_ANGULO_INICIAL);
    nave_setear_ang_g(jugador, 3 * PI / 2);

    bool chorro_prendido = false;
    bool gira_der = false;
    bool gira_izq = false;
    bool dispara = false;
    bool escudo = false;
    size_t disparo_delay = 0;
    size_t disparo_delay_t = 0;

    // Queremos que todo se dibuje escalado por "escala" y centrado por "centro"
    float escala = 1;
    double centro = VENTANA_ANCHO/2;

    double posx_res = 0;
    double posy_res = 0;
    // END código del alumno

    unsigned int ticks = SDL_GetTicks();

    //------------------------------------------------WHILE----------------------------------------------------------
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

        //---------------------------------------------------COMPUTO------------------------------------------------------------

        // Actualizacion de los valores de la nave en este tick
        if (chorro_prendido)
            nave_setear_a_thrust(jugador, NAVE_ACELERACION);
        else 
            nave_setear_a_thrust(jugador, 0);
        if (gira_der && !gira_izq)
            nave_girar_der(jugador, NAVE_ROTACION_PASO);
        if (!gira_der && gira_izq)
            nave_girar_izq(jugador, NAVE_ROTACION_PASO);

        nave_mover(jugador, DT);

        // Guardamos alores de la nave en este tick
        double x_nav = nave_get_posx(jugador);
        double y_nav = nave_get_posy(jugador);
        double vel_nav = nave_get_vel(jugador);
        double x_vel_nav = nave_get_velx(jugador);
        double y_vel_nav = nave_get_vely(jugador);
        double ang_nav = nave_get_ang(jugador);
        estadio_t nivel_nav = nave_get_estadio(jugador);

        nivel_t* nivel_act = niveles[nivel_nav];
        figura_t* layout = nivel_get_figura(nivel_act);
        bool inf = nivel_es_inf(nivel_act);

        // Condiciones según el estadio de la nave
        if (nivel_nav == INICIO) {

            // Escala reset
            escala = 1;
            centro = 0;

            // Nave rebota
            if (y_nav <= 5 || y_nav >= VENTANA_ALTO)
                nave_setear_vely(jugador, y_vel_nav * -1);
            if (x_nav <= 5 || x_nav >= VENTANA_ANCHO)
                nave_setear_velx(jugador, x_vel_nav * -1);

            // Gravedad con la estrella
            nave_setear_ang_g(jugador, computar_angulo(x_nav, y_nav, 457, 364));
            if (computar_distancia(x_nav, y_nav, 457, 364) < 20) {
                nave_matar(jugador);
            }

            // Chequea si la nave entró a algun planeta
            if (nivel_nave_accede_planetas(nivel_act, jugador)) {
                posx_res = x_nav;  // Guarda sus coordenadas para cuando salga del nivel
                posy_res = y_nav;
                nave_setear_vel(jugador, 0, -5);
                nave_setear_ang_g(jugador, 3 * PI / 2); 
                nave_setear_ang_nave(jugador, 3 * PI / 2);
                centro = nave_get_posx(jugador); // Setea el centro en la posicion de la nave por si el nivel es infinito
                continue;
            }
        }

        if(nivel_nav != INICIO) {
            // Calcula dimensiones del nivel
            double ancho = nivel_get_ancho(nivel_act);
            double alto = nivel_get_alto(nivel_act);
            if (!inf) {
                // Calcula bordes arbitrarios del nivel segun su altura y ancho FISICOS y no los dibujados
                double x_min = 0;
                double y_min = 0;
                nivel_get_max_min(nivel_act, NULL, NULL, &x_min, &y_min);
                double y_max = y_min + alto + 100;
                double x_max = x_min * 2 + ancho;

                // Verifica si la nave sale del nivel
                if (y_nav <= 5 || y_nav >= y_max || x_nav <= 5 || x_nav >= x_max) {
                    estadio_t estadio_anterior = nave_get_estadio(jugador);
                    nivel_balas_vaciar(nivel_act);
                    nivel_nave_salir_planeta(jugador, x_base, y_base, niveles[INICIO], INICIO);
                    if (!nivel_tiene_torretas(niveles[estadio_anterior]) && nivel_es_de_torretas(niveles[estadio_anterior])) nivel_planeta_destruir(niveles[INICIO], estadio_anterior);
                }

                // Calcula de centro y escala

                escala = VENTANA_ALTO * 1.0 / alto;
                if (VENTANA_ANCHO * 1.0 / (ancho + x_min) < escala)
                    escala = VENTANA_ANCHO * 1.0 / (ancho + x_min);
                centro = (ancho + x_min) / 2;

                centro = x_min + ancho / 2 - centro;
            }
            
            else {

                // Verifica si la nave escapó del nivel
                if (y_nav > VENTANA_ALTO / ESCALA_MINIMA) {
                    estadio_t estadio_anterior = nivel_nav;
                    nivel_balas_vaciar(niveles[estadio_anterior]);
                    nivel_nave_salir_planeta(jugador, x_base, y_base, niveles[INICIO], INICIO);
                    if (!nivel_tiene_torretas(niveles[estadio_anterior]) && nivel_es_de_torretas(niveles[estadio_anterior])) nivel_planeta_destruir(niveles[INICIO], estadio_anterior);
                }

                // Calcula escala y centro
                if (y_nav > VENTANA_ALTO * MARGEN_ALTURA)
                    escala = VENTANA_ALTO * MARGEN_ALTURA / y_nav;
                if (escala < ESCALA_MINIMA)
                    escala = ESCALA_MINIMA;

                if ((x_nav - centro) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav - VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;
                else if ((centro - x_nav) * escala > VENTANA_ANCHO / 2 * MARGEN_ANCHO)
                    centro = x_nav + VENTANA_ANCHO / 2 * MARGEN_ANCHO / escala;


                // Ilusion de infinito
                if (x_nav > ancho) {
                    nave_setear_pos(jugador, x_nav - ancho, y_nav);
                    centro -= ancho;
                }
                if (x_nav < -10) {
                    nave_setear_pos(jugador, x_nav + ancho, y_nav);
                    centro += ancho;
                }
            }
        }
        
        // Actualizacion y manejo de los objetos del nivel

        // Actualiza las balas y verifica si se tienen que crear nuevas
        nivel_balas_actualizar(nivel_act, DT);
        
        if (dispara && disparo_delay == 0) {
            // Preguntar velocidad bala + nave
            nivel_nave_dispara(nivel_act, jugador, BALA_VELOCIDAD, disparo_fig);
            disparo_delay = DISPARO_DELAY;
        }
        if (disparo_delay != 0) disparo_delay--;

        // Actualiza las torretas

        if (disparo_delay_t == 0) {
            nivel_torretas_disparan_a_nave(nivel_act, jugador, PI / 8, 35, DISPARO_RANGO, BALA_VELOCIDAD, disparo_fig);
            disparo_delay_t = DISPARO_DELAY;
        }
        if (disparo_delay_t != 0) disparo_delay_t--;

        nivel_torretas_disparadas(nivel_act);

        // Verifica colisiones de la nave
        if (nivel_nave_disparada(nivel_act, jugador)) {
            if (!escudo) {
                estadio_t estadio_anterior = nave_get_estadio(jugador);
                nivel_balas_vaciar(nivel_act);
                nave_matar(jugador);
                if (!nivel_tiene_torretas(niveles[estadio_anterior]) && nivel_es_de_torretas(niveles[estadio_anterior])) nivel_planeta_destruir(niveles[INICIO], estadio_anterior);
            }
        }
        if (layout != NULL && nave_distancia_a_figura(jugador, layout) < 5) {
            estadio_t estadio_anterior = nave_get_estadio(jugador);
            nivel_balas_vaciar(nivel_act);
            nave_matar(jugador);
            if (!nivel_tiene_torretas(niveles[estadio_anterior]) && nivel_es_de_torretas(niveles[estadio_anterior])) nivel_planeta_destruir(niveles[INICIO], estadio_anterior);
        }
        if (escudo) {
            nivel_nave_recoge_combustible(nivel_act, jugador);
        }
      
        if (nave_get_vidas(jugador) == 0) {
            if (!chorro_prendido) {
                dibujar_texto("GAME OVER", VENTANA_ANCHO / 2 - 250, VENTANA_ALTO / 2 - 30, 10, 1, 0, 0, VENTANA_ALTO, renderer);
                nave_setear_pos(jugador, x_base, 218);
                nave_setear_estadio(jugador, INICIO);
                nave_setear_vel(jugador, 0, 0);
                nave_setear_ang_nave(jugador, PI / 2);
            }
            else break;
        }
 
        //----------------------------------------------------DIBUJADO------------------------------------------------------

        // Ejecutamos diferentes rutinas de dibujado con diferentes parámetros según el estadio
        if (nivel_nav == INICIO) {
            figura_dibujar(estrella_fig, 457, 364, 0, 0, 1, renderer);
            figura_dibujar(base_fig, x_base, 218, 0, 0, 1, renderer);
            if (escudo) figura_dibujar(escudo_fig, x_nav, y_nav, ang_nav + PI / 2, 0, 1, renderer);
            nave_dibujar(jugador, 0, 0, 0, 1, renderer);
            /*dibujar_texto("2000", 683, 493, 1.5, 0, 1, 1, VENTANA_ALTO, renderer);
            dibujar_texto("4000", 683, 120, 1.5, 0, 1, 1, VENTANA_ALTO, renderer);
            dibujar_texto("6000", 60, 59, 1.5, 0, 1, 1, VENTANA_ALTO, renderer);
            dibujar_texto("8000", 150, 480, 1.5, 0, 1, 1, VENTANA_ALTO, renderer);
            dibujar_texto("9000", 45, 295, 1.5, 0, 1, 1, VENTANA_ALTO, renderer);*/
            
        }
        if (nivel_nav != INICIO) {
            if (!inf) {
                if (nivel_es_asteroide(niveles[nivel_nav])) {
                    double x_min, y_min, x_max, y_max;
                    nivel_get_max_min(niveles[nivel_nav], &x_max, &y_max, &x_min, &y_min);
                    if (escudo) figura_dibujar(escudo2_fig, x_nav * escala - centro * escala, y_nav * escala, PI * 1.5 + computar_angulo(VENTANA_ANCHO / 2 + x_min, VENTANA_ALTO / 2 + y_min, x_nav, y_nav), 0, escala, renderer);
                }
                else
                    if (escudo) figura_dibujar(escudo2_fig, x_nav * escala - centro * escala, y_nav * escala, ang_nav + PI / 2, 0, escala, renderer);
                nave_dibujar(jugador, -centro, 0, centro, escala, renderer);
            }
            else {
                if (escudo) figura_dibujar(escudo2_fig, (x_nav - centro)*escala + (VENTANA_ANCHO / 2) , y_nav*escala, 0, 0, escala, renderer);
                nave_dibujar(jugador, -centro*escala + VENTANA_ANCHO/2 , 0, 0, escala, renderer);
            }
        }
        char fuel[10];
        char puntos[10];

        // Dibujamos del HUD
        for (size_t i = 0; i < nave_get_vidas(jugador); i++)
            figura_dibujar(nave_fig, VENTANA_ANCHO / 2 - 350 + (i*15), VENTANA_ALTO - 55 + (i * 2), PI / 2, 0, 1, renderer);
        dibujar_texto("SCORE", VENTANA_ANCHO / 2 - 40, VENTANA_ALTO - 30, 2, 0, 1, 1, VENTANA_ALTO, renderer);
        dibujar_texto("FUEL", VENTANA_ANCHO / 2 - 30, VENTANA_ALTO - 50, 2, 0, 1, 1, VENTANA_ALTO, renderer);
        dibujar_texto("NEXT SHIP", VENTANA_ANCHO / 2 - 100, VENTANA_ALTO - 70, 2, 0, 1, 1, VENTANA_ALTO, renderer);
        dibujar_texto("10000", VENTANA_ANCHO / 2 + 20, VENTANA_ALTO - 70, 2, 0, 1, 0, VENTANA_ALTO, renderer);
        dibujar_texto(_itoa(nave_get_fuel(jugador), fuel, 10), VENTANA_ANCHO / 2 - 200, VENTANA_ALTO - 50, 2, 0, 1, 0, VENTANA_ALTO, renderer);
        dibujar_texto(_itoa(nave_get_puntos(jugador), puntos, 10), VENTANA_ANCHO / 2 - 200, VENTANA_ALTO - 30, 2, 0, 1, 0, VENTANA_ALTO, renderer);

        // Dibujamos el nivel con todos sus objetos
        nivel_dibujar(nivel_act, centro, escala, VENTANA_ANCHO, renderer);

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
    nave_destruir(jugador, NULL, NULL);
    nivel_destruir(niveles[INICIO], NULL);
    nivel_destruir(niveles[NIVEL1], NULL);
    nivel_destruir(niveles[NIVEL2], NULL);
    nivel_destruir(niveles[NIVEL3], NULL);
    nivel_destruir(niveles[NIVEL4], NULL);
    nivel_destruir(niveles[NIVEL5], NULL);
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
