#include <string>
#include <iostream>
#include <vector>

class Vehicle{
    public:
        int getPassengers() const { return passanger_load; }
        std::string getReg() const { return reg_nr; }

        virtual ~Vehicle(){};

        virtual void message() = 0; 
    protected:
        Vehicle(std::string r = "", int ant = 0) : reg_nr(r), passanger_load(ant){}
    private:
        int passanger_load;
        std::string reg_nr;

        Vehicle(const Vehicle& other) = delete;
        const Vehicle& operator=(const Vehicle& other) = delete;
};

class Truck : public Vehicle{
    public:
        static Truck* getInstance(std::string r, int ant, int kg){
            return new Truck(r, ant, kg);
        }

        int getMaxLoad() const { return max_load; }
        void message() override{
            std::cout << getReg() << " Typ: Lastbil\n";
        }

    protected:
        Truck(std::string r, int ant, int kg=0) : Vehicle{r, ant}, max_load(kg){}
    private:
        int max_load;
};

class Car : public Vehicle{
    public:
        static Car* getInstance(std::string r, int ant){
            return new Car(r, ant);
        }

        void message() override{
            std::cout << getReg() << " Typ: Bil\n";
        }

    protected:
        Car(std::string r, int ant, int kg=0) : Vehicle{r, ant}{}
};


int main(){
    std::vector<Vehicle*> vehicle;

    Truck* firstTruck = Truck::getInstance("ABC 123", 5, 3000);
    vehicle.push_back(firstTruck);
    Truck* secondTruck = Truck::getInstance("DEF 456", 50, 90000);
    vehicle.push_back(secondTruck);
    Car* firstCar = Car::getInstance("DFG 008", 50);
    vehicle.push_back(firstCar);

    int totalAntPassagerare = 0;// Var tidigare felaktigt "double"
    for (int i=0;i < vehicle.size();i++)
        totalAntPassagerare += vehicle[i]->getPassengers();

    int totalAntBilPassagerare;
    for (int i=0;i < vehicle.size();i++)
        totalAntPassagerare += vehicle[i]->getPassengers();

    std::cout << "Totalt antal passagerare= " <<
    totalAntPassagerare << std::endl;

    std::cout << "Totalt antal bilpassagerare= " <<
    totalAntBilPassagerare << std::endl;

    for (int i=0;i < vehicle.size();i++)
        vehicle[i]->message();
    for (int i=0;i < vehicle.size();i++)
        vehicle[i]->message();
}