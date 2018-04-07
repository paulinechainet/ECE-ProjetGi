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
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
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

    m_posx = m_interface->m_top_box.get_posx();
    m_posy = m_interface->m_top_box.get_posy();

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
    std::cout<<"indice : "<<m_indice_sommet << " value : " << m_value <<" popu : " <<m_pop<<" pos y "<<m_posx<<" pos x :"<<m_posy<<" "<<std::endl;
}


/************************************************************************************************************************************************************************************************************
                                            EDGE
*************************************************************************************************************************************************************************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to, int idx)
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
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);


    m_box_edge.add_child(m_idx);
    m_idx.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_idx.set_message(std::to_string(idx));

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



void Graph::init(int path)
{
    std::string pathfolder,pathpic;

    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    load_graphPOP(path);
    load_graph(path);
    //displayAlleg(path);
}

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

    ///Bouton Quitter
    m_tool_box.add_child(m_quit_button);
    m_quit_button.set_frame(2, 2,80, 80);
    m_quit_cross.set_pic_name("pics/cruce/croixrouge.jpg");
    m_quit_cross2.set_pic_name("pics/cruce/croixrouge2.jpg");
    m_quit_cross.set_pic_idx(999);
    m_quit_cross2.set_pic_idx(998);
    m_quit_button.set_gravity_x(grman::GravityX::Right);
    m_quit_cross2.set_gravity_x(grman::GravityX::Right);
    m_quit_button.add_child(m_quit_cross);

    ///Bouton Sauvegarder
    m_tool_box.add_child(m_save_button);
    m_save_button.set_frame(2,85,80, 80);
    m_save_pic_a.set_pic_name("pics/save/sauvegarderA.jpg");
    m_save_pic_n.set_pic_name("pics/save/sauvegarderN.jpg");
    m_save_pic_a.set_pic_idx(997);
    m_save_pic_n.set_pic_idx(996);
    m_save_pic_a.set_gravity_x(grman::GravityX::Right);
    m_save_pic_n.set_gravity_x(grman::GravityX::Right);
    m_save_button.add_child(m_save_pic_a);

    ///Bouton Pause
    m_tool_box.add_child(m_pause_button);
    m_pause_button.set_frame(2, 168,80, 80);
    m_pause_pic_a.set_pic_name("pics/stop/pause2.jpg");
    m_pause_pic_n.set_pic_name("pics/stop/pause1.jpg");
    m_pause_pic_a.set_pic_idx(995);
    m_pause_pic_a.set_pic_idx(994);
    m_pause_pic_a.set_gravity_x(grman::GravityX::Right);
    m_pause_pic_n.set_gravity_x(grman::GravityX::Right);
    m_pause_button.add_child(m_pause_pic_n);

    ///Bouton Ajouter
    m_tool_box.add_child(m_ajou_button);
    m_ajou_button.set_frame(2, 252,80, 80);
    m_ajou_pic.set_pic_name("pics/ajoutsuppr/ajout.jpg");
    m_ajou_button.add_child(m_ajou_pic);
    m_ajou_pic.set_gravity_x(grman::GravityX::Right);

    ///Bouton Supprimer
    m_tool_box.add_child(m_suppr_button);
    m_suppr_button.set_frame(2,335, 80, 80);
    m_suppr_pic.set_pic_name("pics/ajoutsuppr/suppr.jpg");
    m_suppr_button.add_child(m_suppr_pic);
    m_suppr_pic.set_gravity_x(grman::GravityX::Right);

    ///Bouton F. Connexité
    m_tool_box.add_child(m_fconnextite_button);
    m_fconnextite_button.set_frame(2,418, 80, 80);
    m_fconnextite_pic.set_pic_name("pics/connexite/palettedecouleur.jpg");
    m_fconnextite_button.add_child(m_fconnextite_pic);
    m_fconnextite_pic.set_gravity_x(grman::GravityX::Right);

    ///Bouton F. Connexité RAZ
    m_tool_box.add_child(m_fconnextiteRAZ_button);
    m_fconnextiteRAZ_button.set_frame(2,501, 80, 80);
    m_fconnextiteRAZ_pics.set_pic_name("pics/connexite/raz.jpg");
    m_fconnextiteRAZ_button.add_child(m_fconnextiteRAZ_pics);
    m_fconnextiteRAZ_pics.set_gravity_x(grman::GravityX::Right);

    ///Bouton Suppr arrete
    m_tool_box.add_child(m_supprarrete_button);
    m_supprarrete_button.set_frame(2,504, 80,80);
    m_supprarrete_pics.set_pic_name("pics/ajoutsuppr/supprarrete.jpg");
    m_supprarrete_button.add_child(m_supprarrete_pics);
    m_supprarrete_pics.set_gravity_x(grman::GravityX::Right);
}



///Chargement////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

    for(int i(0); i<m_ordre; i++)
    {
        m_matP.push_back(temp);
    }

    std::ifstream fichier(fic_name, std::ios::in);

    if(!fichier.is_open())  // si l'ouverture echoue
    {
        std::cout << "Erreur à l'ouverture de la matrice d'adjacence !" << std::endl;
    }

    for(int i(0); i<m_ordre ; i++)
    {
        for(int j(0); j<m_ordre ; j++)
        {
            fichier >>  m_matP[i][j];
        }
    }

    fichier.close();
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


///DISPLAY////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///affichage du graph en console
void Graph::show_graph_console()
{
    for(int i(0); i<m_ordre ; i++)
    {
        for(int j(0); j<m_ordre ; j++)
        {
            std::cout<< m_matP[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
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
    for(int i(0); i<m_ordre; i++)
    {
        m_vertices[i].displayVertex();
    }

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
}

///Affichage des arretes
void Graph::display_edges()
{
    for(int i(0); i<m_nbedges; i++)
    {
        m_edges[i].display_edge();
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    //std::cout<<m_nbedges;
}

bool Graph::update_stepquit()
{
    bool a(false);
    if (m_interface->m_quit_button.clicked())
    {
        a=true;
        return a;
    }
}

void Graph::update_stepajout(int path)
{
    int temp;
    bool a(false);
    if (m_interface->m_ajou_button.clicked())
    {
        a=true;

    }
    if (a==true)
    {
        std::cout<<"Indice de votre sommet ? ";
        std::cin>> temp;
        std::cout<< std::endl;

        if(temp>=0 && temp<=19)
        {
            add_interfaced_vertex(temp,getPop(temp),100,100,getPicName(temp,path));
        }
    }
}

void Graph::update_stepsave(int path)
{
    int temp;
    bool a(false);
    if (m_interface->m_save_button.clicked())
    {
        a=true;

    }
    if (a==true)
    {
        std::string ficName;

        if(path==1)
        {
            ficName ="Save/savane.txt";
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

        for(int i(0); i<m_ordre; i++)
        {

            if(m_vertices[i].m_indice_sommet!= 0)
            {
                std::cout<<"sauvgarde eff"<< std::endl;
                fichier<< m_vertices[i].m_indice_sommet<<" ";
                fichier<< m_vertices[i].m_value<<" ";
                fichier<< m_vertices[i].m_pop<<" ";
                fichier<< m_vertices[i].m_posx<<" ";
                fichier<< m_vertices[i].m_posy<<" ";
                fichier<< std::endl;
            }
        }
        fichier.close();
    }

}

void Graph::update_stepsuppr()
{
    int temp;
    bool a(false);
    if (m_interface->m_suppr_button.clicked())
    {
        a=true;

    }
    if (a==true)
    {
        int fin(0);
        std::cout<<"Indice du sommet présent sur le graph a supprimer : "<<std::endl;
        std::cin>>temp;
        Vertex &remed =m_vertices.at(temp);
        std::cout<< "removing vertex "<< temp <<" "<< remed.m_pop <<std::endl;

        if(m_interface && remed.m_interface)
        {
            m_interface->m_main_box.remove_child(remed.m_interface->m_top_box);
            m_vertices.erase(temp);
        }
    }
}

void Graph::update_stepfconnexite()
{
    int temp;
    bool a(false);
    if (m_interface->m_fconnextite_button.clicked())
    {
        a=true;

    }
    if (a==true)
    {
        std::cout<<"Bouton forte connexité"<<std::endl;
    }
}
void Graph::update_stepfconnexiteRAZ()
{
    int temp;
    bool a(false);
    if (m_interface->m_fconnextiteRAZ_button.clicked())
    {
        a=true;

    }
    if (a==true)
    {
        std::cout<<"Bouton forte connexité RAZ"<<std::endl;
    }
}
void Graph::update_stepsupprarrete(int eidx)
{
        int temp;
    bool a(false);
    if (m_interface->m_supprarrete_button.clicked())
    {
        a=true;

    }
    if (a==true)
    {
        std::cout<<"arrete a del : " <<std::endl;
        std::cin>> eidx;
        /// référence vers le Edge à enlever
        Edge &remed=m_edges.at(eidx);

        if (m_interface && remed.m_interface)
        {

            m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
        }

        /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
        /// References sur les listes de edges des sommets from et to
        std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
        std::vector<int> &veto = m_vertices[remed.m_to].m_in;
        vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
        veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
        /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
        /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
        m_edges.erase( eidx );
    }
}

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update(int path)
{
    int temp;

    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();
        this->set_thickness();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    if (m_interface->m_pause_button.clicked())
    {
        std::cout<<"Ca Marche pause"<<std::endl;
    }
}



/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    ///on verifie si le ssommet n'existe pa deja , si c'est la cas on ne fait rien
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
    }
    else///ici on ajoute le sommet et on ajoute ses arretes si il en a avec les sommets deja présents
    {
        // Création d'une interface de sommet
        VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
        // Ajout de la top box de l'interface de sommet
        m_interface->m_main_box.add_child(vi->m_top_box);
        // On peut ajouter directement des vertices dans la map avec la notation crochet :
        m_vertices[idx] = Vertex(idx,0,value, vi);

        for (int j(0); j<m_ordre; j++)
        {
            if ((m_matP[idx][j] != 0))
            {
                //std::cout<<j<<"coucou c'est j"<<std::endl;
                //std::cout<<idx<<"coucou c'est idx"<<std::endl;
                add_interfaced_edge(m_nbedges,idx,j,m_matP[idx][j]);
            }
            else if((m_matP[j][idx] != 0))
            {
                add_interfaced_edge(m_nbedges,j,idx,m_matP[idx][j]);
            }
        }
    }

    for(const auto& elem:m_vertices[idx].m_in)
    {
        std::cout << elem << " sommets qui in  m_in de "<<idx <<std::endl;
    }

    for(const auto& elem:m_vertices[idx].m_out)
    {
        std::cout << elem << " sommets qui out de m_out de   "<<  idx <<std::endl;
    }
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    int ok=0;

    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        ok=1;
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        //std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        ok=1;
    }

    if(ok==0)
    {

        //m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );

        EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2],idx);
        m_interface->m_main_box.add_child(ei->m_top_edge);
        m_edges[idx] = Edge(id_vert1, id_vert2, weight, ei);

        /// OOOPS ! Prendre en compte l'arc ajouté dans la topologie du graphe !

        m_edges[idx].m_from = id_vert1;
        m_edges[idx].m_to = id_vert2;

        m_vertices[id_vert1].m_out.push_back(idx);
        m_vertices[id_vert2].m_in.push_back(idx);

        //std::cout<<m_nbedges<<std::endl;
        m_nbedges++;
    }
}


/// Sauvegarde//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Graph::loadSave(int path)
{

    int temp1(0),temp2(0),temp3(0),temp4(0),temp5(0),temp6(0);

    std::string ficName;
    std::string ligne;
    std::string name;
    std::vector<int> test;

    if(path==1)
    {
        ficName ="Save/savane.txt";
        //std::cout<<"path ok"<<std::endl;    if(path==1)

        name="pics/savane/" ;


    }
    else if(path==2)
    {

    }
    else if(path==3)
    {

    }

    std::ifstream fichier(ficName, std::ios::in);

    if(!fichier.is_open())  // si l'ouverture echoue
    {
        std::cout << "Erreur à l'ouverture du fichier save !" << std::endl;
    }

    while(std::getline(fichier, ligne))
    {
        temp1++;
        //std::cout<< temp1;
    }



    fichier.clear();
    fichier.seekg(0,std::ios::beg);


    //temp1= 6;

    std::cout<< temp1;

    for(int i(0); i<temp1; i++)
    {
        fichier >> temp2;
        fichier >> temp3;
        fichier >> temp4;
        fichier >> temp5;
        fichier >> temp6;

        if(temp2!=0)
        {
            add_interfaced_vertex(temp2,temp4,temp5,temp6, name+ std::to_string(temp2) + ".jpg" );
        }

    }

    fichier.close();



}


///   GETTERs//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


///SSETTERSS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Graph::set_thickness()
{
    for (auto& elem: m_edges)
        elem.second.set_thickness(elem.second.m_weight);
}

std::vector<int> Graph::uneCompoCo(int s, std::vector<std::vector<int>> matrice)
{
    std::vector<std::vector<int>> trans;
    std::vector<int> temp(m_ordre,0);

    ///variables loacales
    std::vector<int> c1(m_ordre,0);
    std::vector<int> c2(m_ordre,0);
    std::vector<int> c(m_ordre,0);
    std::vector<int> marque(m_ordre,0);
    int ajoute=1;

    ///constru mat trans
    for(int i(0); i<m_ordre ; i++)
    {
        trans.push_back(temp);
    }

    for(int i = 0; i < m_ordre; ++i)
        for(int j = 0; j < m_ordre; ++j)
        {
            trans[j][i]=matrice[i][j];
        }

    /*for(int i = 0; i < m_ordre; ++i)
    {
        for(int j = 0; j < m_ordre; ++j)
        {
            std::cout<<trans[i][j];
        }
        std::cout<<std::endl;
    }*/

    c1[s]=1;
    c2[s]=1;


    ///recherche des composantes connexes partant de s a ajouter dans c1
    while(ajoute)
    {
        ajoute = 0;

        for(int i(0); i<m_ordre; i++)
        {
            if(!marque[i] && c1[i])
            {
                marque[i]=1;

                for(int j(0); j<m_ordre; j++)
                {
                    if(m_matP[i][j] && !marque[j])
                    {
                        c1[j]=1;
                        ajoute = 1;
                    }
                }
            }
        }
    }

    for(int i(0); i<m_ordre; i++)
    {
        marque[i]=0;
    }

    ajoute =1;

    ///recherche des composantes connexes partant de s a ajouter dans c2
    while(ajoute)
    {
        ajoute = 0;

        for(int i(0); i<m_ordre; i++)
        {
            if(!marque[i] && c2[i])
            {
                marque[i]=1;

                for(int j(0); j<m_ordre; j++)
                {
                    if(trans[i][j] && !marque[j])
                    {
                        c2[j]=1;
                        ajoute = 1;
                    }
                }
            }
        }
    }

    for(int i(0); i<m_ordre; i++)
    {
        c[i]=c1[i] & c2[i];
    }

    return c;
}

