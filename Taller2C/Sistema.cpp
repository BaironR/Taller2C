#include <string>
#include <iostream>
#include "Sistema.h"
#include "NodoABB.h"
#include "NodoAVL.h"
#include "Paquete.h"
#include <fstream>
#include <sstream>

Sistema::Sistema() {
	abb = nullptr;
	avl = nullptr;
	heap = nullptr;
}

void Sistema::menu_principal() {

	//Ciclo while del menú principal.
	while (true) {

		do {

			//Bloque try que contiene el menú.
			try {

				if (hay_avl) {
					NodoAVL* nodo = avl->get_raiz();
					std::cout << nodo->get_paquete()->get_codigo_aduana() << std::endl;
				}

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


									//ELIMINAR LUEGO !!!!!!!! DEBUGUEO
								case(5):
									debugueo();
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

	if (hay_abb == false) {
		abb = new ABB();
		hay_abb = true;
	}
	
	std::string nombreArchivo = "";
	std::cout << std::endl;
	std::cout << "Ingresar envios" << std::endl;
	std::cout << "Ingrese por teclado el nombre del archivo de la aduana a leer (incluyendo su formato, si es .txt por ejemplo.) " << std::endl;
	std::cin >> nombreArchivo;

	// Crear un objeto ifstream para la lectura del archivo
	std::ifstream archivo(nombreArchivo);

	// Verificar si el archivo se abrió correctamente
	if (!archivo.is_open()) {
		std::cerr << "No se pudo abrir el archivo, intente de nuevo con otro nombre." << std::endl;
		return;
	}

	// Variable para almacenar los datos leídos
	std::string linea;
	int contador_linea = 1;

	// Almacenar en ABB el contenido del archivo línea por línea
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

			}
			else if (contenido_fragil_string == "No") {
				contenido_fragil = false;

			}
			else {
				throw std::invalid_argument("");
			}

			Paquete* paquete = new Paquete(codigo_aduana, tipo_envio, numero_de_seguimiento, fecha_recepcion_aduana,
				precio_base, telefono_contacto, peso_paquete, dimension_paquete, contenido_fragil, direccion,
				"", "", -1);

			abb->insertar(paquete);
		}
		catch (const std::invalid_argument& e) {
			continue;
		}
	}

	// Cerrar el archivo después de la lectura
	archivo.close();
	std::cout << "Archivo leido con exito." << std::endl;
}

void Sistema::despacho_sucursal(){

	//Si existe un árbol ABB, entonces se comprueba si está vacía o si hay paquetes en él.
	//Para este último caso, hay que corroborar si ya existe un árbol AVL o no.
	//Si no hay un AVL, se crea directamente. En el caso contrario, hay que corroborar si hay algún dato nuevo.

	if (hay_abb) {
		if (abb->retornar_raiz_abb() == nullptr) {
			std::cout << "Error: no hay ningun paquete disponible en la Aduana." << std::endl;
		}
		else {
			if (hay_avl) {
				std::queue<Paquete*> nodosABB = abb->retornar_ABB();

				while (!nodosABB.empty()) {
					Paquete* paquete = avl->buscar(nodosABB.front()->get_codigo_aduana());

					if (paquete == nullptr) {
						reporte_eliminar_avl(false);
						delete avl;
						hay_avl = false;

						avl = new AVL();
						hay_avl = true;

						std::queue<Paquete*> insertar_nuevo_avl = abb->retornar_ABB();
						while (!insertar_nuevo_avl.empty()) {
							Paquete* paquete_nuevo = new Paquete(insertar_nuevo_avl.front()->get_codigo_aduana(), insertar_nuevo_avl.front()->get_tipo_envio(),
								insertar_nuevo_avl.front()->get_numero_de_seguimiento(), insertar_nuevo_avl.front()->get_fecha_recepcion_aduana(), insertar_nuevo_avl.front()->get_precio_base(),
								insertar_nuevo_avl.front()->get_telefono_contacto(), insertar_nuevo_avl.front()->get_peso_paquete(), insertar_nuevo_avl.front()->get_dimension_paquete(),
								insertar_nuevo_avl.front()->get_contenido_fragil(), insertar_nuevo_avl.front()->get_direccion(), insertar_nuevo_avl.front()->get_codigo_smt(), insertar_nuevo_avl.front()->get_repartidor(),
								insertar_nuevo_avl.front()->get_tiempo_entrega());
							avl->insertar(paquete_nuevo);
							insertar_nuevo_avl.pop();
						}
						break;
					}
					nodosABB.pop();
				}
			}
			else {
				avl = new AVL();
				hay_avl = true;

				std::queue<Paquete*> nodosABB = abb->retornar_ABB();
				while (!nodosABB.empty()) {
					Paquete* paquete = new Paquete(nodosABB.front()->get_codigo_aduana(), nodosABB.front()->get_tipo_envio(), 
						nodosABB.front()->get_numero_de_seguimiento(), nodosABB.front()->get_fecha_recepcion_aduana(), nodosABB.front()->get_precio_base(), 
						nodosABB.front()->get_telefono_contacto(), nodosABB.front()->get_peso_paquete(), nodosABB.front()->get_dimension_paquete(), 
						nodosABB.front()->get_contenido_fragil(), nodosABB.front()->get_direccion(), nodosABB.front()->get_codigo_smt(), nodosABB.front()->get_repartidor(),
						nodosABB.front()->get_tiempo_entrega());
					avl->insertar(paquete);
					nodosABB.pop();
				}

			}

			delete abb;
			abb = nullptr;
			hay_abb = false;
		}
	}else{
		std::cout << "El arbol ABB de Aduana no existe, intente de nuevo." << std::endl;
	}
}

