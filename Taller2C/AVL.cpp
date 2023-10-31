#include "AVL.h"


AVL::AVL(){
    this->raiz = nullptr;
}

void AVL::destruirAVLRecurs(NodoAVL* nodo)
{
    if (nodo == nullptr) {
        return;
    }

    destruirAVLRecurs(nodo->get_hijo_izquierdo());
    destruirAVLRecurs(nodo->get_hijo_derecho());
    delete nodo;
}

AVL::~AVL()
{
    destruirAVLRecurs(this->raiz);
}

NodoAVL* AVL::rotacion_rr(NodoAVL* nodo){

    NodoAVL* x = nodo->get_hijo_izquierdo();
    nodo->set_hijo_izquierdo(x->get_hijo_derecho());
    x->set_hijo_izquierdo(nodo);
    return x;
}

NodoAVL* AVL::rotacion_ll(NodoAVL* nodo){

    NodoAVL* x = nodo->get_hijo_derecho();
    nodo->set_hijo_derecho(x->get_hijo_izquierdo());
    x->set_hijo_izquierdo(nodo); 
    return x;
}

NodoAVL* AVL::rotacion_lr(NodoAVL* nodo){

    nodo->set_hijo_izquierdo(rotacion_ll(nodo->get_hijo_izquierdo()));
    return rotacion_rr(nodo);
}

NodoAVL* AVL::rotacion_rl(NodoAVL* nodo){

    nodo->set_hijo_derecho(rotacion_rr(nodo->get_hijo_derecho())); 
    return rotacion_ll(nodo);
}

int AVL::get_altura_recursivo(NodoAVL* nodo, int nivel)
{
    if (nodo == nullptr) {
        return nivel;
    }

    int hl = get_altura_recursivo(nodo->get_hijo_izquierdo(), nivel + 1);
    int hr = get_altura_recursivo(nodo->get_hijo_derecho(), nivel + 1);

    if (hl > hr) {
        return hl;
    }
    return hr;
}

void AVL::insertar(Paquete* paquete){
    this->raiz = insertar_private(this->raiz, paquete);
}

Paquete* AVL::buscar(int codigo_paquete){
    return buscar_private(this->raiz, codigo_paquete);
}

NodoAVL* AVL::get_raiz()
{
    return this->raiz;
}

int* AVL::totalTiempoCantidadTipoEnvio(std::string tipo_envio, int* totalcantidad)
{
    totalTiempoCantidadTipoEnvioPrivate(this->raiz, tipo_envio, totalcantidad);
    return totalcantidad;
}

std::queue<Paquete*> AVL::paquetes_mayor_24_horas()
{
    std::queue<Paquete*> fila_mayor_24Horas;
    buscar_paquetes_mayor_24horas(this->raiz,fila_mayor_24Horas);
    return fila_mayor_24Horas;
}

void AVL::obtener_paquetes_private(NodoAVL* nodo, std::queue <Paquete*>& cola)
{
   if (nodo == nullptr) {
       return;
   }

    cola.push(nodo->get_paquete());
    obtener_paquetes_private(nodo->get_hijo_izquierdo(),cola);
    obtener_paquetes_private(nodo->get_hijo_derecho(),cola);
}

bool AVL::paquetesConRepartidor_private(NodoAVL* nodo)
{
    if (nodo == nullptr) {
        return true;
    }

    if (nodo->get_paquete()->get_repartidor() == "") {
        return false;
    }

    return paquetesConRepartidor_private(nodo->get_hijo_izquierdo()) && 
        paquetesConRepartidor_private(nodo->get_hijo_derecho());
}


std::queue<Paquete*> AVL::obtener_todos_paquetes()
{
    std::queue <Paquete*> cola;
    obtener_paquetes_private(this->raiz, cola);
    return cola;
}

bool AVL::paquetesConRepartidor()
{
    return paquetesConRepartidor_private(this->raiz);
}


NodoAVL* AVL::insertar_private(NodoAVL* nodo, Paquete* paquete){

    if (nodo == nullptr){
        nodo = new NodoAVL(paquete);
    }else if (paquete->get_codigo_aduana() < nodo->get_paquete()->get_codigo_aduana()) {

        nodo->set_hijo_izquierdo(insertar_private(nodo->get_hijo_izquierdo(), paquete)); 

        if (get_altura_recursivo(nodo->get_hijo_izquierdo(), 0) - get_altura_recursivo(nodo->get_hijo_derecho(), 0) == 2){
            if (paquete->get_codigo_aduana() < nodo->get_hijo_izquierdo()->get_paquete()->get_codigo_aduana()) {
                nodo = rotacion_rr(nodo);

            } else { 
                nodo = rotacion_lr(nodo); 
            }        
        }
    }else if (paquete->get_codigo_aduana() > nodo->get_paquete()->get_codigo_aduana())
    {
        nodo->set_hijo_derecho(insertar_private(nodo->get_hijo_derecho(), paquete)) ;
        if (get_altura_recursivo(nodo->get_hijo_derecho(), 0) - get_altura_recursivo(nodo->get_hijo_derecho(), 0) == 2){
            if (paquete->get_codigo_aduana() > nodo->get_hijo_derecho()->get_paquete()->get_codigo_aduana()) {

                nodo = rotacion_ll(nodo);

            } else {
                nodo = rotacion_rl(nodo);
            }
        }
    }
    return nodo;
}

Paquete* AVL::buscar_private(NodoAVL* nodo, int codigo_paquete){
    
    if (!nodo) {
        return nullptr;
    }

    if (codigo_paquete > nodo->get_paquete()->get_codigo_aduana()) {
        return buscar_private(nodo->get_hijo_derecho(), codigo_paquete);

    } else if (codigo_paquete < nodo->get_paquete()->get_codigo_aduana()) {

        return buscar_private(nodo->get_hijo_izquierdo(), codigo_paquete);
    }

    return nodo->get_paquete();
}

void AVL::totalTiempoCantidadTipoEnvioPrivate(NodoAVL* nodo, std::string tipo_envio, int* totalcantidad)
{
    if (nodo == nullptr) {
        return;
    }

    if (nodo->get_paquete()->get_tipo_envio() == tipo_envio) {
        totalcantidad[0] += nodo->get_paquete()->get_tiempo_entrega();
        totalcantidad[1]++;
        return;
    }

    totalTiempoCantidadTipoEnvioPrivate(nodo->get_hijo_izquierdo(), tipo_envio, totalcantidad);
    totalTiempoCantidadTipoEnvioPrivate(nodo->get_hijo_derecho(), tipo_envio, totalcantidad);
}



void AVL::buscar_paquetes_mayor_24horas(NodoAVL* nodo, std::queue<Paquete*>& cola)
{
    if (nodo == nullptr) {
        return;
    }

    if (nodo->get_paquete()->get_tiempo_entrega() > 1600) {
        cola.push(nodo->get_paquete());
    }

    buscar_paquetes_mayor_24horas(nodo->get_hijo_izquierdo(), cola);
    buscar_paquetes_mayor_24horas(nodo->get_hijo_derecho(), cola);
}





