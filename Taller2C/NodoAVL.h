#pragma once
#include "Paquete.h"


/*
Clase del nodo del árbol de búsqueda binario balanceado (AVL).
Almacena un paquete, posee dos punteros a su hijo izquierdo y derecho, y la altura correspondiente
en el AVL, para realizar cálculos de factor de balance entre nodos.
(En el AVL, el hijo izquierdo tiene menor código de aduana que el nodo, y el hijo derecho,
un mayor código de aduana).
*/

class NodoAVL{

private:
	Paquete* paquete; //Paquete almacenado en el nodo.
	NodoAVL* hijo_izquierdo; //Puntero a hijo izquierdo.
	NodoAVL* hijo_derecho; //Puntero a hijo derecho.
	int altura; //La altura del nodo.
public:

	/*
	Métodos públicos del nodo del AVL:
	Constructor y destructor del nodo, designar hijos izquierdo o derecho, obtener
	los punteros a hijo izquierdo o derecho, obtener el paquete almacenado, designar la altura
	del nodo, obtener la altura del nodo.
	*/

	NodoAVL(Paquete* paquete);
	~NodoAVL();
	void set_hijo_izquierdo(NodoAVL* hijo_izquierdo);
	void set_hijo_derecho(NodoAVL* hijo_derecho);
	NodoAVL* get_hijo_izquierdo();
	NodoAVL* get_hijo_derecho();
	Paquete* get_paquete();
	void set_altura(int altura);
	int get_altura();
};

