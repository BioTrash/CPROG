// Rufus Trukhin, rutr7079
// Labb3, Datum.cpp – definitioner av icke-triviala medlemsfunktioner

#include <iostream>
#include <string>
#include "Datum.h"

const std::array< unsigned int, 13 > Datum::ANT_DAGAR_PER_MAANAD = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

Datum::Datum() {
    set_date(2000, 1, 1);
}

Datum::Datum(int year, int month, int day) {
    set_date(year, month, day);
}

void Datum::set_date(int yy, int mm, int dd) {
    if (yy < 2000 || yy > 2100) {
        throw std::invalid_argument("Året måste vara mellan >= 2000 och <= 2100");
    }

    if (mm < 1 || mm > 12) {
        throw std::invalid_argument("Månaden måste vara >= 1 och <= 12");
    }

    if (dd < 1 || dd > ANT_DAGAR_PER_MAANAD[mm]) {
        if (mm == 2 && is_skott_aar(yy) && dd == 29) {
        } else {
            throw std::invalid_argument("Dagen stämmer inte med år och månad");
        }
    }

    year = yy;
    month = mm;
    day = dd;
}

void Datum::step_one_day() {
    if (!end_of_month(day))
        ++day;
    else if (month < 12) {
        ++month;
        day = 1;
    } else {
        ++year;
        month = 1;
        day = 1;
    }
}

void Datum::step_several_day(int amount) {
    for (int i = 0; i < amount; i++) {
        step_one_day();
    }
}

bool Datum::is_skott_aar(int yy) {
    if (yy % 400 == 0 || (yy % 100 != 0 && yy % 4 == 0))
        return true;
    else
        return false;
}

bool Datum::end_of_month(int dd) const {
    if (month == 2 && is_skott_aar(year))
        return dd == 29;
    else
        return dd == ANT_DAGAR_PER_MAANAD[month];
}

const std::string Datum::intToMonth(int i) const{
  switch(i){
    case 1: return "January"; break;
    case 2: return "February"; break;
    case 3: return "March"; break;
    case 4: return "April"; break;
    case 5: return "May"; break;
    case 6: return "June"; break;
    case 7: return "July"; break;
    case 8: return "August"; break;
    case 9: return "September"; break;
    case 10: return "October"; break;
    case 11: return "November"; break;
    case 12: return "December"; break;
    default: return "NaN"; break;
  }
}

std::ostream &operator<<(std::ostream &output, const Datum &d) {
    // OBS. Glöm inte att modifiera vad som skrivs ut!
    output << d.day << ' ' << d.intToMonth(d.month) << ' ' << d.year;
    return output;
}

// Comparison operators
bool Datum::operator<(const Datum& other) const {
    if (year < other.year)
        return true;
    else if (other.year < year)
        return false;
    else if (month < other.month)
        return true;
    else if (other.month < month)
        return false;
    else if (day < other.day)
        return true;
    else if (other.day < day)
        return false;
    else
        return false;
}

bool Datum::operator==(const Datum& other) const {
    return (year == other.year && month == other.month && day == other.day);
}

bool Datum::operator!=(const Datum& other) const {
    return !(*this == other);
}

bool Datum::operator>(const Datum& other) const {
    return other < *this;
}

bool Datum::operator<=(const Datum& other) const {
    return !(*this > other);
}

bool Datum::operator>=(const Datum& other) const {
    return !(*this < other);
}

// Pre-increment operator
const Datum& Datum::operator++() {
    step_one_day();
    return *this;
}

// Post-increment operator 
const Datum Datum::operator++(int) {
    Datum temp = *this;
    step_one_day();
    return temp;
}

Datum& Datum::operator+=(int right) {
    step_several_day(right);
    return *this;
}

Datum operator+(int left, const Datum& right) {
    Datum result = right;
    result.step_several_day(left);
    return result;
}

Datum operator+(const Datum& left, int right) {
    Datum result = left;
    result.step_several_day(right);
    return result;
}
