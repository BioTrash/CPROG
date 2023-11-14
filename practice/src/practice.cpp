// Rufus Trukhin rutr7079

#include <iostream>
#include <vector>

// Definiera en strukt "Person" för att lagra information om en person
struct Person
{
    std::string fnamn;  // Förnamn
    std::string enamn;  // Efternamn
    std::string nummer; // Telefonnummer
};

// Funktion för att visa information om en person med ett givet förnamn
void visa_person(const std::vector<Person>& telefonregister, std::string fnamn)
{
    bool hittatNummer = false;
    // Loopa genom vektorn av personer
    for (auto person : telefonregister) {
        // Kontrollera om förnamnet matchar det angivna förnamnet
        if (person.fnamn == fnamn) {
            // Visa information om personen
            std::cout << person.fnamn << " " << person.enamn << ": " << person.nummer << std::endl;
            hittatNummer = true;
        }
    }
    // Kontrollera om ingen matchande person hittades
    if (telefonregister.empty() && !hittatNummer) {
        std::cout << "Hittade inget nummer!" << std::endl;
    }
}

// Funktion för att visa hela telefonboken
void skriv_hela_telefonreg(const std::vector<Person>& telefonregister)
{
    // Loopa genom vektorn av personer och visa information om varje person
    for (auto person : telefonregister) {
        std::cout << person.fnamn << " " << person.enamn << ": " << person.nummer << std::endl;
    }
}

// Funktion för att lägga till en ny person i telefonboken
void ny_person(std::vector<Person>& telefonregister, std::string fnamn, std::string enamn, std::string nummer)
{
    // Skapa en ny Person-objekt med den angivna informationen
    Person nyPerson{fnamn, enamn, nummer};
    // Lägg till den nya personen i vektorn
    telefonregister.push_back(nyPerson);
}

// Funktion för att ta bort en person från telefonboken baserat på förnamnet
void ta_bort_person(std::vector<Person>& telefonregister, std::string fnamn)
{
    // Loopa genom vektorn av personer
    for (size_t i = 0; i < telefonregister.size(); i++) {
        // Kontrollera om förnamnet matchar det angivna förnamnet
        if (telefonregister[i].fnamn == fnamn) {
            // Visa ett meddelande och ta bort personen från vektorn
            std::cout << fnamn << " " << telefonregister[i].enamn << " tas nu bort." << std::endl;
            telefonregister.erase(telefonregister.begin() + i);
        }
    }
}

// Huvudfunktionen
int main()
{
    std::vector<Person> telefonregister; // Vektor för att lagra personer i telefonboken

    // Lägg till några initiala personer i telefonboken
    ny_person(telefonregister, "Christina", "Nyberg", "0707423653");
    ny_person(telefonregister, "Josefin", "Danielsson", "0705463245");
    ny_person(telefonregister, "Ellen", "Lindgren", "0705643229");
    ny_person(telefonregister, "Stig", "Ek", "0705673247");
    ny_person(telefonregister, "Linus", "Jonasson", "0703457923");
    ny_person(telefonregister, "Adam", "Nordin", "0203456297");

    std::string kommando, fnamn, enamn, nummer;

    do {
        std::cout << "Kommando: ";
        std::cin >> kommando;

        // Kontrollera kommandot och utför motsvarande åtgärd
        if (kommando == "s") {
            skriv_hela_telefonreg(telefonregister);
        } else if (kommando == "v") {
            std::cin >> enamn;
            visa_person(telefonregister, enamn);
        } else if (kommando == "n") {
            std::cin >> fnamn;
            std::cin >> enamn;
            std::cin >> nummer;
            ny_person(telefonregister, fnamn, enamn, nummer);
        } else if (kommando == "d") {
            std::cin >> fnamn;
            ta_bort_person(telefonregister, fnamn);
        }

    } while (kommando != "q"); // Fortsätt loopen tills kommandot är "q"

    printf("Hejdå!"); // Avslutningsmeddelande

    return 0;
}