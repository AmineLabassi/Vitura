#ifndef perso_H_INCLUDED  
#define perso_H_INCLUDED

#include <stdio.h>  
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h> 

typedef struct struct_text{
 TTF_Font *font;
 SDL_Color color;
 SDL_Surface* text;
 SDL_Rect postext;
}Text;
typedef struct {  

	SDL_Surface *imagePers;//image
	SDL_Rect position;

	SDL_Rect frame; 
	int curframe;
        SDL_Surface *imagec;
	SDL_Rect positionc;
        int nbcoeur;
        Text vie;
	int direction; 
	Text score; 
	double acceleration; 
	double vitesse;   
	double v_x;
	double v_grav ;
	double v_saut ;
	double v_y ;  
        int Vscore;

	
}Personne;


void initPerso(Personne *p);  
void initPerso2(Personne *p);  
void afficherPerso (Personne p,SDL_Surface *screen);
void afficherPerso2(Personne p,SDL_Surface *screen);
void movePerso(Personne *p ,Uint32 dt);
void animerPerso(Personne *p);
void sautdroit(Personne *p);


void sautgauche(Personne *p);



#endif
