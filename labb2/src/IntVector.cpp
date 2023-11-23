//Rufus Trukhin rutr7079
// Labb2, IntVector.cpp – definitioner av icke-triviala medlemsfunktioner

#include "IntVector.h"

IntVector::IntVector() : data(nullptr), volume(0), capacity(0) {

}

IntVector::IntVector(const std::initializer_list<int> entry) : volume(entry.size()), capacity(entry.size()){
    data = new int[capacity];
    int* ptr = data;
    for (const int& val : entry){
        *ptr++ = val;
    }
}

IntVector::IntVector(const IntVector& other) : volume(other.volume), capacity(other.volume){
    data = new int[capacity];
    for (size_t i = 0; i < volume; ++i){
        data[i] = other.data[i];
    }
}

IntVector::IntVector(IntVector&& other) : data(other.data), volume(other.volume), capacity(other.capacity){
    other.data = nullptr;
    other.volume = 0;
    other.capacity = 0;
}

IntVector::~IntVector(){
    delete[] data;
}

int IntVector::size() const{
    return static_cast<int>(volume);
}

void IntVector::push_back(int i){
    if(volume == capacity){
        capacity = (capacity == 0) ? 1 : capacity * 2;
        int* newData = new int[capacity];
        for(size_t i = 0; i < volume; ++i){
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    data[volume++] = i;
}   

std::ostream& operator<<(std::ostream& os, const IntVector& vec){
    for(size_t i = 0; i < vec.volume; ++i){
        os << vec.data[i] << " ";
    }
    return os;
}

IntVector& IntVector::operator=(const IntVector& other){
    if(this != &other){
        delete[] data;
        volume = other.volume;
        capacity = other.volume;
        data = new int[capacity];
        for(size_t i = 0; i < volume; ++i){
            data[i] = other.data[i];
        }
    }
    return *this;
}

int& IntVector::operator[](int index) const{
    return data[index];
}