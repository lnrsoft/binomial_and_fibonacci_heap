#include <iostream>
#include <vector>
#include "../heap.cpp"

int main(int argc, char * argv[]){

  heap<int> a, b, c, d, res1, res2, res3, otro;
  int a1=1, a2=2, b3=3, b4=4, c1=5, c2=6, c3=7, c4=8, c5=9, c6=10, c7=11, c8=12, c9=13;
  vector<_forestNode<int> *> vec;

  vec.push_back(a.add(a1));
  vec.push_back(a.add(a2));
  
  vec.push_back(b.add(b3));
  vec.push_back(b.add(b4));
  
  vec.push_back(c.add(a1));
  vec.push_back(c.add(a2));
  
  vec.push_back(d.add(b3));
  vec.push_back(d.add(b4));
  
  vec.clear();

  vec.push_back(otro.add(a2));
  vec.push_back(otro.add(b3));
  vec.push_back(otro.add(b4));
  vec.push_back(otro.add(c1));
  vec.push_back(otro.add(c3));
  vec.push_back(otro.add(c8));
  vec.push_back(otro.add(c5));
  vec.push_back(otro.add(a1));
  vec.push_back(otro.add(c4));
  vec.push_back(otro.add(c6));
  vec.push_back(otro.add(c7));
  vec.push_back(otro.add(c2));
  vec.push_back(otro.add(c9));


  otro.decreaseKey(vec[5], a2);

  otro.deleteMin();
  otro.deleteMin();
  
  vec.push_back(otro.add(a1));
  vec.push_back(otro.add(a1));
  vec.push_back(otro.add(a1));

  otro.deleteMin();
  otro.deleteMin();
  otro.deleteMin();
  otro.deleteMin();
  otro.deleteMin();
  otro.deleteMin();
  otro.deleteMin();
  otro.deleteMin();
  otro.deleteMin();
  otro.deleteMin();
  otro.deleteMin();
  otro.deleteMin();

  return 0;
}
