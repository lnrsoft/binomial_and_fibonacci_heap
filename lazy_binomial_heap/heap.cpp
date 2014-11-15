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
  heap res;
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
heap<T> & heap<T>::lazyMerge(heap<T> & oper1, heap<T> & oper2){
  if(oper1.elems){
    if(oper2.elems){
      //Si oper2 tiene datos los mezclamos
      //Comprobamos el minimo
      if(oper1.min->value < oper2.min->value)
	oper1.min = oper1.min;
      else
	oper1.min = oper2.min;
      
      //Enlazamos las dos lista de elementos
      pForestNode uno=oper2.elems, dos=oper2.elems->broBackward;
      oper1.elems->broBackward->broForward = uno;
      uno->broBackward = oper1.elems->broBackward;
      oper1.elems->broBackward = dos;
      dos->broForward = oper1.elems;
    }
  }
  else{
    oper1.min = oper2.min;
    oper1.elems = oper2.elems;
  }
  oper2.min = oper2.elems = NULL;
  
  return oper1;
}

template <class T>
void heap<T>::binomialForm(heap<T> & h){
  pForestNode resul = NULL;
  pForestNode minimo, first, next;
  minimo = first = h.elems;
  int maximo = h.elems->range;
  next = h.elems->broForward;
  //Buscamos el minimo valor y el maximo rango
  while(first != next){
    if(next->value < minimo->value)
      minimo = next;
    if(next->range > maximo)
      maximo = next->range;
    next = next->broForward;
  }
  h.min = minimo;
  //Reservamos espacio para todos los posibles nodos que crearemos
  pForestNode vec[maximo + 2];
  //memset(vec, 0, (maximo + 1) * sizeof(forestNode)); //Inicializamos a NULL
  for(int i=0; i < maximo + 2; i++)
    vec[i] = NULL;
  next = first->broForward;
  while(next != first){
    //enlazamos con los otros del mismo rango
    next->lazy = vec[next->range];
    vec[next->range] = next;
    //Hacemos que todos se apunten a si mismos y el padre debe de ser NULL
    if(next->lazy)
      next->lazy->broBackward = next->lazy->broForward = next->lazy;
    next = next->broForward;
  }
  //Nos falta el ultimo elemento
  next->lazy = vec[next->range];
  vec[next->range] = next;
  if(next->lazy)
    next->lazy->broBackward = next->lazy->broForward = next->lazy;
  //fin de insertar los elementos en las posiciones del vector
  pForestNode aux = NULL, swap = NULL;
  //Mezclamos nodos de un mismo rango para crear nodos del rango siguiente mientras haya 2 o mas nodos
  for(int i = 0; i < maximo + 1; i++){
    //Comprobamos si hay nodos con ese rango
    if(vec[i]){
      //Aqui acabamos el trabajo de hacer que todos se apunten a si mismos
      vec[i]->broBackward = vec[i]->broForward = vec[i];
      //si hay dos elementos como mimos mezclamos
      while(vec[i] && vec[i]->lazy){
	aux = littleMerge(vec[i], vec[i]->lazy);
	//cambiamos a donde apunta el vector y quitamos los lazy
	swap = vec[i]->lazy->lazy;
	vec[i]->lazy = vec[i]->lazy->lazy = NULL;
	vec[i] = swap;
	//Si existe algo en la posicion del vector le cambiamos los hermanos a el mismo
	if(vec[aux->range])
	  vec[aux->range]->broBackward = vec[aux->range]->broForward = vec[aux->range];
	//almacenamos en la siguiente posicion el nuevo nodo
	aux->lazy = vec[aux->range];
	vec[aux->range] = aux;
      }
      //Ahora si queda algun nodo de este rango lo agregamos a la lista de elementos
      if(vec[i])
	resul = link(resul, vec[i]);
      vec[i] = NULL;
    }//end if
  }//end for
  //Si hay algo en la ultima posicion del vector debemos seguir
  if(vec[maximo + 1]){
    pForestNode vec2[2] = {NULL, NULL};
    vec2[0] = vec[maximo + 1];
    while(vec2[0]){
      while(vec2[0] && vec2[0]->lazy){
	aux = littleMerge(vec2[0], vec2[0]->lazy);
	swap = vec2[0]->lazy->lazy;
	vec2[0]->lazy = vec2[0]->lazy->lazy = NULL;
	vec2[0] = swap;
	aux->lazy = vec2[1];
	vec2[1] = aux;
      }//end while de recorrido
      //enlazamos el valor si queda
      if(vec2[0])
	resul = link(resul, vec2[0]);
      //pasamos a los del sigueinte rango
      vec2[0] = vec2[1];
      vec2[1] = NULL;
    }//end while de comprobacion
  }//end if si queda algo en la ultima posicion
  h.elems = resul;
}

template <class T>
void heap<T>::deleteMin(){
    if(min){
    if(min != min->broForward){ //Two or more nodes
      pForestNode mysons = min->sons, brothers = min->broForward;
	brothers->broBackward = min->broBackward;
	min->broBackward->broForward = brothers;
      delete min;
      heap hsons, hbro;
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
      /*** Esto es lo que haciamos antes en el binomial ***/
      /*
      if(brothers){
	pForestNodefirst=brothers, *minimo=brothers, *next=brothers->broForward, *maximo=brothers;
	while(first != next){
	  //cout << "El minimo es "<< minimo->value<<", y el maximo es "<<maximo<<endl;
	  if(next->value < minimo->value)
	    minimo = next;
	  if(next->range > maximo)
	    maximo = next;
	  next = next->broForward;
	}
	hbro.min = minimo;
	hbro.elems = maximo;
      }
      */
      hbro.min = hbro.elems = brothers;
      binomialForm(hbro);
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
