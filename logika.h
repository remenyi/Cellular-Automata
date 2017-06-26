#ifndef LOGIKA
#define LOGIKA

#include "fajlkezeles.h"

//visszatér a paraméterben kapott x és y helyen lévõ pont szomszédainak számával
int kornyezet(int x, int y, Sejt* eleje);
//visszatér a paraméterként kapott sejtek összes szomszédjával
Sejt* szomszedok(Sejt* eleje);
//visszatér a született sejtekkel
Sejt* szuletok(Sejt* eleje);
//visszatér az életben maradt sejtekkel
Sejt* eletbenmarad(Sejt* eleje);

#endif
