
#ifndef MINIMAP_H
#define MINIMAP_H

#include<stdio.h>
#include<stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

typedef struct
{
	SDL_Color color;
	TTF_Font *police;
	char ch[50];
	SDL_Surface *txt;
	SDL_Rect pos;
} text;

typedef struct
{
	text time;
	SDL_Surface *img; 
	SDL_Rect pos; 
	SDL_Surface *image_perso; 
        SDL_Surface *img_en;
	SDL_Surface *img_bord;
	SDL_Rect pos_perso;
        SDL_Rect pos_en;
	SDL_Rect pos2;
	SDL_Rect poscamera_mini;
	SDL_Rect pos_minimap, pos_board;
        int p;
	int timeS;
} minimap;
typedef struct
{
	SDL_Surface *img[2]; 
	int p;		     
	SDL_Rect pos ;
	
}bouton ;
typedef struct
{
	SDL_Rect pos;
	SDL_Surface *img[7];
	int nbr;
        int p;
}backgroundM;

void InitMinimap(minimap *m);
void AfficheMinimap(SDL_Surface *screen, minimap m);
void annimer_MiniMap(minimap *m);
void initialiser_textmTime(text *t);
int collisionpp(SDL_Rect pos7,SDL_Rect pose6);
int sauvegarder (SDL_Rect pos_p , SDL_Rect b);
int charger (SDL_Rect *pos_p , SDL_Rect *b);
void initialiser_boutonresume(bouton *resume);
//void initialiser_boutonsave(bouton *save);
void initialiser_boutonexit(bouton *exit);
void initialiser_boutonpasue(bouton *pause);
void initialiser_backSousmenu(backgroundM *Sousmenu);
void afficher_btn(SDL_Surface *screen , bouton btn);

#endif

