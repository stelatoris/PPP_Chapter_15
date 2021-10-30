//main.cpp
// Programming: Principles and Practices using c++ - Bjarne Stroustrup
// 
// Chapter 15 Drill and Exercise solutions

#include "Simple_window.h"
#include "Graph.h"
#include "std_lib_facilities.h"
#include "tools.h"
#include <math.h>

using namespace Graph_lib;

constexpr int xmax = 600;   // window size
constexpr int ymax = 600;

constexpr int xlength = 400;    // Axis length
constexpr int ylength = 400;

constexpr Point x_axis_p = { (xlength / 4),ymax / 2 };  // starting point of axis to cross both at (300,300)
constexpr Point y_axis_p = { xmax / 2,ymax - (ylength / 4) };

constexpr int x_scale = 20;
constexpr int y_scale = 20;

constexpr int r_min = -10; // range [–10:11)
constexpr int r_max = 11;

constexpr int n_points = 400; // number of points used in range

constexpr int x_orig = xmax / 2; // position of (0,0) is center of window
constexpr int y_orig = ymax / 2;
constexpr Point orig{ x_orig,y_orig };

double one(double x) { return 1; }
double slope(double x) { return x / 2; }
double square(double x) { return x * x; }
double sloping_cos(double x) { return cos(x) + slope(x); }


int main()
try
{
    Graph_lib::Window win{ Point{100,100},xmax,ymax,"Function graphs." };

    Axis x{ Axis::x,x_axis_p,xlength,xlength / x_scale,"1==20 pixels" };
    Axis y{ Axis::y,y_axis_p,ylength,ylength / y_scale,"1==20 pixels" };
    x.set_color(Color::red);
    y.set_color(Color::red);

    Function s{ one,r_min,r_max,orig,n_points,x_scale,y_scale };
    Function s2{ slope,r_min,r_max,orig,n_points,x_scale,y_scale };
    Function s3{ square ,r_min ,r_max, orig,n_points,x_scale,y_scale };
    Function s4{ cos,r_min ,r_max, orig,n_points,x_scale,y_scale };
    s4.set_color(Color::blue);
    Function s5{ sloping_cos,r_min ,r_max, orig,n_points,x_scale,y_scale };


    Text t{ Point{100,300-30},"one" };
    Text t2{ Point{100,int(slope(100)) + y_orig+30},"x/2" };
    Text t3{ Point{200,20},"x*x" };
    Text t4{ Point{100,335},"cos" };
    t4.set_color(Color::blue);
    Text t5{ Point{100,430},"sloping cos" };

    win.attach(x);
    win.attach(y);

    win.attach(s);    
    win.attach(s2);
    win.attach(s3);
    win.attach(s4);
    win.attach(s5);
    
    win.attach(t);
    win.attach(t2);
    win.attach(t3);
    win.attach(t4);
    win.attach(t5);

    gui_main();
}

catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
    std::cerr << "exception\n";
}
