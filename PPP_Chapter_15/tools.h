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

    //----------------------------------------------------------------------------
    //    6. Design and implement a bar graph class.Its basic data is a vector<double>
    //       holding N values, and each value should be represented by a “bar” that is
    //       a rectangle where the height represents the value.

    struct Bar_graph :My_fct {
        Bar_graph(Fct f, double r1, double r2, Point orig,
            int count, double xscale, double yscale);
        void add_data(double d) { data.push_back(d); }
        void draw_lines() const;
        void set_fill_color( Color c);
    private:
        vector<double> data;
        Vector_ref<Shape> bars;
    };

}	// end of namespace Graph_lib



