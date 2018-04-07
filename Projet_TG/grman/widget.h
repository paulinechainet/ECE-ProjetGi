#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED

#include "grman.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <allegro.h>

namespace grman
{

/***************************************************
            WIDGET CHILDREN POSITIONS
****************************************************/

enum class GravityX {
    None,
    Center,
    Left,
    Right
};

enum class GravityY {
    None,
    Center,
    Up,
    Down
};



/***************************************************
                WIDGET BASE CLASS
****************************************************/

/// Cette classe est trop grosse, elle fait le repassage, répare la voiture, pêche au harpon...
/// En principe il faut revoir la conception quand une classe devient aussi grosse (refactoriser)
/// Par exemple une classe de base Widget pour l'aspect composite et une classe dérivée WidgetDecorated pour les styles
class Widget
{
    protected :
        Widget *m_parent = nullptr;
        /// Naked pointers : Dangerous...
        std::vector<Widget *> m_children; // weak_ptr ?

        Frame m_frame;
        Frame m_abs_frame;

        // Viewport du contenu (intérieur Padding)
        BITMAP *m_view = nullptr;

        // Viewport total incluant les bords
        BITMAP *m_view_wb = nullptr;

        GravityX m_gravity_x = GravityX::Center;
        GravityY m_gravity_y = GravityY::Center;

        int m_bg_color = -1;

        int m_border_color = GRISSOMBRE;
        int m_border_color_over = VIOLETSOMBRE;
        int m_border_color_focus = ORANGESOMBRE;

        int m_border = 1;
        int m_margin = 1;
        int m_padding = 1;

    /// Méthodes utilisables dans les classes dérivées
    /// et les classes qui ont un Widget ou dérivé en attribut
    public :

        /// Construction/Destruction
        Widget(double x, double y, double w, double h) :
            m_frame(x, y, w, h) {}
        Widget() = default;
        // Destructeur virtuel en principe inutile tant que les objets ne sont pas détruits polymorphiquement
        // ( çàd que des objets dérivés seraient delete en tant que Widget *, ce n'est pas le cas dans les exemples d'utilisation )
        // Note : il n'est pas utile de redéfinir un destructeur virtuel par défaut dans les classes dérivées (si celui par défaut convient)
        virtual ~Widget() = default;

        /// Gestion familiale... navigation et édition de l'arbre des sous-éléments...
        Widget *get_child(int i) { return m_children.at(i); }
        void add_child(Widget &elt) { elt.set_parent(this); m_children.push_back(&elt); elt.reframe(); }
        void remove_child(Widget &elt) { m_children.erase( std::remove( m_children.begin(), m_children.end(), &elt ), m_children.end() ); }
        void reframe();

        /// Gestion géométrie
        void set_no_gravity()
            { m_gravity_x = GravityX::None;   m_gravity_y = GravityY::None;}

        Frame get_abs_frame() { return m_abs_frame; }

        Coords get_abs_pos() { return m_abs_frame.pos; }

        //Coords get_center_abs_pos() { return Coords( m_abs_frame.pos.x+.5*m_abs_frame.dim.x, m_abs_frame.pos.y+.5*m_abs_frame.dim.y );   }
        Coords get_center_abs_pos() { return m_abs_frame.pos+ m_abs_frame.dim * 0.5 ;   }

        void set_frame(Frame frame)
            { m_frame = frame; set_no_gravity(); }

        void set_frame(int x, int y, int w, int h)
            { m_frame = Frame(x, y, w, h); set_no_gravity(); }

        Frame get_frame() { return m_frame; }

        void set_frame_dim(int w, int h)
            { m_frame.dim = Coords(w, h); reframe(); }

        Coords get_frame_dim() { return m_frame.dim; };

        void set_frame_pos(int x, int y)
            { m_frame.pos = Coords(x, y); set_no_gravity(); }

        Coords get_frame_pos() { return m_frame.pos; };

        // Border + padding of parent
        int get_bp() { return m_border + m_padding; }
        int get_parent_bp() { return m_parent ? m_parent->get_bp() : 0; }

        void set_dimx(int w) { m_frame.dim.x=w+2*get_bp(); reframe(); }
        void set_dimy(int h) { m_frame.dim.y=h+2*get_bp(); reframe(); }
        void set_dim(int w,int h) { set_dimx(w); set_dimy(h); }  // Reframe 2x, not efficient...

        int get_dimx() { return m_frame.dim.x-2*get_bp(); }
        int get_dimy() { return m_frame.dim.y-2*get_bp(); }
        Coords get_dim() { return Coords(get_dimx(), get_dimy());  }

        void set_posx(int x) { m_frame.pos.x = x+get_parent_bp(); m_gravity_x = GravityX::None; }
        void set_posy(int y) { m_frame.pos.y = y+get_parent_bp(); m_gravity_y = GravityY::None; }
        void set_pos(int x, int y) { set_posx(x); set_posy(y); }
        void set_pos(Coords pos) { set_posx(pos.x); set_posy(pos.y); }

