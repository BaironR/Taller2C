#include "ABB.h"


/*
Constructor del ABB.
Se inicializa el nodo ra�z como nulo.
*/
ABB::ABB() {
	this->raiz = nullptr;
}


/*
Destructor del ABB.
Se ejecuta el m�todo de eliminar nodos recursivamente, tomando como base el nodo ra�z.
*/
ABB::~ABB() {
	eliminar_nodos(this->raiz);
}

/*
Insertar (m�todo p�blico).
Se ejecuta el m�todo privado de insertar, tomando en cuenta como par�metro el paquete a insertar.
*/

void ABB::insertar(Paquete* paquete) {
	insertar_private(paquete);
}

/*
Retornar ABB (p�blico).
Se retorna una cola creada, que es modificada por referencia en el m�todo privado de retornar todos los
paquetes del ABB.
*/

std::queue<Paquete*> ABB::retornar_ABB() {
	std::queue<Paquete*> cola;
	retornar_ABB_private(this->raiz, cola);
	return cola;
}

/*
Retornar ra�z del ABB.
Se retorna directamente el nodo ra�z, para comprobar si el �rbol est� vac�o.
*/

NodoABB* ABB::retornar_raiz_abb()
{
	return this->raiz;
}

/*
Eliminar nodos.
Recursivamente, en postorden, se eliminan cada uno de los nodos del �rbol, si el nodo actual no es nulo.
La ra�z es el �ltimo nodo en eliminarse.
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
Como par�metro, se tiene el paquete a insertar.
La inserci�n se realiza de manera iterativa, con 2 nodos recorriendo el �rbol: el nodo actual,
y el nodo padre (empezando por la ra�z). Mientras el nodo actual no sea nulo, se itera a trav�s del
arbol, comparando el valor del c�digo de aduana (si es mayor o menor. El ABB est� ordenado en base al c�digo
de aduana. El hijo izquierdo tiene un menor c�digo de aduana que el padre, y el derecho, mayor).

Cuando el nodo actual llegue a ser nulo, se inicializa un nuevo nodo con el paquete a insertar.
Si el nodo actual es la ra�z (o sea, est� vac�o el �rbol), se define como la ra�z.
Dependiendo si su valor de c�digo de paquete es menor o mayor que el nodo padre, el nuevo nodo pasa a ser
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
		this->raiz = nodo; //Si el ABB est� vac�o
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
Se tiene como par�metros el nodo actual, y la referencia de la cola a retornar con los paquetes.
Se comprueba en inorden, todos los nodos del �rbol, comprobando primeramente si se posee un hijo izquierdo o
no, recorriendo recursivamente el �rbol. Si no, se almacena en la cola el paquete del nodo actual. Y desp�es,
se recorre recursivamente hacia la derecha, si se tiene un hijo derecho.
*/

void ABB::retornar_ABB_private(NodoABB* nodo, std::queue<Paquete*>& cola){
	if (nodo->get_hijo_izquierdo()) retornar_ABB_private(nodo->get_hijo_izquierdo(), cola);
	if (nodo) cola.push(nodo->get_paquete());
	if (nodo->get_hijo_derecho()) retornar_ABB_private(nodo->get_hijo_derecho(), cola);
}




