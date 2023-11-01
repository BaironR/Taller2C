#pragma once
#include <queue>
#include "NodoAVL.h"
#include <cmath>

class AVL{

private:
	NodoAVL* raiz;
	NodoAVL* insertar_private(NodoAVL* nodo, Paquete* paquete);
	Paquete* buscar_private(NodoAVL* nodo, int codigo_paquete);
	void buscar_paquetes_mayor_24horas(NodoAVL* nodo, std::queue <Paquete*>& cola);
	void obtener_paquetes_private(NodoAVL* nodo, std::queue <Paquete*>& cola_paquetes);
	bool paquetesConRepartidor_private(NodoAVL* nodo);
	void destruirAVLRecurs(NodoAVL* nodo);
	int cantidad_nodos_private(NodoAVL* nodo);
	int suma_tiempo_envio_private(NodoAVL* nodoAVL, std::string tipo_envio);
	int cantidad_tiempo_envio_private(NodoAVL* nodoAVL, std::string tipo_envio);
public:
	AVL();
	~AVL();
	NodoAVL* rotacion_rr(NodoAVL* nodo);
	NodoAVL* rotacion_ll(NodoAVL* nodo);
	NodoAVL* rotacion_lr(NodoAVL* nodo);
	NodoAVL* rotacion_rl(NodoAVL* nodo);
	int get_altura_recursivo(NodoAVL* nodo, int nivel);
	void insertar(Paquete* paquete);
	Paquete* buscar(int codigo_paquete);
	NodoAVL* get_raiz();
	std::queue<Paquete*> paquetes_mayor_24_horas();
	std::queue<Paquete*> obtener_todos_paquetes();
	bool paquetesConRepartidor();
	int obtener_altura(NodoAVL* nodo);
	int factor_de_balance(NodoAVL* nodo);
	int cantidad_nodos();
	int suma_paquetes_tiempo_envio(std::string tipo_envio);
	int cantidad_paquetes_tiempo_envio(std::string tipo_envio);
};

