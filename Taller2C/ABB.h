#pragma once
#include "NodoABB.h"
#include <queue>

class ABB {

	/*
	La clase del árbol de búsqueda binario.
	Posee nodos que almacenan paquetes. El ABB está ordenado en base al código de aduana de cada paquete.
	El hijo izquierdo de un nodo tiene un código de aduana menor al del padre, y el derecho, un código mayor.
	Se pueden insertar nuevos nodos al árbol, retornar su raíz, retornar una cola con todos los paquetes, o destruir
	recursivamente el árbol. Posee métodos públicos y privados (que suelen trabajar con el nodo raíz directamente).
	*/

private:
	NodoABB* raiz; //Raíz del árbol ABB.
	void insertar_private(Paquete* paquete); //Método para insertar (privado).
	void retornar_ABB_private(NodoABB* nodo, std::queue<Paquete*>& cola); //Método para retornar una fila con los paquetes.

public:
	ABB(); //Constructor del ABB.
	~ABB(); //Destructor del ABB.
	void eliminar_nodos(NodoABB* nodo); //Eliminar recursivamente el árbol.
	void insertar(Paquete* paquete); //Insertar un paquete (público).
	std::queue<Paquete*> retornar_ABB(); //Retornar la cola con los paquetes (público).
	NodoABB* retornar_raiz_abb(); //Retornar la raíz (público).
};
