#include"menu.h"


Thing::Thing()
{

}

void Thing::initialise_menu0()
{
    m_background.set_frame(0,0,1028,768);
    m_background.add_child(m_pic_background);
    m_pic_background.set_pic_name("pics/menu0.bmp");

    m_background.add_child(m_text_intro);
    m_text_intro.set_frame(350,550,200,50);
    m_text_intro.set_message("Cliquez sur la barre espace pour acceder au menu");

}
// Initialisation des élements qui composeront notre premier menu de choix
void Thing::initialise_menu1()
{
    initialise_background1();
    initialise_button_menu1();
}

void Thing:: initialise_background1()
{
      m_background.set_frame(0,0,1028,768);      // mise en place d'un WidgetBox m_background de dimensions 800x600
    m_background.add_child(m_pic_background);             // Affiliation de l'image fond dans la WidgetBox
    m_pic_background.set_pic_name("pics/nature.bmp");   // Affiliation de l'image en BITMAP à l'entité fond

}
void Thing::initialise_button_menu1()
{

    // Initialisation d'un 1er bouton avec un texte

    m_background.add_child(m_button1);            // Affiliation du premier bouton à la widgetBox
    m_button1.set_frame(300,200,200,50);    // Positionnement du bouton en x=300, y=200 en rectangle en 200x50
    m_button1.set_bg_color(BLANC);          // Remplissage du carré en blanc
    m_button1.add_child(m_button1_label);    // Affiliation du texte au 1er bouton
    m_button1_label.set_message("ANIMAUX DE LA SAVANE");        // definition du texte correspondant au premier bouton



    // Initialisation d'un deuxieme bouton avec du texte
    // On adapte le code du premier bouton en changeant le positionnement du bouton et le texte à afficher
    m_background.add_child(m_button2);
    m_button2.set_frame(300,300,200,50);
    m_button2.set_bg_color(BLANC);
    m_button2.add_child(m_button2_label);
    m_button2_label.set_message("LE DEUXIEME");

    // Initialisation d'un troisieme bouton avec du texte
    // On adapte le code du premier bouton en changeant le positionnement du bouton et le texte à afficher
    m_background.add_child(m_button3);
    m_button3.set_frame(300,400,200,50);
    m_button3.set_bg_color(BLANC);
    m_button3.add_child(m_button3_label);
    m_button3_label.set_message("LE TROISIEME");


    // Création d'un bouton close qui permet de quitter le programme
    //toujours le même principe que les boutons codés precedement mais cette fois au lieu du texte, on l'affille à une image

    m_background.add_child(m_button_close);   // Affiliation du bouton close à la WidgetBox
    m_button_close.set_dim(40,40);      // Creation d'un carré de dimension 40x40
    // Positionnement du bouton dans l'angle droit haut
    m_button_close.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_button_close.set_bg_color(ROUGE);         //Coloration du bouton en rouge
    m_button_close.add_child(m_button_close_image);     //Affiliation du bouton à une image
    m_button_close_image.set_pic_name("pics/cls.bmp");       //l'image correspond à une image de base
}



// Méthode qui permet d'effectuer des actions sur notre 1er menu selon les actions faites par l'utilisateur

void Thing::update0()
{

    m_background.update();



}

int Thing::update1()
{

    int choix_menu;
    // Utilisation de la fonction update pour le premier menu
    m_background.update();

    // Si on appuie sur le bouton "ANIMAUX DE LA SAVANE", le premier bouton, alors ...
    if ( m_button1.clicked() )
    {
        choix_menu=1;
        return choix_menu;
    }

    // Si on appuie sur le deucieme bouton  alors ...
    if (m_button2.clicked())
    {
        choix_menu=2;
        return choix_menu;
    }

    // Si on appuie sur le troisieme bouton alors ..
    if (m_button3.clicked())
    {
        choix_menu=3;
        return choix_menu;
    }

    // Si on appuie sur le bouton de croix alors ...
    if (m_button_close.clicked())
    {
        // La fenetre Allegro 4 se ferme et on retourne exclusivement en mode console
        exit(EXIT_FAILURE);
    }
}


