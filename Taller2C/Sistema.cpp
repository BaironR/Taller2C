#include <string>
#include <iostream>
#include "Sistema.h"

Sistema::Sistema() {
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

void Sistema::ingresar_envios() {
}

void Sistema::despacho_sucursal() {
}

//...............  Menu sucursal ...............//

void Sistema::asignar_repartidores() {
}

void Sistema::realizar_entregas() {
}

void Sistema::generar_reporte() {
}
