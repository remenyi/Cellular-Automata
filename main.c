#include "logika.h"
#include "rajzol.h"
#include <stdbool.h>
#include <math.h>

//Időzítő függvény, 40 ms-ként van meghívva
Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

int main(int argc, char *argv[]) {
    #ifdef __WIN32__
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    #endif
    int oszlopszam = 40, sorszam = 30;                      //az életter nagysága sorokban és oszlopokban
    int sejtmeret = 30;                                     //egy rekesz szélessége pixelben
    int x = sejtmeret*oszlopszam;                           //az ablak szélessége pixelben
    int y = sejtmeret*sorszam;                              //az ablak hosszúsága pixelben

    Sejt* sejtek = beolvas();                               //beolvassuk a sejtek.txt-ből a sejteket
    Sejt* szuletett = NULL;                                 //Születő sejtek, egyelőre üres


    SDL_Event event;
    SDL_Surface *screen;
    SDL_TimerID id;

    /* SDL inicializálása és ablak megnyitása */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(x, y, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("Eletjatek", "Eletjatek");

    id = SDL_AddTimer(40, idozit, NULL);                    //időzítő beállítása: 25 fps

    bool kilep = false;                                     //hamis, amíg fut a program
    bool fut = false;                                       //igaz, ha fut a szimuláció
    int mutatottsejt_x;                                     //annak a sejtnek a koordinátái, amire az egér mutat, ha le van nyomva a bal egérgomb és a szimuláció szünetel
    int mutatottsejt_y;
    int xoffset = 0;                                        //a bal egérgomb és a mozgatás eredményeként létrejövő kitérés
    int yoffset = 0;
    int elozox = 0;                                         //az offset-ek kiszámításakor kellenek
    int elozoy = 0;
    int sebesseg = 12;                                      //változtatásával lehet megváltoztatni a szimuláció sebességét
    int sebessegvalt = 0;                                   //számláló, ami ha eléri a sebességet nullázódik, és egy generációt ugrunk

    while (!kilep) {
        SDL_WaitEvent(&event);                              //beolvassuk a következő eventet
        switch(event.type)
        {
            case SDL_USEREVENT:
                boxRGBA(screen, 0, 0, x, y, 0, 0, 0, 255);                                  //fekete háttér kirajzolása
                sejt_kiir(sejtek, screen, sejtmeret, xoffset, yoffset);                     //kiírjuk az összes sejtet
                tabla_kiir(screen, sejtmeret, oszlopszam, sorszam, xoffset, yoffset);       //kiírjuk a rácsot
                sebesseg_kiir(screen, sebesseg);                                            //kiírjuk a sebességet
                if(fut && sebessegvalt >= sebesseg)
                {
                    szuletett = szuletok(sejtek);                      //kiszámoljuk a születőket
                    sejtek = eletbenmarad(sejtek);                                          //és az életbenmaradottakat
                    sejtek = hozzafuz(sejtek, szuletett);                                   //majd összefűzzük őket
                    sebessegvalt = 0;                                                       //a számláló nulla
                }
                if(fut)
                {
                    sebessegvalt += 2;                                                      //növeljük a számlálót
                    stringRGBA(screen, x/2, 10, "FUT!", 0, 255, 0, 255);                    //kiírjuk, hogy fut a szimuláció
                }
                else
                    stringRGBA(screen, x/2, 10, "ALL!", 255, 0, 0, 255);                    //egyébként kiírjuk, hogy nem fut a szimuláció
                SDL_Flip(screen);                                                           //megfordítjuk a képernyő buffert
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_LEFT:                                                         //ha a bal kurzotbillentyűt lenyomjuk
                        if(sebesseg < 20)                                                   //és a sebesség kisebb mint 20
                            sebesseg += 4;                                                  //csökkentjük a sebességet
                        break;
                    case SDLK_RIGHT:
                        if(sebesseg > 0)
                            sebesseg -= 4;
                        break;
                    case SDLK_SPACE:
                        fut = !fut;
                        break;
                    case SDLK_s:
                        if(!fut)
                            kiir(sejtek);
                        break;
                    case SDLK_r:
                        felszabadit(sejtek);
                        sejtek = NULL;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                mutatottsejt_x = (event.button.x-xoffset)/sejtmeret +1;                         //Annak a sejtnek a koordinátái, amire az egér mutat
                mutatottsejt_y = (event.button.y-yoffset)/sejtmeret +1;
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    elozox = event.button.x;
                    elozoy = event.button.y;
                    if(!fut)
                    {
                        Sejt* mozgo;                                                            //ha egy új sejtet akarunk beilleszteni, meg kell vizsgálni, hogy létezik-e már az a sejt
                        bool volte = false;
                        for(mozgo = sejtek; mozgo != NULL; mozgo = mozgo->kov)
                        if(mozgo->x == mutatottsejt_x && mozgo->y == mutatottsejt_y)
                            volte = true;
                        if(!volte)                                                              //ha még nem létezik, létrehozzuk
                            sejtek = epit(sejtek, mutatottsejt_x, mutatottsejt_y);
                    }
                }
                if(event.button.button == SDL_BUTTON_RIGHT && !fut)
                    sejtek = sejttorlo(sejtek, mutatottsejt_x, mutatottsejt_y);
                if(event.button.button == SDL_BUTTON_WHEELUP && sejtmeret < 100)
                {
                    sejtmeret++;                                                                //nagyításnál növeljük a sejtméret nagyságát
                    oszlopszam = x/sejtmeret+1;                                                 //és beállítjuk az oszlopok és sorok számát
                    sorszam = y/sejtmeret+1;

                    xoffset += (x/2-event.motion.x)*2/sejtmeret-oszlopszam/2;                   //kitérés kiszámítása
                    yoffset += (y/2-event.motion.y)*2/sejtmeret-sorszam/2;
                    offset_beallit(sejtek, &xoffset, &yoffset, sejtmeret);                      //és beállítása
                }
                if(event.button.button == SDL_BUTTON_WHEELDOWN && sejtmeret > 10)
                {
                    sejtmeret--;
                    oszlopszam = x/sejtmeret+1;
                    sorszam = y/sejtmeret+1;

                    xoffset += round((oszlopszam)/2.2);
                    yoffset += round((sorszam)/2.2);
                    offset_beallit(sejtek, &xoffset, &yoffset, sejtmeret);
                }
                break;
            case SDL_MOUSEMOTION:
                if(fut && event.button.button == SDL_BUTTON_LEFT)
                {
                    xoffset -= elozox-event.motion.x;                                           //kitérés kiszámítása
                    yoffset -= elozoy-event.motion.y;
                    offset_beallit(sejtek, &xoffset, &yoffset, sejtmeret);                      //és beállítása
                    elozox = event.motion.x;
                    elozoy = event.motion.y;
                }
                break;
            case SDL_QUIT:
                kilep = true;
                break;
            default:
                break;
        }
    }
    felszabadit(sejtek);
    SDL_RemoveTimer(id);
    SDL_Quit();
    return 0;
}
