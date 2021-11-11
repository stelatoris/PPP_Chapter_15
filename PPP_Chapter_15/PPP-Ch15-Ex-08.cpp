//main.cpp
// Programming: Principles and Practices using c++ - Bjarne Stroustrup
// 
// Chapter 15 Drill and Exercise solutions

#include "Simple_window.h"
#include "Graph.h"
#include "std_lib_facilities.h"
#include "tools.h"
#include <math.h>
#define PI 3.14159265

using namespace Graph_lib;


constexpr int xmax = 1200;   // window size
constexpr int ymax = 1200;

constexpr int xlength = 800;    // Axis length
constexpr int ylength = 800;

constexpr int x_offset = 100;
constexpr int y_offset = 100;

constexpr Point x_axis_p = { x_offset, ylength + y_offset };  // starting point of axis to cross both at (300,300)
constexpr Point y_axis_p = { x_offset, ylength + y_offset };

constexpr int x_scale = 20;
constexpr int y_scale = 100;

constexpr int r_min = 1; // range [–10:11)
constexpr int r_max = 10;

constexpr int n_points = 10; // number of points used in range

constexpr int x_orig = x_offset; // position of (0,0) is center of window
constexpr int y_orig = ylength + y_offset;
constexpr Point orig{ x_orig,y_orig };

//-------------------------------------------------------------------------
// Ex 08

ifstream& operator>>(ifstream& ifs, Human_height& h)
// format: ( 175,6 ) "height,number of people"
{
    char ch1;
    if (ifs >> ch1 && ch1 != '(') {
        ifs.unget();
        ifs.clear(ios_base::failbit);
        return ifs;
    }

    char ch2, ch3;
    int height, num;
    ifs >> height >> ch2 >> num >> ch3;
    if (!ifs) return ifs;
    if (0 > height || height > 300) error("bad height");
    if (0 > num) error("number cant be less than zero");
    if (ch2 != ',' || ch3 != ')') error("bad reading");
    h.add_data(height, num);
    return ifs;
}

ostream& operator<<(ostream& os, const Human_height::Pairs& p)
{
    return os << '(' << p.height << ',' << p.num << ')';
}

//-------------------------------------------------------------------------

int main()
try
{
    // 8. Here is a collection of heights in centimeters together with the number
    //    of people in a group of that height(rounded to the nearest 5cm) : (170, 7),
    //    (175, 9), (180, 23), (185, 17), (190, 6), (195, 1).How would you graph that
    //    data ? If you can’t think of anything better, do a bar graph.Remember to
    //    provide axes and labels.Place the data in a fileand read it from that file.

    string iname{ "height_input.txt" };
    ifstream ifs{ iname };
    if (!ifs)error("can't open input file", iname);

    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    Human_height set1{ orig,x_scale,y_scale };

    while (!ifs.eof()) {
        if (!(ifs >> set1)) break;        
    }

    for (int i = 0; i < set1.get_size(); ++i) {
        cout << set1.get_data(i) << '\n';
    }

    set1.set_color(Color::blue);
    
    Graph_lib::Window win{ Point{100,100},xmax,ymax,"Exercise 08" };

    Axis x{ Axis::x,x_axis_p,xlength,xlength / x_scale,"Number of people" };
    Axis y{ Axis::y,y_axis_p,ylength,ylength / y_scale,"Height in cm" };

    Vector_ref<Text> x_labels;    

    // label x-axis with numbers 1-end of axis
    for (int i = 0; i < xlength / x_scale;++i) {
        int l_x = orig.x + (i *  x_scale);
        int l_y = orig.y - (i *  y_scale);
        stringstream ss;
        ss << i;
        string label = ss.str();
            
        x_labels.push_back(new Text{ Point{l_x- x_scale/4,orig.y+40},label });
        win.attach(x_labels[i]);
    }

    Vector_ref<Text> y_labels;
    // label y-axis with height data from v_pairs
    for (int i = 0; i < set1.get_size(); ++i) {
        int l_x = orig.x + (i * x_scale);
        int l_y = orig.y - (i * y_scale);
        stringstream ss;
        ss << set1.get_data(i).height;
        string label = ss.str();

        y_labels.push_back(new Text{ Point{orig.x - 40,l_y - y_scale / 2},label });
        win.attach(y_labels[i]);
    }    

    win.attach(x);
    win.attach(y);
    win.attach(set1);

    gui_main();
}

catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
    std::cerr << "exception\n";
}
