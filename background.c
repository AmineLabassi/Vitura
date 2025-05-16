/**
 * @file background.c
 * @brief Gestion du background, de la musique, du temps et de l'animation dans le jeu SDL.
 * @author Vitura
 * @date 10 mai 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "background.h"
/**
 * @brief Initialise le background (image de fond).
 * @param b Pointeur vers la structure background.
 * @return 1 si succès, 0 sinon.
 */

int initBack(background *b) {
    b->img = IMG_Load("bg1.jpg");
    if (!b->img) {
        fprintf(stderr, "Erreur chargement background.png : %s\n", IMG_GetError());
        return 0;
    }
    b->img_pos.x = b->img_pos.y = 0;
    b->img_size.x = b->img_size.y = 0;
    b->img_size.w = SCREEN_W;
    b->img_size.h = SCREEN_H;
    b->start_time = 0;
    return 1;
}

/**
 * @brief Affiche le background sur l'écran.
 * @param b Structure background.
 * @param screen Surface SDL de l'écran.
 */

void afficherBack(background b, SDL_Surface *screen) {
    SDL_BlitSurface(b.img, &b.img_size, screen, &b.img_pos);
}

int musicLoad1(Mix_Music **music) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        fprintf(stderr, "Erreur audio : %s\n", Mix_GetError());
        return 0;
    }
    *music = Mix_LoadMUS("music.mp3");
    if (!*music) {
        fprintf(stderr, "Erreur musique : %s\n", Mix_GetError());
        return 0;
    }
    Mix_PlayMusic(*music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    return 1;
}
/**
 * @brief Charge et joue la musique de fond.
 * @param music Pointeur vers un pointeur de musique SDL.
 * @return 1 si succès, 0 sinon.
 */

void scrolling(background *b, int direction, int dx, int dy) {
    SDL_Rect nvpos = b->img_size;

    if (direction == 0) nvpos.x += dx;
    else if (direction == 1) nvpos.x -= dx;
    else if (direction == 2) nvpos.y -= dy;
    else if (direction == 3) nvpos.y += dy;

    if (nvpos.x < 0) nvpos.x = 0;
    if (nvpos.x + SCREEN_W > b->img->w) nvpos.x = b->img->w - SCREEN_W;

    if (nvpos.y < 0) nvpos.y = 0;
    if (nvpos.y + SCREEN_H > b->img->h) nvpos.y = b->img->h - SCREEN_H;

    b->img_size = nvpos;
}
/**
 * @brief Gère le scrolling du background.
 * @param b Pointeur vers la structure background.
 * @param direction Direction du scroll (0: droite, 1: gauche, 2: haut, 3: bas).
 * @param dx Déplacement horizontal.
 * @param dy Déplacement vertical.
 */

int backgroundLoad_lvl1(image *img) {
    img->filename = "bg1.jpg";
    img->img = IMG_Load(img->filename);
    if (!img->img) {
        fprintf(stderr, "Erreur chargement bg1.png : %s\n", IMG_GetError());
        return 0;
    }
    img->img_size.x = img->img_size.y = 0;
    img->img_size.w = img->img->w;
    img->img_size.h = img->img->h;
    img->img_pos.x = img->img_pos.y = 0;
    return 1;
}
/**
 * @brief Charge le background pour le niveau 1.
 * @param img Pointeur vers une image.
 * @return 1 si succès, 0 sinon.
 */

void backgroundDraw_lvl1(SDL_Surface *screen, image *img) {
    SDL_BlitSurface(img->img, &img->img_size, screen, &img->img_pos);
}
/**
 * @brief Affichage en écran scindé pour deux joueurs.
 * @param screen Surface SDL de l'écran.
 * @param img Image de fond.
 * @param cam1 Caméra du joueur 1.
 * @param cam2 Caméra du joueur 2.
 */
void splitScreen(SDL_Surface *screen, image *img, SDL_Rect cam1, SDL_Rect cam2) {
    SDL_Rect left_screen = {0, 0, SCREEN_W / 2, SCREEN_H};
    SDL_Rect right_screen = {SCREEN_W / 2, 0, SCREEN_W / 2, SCREEN_H};

    SDL_BlitSurface(img->img, &cam1, screen, &left_screen);
    SDL_BlitSurface(img->img, &cam2, screen, &right_screen);

    SDL_Rect border = {SCREEN_W / 2 - 1, 0, 2, SCREEN_H};
    Uint32 line_color = SDL_MapRGB(screen->format, 255, 255, 255);
    SDL_FillRect(screen, &border, line_color);
}
/**
 * @brief Affiche le temps global écoulé depuis le début.
 * @param start_time Temps de départ (SDL_GetTicks()).
 * @param screen Surface SDL de l'écran.
 * @param font Police pour l'affichage du texte.
 */


void afficherTempsGlobal(Uint32 start_time, SDL_Surface *screen, TTF_Font *font) {
    Uint32 current = SDL_GetTicks() - start_time;
    char time_str[20];
    sprintf(time_str, "Time: %02d:%02d", current / 60000, (current / 1000) % 60);
    SDL_Surface* txt = TTF_RenderText_Solid(font, time_str, (SDL_Color){255,255,255});
    SDL_Rect txt_rect = {SCREEN_W - txt->w - 10, 10};
    SDL_BlitSurface(txt, NULL, screen, &txt_rect);
    SDL_FreeSurface(txt);
}
/**
 * @brief Met à jour et affiche le temps de jeu.
 * @param back Pointeur vers background (contenant start_time).
 * @param screen Surface SDL de l'écran.
 * @param font Police utilisée pour l'affichage.
 */

