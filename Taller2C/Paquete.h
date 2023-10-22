#pragma once
#include <iostream>

class Paquete
{
private:

//...............  Datos de aduana ...............//

	std::string tipo_envio, numero_de_seguimiento, fecha_recepcion_aduana, dimension_paquete, direccion;
	int codigo_aduana, precio_base, peso_paquete;
	std::string telefono_contacto;
	bool contenido_fragil;

//...............  Datos de sucursal  ...............//

	std::string codigo_smt, repartidor;
	int tiempo_entrega;

public:
	Paquete(int codigo_aduana, std::string tipo_envio, std::string numero_de_seguimiento, std::string fecha_recepcion_aduana,
	int precio_base, std::string telefono_contacto, int peso_paquete, std::string dimension_paquete, bool contenido_fragil, std::string direccion,
		std::string codigo_smt, std::string repartidor, int tiempo_entrega);
	int get_codigo_aduana();
	std::string get_tipo_envio();
	std::string get_numero_de_seguimiento();
	std::string get_fecha_recepcion_aduana();
	int get_precio_base();
	std::string get_telefono_contacto();
	int get_peso_paquete();
	std::string get_dimension_paquete();
	bool get_contenido_fragil();
	std::string get_direccion();
	std::string get_codigo_smt();
	std::string get_repartidor();
	int get_tiempo_entrega();
	void set_codigo_smt(std::string codigo_smt);
	void set_repartidor(std::string repartidor);
	void set_tiempo_entrega(int tiempo_entrega);
};


