#include "perso.h"

void initPerso2(Personne *p) {
    (*p).imagePers = IMG_Load("perso.png");

    p->position.x = 200;
    p->position.y = 700;

    p->frame.w = 100;
    p->frame.h = 100;
    p->frame.x = 0;
    p->frame.y = 0;

    p->curframe = 0;

    p->direction = 0;

    p->v_x = 4;
    p->v_grav = 0.5;
    p->v_saut = -6;
    p->v_y = p->v_saut;

    p->acceleration = 0;
    p->vitesse = 5;
    p->imagec = IMG_Load("coeur.png");
    p->positionc.x = 1400;
    p->positionc.y = 0;
    p->nbcoeur = 3;
    TTF_Init();
    p->score.font = TTF_OpenFont("angelina.TTF", 50);

    p->score.color = (SDL_Color){0, 0, 255};
    p->score.text =
        TTF_RenderText_Blended(p->score.font, "score2 0", p->score.color);
    p->vie.text =
        TTF_RenderText_Blended(p->score.font, "vie2 ", p->score.color);
    p->vie.postext.x = 1100;
    p->vie.postext.y = 0;

    p->score.postext.x = 800;
    p->score.postext.y = 0;

    p->Vscore = 0;
}

void initPerso(Personne *p) {
    (*p).imagePers = IMG_Load("perso.png");

    p->position.x = 0;
    p->position.y = 700;

    p->frame.w = 100;
    p->frame.h = 100;
    p->frame.x = 0;
    p->frame.y = 0;

    p->curframe = 0;

    p->direction = 0;

    p->v_x = 4;
    p->v_grav = 0.5;
    p->v_saut = -6;
    p->v_y = p->v_saut;

    p->acceleration = 0;
    p->vitesse = 5;
    p->imagec = IMG_Load("coeur.png");
    p->positionc.x = 545;
    p->positionc.y = 0;
    p->nbcoeur = 3;
    TTF_Init();
    p->score.font = TTF_OpenFont("angelina.TTF", 50);

    p->score.color = (SDL_Color){0, 0, 255};
    p->score.text =
        TTF_RenderText_Blended(p->score.font, "score 0", p->score.color);
    p->vie.text = TTF_RenderText_Blended(p->score.font, "vie ", p->score.color);
    p->vie.postext.x = 300;
    p->vie.postext.y = 0;

    p->score.postext.x = 100;
    p->score.postext.y = 0;

    p->Vscore = 0;
}

void afficherPerso(Personne p, SDL_Surface *screen) {
    char vsc[30];
    sprintf(vsc, "score: %d", p.Vscore);

    p.score.text = TTF_RenderText_Blended(p.score.font, vsc, p.score.color);
    SDL_BlitSurface(p.score.text, NULL, screen, &p.score.postext);
    SDL_BlitSurface(p.vie.text, NULL, screen, &p.vie.postext);

    SDL_BlitSurface(p.imagePers, &(p.frame), screen,
                    &(p.position));  //&(p.frame)

    switch (p.nbcoeur) {
        case 1:
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            break;
        case 2:
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            p.positionc.x = 545 - 60;
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            break;
        case 3:
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            p.positionc.x = 545 - 60;
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            p.positionc.x = 545 - 60 - 60;
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            break;
    }
}

void afficherPerso2(Personne p, SDL_Surface *screen) {
    char vsc[30];
    sprintf(vsc, "score2: %d", p.Vscore);

    p.score.text = TTF_RenderText_Blended(p.score.font, vsc, p.score.color);
    SDL_BlitSurface(p.score.text, NULL, screen, &p.score.postext);
    SDL_BlitSurface(p.vie.text, NULL, screen, &p.vie.postext);

    SDL_BlitSurface(p.imagePers, &(p.frame), screen,
                    &(p.position));  //&(p.frame)

    switch (p.nbcoeur) {
        case 1:
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            break;
        case 2:
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            p.positionc.x = 1400 - 60;
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            break;
        case 3:
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            p.positionc.x = 1400 - 60;
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            p.positionc.x = 1400 - 60 - 60;
            SDL_BlitSurface(p.imagec, NULL, screen, &p.positionc);
            break;
    }
}

void movePerso(Personne *p, Uint32 dt) {
    switch (p->direction) {
        case 1:
            p->position.x +=
                0.5 * p->acceleration * (dt) * (dt) + p->vitesse * dt;
            break;
        case 2:
            p->position.x -=
                0.5 * p->acceleration * (dt) * (dt) + p->vitesse * dt;

            break;
        case 3:
            p->position.y -= 3;
            break;
    }
}

void animerPerso(Personne *p) {
    if (p->direction == 1) {
        p->frame.y = 0;
        p->curframe++;
        if (p->curframe >= 4) {
            p->curframe = 0;
        }
        p->frame.x = p->curframe * p->frame.w;

    } else if (p->direction == 2) {
        p->frame.y = 100;
        p->curframe++;
        if (p->curframe >= 4) {
            p->curframe = 0;
        }
        p->frame.x = p->curframe * p->frame.w;

    } else if (p->direction == 3) {
        p->frame.y = 200; // Attack right animation
        p->curframe++;
        if (p->curframe >= 4) {
            p->curframe = 0;
        }
        p->frame.x = p->curframe * p->frame.w;

    } else if (p->direction == 4) {
        p->frame.y = 300; // Attack left animation
        p->curframe++;
        if (p->curframe >= 4) {
            p->curframe = 0;
        }
        p->frame.x = p->curframe * p->frame.w;

    } else if (p->direction == 0) {
        p->frame.x = 0;
    }
}

void sautdroit(Personne *p) {
    if (p->position.y < 700) {
        p->position.x += p->v_x;
        p->position.y += p->v_y;
        p->v_y += p->v_grav;
    }
    if (p->position.y > 700) p->v_y = p->v_saut;
}

void sautgauche(Personne *p) {
    if (p->position.y < 700) {
        p->position.x -= p->v_x;
        p->position.y += p->v_y;
        p->v_y += p->v_grav;
    }
    if (p->position.y > 700) p->v_y = p->v_saut;
}
