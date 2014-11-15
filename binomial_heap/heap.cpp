#include "heap.h"

template <class T>
heap<T>::~heap(){
  toEmpty(elems);
}

template <class T>
void heap<T>::unlink(pForestNode link){
  //Deslinkamos el nodo de su lista
  link->broBackward->broForward = link->broForward;
  link->broForward->broBackward = link->broBackward;
  link->broBackward = link->broForward = link;
  link->father = NULL;
}

template <class T>
heap<T> & heap<T>::merge(heap<T> & oper1,heap<T> & oper2){
    heap<T> res;
    pForestNode o1 = oper1.elems, o2 = oper2.elems;
    
    if(o1 != NULL){
      //Oper1->elems != NULL
      if(o2 != NULL){
	//Oper1->elems != NULL && Oper2->elems != NULL
	//Aqui es el trabajo de verdad del merge.
	o1 = oper1.elems->broBackward;
	o2 = oper2.elems->broBackward;
	
	//Comprobamos el minimo
	if(oper1.min->value < oper2.min->value)
	  res.min = oper1.min;
	else
	  res.min = oper2.min;
	
	//Empezamos la faena
	pForestNode sig1 = NULL; //El hermano derecho de o1
	pForestNode sig2 = NULL; //El hermano derecho de o2
	pForestNode lmerged = NULL;
	
	while( o1 && o2 ){
	  if(o1->range == o2->range){
	    //Los rangos son los mismo, debemos fusionar estos nodos.
	    
	    //Calculamos siguientes.
	    o1->broBackward != o1 ? sig1 = o1->broBackward : sig1 = NULL;
	    o2->broBackward != o2 ? sig2 = o2->broBackward : sig2 = NULL;
	    //Mezclamos, hacemos unlink y arreglamos punteros.
	    lmerged = littleMerge(o1, o2);
	    unlink(lmerged);
	    lmerged->broBackward = lmerged->broForward = lmerged;
	    //Avanzamos.
	    o1 = sig1;
	    o2 = sig2;
	    
	    //Ahora empezamos con un bucle para mezclarlo con lmerged.
	    do{
	      if(sig1 && lmerged && lmerged->range == sig1->range){
		//sig1 y lmerged tienen el mismo rango.
		if(sig2 && lmerged && lmerged->range == sig2->range){
		  //sig1, sig2 y lmerged tienen el mismo rango.
		  o1->broBackward != o1 ? sig1 = o1->broBackward : sig1 = NULL;
		  o2->broBackward != o2 ? sig2 = o2->broBackward : sig2 = NULL;
		  res.elems = link(res.elems, lmerged);
		  lmerged = littleMerge(o1, o2);
		  unlink(lmerged);
		  lmerged->broBackward = lmerged->broForward = lmerged;
		  o1 = sig1;
		  o2 = sig2;
		}
		else{
		  //sig1 y lmerged tienen el mismo rango, aunque sig2 NO.
		  o1->broBackward != o1 ? sig1 = o1->broBackward : sig1 = NULL;
		  lmerged = littleMerge(lmerged, o1);
		  unlink(lmerged);
		  lmerged->broBackward = lmerged->broForward = lmerged;
		  o1 = sig1;
		}
	      }
	      else{
		//sig1 y lmerged NO tienen el mismo rango.
		if(sig2 && lmerged && lmerged->range == sig2->range){
		  //sig2 y lmerged tienen el mismo rango, sig1 NO.
		  o2->broBackward != o2 ? sig2 = o2->broBackward : sig2 = NULL;
		  lmerged = littleMerge(lmerged, o2);
		  unlink(lmerged);
		  lmerged->broBackward = lmerged->broForward = lmerged;
		  o2 = sig2;
		}
		else{
		  //sig1 y lmerged y sig2 y lmerged tienen diferentes rangos.
		  if(lmerged){
		    res.elems = link(res.elems, lmerged);
		    lmerged = NULL;
		  }
		}
	      }
	    }while(lmerged);
	  }
	  else{
	    //Uno de los nodos tiene un rango mayor
	    if(o1->range > o2->range){
	      //El rango del o1 es mayor, cogemos el nodo del o2 y lo metemos en resul
	      o2->broBackward != o2 ? sig2 = o2->broBackward : sig2 = NULL;
	      unlink(o2);
	      res.elems = link(res.elems, o2);
	      //Calculamos siguientes
	      //o2 = sig2;
	      if (o1)
		sig1 = o1;
	    }
	    else{
	      //El rango del o2 es mayor, cogemos el nodo del o1 y lo metemos en resul
	      o1->broBackward != o1 ? sig1 = o1->broBackward : sig1 = NULL;
	      unlink(o1);
	      res.elems = link(res.elems, o1);
	      //Calculamos siguientes
	      //o1 = sig1;
	      if (o2)
		sig2 = o2;
	    }
	  }
	  //Avanzamos
	  o1 = sig1;
	  o2 = sig2;
	} //end while
	
	//Algunos de los heaps no tiene mas nodos.
	if(o1){
	  //El o1 aun tiene nodos
	  while(o1){
	    o1->broBackward != o1 ? sig1 = o1->broBackward : sig1 = NULL;
	    unlink(o1);
	    res.elems = link(res.elems, o1);
	    o1 = sig1;
	  }
	}
	else{
	  //El o2 aun tiene nodos
	  while(o2){
	    o2->broBackward != o2 ? sig2 = o2->broBackward : sig2 = NULL;
	    unlink(o2);
	    res.elems = link(res.elems, o2);
	    o2 = sig2;
	  }
	}
	//Fin de la fiesta
      }
      else{
	//Oper1->elems != NULL && Oper2->elems == NULL
	//Devolvemos Oper1 y hemos acabado.
	res.min = oper1.min;
	res.elems = oper1.elems;
      }
    }
    else{
      //Oper1->elems == NULL
      if(o2 != NULL){
	//Oper1->elems == NULL && Oper2->elems != NULL
	//Devolvemos Oper2 y hemos acabado.
	res.min = oper2.min;
	res.elems = oper2.elems;
      }
      else{
	//Oper1->elems == NULL && Oper2->elems == NULL
	//Hemos acabado porque no hay nada que hacer.
      }
    }
    
    //Pasamos los valores de res a o1
    pForestNode max, primero;
    max = primero = res.elems;
    while(primero != res.elems->broBackward){
      if (res.elems->range > max->range)
	max = res.elems;
      res.elems = res.elems->broBackward;
    }
    res.elems = max;
    
    oper1.min = res.min;
    oper1.elems = res.elems;
    oper2.min = oper2.elems = res.min = res.elems = NULL;
    while(oper1.min->father != NULL)
      oper1.min = oper1.min->father;
    return oper1;
  }

