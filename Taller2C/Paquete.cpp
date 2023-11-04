#include "Paquete.h"

/*
Constructor del paquete.
Recibe como parámetros: el código de aduana, el tipo de envío, el número de seguimiento, la fecha de recepción en la aduana,
el precio o valor base, el teléfono de contacto, el peso del paquete, la dimensión del paquete, si es frágil o no (true / false),
la dirección, el código SMT, el repartidor y el tiempo de entrega del paquete.
*/
Paquete::Paquete(int codigo_aduana, std::string tipo_envio, std::string numero_de_seguimiento, std::string fecha_recepcion_aduana,
	int precio_base, std::string telefono_contacto, int peso_paquete, std::string dimension_paquete, bool contenido_fragil, std::string direccion,
	std::string codigo_smt, std::string repartidor, int tiempo_entrega)
{

//...............  Datos de paquete ...............//

	this->codigo_aduana = codigo_aduana;
	this->tipo_envio = tipo_envio;
	this->numero_de_seguimiento = numero_de_seguimiento;
	this->fecha_recepcion_aduana = fecha_recepcion_aduana;
	this->precio_base = precio_base;
	this->telefono_contacto = telefono_contacto;
	this->peso_paquete = peso_paquete;
	this->dimension_paquete = dimension_paquete;
	this->contenido_fragil = contenido_fragil;
	this->direccion = direccion;
	this->repartidor = repartidor;
	this->codigo_smt = codigo_smt;
	this->tiempo_entrega = tiempo_entrega;
}

/*
Destructor del paquete.
Se libera la memoria de sus variables.
*/

Paquete::~Paquete()
{
}

/*
Retorna el código de aduana.
*/

int Paquete::get_codigo_aduana() {
	return this->codigo_aduana;
}

/*
Retorna el tipo de envío.
*/

std::string Paquete::get_tipo_envio() {
	return this->tipo_envio;
}

/*
Retorna el número de seguimiento.
*/

std::string Paquete::get_numero_de_seguimiento() {
	return this->numero_de_seguimiento;
}

/*
Retorna la fecha de recepción en la aduana.
*/

std::string Paquete::get_fecha_recepcion_aduana() {
	return this->fecha_recepcion_aduana;
}

/*
Retorna el precio base.
*/

int Paquete::get_precio_base() {
	return this->precio_base;
}

/*
Retorna el teléfono de contacto.
*/

std::string Paquete::get_telefono_contacto() {
	return this->telefono_contacto;
}

/*
Retorna el peso del paquete.
*/

int Paquete::get_peso_paquete() {
	return this->peso_paquete;
}

/*
Retorna las dimensiones del paquete.
*/

std::string Paquete::get_dimension_paquete() {
	return this->dimension_paquete;
}

/*
Retorna si el paquete es frágil (true), o no (false).
*/

bool Paquete::get_contenido_fragil() {
	return this->contenido_fragil;
}

/*
Retorna la dirección.
*/

std::string Paquete::get_direccion() {
	return this->direccion;
}

/*
Retorna el código SMT.
*/

std::string Paquete::get_codigo_smt(){
	return this->codigo_smt;
}

/*
Retorna el repartidor del paquete.
*/

std::string Paquete::get_repartidor(){
	return this->repartidor;
}

/*
Retorna el tiempo de entrega del paquete (en minutos).
*/

int Paquete::get_tiempo_entrega(){
	return this->tiempo_entrega;
}

/*
Designa el código SMT, recibido por parámetro.
*/

void Paquete::set_codigo_smt(std::string codigo_smt){
	this->codigo_smt = codigo_smt;
}

/*
Designa el repartidor, recibido por parámetro.
*/

void Paquete::set_repartidor(std::string repartidor){
	this->repartidor = repartidor;
}

/*
Designa el tiempo de entrega, recibido por parámetro.
*/

void Paquete::set_tiempo_entrega(int tiempo_entrega) {
	this->tiempo_entrega = tiempo_entrega;
}



