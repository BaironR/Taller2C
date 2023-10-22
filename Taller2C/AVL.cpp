#include "AVL.h"

void AVL::insertar_private(Paquete* paquete){

	NodoAVL* nodo = this->raiz;
	NodoAVL* padre = nodo;

	while (nodo) {

		padre = nodo;

		if (paquete->get_codigo_aduana() == raiz->get_paquete()->get_codigo_aduana()) {
			return;
		}

		if (paquete->get_codigo_aduana() < nodo->get_paquete()->get_codigo_aduana()) {
			nodo = nodo->get_hijo_izquierdo();

		} else {
			nodo = nodo->get_hijo_derecho();
		}
	}

	nodo = new NodoAVL(paquete);

	if (!this->raiz) {
		this->raiz = nodo; //Si el ABB está vacío

	} else {

		if (paquete->get_codigo_aduana() < padre->get_paquete()->get_codigo_aduana()) {

			padre->set_hijo_izquierdo(nodo);

		} else {
			
			padre->set_hijo_derecho(nodo);
		}
	}
}

AVL::AVL(){
	this->raiz = nullptr;
}

void AVL::insertar(Paquete* paquete){	
	insertar_private(paquete);
}

int AVL::altura(NodoAVL* nodo){
	
	if (!nodo) {
		return -1;
	}

	else {

		int altura_izquierda = altura(nodo->get_hijo_izquierdo());
		int altura_derecha = altura(nodo->get_hijo_derecho());

		if (altura_izquierda > altura_derecha) {
			return(altura_izquierda+1);

		} else {
			return(altura_derecha+1);
		}
	}
}

int AVL::get_factor_balance(NodoAVL* nodo){
	
	if (!nodo) {
		return -1;
	}

	return altura(nodo->get_hijo_izquierdo()) - altura(nodo->get_hijo_derecho());;
}

NodoAVL* AVL::rotar_derecha(NodoAVL* y){
	
	NodoAVL* x = y->get_hijo_izquierdo();
	NodoAVL* T2 = x->get_hijo_derecho();

	//Rotacion
	x->set_hijo_derecho(y);
	y->set_hijo_izquierdo(T2);
	return x;
}

NodoAVL* AVL::rotar_izquierda(NodoAVL* x){
	
	NodoAVL* y = x->get_hijo_derecho();
	NodoAVL* T2 = y->get_hijo_izquierdo();

	//Rotacion
	y->set_hijo_izquierdo(x);
	x->set_hijo_derecho(T2);
	return y;
}


