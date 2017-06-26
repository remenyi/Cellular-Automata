#ifndef RAJZOL
#define RAJZOL

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include "lista.h"

//kirajzolja a t�bl�t a param�terben megadott k�perny�re a megadott sejtnagys�ggal, koordin�t�kkal �s offsetekkel
void tabla_kiir(SDL_Surface* screen, int sejtnagysag, int oszlopszam, int sorszam, int xoffset, int yoffset);
//kirajzolja a param�terben megadott sejteket az adott k�perny�re, a sejtm�rettel �s az offsetekkel egy�tt
void sejt_kiir(Sejt* eleje, SDL_Surface *screen, int sejtmeret, int xoffset, int yoffset);
//be�ll�tja az offseteket �s a sejtek koordin�t�it az offsetek f�ggv�ny�ben
void offset_beallit(Sejt* eleje, int* xoffset, int* yoffset, int sejtmeret);
//ki�rja a sebess�get a param�terben megadott k�perny�re az adott sebess�ggel
void sebesseg_kiir(SDL_Surface *screen, int sebesseg);

#endif