void update_game_time(background *back, SDL_Surface *screen, TTF_Font *font) {
    if (!back->start_time) back->start_time = SDL_GetTicks();
    afficherTempsGlobal(back->start_time, screen, font);
}

/**
 * @brief Met à jour la position de la caméra selon la direction.
 * @param cam Pointeur vers la SDL_Rect de la caméra.
 * @param direction Direction du mouvement.
 * @param img Surface de l'image.
 * @param dx Déplacement en x.
 * @param dy Déplacement en y.
 */
void update_camera(SDL_Rect *cam, int direction, SDL_Surface *img, int dx, int dy) {
    if (direction == 0) cam->x += dx;
    else if (direction == 1) cam->x -= dx;
    else if (direction == 2) cam->y -= dy;
    else if (direction == 3) cam->y += dy;

    // Limites
    if (cam->x < 0) cam->x = 0;
    if (cam->x + cam->w > img->w) cam->x = img->w - cam->w;
    if (cam->y < 0) cam->y = 0;
    if (cam->y + cam->h > img->h) cam->y = img->h - cam->h;
}
/**
 * @brief Charge une image à partir d’un fichier.
 * @param path Chemin vers le fichier image.
 * @return Surface SDL de l’image chargée ou NULL en cas d’échec.
 */
SDL_Surface* loadImage(char *path) {
    SDL_Surface *img = IMG_Load(path);
    if (!img) {
        printf("Erreur chargement image %s : %s\n", path, IMG_GetError());
    }
    return img;
}
/**
 * @brief Affiche un guide avec une boîte semi-transparente.
 * @param screen Surface de l’écran.
 * @param font Police de texte.
 */

void afficherGuideAvecIcone(SDL_Surface *screen, TTF_Font *font) {
    SDL_Color texte_color = {0, 0, 0};
    SDL_Rect box = {(screen->w - 500) / 2, (screen->h - 140) / 2, 500, 140};

    SDL_Surface *overlay = SDL_CreateRGBSurface(SDL_SRCALPHA, box.w, box.h, 32,
        screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);
    SDL_FillRect(overlay, NULL, SDL_MapRGBA(screen->format, 255, 255, 255, 200));
    SDL_BlitSurface(overlay, NULL, screen, &box);
    SDL_FreeSurface(overlay);

    const char *lignes[] = {
        "            === GUIDE DE JEU ===",
        "Joueur 1 : Z Q S D",
        "Joueur 2 :(up,left,down,right)", 
        "ESC : Quitter",
        NULL
    };

    int y_offset = box.y + 15;
    for (int i = 0; lignes[i] != NULL; i++) {
        SDL_Surface *txt = TTF_RenderText_Blended(font, lignes[i], texte_color);
        if (txt) {
            SDL_Rect pos = {box.x + 20, y_offset};
            SDL_BlitSurface(txt, NULL, screen, &pos);
            SDL_FreeSurface(txt);
            y_offset += 28;
        }
    }
}
/**
 * @brief Vérifie si la fin du background a été atteinte.
 * @param b Pointeur vers le background.
 * @return 1 si la fin est atteinte, 0 sinon.
 */

int is_end_of_background(background *b) {
    return (b->img_size.x + SCREEN_W >= b->img->w);
}
/**
 * @brief Initialise l'animation d’un robot.
 * @param image Pointeur vers background contenant les informations du sprite.
 */



// Fonction pour initialiser l'animation du robot
void init_animerBack(background* image) {
    image->img = IMG_Load("robot.png");
    if (!image->img) {
        fprintf(stderr, "Erreur chargement robot.png : %s\n", IMG_GetError());
        return; // Exit early if the image is not found
    }

    // Initialisation de la première frame
    image->camera_pos.x = 0;
    image->camera_pos.y = 0;
    image->camera_pos.w = 100;  // largeur d'une frame
    image->camera_pos.h = 121;  // hauteur d'une frame

    // Position à l'écran pour l'affichage du robot
    image->pos_ecran.x = 300;   // Assurez-vous que la position est dans les limites de l'écran
    image->pos_ecran.y = 200;
    image->pos_ecran.w = image->camera_pos.w;
    image->pos_ecran.h = image->camera_pos.h;

    image->direction = 0;
}

/**
 * @brief Affiche une frame de l’animation du robot.
 * @param image Structure background avec les infos d’animation.
 * @param screen Surface SDL de l’écran.
 */
// Affichage de l'animation du robot
void afficher_animerBack(background image, SDL_Surface *screen) {
    SDL_BlitSurface(image.img, &image.camera_pos, screen, &image.pos_ecran);
}
/**
 * @brief Met à jour la frame actuelle de l'animation du robot.
 * @param image Pointeur vers la structure background.
 * @param frame_width Largeur d’une frame.
 * @param nb_frames Nombre total de frames.
 */

// Mise à jour des frames de l'animation
void update_animation(background *image, int frame_width, int nb_frames) {
    image->camera_pos.x += frame_width;
    if (image->camera_pos.x >= frame_width * nb_frames) {
        image->camera_pos.x = 0;
    }
}
