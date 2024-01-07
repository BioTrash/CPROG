#include <iostream>

class Klocka {
    public:
        Klocka( int tim = 0, int min = 0, int sek = 0);
        void setTime( int tim, int min, int sek);
        void getTime( int& tim, int& min, int& sek) const;
        int toSecond() const;

        void ticka();

        bool operator<(Klocka kl1);
        bool operator>(Klocka kl1);
        bool operator<=(Klocka kl1);
        bool operator>=(Klocka kl1);
        bool operator==(Klocka kl1);
        bool operator!=(Klocka kl1);

        const Klocka& operator++();

        friend std::ostream& operator<<(std::ostream& output, const Klocka& kl1){
            output << kl1.t << ':' << kl1.m << ':' << kl1.s;
            return output;
        }

    private:
        int t, m, s;
};

Klocka::Klocka(int tim, int min, int sek){
    setTime(tim, min, sek);
}

int Klocka::toSecond() const{
    return s + m*60 + t*3600;
}

const Klocka& Klocka::operator++(){
    this->ticka();
    return *this;
}

bool Klocka::operator<(Klocka kl1){
   return (this->toSecond() < kl1.toSecond()) ? true : false;
}

bool Klocka::operator>(Klocka kl1){
    return (this->toSecond() > kl1.toSecond()) ? true : false;
}

bool Klocka::operator<=(Klocka kl1){
    return (this->toSecond() <= kl1.toSecond()) ? true : false;
}

bool Klocka::operator>=(Klocka kl1){
    return (this->toSecond() >= kl1.toSecond()) ? true : false;
}

bool Klocka::operator==(Klocka kl1){
    return (this->toSecond() == kl1.toSecond()) ? true : false;
}

bool Klocka::operator!=(Klocka kl1){
    return (this->toSecond() != kl1.toSecond()) ? true : false;
}

void Klocka::setTime(int tim, int min, int sek){
    this->t = tim;
    this->m = min;
    this->s = sek;
}

void Klocka::getTime( int& tim, int& min, int& sek) const {
    tim = this->t;
    min = this->m;
    sek = this->s;
}

void Klocka::ticka() {
    s = ( s+1 ) % 60;
    if ( s==0 ) {
        m = ( m+1 ) % 60;
        if ( m==0 )
            t = ( t+1 ) % 24;
    }
}

int main(){
    int timme, minut, sekund;
    Klocka refKlocka;
    refKlocka.setTime(14, 29, 45);
    Klocka minKlocka( 9, 30, 05 ); //what is the point of octal digits
    std::cout << "minKlocka = " << minKlocka << std::endl;
    minKlocka.getTime( timme, minut, sekund );
    ++minKlocka;
    if (minKlocka <= refKlocka){
        std::cout << "Jämförelsen funkade fint";
    }
}