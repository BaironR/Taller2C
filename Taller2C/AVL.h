#pragma once
#include "NodoAVL.h"
class AVL{

private:
	NodoAVL* raiz;
	NodoAVL* insertar_private(NodoAVL* nodo, Paquete* paquete);

public:
	AVL();
	NodoAVL* rotacion_rr(NodoAVL* nodo);
	NodoAVL* rotacion_ll(NodoAVL* nodo);
	NodoAVL* rotacion_lr(NodoAVL* nodo);
	NodoAVL* rotacion_rl(NodoAVL* nodo);
	int get_altura_recursivo(NodoAVL* nodo, int nivel);
	void insertar(Paquete* paquete);
};

