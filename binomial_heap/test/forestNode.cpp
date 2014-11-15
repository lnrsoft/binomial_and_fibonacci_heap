#include <iostream>
#include "../heap.h"

using namespace std;

int main(int argc, char * argv[]){
  
  forestNode a(12), b(3), c(4);

  a.show(); cout << endl;
  b.show(); cout << endl;
  c.show(); cout << endl;

  if (a<b)
    cout << "12 nunca deberia ser menos que 3" << endl;
  else
    cout << "3 siempre deberia ser mayor que 12" << endl;

  return 0;
}
