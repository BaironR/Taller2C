#include "Heap.h"

Heap::Heap(int tamanio_maximo)
{
	this->cantidad_actual = 0;
	this->tamanio_maximo = tamanio_maximo;
	arreglo_paquetes = new Paquete * [tamanio_maximo];
}

void Heap::insertar_paquete(Paquete* paquete_agregar)
{
	if (cantidad_actual == tamanio_maximo) {
		return;
	}

	this->cantidad_actual++;
	int indice = cantidad_actual - 1;
	arreglo_paquetes[indice] = paquete_agregar;

	while (indice != 0 && arreglo_paquetes[get_padre(indice)]->getTiempoEstimado() > arreglo_paquetes[indice]->getTiempoEstimado()) {
		std::swap(arreglo_paquetes[indice],arreglo_paquetes[get_padre(indice)]);
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

	if (izquierdo < cantidad_actual && arreglo_paquetes[izquierdo] < arreglo_paquetes[mas_pequenio]) {
		mas_pequenio = izquierdo;
	}

	if (derecho < cantidad_actual && arreglo_paquetes[derecho] < arreglo_paquetes[mas_pequenio]) {
		mas_pequenio = derecho;
	}

	if (mas_pequenio != indice) {
		std::swap(arreglo_paquetes[indice], arreglo_paquetes[mas_pequenio]);
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
		Paquete* paquete = arreglo_paquetes[i];

		std::cout << paquete->get_codigo_aduana() << "-" << paquete->get_contenido_fragil() << "-" << paquete->getTiempoEstimado() << std::endl;
	}



}