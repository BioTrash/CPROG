#include <iostream>
#include <vector>

//num = 5, i = 2
//num = 000101
//result = 000111
//result = 7

int setBit(int num, int i){
    int result;

    result = num | (0x1 << i);

    return result;
}

int clearBit(int num, int i){
    int result;

    result = num & ~(0x1 << i);

    return result;
}  

int number = 7;

void toggleBit(int &num, int i){
    num = num ^ 0x1 << i;
}

/* bool checkBit(int num, int i){
    if((num | (0x1 << i)) == num){
        return true;
    }
    else return false;
} */

int countBit(int num){
    int i = 0;
    while (num > 0){
        i++;
        num = num & (num -1 );
    }
    return i;
}

unsigned long int myZero (unsigned long int uli, int nr){
    uli = ~(uli | (0xFUL << 4*nr));
    return uli;
}

unsigned long int zero(unsigned long int uli, int nr){
    uli = uli & ~(0xFUL << 4*nr);
    return uli;
}

unsigned int rotateLeft(unsigned int num, int k){
    std::vector<int> dropped;

    for(int i = 0; i < k; i++){
        if((num | (0x1 << 0)) == num){
            dropped.push_back(1);
        }
        else {
            dropped.push_back(0);
        }

        num = num >> 1;
    }

    for(int i = 0, j = 0; i < dropped.size(); j++){
        num = num | (dropped.back() << k+j);
        dropped.pop_back();
    }

    return num;
}

//000101 -> 101000

int main(){
/*     std::cout << setBit(5, 1) << std::endl;
    std::cout << clearBit(5, 2) << std::endl; */
/*     toggleBit(number, 1);
    std::cout << number << std::endl;
    toggleBit(number, 1);
    std::cout << number << std::endl; */
/*     std::cout << checkBit(7, 1) << std::endl;
    std::cout << checkBit(5, 1) << std::endl; */
    /* std::cout << countBit(31) << std::endl; */
/*     std::cout << myZero(2147483647, 5) << std::endl;
    std::cout << zero(2147483647, 5) << std::endl; */
    std::cout << rotateLeft(5,3) << std::endl;
}