        int get_posx() { return m_frame.pos.x-get_parent_bp(); }
        int get_posy() { return m_frame.pos.y-get_parent_bp(); }
        Coords get_pos() { return Coords(get_posx(), get_posy()); }


        void set_gravity_xy(GravityX gx, GravityY gy)
            { m_gravity_x=gx; m_gravity_y=gy; reframe(); }

        void set_gravity_x(GravityX gx)
            { m_gravity_x=gx; reframe(); }

        void set_gravity_y(GravityY gy)
            { m_gravity_y=gy; reframe(); }

        void set_margin(int margin) { m_margin=margin; reframe(); }
        void set_border(int border) { m_border=border; reframe(); }
        void set_padding(int padding) { m_padding=padding; reframe(); }
        //void set_(int ) { m_=; }

        // Usage "interne"
        Frame get_parent_frame()
            { return m_parent ? m_parent->m_frame : page_frame; }
        Frame get_parent_abs_frame()
            { return m_parent ? m_parent->m_abs_frame : page_frame; }

        void reset_posx(int x) { m_frame.pos.x = x+get_parent_bp(); }
        void reset_posy(int y) { m_frame.pos.y = y+get_parent_bp(); }


        /// Gestion affichage et interaction
        void update();

        void update_interact();
        void update_pre_draw();
        void update_draw();

        virtual void draw() {}
        virtual void draw_border();

        virtual void interact_over() {}
        virtual void interact_focus() {}
        virtual void interact_leave() {}

        virtual bool captures_focus() { return false; }

        bool is_gui_over() {return this==gui_over || this==gui_last_over;}
        bool is_gui_focus() {return this==gui_focus;}
        bool is_gui_leave() {return this==gui_leave;}

        bool is_mouse_over();

        /// Les accesseurs de "styles" sont à compléter...
        void set_bg_color(int bgc) { m_bg_color = bgc; }
        int get_border_color() { return is_gui_focus() ? m_border_color_focus : is_gui_over() ? m_border_color_over : m_border_color; }

        Widget(const Widget&) = delete;
        Widget & operator=(const Widget&) = delete;


    /// En principe non directement utiles dans les classes dérivées (aspects techniques)
    private:
        // Gestion familiale... construction de l'arbre des éléments/sous-éléments ...
        void set_parent(Widget *parent) { m_parent = parent; }

        // Gestion géométrie
        void create_frame_context();
        void destroy_frame_context();
};



/***************************************************
                    TEXT
****************************************************/

/// Extrêmement rudimentaire : à compléter !
class WidgetText : public Widget
{
    protected :
        std::string m_message;
        int m_color = NOIR;
        FONT *m_font = font;
        bool m_vertical = false;

    public :
        WidgetText(std::string message="") { m_border=m_padding=0; set_message(message); }
        virtual void draw();

        void set_message(std::string message="");
        std::string get_message() { return m_message; }
        void set_vertical(bool vertical=true) { m_vertical=vertical; set_message(m_message); } /// BRICOLAGE ...
};



/***************************************************
                    CHECKBOX
****************************************************/

class WidgetCheckBox : public Widget
{
    protected :
        bool m_value = false;

    public :

        virtual void draw();
        virtual void interact_focus();
        virtual bool captures_focus() { return true; }

        bool get_value() { return m_value; }
        void set_value(bool value) { m_value = value; }
};



/***************************************************
                    BUTTON
****************************************************/

class WidgetButton : public Widget
{
    protected :
        bool m_value = false;

    public :

        virtual void interact_focus();
        virtual bool captures_focus() { return true; }

        bool clicked() { bool clk = m_value; m_value=false; return clk; }
        bool get_value() { return m_value; }
        void set_value(bool value) { m_value = value; }
};



/***************************************************
                    VSLIDER
****************************************************/

class WidgetVSlider : public Widget
{
    protected :
        double m_value = 0;
        double m_min;
        double m_max;

        bool m_integer;

        double m_handle_ratio = .5;
        double m_rail_ratio = .3;
        double m_specific_padding = 2;

        int m_rail_color = GRIS;
        int m_handle_color = GRISSOMBRE;

        int get_hhandle() { return std::max(1., m_handle_ratio * m_view->w/2); }

    public :

        WidgetVSlider(double min=0, double max=1, bool integer=false) :
            m_min(min), m_max(max), m_integer(integer)
            { m_padding=m_specific_padding; limit_to_range(); }

        virtual void draw();
        virtual void interact_focus();
        virtual void interact_over();
        virtual bool captures_focus() { return true; }

