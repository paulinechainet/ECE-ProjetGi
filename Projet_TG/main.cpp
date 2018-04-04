#include "grman/grman.h"
#include <iostream>
#include <string.h>

#include "graph.h"


int main()
{
    int path_Matrice;

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    std::cout<< "Numero de fichier a charger : ";
    std::cin>> path_Matrice;

    /// Le nom du r�pertoire o� se trouvent les images � charger
    //grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;

    g.load_graph(path_Matrice);
    g.show_graph_console();




    //g.make_example();


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {

        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


