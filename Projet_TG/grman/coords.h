#ifndef COORDS_H
#define COORDS_H

#include <cmath>

struct Coords
{
        double x;
        double y;

        Coords()
            : x(0), y(0) {}

        Coords(double x_, double y_)
            : x(x_), y(y_) {}

        double norm2() { return x*x + y*y; }

        double norm() { return sqrt(norm2()); }


        Coords operator+ (const Coords &rhs)
        {
            return Coords( x+rhs.x, y+rhs.y  );
        }

        Coords operator- (const Coords &rhs)
        {
            return Coords( x-rhs.x, y-rhs.y  );
        }

        Coords operator- ()
        {
            return Coords( -x, -y  );
        }

        Coords operator* (const double &rhs)
        {
            return Coords( x*rhs, y*rhs  );
        }

        Coords operator* (const Coords &rhs)
        {
            return Coords( x*rhs.x, y*rhs.y  );
        }

        Coords operator/ (const Coords &rhs)
        {
            return Coords( x/rhs.x, y/rhs.y  );
        }

        Coords normalize()
        {
            double nrm = norm();
            if ( !nrm )
                return Coords(0,0);

            return *this * (1./nrm);
        }

        Coords rotate_90() { return Coords(y, -x);  }

};

struct Frame
{
        Coords pos;
        Coords dim;

        Frame()
            : pos(), dim() {}

        Frame(Coords pos_, Coords dim_)
            : pos(pos_), dim(dim_) {}

        Frame(double x_, double y_, double w_, double h_)
            : pos(x_, y_), dim(w_, h_) {}

        // Renvoie les coordonnées (dans le repère de la position de Frame) de l'intersection
        // entre la demi-droite centre Frame -> vecteur directeur vec et le cadre de la Frame
        Coords intersect(Coords vec);

};


#endif // COORDS_H
