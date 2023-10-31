#include "NodoAVL.h"

NodoAVL::NodoAVL(Paquete* paquete){
	this->paquete = paquete;
	this->hijo_izquierdo = nullptr;
	this->hijo_derecho = nullptr;
}

NodoAVL::~NodoAVL()
{
	
}

void NodoAVL::set_hijo_izquierdo(NodoAVL* hijo_izquierdo){
	this->hijo_izquierdo = hijo_izquierdo;
}

void NodoAVL::set_hijo_derecho(NodoAVL* hijo_derecho){
	this->hijo_derecho = hijo_derecho;
}

NodoAVL* NodoAVL::get_hijo_izquierdo(){
	return this->hijo_izquierdo;
}

NodoAVL* NodoAVL::get_hijo_derecho(){
	return this->hijo_derecho;
}

Paquete* NodoAVL::get_paquete(){
	return this->paquete;
}


