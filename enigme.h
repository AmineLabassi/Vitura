#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <math.h>  // Added for animation math

typedef struct {
    SDL_Surface *background,*question,*reponses[4],*button,*button_s,*button1_img,*button2_img;
    int pos_selected,num_question,vrai_reponse,positionVraiReponse,num_animation,time_over;
    SDL_Rect pos_question,pos_reponse1,pos_reponse2,pos_reponse3,pos_reponse1txt,pos_reponse2txt,pos_reponse3txt,pos_timer;
    Mix_Chunk *sound;
    SDL_Surface *timer[12];
    Uint32 timer_start;
    int timer_duration;
    float anim_angle;  // For rotation animation
    float anim_scale;  // For scale animation
    float rotation_angle;
} enigme;

void generer_enigme(enigme *e);
void afficher_enigme(enigme *e,SDL_Surface *ecran);
void verify_enigme(enigme *e,SDL_Surface *ecran);
void init_timer(enigme *e);
int check_timer(enigme *e);
#endif
