#include "lista.h"

//Listaépítõ
Sejt* epit(Sejt* eleje, int x, int y)
{
    Sejt* uj = NULL;
    uj = (Sejt*)malloc(sizeof(Sejt));
    if(uj == NULL)
        perror("Nem sikerult helyet foglalni a memoriaban!\n");     //ha nem sikerült lefoglalni a memóriaterületet: hibaüzenet
    uj->x = x;
    uj->y = y;
    uj->kov = eleje;        //a lista elejére rakjuk az új sejtet
    return uj;
}

Sejt* sejttorlo(Sejt* eleje, int x, int y)
{
    Sejt *lemarado, *mozgo;
    lemarado = NULL, mozgo = eleje;
    while(mozgo != NULL && (mozgo->x != x || mozgo->y != y))        //mozgo-val végigmegyünk a listán, amíg a keresett feltétel nem teljesül. A lemarado egyel lemaradva követi
    {
        lemarado = mozgo;
        mozgo = mozgo->kov;
    }
    if(mozgo == NULL)                   //ha üres listát kapunk, visszatérünk vele
    {
        return eleje;
    }
    if(lemarado == NULL)                //ha az első elemet kell kitörölni, a lista új eleje a következő cím lesz, amivel visszatérünk
    {
        Sejt* ujeleje = mozgo->kov;
        free(mozgo);
        return ujeleje;
    }
    lemarado->kov = mozgo->kov;         //egyébként kitöröljük a mozgo-t (ha végigmentünk úgy a listán, hogy nem találtuk meg a keresett értéket, mozgo nullpointer)
    free(mozgo);
    return eleje;                       //és visszatérünk a lista elejével
}

Sejt* hozzafuz(Sejt* eleje, Sejt* fuzendo)
{
    if(eleje == NULL)                   //ha az első lista NULL, a második listával térünk vissza
        return fuzendo;
    Sejt* mozgo;
    for(mozgo = eleje; mozgo->kov != NULL; mozgo = mozgo->kov); //végigmegyünk az egyik listán a végéig
    mozgo->kov = fuzendo;                                       //és hozzáfűzzük a füzendő listát
    return eleje;
}

void felszabadit(Sejt* eleje)
{
    Sejt* temp = eleje;             //átmeneti változóban tároljuk a törlendő elemet
    while(temp != NULL)
    {
        eleje = temp->kov;          //a következő elemet mindig eltároljuk
        free(temp);                 //hogy egy sejt kitörlése után
        temp = eleje;               //az legyen a következő örlendő elem
    }
}

