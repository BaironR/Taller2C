#include "NodoABB.h"

/*
Constructor del nodo de ABB.
El atributo de paquete lo inicializa por el que recibe por parámetro,
sin hijo izquierdo ni derecho.
*/

NodoABB::NodoABB(Paquete* paquete) {
	this->paquete = paquete;
	this->hijo_derecho = nullptr;
	this->hijo_izquierdo = nullptr;
}

/*
Destructor del nodo ABB.
Recursivamente destruye el paquete contenido.
*/
NodoABB::~NodoABB()
{
	delete paquete;
}

/*
Retorna el paquete.
*/
Paquete* NodoABB::get_paquete() {
	return this->paquete;
}

/*
Retorna el puntero al hijo izquierdo.
*/
NodoABB* NodoABB::get_hijo_izquierdo() {
	return this->hijo_izquierdo;
}

/*
Retorna el puntero al hijo derecho.
*/
NodoABB* NodoABB::get_hijo_derecho() {
	return this->hijo_derecho;
}

/*
Set hijo izquierdo: designa el hijo izquierdo del nodo, recibido como parámetro.
*/
void NodoABB::set_hijo_izquierdo(NodoABB* hijo_izquierdo) {
	this->hijo_izquierdo = hijo_izquierdo;
}

/*
Set hijo derecho: designa el hijo derecho del nodo, recibido como parámetro.
*/
void NodoABB::set_hijo_derecho(NodoABB* hijo_derecho) {
	this->hijo_derecho = hijo_derecho;
}
