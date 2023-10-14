#include <string>
#include <iostream>
#include "Sistema.h"
#include "NodoABB.h"
#include "Paquete.h"
#include <fstream>
#include <sstream>

Sistema::Sistema() {
	abb = new ABB();
}

void Sistema::menu_principal() {

	//Ciclo while del men� principal.
	while (true) {

		do {

			//Bloque try que contiene el men�.
			try {

				//El usuario ingresa una opci�n (tipo string) que realiza la conversi�n a int luego.
				std::string opcion;
				std::cout <<
					"****************************************\n"
					"          Menu Sistema de Envios        \n"
					"****************************************\n"
					"[1] Menu Aduana\n"
					"[2] Menu Sucursal\n"
					"[3] Cerrar Programa" << std::endl;

				std::cin >> opcion;

				//Conversi�n opci�n string -> int.
				int opcionInt = std::stoi(opcion);

				//Si el usuario ingresa 3, se termina el programa, eliminando los elementos contenidos en memoria.
				if (opcionInt == 3) {
					return;
					break;
				}

				switch (opcionInt) {

				case(1): {

					//Ciclo while del men� de aduana.
					bool termino = false;

					while (!termino) {
						int opcionInt;

						do {
							//Bloque try que contiene el men�.
							try {

								//El usuario ingresa una opci�n (tipo string) que realiza la conversi�n a int luego.
								std::string opcion;
								std::cout <<
									"****************************************\n"
									"     Menu Sistema de Envios - Aduana    \n"
									"****************************************\n"
									"[1] Ingresar Envios\n"
									"[2] Despacho a Sucursal\n"
									"[3] Volver al menu principal" << std::endl;

								std::cin >> opcion;

								//Conversi�n opci�n string -> int.
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
									//Opci�n default: cuando el usuario ingrese un n�mero que no est� en el rango
									//de 1 y 2. Despliega un mensaje de error.
									std::cout << "Dicha opcion no existe, intente nuevamente. " << std::endl;
									std::cout << std::endl;
									break;
								}
							}
							catch (const std::invalid_argument& e) {
								//Captura de excepci�n (argumento inv�lido).
								//Se captura una excepci�n producida por la conversi�n fallida de string a int
								//(El usuario ingresa un caracter no num�rico).
								std::cerr << "Excepcion de tipo: " << e.what() << std::endl << " Ingrese una opcion valida. " << std::endl;
							}

						} while (opcionInt != 3);
					}
					break;
				}

				case(2): {

					//Ciclo while del men� de sucursal.
					bool termino = false;

					while (!termino) {
						int opcionInt;

						do {
							//Bloque try que contiene el men�.
							try {

								//El usuario ingresa una opci�n (tipo string) que realiza la conversi�n a int luego.
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

								//Conversi�n opci�n string -> int.
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
									//Opci�n default: cuando el usuario ingrese un n�mero que no est� en el rango
									//de 1 y 2. Despliega un mensaje de error.
									std::cout << "Dicha opcion no existe, intente nuevamente. " << std::endl;
									std::cout << std::endl;
									break;
								}
							}
							catch (const std::invalid_argument& e) {
								//Captura de excepci�n (argumento inv�lido).
								//Se captura una excepci�n producida por la conversi�n fallida de string a int
								//(El usuario ingresa un caracter no num�rico).
								std::cerr << "Excepcion de tipo: " << e.what() << std::endl << " Ingrese una opcion valida. " << std::endl;
							}

						} while (opcionInt != 4);
					}
				}
					   break;

				default:
					//Opci�n default: cuando el usuario ingrese un n�mero que no est� en el rango
					//de 1 y 2. Despliega un mensaje de error.
					std::cout << "Dicha opcion no existe, intente nuevamente. " << std::endl;
					std::cout << std::endl;
					break;
				}
			}
			catch (const std::invalid_argument& e) {
				//Captura de excepci�n (argumento inv�lido).
				//Se captura una excepci�n producida por la conversi�n fallida de string a int
				//(El usuario ingresa un caracter no num�rico).
				std::cerr << "Excepcion de tipo: " << e.what() << std::endl << " Ingrese una opcion valida. " << std::endl;
			}

		} while (true);
	}
}


//...............  Menu aduana ...............//

void Sistema::ingresar_envios(){

	std::string nombreArchivo = "Aduana.txt";

	// Crear un objeto ifstream para la lectura del archivo
	std::ifstream archivo(nombreArchivo);

	// Verificar si el archivo se abri� correctamente
	if (!archivo.is_open()) {
		std::cerr << "No se pudo abrir el archivo." << std::endl;
		return; 
	}

	// Variable para almacenar los datos le�dos
	std::string linea;
	int contador_linea = 1;

	// Almacenar en ABB el contenido del archivo l�nea por l�nea
	while (std::getline(archivo, linea)) {

		std::stringstream stream(linea);
		std::string codigo_aduana_string, tipo_envio, numero_de_seguimiento, fecha_recepcion_aduana, dimension_paquete, direccion, precio_base_string, 
		peso_paquete_string, telefono_contacto, contenido_fragil_string;

		std::getline(stream, codigo_aduana_string, ',');
		std::getline(stream, tipo_envio, ',');
		std::getline(stream, numero_de_seguimiento, ',');
		std::getline(stream, fecha_recepcion_aduana, ',');
		std::getline(stream, precio_base_string, ',');
		std::getline(stream, telefono_contacto, ',');
		std::getline(stream, peso_paquete_string, ',');
		std::getline(stream, dimension_paquete, ',');
		std::getline(stream, contenido_fragil_string, ',');
		std::getline(stream, direccion, ',');

		try {

			int codigo_aduana = std::stoi(codigo_aduana_string);
			int precio_base = std::stoi(precio_base_string);
			int peso_paquete = std::stoi(peso_paquete_string);
			bool contenido_fragil;

			// Elimina espacios en blanco al principio
			contenido_fragil_string.erase(0, contenido_fragil_string.find_first_not_of(" "));

			// Elimina espacios en blanco al final
			contenido_fragil_string.erase(contenido_fragil_string.find_last_not_of(" ") + 1);

			if (contenido_fragil_string == "Si") {
				contenido_fragil = true;

			}else if (contenido_fragil_string == "No") {
				contenido_fragil = false;

			} else {
				throw std::invalid_argument("");
			}

			Paquete* paquete = new Paquete(codigo_aduana, tipo_envio, numero_de_seguimiento, fecha_recepcion_aduana, precio_base, telefono_contacto,
			peso_paquete, dimension_paquete, contenido_fragil, direccion);
			abb->insertar(paquete);

		} catch (const std::invalid_argument& e) {
			continue;
		}
	}

	// Cerrar el archivo despu�s de la lectura
	archivo.close();
}

void Sistema::despacho_sucursal(){

	std::queue<Paquete*> nodosABB = abb->retornar_ABB();

	while (!nodosABB.empty()) { // SOLAMENTE PARA VISUALIZAR !!!!!, aca debe insertarse al arbol correspondiente a la sucursal
		std::cout << nodosABB.front()->get_codigo_aduana() << std::endl;
		nodosABB.pop();
	}

	delete abb;
}

//...............  Menu sucursal ...............//

void Sistema::asignar_repartidores() {
}

void Sistema::realizar_entregas() {
}

void Sistema::generar_reporte() {
}
