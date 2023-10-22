#pragma once
#include "NodoAVL.h"
class AVL{

private:
	NodoAVL* raiz;
	void insertar_private(Paquete* paquete);

public:
	AVL();
	void insertar(Paquete* paquete);
	int altura(NodoAVL* nodo);
	int get_factor_balance(NodoAVL* nodo);
	NodoAVL* rotar_derecha(NodoAVL* nodo);
	NodoAVL* rotar_izquierda(NodoAVL* nodo);
};

