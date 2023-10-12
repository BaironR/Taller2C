#include "ABB.h"

ABB::ABB() {
}



void ABB::insertar(Paquete* paquete) {
	insertar_private(paquete);
}

std::queue<Paquete*> ABB::retornar_ABB(NodoABB* nodo, std::queue<Paquete*> cola) {
	return cola;
}

ABB::~ABB() {
	eliminar_nodos(this->raiz);
}

void ABB::eliminar_nodos(NodoABB* nodo) {

	if (nodo) {
		eliminar_nodos(nodo->get_hijo_derecho());
		eliminar_nodos(nodo->get_hijo_izquierdo());
		delete nodo;
	}
}

void ABB::insertar_private(Paquete* paquete) {

	NodoABB* nodo = this->raiz;
	NodoABB* padre = nodo;

	while (nodo) {

		padre = nodo;

		if (paquete->get_codigo_aduana() == raiz->get_paquete()->get_codigo_aduana()) {
			return;
		}

		if (paquete->get_codigo_aduana() < nodo->get_paquete()->get_codigo_aduana()) {
			nodo = nodo->get_hijo_izquierdo();

		}
		else {
			nodo = nodo->get_hijo_izquierdo();
		}
	}

	nodo = new NodoABB(paquete);

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




