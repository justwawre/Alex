
/*
g++ -std=c++1z -g IO.cpp

*/
#include <iostream>
#include <vector>

#include <array>
#include <tuple>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "../toolkit.h"
using namespace std;

vector<int> read_ints(istream &is)
{
    FUNC_HEAD();
    cout << "please input integer to a vector" << endl;
    vector<int> res;
    int i;
    while (is >> i)
        res.push_back(i);
    if (is.eof())
    {
        is.clear();
    }

    return res;
}

vector<int> read_ints_2(istream &is)
{
    FUNC_HEAD();
    cout << "please input integer to a vector" << endl;
    vector<int> res;
    int i;

    while (is)
    {
        for (int i; is >> i;)
        {
            res.push_back(i);
            cout << "got\t" << i << endl;
        }
        if (is.eof())
        {
            cout << "got eof" << endl;
            is.clear();
            break; // .. all is well we reached the end-of-file ...
        }
        else if (is.fail())
        {               // a potentially recoverable error
            is.clear(); // reset the state to good()
            char ch;
            if (is >> ch)
            { // look for nesting represented by { ... }
                switch (ch)
                {
                case ',':
                case '{':
                case '}':
                    cout << "got " << ch << endl;
                    continue;
                    break;

                default:
                    is.setstate(ios_base::failbit); // add fail() to cin’s state
                }
            }
        }
        // ...
    }
    return res;
}

void input_simple()
{
    FUNC_HEAD();
    vector<int> v = read_ints(cin);
    cout << "Got " << v.size() << " elements" << endl;
}

void input_nested()
{
    FUNC_HEAD();
    vector<int> v = read_ints_2(cin);
    cout << "Got " << v.size() << " elements" << endl;
}

struct Entry
{
    string name;
    int number;
};

ostream &operator<<(ostream &os, const Entry &e)
{
    return os << "{\"" << e.name << "\", " << e.number << "}";
}

istream &operator>>(istream &is, Entry &e)
// read { "name" , number } pair. Note: formatted with { " " , and }
{
    char c, c2;
    if (is >> c && c == '{' && is >> c2 && c2 == '"')
    {                                 // star t with a { "
        string name;                  // the default value of a string is the empty string: ""
        while (is.get(c) && c != '"') // anything before a " is part of the name
            name += c;
        if (is >> c && c == ',')
        {
            int number = 0;
            if (is >> number >> c && c == '}')
            {                       // read the number and a }
                e = {name, number}; // assign to the entry
                return is;
            }
        }
    }
    is.setstate(ios_base::failbit); // register the failure in the stream
    return is;
}

void usser_defined_type()
{
    FUNC_HEAD();
    Entry e;
    cout << "please input entry in format { \"name\" , number }" << endl;
    cin >> e;
    cout << "we got:" << endl;
    cout << e << endl;
}

void output_format()
{
    FUNC_HEAD();
    constexpr double d = 123.456;
    cout << d << "; "                  // use the default for mat for d
         << scientific << d << "; "    // use 1.123e2 style for mat for d
         << hexfloat << d << "; "      // use hexadecimal notation for d
         << fixed << d << "; "         // use 123.456 style for mat for f
         << defaultfloat << d << '\n'; // use the default for mat for d

    auto str_time = [](int year, int mon, int day) {
        constexpr std::array<const char *, 7> week_day{{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}};

        std::tm tm{};
        tm.tm_year = year - 1900;
        tm.tm_mon = mon - 1;
        tm.tm_mday = day;

        day += mon < 3 ? year-- : year - 2;
        tm.tm_wday = (23 * mon / 9 + day + 4 + year / 4 - year / 100 + year / 400) % 7;

        std::ostringstream out;
        out << week_day[tm.tm_wday] << ", " << std::put_time(&tm, "%B %d, %Y");
        return out.str();
    };

    constexpr int column_size = 4;
    using table_t = std::array<std::string, column_size>;

    table_t headers{{"Name", "Birthdate", "Death date", "Language Created"}};

    std::array<table_t, 5> data{{{{"Dennis MacAlistair Ritchie", str_time(1941, 9, 9), str_time(2011, 10, 12), "C"}},
                                 {{"Bjarne Stroustrup", str_time(1950, 12, 30), "", "C++"}},
                                 {{"Anders Hejlsberg", str_time(1960, 12, 2), "", "C#"}},
                                 {{"Guido van Rossum", str_time(1956, 1, 31), "", "Python"}},
                                 {{"Brendan Eich", str_time(1961, 7, 4), "", "Javascript"}}}};

    constexpr int name_wid = 30;
    constexpr int birth_wid = 30;
    constexpr int death_wid = 30;
    constexpr int lang_wid = 18;

    auto print_line = [](table_t const &tbl) {
        auto const &[Name, Birthdate, DeathDate, LanguageCreated] = tbl;

        std::cout.width(name_wid);
        std::cout << ("| " + Name) << '|';

        std::cout.width(birth_wid);
        std::cout << (' ' + Birthdate) << '|';

        std::cout.width(death_wid);
        std::cout << (' ' + DeathDate) << '|';

        std::cout.width(lang_wid);
        std::cout << (' ' + LanguageCreated) << '|';

        std::cout << '\n';
    };

    constexpr int total_wid = name_wid + birth_wid + death_wid + lang_wid + column_size;

    auto print_break = [] {
        std::cout.width(total_wid);
        std::cout.fill('-');
        std::cout << '-' << std::endl;
        std::cout.fill(' ');
    };

    std::cout.setf(std::ios::left, std::ios::adjustfield);
    print_break();
    print_line(headers);
    print_break();
    for (auto const &entry : data)
        print_line(entry);
    print_break();
}

void test_stringstream()
{
    FUNC_HEAD();
    ostringstream oss;

    oss << "{temperature," << scientific << 123.4567890 << "}";
    cout << oss.str() << '\n';
}

main()
{
    /*
    now 1 ctrl-d will terminate the followed input, so have to comment one 
*/
    //input_simple();
    //input_nested();

    //usser_defined_type();

    output_format();
    test_stringstream();
}