// fonctions.c
#include"header.h"

void InitMinimap(minimap *m)
{
	m->image_perso = IMG_Load("aziz2.png");
	m->img = IMG_Load("MINIMAP3.png");
	m->pos.x = 0;
	m->pos.y = 0;
	m->pos.h = m->img->h;  
	m->pos.w = m->img->w; 
	m->pos_perso.x = 0;
	m->pos_perso.y = 0;
	initialiser_textmTime(&m->time);
	m->pos2.w = 14936; 
	m->pos2.h = 1200; 
	m->pos2.x = 500; 
	m->pos2.y = 500; 
	m->img_bord = IMG_Load("border.png");
	m->poscamera_mini.w = m->img_bord->w - 30;  
	m->poscamera_mini.h = m->img_bord->h - 30;
	m->poscamera_mini.x = 30;
	m->poscamera_mini.y = 170;
	m->pos_minimap.x = 20;
	m->pos_minimap.y = 185;
	m->pos_board.x = 10;
	m->pos_board.y = 170;
}

void AfficheMinimap(SDL_Surface *screen, minimap m)
{
	SDL_BlitSurface(m.img, &m.poscamera_mini, screen, &m.pos_minimap);
	SDL_BlitSurface(m.img_bord, NULL, screen, &m.pos_board);
	SDL_BlitSurface(m.image_perso, NULL, screen, &m.pos_perso);
	SDL_BlitSurface(m.time.txt, NULL, screen, &m.time.pos);
}

void initialiser_textmTime(text *t)
{
	t->color.r = 255;
	t->color.g = 255;
	t->color.b = 255;
	t->police = TTF_OpenFont("Ubuntu-Bold.ttf", 40); 
	strcpy(t->ch, "00:00");
	t->txt = TTF_RenderText_Blended(t->police, t->ch, t->color); 
	t->pos.x = 1600;
	t->pos.y = 70;
}
void annimer_MiniMap(minimap *m)
{
	int time = SDL_GetTicks() / 1000; 

	int heur = time / 3600;

	int minute = time / 60 - heur * 60;

	int seconde = time - heur * 3600 - minute * 60;

	char h[10], mi[10], s[10];


	sprintf(h, "%d", heur); 
	sprintf(mi, "%d", minute);
	sprintf(s, "%d", seconde);

	if (heur < 10)
		strcpy(m->time.ch, "0");
	strcat(m->time.ch, h);
	strcat(m->time.ch, ":");
	if (minute < 10)
		strcat(m->time.ch, "0");
	strcat(m->time.ch, mi);
	strcat(m->time.ch, ":");
	if (seconde < 10)
		strcat(m->time.ch, "0");
	strcat(m->time.ch, s);


	SDL_FreeSurface(m->time.txt);
	m->time.txt = TTF_RenderText_Blended(m->time.police, m->time.ch, m->time.color);

	int px = (m->pos2.x * 100) / m->pos2.w;
	int py = (m->pos2.y * 100) / m->pos2.h; 


	m->pos_perso.x = (px * m->pos.w) / 100 + m->pos.x;
	m->pos_perso.y = ((py * m->pos.h) / 100 + m->pos.y) + 150;
	m->poscamera_mini.x = (px * m->pos.w) / 100 + m->pos.x;
	m->poscamera_mini.y = ((py * m->pos.h) / 100 + m->pos.y);
}

//tache blanche

int sauvegarder (SDL_Rect pos_p , SDL_Rect b)
{
	FILE *fichier=fopen("sauv.txt" , "w");
	if(fichier !=NULL)
	{
		fprintf(fichier,"%d\t%d\t%d\t%d\t%d",pos_p.x , pos_p.y , b.x , b.y , SDL_GetTicks()/1000);
	}
	fclose(fichier);
}
int charger (SDL_Rect *pos_p , SDL_Rect *b)
{
	int x_p;
	int y_p;
	int x_b;
	int y_b;
	int timeS;
	FILE *fichier=fopen("sauv.txt" , "r");
	if(fichier!=NULL)
	{
		fscanf(fichier , "%d\t%d\t%d\t%d\t%d",&x_p , &y_p , &x_b , &y_b , &timeS);
		pos_p->x=x_p;
		pos_p->y=y_p;
		b->x=x_b;
		b->y=y_b;
		
	}
	return timeS;
}
int collisionpp(SDL_Rect pos7,SDL_Rect pose6)
{
        if((pose6.x+pose6.w < pos7.x) || (pose6.x > pos7.x+pos7.w) || (pose6.y+pose6.h < pos7.y) || (pose6.y > pos7.y+pos7.h))
	{
		return 0;
	}  
	else
	{
		return 1;
	}

}

	
void initialiser_boutonresume(bouton *resume)
{
	resume->img[1]=IMG_Load("Gaia_ResumeButton2.png");
	resume->img[0]=IMG_Load("Gaia_ResumeButton1.png");
	resume->pos.x=740;
	resume->pos.y=480;
	resume->pos.w=resume->img[0]->w;
	resume->pos.h=resume->img[0]->h;
	resume->p=0; // non selectionne 
}

void initialiser_boutonexit(bouton *exit)
{
	exit->img[0]=IMG_Load("Gaia_ExitButton1.png");
	exit->img[1]=IMG_Load("Gaia_ExitButton2.png");
	exit->pos.x=740;
	exit->pos.y=620;
	exit->pos.w=exit->img[0]->w;
	exit->pos.h=exit->img[0]->h;
	exit->p=0;
}
void initialiser_boutonpasue(bouton *pause)
{
	pause->img[0]=IMG_Load("Gaia_Pause_Button.png");
	pause->img[1]=IMG_Load("Gaia_Pause_Button.png");
	pause->pos.x=1400;
	pause->pos.y=50;
	pause->pos.w=pause->img[0]->w;
	pause->pos.h=pause->img[0]->h;
	pause->p=0;
}
	//BACKGROUND
void initialiser_backSousmenu(backgroundM *Sousmenu)
{
	Sousmenu->img[0]=IMG_Load("Gaia_Pause_Screen.png");
	Sousmenu->pos.x=600;
	Sousmenu->pos.y=300;
	Sousmenu->pos.h=Sousmenu->img[0]->h;
	Sousmenu->pos.w=Sousmenu->img[0]->w;
	Sousmenu->nbr=1;
	Sousmenu->p=0;
}
void afficher_btn(SDL_Surface *screen , bouton btn)
{
	SDL_BlitSurface(btn.img[btn.p] , NULL , screen , &btn.pos);
}


