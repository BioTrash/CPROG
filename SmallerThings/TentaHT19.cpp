#include <iostream>

class Rectangle{
    public:
        Rectangle() : height(0), width(0) {};
        Rectangle(double h, double w) : height(h), width(w) {};

        double area() const { return width*height; }

        friend std::ostream &operator<<( std::ostream &output, const Rectangle &r ){
            output << r.height << ' ' << r.width << ' ' << r.area();
            return output;
        }

        friend Rectangle operator+ (Rectangle r1, Rectangle r2){
            Rectangle result;
            result.height = r1.height + r2.height;
            result.width = r1.width + r2.width;
            return result;
        }

        friend Rectangle operator+ (Rectangle r1, int rValue){
            Rectangle result = r1;
            result.height = r1.height + rValue;
            result.width = r1.width + rValue;
            return result;
        }

        friend Rectangle operator+ (int lValue, Rectangle& r2){
            Rectangle result = r2;
            result.height = r2.height + lValue;
            result.width = r2.width + lValue;
            return result;
        }

        bool operator==(Rectangle& r1){
            if(r1.height == this->height && r1.width == this->width){ return true; }
            else return false;
        }

        const Rectangle& operator++(){
            this->height++;
            this->width++;
            return *this;
        }

        const Rectangle operator++(int){
            Rectangle temp = *this;
            this->height++;
            this->width++;
            return temp;
        }

        Rectangle& operator+=(int rValue){
            this->height += rValue;
            this->width += rValue;
            return *this;
        }

        Rectangle& operator+=(const Rectangle r1){
            this->height += r1.height;
            this->width += r1.width;
            return *this;
        }

    private:
        double height;
        double width;
};

int main(){
    Rectangle r1(2,4), r2(2,4);
    Rectangle r3(0,0), r4;
    Rectangle r5 = r1 + r2;
    ((r1==r2) ? r4+=0 : r4+=1);
    r2 += r1;
    r2 += 2;
    r3 = r2 + r4 + r5 + 5;
    r3++;
    ++r3;
    std::cout << "r3: " << r3 << '\n';
}