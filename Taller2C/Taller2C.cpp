// Taller2C.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include "Sistema.h"

//Hecho por Bairon Rojas Castro y Benjamín Rivera Portilla.

/*
El main del programa.
Se inicializa el sistema, y se ejecuta el menú principal.
Está con un cláusula try y catch, para evitar los errores.
*/

int main() {
    try {
        Sistema* sistema = new Sistema(); //Inicialización del sistema.
        sistema->menu_principal(); //Iniciar el menu.
    }
    catch (std::exception e) {
        //Captura de excepción grave en el sistema.
        std::cerr << "Excepcion de tipo: " << e.what() << " Hubo un error en el sistema, lo sentimos." << std::endl;
    }
}
