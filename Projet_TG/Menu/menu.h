#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "../grman/grman.h"
#include <iostream>
#include <stack>
class Thing
{

private :

    /// Utiliser une top_box de type WidgetBox pour encapsuler
    /// tous les éléments de l'interface associés à votre objet
    grman::WidgetBox m_background;
    grman::WidgetImage m_pic_background;
    grman::WidgetCheckBox m_top_box;


    // Texte pour le menu d'introduction

    grman::WidgetText m_text_intro;

    // grman::WidgetBox m_boite_boutons;    //pas utilisé
    grman::WidgetButton m_button1;
    grman::WidgetText m_button1_label;
    grman::WidgetButton m_button2;
    grman::WidgetText m_button2_label;
    grman::WidgetButton m_button3;
    grman::WidgetText m_button3_label;

    //bouton pour fermer allegro
    grman::WidgetButton m_button_close;
    grman::WidgetImage m_button_close_image;

public :

    /// Le constructeur de la classe (pas forcément par défaut !)
    /// initialise les données des widgets, place la hiérarchie des sous-cadres etc...
    Thing();

    void initialise_menu0();
    void update0();

    // Initialisation & affichage du premier menu
    void initialise_menu1();
    void initialise_button_menu1();
    void initialise_background1();
    int update1();

    ~Thing();


};


class Menu
{

private :

 Thing menu;



public :

    // Méthode qui permettra l'affichage du menu
    int display_menu1();
   ~Menu();


};



#endif // MENU_H_INCLUDED
