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
    m_button2_label.set_message("Le CYCLE de l'eau");

    // Initialisation d'un troisieme bouton avec du texte
    // On adapte le code du premier bouton en changeant le positionnement du bouton et le texte à afficher
    m_background.add_child(m_button3);
    m_button3.set_frame(300,400,200,50);
    m_button3.set_bg_color(BLANC);
    m_button3.add_child(m_button3_label);
    m_button3_label.set_message("L'OCEAN");


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


Thing::~Thing()
{

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



