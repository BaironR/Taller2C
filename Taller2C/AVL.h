#pragma once
#include <queue>
#include "NodoAVL.h"
#include <cmath>

/*
Clase del �rbol binario de b�squeda balanceado (AVL).
Su forma de organizaci�n es igual a la del ABB (izquierda con c�digo menor al padre, derecho con c�digo mayor),
pero se tiene en cuenta el factor de balance, a partir de la altura de los nodos izquierdo y derecho.
Si hay un desbalance, se realizan las rotaciones para mantener el equilibrio.

Posee otros m�todos clave para la ejecuci�n del taller, como la obtenci�n de datos presentes en el AVL actual (
los paquetes con un tiempo de entrega mayor a 1440 minutos o 24 horas, obtener la altura de un nodo, confirmar que
todos los paquetes tienen repartidor, buscar, retornar todos los paquetes, eliminar todo el �rbol, etc�tera).
*/


//Importante: los m�todos p�blicos que posean una misma funci�n que los privados, ejecutan la versi�n privada
//del m�todo, que trabaja directamente con la ra�z del �rbol.

class AVL{

private:
	NodoAVL* raiz; //Ra�z del AVL.


	/*
	M�todos privados del AVL:
	Insertar, buscar paquete, buscar paquetes con tiempo de entrega mayor a 24 horas, obtener todos
	los paquetes, destruir ell AVL recursivamente, recuento total de nodos, sumatoria total de tiempo de 
	entrega de paquetes con un tipo de env�o, cantidad de paquetes con tipo de env�o espec�fico,
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
	M�todos p�blicos del AVL:
	Constructor y destructor del AVL, insertar, buscar paquete, obtener la ra�z, buscar paquetes con tiempo de entrega mayor a 24 horas,
	obtener todos los paquetes, comprobar si todos los paquetes tienen repartidor, obtener la cantidad de nodos, sumatoria total de 
	tiempo de entrega de paquetes con un tipo de env�o y cantidad de paquetes con tipo de env�o espec�fico
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

