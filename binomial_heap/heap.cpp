#include "heap.h"

template <class T>
heap<T>::~heap(){
  toEmpty(elems);
}

template <class T>
void heap<T>::unlink(pForestNode link){
  link->broBackward->broForward = link->broForward;
  link->broForward->broBackward = link->broBackward;
  link->broBackward = link->broForward = link;
  link->father = NULL;
}

template <class T>
heap<T> & heap<T>::merge(heap<T> & oper1,heap<T> & oper2){
    heap<T> res;
    pForestNode o1 = oper1.elems, o2 = oper2.elems;
    
    if (o1 != NULL){
      //oper1->elems != NULL
      if (o2 != NULL){
	//oper1->elems != NULL && oper2->elems != NULL

	o1 = oper1.elems->broBackward;
	o2 = oper2.elems->broBackward;
	
	//Check the minimum
	if (oper1.min->value < oper2.min->value)
	  res.min = oper1.min;
	else
	  res.min = oper2.min;
	
	//Begin the party
	pForestNode next1 = NULL; //It will be the right brother of o1
	pForestNode next2 = NULL; //It will be the right brother of o2
	pForestNode lmerged = NULL;
	
	while( o1 && o2 ){
	  if(o1->range == o2->range){
	    //Both have the same rank, we have to merge them
	    
	    //Calculate the next nodes to merge
	    o1->broBackward != o1 ? next1 = o1->broBackward : next1 = NULL;
	    o2->broBackward != o2 ? next2 = o2->broBackward : next2 = NULL;
	    //Merge, unlink and fix the pointer
	    lmerged = littleMerge(o1, o2);
	    unlink(lmerged);
	    lmerged->broBackward = lmerged->broForward = lmerged;
	    //Move to the next nodes
	    o1 = next1;
	    o2 = next2;

	    //Begin loop to merge lmerged with the current elements
	    do{
	      if(next1 && lmerged && lmerged->range == next1->range){
		//next1 and lmerged have the same rank
		if(next2 && lmerged && lmerged->range == next2->range){
		  //next1, next2 and lmerged have the same rank
		  o1->broBackward != o1 ? next1 = o1->broBackward : next1 = NULL;
		  o2->broBackward != o2 ? next2 = o2->broBackward : next2 = NULL;
		  res.elems = link(res.elems, lmerged);
		  lmerged = littleMerge(o1, o2);
		  unlink(lmerged);
		  lmerged->broBackward = lmerged->broForward = lmerged;
		  o1 = next1;
		  o2 = next2;
		}
		else{
		  //next1 and lmerged have the same rank, however next2 has NOT.
		  o1->broBackward != o1 ? next1 = o1->broBackward : next1 = NULL;
		  lmerged = littleMerge(lmerged, o1);
		  unlink(lmerged);
		  lmerged->broBackward = lmerged->broForward = lmerged;
		  o1 = next1;
		}
	      }
	      else{
		//next1 and lmerged have NOT the same rank
		if(next2 && lmerged && lmerged->range == next2->range){
		  //next2 and lmerged have the same rank, however next1 has NOT
		  o2->broBackward != o2 ? next2 = o2->broBackward : next2 = NULL;
		  lmerged = littleMerge(lmerged, o2);
		  unlink(lmerged);
		  lmerged->broBackward = lmerged->broForward = lmerged;
		  o2 = next2;
		}
		else{
		  //next1 and lmerged have NOT the same rank
		  //AND next2 and lmerged have NOT the same rank either
		  if(lmerged){
		    res.elems = link(res.elems, lmerged);
		    lmerged = NULL;
		  }
		}
	      }
	    }while(lmerged);
	  }
	  else{
	    //One of the nodes has a greater rank
	    if(o1->range > o2->range){
	      //o1's rank is bigger, then take the o2's node and put it in resul
	      o2->broBackward != o2 ? next2 = o2->broBackward : next2 = NULL;
	      unlink(o2);
	      res.elems = link(res.elems, o2);
	      //Update next
	      if (o1)
		next1 = o1;
	    }
	    else{
	      //o2's rank is bigger, then take the o1's node and put it in resul
	      o1->broBackward != o1 ? next1 = o1->broBackward : next1 = NULL;
	      unlink(o1);
	      res.elems = link(res.elems, o1);
	      //Update next
	      if (o2)
		next2 = o2;
	    }
	  }
	  //Go Forward
	  o1 = next1;
	  o2 = next2;
	} //end while

	//Some of the heaps do not have more nodes
	if(o1){
	  //o1 has nodes
	  while(o1){
	    o1->broBackward != o1 ? next1 = o1->broBackward : next1 = NULL;
	    unlink(o1);
	    res.elems = link(res.elems, o1);
	    o1 = next1;
	  }
	}
	else{
	  //o2 has nodes
	  while(o2){
	    o2->broBackward != o2 ? next2 = o2->broBackward : next2 = NULL;
	    unlink(o2);
	    res.elems = link(res.elems, o2);
	    o2 = next2;
	  }
	}
	//Party is over
      }
      else{
	//Return oper1 and finish
	res.min = oper1.min;
	res.elems = oper1.elems;
      }
    }
    else{
      //oper1->elems == NULL
      if(o2 != NULL){
	//oper1->elems == NULL && oper2->elems != NULL
	//Return oper2 and finish
	res.min = oper2.min;
	res.elems = oper2.elems;
      }
      else{
	//oper1->elems == NULL && oper2->elems == NULL
	//It is over, because is nothing else to do
      }
    }

    //Move the values from res to o1
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
	  if(next->value < minimo->value)
	    minimo = next;
	  if(next->range > maximo->range)
	    maximo = next;
	  next = next->broForward;
	}
	hbro.min = minimo;
	hbro.elems = maximo;
      }
      *this = merge(hsons, hbro);
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
