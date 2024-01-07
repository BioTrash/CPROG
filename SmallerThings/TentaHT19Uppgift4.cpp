#include <iostream>
#include <string>

class Person{
    public:
        virtual ~Person() = default;
        std::string getNamn() const { return namn; } 
        int getArsikomst() const { return arsinkomst; }

        virtual void skrivUt() const = 0;
    protected:
        Person(std::string namn, int arsinkomst) : namn(namn), arsinkomst(arsinkomst) {};
    private:
        std::string namn;
        int arsinkomst;

        Person(const Person&) = delete;
        const Person operator=(const Person&) = delete;
};

class Anstalld : public Person{
    public:
        static Anstalld* getInstance(std::string namn, int arsinkomst, int manadslon){
            return new Anstalld(namn, arsinkomst, manadslon);
        }

        void skrivUt() const override { std::cout << getNamn() << ' ' << getArsikomst() << ' ' << manadslon; }
    protected:
        Anstalld(std::string namn, int arsinkomst, int manadslon) : Person{namn, arsinkomst}, manadslon(manadslon) {}
    private:
        int manadslon;
};

int main(){
    Anstalld* anstalldObj = Anstalld::getInstance("John Doe", 2022, 5000);
    anstalldObj->skrivUt(); 
    delete anstalldObj; 
}