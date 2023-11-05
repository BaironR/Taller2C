#pragma once
#include "Paquete.h"

/*
Clase del nodo del �rbol de b�squeda binario (ABB).
Almacena un paquete, y posee dos punteros a su hijo izquierdo y derecho.
(En el ABB, el hijo izquierdo tiene menor c�digo de aduana que el nodo, y el hijo derecho,
un mayor c�digo de aduana).
*/

class NodoABB {

private:
	Paquete* paquete; //Paquete almacenado en el nodo.
	NodoABB* hijo_izquierdo; //Puntero al hijo izquierdo.
	NodoABB* hijo_derecho; //Puntero al hijo derecho.

public:

	/*
	M�todos p�blicos del nodo de ABB.
	Constructor (paquete como par�metro) y destructor del nodo, obtener paquete, 
	obtener hijo izquierdo o derecho, designar hijo izquierdo o derecho (con el puntero 
	a ese nodo como par�metro).
	*/

	NodoABB(Paquete* paquete);
	~NodoABB();
	Paquete* get_paquete();
	NodoABB* get_hijo_izquierdo();
	NodoABB* get_hijo_derecho();
	void set_hijo_izquierdo(NodoABB* hijo_izquierdo);
	void set_hijo_derecho(NodoABB* hijo_derecho);
};
