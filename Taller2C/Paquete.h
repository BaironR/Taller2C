#pragma once
#include <iostream>

/*
Clase del paquete.
Los paquetes se almacenan en nodos entre las 3 estructuras del taller (ABB, AVL y Min Heap).
Posee un total de 13 variables características, que son leídas mediante lectura de archivos: 
El código de aduana, el tipo de envío, el número de seguimiento, la fecha de recepción en la aduana,
el precio o valor base, el teléfono de contacto, el peso del paquete, la dimensión del paquete, si es frágil o no (true / false),
la dirección, el código SMT, el repartidor y el tiempo de entrega del paquete.
El paquete tiene sus métodos para retornar cualquiera de estos atributos, y 3 métodos set: para el código SMT, repartidor, y el tiempo
de entrega.
*/

class Paquete
{
private:
	/*
	Variables privadas del paquete:
	El código de aduana, el tipo de envío, el número de seguimiento, la fecha de recepción en la aduana,
	el precio o valor base, el teléfono de contacto, el peso del paquete, la dimensión del paquete, si es frágil o no (true / false),
	la dirección, el código SMT, el repartidor y el tiempo de entrega del paquete.
	*/

//...............  Datos de aduana ...............//

	std::string tipo_envio, numero_de_seguimiento, fecha_recepcion_aduana, dimension_paquete, direccion;
	int codigo_aduana, precio_base, peso_paquete;

	

	std::string telefono_contacto;
	bool contenido_fragil;

//...............  Datos de sucursal  ...............//

	std::string codigo_smt, repartidor;
	int tiempo_entrega;

public:
	
	/*
	Métodos públicos del paquete:
	Constructor y destructor, métodos get para retornar cualquiera de sus atributos,
	y 3 métodos set para su código SMT, repartidor y tiempo de entrega.
	*/

	Paquete(int codigo_aduana, std::string tipo_envio, std::string numero_de_seguimiento, std::string fecha_recepcion_aduana,
	int precio_base, std::string telefono_contacto, int peso_paquete, std::string dimension_paquete, bool contenido_fragil, std::string direccion,
	std::string codigo_smt, std::string repartidor, int tiempo_entrega);
	~Paquete();
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


