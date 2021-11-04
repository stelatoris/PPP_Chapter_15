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

int fac(int n) { return n > 1 ? n * fac(n-1) : 1; } // factorial n!

int my_fac(int n)
{
    int r = 1;
    while (n > 1) {
        r *= n;
        --n;
    }
    return r;
}

int main()
try
{
    int sum{ fac(20) };
    int sum2{ my_fac(20) };

    std::cout << "Sum : " << sum << '\n';
    std::cout << "Sum2: " << sum2 << '\n';

    /*int n1{ 0 };
    while (n1 < 21) {
        int sum{ fac(n1) };
        std::cout << "fac(" << n1 << "):" << sum << ", ";
        ++n1;
    }

    std::cout << '\n';

    int n2{ 0 };
    while (n2 < 21) {
        int sum{ my_fac(n2) };
        std::cout << "my_fac(" << n2 << "):" << sum << ", ";
        ++n2;
    }*/
}

catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
    std::cerr << "exception\n";
}
