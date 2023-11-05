#include <string>
#include <iostream>
#include "Sistema.h"
#include "NodoABB.h"
#include "NodoAVL.h"
#include "Paquete.h"
#include <fstream>
#include <sstream>


/*
Constructor de la clase sistema.
Todos los árboles se inicializan en valor nulo.
*/
Sistema::Sistema() {
	abb = nullptr;
	avl = nullptr;
	min_heap = nullptr;
}


/*
Método del menú principal.
Mediante ciclos while, se accede al menú principal y los submenús de aduana y sucursal.
Se utilizan cláusulas try y catch, para evitar la caída del programa al ingresar a un valor no válido.
Al salir del programa, se eliminan los árboles ABB y AVL (se crea un reporte), para liberar memoria.
*/

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

					std::cout << "Programa finalizado, hasta luego." << std::endl;

					//Si hay ABB o AVL, se libera su memoria al finalizar el programa.

					if (hay_abb) {
						delete abb;
						abb = nullptr;
					}

					if (hay_avl) {
						reporte_eliminar_avl(3);
						delete avl;
						avl = nullptr;
					}
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



/*
Método de ingresar envíos.
Si no existe un ABB al ingresar este método, se crea uno nuevo. En caso contrario, se sigue ampliando el ABB 
mientras se lean más archivos. El usuario ingresa por teclado el nombre del archivo a leer (puede ingresar varios), para 
abrirlo con una variable ifstream. Si no existe el archivo (no se abre), se despliega un mensaje de error. 

En caso contrario, mientras haya una línea en el archivo al momento de leerlo, se obtienen los datos de cada línea, con
una variable stringstream. Se definen todos los atributos necesarios de los paquetes en la aduana (a excepción del repartidor,
código SMT y tiempo de entrega), y en cada línea del archivo, se separan todos los valores delimitados por comas, para asignarlo
a cada variable. Se realiza la conversión de tipo string a int, para el código de aduana/paquete, el peso del paquete y el precio base.
También, se eliminan los espacios del campo de contenido frágil, y dependiendo si es frágil o no, se define la variable booleana de
contenido frágil (true/false). Se crea un nuvo paquete, y se inserta en el ABB.

Durante a lectura de archivo, se tiene una variable entera con la sumatoria de los precios base, que aumenta hasta terminar de leer
el archivo. Luego, se utilizan los vectores de nombres de archivo de aduana y la suma de valores de los archivos. Aquí se insertan 
los nombres de los archivos de aduana, para desplegarlos al generar los reportes. El nombre del archivo y la suma se insertan, solo
si el vector de nombres está vacío si no existe en el vector, para evitar repeticiones.

Al terminar, se cierra el archivo.
*/

