#include "Heap.h"

/*
Constructor del heap.
Como par�metro se recibe la cantidad m�xima de paquetes en el heap.
La cantidad actual de nodos comienza en 0, se define el tama�o m�ximo y se crea el arreglo de nodos
con los paquetes, del heap.
*/

Heap::Heap(int tamanio_maximo)
{
	this->cantidad_actual = 0;
	this->tamanio_maximo = tamanio_maximo;
	arreglo_nodos = new NodoHeap* [tamanio_maximo];
}

/*
Destructor del heap.
Se destruye cada uno de los nodos en cada espacio del arreglo.
*/

Heap::~Heap(){
	for (int i = 0; i < this->cantidad_actual; i++) {
		delete arreglo_nodos[i];
	}
}


/*
Insertar paquete en el heap.
Si la cantidad actual de nodos alcanza el l�mite m�ximo, se retorna.
Se aumenta la cantidad actual en 1, y en el �ltimo espacio del arreglo se inserta el paquete en un nodo.
En caso de que no se cumpla la condici�n de ser un min heap (est� ordenado en base al tiempo de env�o),
se compara el tiempo de entrega del nodo insertado, con el paquete padre (que est� en el espacio indice/2).
Mientras el indice sea distinto de 0, y el valor de entrega del hijo sea menor al del padre, se realiza el 
intercambio de espacios. El indice actual se actualiza al del padre, hasta llegar a la ra�z, donde est�
el paquete con menor tiempo de entrega.
*/

void Heap::insertar_paquete(Paquete* paquete_agregar)
{
	if (cantidad_actual == tamanio_maximo) {
		return;
	}

	// Se inserta el paquete al final del arreglo, y se modifica la cantidad actual.
	this->cantidad_actual++;
	int indice = cantidad_actual - 1;
	arreglo_nodos[indice] = new NodoHeap(paquete_agregar);

	/* Se modifica el min heap en caso de no cumplirse la condici�n de heap
	Mientras el indice no sea 0, y el tiempo de entrega del paquete del padre sea mayor que el de su hijo, se intercambia padre con hijo */

	while (indice != 0 && arreglo_nodos[get_padre(indice)]->get_paquete()->get_tiempo_entrega() > arreglo_nodos[indice]->get_paquete()->get_tiempo_entrega()) {
		std::swap(arreglo_nodos[indice],arreglo_nodos[get_padre(indice)]);
		indice = get_padre(indice);
	}
}


/*
Heapify min. 
Este m�todo permite reordenar el arreglo para mantener la condici�n de min heap, donde
la ra�z tiene el menor tiempo de entrega.
El m�todo recibe un �ndice como par�metro (la primera vez que se llama, 0, la ra�z del heap).
Luego, se obtienen los valores �ndices de sus hijos izquierdo y derecho (2i+1, 2i+2), para definir
cual entre todos los nodos tiene el menor tiempo de entrega (el indice de izquierda y derecha deben ser
menores a la cantidad actual). 

Si alguno de los hijos tiene menor tiempo de entrega, se actualiza la variable del m�s peque�o, y si no
es igual al �ndice recibido originalmente (o sea, que el padre no es el m�s peque�o), se realiza el intercambio.
Recursivamente, se compara hacia abajo, con sus otros hijos, para que se cumpla la condici�n de min heap.
*/

void Heap::heapify_min(int indice)
{
	//�ndices de hijo izquierdo, derecho, y el �ndice del m�s peque�o, inicializado como el �ndice padre.
	int izquierdo = get_hijo_izq(indice);
	int derecho = get_hijo_der(indice);
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

/*
Extraer paquete de la ra�z.
Este m�todo retorna directamente el paquete del nodo en la ra�z del heap.
Si la cantidad actual de nodos es 0, se retorna null. Si solo hay un elemento, se crea
una nueva referencia del paquete con sus datos, se retorna, y elimina el espacio de la ra�z.

Si hay m�s de un elemento, despu�s de crear el paquete a retornar, se elimina el nodo de la ra�z, y en la
ra�z asume en su lugar el nodo que est� en el �ltimo espacio ocupado (espacio actual - 1), y este �ltimo pasa a ser nulo. Se reduce en 1 la 
cantidad actual de nodos. Y para recuperar la condici�n de heap, se ejecuta el m�todo de heapify min con el �ndice
0, de la ra�z, para que el paquete del nodo en el primer espacio posea el menor tiempo de entrega de los paquetes que
est� presentes en el heap de nodos con paquetes.
*/

Paquete* Heap::extraer_paquete()
{
	if (cantidad_actual <= 0) {
		return nullptr;
	}

	if (cantidad_actual == 1) {
		this->cantidad_actual--;
		Paquete* paquete_raiz = arreglo_nodos[0]->get_paquete();

		Paquete* nuevo_paquete = new Paquete(paquete_raiz->get_codigo_aduana(), paquete_raiz->get_tipo_envio(),
			paquete_raiz->get_numero_de_seguimiento(), paquete_raiz->get_fecha_recepcion_aduana(), paquete_raiz->get_precio_base(),
			paquete_raiz->get_telefono_contacto(), paquete_raiz->get_peso_paquete(), paquete_raiz->get_dimension_paquete(), paquete_raiz->get_contenido_fragil(),
			paquete_raiz->get_direccion(),paquete_raiz->get_codigo_smt(),paquete_raiz->get_repartidor(),paquete_raiz->get_tiempo_entrega());

		delete arreglo_nodos[0];
		return nuevo_paquete;
	}

	Paquete* paquete_raiz = arreglo_nodos[0]->get_paquete();

	Paquete* nuevo_paquete = new Paquete(paquete_raiz->get_codigo_aduana(), paquete_raiz->get_tipo_envio(),
		paquete_raiz->get_numero_de_seguimiento(), paquete_raiz->get_fecha_recepcion_aduana(), paquete_raiz->get_precio_base(),
		paquete_raiz->get_telefono_contacto(), paquete_raiz->get_peso_paquete(), paquete_raiz->get_dimension_paquete(), paquete_raiz->get_contenido_fragil(),
		paquete_raiz->get_direccion(), paquete_raiz->get_codigo_smt(), paquete_raiz->get_repartidor(), paquete_raiz->get_tiempo_entrega());

	delete arreglo_nodos[0];
	arreglo_nodos[0] = arreglo_nodos[cantidad_actual-1];
	arreglo_nodos[cantidad_actual - 1] = nullptr;
	this->cantidad_actual--;
	heapify_min(0);
	return nuevo_paquete;
}

/*
Obtener padre.
Se retorna el �ndice del nodo padre ((i-1)/2), del �ndice recibido por par�metro.
*/

int Heap::get_padre(int indice)
{
	return (indice - 1) / 2;
}

/*
Obtener hijo izquierdo.
Se retorna el �ndice del nodo izquierdo (2i+1), del �ndice padre recibido por par�metro.
*/

int Heap::get_hijo_izq(int indice)
{
	return 2 * indice + 1;
}

/*
Obtener hijo derecho.
Se retorna el �ndice del nodo derecho, del �ndice padre recibido por par�metro.
*/

int Heap::get_hijo_der(int indice)
{
	return 2 * indice + 2;
}

/*
Obtener cantidad actual.
Se retorna la cantidad actual de nodos en el heap.
*/

int Heap::get_cantidad_actual()
{
	return this->cantidad_actual;
}
