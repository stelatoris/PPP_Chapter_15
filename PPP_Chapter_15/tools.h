// tools.h

#include "Graph.h"
#include "std_lib_facilities.h"
#define PI 3.14159265

using namespace Graph_lib;

namespace Graph_lib {

	struct My_fct : Function {
        My_fct(Fct f, double r1, double r2, Point orig,
            int count, double xscale, double yscale);
        My_fct(double (*f)(double), double r1, double r2, Point orig,
            int count, double xscale, double yscale);

        void set_range(double r1, double r2);
        void set_count(int count);
        void set_scale(double xscale, double yscale);
        void set_function(const Fct& f);
        double range1() const { return r_1_p; }
        double range2() const { return r_2_p; }
        Point origin() const { return p_orig_p; }
        int count() const { return count_p; }
        double x_scale() const { return x_scale_p; }
        double y_scale() const { return y_scale_p; }

    private:
        void reset();   // replots points to be drawn
        Fct f_p;
        double r_1_p;
        double r_2_p;
        Point p_orig_p;
        int count_p;
        double x_scale_p;
        double y_scale_p;
    };

    //---------------------------------------------------------------------------------------
    //    6. Design and implement a bar graph class.Its basic data is a vector<double>
    //       holding N values, and each value should be represented by a “bar” that is
    //       a rectangle where the height represents the value.

    struct Bar_graph :Shape {
        Bar_graph(Point orig, double xscale, double yscale);
        Bar_graph(Point orig, double xscale, double yscale, vector<double> v);
        void add_data(double d) { data.push_back(d); }
        void draw_lines() const;
        void set_spacing(int x) { spacing = x; }
    private:
        vector<double> data;
        Vector_ref<Shape> bars;
        Point origin;
        double x_scale;
        double y_scale;
        int spacing;
    };
    //---------------------------------------------------------------------------------------
    // 8. Here is a collection of heights in centimeters together with the number
    //    of people in a group of that height(rounded to the nearest 5cm) : (170, 7),
    //    (175, 9), (180, 23), (185, 17), (190, 6), (195, 1).How would you graph that
    //    data ? If you can’t think of anything better, do a bar graph.Remember to
    //    provide axes and labels.Place the data in a fileand read it from that file.

    struct Human_height :Shape {
        Human_height(Point orig, double xscale, double yscale);

        struct Pairs {
            Pairs(int h_cm, int n);
            Pairs() :height{ 0 }, num{ 0 } {}

            int height;
            int num;
        };

        void draw_lines() const;
        void add_data(int h, int n) { v_pairs.push_back({ h,n }); }
        void set_spacing(int x) { spacing = x; }

        Pairs get_data(int i) { return v_pairs[i]; }
        int get_size() { return v_pairs.size(); } 

    private:
        vector<Pairs> v_pairs;
        Point origin;
        double x_scale;
        double y_scale;
        int spacing;
              
    };


    //---------------------------------------------------------------------------------------

}	// end of namespace Graph_lib



