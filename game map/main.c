#include "header.h"

int main() {
    int stage = 1;
    int sousMenu = 0;
    int boucle = 1;
    SDL_Event event;
    SDL_Surface *screen;
    int isPaused = 0; 

    minimap m;
    int colision = 0;
    SDL_Surface *img_p = IMG_Load("aziz1.png");
    SDL_Rect pos_p;
    SDL_Rect pos4;
    SDL_Rect posCamera;
    pos_p.x = 500;
    pos_p.y = 750;
    pos4.x = 0;
    pos4.y = 0;
    SDL_Surface *img_ms = NULL;
    bouton pause, exite, save, resume;
    backgroundM backM;
    Mix_Chunk *music;
    //
      if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    Mix_Music *musi;
    musi = Mix_LoadMUS("Dreamcatcher.mp3");
    Mix_PlayMusic(musi, -1);

   
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init(); 
    srand(time(NULL));
    screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_SRCALPHA);
    InitMinimap(&m);
    SDL_Surface *image_background = IMG_Load("bg111.png");
    SDL_Surface *test = IMG_Load("Gaia_Health_Bar.png");

 
    initialiser_boutonresume(&resume);
   // initialiser_boutonsave(&save);
    initialiser_boutonexit(&exite);
    initialiser_boutonpasue(&pause);
    initialiser_backSousmenu(&backM);
    music = Mix_LoadWAV("BoutonClick.wav");
    SDL_Surface *masque = IMG_Load("Tree.png");
    SDL_Surface *img_tree2 = IMG_Load("Tree.png");
    SDL_Rect pos_mas;
    pos_mas.x = 900;
    pos_mas.y = 640;
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    posCamera.x = 20;
    posCamera.y = 400;
    posCamera.h = 1080;
    posCamera.w = 1920;

    while (boucle) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    boucle = 0;
                   sauvegarder(pos_p , pos_mas);
                    break;
                case SDL_KEYDOWN:
                     if (stage == 1 && isPaused==0 && !collisionpp(pos_p, pos_mas )) {
                        if (event.key.keysym.sym == SDLK_RIGHT) {
                            pos_p.x += 40;
                            m.pos2.x = pos_p.x;
                        } else if (event.key.keysym.sym == SDLK_LEFT) {
                            pos_p.x -= 40;
                            m.pos2.x = pos_p.x;
                        } else if (event.key.keysym.sym == SDLK_UP) {
                            pos_p.y -= 40;
                            m.pos.y -= 5;
                        } else if (event.key.keysym.sym == SDLK_DOWN) {
                            pos_p.y += 40;
                            m.pos.y += 5;
                        } else if (event.key.keysym.sym == SDLK_y) {
                           m.timeS=charger(&pos_p , &pos_mas) - SDL_GetTicks()/1000 ;
                           sauvegarder(pos_p , pos_mas);
                        }
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (stage == 1 ) {
                        if (event.motion.x > pause.pos.x && event.motion.x < pause.pos.x + pause.pos.w &&
                            event.motion.y > pause.pos.y && event.motion.y < pause.pos.y + pause.pos.h) {
                            
                            pause.p = 1;
                            Mix_PlayChannel(-1, music, 0);
                        } else {
                            pause.p = 0;
                        }
                    } else if (sousMenu == 1) {
                        if (event.motion.x > resume.pos.x && event.motion.x < resume.pos.x + resume.pos.w &&
                            event.motion.y > resume.pos.y && event.motion.y < resume.pos.y + resume.pos.h) {
                            resume.p = 1;
               
                            Mix_PlayChannel(-1, music, 0);
                        } else if (event.motion.x > exite.pos.x && event.motion.x < exite.pos.x + exite.pos.w &&
                                   event.motion.y > exite.pos.y && event.motion.y < exite.pos.y + exite.pos.h) {
                            exite.p = 1;
                            Mix_PlayChannel(-1, music, 0);
                      /*  } else if (event.motion.x > save.pos.x && event.motion.x < save.pos.x + save.pos.w &&
                                   event.motion.y > save.pos.y && event.motion.y < save.pos.y + save.pos.h) {
                            save.p = 1;
               
                            Mix_PlayChannel(-1, music, 0);*/
                        } else {
                           // save.p = 0;
                            exite.p = 0;
                            resume.p = 0;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (stage == 1 && !isPaused ) {
                        if (event.motion.x > pause.pos.x && event.motion.x < pause.pos.x + pause.pos.w &&
                            event.motion.y > pause.pos.y && event.motion.y < pause.pos.y + pause.pos.h) {
                            stage = 0;
                            sousMenu = 1;
                            isPaused=1;
                             m.timeS=charger(&pos_p , &pos_mas) - SDL_GetTicks()/1000 ;
                          
                        }
                    } else if (sousMenu == 1) {
                        if (event.motion.x > resume.pos.x && event.motion.x < resume.pos.x + resume.pos.w &&
                            event.motion.y > resume.pos.y && event.motion.y < resume.pos.y + resume.pos.h) {
                            stage = 1;
                            sousMenu = 0;
                            isPaused=0;
                        } else if (event.motion.x > exite.pos.x && event.motion.x < exite.pos.x + exite.pos.w &&
                                   event.motion.y > exite.pos.y && event.motion.y < exite.pos.y + exite.pos.h) {
                            boucle = 0;
                       /* } else if (event.motion.x > save.pos.x && event.motion.x < save.pos.x + save.pos.w &&
                                   event.motion.y > save.pos.y && event.motion.y < save.pos.y + save.pos.h) {*/
                            sauvegarder(pos_p , pos_mas);
                           
                            
                        }
                    }
                    break;
              //yeah
            }
        }

       
        if (!isPaused) {
        annimer_MiniMap(&m);
        colision = collisionpp(pos_p, pos_mas);
    }
       
        colision = collisionpp(pos_p, pos_mas);

        if (colision == 1) {
           
            if (event.key.keysym.sym == SDLK_RIGHT) {
                pos_p.x -= 35;
                m.pos2.x = pos_p.x;
            } else if (event.key.keysym.sym == SDLK_LEFT) {
                pos_p.x += 35;
                m.pos2.x = pos_p.x;
            } else if (event.key.keysym.sym == SDLK_UP) {
                pos_p.y += 35;
                m.pos.y = m.pos.y + 5;
            } else if (event.key.keysym.sym == SDLK_DOWN) {
                pos_p.y -= 35;
                m.pos.y = m.pos.y - 5;
            }
        }


        
          if (colision == 1) {
            img_ms = img_tree2; 
        } else {
            img_ms = masque; 
        }

        
        SDL_BlitSurface(image_background, &posCamera, screen, NULL);
        SDL_BlitSurface(test, NULL, screen, &pos4);
        AfficheMinimap(screen, m);
        SDL_BlitSurface(img_p, NULL, screen, &pos_p);
        SDL_BlitSurface(img_ms, NULL, screen, &pos_mas); 

        if (stage == 1) {
            afficher_btn(screen, pause);
        } else if (sousMenu == 1) {
            SDL_BlitSurface(backM.img[0], NULL, screen, &backM.pos);
            afficher_btn(screen, resume);
            //afficher_btn(screen, save);
            afficher_btn(screen, exite);
        }

       
        SDL_Flip(screen);
    }
    

    
    SDL_FreeSurface(image_background);
    SDL_FreeSurface(img_p);
    SDL_FreeSurface(masque);
    SDL_FreeSurface(img_tree2); 
    SDL_FreeSurface(m.img);
    SDL_FreeSurface(m.image_perso);
    Mix_FreeChunk(music);
    Mix_FreeMusic(musi);
    TTF_Quit(); 
    SDL_Quit();
    return 0;
}


