#include "GUI.h"
#include <iostream>

using namespace Graph_lib;

struct Lines_window : Graph_lib::Window {
    Lines_window(Point xy, int w, int h, const string& title);
private:
    
    Open_polyline lines;

    
    Button next_button;     
    Button quit_button;     
    In_box next_x;
    In_box next_y;
    Out_box xy_out;
    Menu color_menu;
    Button color_button;
    

    void change(Color c) { lines.set_color(c); }
    

    void hide_menu() { color_menu.hide(); color_button.show(); }
    
    void red_pressed() { change(Color::red); hide_menu(); }
    void blue_pressed() { change(Color::blue); hide_menu(); }
    void black_pressed() { change(Color::black); hide_menu(); }
    void color_pressed() { color_button.hide(); color_menu.show(); }

    void next();
    void quit();

   
    /*
    static void cb_red(Address, Address);
    static void cb_blue(Address, Address);
    static void cb_black(Address, Address);
    static void cb_menu(Address, Address);
    static void cb_next(Address, Address);
    static void cb_quit(Address, Address);
    */
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    : Window{xy, w, h, title},
    next_button{Point{x_max() - 150, 0}, 70, 20, "Next point",
        [](Address, Address pw) { reference_to<Lines_window>(pw).next(); }},
    quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit",
        [](Address, Address pw) { reference_to<Lines_window>(pw).quit(); }},
    next_x{Point{x_max() - 310, 0}, 50, 20, "next x:"},
    next_y{Point{x_max() - 210, 0}, 50, 20, "next y:"},
    xy_out{Point{100, 0}, 100, 20, "current (x,y):"},
    color_menu{Point{x_max() - 70, 30}, 70, 20, Menu::vertical, "color"},
    color_button{Point{x_max() - 80, 30}, 80, 20, "color menu",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).color_pressed();
        }
    }
{
    attach(next_button);
    attach(quit_button);
    attach(next_x);
    attach(next_y);
    attach(xy_out);
    xy_out.put("no point");
    
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "red",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).red_pressed();
        }
    });
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "blue",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).blue_pressed();
        }
    });
    color_menu.attach(new Button{Point{0, 0}, 0, 0, "black",
        [](Address, Address pw) {
            reference_to<Lines_window>(pw).black_pressed();
        }
    });
    
    attach(color_menu);
    attach(lines);
}

void Lines_window::quit()
{
    hide();     
}

void Lines_window::next()
{
    int x = next_x.get_int();
    int y = next_y.get_int();

    lines.add(Point{x, y});

    
    ostringstream ss;
    ss << '(' << x << ',' << y << ')';
    xy_out.put(ss.str());

    redraw();
}

int main()
try {
    Lines_window win {Point{100, 100}, 600, 400, "lines"};
    return gui_main();
}
catch(exception& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "Unknown exception\n";
    return 2;
}
/* Compile command
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp drill16_2.cpp `fltk-config --ldflags --use-images` -o a.out
*/

