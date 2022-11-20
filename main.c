#include <stdio.h>

int main()
{
    printf("hello world");
}

void attente(int temps) // attend temps secondes/1000
{
    clock_t hdeb;
    hdeb=clock();
    while (clock()-hdeb<=temps*CLOCKS_PER_SEC/1000);
    return;
}

void image() // chargement images
{
    //Tampon= load_bitmap("elec.bmp", NULL); // oui mais assez grand
    //Tampon= load_bitmap("eau.bmp", NULL); // oui mais assez grand

    terrainvierge = load_bitmap("herbe.bmp",NULL);
    if (!terrainvierge) ERREUR("load terrainvierge");
    mairie = load_bitmap("mairie.bmp",NULL);
    if (!mairie) ERREUR("load mairie"); //60x60
    route = load_bitmap("route.bmp",NULL);
    if (!route) ERREUR("load route"); // 20x20
    iconeroute = load_bitmap("iconeroute.bmp",NULL);
    if (!iconeroute) ERREUR("load iconeroute"); //50x50
    elec = load_bitmap("elec.bmp",NULL);
    if (!elec) ERREUR("load elec"); //80x120
    iconeelec = load_bitmap("iconeelec.bmp",NULL);
    if (!iconeelec) ERREUR("load iconeelec");
    eau = load_bitmap("eau.bmp",NULL);
    if (!eau) ERREUR("load eau");
    iconeeau = load_bitmap("iconeeau.bmp",NULL);
    if (!iconeeau) ERREUR("load iconeeau");
    hab[0] = load_bitmap("habniv0.bmp", NULL);
    if (!hab[0]) ERREUR("load hab[0]");
    hab[1] = load_bitmap("habniv1.bmp", NULL);
    if (!hab[1]) ERREUR("load hab[1]");
    hab[2] = load_bitmap("habniv2.bmp", NULL);
    if (!hab[2]) ERREUR("load hab[2]");
    hab[3] = load_bitmap("habniv3.bmp", NULL);
    if (!hab[3]) ERREUR("load hab[3]");
    hab[4] = load_bitmap("habniv4.bmp", NULL);
    if (!hab[4]) ERREUR("load hab[4]");

page = load_bitmap("eau.bmp",NULL);
    if (!page) ERREUR("load page");
    //page=(BITMAP *)malloc(sizeof(BITMAP)*700*900+20);
    buche = load_bitmap("buche.bmp", NULL);
    return;
}

void affichechrono() // revoir position
{
    rectangle(950,28,5,1,0,0);
    itoa((int)(tmax-(clock()-dchrono)/1000.+0.1),chaine,10);
    textout_ex(screen,font,chaine,970,28,makecol(255,0,0),makecol(0,0,0));
}