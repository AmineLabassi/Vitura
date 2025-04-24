#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "enigme.h"
#include <string.h>
int main(){
SDL_Surface *ecran=SDL_SetVideoMode(1129,900,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)==-1){printf("SDL_Init: %s\n",SDL_GetError());return 1;}
if(TTF_Init()==-1){printf("TTF_Init: %s\n",TTF_GetError());return 1;}
if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)==-1){printf("Mix_OpenAudio: %s\n",Mix_GetError());return 1;}
int continuer=1;
SDL_Event event;
enigme e;
SDL_Surface *background=IMG_Load("/home/user/Desktop/enigme texte (1)/MENU2.png");
generer_enigme(&e);
SDL_Surface *bouton1=e.button1_img,*bouton2=e.button1_img,*bouton3=e.button1_img;
const int FPS=30;
const int frame_delay=1000/FPS;
while(continuer){
Uint32 frame_start=SDL_GetTicks();
if(check_timer(&e)){
e.pos_selected=-1;
verify_enigme(&e,ecran);
generer_enigme(&e);}
while(SDL_PollEvent(&event)){
switch(event.type){
case SDL_KEYDOWN:
if(event.key.keysym.sym==SDLK_ESCAPE)continuer=0;
break;
case SDL_MOUSEBUTTONDOWN:
if(event.button.button==SDL_BUTTON_LEFT){
if(event.button.x>=150&&event.button.x<=350&&event.button.y>=400&&event.button.y<=480){
e.pos_selected=1;
Mix_PlayChannel(2,e.sound,0);
verify_enigme(&e,ecran);
generer_enigme(&e);}
else if(event.button.x>=450&&event.button.x<=650&&event.button.y>=400&&event.button.y<=480){
e.pos_selected=2;
Mix_PlayChannel(2,e.sound,0);
verify_enigme(&e,ecran);
generer_enigme(&e);}
else if(event.button.x>=750&&event.button.x<=950&&event.button.y>=400&&event.button.y<=480){
e.pos_selected=3;
Mix_PlayChannel(2,e.sound,0);
verify_enigme(&e,ecran);
generer_enigme(&e);}}
break;
case SDL_MOUSEMOTION:
if(event.motion.x>=150&&event.motion.x<=350&&event.motion.y>=400&&event.motion.y<=480){
bouton1=e.button2_img;bouton2=e.button1_img;bouton3=e.button1_img;}
else if(event.motion.x>=450&&event.motion.x<=650&&event.motion.y>=400&&event.motion.y<=480){
bouton1=e.button1_img;bouton2=e.button2_img;bouton3=e.button1_img;}
else if(event.motion.x>=750&&event.motion.x<=950&&event.motion.y>=400&&event.motion.y<=480){
bouton1=e.button1_img;bouton2=e.button1_img;bouton3=e.button2_img;}
else{bouton1=e.button1_img;bouton2=e.button1_img;bouton3=e.button1_img;}
break;}}
SDL_FillRect(ecran,NULL,0);
SDL_BlitSurface(background,NULL,ecran,NULL);
SDL_BlitSurface(e.question,NULL,ecran,&e.pos_question);
SDL_BlitSurface(e.timer[e.num_animation],NULL,ecran,&e.pos_timer);
SDL_BlitSurface(bouton1,NULL,ecran,&e.pos_reponse1);
SDL_BlitSurface(bouton2,NULL,ecran,&e.pos_reponse2);
SDL_BlitSurface(bouton3,NULL,ecran,&e.pos_reponse3);
afficher_enigme(&e,ecran);
SDL_Flip(ecran);
Uint32 frame_time=SDL_GetTicks()-frame_start;
if(frame_time<frame_delay)SDL_Delay(frame_delay-frame_time);}
SDL_FreeSurface(background);
SDL_Quit();
return 0;}
