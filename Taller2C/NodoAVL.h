#pragma once
#include "Paquete.h"

class NodoAVL{

private:
	Paquete* paquete;
	NodoAVL* hijo_izquierdo;
	NodoAVL* hijo_derecho;

public:
	NodoAVL(Paquete* paquete);
	~NodoAVL();
	void set_hijo_izquierdo(NodoAVL* hijo_izquierdo);
	void set_hijo_derecho(NodoAVL* hijo_derecho);
	NodoAVL* get_hijo_izquierdo();
	NodoAVL* get_hijo_derecho();
	Paquete* get_paquete();
};

