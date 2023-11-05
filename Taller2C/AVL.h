#pragma once
#include <queue>
#include "NodoAVL.h"
#include <cmath>

/*
Clase del árbol binario de búsqueda balanceado (AVL).
Su forma de organización es igual a la del ABB (izquierda con código menor al padre, derecho con código mayor),
pero se tiene en cuenta el factor de balance, a partir de la altura de los nodos izquierdo y derecho.
Si hay un desbalance, se realizan las rotaciones para mantener el equilibrio.

Posee otros métodos clave para la ejecución del taller, como la obtención de datos presentes en el AVL actual (
los paquetes con un tiempo de entrega mayor a 1440 minutos o 24 horas, obtener la altura de un nodo, confirmar que
todos los paquetes tienen repartidor, buscar, retornar todos los paquetes, eliminar todo el árbol, etcétera).
*/


//Importante: los métodos públicos que posean una misma función que los privados, ejecutan la versión privada
//del método, que trabaja directamente con la raíz del árbol.

class AVL{

private:
	NodoAVL* raiz; //Raíz del AVL.


	/*
	Métodos privados del AVL:
	Insertar, buscar paquete, buscar paquetes con tiempo de entrega mayor a 24 horas, obtener todos
	los paquetes, destruir ell AVL recursivamente, recuento total de nodos, sumatoria total de tiempo de 
	entrega de paquetes con un tipo de envío, cantidad de paquetes con tipo de envío específico,
	rotaciones RR, LL, LR y RL, obtener la altura de un nodo y su factor de balance.
	*/

	NodoAVL* insertar_private(NodoAVL* nodo, Paquete* paquete);
	Paquete* buscar_private(NodoAVL* nodo, int codigo_paquete);
	void buscar_paquetes_mayor_24horas(NodoAVL* nodo, std::queue <Paquete*>& cola);
	void obtener_paquetes_private(NodoAVL* nodo, std::queue <Paquete*>& cola_paquetes);
	bool paquetesConRepartidor_private(NodoAVL* nodo);
	void destruirAVLRecurs(NodoAVL* nodo);
	int cantidad_nodos_private(NodoAVL* nodo);
	int suma_tiempo_envio_private(NodoAVL* nodoAVL, std::string tipo_envio);
	int cantidad_tipo_envio_private(NodoAVL* nodoAVL, std::string tipo_envio);
	NodoAVL* rotacion_rr(NodoAVL* nodo);
	NodoAVL* rotacion_ll(NodoAVL* nodo);
	NodoAVL* rotacion_lr(NodoAVL* nodo);
	NodoAVL* rotacion_rl(NodoAVL* nodo);
	int obtener_altura(NodoAVL* nodo);
	int factor_de_balance(NodoAVL* nodo);
public:

	/*
	Métodos públicos del AVL:
	Constructor y destructor del AVL, insertar, buscar paquete, obtener la raíz, buscar paquetes con tiempo de entrega mayor a 24 horas,
	obtener todos los paquetes, comprobar si todos los paquetes tienen repartidor, obtener la cantidad de nodos, sumatoria total de 
	tiempo de entrega de paquetes con un tipo de envío y cantidad de paquetes con tipo de envío específico
	*/

	AVL();
	~AVL();
	void insertar(Paquete* paquete);
	Paquete* buscar(int codigo_paquete);
	NodoAVL* get_raiz();
	std::queue<Paquete*> paquetes_mayor_24_horas();
	std::queue<Paquete*> obtener_todos_paquetes();
	bool paquetesConRepartidor();
	int cantidad_nodos();
	int suma_paquetes_tiempo_envio(std::string tipo_envio);
	int cantidad_paquetes_tipo_envio(std::string tipo_envio);
};