//...............  Menu sucursal ...............//

void Sistema::asignar_repartidores() {

	std::cout << "Asignar repartidores" << std::endl;

	if (hay_avl) {

		NodoAVL* raiz = avl->get_raiz();
		if (raiz != nullptr) {

			std::string nombreArchivo;
			std::cout << "Ingrese el nombre del archivo para leer los datos de la sucursal: ";
			std::cin >> nombreArchivo;

			// Crear un objeto ifstream para la lectura del archivo
			std::ifstream archivo(nombreArchivo);

			// Verificar si el archivo se abrió correctamente
			if (!archivo.is_open()) {
				std::cerr << "No se pudo abrir el archivo." << std::endl;
				return;
			}

			// Variable para almacenar los datos leídos
			std::string linea;
			int contador_linea = 1;

			// Almacenar en ABB el contenido del archivo línea por línea
			while (std::getline(archivo, linea)) {


				try {
				std::stringstream stream(linea);
				std::string codigo_paquete_string, codigo_smt, repartidor, tiempo_entrega_string;

				std::getline(stream, codigo_paquete_string, ',');
				std::getline(stream, codigo_smt, ',');
				std::getline(stream, repartidor, ',');
				std::getline(stream, tiempo_entrega_string, ',');

				int tiempo_entrega = std::stoi(tiempo_entrega_string);
				int codigo_paquete = std::stoi(codigo_paquete_string);
				Paquete* paqueteAVL = avl->buscar(codigo_paquete);

					if (paqueteAVL != nullptr) {
						paqueteAVL->set_codigo_smt(codigo_smt);
						paqueteAVL->set_repartidor(repartidor);
						paqueteAVL->set_tiempo_entrega(tiempo_entrega);
					}
				}
				catch (const std::invalid_argument& e) {
					continue;
			}
		}
			// Cerrar el archivo después de la lectura.
			archivo.close();
	}else {
		std::cout << "No hay ningun paquete disponible en el arbol AVL, intentelo de nuevo." << std::endl;
	}
}else {
	std::cout << "No existe ningun arbol AVL para asignar repartidores, intente de nuevo." << std::endl;
}
}

std::string* Sistema::obtener_fecha_actual()
{
	std::string* nombre_y_fecha = new std::string[2];

	if (hay_avl) {

		struct tm hora;
		std::time_t now = std::time(nullptr);
		localtime_s(&hora, &now);

		int dia_int = hora.tm_mday;
		std::string dia_string = "";
		if (dia_int < 10) { dia_string += "0"; }
		dia_string += std::to_string(dia_int);

		int mes_int = hora.tm_mon + 1;
		std::string mes_string = "";
		if (mes_int < 10) { mes_string += "0"; }
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


		nombre_y_fecha[0] = nombre_archivo;
		nombre_y_fecha[1] = fecha_reporte;
		fechas_reporte.push_back(fecha_reporte);

		return nombre_y_fecha;
	}
	
	nombre_y_fecha[0] = "";
	nombre_y_fecha[1] = "";
	return nombre_y_fecha;
}

