#include "Paquete.h"

Paquete::Paquete(int codigo_aduana, std::string tipo_envio, std::string numero_de_seguimiento, std::string fecha_recepcion_aduana,
	int precio_base, std::string telefono_contacto, int peso_paquete, std::string dimension_paquete, bool contenido_fragil, std::string direccion,
	std::string codigo_smt, std::string repartidor, int tiempo_entrega)
{

//...............  Datos de aduana ...............//

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
}

int Paquete::get_codigo_aduana() {
	return this->codigo_aduana;
}

std::string Paquete::get_tipo_envio() {
	return this->tipo_envio;
}

std::string Paquete::get_numero_de_seguimiento() {
	return this->numero_de_seguimiento;
}

std::string Paquete::get_fecha_recepcion_aduana() {
	return this->fecha_recepcion_aduana;
}

int Paquete::get_precio_base() {
	return this->precio_base;
}

std::string Paquete::get_telefono_contacto() {
	return this->telefono_contacto;
}

int Paquete::get_peso_paquete() {
	return this->peso_paquete;
}

std::string Paquete::get_dimension_paquete() {
	return this->dimension_paquete;
}

bool Paquete::get_contenido_fragil() {
	return this->contenido_fragil;
}

std::string Paquete::get_direccion() {
	return this->direccion;
}

std::string Paquete::get_codigo_smt(){
	return this->codigo_smt;
}

std::string Paquete::get_repartidor(){
	return this->repartidor;
}

int Paquete::get_tiempo_entrega(){
	return this->tiempo_entrega;
}

void Paquete::set_codigo_smt(std::string codigo_smt){
	this->codigo_smt = codigo_smt;
}

void Paquete::set_repartidor(std::string repartidor){
	this->repartidor = repartidor;
}

void Paquete::set_tiempo_entrega(int tiempo_entrega){
	this->tiempo_entrega = tiempo_entrega;

std::string Paquete::getRepartidor()
{
	return this->repartidor;
}

std::string Paquete::getCodigoSMT()
{
	return this->codigoSMT;
}

int Paquete::getTiempoEstimado()
{
	return this->tiempo_estimado;
}

void Paquete::setRepartidor(std::string repartidor)
{
	this->repartidor = repartidor;
}

void Paquete::setCodigoSMT(std::string codigoSMT)
{
	this->codigoSMT = codigoSMT;
}

void Paquete::setAduana(int codigoAduana)
{
	this->codigo_aduana = codigoAduana;
}

void Paquete::setTiempo(int tiempo_entrega)
{
	this->tiempo_estimado = tiempo_entrega;
}