void Graph::toutesLesCompo()
{
    std::vector<std::vector<int>> matrice;
    std::vector<int> temp(m_ordre,0);

    std::vector<std::vector<int>> tacb;

    std::vector<int> marque(m_ordre, 0);


    for(int i(0); i<m_ordre ; i++)
    {
        matrice.push_back(temp);
        tacb.push_back(temp);
    }

    for(int i = 0; i < m_ordre; ++i)
    {
        for(int j = 0; j < m_ordre ; ++j)
        {
            for(int k(0); k<m_edges.size(); k++)
            {
                if(m_edges[k].m_from == i && m_edges[k].m_to == j)
                {
                    matrice[i][j]=1;
                }
            }
        }
    }

    for(int i = 0; i < m_ordre; ++i)
    {
        if(!marque[i])
        {
            tacb[i]= uneCompoCo(i,matrice);
        }
    }

    for(int i(0); i<m_ordre; i++)
    {
        for(int j(0); j<m_ordre; j++)
        {
            std::cout<<tacb[i][j];
        }
        std::cout<<std::endl;
    }



}

Thing2::Thing2()
{

    ///Boite Totale
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    ///Boite d'Objet
    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    ///Boite de Graph
    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    ///Bouton Quitter
    m_tool_box.add_child(m_quit_button);
    m_quit_button.set_frame(2, 2,80, 80);
    m_quit_cross.set_pic_name("pics/cruce/croixrouge.jpg");
    m_quit_cross2.set_pic_name("pics/cruce/croixrouge2.jpg");
    m_quit_cross.set_pic_idx(999);
    m_quit_cross2.set_pic_idx(998);
    m_quit_button.set_gravity_x(grman::GravityX::Right);
    m_quit_cross2.set_gravity_x(grman::GravityX::Right);
    m_quit_button.add_child(m_quit_cross);

    ///Bouton Sauvegarder
    m_tool_box.add_child(m_save_button);
    m_save_button.set_frame(2,85,80, 80);
    m_save_pic_a.set_pic_name("pics/save/sauvegarderA.jpg");
    m_save_pic_n.set_pic_name("pics/save/sauvegarderN.jpg");
    m_save_pic_a.set_pic_idx(997);
    m_save_pic_n.set_pic_idx(996);
    m_save_pic_a.set_gravity_x(grman::GravityX::Right);
    m_save_pic_n.set_gravity_x(grman::GravityX::Right);
    m_save_button.add_child(m_save_pic_a);

    ///Bouton Pause
    m_tool_box.add_child(m_pause_button);
    m_pause_button.set_frame(2, 168,80, 80);
    m_pause_pic_a.set_pic_name("pics/stop/pause2.jpg");
    m_pause_pic_n.set_pic_name("pics/stop/pause1.jpg");
    m_pause_pic_a.set_pic_idx(995);
    m_pause_pic_a.set_pic_idx(994);
    m_pause_pic_a.set_gravity_x(grman::GravityX::Right);
    m_pause_pic_n.set_gravity_x(grman::GravityX::Right);
    m_pause_button.add_child(m_pause_pic_n);

    ///Bouton Ajouter
    m_tool_box.add_child(m_ajou_button);
    m_ajou_button.set_frame(2, 252,80, 80);
    m_ajou_pic.set_pic_name("pics/ajoutsuppr/ajout.jpg");
    m_ajou_button.add_child(m_ajou_pic);
    m_ajou_pic.set_gravity_x(grman::GravityX::Right);

    ///Bouton Supprimer
    m_tool_box.add_child(m_suppr_button);
    m_suppr_button.set_frame(2,335, 80, 80);
    m_suppr_pic.set_pic_name("pics/ajoutsuppr/suppr.jpg");
    m_suppr_button.add_child(m_suppr_pic);
    m_suppr_pic.set_gravity_x(grman::GravityX::Right);

    ///Bouton F. Connexité
    m_tool_box.add_child(m_fconnextite_button);
    m_fconnextite_button.set_frame(2,418, 80, 80);
    m_fconnextite_pic.set_pic_name("pics/connexite/palettedecouleur.jpg");
    m_fconnextite_button.add_child(m_fconnextite_pic);
    m_fconnextite_pic.set_gravity_x(grman::GravityX::Right);

    ///Bouton F. Connexité RAZ
    m_tool_box.add_child(m_fconnextiteRAZ_button);
    m_fconnextiteRAZ_button.set_frame(2,501, 80, 80);
    m_fconnextiteRAZ_pics.set_pic_name("pics/connexite/raz.jpg");
    m_fconnextiteRAZ_button.add_child(m_fconnextite_pic);
    m_fconnextite_pic.set_gravity_x(grman::GravityX::Right);

    ///Bouton Suppr arrete
    m_tool_box.add_child(m_supprarrete_button);
    m_supprarrete_button.set_frame(2,504, 80,80);
    m_supprarrete_pics.set_pic_name("pics/ajoutsuppr/supprarrete.jpg");
    m_supprarrete_button.add_child(m_supprarrete_pics);
    m_supprarrete_pics.set_gravity_x(grman::GravityX::Right);
}

