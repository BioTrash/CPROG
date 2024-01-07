#include <iostream>

unsigned long week01;

void setBit(unsigned long &week01, int pos){
    week01 |= (0x1 << pos);
}

void clearBit(unsigned long &week01, int pos){
    week01 &= ~(0x1 << pos);
}

bool checkBit(unsigned long week01, int pos){
    if((week01 |(0x1 << pos)) == week01) { return true; }
    else return false;
}

int main(){
    setBit(week01, 26);
    setBit(week01, 20);
    std::cout << checkBit(week01, 26) << std::endl;
    clearBit(week01, 26);
    std::cout << checkBit(week01, 26) << std::endl;
}