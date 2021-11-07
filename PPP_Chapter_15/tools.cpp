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
// 5.

Bar_graph::Bar_graph(Fct f, double r1, double r2, Point orig,
    int count, double xscale, double yscale) :
    My_fct{ f, r1, r2, orig, count, xscale, yscale }
{
    
    int num_points = My_fct::number_of_points();
    for (int i = 0; i < num_points; ++i) {
        add_data(orig.y- My_fct::point(i).y );

        Point rec1 = My_fct::point(i);

        Point rec2 = Point{ My_fct::point(i).x
            + int(My_fct::range1() * x_scale()),
            My_fct::origin().y };
        
        if (rec1.y!=rec2.y) {
            bars.push_back(new Rectangle{ rec1,rec2 });            
        }        
    }
    draw_lines();
}

void Bar_graph::set_fill_color( Color c)
{
    for (int i = 0; i < bars.size(); ++i) {
        bars[i].set_fill_color(c);
    }
}

void Bar_graph::draw_lines() const
{
    for (int i = 0; i < bars.size(); ++i) {      
        bars[i].draw();
    }
}