void Thing2::update()
{
    m_top_box.update();


    if (m_suppr_button.clicked())
    {
        std::cout<<"Ca Marche suppr"<<std::endl;
    }
    if (m_ajou_button.clicked())
    {
        std::cout<<"Ca Marche ajout"<<std::endl;
    }
    if (mouse_x<80 && mouse_y<235 && mouse_y>165 && mouse_b==true)
    {
        while (mouse_x<80 && mouse_y<235 && mouse_y>165 && mouse_b==true)
        {
            m_pause_button.add_child(m_pause_pic_a);
        }
    }
    if (m_pause_button.clicked())
    {
        std::cout<<"Ca Marche pause"<<std::endl;
    }
    if (mouse_x<80 && mouse_y<155 && mouse_y>85)
    {
        while(mouse_x<80 && mouse_y<155 && mouse_y>85)
        {
            m_save_button.add_child(m_save_pic_a);
        }
    }

    if (m_save_button.clicked())
    {
        std::cout<<"Ca Marche sve"<<std::endl;
    }
    if (mouse_x<80 && mouse_y<80)
    {
        while (mouse_x<80 && mouse_y<80)
        {
            m_quit_button.add_child(m_quit_cross2);
        }
    }

    if (m_quit_button.clicked())
    {
        std::cout<<"Ca Marche"<<std::endl;
    }
}