        double typed(double v) { return m_integer ? round(v) : v; }
        double get_value() { return typed(m_value); }
        void limit_to_range() { if (m_value<m_min) m_value=m_min; if (m_value>m_max) m_value=m_max; }
        void set_value(double value) { m_value = value; m_value =get_value(); limit_to_range(); }
        void set_range(double min, double max, bool integer=false) { m_min = min; m_max = max; m_integer = integer; limit_to_range(); }
};




/***************************************************
                    IMAGE
****************************************************/

class WidgetImage : public Widget
{
    protected :
        std::string m_pic_name;
        int m_pic_idx = 0;
        bool m_animate = false;
        int m_animate_cpt_tempo = 0;
        int m_animate_tempo = 10;

    public :
        WidgetImage(std::string pic_name="") : m_pic_name(pic_name) { m_margin=m_border=m_padding=0; reframe(); }
        virtual void draw();

        virtual void reframe();
        void set_pic_name(std::string pic_name) { m_pic_name = pic_name; reframe(); }

        void set_animate(bool ani=true) { m_animate = ani; }
        void set_animate_tempo(int tempo) { m_animate_tempo = tempo; }

        void set_pic_idx(int pic_idx) { m_pic_idx=pic_idx; }
};



/***************************************************
                    BOX
****************************************************/

class WidgetBox : public Widget
{
    protected :
        // La WidgetBox a une position modifiable par drag & drop
        bool m_moveable = false;

        // La WidgetBox reste dans le cadre de son parent (préférable)
        bool m_contained = true;

        // Position au moment du click quand on commence à bouger la WidgetBox
        Coords m_pos_start_move;


    public :

        virtual void interact_focus();
        virtual bool captures_focus() { return true; }
        void set_moveable(bool moveable=true) { m_moveable = moveable; }
};



/***************************************************
                    EDGE
****************************************************/

/// Différents éléments de décoration des flèches
/// Ceci peut être étendu en étendant le code WidgetEdge::draw
enum class ArrowItemType
{
    Arrow,
    Triangle,
    Bullet,
};

struct ArrowItem
{
    // Type de décoration (pointe de flèche, triangle, rond...
    ArrowItemType m_type;

    // Position relative de l'élément le long de l'arc, 0 origine, 0.5 milieu, 1.0 destination
    double m_position;

    // Taille absolue de l'élément (voir valeur par défaut dans le constructeur)
    double m_size;

    // Proportion (pointe de flèche plus aigue <1 ou plus obtuse >1) (voir valeur par défaut dans le constructeur)
    double m_proportion;

    ArrowItem(ArrowItemType type, double position, double size=14.0, double proportion=0.5) :
        m_type(type), m_position(position), m_size(size), m_proportion(proportion) {}
};

class WidgetEdge : public Widget
{
    protected :

        // Les Widgets de référence de départ [0] et d'arrivée [1] de l'arête
        /// Si un de 2 pointeur est à nul, l'arête n'est pas traitée
        /// Si les 2 pointeurs sont distincts du nul l'arête est traité
        /// Les 2 instances pointées ne doivent pas être détruites
        /// sous peine de plantage douloureux du programme !
        Widget *m_attach[2] = {nullptr, nullptr};

        // Elements de décoration : pointes de flèches, rond etc...
        std::vector<ArrowItem> m_items;

        int m_color = GRISSOMBRE;
        int m_thickness = 2;

        // Position relative des éventuels Widgets enfants le long de l'arc, 0 origine, 0.5 milieu, 1.0 destination
        double m_children_position = 0.5;

        // Position laterale absolue des éventuels Widgets enfants à l'écart de l'arc, >0 à gauche en suivant l'arc, <0 à droite en suivant l'arc
        double m_children_lateral = 16;

    public :

        virtual void draw();

        void attach_from(Widget& from) { m_attach[0] = &from; }
        void attach_to(Widget& to) { m_attach[1] = &to; }

        void reset_no_items() { m_items.clear(); }
        void reset_arrow() { m_items = { {ArrowItemType::Arrow, 1.0} }; }
        void reset_arrow_with_bullet() { m_items = { {ArrowItemType::Arrow, 1.0},
                                                     {ArrowItemType::Bullet, 0.0},  }; }
        void reset_middle_arrow() { m_items = { {ArrowItemType::Arrow, 0.5}  }; }
        void reset_middle_arrow_with_bullets() { m_items = { {ArrowItemType::Arrow, 0.5},
                                                             {ArrowItemType::Bullet, 0.0},
                                                             {ArrowItemType::Bullet, 1.0}  }; }

        void add_item( ArrowItem ai )  { m_items.push_back(ai); }

        void set_children_position(double rel_pos) { m_children_position = rel_pos; }
        void set_children_lateral(double abs_lat) { m_children_lateral = abs_lat; }
};


}


#endif // WIDGET_H_INCLUDED
