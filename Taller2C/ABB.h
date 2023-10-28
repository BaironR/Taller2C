#pragma once
#include "NodoABB.h"
#include <queue>

class ABB {

private:
	NodoABB* raiz;
	void insertar_private(Paquete* paquete);
	void retornar_ABB_private(NodoABB* nodo, std::queue<Paquete*>& cola);

public:
	ABB();
	~ABB();
	void eliminar_nodos(NodoABB* nodo);
	void insertar(Paquete* paquete);
	std::queue<Paquete*> retornar_ABB();
	NodoABB* retornar_raiz_abb();
};
