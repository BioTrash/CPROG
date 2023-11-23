//Rufus Trukhin rutr7079
// Labb2, IntVector.h – klassdefinition
#ifndef INTVECTOR_H
#define INTVECTOR_H
#include <iostream>

class IntVector
{
    public:
        IntVector();
        IntVector(const std::initializer_list<int> entry);
        IntVector(const IntVector& other);
        IntVector(IntVector&& other);
        ~IntVector();

        int& operator[](int index) const;
        IntVector& operator=(const IntVector& other);
        
        friend std::ostream& operator<<(std::ostream& os, const IntVector& vec);
    
        int size() const;
        void push_back(int i);
    private:
        int* data;
        size_t volume;
        size_t capacity;

};

#endif