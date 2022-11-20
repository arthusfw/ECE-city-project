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

void affichecapital()
{
    char cap[10];
    rectangle(902,64,14,1,makecol(0,0,0),makecol(180,180,0));
    itoa(capital,cap,10);
    textout_ex(screen,font,cap,912,64,makecol(255,0,0),makecol(180,180,0));
}

void affichepopulation()
{
    char pop[10];
    int i;
    population=0;
    for (i=0; i<nbhab; i++)
        switch (etathab[i])
        {
        case 1 :
            population+=10;
            break;
        case 2 :
            population+=50;
            break;
        case 3 :
            population+=100;
            break;
        case 4 :
            population+=1000;
            break;
        }
    rectangle(902,104,14,1,makecol(0,0,0),makecol(180,180,0));
    itoa(population,pop,10);
    textout_ex(screen,font,pop,912,104,makecol(255,0,0),makecol(180,180,0));
}

void posebati(int type)
{
    int xm,ym,xh,yh,xs,ys;
    int cout;
    int bon; // O au début du test, 1 si bonne position, 2 si connexité possible
    int li,co;
    switch (type)
    {
    case 1 :
        cout=10;
        xh=1;
        yh=1;
        strcpy(chaine,"route");
        break;
    case 2 :
        cout=100000;
        xh=4;
        yh=6;
        strcpy(chaine,"chateau d'eau");
        break;
    case 3 :
        cout=100000;
        xh=4;
        yh=6;
        strcpy(chaine,"centrale electrique");
        break;
    case 4 :
        cout=1000;
        xh=3;
        yh=3;
        strcpy(chaine,"habitation");
        break;
    }
    rectangle(100,705,80,7,0,makecol(180,180,0));
    textout_ex(screen,font,"Pose sur le plateau d'un element",102,707,makecol(100,100,255),makecol(180,180,0));
    textout_ex(screen,font,"chaine",364,707,makecol(100,100,255),makecol(180,180,0));

    while ((mouse_x>=919-xh*20) || (mouse_y>=719-yh*20)) {} // attente que la souris soit dans la zone jeu permettant de poser un bâtiment
    textout_ex(screen,font,"Cliquer pour poser de manière connexe.",102,717,makecol(100,100,255),makecol(180,180,0));
    textout_ex(screen,font,"Fin de pose en sortant du plateau",102,727,makecol(100,100,255),makecol(180,180,0));

    while (((mouse_x<919-xh*20) && (mouse_y<719-yh*20) && (capital>=cout)) && ((clock()-dchrono)/1000.<tmax)) // tant que la souris reste dans la zone jeu et assez d'argent

    {
       affichechrono();
       xs=mouse_x/20;
        ys=mouse_y/20;

        blit(screen,page,xs*20,ys*20,0,0,xh*20,yh*20);
       // attente(5);
        switch (type)
        {
        case 1 : blit(route,screen,0,0,xs*20,ys*20,20,20); break;
        case 2 : blit(eau,screen,0,0,xs*20,ys*20,80,120); break;
        case 3 : blit(elec,screen,0,0,xs*20,ys*20,80,120); break;
        case 4 : blit(hab[0],screen,0,0,xs*20,ys*20,60,60); break;
        }
        attente(60);
        blit(page,screen,0,0,xs*20,ys*20,xh*20,yh*20);
        attente(3);

        if(mouse_b & 2) // si double clic
        {
           xm=mouse_x/20; //converti les coordonnées souris en coordonnées plateau
           ym=mouse_y/20;
            bon=1;
            for (co=0; co<xh; co++) // test si place suffisante
                for(li=0; li<yh; li++)
                    if (plateau[ym+li][xm+co]!=-1) bon=0; // si la case n'est pas vide pose impossible
            //test de la convexité
            if (bon==1)
            {
                for (co=0; co<xh; co++)
                {
                    if (ym>0) if (plateau[ym-1][xm+co]==0) bon=2; //par le haut
                    if (ym+yh<35) if (plateau[ym+yh][xm+co]==0) bon=2; // par le bas
                }
                for (li=0; li<yh; li++)
                {
                    if (xm>0) if (plateau[ym+li][xm-1]==0) bon=2; // par la gauche
                    if (xm+xh<45) if (plateau[ym+li][xm+xh]==0) bon=2; // par la droite
                }
                if (bon==2)
                {
                    //ajouter le point de connexion si type >1
                    for (co=0; co<xh; co++)
                        for(li=0; li<yh; li++)
                            plateau[ym+li][xm+co]=type-1; // marque les cases occupées du plateau par type-1
                    switch (type)
                    {
                    case 1 :
                        blit(route,screen,0,0,20*xm, 20*ym,20,20);
                        break;
                    case 2 :
                        blit(eau,screen,0,0,20*xm, 20*ym,80,120); // dessine l'objet
                        // mise à jour des chateaux d'eau
                        tabeaux[nbeau].xh=xm; //
                        tabeaux[nbeau].yh=ym; //
                        nbeau++;
                        break;
                    case 3 :
                        blit(elec,screen,0,0,20*xm, 20*ym,80,120);
                        tabelec[nbelec].xh=xm;
                        tabelec[nbelec].yh=ym;
                        nbelec++;
                        break;
                    case 4 :
                        blit(hab[0],screen,0,0,20*xm, 20*ym,60,60);
                        tabhab[nbhab].xh=xm;
                        tabhab[nbhab].yh=ym;
                        etathab[nbhab]=0;
                        nbhab++;
                        break;
                    }
                    capital-=cout; //mise à jour argent
                    affichecapital();
                }
            } // fin position bonne
        } // fin clic
    } // fin while
}