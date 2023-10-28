#pragma once
#include "ABB.h"
#include "AVL.h"
#include <vector>
#include <ctime>
#include "Heap.h"
#include <string>

class Sistema {

private:
	ABB* abb;
	AVL* avl;
	Heap* heap;
	std::vector <std::string> fechas_reporte;
	int cantidad_reportes; 
	bool abb_eliminado = false;
	bool hay_avl;
	bool avl_eliminado = false;
	bool heap_eliminado = false;

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




};