#include <vector>
#include <string>

class Shape{
    public:
        virtual float getArea() = 0;
        virtual int getCorner();
    protected:
        Shape(std::string name, float width, float height, int corner = 0) : name(name), width(width), height(height), corner(corner){}
    private:
        std::string name;
        float width;
        float height;
        int corner;

        Shape(const Shape& other) = delete;
        const Shape& operator=(const Shape& other) = delete;
};

class Circle : public Shape{
    public:
        Circle* getInstance(std::string name, float width, float height, int corner){
            return new Circle(name, width, height, corner);
        }

        float getArea() override{
            return 3.14 * (radius * radius);
        }
    protected:
        Circle(std::string name, float width, float height, int corner) : Shape{name, width, height, corner}{
            radius = width/2;
        } 
    private:
        float radius;
};

class Triangle : public Shape{
    public:
    protected:
};

int main(){
    
}