/// STOCKAGE DU CODE DE FERCOQ ///
/*/// Une méthode update de la classe doit être appelée dans la boucle de jeu
/// et cette méthode doit propager l'appel à update sur les widgets contenus...
/// Cette méthode fait le lien entre l'interface, les événements, et les conséquences
void Thing::update1()
{

    /// Si tous les widgets dépendants de l'objet sont dans une top box
    /// alors ce seul appel suffit (la propagation d'updates se fait ensuite automatiquement)
    m_fond.update();

    /// Ici on montre la récupération de la valeur booléenne du check box en bas à gauche
    /*  /// pour décider d'animer ou pas le widget d'image au centre
      m_img_anime.set_animate( m_marche.get_value() );

      /// Ici on montre la récupération de la valeur entière de l'ascenseur de droite
      /// pour décider du rythme d'animation
      m_img_anime.set_animate_tempo( m_regle_entier.get_value() );

      /// Ici on montre la récupération de la valeur réelle de l'ascenseur de gauche
      /// pour fixer l'ordonnée de l'image au centre
      m_img_anime.set_pos( m_img_anime.get_pos().x, 140-10.0*m_regle_reel.get_value() );

      /// Utilisation d'un bouton pour déclencher un événement
      /// L'accès à clicked() fait un reset : tant que le bouton n'est pas
      /// à nouveau cliqué les futurs accès à clicked seront faux
      /// ( Donc il faut appeler clicked() UNE FOIS ET UNE SEULE par update )

    if ( m_bouton1.clicked() )
    {
        std::cout << "bouton 1 !" << std::endl;

        /// Expérimental, ajout dynamique d'éléments, ATTENTION ICI ALLOCATION
         grman::WidgetImage * clown = new grman::WidgetImage(); // On pourrait déclarer auto ...
         m_dynaclowns.push(clown);
         m_top_box.add_child( *clown );
         clown->set_pic_name("crusty_xx4xx.png");
         clown->set_pos(rand()%100+10, rand()%100+110 );
         clown->set_animate();
         clown->set_animate_tempo(rand()%5+3);

         /// Mise à jour du nombre de clowns dynamiques sur le label du lien
         m_lien2_label.set_message( std::to_string( m_dynaclowns.size() ) );
    }

    if (m_bouton2.clicked())
    {
        std::cout<<"bouton 2!"<<std::endl;
    }


    if (m_bouton3.clicked())
    {
        std::cout<<"bouton 3"<<std::endl;
    }


    if (m_bouton_close.clicked())
    {
       exit(EXIT_FAILURE);
    }
    /// Utilisation de l'autre bouton (méchant clown) pour enlever un clown
    if ( m_bouton2.clicked() && !m_dynaclowns.empty() )
    {
        std::cout << "ARGHHH !" << std::endl;

        /// Expérimental, retrait dynamique d'éléments
        grman::WidgetImage * clown = m_dynaclowns.top(); // On pourrait déclarer auto ...
        m_dynaclowns.pop();

        // On est pas obligé d'enlever les éléments dans l'ordre inverse de leur ajout
        // il suffit de se souvenir de l'adresse de l'élément à supprimer
        m_top_box.remove_child( *clown );

        /// Le remove de la collection ne détruit pas l'objet
        /// C'est la responsabilité de la classe qui a fait new de faire delete
        delete clown;

        /// Mise à jour du nombre de clowns dynamiques sur le label du lien
        m_lien2_label.set_message( std::to_string( m_dynaclowns.size() ) );
    }


}*/


/// On a des allocations dynamiques dans m_dynaclowns => à nettoyer dans le destructeur
Thing::~Thing()
{
/*    while ( !m_dynaclowns.empty() )
    {
        delete m_dynaclowns.top();
        m_dynaclowns.pop();
    }*/
}


Menu::~Menu()
{

}

int Menu::display_menu1()
{
    int choix_menu, retour_menu;
    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )

    menu.initialise_menu0();
    do
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        menu.update0();


        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }
    while (!key[KEY_SPACE]);
    grman::mettre_a_jour();
    do
    {
        menu.initialise_menu1();
        choix_menu=menu.update1();
        if (choix_menu!=0)
        {
            std::cout<<choix_menu<<std::endl;
            return choix_menu;
        }
        grman::mettre_a_jour();

    }
    while (choix_menu==0);
    grman::mettre_a_jour();

}



