#include <string>
#include <vector>

//Bad implementation, need to train more

class Managed{
    public:
        Managed(std::string d) : data(d) { objects.push_back(this); }
        
        Managed operator=(Managed* m){
            this->data = m->data;
            objects.pop_back();
            objects.push_back(m);
        }

        ~Managed(){
            objects.pop_back();
        }

        std::string get_data() const { return data; }
    private:
        std::string data;
        static std::vector<Managed *> objects;
};

std::vector<Managed *> Managed::objects;

int main(){
    Managed d = Managed("Hello, World");
    Managed e = d;
}