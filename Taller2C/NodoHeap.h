#pragma once
#include "Paquete.h"
class NodoHeap
{
private:
	Paquete* paquete;
public:
	~NodoHeap();
	NodoHeap(Paquete* paquete);
	Paquete* get_paquete();
	void set_paquete(Paquete* paquete);
};

