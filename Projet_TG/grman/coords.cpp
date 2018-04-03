#include "coords.h"

// Renvoie les coordonnées (dans le repère de la position de Frame) de l'intersection
// entre la demi-droite centre Frame -> vecteur directeur vec et le cadre de la Frame
Coords Frame::intersect(Coords vec)
{
    Coords mid = dim *0.5;
    Coords rel = vec / mid;

    Coords res;
    if ( rel.x || rel.y )
    {
        if ( rel.x + rel.y > 0 )
        {
            if ( rel.x - rel.y > 0)
                res.x = 1, res.y = rel.y/rel.x;  // Secteur droit
            else
                res.x = rel.x/rel.y, res.y = 1;  // Secteur bas
        }
        else
        {
            if ( rel.x - rel.y > 0)
                res.x = -rel.x/rel.y, res.y = -1; // Secteur haut
            else
                res.x = -1, res.y = -rel.y/rel.x; // Secteur gauche
        }
    }
    return pos + mid + (res*mid);
}

