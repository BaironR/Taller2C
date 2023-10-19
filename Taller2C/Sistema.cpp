#include <string>
#include <iostream>
#include "Sistema.h"
#include "NodoABB.h"
#include "Paquete.h"
#include <fstream>
#include <sstream>

Sistema::Sistema() {
}

void Sistema::menu_principal() {

	//Ciclo while del menú principal.
	while (true) {

		do {

			//Bloque try que contiene el menú.
			try {

				//El usuario ingresa una opción (tipo string) que realiza la conversión a int luego.
				std::string opcion;
				std::cout <<
					"****************************************\n"
					"          Menu Sistema de Envios        \n"
					"****************************************\n"
					"[1] Menu Aduana\n"
					"[2] Menu Sucursal\n"
					"[3] Cerrar Programa" << std::endl;

				std::cin >> opcion;

				//Conversión opción string -> int.
				int opcionInt = std::stoi(opcion);

				//Si el usuario ingresa 3, se termina el programa, eliminando los elementos contenidos en memoria.
				if (opcionInt == 3) {
					return;
					break;
				}

				switch (opcionInt) {

				case(1): {

					//Ciclo while del menú de aduana.
					bool termino = false;

					while (!termino) {
						int opcionInt;

						do {
							//Bloque try que contiene el menú.
							try {

								//El usuario ingresa una opción (tipo string) que realiza la conversión a int luego.
								std::string opcion;
								std::cout <<
									"****************************************\n"
									"     Menu Sistema de Envios - Aduana    \n"
									"****************************************\n"
									"[1] Ingresar Envios\n"
									"[2] Despacho a Sucursal\n"
									"[3] Volver al menu principal" << std::endl;

								std::cin >> opcion;

								//Conversión opción string -> int.
								opcionInt = std::stoi(opcion);

								switch (opcionInt) {

								case(1):
									ingresar_envios();
									break;

								case(2):
									despacho_sucursal();
									break;

								case(3):
									termino = true;
									break;

								default:
									//Opción default: cuando el usuario ingrese un número que no esté en el rango
									//de 1 y 2. Despliega un mensaje de error.
									std::cout << "Dicha opcion no existe, intente nuevamente. " << std::endl;
									std::cout << std::endl;
									break;
								}
							}
							catch (const std::invalid_argument& e) {
								//Captura de excepción (argumento inválido).
								//Se captura una excepción producida por la conversión fallida de string a int
								//(El usuario ingresa un caracter no numérico).
								std::cerr << "Excepcion de tipo: " << e.what() << std::endl << " Ingrese una opcion valida. " << std::endl;
							}

						} while (opcionInt != 3);
					}
					break;
				}

				case(2): {

					//Ciclo while del menú de sucursal.
					bool termino = false;

					while (!termino) {
						int opcionInt;

						do {
							//Bloque try que contiene el menú.
							try {

								//El usuario ingresa una opción (tipo string) que realiza la conversión a int luego.
								std::string opcion;
								std::cout <<
									"****************************************\n"
									"    Menu Sistema de Envios - Sucursal   \n"
									"****************************************\n"
									"[1] Asignar repartidores\n"
									"[2] Realizar Entregas\n"
									"[3] Generar Reporte\n"
									"[4] Volver al menu principal" << std::endl;

								std::cin >> opcion;

								//Conversión opción string -> int.
								opcionInt = std::stoi(opcion);


								switch (opcionInt) {

								case(1):
									asignar_repartidores();
									break;

								case(2):
									realizar_entregas();
									break;

								case(3):
									generar_reporte();
									break;

								case(4):
									termino = true;
									break;

								default:
									//Opción default: cuando el usuario ingrese un número que no esté en el rango
									//de 1 y 2. Despliega un mensaje de error.
									std::cout << "Dicha opcion no existe, intente nuevamente. " << std::endl;
									std::cout << std::endl;
									break;
								}
							}
							catch (const std::invalid_argument& e) {
								//Captura de excepción (argumento inválido).
								//Se captura una excepción producida por la conversión fallida de string a int
								//(El usuario ingresa un caracter no numérico).
								std::cerr << "Excepcion de tipo: " << e.what() << std::endl << " Ingrese una opcion valida. " << std::endl;
							}

						} while (opcionInt != 4);
					}
				}
					   break;

				default:
					//Opción default: cuando el usuario ingrese un número que no esté en el rango
					//de 1 y 2. Despliega un mensaje de error.
					std::cout << "Dicha opcion no existe, intente nuevamente. " << std::endl;
					std::cout << std::endl;
					break;
				}
			}
			catch (const std::invalid_argument& e) {
				//Captura de excepción (argumento inválido).
				//Se captura una excepción producida por la conversión fallida de string a int
				//(El usuario ingresa un caracter no numérico).
				std::cerr << "Excepcion de tipo: " << e.what() << std::endl << " Ingrese una opcion valida. " << std::endl;
			}

		} while (true);
	}
}


