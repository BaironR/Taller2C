// Taller2C.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Sistema.h"

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
