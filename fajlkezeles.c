#include "fajlkezeles.h"
#include <stdbool.h>

Sejt* beolvas()
{
    FILE* fp;
    fp = fopen("sejtek.txt", "r");
    char sor[100];                 //átmeneti tároló a beolvasott soroknak
    Sejt* eleje = NULL;
    int x_kord, y_kord;
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fgets(sor, 100, fp);                                                            //következő sor eltárolása

            if(sscanf(sor, "(%d, %d)", &x_kord, &y_kord) != 2)                              //koordináták beolvasása
                   perror("Nem sikerult beolvasni az adatokat vagy nincsenek adatok!\n");   //ha nem sikerült: hibaüzenet
            bool volte = false;                                                             //megvizsgáljuk, hogy tartalmazza-e már a sejtet a lista
            Sejt* mozgo;
            for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov)
                if(mozgo->x == x_kord && mozgo->y == y_kord)
                    volte = true;
            if(!volte)
                eleje = epit(eleje, x_kord, y_kord);                                        //hozzáadjuk a listához
        }
        fclose(fp);
    }
    else
        perror("Nem sikerult megnyitni a fajlt\n");                                         //ha nem sikerült megnyitni a fájlt: hibaüzenet
    return eleje;
}

void kiir(Sejt* eleje)
{
    FILE* fp;
    fp = fopen("mentes.txt", "w");
    if(fp != NULL)
    {
        Sejt* mozgo;
        for(mozgo = eleje; mozgo != NULL; mozgo = mozgo->kov)
        {
            fprintf(fp, "(%d, %d)\n", mozgo->x, mozgo->y);
        }
        fclose(fp);
    }
    else
        perror("Nem sikerult letrehozni a fajlt!\n");
}

