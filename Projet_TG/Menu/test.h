#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED
#include "
#include <iostream>
#include <stack>


/***************************************************
                    THING (test)

  Cette classe correspond au cadre en bas � gauche
  avec diff�rents bidules interactifs assembl�s dessus
  VOIR LE CONSTRUCTEUR ET LA METHODE UPDATE EN DETAIL
  ( dans test.cpp ) pour d�crypter l'utilisation
  des widgets propos�s ( vous pouvez en ajouter d'autres
  en compl�tant widget.h et widget.cpp, r�pertoire
  de projet grman )
****************************************************/
class Thing
{

private :

    /// Utiliser une top_box de type WidgetBox pour encapsuler
    /// tous les �l�ments de l'interface associ�s � votre objet
    grman::WidgetBox m_background;
    grman::WidgetImage m_pic_background;
    grman::WidgetCheckBox m_top_box;


    // Texte pour le menu d'introduction

    grman::WidgetText m_text_intro;

    //definition des boutons




    //Boutons pour la selectrion des graphes
    // grman::WidgetBox m_boite_boutons;    //pas utilis�
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

    /// Le constructeur de la classe (pas forc�ment par d�faut !)
    /// initialise les donn�es des widgets, place la hi�rarchie des sous-cadres etc...
    Thing();

    void initialise_menu0();
    void update0();

    // Initialisation & affichage du premier menu
    void initialise_menu1();
    void initialise_button_menu1();
    void initialise_background1();
    void update1();

    ~Thing();


};


#endif // TEST_H_INCLUDED
