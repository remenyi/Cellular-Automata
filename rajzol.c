#include "rajzol.h"


void tabla_kiir(SDL_Surface* screen, int sejtmeret, int oszlopszam, int sorszam, int xoffset, int yoffset)
{
    int i;
    for(i = xoffset; i < oszlopszam*sejtmeret; i+=sejtmeret)                        //függőleges vonalak kiírása
    {
        thickLineRGBA(screen, i, 0, i, sejtmeret*sorszam, 1, 255, 255, 255, 50);
    }
    for(i = yoffset; i < sorszam*sejtmeret; i+=sejtmeret)                           //vízszintes vonalak kiírása
    {
        thickLineRGBA(screen, 0, i, sejtmeret*oszlopszam, i, 1, 255, 255, 255, 50);
    }
}


void sejt_kiir(Sejt* eleje, SDL_Surface *screen, int sejtmeret, int xoffset, int yoffset)
{
    Sejt* mozgo;
    for(mozgo = eleje; mozgo != NULL; mozgo=mozgo->kov)                         //végigmegyünk a listán
    {
        int t_x = (mozgo->x-1)*sejtmeret+xoffset;                               //átváltjuk a sejtek koordinátáit pixel koordinátákba
        int t_y = (mozgo->y-1)*sejtmeret+yoffset;
        boxRGBA(screen, t_x, t_y, t_x+sejtmeret, t_y+sejtmeret, 46, 139, 87, 255);
    }
}

void offset_beallit(Sejt* eleje, int* xoffset, int* yoffset, int sejtmeret)
{
    Sejt* mozgo;
    int xoffset_offset = abs(*xoffset/sejtmeret);       //az offset (pixelben megadva) mennyi koordinátával változtatná meg a sejteket (sejtmérettől függő koordinátarendszerben megadva)
    int yoffset_offset = abs(*yoffset/sejtmeret);
    for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov)
    {
        if(*xoffset >= sejtmeret)                       //ha az offset nagyobb, mint a sejtméret (vagyis a koordinátarendszerben az 1), hozzá kell adni a sejtek koordinátáihoz az előbbi értéket
            mozgo->x += xoffset_offset;
        if(*xoffset <= sejtmeret*(-1))
            mozgo->x -= xoffset_offset;
        if(*yoffset >= sejtmeret)
            mozgo->y += yoffset_offset;
        if(*yoffset <= sejtmeret*(-1))
            mozgo->y -= yoffset_offset;
    }
    *xoffset %= sejtmeret;                              //az új offset értéke nem lehet nagyobb, mint a sejtméret
    *yoffset %= sejtmeret;
}

void sebesseg_kiir(SDL_Surface *screen, int sebesseg)
{
    switch(sebesseg)
    {
            case 20:
                stringRGBA(screen, 10, 10, "SEBESSEG: 1X", 255, 0, 0, 255);
                break;
            case 16:
                stringRGBA(screen, 10, 10, "SEBESSEG: 2X", 255, 0, 0, 255);
                break;
            case 12:
                stringRGBA(screen, 10, 10, "SEBESSEG: 3X", 255, 0, 0, 255);
                break;
            case 8:
                stringRGBA(screen, 10, 10, "SEBESSEG: 4X", 255, 0, 0, 255);
                break;
            case 4:
                stringRGBA(screen, 10, 10, "SEBESSEG: 5X", 255, 0, 0, 255);
                break;
            case 0:
                stringRGBA(screen, 10, 10, "SEBESSEG: 6X", 255, 0, 0, 255);
                break;
                }
}
