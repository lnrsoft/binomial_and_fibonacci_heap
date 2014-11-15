#include <iostream>
#include <vector>
#include "../heap.cpp"

int main(int argc, char * argv[]){

  heap<int> a, b, c, d, res1, res2, res3, otro;
  int a1=1, a2=2, b3=3, b4=4, c1=5, c2=6, c3=7, c4=8, c5=9, c6=10, c7=11, c8=12, c9=13;

  otro.add(a1);
  otro.check();
  otro.add(a2);
  otro.check();
  otro.add(b3);
  otro.check();
  otro.add(b4);
  otro.check();

  otro.add(c1);
  otro.check();
  otro.add(c2);
  otro.check();
  otro.add(c3);
  otro.check();
  otro.add(c4);
  otro.check();
  otro.add(c5);
  otro.check();
  otro.add(c6);
  otro.check();
  otro.add(c7);
  otro.check();
  otro.add(c8);
  otro.check();
  otro.add(c9);
  otro.check();

  return 0;
}