void Sistema::reporte_eliminar_avl(bool heap_o_abb)
{
	std::string* nombrearchivo_fecha = obtener_fecha_actual();
	std::ofstream nuevo_reporte;
	std::string nombre_archivo = nombrearchivo_fecha[0];
	nuevo_reporte.open(nombre_archivo, std::ios::out);
	std::queue <Paquete*> fila_paquetes = avl->obtener_todos_paquetes();

	if (!nuevo_reporte.is_open()) {
		std::cout << "No se pudo escribir el reporte, intente de nuevo." << std::endl;
	}
	else {
		while (!fila_paquetes.empty()) {
			Paquete* paquete = new Paquete(fila_paquetes.front()->get_codigo_aduana(), fila_paquetes.front()->get_tipo_envio(),
				fila_paquetes.front()->get_numero_de_seguimiento(), fila_paquetes.front()->get_fecha_recepcion_aduana(), fila_paquetes.front()->get_precio_base(),
				fila_paquetes.front()->get_telefono_contacto(), fila_paquetes.front()->get_peso_paquete(), fila_paquetes.front()->get_dimension_paquete(),
				fila_paquetes.front()->get_contenido_fragil(), fila_paquetes.front()->get_direccion(), fila_paquetes.front()->get_codigo_smt(), fila_paquetes.front()->get_repartidor(),
				fila_paquetes.front()->get_tiempo_entrega());

			std::string fragil = "No";
			if (paquete->get_contenido_fragil()) {
				fragil = "Si";
			}

			nuevo_reporte << paquete->get_codigo_aduana() << "," << paquete->get_tipo_envio() << "," << paquete->get_numero_de_seguimiento() << "," << paquete->get_fecha_recepcion_aduana() << "," << paquete->get_precio_base() << "," <<
				paquete->get_telefono_contacto() << "," << paquete->get_peso_paquete() << "," << paquete->get_dimension_paquete() << "," << fragil << "," << paquete->get_direccion() << "," << paquete->get_codigo_smt() << "," <<
				paquete->get_repartidor() << "," << paquete->get_tiempo_entrega();
			nuevo_reporte << std::endl;
			
			if (heap_o_abb) {
				heap->insertar_paquete(paquete);
			}
			else {

			}

			fila_paquetes.pop();
		}
		nuevo_reporte.close();
	}

	std::string fecha_hora_reporte = nombrearchivo_fecha[1];
	std::string nombreArchivosReportes = "NombresReportes.txt";
	std::ofstream archivoReportes;
	archivoReportes.open(nombreArchivosReportes, std::ios::app);
	if (archivoReportes.is_open()) {
		archivoReportes << fecha_hora_reporte;
		archivoReportes << std::endl;
		archivoReportes.close();
	}
	else {
		std::cout << "Error: no se pudo abrir el archivo porque no existe, creando uno nuevo..." << std::endl;
		std::ofstream nuevoArchivoReportes;
		nuevoArchivoReportes.open("NombresReportes.txt", std::ios::out);
		nuevoArchivoReportes.close();
		std::cout << "Se genero un nuevo archivo para las fechas de los reportes." << std::endl;
	}
}

void Sistema::realizar_entregas() {
	try {
		if (hay_avl) {
			if (avl->get_raiz() == nullptr) {
				std::cout << "El arbol AVL de la sucursal esta vacio, intente de nuevo.";
				return;
			}
			else {
				bool todos_con_repartidor = avl->paquetesConRepartidor();
				if (todos_con_repartidor) {
					if (hay_heap) {


						//Falta averiguar qué hacer si ya existe un heap.



					}
					else {
						int cantidad_nodos_avl = avl->cantidad_nodos();
						heap = new Heap(cantidad_nodos_avl);
						hay_heap = true;
						reporte_eliminar_avl(true);
						delete avl;
						hay_avl = false;
					}
				}
				else {
					std::cout << "No se puede realizar la entrega de los paquetes: hay paquetes en la sucursal sin repartidor. Intente de nuevo" << std::endl;
				}
			}
		}
		else {
			std::cout << "El arbol AVL de la sucursal no existe, intente de nuevo." << std::endl;
		}
	}
	catch (std::exception e) {

	}
	
}

