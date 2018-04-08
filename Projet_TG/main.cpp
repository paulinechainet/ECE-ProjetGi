#include "grman/grman.h"
#include <iostream>
#include <string.h>
#include "Menu/menu.h"
#include "graph.h"



int main()
{
    int boucle=0;
    int path_Matrice;
    int temp=-1;
    int sommet;
    int choix_menu(0);

    std::string picname;
    char a='v';

    bool fin_boucle(false);


    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    do
    {
        //Affichage Ecran Titre
        Menu menu;
        //Choix du menu
        path_Matrice=menu.display_menu1();

        Graph g;
        g.init(path_Matrice);

        g.loadSave(path_Matrice);

        /// Vous gardez la main sur la "boucle de jeu"while(fin==0)
        /// ( contrairement à des frameworks plus avancés )

        while ( fin_boucle==false )
        {
            //test
            g.update();

            g.regroup(path_Matrice);
s


            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();

            fin_boucle=g.update_stepquit();
        }
        fin_boucle=false;

        std::cout<< "Quitter le jeu ? 1. oui 0.non  "<<std::endl;
        std::cin>> boucle;

    }
    while(boucle==0);

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


