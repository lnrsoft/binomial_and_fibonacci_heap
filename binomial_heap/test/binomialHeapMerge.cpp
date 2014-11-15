#include <iostream>
#include <vector>
#include "../heap.cpp"

int main(int argc, char * argv[]){

  heap<int> res1, res2, res3, res4, res5, res6, res7;
  int a1=1;

  //8 elementos, un nodo de rango 3
  res1.add(a1);
  res1.add(a1);
  res1.add(a1);
  res1.add(a1);
  res1.add(a1);
  res1.add(a1);
  res1.add(a1);
  res1.add(a1);

  //23 elementos, nodos de rango 0, 1, 2 y 4
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  res2.add(a1);
  
  //14 elementos, nodos de rango 1, 2 y 3
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);
  res4.add(a1);

  //26 elementos, nodos de rango 1, 3 y 4
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);
  res6.add(a1);

  return 0;
}
