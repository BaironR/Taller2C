#pragma once
#include "Paquete.h"

/*
Clase del nodo del árbol de búsqueda binario (ABB).
Almacena un paquete, y posee dos punteros a su hijo izquierdo y derecho.
(En el ABB, el hijo izquierdo tiene menor código de aduana que el nodo, y el hijo derecho,
un mayor código de aduana).
*/

class NodoABB {

private:
	Paquete* paquete; //Paquete almacenado en el nodo.
	NodoABB* hijo_izquierdo; //Puntero al hijo izquierdo.
	NodoABB* hijo_derecho; //Puntero al hijo derecho.

public:

	/*
	Métodos públicos del nodo de ABB.
	Constructor (paquete como parámetro) y destructor del nodo, obtener paquete, 
	obtener hijo izquierdo o derecho, designar hijo izquierdo o derecho (con el puntero 
	a ese nodo como parámetro).
	*/

	NodoABB(Paquete* paquete);
	~NodoABB();
	Paquete* get_paquete();
	NodoABB* get_hijo_izquierdo();
	NodoABB* get_hijo_derecho();
	void set_hijo_izquierdo(NodoABB* hijo_izquierdo);
	void set_hijo_derecho(NodoABB* hijo_derecho);
};
