#pragma once
#include "ABB.h"
#include "AVL.h"
#include <vector>
#include <ctime>
#include "Heap.h"
#include <string>
#include <vector>

class Sistema {

private:
	ABB* abb;
	AVL* avl;
	Heap* heap;
	std::vector <std::string> fechas_reporte;
	int cantidad_reportes; 
	bool hay_abb = false;
	bool hay_avl = false;
	bool hay_heap = false;
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
	void reporte_eliminar_avl(bool heap_o_abb);


	void debugueo();

};