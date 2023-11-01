#include "Heap.h"

Heap::Heap(int tamanio_maximo)
{
	this->cantidad_actual = 0;
	this->tamanio_maximo = tamanio_maximo;
	arreglo_nodos = new NodoHeap* [tamanio_maximo];
}

Heap::~Heap()
{
}

void Heap::insertar_paquete(Paquete* paquete_agregar)
{
	if (cantidad_actual == tamanio_maximo) {
		return;
	}

	this->cantidad_actual++;
	int indice = cantidad_actual - 1;
	arreglo_nodos[indice] = new NodoHeap(paquete_agregar);

	while (indice != 0 && arreglo_nodos[get_padre(indice)]->get_paquete()->get_tiempo_entrega() > arreglo_nodos[indice]->get_paquete()->get_tiempo_entrega()) {
		std::swap(arreglo_nodos[indice],arreglo_nodos[get_padre(indice)]);
		indice = get_padre(indice);
	}
}

void Heap::eliminar_paquete(int indice)
{
}

void Heap::heapify_min(int indice)
{
	int izquierdo = 2 * indice;
	int derecho = 2 * indice + 1;
	int mas_pequenio = indice;

	if (izquierdo < cantidad_actual && arreglo_nodos[izquierdo]->get_paquete()->get_tiempo_entrega() < arreglo_nodos[mas_pequenio]->get_paquete()->get_tiempo_entrega()) {
		mas_pequenio = izquierdo;
	}

	if (derecho < cantidad_actual && arreglo_nodos[derecho]->get_paquete()->get_tiempo_entrega() < arreglo_nodos[mas_pequenio]->get_paquete()->get_tiempo_entrega()) {
		mas_pequenio = derecho;
	}

	if (mas_pequenio != indice) {
		std::swap(arreglo_nodos[indice], arreglo_nodos[mas_pequenio]);
		heapify_min(mas_pequenio);
	}
}

Paquete* Heap::retornar_paquete()
{
	return nullptr;
}

Paquete* Heap::extraer_paquete()
{
	return nullptr;
}

int Heap::get_padre(int indice)
{
	return (indice - 1) / 2;
}

int Heap::get_hijo_izq(int indice)
{
	return 2 * indice + 1;
}

int Heap::get_hijo_der(int indice)
{
	return 2 * indice + 2;
}

void Heap::imprimir_arreglo() {
	for (int i = 0; i < this->cantidad_actual; i++) {
		Paquete* paquete = arreglo_nodos[i]->get_paquete();

		std::cout << paquete->get_codigo_aduana() << "-" << paquete->get_contenido_fragil() << "-" << paquete->get_tiempo_entrega() << std::endl;
	}
}