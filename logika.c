#include "logika.h"
#include <stdbool.h>

int kornyezet(int x, int y, Sejt* eleje)
{
    Sejt* mozgo;
    int x_mozgo, y_mozgo;
    int i, j;
    int darab = 0;
    for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov)   //végigmegyünk a lista összes sejtjén
    {
        x_mozgo = mozgo->x;
        y_mozgo = mozgo->y;
        for(i = x-1; i <= x+1; i++)                         //végigmegyünk mind a kilenc szomszédos sejten
            for(j = y-1; j <= y+1; j++)
                if(i == x_mozgo && j == y_mozgo)            //és ha az egyik szomszédos sejt koordinátái megegyeznek a lista egyik sejtjének koordinátáival
                    darab++;                                //eggyel több szomszéd van
    }
    for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov)   //ha a kapott lista egyik elemének szomszédjait vizsgáljuk, az adott elemet nem számoljuk bele szomszédként
    {
        if(mozgo->x == x && mozgo->y == y)
            return --darab;
    }
    return darab;
}

Sejt* szomszedok(Sejt* eleje)
{
    if(eleje == NULL)
        return NULL;
    Sejt* szomszedok_eleje = NULL;
    Sejt *mozgo1, *mozgo2;
    bool vane1, vane2;
    int i, j;
    for(mozgo1 = eleje; mozgo1 != NULL; mozgo1 = mozgo1->kov)                           //végigmegyünk a lista összes szomszédján
        for(i = mozgo1->x-1; i <= mozgo1->x+1; i++)
            for(j = mozgo1->y-1; j <= mozgo1->y+1; j++)
            {
                vane1 = vane2 = true;
                for(mozgo2 = eleje; mozgo2 != NULL; mozgo2 = mozgo2->kov)               //és ha nincs benne a kapott listában
                    if(mozgo2->x == i && mozgo2->y == j)
                    {
                        vane1 = false;
                        break;
                    }
                for(mozgo2 = szomszedok_eleje; mozgo2 != NULL; mozgo2 = mozgo2->kov)    //vagy a készülő listában, ami a szomszédokat tartalmazza
                    if(mozgo2->x == i && mozgo2->y == j)
                    {
                        vane2 = false;
                        break;
                    }
                if(vane1 && vane2)                                                      //hozzáadjuk a zomszédok listájához
                {
                    szomszedok_eleje = epit(szomszedok_eleje, i, j);
                }
            }
    return szomszedok_eleje;
}

Sejt* szuletok(Sejt* eleje)
{
    Sejt* mozgo;
    Sejt* szuletok = NULL;
    szuletok = szomszedok(eleje);                       //készítünk egy listát a kapott lista összes szomszédjával
    for(mozgo = szuletok; mozgo != NULL; mozgo = mozgo->kov)
    {
        if(kornyezet(mozgo->x, mozgo->y, eleje) != 3)   //ha a szomszédok szomszédos sejtjeinek a száma nem 3, akkor kitöröljük
        {
            szuletok = sejttorlo(szuletok, mozgo->x, mozgo->y);
        }
    }
    return szuletok;
}

Sejt* eletbenmarad(Sejt* eleje)
{
    Sejt* mozgo;
    Sejt* torlendo = NULL;
    int kornyezetszam;
    for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov)
    {
        kornyezetszam = kornyezet(mozgo->x, mozgo->y, eleje);
        if(kornyezetszam < 2 || kornyezetszam > 3)              //ha a paraméterként kapott lista egyik elemének a szomszédjainak száma nem 2 vagy 3, akkor törlendő
        {
            torlendo = epit(torlendo, mozgo->x, mozgo->y);
        }
    }
    for(mozgo = torlendo; mozgo != NULL; mozgo = mozgo->kov)    //amit ki kell törölni a meglévőkből
    {
        eleje = sejttorlo(eleje, mozgo->x, mozgo->y);
        torlendo = sejttorlo(torlendo, mozgo->x, mozgo->y);     //meg saját magát is, hogy ne legyen memóriaszivárgás
    }
    return eleje;
}