void Sistema::ingresar_envios() {

	//Si no existe un ABB, se crea y se deja en claro que existe con una variable booleana.
	if (hay_abb == false) {
		abb = new ABB();
		hay_abb = true;
	}
	
	std::string nombreArchivo = "";
	std::cout << std::endl;
	std::cout << "Ingresar envios" << std::endl;
	std::cout << "Ingrese por teclado el nombre del archivo de la aduana a leer (incluyendo su formato, si es .txt por ejemplo.) " << std::endl;
	std::cin >> nombreArchivo;

	// Crear un objeto ifstream para la lectura del archivo, con el nombre ingresado.
	std::ifstream archivo(nombreArchivo);

	// Verificar si el archivo se abrió correctamente
	if (!archivo.is_open()) {
		std::cerr << "No se pudo abrir el archivo, intente de nuevo con otro nombre." << std::endl;
		return;
	}

	// Variable para almacenar los datos leídos
	std::string linea;
	int contador_linea = 1;
	int sumatoria_valores = 0;

	// Almacenar en ABB el contenido del archivo línea por línea
	while (std::getline(archivo, linea)) {
		try{
			std::stringstream stream(linea);
			std::string codigo_aduana_string, tipo_envio, numero_de_seguimiento, fecha_recepcion_aduana, dimension_paquete, direccion, precio_base_string,
				peso_paquete_string, telefono_contacto, contenido_fragil_string;

			//Se leen y se almacenan todos los datos en las variables del paquete, separados por comas.

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

			int codigo_aduana = std::stoi(codigo_aduana_string);
			int precio_base = std::stoi(precio_base_string);
			int peso_paquete = std::stoi(peso_paquete_string);
			bool contenido_fragil;

			// Elimina espacios en blanco al principio
			contenido_fragil_string.erase(0, contenido_fragil_string.find_first_not_of(" "));

			// Elimina espacios en blanco al final
			contenido_fragil_string.erase(contenido_fragil_string.find_last_not_of(" ") + 1);


			//Variable booleana de contenido frágil.
			if (contenido_fragil_string == "Si") {
				contenido_fragil = true;

			}
			else if (contenido_fragil_string == "No") {
				contenido_fragil = false;

			}
			else {
				throw std::invalid_argument("");
			}

			//Se crea un nuevo paquete, y se inserta en el ABB.
			Paquete* paquete = new Paquete(codigo_aduana, tipo_envio, numero_de_seguimiento, fecha_recepcion_aduana,
				precio_base, telefono_contacto, peso_paquete, dimension_paquete, contenido_fragil, direccion,
				"", "", -1);

			abb->insertar(paquete);

			//Se realiza la suma del precio base del paquete a la sumatoria total por el conjunto de datos leído.
			sumatoria_valores += precio_base;
		}
		catch (const std::invalid_argument& e) {
			continue;
		}
	}

	
	//Bloque try y catch.
	try
	{

		//Si el vector con los nombres de archivos está vacío, se insertan directamente el nombre del archivo
		//y el valor total base en el otro vector.
		if (nombres_conjuntos_aduana.empty()) {
			nombres_conjuntos_aduana.push_back(nombreArchivo);
			valor_conjuntos_aduana.push_back(sumatoria_valores);
		}
		else {

			//Si no está vacío, primero se busca si ese archivo ya se leyó.
			bool archivo_encontrado = false;
			for (int i = 0; i < nombres_conjuntos_aduana.size(); i++) {
				if (nombres_conjuntos_aduana.at(i) == nombreArchivo) {
					archivo_encontrado = true;
				}

			}

			//Si no se leyó, se añade el nombre del archivo y la sumatoria total del valor.
			if (!archivo_encontrado) {
				nombres_conjuntos_aduana.push_back(nombreArchivo);
				valor_conjuntos_aduana.push_back(sumatoria_valores);
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Hubo un error de tipo " << e.what() << ", intente de nuevo." << std::endl;
	}

	// Cerrar el archivo después de la lectura
	archivo.close();
	std::cout << "Archivo leido con exito." << std::endl;
}


/*
Método de despacho a sucursal.
Se comprueba primero la existencia de un árbol ABB en la aduana. Si no existe, se despliega un mensaje de error.
En cambio, si existe, primero se comprueba que la raíz no es nula. En el caso de que sea nula, se despliega otro
mensaje de error indicando que el árbol está vacío. Pero si hay elementos en el ABB, se comprueba si existe algún
AVL anterior o no. Si ya existe un AVL anterior, se realiza una búsqueda de cada uno de los paquetes obtenidos
en la fila retornada del ABB, con todos los paquetes del árbol. Si al menos un dato no existe en el AVL, significa
que es un dato nuevo. Se genera un reporte del AVL actual, se elimina y variable booleana de hay_avl cambia a false.
En ambos casos, la inserción al AVL se produce de la misma forma: a partir de la fila retornada del método retornar ABB, 
y se insertan a medida que se va vaciando el AVL. Luego, se elimina el ABB, se vuelve nulo, y la variable de hay_abb se cambia a false.
*/


void Sistema::despacho_sucursal(){

	//Si existe un árbol ABB, entonces se comprueba si está vacía o si hay paquetes en él.
	//Para este último caso, hay que corroborar si ya existe un árbol AVL o no.
	//Si no hay un AVL, se crea directamente. En el caso contrario, hay que corroborar si hay algún dato nuevo.


	//Si hay un ABB...
	if (hay_abb) {

		//Si el ABB está vacío...
		if (abb->retornar_raiz_abb() == nullptr) {
			std::cout << "Error: no hay ningun paquete disponible en la Aduana." << std::endl;
		}
		else {

			//Si ya existe un AVL, hay que comprobar si hay algún dato que se traspasará del ABB al AVL, 
			//que no exista en el AVL actual (un dato nuevo), implicando la eliminación del AVL actual.
			if (hay_avl) {

				//Se retornan todos los paquetes del ABB.
				std::queue<Paquete*> paquetesABB = abb->retornar_ABB();

				while (!paquetesABB.empty()) {
					Paquete* paquete = avl->buscar(paquetesABB.front()->get_codigo_aduana());

					//Si al buscar el paquete en el AVL actual, no existe (el método de buscar retorna nulo),
					//entonces se debe eliminar el AVL, para crear uno nuevo con los datos nuevos.
					if (paquete == nullptr) {

						//Generar reporte, y eliminar AVL.
						reporte_eliminar_avl(2);
						delete avl;
						avl = nullptr;
						hay_avl = false;
						avl = new AVL();
						hay_avl = true;

						std::queue<Paquete*> insertar_nuevo_avl = abb->retornar_ABB();
						while (!insertar_nuevo_avl.empty()) {
							//Mientras la cola de paquetes del ABB no esté vacía, se clonan los paquetes del ABB para insertarlos
							//en el nuevo ABB.
							Paquete* paquete_nuevo = new Paquete(insertar_nuevo_avl.front()->get_codigo_aduana(), insertar_nuevo_avl.front()->get_tipo_envio(),
								insertar_nuevo_avl.front()->get_numero_de_seguimiento(), insertar_nuevo_avl.front()->get_fecha_recepcion_aduana(), insertar_nuevo_avl.front()->get_precio_base(),
								insertar_nuevo_avl.front()->get_telefono_contacto(), insertar_nuevo_avl.front()->get_peso_paquete(), insertar_nuevo_avl.front()->get_dimension_paquete(),
								insertar_nuevo_avl.front()->get_contenido_fragil(), insertar_nuevo_avl.front()->get_direccion(), insertar_nuevo_avl.front()->get_codigo_smt(), insertar_nuevo_avl.front()->get_repartidor(),
								insertar_nuevo_avl.front()->get_tiempo_entrega());
							//Insertar.
							avl->insertar(paquete_nuevo);
							insertar_nuevo_avl.pop();
						}

						//Se rompe el ciclo de búsqueda de paquetes, puesto a que ya se creó uno nuevo.
						break;
					}
					paquetesABB.pop();
				}
			}
			else {

				//Si no existe un AVL, se crea directamente, de la misma manera que después de eliminar el actual
				//(en uas líneas de código más arriba).
				avl = new AVL();
				hay_avl = true;

				std::queue<Paquete*> paquetesABB = abb->retornar_ABB();
				while (!paquetesABB.empty()) {
					Paquete* paquete = new Paquete(paquetesABB.front()->get_codigo_aduana(), paquetesABB.front()->get_tipo_envio(),
						paquetesABB.front()->get_numero_de_seguimiento(), paquetesABB.front()->get_fecha_recepcion_aduana(), paquetesABB.front()->get_precio_base(),
						paquetesABB.front()->get_telefono_contacto(), paquetesABB.front()->get_peso_paquete(), paquetesABB.front()->get_dimension_paquete(),
						paquetesABB.front()->get_contenido_fragil(), paquetesABB.front()->get_direccion(), paquetesABB.front()->get_codigo_smt(), paquetesABB.front()->get_repartidor(),
						paquetesABB.front()->get_tiempo_entrega());
					avl->insertar(paquete);
					paquetesABB.pop();
				}
			}

			//Se elimina el ABB, y se indica que no hay un ABB.
			delete abb;
			abb = nullptr;
			hay_abb = false;
		}
	}else{
		//Mensaje de error.
		std::cout << "El arbol ABB de Aduana no existe, intente de nuevo." << std::endl;
	}
}

//...............  Menu sucursal ...............//

/*
Método de asignar repartidores.
Primero se comprueba si existe un AVL ya en el sistema. Si no, se despliega un mensaje de error. En caso
de que exista pero esté vacío (raíz == null), se despliega otro mensaje de error. Si hay datos presentes
en el AVL, se pide al usuario un nombre de archivo de texto a leer (que contiene la información adicional de
la sucursal). Con el objeto ifstream, usando el nombre del archivo, se abre. Se despliega un mensaje de error si 
no se pudo abrir el archivo (no existe). En caso de que sí se abra, mientras se obtenga una línea no vacía en el 
archivo, se leen los datos, separando las comas (mediante una variable stringstream), y asignando valores a cada
variable para los paquetes (código SMT, el código de paquete, el repartidor y el tiempo de entrega en string).
Se realizan conversiones de string a int para el tiempo de entrega y el código de paquete.
Luego, se busca el paquete con su correspondiente código de paquete en el AVL. Si el paquete retornado existe (no es nulo), 
se asignan sus valores de repartidor, tiempo y código SMT. Todo está encerrado en cláusulas try y catch. Y se cierra
el archivo, finalmente.
*/



void Sistema::asignar_repartidores() {
	std::cout << "Asignar repartidores" << std::endl;

	//Solo se puede asignar repartidores si hay un AVL.
	if (hay_avl) {

		//Si el AVL no está vacío...
		if (avl->get_raiz() != nullptr) {

			std::string nombreArchivo;
			std::cout << "Ingrese el nombre del archivo para leer los datos de la sucursal: ";
			std::cin >> nombreArchivo;

			// Crear un objeto ifstream para la lectura del archivo, con el nombre ingresado.
			std::ifstream archivo(nombreArchivo);

			// Verificar si el archivo se abrió correctamente
			if (!archivo.is_open()) {
				std::cerr << "No se pudo abrir el archivo." << std::endl;
				return;
			}

			// Variable para almacenar los datos leídos
			std::string linea;
			int contador_linea = 1;

			//Cada dato leído corresponde a un paquete en específico (mediante su código de aduana).
			while (std::getline(archivo, linea)) {
				try {
				
				//Variable de tipo stringstream.
				std::stringstream stream(linea);
				std::string codigo_paquete_string, codigo_smt, repartidor, tiempo_entrega_string;


				//Se almacenan los valores del código de paquete que corresponde, con su código SMT, repartidor y tiempo de entrega.
				std::getline(stream, codigo_paquete_string, ',');
				std::getline(stream, codigo_smt, ',');
				std::getline(stream, repartidor, ',');
				std::getline(stream, tiempo_entrega_string, ',');

				int tiempo_entrega = std::stoi(tiempo_entrega_string);
				int codigo_paquete = std::stoi(codigo_paquete_string);

				//Se realiza la búsqueda del paquete con su código, para asignarle su respectivo repartidor y datos adicionales.
				Paquete* paqueteAVL = avl->buscar(codigo_paquete);

				//Si el paquete existe, se usan sus métodos set para asignar los atributos.
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
			std::cout << "Archivo de sucursal leido con exito." << std::endl;
		} else {
			std::cout << "No hay ningun paquete disponible en el arbol AVL, intentelo de nuevo." << std::endl;
		}
	} else {
		std::cout << "No existe ningun arbol AVL para asignar repartidores, intente de nuevo." << std::endl;
	}
}

/*
Método de obtener fecha actual.
Se crea un vector que almacene el nombre del archivo en la casilla 0, y la fecha en la casilla 1.
En el caso de que exista un AVL, se obtiene la hora y día actual local (con la estructura tm hora, la variable
time_t, y localtime_s). Para el día, mes, año, hora, minuto y segundo se realizan conversiones necesarias de int a 
string, para almacenar el nombre del archivo y fecha actual. Se realizan otras conversiones, por ejemplo, si el día
es menor al valor 10, para agregar un 0 atrás, o también con el año (se retorna la cantidad de años desde 1900, y por esto
se suman 1900 al valor del año).

Lo mismo aplica para la hora, minuto, y segundo. Luego, se forma una cadena a partir de concatenar todos los datos en string
del día y la hora, y agregando "_DatosSucursal.txt" para el nombre del reporte.
Se retorna el vector inicializado para almacenar estas cadenas de texto, con los valores modificados.
*/


std::string* Sistema::obtener_fecha_actual()
{
	//Vector de 2 espacios que almacena el nombre del archivo, y la fecha con la hora de creación.
	std::string* nombre_y_fecha = new std::string[2];

	//Solamente si hay un AVL.
	if (hay_avl) {


		//Estructura tm hora, con variable de tipo time_t, para obtener la fecha y hora actuales.
		struct tm hora;
		std::time_t now = std::time(nullptr);
		localtime_s(&hora, &now);

		//Aquí se realizan las conversiones de int a string, considerando si el día o el mes es menor a 10
		//para agregar un 0, o sumar 1900 al año obtenido (el método .tm_year retorna la cantidad de años
		//transcurridos desde el año 1900). Después de cada conversión a string, se concatenan a cada variable 
		//correspondiente a la versión string.

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

		//La misma conversión se realiza

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

		//La fecha del reporte es la concatenación del día, mes, año, hora, minutos, y segundos.
		//El nombre del archivo es la concatenación entre la fecha del reporte y "_DatosSucursal.txt", como se pide en el taller.
		std::string fecha_reporte = dia_string + "-" + mes_string + "-" + anio_string + "_" + hora_string + "-" + min_string + "-" + segun_string;
		std::string nombre_archivo = fecha_reporte + "_DatosSucursal.txt";


		//Se almacenan en sus respectivos espacios en el vector inicializado.
		nombre_y_fecha[0] = nombre_archivo;
		nombre_y_fecha[1] = fecha_reporte;
		return nombre_y_fecha;
	}
	
	nombre_y_fecha[0] = "";
	nombre_y_fecha[1] = "";
	return nombre_y_fecha;
}


//1: Heap
//2: ABB
//3: Eliminar al salir.



/*
Método de crear reporte y eliminar el AVL.
Este método recibe como parámetro una variable entera, que permite diferenciar el uso del método (para
rellenar un heap (1), eliminar un AVL anterior para crear otro nuevo (2), o eliminar al salir de la aplicación (3)).

Primero se obtiene la fecha actual (con el método obtener fecha actual), para crear el nuevo reporte.
Luego, para proceder a la eliminación del AVL, se recuperan todos los paquetes del AVL actual, a partir
de una queue retornada por el método obtener todos los paquetes. Si el archivo se pudo abrir, se realiza un ciclo
mientras la queue retornada no se acabe.

Se crean nuevos paquetes (con nuevas referencias), a partir de los datos del primer paquete de la fila. En el caso
de que se deba insertar el paquete a un heap, se inserta el nuevo paquete dentro del heap. A partir de ciertos
valores, se escriben cadenas de texto para mejorar la lectura de los reportes.
Por ejemplo, en el caso de que se tenga o no se tenga un repartidor asignado al paquete.
Cada uno de los datos se escriben por una línea del archivo, separados por comas. Finalmente, se destruye el paquete
en el frente de la fila, mientras la fila no esté vacía. Finalmente, se cierra el archivo y se despliega un mensaje de feedback.

Luego, en el archivo de los nombres de reportes, se almacena la fecha actual con la hora (también obtenida con el método
obtener fecha actual), para almacenar la nueva fecha en el archivo de nombres de reportes. Si no existe ese archivo, se crea.
*/

void Sistema::reporte_eliminar_avl(int heap_abb_eliminar)
{
	//Se obtiene el vector con el nombre del archivo y la fecha, a partir del método de obtener fecha actual.
	std::string* nombrearchivo_fecha = obtener_fecha_actual();

	//Nuevo archivo de salida, con el nombre del archivo (espacio 0).
	std::ofstream nuevo_reporte;
	std::string nombre_archivo = nombrearchivo_fecha[0];

	//Se abre el archivo, y se obtiene la cola con todos los paquetes del AVL a eliminar.
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

			std::string hay_repartidor = paquete->get_repartidor();
			std::string hay_codigo_smt = paquete->get_codigo_smt();

			if (hay_repartidor == "") {
				hay_repartidor = "No tiene repartidor";
			}

			if (hay_codigo_smt == "") {
				hay_codigo_smt = "No tiene codigo SMT";
			}

			nuevo_reporte << paquete->get_codigo_aduana() << "," << paquete->get_tipo_envio() << "," << paquete->get_numero_de_seguimiento() << "," << paquete->get_fecha_recepcion_aduana() << "," << paquete->get_precio_base() << "," <<
				paquete->get_telefono_contacto() << "," << paquete->get_peso_paquete() << "," << paquete->get_dimension_paquete() << "," << fragil << "," << paquete->get_direccion() << "," << hay_codigo_smt << "," <<
				hay_repartidor << "," << paquete->get_tiempo_entrega();
			nuevo_reporte << std::endl;
			
			if (heap_abb_eliminar == 1) {
				min_heap->insertar_paquete(paquete);
			}

			fila_paquetes.pop();
		}
		nuevo_reporte.close();
		std::cout << "Reporte generado con exito." << std::endl;
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

/*
Método de realizar entregas.
El traspaso de todos los paquetes al heap, para su consiguiente reporte y eliminación.
Primero se comprueba si hay un AVL activo, y a su vez, si no está vacía. En este último caso, se comprueba
si todos los paquetes en el AVL poseen un repartidor. Si al menos uno no posee repartidor, no se puede proceder
a la entrega de paquetes. En el caso contrario, se realiza la entrega de paquetes.

Se inicializa el heap, a partir de la cantdad de nodos que hay en el AVL actual, se genera el reporte antes de eliminar
el AVL (llamando al método de reportes, con el código 1 para insertar en el heap).
El heap retornará el paquete que se encuentre en su primer espacio (el espacio raíz, con menor tiempo de envío), y a su vez, 
el heap elimina el nodo presente en la raíz, mientras la cantdad actual de datos en el heap sea mayor a 0.

Finalmente, se elimina el heap, y se designa en null.
*/

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

					int cantidad_nodos_avl = avl->cantidad_nodos();
					min_heap = new Heap(cantidad_nodos_avl);
					reporte_eliminar_avl(1);
					delete avl;
					hay_avl = false;

					std::cout << "Se realizara la entrega de los paquetes." << std::endl;
					std::cout << "Realizando entregas..." << std::endl;
					std::cout << std::endl;
					
				

					while (min_heap->get_cantidad_actual() > 0) {
						Paquete* paquete = min_heap->extraer_paquete();
						std::cout << "Paquete con codigo de aduana " << paquete->get_codigo_aduana() << ", por el repartidor " << paquete->get_repartidor() << ", tiempo de entrega de " << paquete->get_tiempo_entrega() << " minutos." << std::endl;
					}

					delete min_heap;
					min_heap = nullptr;
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
	catch (const std::exception& e) {
		std::cout << "Hubo un error de tipo " << e.what() << ", intente de nuevo." << std::endl;
	}
	
}

/*
Método para generar reportes.
Primeramente, el usuario ingresa una fecha para buscar y desplegar todos los reportes de esa fecha en específico.
Se realizan los ajustes respectivos para el día y mes (si es menor a 10), y el año. Se poseen cláusulas de tipo try
y catch, para capturar errores. Todas estas cadenas se concatenan en una sola, como la "fecha a buscar".

Luego de esto, a partir de la cadena formada de la fecha, se busca esa fecha en el archivo de nombres de reportes.
Si el archivo existe y se abrió correctamente, por cada línea se lee la fecha que está presente ahí.
Mediante un ciclo for, se crea una cadena de texto nueva para hacer coincidir únicamente la fecha de creación (un total
de 10 caracteres, asumiendo un año superior a 999, considerando los guiones entre día, mes y año).

Si la "fecha a coincidir", coincide con la cadena de "fecha a buscar" (es decir, existe el registro de un archivo con
esa fecha), se abre el archivo con ese nombre completo (fecha y hora, con el método leer_reporte), y así hasta acabar
el archivo de nombres de reportes. Si no existe, se crea uno nuevo con el nombre "NombresReportes.txt".


Para el valor total de cada conjunto de datos en todos los archivos de Aduana, se usa el vector dinámico de nombres de archivos
de Aduana, junto con el otro vector que almacena los valores enteros del total. Si el vector de nombres está vacío, se despliega
que no se ha leído ningún archivo de aduana hasta el momento. En caso contrario, se despliegan todos los nombres de los archivos
de Aduana con su respectivo valor base total.

Ahora, se despliegan 2 estadísticas, que requieren de tener un AVL de Sucursal activo. En el caso de que no haya un AVL activo, se despliega
un mensaje de error. Si hay un AVL pero está vacío, también. En el caso contrario (hay un AVL con datos), se obtiene una queue con todos los
paquetes cuyo tiempo de entrega sea mayor a 1440 minutos (equivalente a 24 horas, 1 día), desplegando los códigos SMT, y se realiza el conteo de la cantidad de paquetes con
un tipo de envío específico (Económico, Gratis y Express) con su suma total de tiempo de envío, para desplegar por pantalla su promedio de tiempo.
Al desplegar el promedio, si hay paquetes (cantidad mayor a 0), pero el promedio resulta 0, es porque no hay tiempo definido para ningún paquete
de ese tipo (los tiempos de envío están en -1). También se considera si no hay paquetes con un tipo de envío, o si no hay paquetes con un tiempo
den entrega mayor a 24 horas.
*/

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
	catch (const std::exception& e)
	{
		std::cout << "Hubo un error de tipo " << e.what() << ", intente de nuevo." << std::endl;
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
					std::cout << "****************************" << std::endl;
				}
			}
			catch (const std::exception& exception) {
				std::cout << "Hubo un error de tipo " << exception.what() << ", intente de nuevo." << std::endl;
			}
		}
	}else{
		std::cout << "Error: no se pudo abrir el archivo porque no existe, creando uno nuevo..." << std::endl;
		std::ofstream nuevoArchivoReportes;
		nuevoArchivoReportes.open("NombresReportes.txt");
		nuevoArchivoReportes.close();
		std::cout << "Se genero un nuevo archivo para las fechas de los reportes." << std::endl;
	}

	try
	{
		if (nombres_conjuntos_aduana.empty()) {
			std::cout << "No se ha leido ningun archivo con conjuntos de datos para la Aduana." << std::endl;
		}
		else {
			for (int i = 0; i < nombres_conjuntos_aduana.size(); i++) {
				std::cout << "Valor total para el conjunto de datos del archivo " << nombres_conjuntos_aduana[i] << ": $" << valor_conjuntos_aduana[i] << std::endl;
			}
			std::cout << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Ocurrio un error de tipo: " << e.what() << ". Intente de nuevo." << std::endl;
		std::cout << std::endl;
	}

	try {
		if (hay_avl) {
			if (avl->get_raiz() != nullptr) {

				std::cout << "Codigo SMT de paquetes con tiempo de entrega mayor a 24 horas (1440 minutos): " << std::endl;
				std::queue <Paquete*> fila_smt_24horas = avl->paquetes_mayor_24_horas();

				if (fila_smt_24horas.size() == 0) {
					std::cout << "No hay paquetes con un tiempo de entrega mayor a 24 horas." << std::endl;
				}
				else {
					while (!fila_smt_24horas.empty()) {
						Paquete* paquete = fila_smt_24horas.front();
						std::cout << "Paquete con el codigo SMT " << paquete->get_codigo_smt() << ", con un tiempo de entrega de " << paquete->get_tiempo_entrega() << " minutos." << std::endl;
						fila_smt_24horas.pop();
					}
				}

				std::cout << std::endl;

				int cantidad_express = avl->cantidad_paquetes_tipo_envio("Express");
				int suma_tiempo_express = avl->suma_paquetes_tiempo_envio("Express");

				int cantidad_economico = avl->cantidad_paquetes_tipo_envio("Economico");
				int suma_tiempo_economico = avl->suma_paquetes_tiempo_envio("Economico");

				int cantidad_gratis = avl->cantidad_paquetes_tipo_envio("Gratis");
				int suma_tiempo_gratis = avl->suma_paquetes_tiempo_envio("Gratis");
				

				if (cantidad_express == 0) {
					std::cout << "No hay ningun paquete con tipo de envio Express en la sucursal. " << std::endl;
				}
				else {
					double promedio_express = ((suma_tiempo_express * 1.0)/ cantidad_express);
					if (promedio_express == 0.0) {
						std::cout << "Ningun paquete con tipo de envio Express tiene un tiempo de entrega definido." << std::endl;
					}
					else {
						std::cout << "Hay un promedio de tiempo de entrega de " + std::to_string(promedio_express) + " minutos para un paquete con envio Express." << std::endl;
					}
				}

				if (cantidad_economico == 0) {
					std::cout << "No hay ningun paquete con tipo de envio Economico en la sucursal. " << std::endl;
				}
				else {
					double promedio_economico = ((suma_tiempo_economico * 1.0) / cantidad_economico);

					if (promedio_economico == 0.0) {
						std::cout << "Ningun paquete con tipo de envio Economico tiene un tiempo de entrega definido." << std::endl;
					}
					else {
						std::cout << "Hay un promedio de tiempo de entrega de " + std::to_string(promedio_economico) + " minutos para un paquete con envio Economico." << std::endl;
					}
				}

				if (cantidad_gratis == 0) {
					std::cout << "No hay ningun paquete con tipo de envio Gratis en la sucursal. " << std::endl;
				}
				else {
					double promedio_gratis = ((suma_tiempo_gratis * 1.0) / cantidad_gratis);
					if (promedio_gratis == 0.0) {
						std::cout << "Ningun paquete con tipo de envio Gratis tiene un tiempo de entrega definido." << std::endl;
					}
					else {
						std::cout << "Hay un promedio de tiempo de entrega de " + std::to_string(promedio_gratis) + " minutos para un paquete con envio Gratis." << std::endl;
					}
				}
			}
			else {
				std::cout << "El arbol AVL de la Sucursal esta vacio, por favor intente de nuevo." << std::endl;
			}
		}
		else {
			std::cout << "No se puede lista los codigos SMT de los paquetes con una entrega mayor a 24 horas ni desplegar promedios de tiempo, ya que no existe el arbol AVL de Sucursal." << std::endl;
		}
	}
	catch (std::exception e) {
		std::cout << "Hubo un error de tipo " << e.what() << ", intente de nuevo." << std::endl;
	}

}