template <class T>
void heap<T>::deleteMin(){
    if(min){
    if(min != min->broForward){ //Two or more nodes
      pForestNode mysons = min->sons, brothers = min->broForward;
	brothers->broBackward = min->broBackward;
	min->broBackward->broForward = brothers;
      delete min;
      heap<T> hsons, hbro;
      hsons.elems = mysons;
      if(mysons){ //Find min of the sons
	pForestNode first=mysons, minimo=mysons, next=mysons->broForward;
	first->father = NULL;
	while(first != next){
	  next->father = NULL;
	  if(next->value < minimo->value)
	    minimo = next;
	  next = next->broForward;
	}
	hsons.min = minimo;
      }
      else{
	hsons.min = NULL;
      }
      if(brothers){
	pForestNode first=brothers, minimo=brothers, next=brothers->broForward, maximo=brothers;
	while(first != next){
	  //cout << "El minimo es "<< minimo->value<<", y el maximo es "<<maximo->range<<endl;
	  if(next->value < minimo->value)
	    minimo = next;
	  if(next->range > maximo->range)
	    maximo = next;
	  next = next->broForward;
	}
	hbro.min = minimo;
	hbro.elems = maximo;
      }
      //hbro.elems = brothers;
      /*cout << "Compruebo los hijos" << endl;
      hsons.check();
      cout << "Compruebo los hermanos" << endl;
      hbro.check();
      cout << "Ya estan comprobados" << endl;
      */
      *this = merge(hsons, hbro);
      /*cout << "Despues del merge me compruebo a mi mismo" << endl;
      check();
      cout << "Fin de las comprobaciones" << endl;
      */
      hsons.elems = hsons.min = NULL;
    }
    else{ //One node
      if (elems->sons == NULL){
	delete elems;
	elems = min = NULL;
      }
      else{
	//One node with sons
	pForestNode toDelete = elems;
	pForestNode first = elems->sons, minimo = elems->sons, next = elems->sons->broForward;
	first->father=NULL;
	while(first != next){
	  next->father=NULL;
	  if(next->value < minimo->value)
	    minimo = next;
	  next = next->broForward;
	}
	delete elems;
	elems = first;
	min = minimo;
      }
    }
  }
}

