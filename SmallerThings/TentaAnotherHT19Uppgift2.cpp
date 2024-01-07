#include <vector>
#include <iostream>
unsigned int bitskiftLeft ( unsigned int value, int steps){
    return value <<= steps;
}

unsigned int bitskiftRight ( unsigned int value, int steps){
    std::vector<int> droppped;
    for(int i = 0; i < steps; i++){
        if((value | (0x1 << 0)) == value){
            droppped.push_back(1);
        }
        else{
            droppped.push_back(0);
        }

        value >>= 1;
    }

    for(int i = 0, j = 0; i < droppped.size(); j++){
        value |= droppped.back() << steps+j;
        droppped.pop_back();
    }

    return value;   
}

void visaBitar ( unsigned int value){
    std::cout<<value<<std::endl;
}

int main(){
    visaBitar( 780 );
    visaBitar( bitskiftLeft(780, 8) );
    visaBitar( bitskiftRight(780, 8) );
}