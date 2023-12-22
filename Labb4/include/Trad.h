// Rufus Trukhin rutr7079
// Trad.h
// labb4_tree

#ifndef TRAD_H
#define TRAD_H

#include <iostream>

template <typename T>
class Trad {
public:
    // Default constructor
    Trad() : rot(0) {};

    // Parameterized constructor
    Trad(T d) { rot = new Nod(d); };

    // Copy constructor
    Trad(const Trad& t) { kopiera(t); };

    // Destructor
    ~Trad() { delete rot; };

    // Check if the tree is empty
    bool tomt() const { return !rot; };

    // Get a reference to the data in the root node
    int& varde() const
    {
        koll();
        return rot->data;
    };

    // Get a reference to the left subtree
    Trad& v_barn() const
    {
        koll();
        return *rot->vanster;
    };

    // Get a reference to the right subtree
    Trad& h_barn() const
    {
        koll();
        return *rot->hoger;
    };

    // Assignment operator for deep copy
    Trad& operator=(const Trad&);

    // Equality operator for comparing two trees
    bool operator==(const Trad&) const;

    // Output the elements of the tree
    void skriv_ut() const;
    
    void satt_in(const T& i);

    bool sok(const T& i);

private:
    // Internal private class representing a node in the binary tree
    class Nod {
        friend class Trad;
        T data;
        Trad* vanster; // Left child
        Trad* hoger;   // Right child

        // Parameterized constructor for creating a node with data
        Nod(T d) : data(d), vanster(new Trad), hoger(new Trad) {};

        // Destructor for deallocating memory of children
        ~Nod()
        {
            delete vanster;
            delete hoger;
        };
    }; // end class Nod

    // Pointer to the root node
    Nod* rot;

    // Private function to check if the tree is empty
    void koll() const
    {
        if (tomt())
            throw std::range_error("Trad");
    }

    // Private function for deep copying another tree
    void kopiera(const Trad& t);
};

#endif /* Trad_h */
