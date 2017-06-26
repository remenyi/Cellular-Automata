#ifndef LISTA
#define LISTA

#include <stdlib.h>

//Sejt típus
//a láncolt lista eleme
typedef struct Sejt
{
    int x, y;             //a sejt koordinátái
    struct Sejt* kov;     //a következő sejt címe
} Sejt;

//a paraméterként kapott listához hozzáfűzi az x, y koordinátákból létrehozott Sejt típust. A visszatérítési érték az új lista
Sejt* epit(Sejt* eleje, int x, int y);
//a paraméterként kapott listából kitörli az x, y koordinátákkal megadott Sejt típust. A visszatérítési érték az új lista
Sejt* sejttorlo(Sejt* eleje, int x, int y);
//az eleje listához hozzáfűzi a fuzendo listát. A visszatérítési érték az új lista
Sejt* hozzafuz(Sejt* eleje, Sejt* fuzendo);
//felszabadítja a paraméterként kapott listát
void felszabadit(Sejt* eleje);


#endif
