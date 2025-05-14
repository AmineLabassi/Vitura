#include"header.h"
int main()
{

	int boucle=1;
       SDL_Event event ;
	SDL_Surface *screen;
	minimap m;
        int colision = 0; 
	SDL_Surface *img_p = IMG_Load("aziz1.png");
	SDL_Rect pos_p; 
        SDL_Rect pos4;
        SDL_Rect posCamera;
       pos_p.x=500 ;
       pos_p.y=750;
       pos4.x=0;
       pos4.y=0;
       SDL_Surface *img_ms = NULL;
        
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    Mix_Music *music;
    music = Mix_LoadMUS("Dreamcatcher.mp3");
    Mix_PlayMusic(music, -1);
	screen = SDL_SetVideoMode(1920 , 1080 , 32 , SDL_HWSURFACE|SDL_SRCALPHA);
        TTF_Init();
        InitMinimap(&m);
	SDL_Surface *image_background = IMG_Load("Gaia_s_Revival_Level_1.png"), *test=IMG_Load("Gaia_Health_Bar.png");
        //
        SDL_Surface *masque=IMG_Load("Tree.png");
        SDL_Rect pos_mas ; pos_mas.x=900 ; pos_mas.y=640;
	SDL_Rect pos ; pos.x=0 ; pos.y=0; posCamera.x=20; posCamera.y=400; posCamera.h=1080; posCamera.w=1920;
       

	while(boucle==1)
	{
	
		
		SDL_BlitSurface(image_background , &posCamera , screen , &pos);	
		SDL_BlitSurface(test , NULL , screen , &pos4);
                  	
		SDL_BlitSurface(img_p , NULL , screen , &pos_p);
                SDL_BlitSurface(masque , NULL , screen , &pos_mas);	
                AfficheMinimap(screen , m);
		SDL_Flip(screen);
		//LECTEUR D'EVENNEMENT

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					boucle=0;
                                        sauvegarder(pos_p , pos_mas);
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE)
						boucle=0;
					if(event.key.keysym.sym == SDLK_RIGHT)
					{
						pos_p.x+=40;
						m.pos2.x=pos_p.x;
					}
					else if(event.key.keysym.sym == SDLK_LEFT)
					{
						pos_p.x-=40;
						m.pos2.x=pos_p.x;
					}
					else if(event.key.keysym.sym == SDLK_UP)
					{
						pos_p.y-=40;
						m.pos.y=m.pos.y-5;
					}
					else if(event.key.keysym.sym == SDLK_DOWN)
					{
						pos_p.y+=40;
						m.pos.y=m.pos.y+5;
					}
					else if(event.key.keysym.sym == SDLK_y)
					{
						charger(&pos_p , &pos_mas);
					}
					break;
			}
                      
		}
		
		annimer_MiniMap(&m);
                colision = collisionBb(pos_p, pos_mas);
                if (colision == 1)
        {
            img_ms = IMG_Load("Tree_2.png");
            SDL_Rect pos_ms;
            pos_ms.x = 900;
            pos_ms.y = 640;
        }

               
                 
                 
                /*if(printPixelColors(pos_p , masque)==1)
		{
			pos_p.x=0;
			pos_p.y=500;
		}*/
    
                SDL_Flip(screen);
		
	}
	SDL_FreeSurface(image_background) ;
	SDL_FreeSurface(img_p);
        SDL_FreeSurface(masque);
        SDL_FreeSurface(img_ms);
	SDL_FreeSurface(m.img);
	SDL_FreeSurface(m.image_perso);
        TTF_Quit();
        SDL_FreeSurface(screen);
        Mix_FreeMusic(music);
        
        
	
}
///LE MAIN.C DE SOUS MENU
#include"header.h"
int main()
{
         
        //variable d'etat
	int stage = 1;
	int sousMenu=0;
	int boucle=1;
       SDL_Event event ;
	SDL_Surface *screen;
	minimap m;
        int colision = 0; 
	SDL_Surface *img_p = IMG_Load("aziz1.png");
	SDL_Rect pos_p; 
        SDL_Rect pos4;
        SDL_Rect posCamera;
       pos_p.x=500 ;
       pos_p.y=750;
       pos4.x=0;
       pos4.y=0;
       SDL_Surface *img_ms = NULL;
       //bouton SousMenu
	bouton pause , exite , save , resume;
	backgroundM backM;
	Mix_Chunk *music;

        Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
        TTF_Init();
	srand(time(NULL));
	screen = SDL_SetVideoMode(1920 , 1080 , 32 , SDL_HWSURFACE|SDL_SRCALPHA);
        InitMinimap(&m);
	SDL_Surface *image_background = IMG_Load("Gaia_s_Revival_Level_1.png"), *test=IMG_Load("Gaia_Health_Bar.png");
        
        //
        initialiser_boutonresume(&resume);
	initialiser_boutonsave(&save);
	initialiser_boutonexit(&exite);
	initialiser_boutonpasue(&pause);
	initialiser_backSousmenu(&backM);
	music=Mix_LoadWAV("BoutonClick.wav");
        SDL_Surface *masque=IMG_Load("Tree.png");
        SDL_Rect pos_mas ; pos_mas.x=900 ; pos_mas.y=640;
	SDL_Rect pos ; pos.x=0 ; pos.y=0; posCamera.x=20; posCamera.y=400; posCamera.h=1080; posCamera.w=1920;


	while(boucle==1)
	{
                /*****AFFICHAGE****/
		if(stage == 1)
		{
                        
			SDL_BlitSurface(image_background , &posCamera , screen , &pos);	
			AfficheMinimap(screen , m);
                        SDL_BlitSurface(img_p , NULL , screen , &pos_p);
			SDL_BlitSurface(test , NULL , screen , &pos4);
                        SDL_BlitSurface(masque , NULL , screen , &pos_mas);	
			afficher_btn(screen , pause);
		}
		else if(sousMenu == 1)
		{
			SDL_BlitSurface(backM.img[0] , NULL , screen , &backM.pos);	
			afficher_btn(screen , resume);
			afficher_btn(screen , save);
			afficher_btn(screen , exite);
			
		}
                
                SDL_Flip(screen);
		


		//LECTEUR D'EVENNEMENT
                 while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
             
            case SDL_QUIT:
                boucle = 0;
                sauvegarder(pos_p, pos_mas);
               
                break;
            case SDL_KEYDOWN:
                if (stage == 1 && colision == 0)
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        boucle = 0;
                    if (event.key.keysym.sym == SDLK_RIGHT)
                    {
                        pos_p.x += 40;
                        m.pos2.x = pos_p.x;
                    }
                    else if (event.key.keysym.sym == SDLK_LEFT)
                    {
                        pos_p.x -= 40;
                        m.pos2.x = pos_p.x;
                    }
                    else if (event.key.keysym.sym == SDLK_UP)
                    {
                        pos_p.y -= 40;
                        m.pos.y = m.pos.y - 5;
                    }
                    else if (event.key.keysym.sym == SDLK_DOWN)
                    {
                        pos_p.y += 40;
                        m.pos.y = m.pos.y + 5;
                    }
                    else if (event.key.keysym.sym == SDLK_y)
                    {
                        m.timeS = charger(&pos_p, &pos_mas) - SDL_GetTicks() / 1000;
                    }
                }
                break;
             colision = collisionpp(pos_p, pos_mas);
            case SDL_MOUSEMOTION:
                if (stage == 1)
                {
                    if (event.motion.x > pause.pos.x && event.motion.x < pause.pos.x + pause.pos.w &&
                        event.motion.y > pause.pos.y && event.motion.y < pause.pos.y + pause.pos.h)
                    {
                        pause.p = 1;
                        Mix_PlayChannel(-1, music, 0);
                    }
                    else
                    {
                        pause.p = 0;
                    }
                }
                else if (sousMenu == 1)
                {
                    if (event.motion.x > resume.pos.x && event.motion.x < resume.pos.x + resume.pos.w &&
                        event.motion.y > resume.pos.y && event.motion.y < resume.pos.y + resume.pos.h)
                    {
                        resume.p = 1;
                        Mix_PlayChannel(-1, music, 0);
                    }
                    else if (event.motion.x > exite.pos.x && event.motion.x < exite.pos.x + exite.pos.w &&
                             event.motion.y > exite.pos.y && event.motion.y < exite.pos.y + exite.pos.h)
                    {
                        exite.p = 1;
                        Mix_PlayChannel(-1, music, 0);
                    }
                    else if (event.motion.x > save.pos.x && event.motion.x < save.pos.x + save.pos.w &&
                             event.motion.y > save.pos.y && event.motion.y < save.pos.y + save.pos.h)
                    {
                        save.p = 1;
                        Mix_PlayChannel(-1, music, 0);
                    }
                    else
                    {
                        save.p = 0;
                        exite.p = 0;
                        resume.p = 0;
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (stage == 1)
                {
                    if (event.motion.x > pause.pos.x && event.motion.x < pause.pos.x + pause.pos.w &&
                        event.motion.y > pause.pos.y && event.motion.y < pause.pos.y + pause.pos.h)
                    {
                        stage = 0;
                        sousMenu = 1;
                    }
                }
                else if (sousMenu == 1)
                {
                    if (event.motion.x > resume.pos.x && event.motion.x < resume.pos.x + resume.pos.w &&
                        event.motion.y > resume.pos.y && event.motion.y < resume.pos.y + resume.pos.h)
                    {
                        stage = 1;
                        sousMenu = 0;
                    }
                    else if (event.motion.x > exite.pos.x && event.motion.x < exite.pos.x + exite.pos.w &&
                             event.motion.y > exite.pos.y && event.motion.y < exite.pos.y + exite.pos.h)
                    {
                        boucle = 0;
                    }
                    else if (event.motion.x > save.pos.x && event.motion.x < save.pos.x + save.pos.w &&
                             event.motion.y > save.pos.y && event.motion.y < save.pos.y + save.pos.h)
                    {
                        sauvegarder(pos_p , pos_mas);
                    }
                }
                break;
            }
        }

		
		annimer_MiniMap(&m);
                //colision = collisionpp(pos_p, pos_mas);
                if (colision == 1)
        {
            img_ms = IMG_Load("Tree_2.png");
            SDL_Rect pos_ms;
            pos_ms.x = 900;
            pos_ms.y = 640;
        }




                /*if(printPixelColors(pos_p , masque)==1)
		{
			pos_p.x=0;
			pos_p.y=500;
		}*/

                SDL_Flip(screen);

	}
	SDL_FreeSurface(image_background) ;
	SDL_FreeSurface(img_p);
        SDL_FreeSurface(masque);
        SDL_FreeSurface(img_ms);
	SDL_FreeSurface(m.img);
	SDL_FreeSurface(m.image_perso);
        TTF_Quit();
        SDL_FreeSurface(screen);
       
       



}

