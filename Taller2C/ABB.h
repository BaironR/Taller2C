#pragma once
#include "NodoABB.h"
#include <queue>

class ABB {

private:
	NodoABB* raiz;
	void insertar_private(Paquete* paquete);

public:
	ABB();
	~ABB();
	void eliminar_nodos(NodoABB* nodo);
	void insertar(Paquete* paquete);
	std::queue<Paquete*> retornar_ABB(NodoABB* nodo, std::queue<Paquete*> cola);
};
