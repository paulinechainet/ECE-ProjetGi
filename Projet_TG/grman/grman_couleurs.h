#ifndef COULEURS_H_INCLUDED
#define COULEURS_H_INCLUDED

namespace grman
{

/// Les couleurs proposées. Il est possible d'en ajouter en respectant la syntaxe.
/// Faire une recherche "couleur html" dans google image pour d'autres valeurs.

#define NOIR 0x000000

#define GRIS 0x808080
#define GRISCLAIR 0xC0C0C0
#define GRISSOMBRE 0x696969

#define BLANC 0xFFFFFF
#define BLANCBLEU 0xF0FFFF
#define BLANCJAUNE 0xFFFFF0
#define BLANCROSE 0xFFFAFA

#define FUCHSIA 0xFE00FE
#define FUCHSIACLAIR 0xEE82EE
#define FUCHSIASOMBRE 0x9932CC

#define ROSE 0xFF69B4
#define ROSECLAIR 0xFFC0CB
#define ROSESOMBRE 0xFF1493

#define VIOLET 0x800080
#define VIOLETCLAIR 0xBA55D3
#define VIOLETSOMBRE 0x4A004A

#define MARRON 0x8000800
#define MARRONCLAIR 0xA52A2A
#define MARRONSOMBRE 0x8B0000

#define VERT 0x008000
#define VERTCLAIR 0x00FA9A
#define VERTSOMBRE 0x006400

#define VERTFLUO 0x00FF00
#define VERTFLUOCLAIR 0xADFF2F
#define VERTFLUOSOMBRE 0x32CD32

#define KAKI 0x808000
#define KAKICLAIR 0xA6A600
#define KAKISOMBRE 0x556B2F

#define CYAN 0x00FFFF
#define CYANCLAIR 0xE0FFFF
#define CYANSOMBRE 0x00CED1

#define BLEU 0x000FF
#define BLEUCLAIR 0x1E90FF
#define BLEUSOMBRE 0x00080

#define ROUGE 0xFF0000
#define ROUGECLAIR 0xFF6347
#define ROUGESOMBRE 0xDC143C

#define ORANGE 0xFF8000
#define ORANGECLAIR 0xFFA500
#define ORANGESOMBRE 0xFF4500

#define JAUNE 0xFFFF00
#define JAUNECLAIR 0xFFFACD
#define JAUNESOMBRE 0xFFD700

#define SABLE 0xFFF8DC
#define SABLECLAIR 0xF5DEB3
#define SABLESOMBRE 0xDEB887


/// !!! Systeme : ne pas intervenir sur le code ci dessous !!!

// Masques binaires de spécification de type de remplissage
#define CONTOUR 0X10000000

// Masque binaire de spécification de dessin torique
#define TORIQUE 0x40000000

// Masque binaire de spécification de bitmap destination (sur page ou sur fond)
#define PEINDRE 0x01000000

// Macro de facilitation de determination bitmap destination du dessin :
#define DESTBMP()                   \
    BITMAP *bmp=NULL;               \
    do {                            \
        if ( couleur&PEINDRE ) {    \
            bmp=fond;               \
            couleur^=PEINDRE;  }    \
        else bmp=page;              \
    } while(0)

// Macro de facilitation de determination dessin multiple torique :
#define TORIQUE_DEBUT           \
    int torx,tory,rep=0;        \
    if ( couleur&TORIQUE ) {    \
        rep=1;                  \
        couleur^=TORIQUE;  }    \
    for (tory=-HAUTEURECRAN*rep; tory<=HAUTEURECRAN*rep; tory+=HAUTEURECRAN)  \
        for (torx=-LARGEURECRAN*rep; torx<=LARGEURECRAN*rep; torx+=LARGEURECRAN) \
        {

#define TORIQUE_FIN  }         \


/// Couleur spéciale : rend "invisible"
#define EFFACER (0xFF00FF|PEINDRE)

/// Couleur à tester pour recupCouleurFond ( -> pas de peinture dessous)
#define FOND 0xFF00FF

/// Couleurs aleatoires
#define COULEURALEATOIRE makecol(rand()&0xFF, rand()&0xFF, rand()&0xFF)
#define COULEURALEATOIRESOMBRE makecol(rand()&0x7F, rand()&0x7F, rand()&0x7F)
#define COULEURALEATOIRECLAIR makecol((rand()&0x7F)+0x80, (rand()&0x7F)+0x80, (rand()&0x7F)+0x80)

}

#endif // COULEURS_H_INCLUDED


