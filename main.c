#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <allegro.h>
#include <allegro_native_dialog.h>


#define ERREUR(msg){\



int main()
{
    initialisation();
    show_mouse(screen);
    imenu=1;
    do
    {
        if (imenu==1) nouveau(); // Nouvelle partie seulement
        jeu();
        //refaire menu ici
        rectangle(900,200,15,83,0,0);
        rectangle(900,220,15,3,makecol(0,0,0),makecol(180,180,0));
        textout_ex(screen,font,"   Menu",905,224,makecol(100,100,255),makecol(180,180,0));
        //rectangle(840,124,40,37,0,0);
        textout_ex(screen,font,"Nouveau",940,268,makecol(255,0,0),0);
        textout_ex(screen,font,"Reprendre",940,328,makecol(255,0,0),0);
        textout_ex(screen,font,"Quitter",940,388,makecol(255,0,0),0);

        affichemenu(1,3);
        imenu=choixmenu(1,3);
        rectangle(900,200,15,83,0,0);
    }
    while (imenu!=3);
    supimage();
    return 0;
}
END_OF_MAIN();