//...............  Menu aduana ...............//

void Sistema::ingresar_envios() {
}

void Sistema::despacho_sucursal() {
}

			Paquete* paquete = new Paquete(codigo_aduana, tipo_envio, numero_de_seguimiento, fecha_recepcion_aduana, precio_base, telefono_contacto,
			peso_paquete, dimension_paquete, contenido_fragil, direccion);
			abb->insertar(paquete);

		} catch (const std::invalid_argument& e) {
			continue;
		}
	}

	// Cerrar el archivo después de la lectura
	archivo.close();
}

void Sistema::despacho_sucursal(){
	std::queue<Paquete*> nodosABB = abb->retornar_ABB();

	std::queue<Paquete*> filaAuxiliar;
	int cantidad_paquetes = 0;



	while (!nodosABB.empty()) { // SOLAMENTE PARA VISUALIZAR !!!!!, aca debe insertarse al arbol correspondiente a la sucursal
		std::cout << nodosABB.front()->get_codigo_aduana() << std::endl;
		filaAuxiliar.push(nodosABB.front());
		cantidad_paquetes++;
		nodosABB.pop();
	}

	delete abb;


	heap = new Heap(cantidad_paquetes);

	int tiempo = 10000;

	while (!filaAuxiliar.empty()) {
		filaAuxiliar.front()->setTiempo(tiempo);
		heap->insertar_paquete(filaAuxiliar.front());
		filaAuxiliar.pop();
		tiempo -= 500;
	}

	heap->imprimir_arreglo();

	hay_avl = true;
}

//...............  Menu sucursal ...............//

void Sistema::asignar_repartidores() {
}

void Sistema::realizar_entregas() {
	if (hay_avl) {

	struct tm hora;
	std::time_t now = std::time(nullptr);
	localtime_s(&hora, &now);

	int dia_int = hora.tm_mday;
	std::string dia_string = "";
	if (dia_int < 10) { dia_string += "0";}
	dia_string += std::to_string(dia_int);

	int mes_int = hora.tm_mon + 1;
	std::string mes_string = "";
	if (mes_int < 10) {mes_string += "0";}
	mes_string += std::to_string(mes_int);


	int anio_int = hora.tm_year + 1900;
	std::string anio_string = std::to_string(anio_int);


	int hora_local = hora.tm_hour;
	int minuto = hora.tm_min;
	int segundo = hora.tm_sec;
	std::string hora_string = "";
	std::string min_string = "";
	std::string segun_string = "";

	if (hora_local < 10) {
		hora_string += "0";
	}

	if (minuto < 10) {
		min_string += "0";
	}

	if (segundo < 10) {
		segun_string += "0";
	}

	hora_string += std::to_string(hora_local);
	min_string += std::to_string(minuto);
	segun_string += std::to_string(segundo);


	std::string fecha_reporte = dia_string + "-" + mes_string + "-" + anio_string + "_" + hora_string + "-" + min_string + "-" + segun_string;
	std::string nombre_archivo = fecha_reporte + "_DatosSucursal.txt";
	std::cout << nombre_archivo << std::endl;
	std::cout << fecha_reporte << std::endl;
	fechas_reporte.push_back(fecha_reporte);


	}







}

void Sistema::generar_reporte() {

	int dia = 0;
	int mes = 0;
	int anio = 0;

	try
	{
		std::cout << "Generar reportes: " << std::endl;
		std::cout << "Primer reporte: busqueda por fecha " << std::endl;
		std::cout << "Ingrese el dia del reporte";
		std::cin >> dia;
		std::cout << "Ingrese el mes del reporte";
		std::cin >> mes;
		std::cout << "Ingrese el dia del reporte";
		std::cin >> anio;

		std::string fecha_a_buscar = "";

		if (dia < 10) {
			fecha_a_buscar = "0" + dia;
		}
		else {
			fecha_a_buscar += dia;
		}

		fecha_a_buscar += "-";

		if (mes < 10) {
			fecha_a_buscar = "0" + mes;
		}
		else {
			fecha_a_buscar += mes;
		}

		fecha_a_buscar += "-";
		fecha_a_buscar += anio;




	}
	catch (const std::exception&)
	{

	}
	








}
