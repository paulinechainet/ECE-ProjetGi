#include "grman/grman.h"
#include <iostream>
#include <string.h>
#include "allegro.h"
#include "graph.h"



int main()
{
    int path_Matrice;
    int temp=0;
    std::string picname;
    BITMAP *bmp1;
    BITMAP *bmp2;
    BITMAP *ecrantouche;

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    std::cout<< "Numero de fichier a charger : ";
    std::cin>> path_Matrice;

    Graph g;

    g.load_graphPOP(path_Matrice);
    g.load_graph(path_Matrice);

    g.displayAlleg(path_Matrice);

    ///TEST ALLEGRO
    //grman::allegro_buffer_touche(ecrantouche);
    //grman::allegro_prog_chargement_croix(bmp1, bmp2);
    /// Vous gardez la main sur la "boucle de jeu"while(fin==0)
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();
        //g.m_interface.

        if(key[KEY_H])
        {
            std::cout<<"Indice de votre sommet ? ";
            std::cin>> temp;
            std::cout<< std::endl;

            g.add_interfaced_vertex(temp,g.getPop(temp),100,100,g.getPicName(temp,path_Matrice));
        }

        //g.save(path_Matrice);

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }


    //std::cout<< "Temp ? ";
    //std::cin>> temp;

    //}while(temp==0);

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();
