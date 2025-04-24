#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "background.h"
background robot;
    
SDL_Surface *iconeGuide = NULL;
Uint32 start_time; // déclaration globale

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    start_time = SDL_GetTicks(); 

    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Jeu ", NULL);

    TTF_Font *font = TTF_OpenFont("nasa.ttf", 24);
    if (!font) {
        fprintf(stderr, "Erreur chargement arial.ttf : %s\n", TTF_GetError());
        return 1;
    }

    iconeGuide = loadImage("guide.png");
    if (!iconeGuide) {
        printf("Erreur chargement guide.png\n");
        return 1;
    }

    SDL_Rect posIcone = {10, 10};
    int afficher_guide = 0;

    image lvl1_img, lvl2_img;
    if (!backgroundLoad_lvl1(&lvl1_img)) return 1;
    lvl2_img.filename = "bg2.jpg";
    lvl2_img.img = IMG_Load(lvl2_img.filename);
    if (!lvl2_img.img) {
        fprintf(stderr, "Erreur chargement bg2.png : %s\n", IMG_GetError());
        return 1;
    }
    lvl2_img.img_size.x = lvl2_img.img_size.y = 0;
    lvl2_img.img_size.w = lvl2_img.img->w;
    lvl2_img.img_size.h = lvl2_img.img->h;
    lvl2_img.img_pos.x = lvl2_img.img_pos.y = 0;

    int niveau_p1 = 1, niveau_p2 = 1;

    Mix_Music *music;
    if (!musicLoad1(&music)) fprintf(stderr, "Continuer sans musique.\n");

    SDL_Event event;
    int running = 1, direction1 = -1, direction2 = -1, split_screen = 0;
    SDL_Rect cam1 = {0, 0, SCREEN_W / 2, SCREEN_H};
    SDL_Rect cam2 = {SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_H};
    
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_d: direction1 = 0; break;
                    case SDLK_q: direction1 = 1; break;
                    case SDLK_z: direction1 = 2; break;
                    case SDLK_s: direction1 = 3; break;

                    case SDLK_RIGHT: direction2 = 0; break;
                    case SDLK_LEFT:  direction2 = 1; break;
                    case SDLK_UP:    direction2 = 2; break;
                    case SDLK_DOWN:  direction2 = 3; break;

                    case SDLK_p: split_screen = !split_screen; break;
                    case SDLK_ESCAPE: running = 0; break;
                }
            }

            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_d: case SDLK_q: case SDLK_z: case SDLK_s:
                        direction1 = -1; break;
                    case SDLK_RIGHT: case SDLK_LEFT: case SDLK_UP: case SDLK_DOWN:
                        direction2 = -1; break;
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mx = event.button.x;
                int my = event.button.y;

                if (mx >= posIcone.x && mx <= posIcone.x + iconeGuide->w &&
                    my >= posIcone.y && my <= posIcone.y + iconeGuide->h) {
                    afficher_guide = !afficher_guide;
                }
            }
        }
        
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        if (split_screen) {
            if (niveau_p1 == 1) update_camera(&cam1, direction1, lvl1_img.img, 5, 5);
            else update_camera(&cam1, direction1, lvl2_img.img, 5, 5);

            if (niveau_p2 == 1) update_camera(&cam2, direction2, lvl1_img.img, 5, 5);
            else update_camera(&cam2, direction2, lvl2_img.img, 5, 5);

            SDL_Rect left_screen = {0, 0, SCREEN_W / 2, SCREEN_H};
            SDL_Rect right_screen = {SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_H};

            if (niveau_p1 == 1)
                SDL_BlitSurface(lvl1_img.img, &cam1, screen, &left_screen);
            else
                SDL_BlitSurface(lvl2_img.img, &cam1, screen, &left_screen);

            if (niveau_p2 == 1)
                SDL_BlitSurface(lvl1_img.img, &cam2, screen, &right_screen);
            else
                SDL_BlitSurface(lvl2_img.img, &cam2, screen, &right_screen);

            // Mise à jour de chaque niveau + reset camera si passage au niveau 2
            if (niveau_p1 == 1 && cam1.x + cam1.w >= lvl1_img.img->w) {
                niveau_p1 = 2;
                cam1.x = 0; cam1.y = 0; // retour au début du niveau 2
            }
            if (niveau_p2 == 1 && cam2.x + cam2.w >= lvl1_img.img->w) {
                niveau_p2 = 2;
                cam2.x = 0; cam2.y = 0;
            }
        } else {
            static background bg, bg2;
            static int bg2_charge = 0;
            if (!bg.img) initBack(&bg);

            if (niveau_p1 == 1) {



                scrolling(&bg, direction1, 5, 5);
                afficherBack(bg, screen);
                init_animerBack(&robot);
                
                if (is_end_of_background(&bg)) {
                    niveau_p1 = 2;
                    if (!bg2_charge) {
                        bg2.img = IMG_Load("bg2.jpg");
                        if (!bg2.img) {
                            fprintf(stderr, "Erreur chargement bg2.jpg : %s\n", IMG_GetError());
                            return 1;
                        }
                        bg2.img_pos.x = bg2.img_pos.y = 0;
                        bg2.img_size.x = bg2.img_size.y = 0;
                        bg2.img_size.w = SCREEN_W;
                        bg2.img_size.h = SCREEN_H;
                        bg2.start_time = SDL_GetTicks();
                        bg2_charge = 1;
                    }
                }
            } else {
                scrolling(&bg2, direction1, 5, 5);
                afficherBack(bg2, screen);
            }

            /**update_game_time((niveau_p1 == 1) ? &bg : &bg2, screen, font);*/
        }

        SDL_BlitSurface(iconeGuide, NULL, screen, &posIcone);
        if (afficher_guide) afficherGuideAvecIcone(screen, font);
        afficherTempsGlobal(start_time, screen, font);
        SDL_Flip(screen);
        SDL_Delay(30);
    }

    if (iconeGuide) SDL_FreeSurface(iconeGuide);
    SDL_FreeSurface(lvl1_img.img);
    SDL_FreeSurface(lvl2_img.img);
    TTF_CloseFont(font);
    if (music) Mix_FreeMusic(music);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
