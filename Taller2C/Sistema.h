#pragma once
#include "ABB.h"
#include <vector>
#include <ctime>
#include "Heap.h"

class Sistema {

private:
	ABB* abb;
	Heap* heap;
	std::vector <std::string> fechas_reporte;
	int cantidad_reportes; 
	bool hay_avl;

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
};