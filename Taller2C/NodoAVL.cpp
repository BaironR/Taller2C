#include "NodoAVL.h"


/*
Constructor del nodo de AVL.
El atributo de paquete lo inicializa por el que recibe por parámetro,
sin hijo izquierdo ni derecho.
Su altura se define en 1.
*/

NodoAVL::NodoAVL(Paquete* paquete){
	this->paquete = paquete;
	this->hijo_izquierdo = nullptr;
	this->hijo_derecho = nullptr;
	this->altura = 1;
}

/*
Destructor del nodo AVL.
Recursivamente destruye el paquete contenido.
*/
NodoAVL::~NodoAVL()
{
	delete paquete;
}

/*
Designar la altura del nodo, por parámetro.
*/

void NodoAVL::set_altura(int altura)
{
	this->altura = altura;
}

/*
Retorna directamente la altura del nodo.
*/
int NodoAVL::get_altura()
{
	return this->altura;
}

/*
Set hijo izquierdo: designa el hijo izquierdo del nodo, recibido como parámetro.
*/
void NodoAVL::set_hijo_izquierdo(NodoAVL* hijo_izquierdo){
	this->hijo_izquierdo = hijo_izquierdo;
}

/*
Set hijo derecho: designa el hijo derecho del nodo, recibido como parámetro.
*/
void NodoAVL::set_hijo_derecho(NodoAVL* hijo_derecho){
	this->hijo_derecho = hijo_derecho;
}

/*
Retorna el puntero al hijo izquierdo.
*/
NodoAVL* NodoAVL::get_hijo_izquierdo(){
	return this->hijo_izquierdo;
}

/*
Retorna el puntero al hijo derecho.
*/
NodoAVL* NodoAVL::get_hijo_derecho(){
	return this->hijo_derecho;
}

/*
Retorna el paquete.
*/
Paquete* NodoAVL::get_paquete(){
	return this->paquete;
}


