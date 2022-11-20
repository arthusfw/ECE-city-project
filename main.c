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

void initialisation() //défini les modes graphiques, la souris et charge les images
{
//éléments techniques
    allegro_init();
    //install_keyboard();  //utile ?
    install_mouse();
    set_color_depth(32);
    set_uformat(U_ASCII);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0)!=0) //Taille écran en  mettre 1078
        ERREUR(allegro_error);
//initialiser le drawing mode(alpha channel blend)
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    set_write_alpha_blender();
    //srand(time(NULL)); // initialise nb aléa
    image(); // chargement des images
    //terrainvide();
    return;
}

void rectangle(int xc, int yc, int nbx,int nby, int col, int colfond)
// des rectangle   origine           taille x8?         couleur
{
    int k;
    char chaine2[80];
    strcpy(chaine2,"");
    for(k=0; k<nbx; k++) strcat(chaine2," ");
    for(k=0; k<nby; k++)
        textout_ex(screen,font,chaine2,xc,yc+8*k,col,colfond);
    return;
}

int choixmenu(int min, int max) // revoir position
//ok retourne le nombre cliqué dans le menu entre min et max
{
    int k,xm,ym;
    k=0;
    do
    {
        if(mouse_b & 2)
        {
            xm=mouse_x;
            ym=mouse_y;
            if ((xm>=905) && (xm<929) && (ym>=200+60*min) && (ym<224+60*max) && ((ym-200)%60)<24) // bonne dimension horizontale, verticale,
                k=(ym-200)/60;
        }
    }
    while (k==0);
    return k;
}