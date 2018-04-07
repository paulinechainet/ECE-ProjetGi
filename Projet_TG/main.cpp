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
    std::string picname;
    char a='v';
    int sommet;
    int choix_menu;

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    do
    {
    //Affichage Ecran Titre
    Menu menu;
    //Choix du menu
    choix_menu=menu.display_menu1();
    //std::cin>>  choix_menu;
    path_Matrice=choix_menu;

        Graph g;
        g.init(path_Matrice);

        g.loadSave(path_Matrice);

        /// Vous gardez la main sur la "boucle de jeu"while(fin==0)
        /// ( contrairement à des frameworks plus avancés )
        while ( !key[KEY_ESC] )
        {
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g.update();

            g.add_vertex(path_Matrice);///H
            g.del_vertex();///D

            g.save(path_Matrice);///B
            g.test_remove_edge(sommet);///P
            g.toutesLesCompo();///L

            if(key[KEY_O])
            {
                g.retrachement();
            }





            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
        }

        //g.display_vertices();
        g.display_edges();





        std::cout<< "Quitter le jeu ? 1. oui 0.non  "<<std::endl;
        std::cin>> boucle;

    }while(boucle==0);

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


