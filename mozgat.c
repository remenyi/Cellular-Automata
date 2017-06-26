
#include "mozgat.h"

void balra(Sejt* eleje, int xoffset)
{
    Sejt* mozgo;
    for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov)
        mozgo->x = xoffset;
}

void jobbra(Sejt* eleje, int xoffset)
{
    Sejt* mozgo;
    for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov)
        mozgo->x = xoffset;
}

void fel(Sejt *eleje, int yoffset)
{
    Sejt* mozgo;
    for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov)
        mozgo->y = yoffset;
}

void le(Sejt *eleje, int yoffset)
{
    Sejt* mozgo;
    for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov)
        mozgo->y = yoffset;
}

