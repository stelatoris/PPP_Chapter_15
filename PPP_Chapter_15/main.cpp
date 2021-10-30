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


struct Name {
    
};

struct Person {
    Person(std::string name, int age);
    Person() : n{ "" }, a{ 0 } {}
    std::string name() const { return n; }
    int age() const { return a; }

    void set_name(const std::string& name) { n = name; }
    void set_age(int age) { a = age; }
private:
    std::string n;
    int a;
};

Person::Person(std::string name, int age) 
    : n{ name }, a{ age } 
{
    const std::string false_chars{ ";:\"'[]*&^%$#@!" };
    for (char c1 : name) {        
        for (char c2 : false_chars) {
            if (c1 == c2) error("name has an invalid character");
        }
    }
    if (0 > age || age > 150) error("age must be in 0:150 range");
}

bool operator==(const Person& p1, const Person& p2)
{
    return p1.name() == p2.name()
        && p1.age() == p2.age();
}

bool operator!=(const Person& p1, const Person& p2)
{
    return !(p1 == p2);
}


ostream& operator<<(ostream& os, Person& const p)
{
    os <<'('<< p.name() << ", " << p.age() <<')';
    return os;
}

istream& operator>>(istream& is, Person& p)
// read name and age
// format: name,age
{
    std::string n;
    int a;

    is >> n >> a;
    if (!is) return is;
    p = Person{ n,a };
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
            if (p1 == v_persons[i]) {                
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
