#ifndef __BINOMIAL_HEAP__
#define __BINOMIAL_HEAP__

#include <iostream>

using namespace std;

/*************************/
/***   Node for Heap   ***/
/*************************/
template <class T>
struct _forestNode{
  /***   Attributes   ***/
  T value;

  int range;  
  _forestNode * father;
  _forestNode * broForward;
  _forestNode * broBackward;
  _forestNode * sons;

  /***   Constructor   ***/
  _forestNode(T v=T()){  value = v; range = 0; sons = father = NULL; broForward = broBackward = this; }

  /***   Methods   ***/
  void show(){
    cout << "Value: " << value << " range: " << range;
  }

  friend ostream & operator<<(ostream & out, const _forestNode & salida){
    return out << "(T:"<<&salida<<",V:"<<salida.value<<",R:"<<salida.range<<")--(F:"<<salida.father<<",BF:"<<salida.broForward<<",BB:"<<salida.broBackward<<",S:"<<salida.sons<<")";
  }

  /***   Operators   ***/
  bool operator<(const _forestNode & other){
    return value < other.value;
  }
};


/*************************/
/***   Binomial Heap   ***/
/*************************/
template <class T>
class heap{
  /***   public   ***/
 public:
  /***   Typedefs  ***/
  typedef struct _forestNode<T> forestNode;
  typedef struct _forestNode<T> * pForestNode;
  /***   Constructors   ***/
  heap(){
    min = NULL;
    elems = NULL;
  }
  heap(T* vector, int size);
  /***   Destructor   ***/
  ~heap();

  /***   Methods   ***/
  const T & queryMin(){  return min->value;  }
  void deleteMin();
  void decreaseKey(pForestNode & node, T & priority);
  bool isEmpty(){  return !elems;  }
  bool check() const;
  pForestNode add(const T & value){
    heap<T> vacio;
    pForestNode aux = new forestNode(value);
    vacio.min = aux;
    vacio.elems = aux;
    *this = merge(*this, vacio);
    return aux;
  }

  /***   private   ***/
 private:
  /***   attributes   ***/
  pForestNode min;
  pForestNode elems;
  
  /***   Private Methods   ***/
  heap<T> & merge(heap<T> & oper1, heap<T> & oper2);
  void unlink(pForestNode link);
  void hover(pForestNode node);
  void toEmpty(pForestNode toDel);
  bool check(const pForestNode & root) const; //For the first list
  bool check(const pForestNode & sons, int range) const; //For the other lists
  pForestNode link(pForestNode link, pForestNode victim){
    if(link){
      link->broBackward->broForward = victim;
      victim->broBackward = link->broBackward;
      link->broBackward = victim;
      victim->broForward = link;
    }
    else{
      link = victim;
    }
    return victim;
  }
  
  pForestNode littleMerge(pForestNode link1, pForestNode link2){
    //Merge both nodes of the same rank
    pForestNode resul;
    if( link1->value < link2->value ){
      //link2 will became a son of link1 and link1 will increase the rank by one
      resul = link1;
      unlink(link2);
      //Link with the sons
      resul->sons = link(resul->sons, link2);
      //Change links of the fathers and sons
      resul->sons = link2;
      link2->father = resul;
    }
    else{
      //link1 will became son of link2 and link2 will increase the rank by one
      resul = link2;
      unlink(link1);
      //Link with the sons
      resul->sons = link(resul->sons, link1);
      //Change the links of the fathers and sons
      resul->sons = link1;
      link1->father = resul;
    }
    resul->range++;
    return resul;
  }
};

#endif
