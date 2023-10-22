#pragma once
#include "Paquete.h"

class NodoAVL{

private:
	Paquete* paquete;
	int altura = 1;
	NodoAVL* hijo_izquierdo;
	NodoAVL* hijo_derecho;

public:

	NodoAVL(Paquete* paquete);
	void set_altura(int altura);
	void set_hijo_izquierdo(NodoAVL* hijo_izquierdo);
	void set_hijo_derecho(NodoAVL* hijo_derecho);
	int get_altura();
	NodoAVL* get_hijo_izquierdo();
	NodoAVL* get_hijo_derecho();
	Paquete* get_paquete();
};

