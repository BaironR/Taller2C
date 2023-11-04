#pragma once
#include "NodoABB.h"
#include <queue>

class ABB {

	/*
	La clase del �rbol de b�squeda binario.
	Posee nodos que almacenan paquetes. El ABB est� ordenado en base al c�digo de aduana de cada paquete.
	El hijo izquierdo de un nodo tiene un c�digo de aduana menor al del padre, y el derecho, un c�digo mayor.
	Se pueden insertar nuevos nodos al �rbol, retornar su ra�z, retornar una cola con todos los paquetes, o destruir
	recursivamente el �rbol. Posee m�todos p�blicos y privados (que suelen trabajar con el nodo ra�z directamente).
	*/

private:
	NodoABB* raiz; //Ra�z del �rbol ABB.
	void insertar_private(Paquete* paquete); //M�todo para insertar (privado).
	void retornar_ABB_private(NodoABB* nodo, std::queue<Paquete*>& cola); //M�todo para retornar una fila con los paquetes.

public:
	ABB(); //Constructor del ABB.
	~ABB(); //Destructor del ABB.
	void eliminar_nodos(NodoABB* nodo); //Eliminar recursivamente el �rbol.
	void insertar(Paquete* paquete); //Insertar un paquete (p�blico).
	std::queue<Paquete*> retornar_ABB(); //Retornar la cola con los paquetes (p�blico).
	NodoABB* retornar_raiz_abb(); //Retornar la ra�z (p�blico).
};
