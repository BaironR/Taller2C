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
	Aqu� se ejecuta la l�gica principal del programa.
	Posee los 3 �rboles (ABB, AVL, Heap), variables booleanas que indican si hay un ABB o AVL, 
	y 2 vectores, que almacenan los nombres de archivos de aduana y su valor base.
	Tiene los m�todos para la ejecuci�n del taller: el men� principal, ingresar env�os, el despacho a sucursal,
	asignar repartidores, realizar las entregas, generar reportes, leer los reportes, obtener la fecha actual, 
	y crear un reporte al eliminar el AVL, si hay.
	*/

private:

	/*
	Variables privadas del Sistema:
	El �rbol binario de b�squeda (ABB), el �rbol binario de b�squeda balanceado (AVL),
	el min heap, variables booleanas para comprobar si existe el ABB y AVL, vector de strings
	para almacenar los nombres de los archivos de aduana, y vector de enteros que almacena el valor
	total base le�do en un archivo de aduana espec�fico.
	*/

	ABB* abb;
	AVL* avl;
	Heap* min_heap;
	bool hay_abb = false;
	bool hay_avl = false;
	std::vector <std::string> nombres_conjuntos_aduana;
	std::vector <int> valor_conjuntos_aduana;

public:

	/*
	 M�todos p�blicos del sistema.
	 Constructor del sistema, men� principal, el despacho a sucursal, asignar repartidores, realizar las entregas,
	 generar reportes, leer un reporte, obtener la fecha actual, y crear un reporte al eliminar el AVL.
	*/



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