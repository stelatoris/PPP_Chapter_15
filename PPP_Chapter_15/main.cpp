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

struct Person {
    Person(std::string f_name, std::string s_name, int age);
    Person() : f_n{ "" }, s_n{ "" }, a{ 0 } {}

    std::string first_name() const { return f_n; }
    std::string second_name() const { return s_n; }
    int age() const { return a; }

    void set_name(const std::string f_name, std::string s_name) 
    {
        f_n = f_name; s_n = s_name;
    }
    void set_age(int age) { a = age; }
private:
    std::string f_n;
    std::string s_n;
    int a;
};

Person::Person(std::string f_name, std::string s_name, int age)
    : f_n{ f_name }, s_n{ s_name }, a{ age }
{
    const std::string false_chars{ ";:\"'[]*&^%$#@!" };
    for (char c1 : f_name) {    // first name
        for (char c2 : false_chars) {
            if (c1 == c2) error("name has an invalid character");
        }
    }
    for (char c1 : s_name) {    // second name
        for (char c2 : false_chars) {
            if (c1 == c2) error("name has an invalid character");
        }
    }

    if (0 > age || age > 150) error("age must be in 0:150 range");
}

bool operator==(const Person& p1, const Person& p2)
{
    return p1.first_name() == p2.first_name()
        && p1.second_name() == p2.second_name()
        && p1.age() == p2.age();
}

bool operator!=(const Person& p1, const Person& p2)
{
    return !(p1 == p2);
}

ostream& operator<<(ostream& os, Person& const p)
{
    os <<'('<< p.first_name() <<' ' << p.second_name()
        << ", " << p.age() <<')';
    return os;
}

istream& operator>>(istream& is, Person& p)
// read name and age
// format: name,age
{
    std::string f_n;
    std::string s_n;
    int a;

    is >> f_n >> s_n >> a;
    if (!is) return is;
    p = Person{ f_n,s_n,a };
    return is;
}

int main()
try
{
    vector<Person>v_persons;

    Person p1;
    std::cout << "Please enter name and age: ";
    while (cin) {
        char ch;
        if (cin >> ch && ch == '|') break;
        
        cin.unget();    //return 1st character used to check for '|'
        std::cin >> p1;
        
        bool repeat = false;        // repeated in put
        for (int i = 0; i < v_persons.size(); ++i) {    // look for double input
            if (p1.first_name() == v_persons[i].first_name() &&
                p1.second_name() == v_persons[i].second_name()) {
                repeat = true;
                break;
            }                
        }

        if(repeat) std::cout << "Name already entered." << '\n';
        else { v_persons.push_back(p1); }
    }
    
    for (int i = 0; i < v_persons.size(); ++i) {
        std::cout << v_persons[i] << '\n';
    }
}

catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
    std::cerr << "exception\n";
}
