#include "enigme.h"
#include <SDL/SDL.h>
#include <time.h>
void init_timer(enigme *e) {
e->timer_start=SDL_GetTicks();
e->timer_duration=30000;
e->num_animation=0;
e->time_over=0;
}
int check_timer(enigme *e) {
Uint32 current_time=SDL_GetTicks();
Uint32 elapsed=current_time-e->timer_start;
if(elapsed>=e->timer_duration) {
e->time_over=1;
return 1;
}
int frame=(elapsed*12)/e->timer_duration;
if(frame>=12) frame=11;
e->num_animation=frame;
return 0;
}
void generer_enigme(enigme *e){
e->pos_selected=0;
e->background=IMG_Load("img/background.png");
e->button1_img=IMG_Load("/home/user/Desktop/enigme texte (1)/button1.png");
e->button2_img=IMG_Load("/home/user/Desktop/enigme texte (1)/button2.png");
e->pos_timer.x=772;e->pos_timer.y=50;
for(int i=0;i<12;i++){char f[20];sprintf(f,"timer%d.png",i);e->timer[i]=IMG_Load(f);}
TTF_Init();
TTF_Font *police=TTF_OpenFont("/home/user/Desktop/enigme texte (1)/Nasalization Rg.otf",45);
TTF_Font *police1=TTF_OpenFont("/home/user/Desktop/enigme texte (1)/Nasalization Rg.otf",35);
SDL_Color couleur={225,225,225,225};
char questionn[300];
srand(time(NULL));
e->num_question=rand()%4;
while(e->num_question==0){srand(time(NULL));e->num_question=rand()%4;}
FILE *fquestion=fopen("questions.txt","r");
if(fquestion){int t=1;while(fgets(questionn,300,fquestion)&&(t!=e->num_question))t++;fclose(fquestion);}
char reponse[50];
int min,max;
switch(e->num_question){
case 1:{min=0;max=2;break;}
case 2:{min=3;max=5;break;}
case 3:{min=6;max=8;break;}}
FILE *freponse=fopen("reponses.txt","r");
if(freponse){int t=0;while(fgets(reponse,50,freponse)&&(t<max)){if(t>=min)e->reponses[t-min]=TTF_RenderText_Blended(police1,reponse,couleur);t++;}fclose(freponse);}
FILE *fvraireponse=fopen("vraireponses.txt","r");
if(fvraireponse){int t=1;while(fgets(reponse,50,fvraireponse)){if(t==e->num_question){printf("%s\n",reponse);e->reponses[2]=TTF_RenderText_Blended(police1,reponse,couleur);}t++;}fclose(fvraireponse);}
srand(time(NULL));e->positionVraiReponse=rand()%3;
while(e->positionVraiReponse==0){srand(time(NULL));e->positionVraiReponse=rand()%3;}
printf("%d\n",e->positionVraiReponse);
e->question=TTF_RenderText_Blended(police,questionn,couleur);
e->pos_question.x=50;e->pos_question.y=300;
e->pos_reponse1.x=150;e->pos_reponse1.y=400;
e->pos_reponse2.x=450;e->pos_reponse2.y=400;
e->pos_reponse3.x=750;e->pos_reponse3.y=400;
e->pos_reponse1txt.x=200;e->pos_reponse1txt.y=410;
e->pos_reponse2txt.x=500;e->pos_reponse2txt.y=410;
e->pos_reponse3txt.x=800;e->pos_reponse3txt.y=410;
Mix_AllocateChannels(20);
SDL_WM_SetCaption("Enigme",NULL);
if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)==-1){printf("Mix_OpenAudio: %s\n",Mix_GetError());}
e->sound=Mix_LoadWAV("clic.wav");
Mix_VolumeMusic(MIX_MAX_VOLUME);
init_timer(e);
}
void afficher_enigme(enigme *e,SDL_Surface *ecran){
switch(e->positionVraiReponse){
case 1:{
SDL_BlitSurface(e->reponses[2],NULL,ecran,&e->pos_reponse1txt);
SDL_BlitSurface(e->reponses[0],NULL,ecran,&e->pos_reponse2txt);
SDL_BlitSurface(e->reponses[1],NULL,ecran,&e->pos_reponse3txt);
break;}
case 2:{
SDL_BlitSurface(e->reponses[0],NULL,ecran,&e->pos_reponse1txt);
SDL_BlitSurface(e->reponses[2],NULL,ecran,&e->pos_reponse2txt);
SDL_BlitSurface(e->reponses[1],NULL,ecran,&e->pos_reponse3txt);
break;}
case 3:{
SDL_BlitSurface(e->reponses[0],NULL,ecran,&e->pos_reponse1txt);
SDL_BlitSurface(e->reponses[1],NULL,ecran,&e->pos_reponse2txt);
SDL_BlitSurface(e->reponses[2],NULL,ecran,&e->pos_reponse3txt);
break;}}
}
void verify_enigme(enigme *e,SDL_Surface *ecran){
SDL_Rect pos={160,330};
if(e->positionVraiReponse==e->pos_selected){
SDL_Surface *win=IMG_Load("/home/user/Desktop/enigme texte (1)/youwin.png");
SDL_BlitSurface(win,NULL,ecran,&pos);
SDL_Flip(ecran);}
else if(e->pos_selected==-1){
SDL_Surface *lost=IMG_Load("/home/user/Desktop/enigme texte (1)/youlost.png");
SDL_BlitSurface(lost,NULL,ecran,&pos);
SDL_Flip(ecran);}
else{
SDL_Surface *lost=IMG_Load("/home/user/Desktop/enigme texte (1)/youlost.png");
SDL_BlitSurface(lost,NULL,ecran,&pos);
SDL_Flip(ecran);}
SDL_Delay(2000);
}

