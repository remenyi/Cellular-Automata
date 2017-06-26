#ifndef LOGIKA
#define LOGIKA

#include "fajlkezeles.h"

//visszat�r a param�terben kapott x �s y helyen l�v� pont szomsz�dainak sz�m�val
int kornyezet(int x, int y, Sejt* eleje);
//visszat�r a param�terk�nt kapott sejtek �sszes szomsz�dj�val
Sejt* szomszedok(Sejt* eleje);
//visszat�r a sz�letett sejtekkel
Sejt* szuletok(Sejt* eleje);
//visszat�r az �letben maradt sejtekkel
Sejt* eletbenmarad(Sejt* eleje);

#endif
