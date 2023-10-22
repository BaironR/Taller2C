#include "NodoAVL.h"

NodoAVL::NodoAVL(Paquete* paquete){
	this->paquete = paquete;
}

void NodoAVL::set_altura(int altura){
	this->altura = altura;
}

void NodoAVL::set_hijo_izquierdo(NodoAVL* hijo_izquierdo){
	this->hijo_izquierdo = hijo_izquierdo;
}

void NodoAVL::set_hijo_derecho(NodoAVL* hijo_derecho){
	this->hijo_derecho = hijo_derecho;
}

int NodoAVL::get_altura(){
	return this->altura;
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
