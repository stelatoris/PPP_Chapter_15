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

}	// end of namespace Graph_lib



