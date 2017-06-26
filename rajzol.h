#ifndef RAJZOL
#define RAJZOL

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include "lista.h"

//kirajzolja a táblát a paraméterben megadott képernyõre a megadott sejtnagysággal, koordinátákkal és offsetekkel
void tabla_kiir(SDL_Surface* screen, int sejtnagysag, int oszlopszam, int sorszam, int xoffset, int yoffset);
//kirajzolja a paraméterben megadott sejteket az adott képernyõre, a sejtmérettel és az offsetekkel együtt
void sejt_kiir(Sejt* eleje, SDL_Surface *screen, int sejtmeret, int xoffset, int yoffset);
//beállítja az offseteket és a sejtek koordinátáit az offsetek függvényében
void offset_beallit(Sejt* eleje, int* xoffset, int* yoffset, int sejtmeret);
//kiírja a sebességet a paraméterben megadott képernyõre az adott sebességgel
void sebesseg_kiir(SDL_Surface *screen, int sebesseg);

#endif
