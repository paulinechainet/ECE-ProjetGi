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

    /// Le nom du répertoire où se trouvent les images à charger
    //grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;

    g.load_graph(path_Matrice);
    g.show_graph_console();

    std::cout <<std::endl;
    std::cout <<std::endl;

    g.load_graphPOP(path_Matrice);
    g.show_graph_consolePOP();

    std::cout <<std::endl;
    std::cout <<std::endl;

    //g.add_vertex();
    //g.display_vertices();

    std::cout <<std::endl;
    std::cout <<std::endl;

    //g.add_edge();
    //g.display_edges();

    //g.make_example();
    g.displayAlleg(path_Matrice);

    g.display_edges();
    g.display_vertices();


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


