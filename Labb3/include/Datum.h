// Rufus Trukhin, rutr7079
// Labb3, Datum.h – klassdefinition

#ifndef DATUM_H
#define DATUM_H

#include <array>
#include <iostream>
#include <string>

class Datum
{
    friend std::ostream &operator<<( std::ostream &, const Datum & );
    
    unsigned int year;
    unsigned int month;
    unsigned int day;

        // Addition operator with an integer on the left side
    friend Datum operator+(int left, const Datum& right);

    // Addition operator with an integer on the right side
    friend Datum operator+(const Datum& left, int right);

    // Deklaration av statisk privat medlem, "ant_dagar per månad"
    static const std::array< unsigned int, 13 > ANT_DAGAR_PER_MAANAD;
  
public:

    //Operatorer som skall överlagras: +=, +, ++(pre/post), <, <=, >, >=, ==, !=, << 

    Datum();
    Datum( int, int, int );
    void set_date( int, int, int ); // set year, month, day

    //OBS. funktionen "step_one_day()" bör vara PRIVATE
    void step_one_day(); // Öka datum med en dag
    void step_several_day(int amount);
    static bool is_skott_aar( int ); // Är det skottår?
    bool end_of_month( int ) const; // Är dagen den sista i månaden?
    const std::string intToMonth(int i) const;

    // Operator overloads
    bool operator<(const Datum& other) const;
    bool operator==(const Datum& other) const;
    bool operator!=(const Datum& other) const;
    bool operator>(const Datum& other) const;
    bool operator<=(const Datum& other) const;
    bool operator>=(const Datum& other) const;

    // Pre-increment operator (++d)
    const Datum& operator++();
    
    // Post-increment operator (d++)
    const Datum operator++(int);

    // Addition assignment operator with an integer
    Datum& operator+=(int right);
};

#endif