void Sistema::generar_reporte() {

	int dia = 0;
	int mes = 0;
	int anio = 0;

	std::string fecha_a_buscar = "";

	try
	{
		std::cout << "Generar reportes: " << std::endl;
		std::cout << "Primer reporte: busqueda por fecha " << std::endl;
		std::cout << "Ingrese el dia del reporte: ";
		std::cin >> dia;
		std::cout << "Ingrese el mes del reporte: ";
		std::cin >> mes;
		std::cout << "Ingrese el anio del reporte: ";
		std::cin >> anio;

		if (dia < 10) {
			fecha_a_buscar = "0" + std::to_string(dia);
		}
		else {
			fecha_a_buscar += std::to_string(dia);
		}

		fecha_a_buscar += "-";

		if (mes < 10) {
			fecha_a_buscar = "0" + std::to_string(mes);
		}
		else {
			fecha_a_buscar += std::to_string(mes);
		}

		fecha_a_buscar += "-";

		if (anio < 1000) {
			fecha_a_buscar = "0" + std::to_string(anio);
		}
		else if (anio < 100) {
			fecha_a_buscar = "00" + std::to_string(anio);
		}
		else if (anio < 10) {
			fecha_a_buscar = "000" + std::to_string(anio);
		}
		else if (anio < 0) {
			fecha_a_buscar = "0000";
		}else{
			fecha_a_buscar += std::to_string(anio);
		}
	}
	catch (const std::exception&)
	{

	}
	
	std::string nombreArchivosReportes = "NombresReportes.txt";
	std::ifstream archivoReportes;
	archivoReportes.open(nombreArchivosReportes,std::ios::in);

	if (archivoReportes.is_open()) {
		std::string linea;
		std::string fecha;

		while (std::getline(archivoReportes,linea)) {
			try {
				std::stringstream stream(linea);
				std::getline(stream, fecha);
				std::string fecha_a_coincidir = "";

				for (int i = 0; i < 10; i++) {
					fecha_a_coincidir += fecha.at(i);
				}

				if (fecha_a_coincidir == fecha_a_buscar) {
					leer_reporte(fecha);
				}

				std::cout << "****************************" << std::endl;
			}
			catch (std::exception exception) {

			}
		}

	}else{
		std::cout << "Error: no se pudo abrir el archivo porque no existe, creando uno nuevo..." << std::endl;
		std::ofstream nuevoArchivoReportes;
		nuevoArchivoReportes.open("NombresReportes.txt");
		nuevoArchivoReportes.close();
		std::cout << "Se genero un nuevo archivo para las fechas de los reportes." << std::endl;
	}

	try {
		if (hay_avl) {


		}
		else {
			std::cout << "No se puede lista los codigos SMT de los paquetes con una entrega myor a 24 horas ni desplegar promedios de tiempo, ya que no existe el arbol AVL de Sucursal." << std::endl;
		}
	}
	catch (std::exception e) {
		std::cout << "Hubo un error de tipo " << e.what() << ", intente de nuevo." << std::endl;
	}

}

void Sistema::leer_reporte(std::string nombre_reporte){
	std::cout << "Reporte " << nombre_reporte << std::endl << std::endl;
	nombre_reporte = nombre_reporte + "_DatosSucursal.txt";
	std::string linea;
	std::ifstream reporte_a_leer(nombre_reporte, std::ios::in);

	while (std::getline(reporte_a_leer, linea)) {

		std::stringstream stream(linea);
		std::string codigo_aduana_string, tipo_envio, numero_de_seguimiento, fecha_recepcion_aduana, dimension_paquete, direccion, precio_base_string,
			peso_paquete_string, telefono_contacto, contenido_fragil_string, codigo_smt, repartidor, tiempo;

		std::cout << "---------------------------------" << std::endl;

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
		std::getline(stream, codigo_smt, ',');
		std::getline(stream, repartidor, ',');
		std::getline(stream, tiempo, ',');

		std::cout << "Codigo de paquete: " << codigo_aduana_string << std::endl;
		std::cout << "Tipo de envio: " << tipo_envio << std::endl;
		std::cout << "Numero de seguimiento: " << numero_de_seguimiento << std::endl;
		std::cout << "Fecha de recepcion: " << fecha_recepcion_aduana << std::endl;
		std::cout << "Valor base del paquete: " << precio_base_string << std::endl;
		std::cout << "Telefono de contacto: " << telefono_contacto << std::endl;
		std::cout << "Peso del paquete: " << peso_paquete_string << std::endl;
		std::cout << "Dimension del paquete: " << dimension_paquete << std::endl;
		std::cout << "¿Es fragil? " << contenido_fragil_string << std::endl;
		std::cout << "Direccion: " << direccion << std::endl;
		std::cout << "Codigo SMT: " << codigo_smt << std::endl;
		std::cout << "Repartidor: " << repartidor << std::endl;
		std::cout << "Tiempo de entrega: " << tiempo << std::endl;
	}

	std::cout << "---------------------------------" << std::endl;
}


void Sistema::debugueo()
{
	std::queue<Paquete*> fila = avl->obtener_todos_paquetes();

	while (!fila.empty()) {
		std::cout << fila.front()->get_codigo_aduana() << std::endl;
		fila.pop();
	}
}