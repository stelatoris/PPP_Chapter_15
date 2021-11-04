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

//  2. Define a class Fct that is just like Function except that it stores its constructor
//  arguments.Provide Fct with “reset” operations, so that you can
//  use it repeatedly for different ranges, different functions, etc.

struct My_fct : Function {
    My_fct(Fct f, double r1, double r2, Point orig,
        int count, double xscale, double yscale);

    void set_range(double r1, double r2);
    void set_count(int count);
    void set_scale(double xscale, double yscale);
    void set_function(const Fct& f);

private:
    void reset();   // replots points to be drawn
    Fct f_p;
    double r_1_p;
    double r_2_p;
    Point p_orig_p;
    int count_p;
    double x_scale_p;
    double y_sclae_p;
};

My_fct::My_fct(Fct f, double r1, double r2, Point orig,
    int count = 100, double xscale = 25, double yscale = 25):
    Function{f,r1,r2,orig,count,xscale,yscale},    
     f_p{ f }, r_1_p{ r1 }, r_2_p{ r2 }, p_orig_p{ orig },
    count_p{ count }, x_scale_p{ xscale }, y_sclae_p{ yscale }
{
    
}

void My_fct::reset()
{
    if (r_2_p - r_1_p <= 0) error("bad graphing range");
    if (count_p <= 0) error("non-positive graphing count");
    double dist = (r_2_p - r_1_p) / count_p;
    double r = r_1_p;
    clear_points();
    for (int i = 0; i < count_p; ++i) {
        add(Point{ p_orig_p.x + int(r * x_scale_p),p_orig_p.y - int(f_p(r) * y_sclae_p) });
        r += dist;
    }
}

void My_fct::set_range(double r1, double r2)
{
    r_1_p = r1;
    r_2_p = r2;
    reset();
}

void My_fct::set_count(int count)
{
    if (count <= 0)error"count cannot be less than 1";
    count_p = count;
    reset();
}

void My_fct::set_scale(double xscale, double yscale)
{
    if (count <= 0)error"scales cannot be less than 1";
    x_scale_p = xscale;
    y_sclae_p = yscale;
    reset();
}

void My_fct::set_function(const Fct& f)
{
    f_p = f;
    reset();
}

//-------------------------------------------------------------------------
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

//-------------------------------------------------------------------------

int main()
try
{
    Graph_lib::Window win{ Point{100,100},xmax,ymax,"Exercise 02" };

    Axis x{ Axis::x,x_axis_p,xlength,xlength / x_scale,"1==20 pixels" };
    Axis y{ Axis::y,y_axis_p,ylength,ylength / y_scale,"1==20 pixels" };
    x.set_color(Color::red);
    y.set_color(Color::red);

    //My_fct s{ one,r_min,r_max,orig,n_points,x_scale,y_scale };
    My_fct s2{ slope,r_min,r_max,orig,n_points,x_scale,y_scale };

    s2.set_range(-12, 12);
    s2.set_count(1000);
    s2.set_function(sloping_cos);

    win.attach(x);
    win.attach(y);
    //win.attach(s);
    win.attach(s2);


    gui_main();
}

catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
    std::cerr << "exception\n";
}
