#include "ABB.h"

ABB::ABB() {
	this->raiz = nullptr;
}

ABB::~ABB() {
	eliminar_nodos(this->raiz);
}


void ABB::insertar(Paquete* paquete) {
	insertar_private(paquete);
}

std::queue<Paquete*> ABB::retornar_ABB() {
	std::queue<Paquete*> cola;
	retornar_ABB_private(this->raiz, cola);
	return cola;
}

NodoABB* ABB::retornar_raiz_abb()
{
	return this->raiz;
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

		} else {
			nodo = nodo->get_hijo_derecho();
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

void ABB::retornar_ABB_private(NodoABB* nodo, std::queue<Paquete*>& cola){

	if (nodo->get_hijo_izquierdo()) retornar_ABB_private(nodo->get_hijo_izquierdo(), cola);
	if (nodo) cola.push(nodo->get_paquete());
	if (nodo->get_hijo_derecho()) retornar_ABB_private(nodo->get_hijo_derecho(), cola);
}




