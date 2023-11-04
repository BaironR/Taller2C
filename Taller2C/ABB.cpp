#include "ABB.h"


/*
Constructor del ABB.
Se inicializa el nodo raíz como nulo.
*/
ABB::ABB() {
	this->raiz = nullptr;
}


/*
Destructor del ABB.
Se ejecuta el método de eliminar nodos recursivamente, tomando como base el nodo raíz.
*/
ABB::~ABB() {
	eliminar_nodos(this->raiz);
}

/*
Insertar (método público).
Se ejecuta el método privado de insertar, tomando en cuenta como parámetro el paquete a insertar.
*/

void ABB::insertar(Paquete* paquete) {
	insertar_private(paquete);
}

/*
Retornar ABB (público).
Se retorna una cola creada, que es modificada por referencia en el método privado de retornar todos los
paquetes del ABB.
*/

std::queue<Paquete*> ABB::retornar_ABB() {
	std::queue<Paquete*> cola;
	retornar_ABB_private(this->raiz, cola);
	return cola;
}

/*
Retornar raíz del ABB.
Se retorna directamente el nodo raíz, para comprobar si el árbol está vacío.
*/

NodoABB* ABB::retornar_raiz_abb()
{
	return this->raiz;
}

/*
Eliminar nodos.
Recursivamente, en postorden, se eliminan cada uno de los nodos del árbol, si el nodo actual no es nulo.
La raíz es el último nodo en eliminarse.
*/

void ABB::eliminar_nodos(NodoABB* nodo) {
	if (nodo) {
		eliminar_nodos(nodo->get_hijo_derecho());
		eliminar_nodos(nodo->get_hijo_izquierdo());
		delete nodo;
	}
}

/*
Insertar (privado).
Como parámetro, se tiene el paquete a insertar.
La inserción se realiza de manera iterativa, con 2 nodos recorriendo el árbol: el nodo actual,
y el nodo padre (empezando por la raíz). Mientras el nodo actual no sea nulo, se itera a través del
arbol, comparando el valor del código de aduana (si es mayor o menor. El ABB está ordenado en base al código
de aduana. El hijo izquierdo tiene un menor código de aduana que el padre, y el derecho, mayor).

Cuando el nodo actual llegue a ser nulo, se inicializa un nuevo nodo con el paquete a insertar.
Si el nodo actual es la raíz (o sea, está vacío el árbol), se define como la raíz.
Dependiendo si su valor de código de paquete es menor o mayor que el nodo padre, el nuevo nodo pasa a ser
el hijo izquierdo o derecho del padre.
*/

void ABB::insertar_private(Paquete* paquete) {

	NodoABB* nodo = this->raiz;
	NodoABB* padre = nodo;

	while (nodo) {

		padre = nodo;

		if (paquete->get_codigo_aduana() == raiz->get_paquete()->get_codigo_aduana()) {
			return;
		}

		if (paquete->get_codigo_aduana() < nodo->get_paquete()->get_codigo_aduana()) {
			nodo = nodo->get_hijo_izquierdo();

		} else {
			nodo = nodo->get_hijo_derecho();
		}
	}

	nodo = new NodoABB(paquete);

	if (!this->raiz) {
		this->raiz = nodo; //Si el ABB está vacío
	} else {

		if (paquete->get_codigo_aduana() < padre->get_paquete()->get_codigo_aduana()) {

			padre->set_hijo_izquierdo(nodo);

		} else {

			padre->set_hijo_derecho(nodo);
		}
	}
}


/*
Retornar ABB (privado).
Se tiene como parámetros el nodo actual, y la referencia de la cola a retornar con los paquetes.
Se comprueba en inorden, todos los nodos del árbol, comprobando primeramente si se posee un hijo izquierdo o
no, recorriendo recursivamente el árbol. Si no, se almacena en la cola el paquete del nodo actual. Y despúes,
se recorre recursivamente hacia la derecha, si se tiene un hijo derecho.
*/

void ABB::retornar_ABB_private(NodoABB* nodo, std::queue<Paquete*>& cola){
	if (nodo->get_hijo_izquierdo()) retornar_ABB_private(nodo->get_hijo_izquierdo(), cola);
	if (nodo) cola.push(nodo->get_paquete());
	if (nodo->get_hijo_derecho()) retornar_ABB_private(nodo->get_hijo_derecho(), cola);
}




