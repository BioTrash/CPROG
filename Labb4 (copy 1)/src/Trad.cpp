//  Rufus Trukhin rutr7079 
//  Trad.cpp
//  labb4_tree

#include <iostream>
#include <stdexcept>
#include "Trad.h"

template class Trad<short>;
template class Trad<double>;

template <typename T>
void Trad<T>::kopiera( const Trad<T>& t)
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
Trad<T>& Trad<T>::operator= (const Trad<T>& t)
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
bool Trad<T>::operator== (const Trad<T>& t) const
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
  if(tomt()){ rot = new Nod(i); }
  else{
    if(i < rot->data){
      if(v_barn().tomt()){
        v_barn() = Trad(i);
      }
      else { v_barn().satt_in(i); }
    }
    else if (i == rot->data  || sok(i)){
      return;
    }
    else if (i > rot->data){
      if(h_barn().tomt()){
        h_barn() = Trad(i);
      }
      else { h_barn().satt_in(i); }
    }
  }


}

template <typename T>
bool Trad<T>::sok(const T& i) const{
  if(i < rot->data){
    if(v_barn().tomt()){
      return 0;
    }
    else { v_barn().sok(i); }
  }
  else if(i == rot->data){
    return 1;
  }
  else if(i > rot->data){
    if(h_barn().tomt()){
      return 0;
    }
    else { h_barn().sok(i); }
  }
}