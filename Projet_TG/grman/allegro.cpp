#include <cmath>
#include <string>
#include <iostream>
#include <allegro.h>

void allegro_prog_croix()
{
    BITMAP *croix[1];
    BITMAP *buffer;

    croix[0]=load_bitmap("BMP_Base/croix.bmp", NULL);
    croix[1]=load_bitmap("BMP_Base/croix_r2.bmp", NULL);

    while (key(!KEY_ESC))
    {
        blit()
        while (mouse_x>50 && mouse_y>50)
        {

            blit(croix[0], screen,0,0,50,50, 50, 50);
        }

        if (mouse_x<50 && mouse_y<50)
        {
            while (mouse_x<50 && mouse_y<50)
            {

                blit(croix[1], screen,0,0,50,50, 50, 50);
                textprintf(screen,font,50,50,makecol(0,0,0),"Sauvegarder & Quitter");
            }
            if (mouse_b & 1)
            {
                textprintf(screen,font,50,50,makecol(0,0,0),"Sauvegardé");
            }
        }
    }
}
