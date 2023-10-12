#include "NodoABB.h"

NodoABB::NodoABB(Paquete* paquete) {
	this->paquete = paquete;
	this->hijo_derecho;
	this->hijo_izquierdo;
}

Paquete* NodoABB::get_paquete() {
	return this->paquete;
}

NodoABB* NodoABB::get_hijo_izquierdo() {
	return this->hijo_izquierdo;
}

NodoABB* NodoABB::get_hijo_derecho() {
	return this->hijo_derecho;
}

void NodoABB::set_hijo_izquierdo(NodoABB* hijo_izquierdo) {
	this->hijo_izquierdo = hijo_izquierdo;
}

void NodoABB::set_hijo_derecho(NodoABB* hijo_derecho) {
	this->hijo_derecho = hijo_derecho;
}
