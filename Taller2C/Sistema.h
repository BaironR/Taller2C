#pragma once
#include "ABB.h"
#include "AVL.h"
#include <vector>
#include <ctime>
#include "Heap.h"
#include <string>
#include <vector>

class Sistema {

	/*
	La clase del sistema.
	Aquí se ejecuta la lógica principal del programa.
	Posee los 3 árboles (ABB, AVL, Heap), variables booleanas que indican si hay un ABB o AVL, 
	y 2 vectores, que almacenan los nombres de archivos de aduana y su valor base.
	Tiene los métodos para la ejecución del taller: el menú principal, ingresar envíos, el despacho a sucursal,
	asignar repartidores, realizar las entregas, generar reportes, leer los reportes, obtener la fecha actual, 
	y crear un reporte al eliminar el AVL, si hay.
	*/

private:
	ABB* abb;
	AVL* avl;
	Heap* heap;
	bool hay_abb = false;
	bool hay_avl = false;
	std::vector <std::string> nombres_conjuntos_aduana;
	std::vector <int> valor_conjuntos_aduana;

public:
	Sistema();
	void menu_principal();

	//...............  Menu aduana ...............//

	void ingresar_envios();
	void despacho_sucursal();

	//...............  Menu sucursal ...............//

	void asignar_repartidores();
	void realizar_entregas();
	void generar_reporte();

	void leer_reporte(std::string nombre_reporte);
	std::string* obtener_fecha_actual();
	void reporte_eliminar_avl(int heap_abb_eliminar);
};