template <class T>
void heap<T>::hover(pForestNode node){
  while(node->father && node->value < node->father->value ){
    pForestNode paux = node->father;
    if (paux->father && paux->father->sons == paux)
      paux->father->sons = node;
    node->father = paux->father;
    if (node->sons){
      pForestNode sonsI = node->sons, sonsNext = node->sons->broForward;
      sonsI->father = paux;
      while(sonsI != sonsNext){
	sonsNext->father = paux;
	sonsNext = sonsNext->broForward;
      }
    }
    paux->sons = node->sons;
    paux->father = node;
    node->sons = paux;
    int rangeAux = paux->range;
    paux->range = node->range;
    node->range = rangeAux;
    pForestNode pauxBroB = paux->broBackward, pauxBroF = paux->broForward;
    if(node != node->broBackward){
      paux->broBackward = node->broBackward;
      paux->broForward = node->broForward;
      node->broBackward->broForward = paux;
      node->broForward->broBackward = paux;
    }
    else
      paux->broBackward = paux->broForward = paux;
    if(paux != pauxBroB){
      node->broBackward = pauxBroB;
      node->broForward = pauxBroF;
      pauxBroB->broForward = node;
      pauxBroF->broBackward = node;
    }
    else
      node->broBackward = node->broForward = node;
    pForestNode first=paux, next=paux->broForward, max=paux;
    first->father = node;
    while(first != next){
      next->father = node;
      if(next->range > max->range)
	max = next;
      next = next->broForward;
    }
    node->sons = max;
  }
  if(!node->father){
    if(node->value < min->value)
      min = node;
    if( node == node->broBackward)
      elems = node;
    else
      if(node->range > node->broBackward->range)
	elems = node;
  }
}

template <class T>
void heap<T>::decreaseKey(pForestNode &node, T & priority){
  if(priority < node->value){
    node->value = priority;
    hover(node);
  }
}

template <class T>
void heap<T>::toEmpty(pForestNode toDel){
  if(toDel){
    pForestNode toDelete = NULL, next=NULL;
    while(toDel){
      toEmpty(toDel->sons);
      toDelete = toDel;
      if(toDel != toDel->broForward){
	next = toDel->broForward;
	toDel->broBackward->broForward = toDel->broForward;
	toDel->broForward->broBackward = toDel->broBackward;
	toDel = next;
      }
      else
	toDel = NULL;
      delete toDelete;
    }
  }
}

template <class T>
bool heap<T>::check()const{
  return check(elems);
}

template <class T>
bool heap<T>::check(const pForestNode & root) const{
  bool estado = true, minF = false;
  pForestNode first = root, next = root->broForward;
  while( first != next ){
    if (next == min)
      minF = true;
    if (estado = estado && next->broBackward->broForward == next && next->broForward->broBackward == next && next->father == NULL && check(next, next->range))
      next = next->broForward;
    else{
      cout << "Ha petado en el nodo " << next << endl;
      cout << "next->broBackward->broForward == next = " << (next->broBackward->broForward == next) << endl;
      cout << "next->broForward->broBackward == next = " << (next->broForward->broBackward == next) << endl;
      cout << "next->father == NULL = " << (next->father == NULL) << endl;
      cout << "check(next, next->range) = " << check(next, next->range) << endl;
      return false;
    }
  }
  if (first == min)
    minF = true;
  if(!minF)
    cout << "El minimo no esta en la lista" << endl;
  return estado && first->broBackward->broForward == first && first->broForward->broBackward == first && first->father == NULL && check(first, first->range);
}

template <class T>
bool heap<T>::check(const pForestNode & node, int range) const{
  bool estado = true;
  pForestNode aux = node->sons;
  for(int i=range-1; i > 0; i--, aux = aux->broForward){
    estado = estado && aux->range == i && aux->broBackward->broForward == aux && aux->broForward->broBackward == aux && aux->father == node && check(aux, aux->range);
    if(!estado){
      cout << "Ha petado en el nodo " << aux << endl;
      cout << "aux->broBackward->broForward == aux = " << (aux->broBackward->broForward == aux) << endl;
      cout << "aux->broForward->broBackward == aux = " << (aux->broForward->broBackward == aux) << endl;
      cout << "aux->father == node = " << (aux->father == node) << endl;
      cout << "check(aux, aux->range) = " << check(aux, aux->range) << endl;
      return false;
    }
  }
  return estado;
}
