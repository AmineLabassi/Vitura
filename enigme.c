/**
 * @file filename.c
 * @brief Brief description
 * @author Your Name
 * @version 0.1
 * @date 2023-11-20
 * 
 * Detailed description
 */
#include "enigme.h"
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <time.h>
#include <math.h>
void init_timer(enigme *e) {
    e->timer_start = SDL_GetTicks();
    e->timer_duration = 30000;
    e->num_animation = 0;
    e->time_over = 0;
}

int check_timer(enigme *e) {
    Uint32 current_time = SDL_GetTicks();
    Uint32 elapsed = current_time - e->timer_start;
    
    if(elapsed >= (Uint32)e->timer_duration) {
        e->time_over = 1;
        return 1;
    }
    
    int frame = (elapsed * 12) / e->timer_duration;
    if(frame >= 12) frame = 11;
    e->num_animation = frame;
    return 0;
}

void generer_enigme(enigme *e) {
    // Initialisation
    e->pos_selected = 0;
    e->background = IMG_Load("/home/user/Desktop/enigme texte (1)/MENU2.png");
    e->button1_img = IMG_Load("/home/user/Desktop/enigme texte (1)/button1.png");
    e->button2_img = IMG_Load("/home/user/Desktop/enigme texte (1)/button2.png");
    
    // Position timer
    e->pos_timer.x = 772;
    e->pos_timer.y = 50;
    
    // Chargement images timer
    for(int i = 0; i < 12; i++) {
        char f[20];
        sprintf(f, "timer%d.png", i);
        e->timer[i] = IMG_Load(f);
    }
    
    // Initialisation polices
    TTF_Init();
    TTF_Font *police = TTF_OpenFont("/home/user/Desktop/enigme texte (1)/Nasalization Rg.otf", 45);
    TTF_Font *police1 = TTF_OpenFont("/home/user/Desktop/enigme texte (1)/Nasalization Rg.otf", 35);
    SDL_Color couleur = {225, 225, 225, 225};
    
    // Sélection question aléatoire
    char questionn[300];
    srand(time(NULL));
    e->num_question = rand() % 4;
    while(e->num_question == 0) {
        srand(time(NULL));
        e->num_question = rand() % 4;
    }
    
    // Lecture question
    FILE *fquestion = fopen("questions.txt", "r");
    if(fquestion) {
        int t = 1;
        while(fgets(questionn, 300, fquestion) && (t != e->num_question))
            t++;
        fclose(fquestion);
    }
    
    // Détermination plage réponses
    char reponse[50];
    int min, max;
    switch(e->num_question) {
        case 1: {min = 0; max = 2; break;}
        case 2: {min = 3; max = 5; break;}
        case 3: {min = 6; max = 8; break;}
    }
    
    // Lecture réponses
    FILE *freponse = fopen("reponses.txt", "r");
    if(freponse) {
        int t = 0;
        while(fgets(reponse, 50, freponse) && (t < max)) {
            if(t >= min)
                e->reponses[t-min] = TTF_RenderText_Blended(police1, reponse, couleur);
            t++;
        }
        fclose(freponse);
    }
    
    // Lecture bonne réponse
    FILE *fvraireponse = fopen("vraireponses.txt", "r");
    if(fvraireponse) {
        int t = 1;
        while(fgets(reponse, 50, fvraireponse)) {
            if(t == e->num_question) {
                printf("%s\n", reponse);
                e->reponses[2] = TTF_RenderText_Blended(police1, reponse, couleur);
            }
            t++;
        }
        fclose(fvraireponse);
    }
    
    // Position aléatoire bonne réponse
    srand(time(NULL));
    e->positionVraiReponse = rand() % 3;
    while(e->positionVraiReponse == 0) {
        srand(time(NULL));
        e->positionVraiReponse = rand() % 3;
    }
    printf("%d\n", e->positionVraiReponse);
    
    // Préparation affichage
    e->question = TTF_RenderText_Blended(police, questionn, couleur);
    e->pos_question.x = 50; e->pos_question.y = 300;
    e->pos_reponse1.x = 150; e->pos_reponse1.y = 400;
    e->pos_reponse2.x = 450; e->pos_reponse2.y = 400;
    e->pos_reponse3.x = 750; e->pos_reponse3.y = 400;
    e->pos_reponse1txt.x = 200; e->pos_reponse1txt.y = 410;
    e->pos_reponse2txt.x = 500; e->pos_reponse2txt.y = 410;
    e->pos_reponse3txt.x = 800; e->pos_reponse3txt.y = 410;
    
    // Initialisation audio
    Mix_AllocateChannels(20);
    SDL_WM_SetCaption("Enigme", NULL);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
    }
    e->sound = Mix_LoadWAV("clic.wav");
    Mix_VolumeMusic(MIX_MAX_VOLUME);
    
    init_timer(e);
}

void afficher_enigme(enigme *e, SDL_Surface *ecran) {
    switch(e->positionVraiReponse) {
        case 1: {
            SDL_BlitSurface(e->reponses[2], NULL, ecran, &e->pos_reponse1txt);
            SDL_BlitSurface(e->reponses[0], NULL, ecran, &e->pos_reponse2txt);
            SDL_BlitSurface(e->reponses[1], NULL, ecran, &e->pos_reponse3txt);
            break;
        }
        case 2: {
            SDL_BlitSurface(e->reponses[0], NULL, ecran, &e->pos_reponse1txt);
            SDL_BlitSurface(e->reponses[2], NULL, ecran, &e->pos_reponse2txt);
            SDL_BlitSurface(e->reponses[1], NULL, ecran, &e->pos_reponse3txt);
            break;
        }
        case 3: {
            SDL_BlitSurface(e->reponses[0], NULL, ecran, &e->pos_reponse1txt);
            SDL_BlitSurface(e->reponses[1], NULL, ecran, &e->pos_reponse2txt);
            SDL_BlitSurface(e->reponses[2], NULL, ecran, &e->pos_reponse3txt);
            break;
        }
    }
}

void verify_enigme(enigme *e, SDL_Surface *ecran) {
    const Uint32 DURATION = 2000; // 2 seconds
    Uint32 start_time = SDL_GetTicks();
    
    // Load result image - make sure these files exist!
    const char* image_path = (e->positionVraiReponse == e->pos_selected) ? 
        "youwin.png" : "youlost.png";
    
    SDL_Surface* original = IMG_Load(image_path);
    if (!original) {
        printf("Error loading image %s: %s\n", image_path, IMG_GetError());
        return;
    }

    // Main animation loop
    while ((SDL_GetTicks() - start_time) < DURATION) {
        float progress = (float)(SDL_GetTicks() - start_time) / DURATION;
        
        // More dramatic zoom (0.2 to 1.5)
        float zoom = 0.2f + progress * 1.0f;
        
        // Faster rotation (0 to 720 degrees)
        float angle = progress * 720.0f;
        
        // Create transformed surface
        SDL_Surface* rotated = rotozoomSurface(original, angle, zoom, SMOOTHING_ON);
        if (!rotated) {
            printf("Rotation failed!\n");
            break;
        }
        
        // Clear screen with black
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        
        // Center the image
        SDL_Rect dst = {
            (ecran->w - rotated->w)/2,
            (ecran->h - rotated->h)/2,
            rotated->w,
            rotated->h
        };
        
        SDL_BlitSurface(rotated, NULL, ecran, &dst);
        SDL_Flip(ecran);
        
        SDL_FreeSurface(rotated);
        SDL_Delay(16);
    }
    
    SDL_FreeSurface(original);
    SDL_Delay(500);
}
