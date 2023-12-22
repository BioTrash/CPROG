// Rufus Trukhin rutr7079
//  Trad.cpp
//  labb4_tree

#include <iostream>
#include "Trad.h"

template <typename T>
void Trad<T>::kopiera( const Trad& t)
{
  //std::cout << "*** Trad<T>::kopiera\n";
  if (t.tomt())
    rot = 0;
  else
  {
    rot = new Nod( t.varde());
    v_barn().kopiera( t.v_barn());
    h_barn().kopiera( t.h_barn());
  }
}

template <typename T>
Trad<T>& Trad<T>::operator= (const Trad& t)
{
  //std::cout << "*** Trad<T>::operator=\n";
  if (rot != t.rot)
  {
    delete rot;
    kopiera(t);
  }
  return *this;
}

template <typename T>
bool Trad<T>::operator== (const Trad& t) const
{
  //std::cout << "*** Trad<T>::operator==\n";
  return (tomt() && t.tomt()) ||
          (!tomt() && !t.tomt() && varde() == t.varde() &&
           v_barn() == t.v_barn() && h_barn() == t.h_barn());
}

template <typename T>
void Trad<T>::skriv_ut() const
{
  // traversera igenom trädet rekursivt enligt principen "in-order"
  if (!tomt())
  {
    v_barn().skriv_ut();
    std::cout << varde() << ' ';
    h_barn().skriv_ut();
  }
}

template <typename T>
void Trad<T>::satt_in(const T& i){
    if (tomt()) { rot = new Nod(i); } 

}

template <typename T>
bool Trad<T>::sok(const T& i){
  return 0;
}

/* template <typename T>
void Trad<T>::inOrderInsert(Nod* node, const T& value){
  if(value < node->data){
    if(node->v_barn().tomt()) { node->v_barn().satt_in(value); }
    else { inOrderInsert(node-v_barn().rot, value); }
  }
  else if(value > node->data) {
    if(node->h_barn().tomt()) { node->h_barn().satt_in(value); }
    else { inOrderInsert(node-h_barn().rot, value); }
  }
}

template <typename T>
bool Trad<T>::inOrderSearch(Nod* node, const T& value){
  if( node == nullptr){ return 0; }
  if(inOrderSearch(node->vanster, value)) { return 1; }
  if(node->data == value) { return 1; }
  if(inOrderSearch(node->hoger, value)) { return 1; }
} */
