// tools.cpp
// Programming: Principles and Practices using c++ - Bjarne Stroustrup
// 
// Chapter 15 Drill and Exercise solutions

#include "Simple_window.h"
#include "tools.h"
#include <math.h>
using namespace std;

using namespace Graph_lib;

//  2. Define a class Fct that is just like Function except that it stores its constructor
//  arguments.Provide Fct with “reset” operations, so that you can
//  use it repeatedly for different ranges, different functions, etc.

My_fct::My_fct(Fct f, double r1, double r2, Point orig,
    int count = 100, double xscale = 25, double yscale = 25) :
    Function{ f,r1,r2,orig,count,xscale,yscale },
    f_p{ f }, r_1_p{ r1 }, r_2_p{ r2 }, p_orig_p{ orig },
    count_p{ count }, x_scale_p{ xscale }, y_scale_p{ yscale }
{
}

My_fct::My_fct(double (*f)(double), double r1, double r2, Point orig,
    int count, double xscale, double yscale):
    Function(*f, r1, r2, orig, count, xscale, yscale),
    f_p{ *f }, r_1_p{ r1 }, r_2_p{ r2 }, p_orig_p{ orig },
    count_p{ count }, x_scale_p{ xscale }, y_scale_p{ yscale }
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
        add(Point{ p_orig_p.x + int(r * x_scale_p),p_orig_p.y - int(f_p(r) * y_scale_p) });
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
    count_p = count;
    reset();
}

void My_fct::set_scale(double xscale, double yscale)
{
    x_scale_p = xscale;
    y_scale_p = yscale;
    reset();
}

void My_fct::set_function(const Fct& f)
{
    f_p = f;
    reset();
}

//-------------------------------------------------------------------------
// 6.

Bar_graph::Bar_graph(Point orig, double xscale, double yscale) :
    origin{ orig }, x_scale{ xscale }, y_scale{ yscale }, spacing{10}
{
    draw_lines();
}

Bar_graph::Bar_graph(Point orig, double xscale, double yscale, vector<double> v):
    origin{ orig }, x_scale{ xscale }, y_scale{ yscale }, spacing{ 10 }, data{ v }
{
    draw_lines();
}

void Bar_graph::draw_lines() const
{
    int w = x_scale-spacing;
    for (int i = 0; i < data.size(); ++i) {
        int h = data[i]*y_scale;
        int x = (origin.x + (i * (w + spacing)));
        int y = origin.y - data[i] * y_scale;
        Point p { x,y };

        if (fill_color().visibility()) {    // fill
            fl_color(fill_color().as_int());
            fl_rectf(p.x, p.y, w, h);
        }

        if (color().visibility()) {    // lines on top of fill
            fl_color(color().as_int());
            fl_rectf(p.x, p.y, w, h);
        }
    }   
}

//---------------------------------------------------------------------------------------
    // 8. Here is a collection of heights in centimeters together with the number
    //    of people in a group of that height(rounded to the nearest 5cm) : (170, 7),
    //    (175, 9), (180, 23), (185, 17), (190, 6), (195, 1).How would you graph that
    //    data ? If you can’t think of anything better, do a bar graph.Remember to
    //    provide axes and labels.Place the data in a fileand read it from that file.

Human_height::Pairs::Pairs(int h_cm, int n) :
    height{ h_cm }, num{ n }
{    
}

Human_height::Human_height(Point orig, double xscale, double yscale) :
    origin{ orig }, x_scale{ xscale }, y_scale{ yscale }, spacing{ 10 }
{
    
    draw_lines();
}

void Human_height::draw_lines() const
// bars drawn horizontally from Y axis
// X-axis shows number of people
// y-axis shows height
{
    int h = y_scale - spacing;
    for (int i = 0; i < v_pairs.size(); ++i) {
        int w = v_pairs[i].num * x_scale;
        int x = origin.x;
        int y = (origin.y - y_scale - (i * (h + spacing)));
        Point p{ x,y };

        if (fill_color().visibility()) {    // fill
            fl_color(fill_color().as_int());
            fl_rectf(p.x, p.y, w, h);
        }

        if (color().visibility()) {    // lines on top of fill
            fl_color(color().as_int());
            fl_rectf(p.x, p.y, w, h);
        }        
    }    
}

//---------------------------------------------------------------------------------------



