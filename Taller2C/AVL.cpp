#include "AVL.h"


AVL::AVL(){
    this->raiz = nullptr;
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

NodoAVL* AVL::insertar_private(NodoAVL* nodo, Paquete* paquete){

    if (nodo == nullptr){
        nodo = new NodoAVL(paquete);
    }

    else if (paquete->get_codigo_aduana() < nodo->get_paquete()->get_codigo_aduana()) {

        nodo->set_hijo_izquierdo(insertar_private(nodo->get_hijo_izquierdo(), paquete)); 

        if (get_altura_recursivo(nodo->get_hijo_izquierdo(), 0) - get_altura_recursivo(nodo->get_hijo_derecho(), 0) == 2){
            if (paquete->get_codigo_aduana() < nodo->get_hijo_izquierdo()->get_paquete()->get_codigo_aduana()) {
                nodo = rotacion_rr(nodo);

            } else { 
                nodo = rotacion_lr(nodo); 
            }        
        }
    }
    else if (paquete->get_codigo_aduana() > nodo->get_paquete()->get_codigo_aduana())
    {
        nodo->set_hijo_derecho(insertar_private(nodo->get_hijo_derecho(), paquete)) ;
        if (get_altura_recursivo(nodo->get_hijo_derecho(), 0) - get_altura_recursivo(nodo->get_hijo_derecho(), 0) == 2)
        {
            if (paquete->get_codigo_aduana() > nodo->get_hijo_derecho()->get_paquete()->get_codigo_aduana()) {

                nodo = rotacion_ll(nodo);

            } else {
                nodo = rotacion_rl(nodo);
            }
        }
    }

    return nodo;
}



