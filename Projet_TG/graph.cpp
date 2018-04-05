#include "graph.h"

/************************************************************************************************************************************************************************************************************
                                            VERTEX
*************************************************************************************************************************************************************************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}

void Vertex::displayVertex()
{
    std::cout<<m_indice_sommet << " " << m_value <<" " <<m_pop<<" "<<std::endl;
}


/************************************************************************************************************************************************************************************************************
                                            EDGE
*************************************************************************************************************************************************************************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}

void Edge::display_edge()
{
    std::cout << m_from << " " << m_to << " " << m_weight << std::endl;
}


/************************************************************************************************************************************************************************************************************
                                            GRAPH
**********************************************************************************************************************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}

void Graph::displayAlleg(int path)
{
    std::string pathfolder,pathpic;

    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    if(path==1)
    {
        m_ordre = 20;
    }
    else if(path==2)
    {

    }
    else if(path==3)
    {

    }
}

///Méthode pour lire les fichiers et le load dans les différents conteneurs
void Graph::load_graph(int fic)
{
    std::string fic_name;
    std::vector<int> temp(m_ordre,0);

    if(fic==1)
    {
        fic_name ="Matrice_P/savane.txt";
        m_ordre = 20;
    }
    else if(fic==2)
    {

    }
    else if(fic==3)
    {

    }
    else
    {
        std::cout << "erreur fatale";
        exit(1);
    }

    for(int i(0);i<m_ordre; i++)
    {
        m_matP.push_back(temp);
    }

    std::ifstream fichier(fic_name, std::ios::in);

    if(!fichier.is_open())  // si l'ouverture echoue
    {
        std::cout << "Erreur à l'ouverture de la matrice d'adjacence !" << std::endl;
    }

    for(int i(0);i<m_ordre ; i++)
    {
        for(int j(0);j<m_ordre ; j++)
        {
            fichier >>  m_matP[i][j];
        }
    }

    fichier.close();
}

///affichage du graph en console
void Graph::show_graph_console()
{
    for(int i(0);i<m_ordre ; i++)
    {
        for(int j(0);j<m_ordre ; j++)
        {
            std::cout<< m_matP[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

///chargement du graph population
void Graph::load_graphPOP(int fic)
{
    std::string fic_name;
    int temp;

     if(fic==1)
     {
         fic_name ="Population/savane.txt";
         m_ordre=20;
     }
     else if(fic==2)
     {

     }
     else if(fic==3)
     {

     }
     else
     {
         std::cout << "erreur fatale";
         exit(1);
     }

    std::ifstream fichier(fic_name, std::ios::in);

    if(!fichier.is_open())  // si l'ouverture echoue
    {
        std::cout << "Erreur à l'ouverture du tableau des populations !" << std::endl;
    }

    for(int i(0); i<m_ordre ; i++)
    {
        fichier >>  temp;
        m_matPOP.push_back(temp);
    }

    fichier.close();
}

///affichage graph pop en console
void Graph::show_graph_consolePOP()
{
    for(int i(0); i<m_ordre ; i++)
    {
        std::cout<< m_matPOP[i]<<" ";
    }
}

///Display des sommets
void Graph::display_vertices()
{
    for(int i(0); i<m_ordre;i++)
    {
        m_vertices[i].displayVertex();
    }
}

///Affichage des arretes
void Graph::display_edges()
{
    for(int i(0); i<m_nbedges;i++)
    {
        m_edges[i].display_edge();
    }
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    ///on verifie si le ssommet n'existe pa deja , si c'est la cas on ne fait rien
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        //throw "Error adding vertex";
    }
    else///ici on ajoute le sommet et on ajoute ses arretes si il en a avec les sommets deja présents
    {
        // Création d'une interface de sommet
        VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
        // Ajout de la top box de l'interface de sommet
        m_interface->m_main_box.add_child(vi->m_top_box);
        // On peut ajouter directement des vertices dans la map avec la notation crochet :
        m_vertices[idx] = Vertex(idx,0,value, vi);

        for (int i(0);i<m_ordre;i++)
        {
            for (int j(0);j<m_ordre;j++)
            {
                if ((m_matP[i][j] != 0))
                {
                    add_interfaced_edge(m_nbedges,i,j,m_matP[i][j]);
                    //std::cout<<m_nbedges<<std::endl;
                    m_nbedges++;
                }
            }
        }
    }
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    int ok=0;

    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        // "Error adding edge";
        ok=1;
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        //std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        //throw "Error adding edge";
        ok=1;
    }

    if(ok==0)
    {
        EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
        m_interface->m_main_box.add_child(ei->m_top_edge);
        m_edges[idx] = Edge(0, 0, weight, ei);
    }

}

void Graph::save(int path)
{
    savePOP(path);
    //saveCoef();
    //savePOS();
}

void Graph::add_vertex()
{




}

void Graph::savePOP(int path)
{
    std::string ficName;

    if(key[KEY_D])
    {

        if(path==1)
        {
            ficName ="Population/savane.txt";
        }
        else if(path==2)
        {

        }
        else if(path==3)
        {

        }


        std::ofstream fichier(ficName, std::ios::out | std::ios::trunc);

        if(!fichier)
        {
            std::cout<<"erreur enregistrement POP"<<std::endl;
        }

        for(int i(0);i<m_ordre;i++)
        {

        }
    }
}

void Graph::saveCoef()
{

}

void Graph::savePOS()
{


}

Vertex Graph::getVertex(int t)
{
    return m_vertices[t];
}

int Graph::getPop(int t)
{
    return m_matPOP[t];
}

std::string Graph::getPicName(int idx, int path)
{
    std::string name;

    if(path==1)
    {
        name="pics/savane/" + std::to_string(idx) + ".jpg" ;
    }
    return name;
}

