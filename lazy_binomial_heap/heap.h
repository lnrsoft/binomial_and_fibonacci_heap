#ifndef __LAZY_BINOMIAL_HEAP__
#define __LAZY_BINOMIAL_HEAP__

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
  _forestNode * lazy;

  /***   Constructor   ***/
  _forestNode(T v=T()){  value = v; range = 0; sons = father = lazy = NULL; broForward = broBackward = this; }

  /***   Methods   ***/
  void show(){
    cout << "Value: " << value << " range: " << range;
  }

  friend ostream & operator<<(ostream & out, const _forestNode & salida){
    return out << "(T:"<<&salida<<",V:"<<salida.value<<",R:"<<salida.range<<")--(F:"<<salida.father<<",BF:"<<salida.broForward<<",BB:"<<salida.broBackward<<",S:"<<salida.sons<<",L:"<<salida.lazy<<")";
  }

  /***   Operators   ***/
  bool operator<(const _forestNode & other){
    return value < other.value;
  }
};


/******************************/
/***   Lazy Binomial Heap   ***/
/******************************/
template <class T>
class heap{
  /***   public   ***/
 public:
  /***   typedefs   ***/
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
    pForestNode add(const T & value){
    heap<T> vacio;
    pForestNode aux = new forestNode(value);
    vacio.min = aux;
    vacio.elems = aux;
    //merge(*this, vacio);
    *this = lazyMerge(*this, vacio);
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
  heap<T> & lazyMerge(heap<T> & oper1, heap<T> & oper2);
  void binomialForm(heap & h);
  void hover(forestNode *node);
  void toEmpty(forestNode * toDel);
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
    //Mezclamos dos nodos del mismo rango.
    pForestNode resul;
    if( link1->value < link2->value ){
      //link2 sera un hijo de link1 y link1 subira de rango
      resul = link1;
      unlink(link2);
      //Linkar con los hijos
      resul->sons = link(resul->sons, link2);
      //Cambiamos enlaces a padres e hijos
      resul->sons = link2;
      link2->father = resul;
    }
    else{
      //link1 sera un hijo de link2 y link2 subira de rango
      resul = link2;
      unlink(link1);
      //Linkar con los hijos
      resul->sons = link(resul->sons, link1);
      //Cambiamos enlaces a padres e hijos
      resul->sons = link1;
      link1->father = resul;
    }
    resul->range++;
    return resul;
  }
};

#endif