/*
Método de leer reporte.
Este método recibe por parámetro el nombre del reporte a leer.
Se agrega la cadena "_DatosSucursal.txt", para abrir el archivo con la variable ifstream.
Cuando se abra el archivo, mediante la variable de tipo stringstream se reciben todos los datos de cada paquete, 
separando mediante comas. Si hay un tiempo de valor -1, es porque no se definió un tiempo de entrega.
Todos los datos de cada paquete se despliegan por pantalla.
*/

void Sistema::leer_reporte(std::string nombre_reporte){
	try
	{
		std::cout << "Reporte " << nombre_reporte << std::endl << std::endl;
		nombre_reporte = nombre_reporte + "_DatosSucursal.txt";

		//Se abre el archivo con el nombre del reporte (incluyendo la partícula "_DatosSucursal.txt").

		std::string linea;
		std::ifstream reporte_a_leer(nombre_reporte, std::ios::in);

		while (std::getline(reporte_a_leer, linea)) {

			//Se lee el archivo del reporte, desplegando todos los datos del paquete por línea.

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
			std::cout << "Valor base del paquete: $" << precio_base_string << std::endl;
			std::cout << "Telefono de contacto: " << telefono_contacto << std::endl;
			std::cout << "Peso del paquete: " << peso_paquete_string << std::endl;
			std::cout << "Dimension del paquete: " << dimension_paquete << std::endl;
			std::cout << "¿Es fragil? " << contenido_fragil_string << std::endl;
			std::cout << "Direccion: " << direccion << std::endl;
			std::cout << "Codigo SMT: " << codigo_smt << std::endl;
			std::cout << "Repartidor: " << repartidor << std::endl;
			
			if (tiempo == "-1") {
				std::cout << "No hay tiempo de entrega definido." << std::endl;
			}
			else {
				std::cout << "Tiempo de entrega: " << tiempo << " minutos" << std::endl;
			}
		}
		std::cout << "---------------------------------" << std::endl;
	}catch (const std::exception& e)
	{
		std::cout << "Hubo un error de tipo " << e.what() << ", intente de nuevo." << std::endl;
	}
}