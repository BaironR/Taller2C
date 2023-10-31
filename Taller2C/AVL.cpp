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

    NodoAVL* x = nodo->get_hijo_derecho();
    NodoAVL* y = x->get_hijo_izquierdo();

    x->set_hijo_izquierdo(nodo);
    nodo->set_hijo_derecho(y);

    nodo->set_altura((int)(std::fmax(obtener_altura(nodo->get_hijo_izquierdo()),obtener_altura(nodo->get_hijo_derecho())) + 1));
    x->set_altura((int) (std::fmax(obtener_altura(x->get_hijo_izquierdo()), obtener_altura(x->get_hijo_derecho())) + 1));

    return x;
}

NodoAVL* AVL::rotacion_ll(NodoAVL* nodo){

    NodoAVL* x = nodo->get_hijo_izquierdo();
    NodoAVL* y = x->get_hijo_derecho();

    x->set_hijo_derecho(nodo);
    nodo->set_hijo_izquierdo(y);

    nodo->set_altura((int) (std::fmax(obtener_altura(nodo->get_hijo_izquierdo()), obtener_altura(nodo->get_hijo_derecho())) + 1));
    x->set_altura((int)(std::fmax(obtener_altura(x->get_hijo_izquierdo()), obtener_altura(x->get_hijo_derecho())) + 1));

    return x;
}

NodoAVL* AVL::rotacion_lr(NodoAVL* nodo){

    nodo->set_hijo_izquierdo(rotacion_rr(nodo->get_hijo_izquierdo()));
    return rotacion_ll(nodo);
}

NodoAVL* AVL::rotacion_rl(NodoAVL* nodo){

    nodo->set_hijo_derecho(rotacion_ll(nodo->get_hijo_derecho())); 
    return rotacion_rr(nodo);
}

int AVL::get_altura_recursivo(NodoAVL* nodo, int nivel)
{
    if (nodo == nullptr) {
        return nivel;
    }

    int hl = get_altura_recursivo(nodo->get_hijo_izquierdo(), nivel + 1);
    int hr = get_altura_recursivo(nodo->get_hijo_derecho(), nivel + 1);

    return (int) (std::fmax(hl,hr));
}

void AVL::insertar(Paquete* paquete){

    if (this->raiz == nullptr) {
        this->raiz = new NodoAVL(paquete);
    }
    else {
        this->raiz = insertar_private(this->raiz, paquete);
    }
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

int AVL::obtener_altura(NodoAVL* nodo)
{
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->get_altura();
}

int AVL::factor_de_balance(NodoAVL* nodo)
{
    if (nodo == nullptr) {
        return 0;
    }
    return obtener_altura(nodo->get_hijo_izquierdo()) - obtener_altura(nodo->get_hijo_derecho());
}


NodoAVL* AVL::insertar_private(NodoAVL* nodo, Paquete* paquete) {

    if (nodo == nullptr) {
        return new NodoAVL(paquete);
    }
    else if (paquete->get_codigo_aduana() < nodo->get_paquete()->get_codigo_aduana()) {
        nodo->set_hijo_izquierdo(insertar_private(nodo->get_hijo_izquierdo(), paquete));

        /*
        if (get_altura_recursivo(nodo->get_hijo_izquierdo(), 0) - get_altura_recursivo(nodo->get_hijo_derecho(), 0) == 2) {
            if (paquete->get_codigo_aduana() < nodo->get_hijo_izquierdo()->get_paquete()->get_codigo_aduana()) {
                nodo = rotacion_rr(nodo);

            } else {
                nodo = rotacion_lr(nodo);
            }
        }
        */

    }
    else if (paquete->get_codigo_aduana() > nodo->get_paquete()->get_codigo_aduana()) {

        nodo->set_hijo_derecho(insertar_private(nodo->get_hijo_derecho(), paquete));

        /*
        if (get_altura_recursivo(nodo->get_hijo_derecho(), 0) - get_altura_recursivo(nodo->get_hijo_derecho(), 0) == 2){
            if (paquete->get_codigo_aduana() > nodo->get_hijo_derecho()->get_paquete()->get_codigo_aduana()) {

                nodo = rotacion_ll(nodo);

            } else {
                nodo = rotacion_rl(nodo);
            }
        }
        */

    }
    else {
        return nodo;
    }

    nodo->set_altura(1 + (int) (std::fmax(obtener_altura(nodo->get_hijo_izquierdo()), obtener_altura(nodo->get_hijo_derecho()))));
    int factor_balance = factor_de_balance(nodo);
    
    if (factor_balance < -1 && paquete->get_codigo_aduana() > nodo->get_hijo_derecho()->get_paquete()->get_codigo_aduana()) {
        //RR
        return rotacion_rr(nodo);
    }
    else if (factor_balance > 1 && paquete->get_codigo_aduana() < nodo->get_hijo_izquierdo()->get_paquete()->get_codigo_aduana()) {
        //LL
        return rotacion_ll(nodo);
    }
    else if (factor_balance > 1 && paquete->get_codigo_aduana() > nodo->get_hijo_izquierdo()->get_paquete()->get_codigo_aduana()) {
        //LR
        return rotacion_lr(nodo);
    }
    else if (factor_balance < -1 && paquete->get_codigo_aduana() < nodo->get_hijo_derecho()->get_paquete()->get_codigo_aduana()) {
        //RL
        return rotacion_rl(nodo);
    }
    return nodo;
}

Paquete* AVL::buscar_private(NodoAVL* nodo, int codigo_paquete){
    
    if (!nodo) {
        return nullptr;
    }

    int codigo_actual = nodo->get_paquete()->get_codigo_aduana();

    if (codigo_paquete > codigo_actual) {
        return buscar_private(nodo->get_hijo_derecho(), codigo_paquete);

    }else if (codigo_paquete < codigo_actual) {
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

Paquete* AVL::buscar(int codigo_paquete) {
    int codigo_aduana = codigo_paquete;
    NodoAVL* copia_raiz = this->raiz;
    return buscar_private(copia_raiz, codigo_aduana);
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





