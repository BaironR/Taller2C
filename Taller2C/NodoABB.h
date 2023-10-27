#pragma once
#include "Paquete.h"

class NodoABB {

private:
	Paquete* paquete;
	NodoABB* hijo_izquierdo;
	NodoABB* hijo_derecho;

public:
	NodoABB(Paquete* paquete);
	Paquete* get_paquete();
	NodoABB* get_hijo_izquierdo();
	NodoABB* get_hijo_derecho();
	void set_hijo_izquierdo(NodoABB* hijo_izquierdo);
	void set_hijo_derecho(NodoABB* hijo_derecho);
};
