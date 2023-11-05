#include "AVL.h"

/*
Constructor del AVL.
Se inicializa el nodo raíz como nulo.
*/

AVL::AVL(){
    this->raiz = nullptr;
}

/*
Eliminar nodos.
Recursivamente, en postorden, se eliminan cada uno de los nodos del árbol, si el nodo actual no es nulo.
La raíz es el último nodo en eliminarse, del AVL.
*/

void AVL::destruirAVLRecurs(NodoAVL* nodo)
{
    if (nodo == nullptr) {
        return;
    }

    destruirAVLRecurs(nodo->get_hijo_izquierdo());
    destruirAVLRecurs(nodo->get_hijo_derecho());
    delete nodo;
}

/*
Cantidad de nodos, privado.
Recursivamente, se recorre todo el AVL para realizar el conteo de nodos en el árbol.
Si el nodo es nulo, se suma 0.
*/


int AVL::cantidad_nodos_private(NodoAVL* nodo)
{
    if (nodo == nullptr) {
        return 0;
    }

    return 1 + cantidad_nodos_private(nodo->get_hijo_izquierdo()) + cantidad_nodos_private(nodo->get_hijo_derecho());
}

/*
Suma de tiempo de envío (privado).
Como parámetro, se recibe el nodo actual y el tipo de envío específico.
Si el nodo es nulo, se retorna 0. En cambio, si el paquete del nodo actual corresponde con el tipo
de envío indicado, la variable de tiempo se obtiene del paquete. En caso de que el tiempo sea -1, 
es porque aún no está definido su tiempo de entrega. 
Recursivamente realiza la suma por todo el AVL, para retornar el total.
*/

int AVL::suma_tiempo_envio_private(NodoAVL* nodoAVL, std::string tipo_envio)
{
    int tiempo = 0;

    if (nodoAVL == nullptr) {
        return tiempo;
    }
    
    if (nodoAVL->get_paquete()->get_tipo_envio() == tipo_envio) {
        tiempo = nodoAVL->get_paquete()->get_tiempo_entrega();

        if (tiempo == -1) {
            tiempo = 0;
        }
    }

    return tiempo + suma_tiempo_envio_private(nodoAVL->get_hijo_izquierdo(), tipo_envio) +
        suma_tiempo_envio_private(nodoAVL->get_hijo_derecho(), tipo_envio);
}

/*
Cantidad de paquetes con un tipo de envio, privado.
Se realiza el conteo de paquetes con el tipo de envío especificado.
Si el nodo es nulo, se retorna 0. Si el paquete del nodo corresponde con el tipo de envío,
el contador aumenta a 1. Recursivamente se recorre el árbol para retornar la suma total de paquetes
con el tipo de envío.
*/

int AVL::cantidad_tipo_envio_private(NodoAVL* nodoAVL, std::string tipo_envio)
{
    int contador = 0;

    if (nodoAVL == nullptr) {
        return contador;
    }
    
    if (nodoAVL->get_paquete()->get_tipo_envio() == tipo_envio) {
        contador++;
    }

    return contador + cantidad_tipo_envio_private(nodoAVL->get_hijo_izquierdo(),tipo_envio) + 
        cantidad_tipo_envio_private(nodoAVL->get_hijo_derecho(), tipo_envio);
}

/*
Destructor del AVL.
Se ejecuta el método de eliminar nodos recursivamente, tomando como base el nodo raíz.
*/

AVL::~AVL()
{
    destruirAVLRecurs(this->raiz);
}

/*
Rotación RR, con un nodo.
Rotación RR del nodo con desbalance, tras insertar (arcos derecho-derecho).
Se tienen 3 nodos en esta rotación. El nodo del desbalance (nodo), su hijo derecho (x), y el hijo
izquierdo de x (y). X pasa a ser el padre de "nodo" (hijo izquierdo), e y pasa a ser el hijo derecho de nodo.
Luego se recalcula la altura de nodo y x, con el método de obtener altura, y el máximo entre sus hijos izquierda y la derecha.
*/

NodoAVL* AVL::rotacion_rr(NodoAVL* nodo){

    NodoAVL* x = nodo->get_hijo_derecho();
    NodoAVL* y = x->get_hijo_izquierdo();

    x->set_hijo_izquierdo(nodo);
    nodo->set_hijo_derecho(y);

    nodo->set_altura((int)(std::fmax(obtener_altura(nodo->get_hijo_izquierdo()),obtener_altura(nodo->get_hijo_derecho())) + 1));
    x->set_altura((int) (std::fmax(obtener_altura(x->get_hijo_izquierdo()), obtener_altura(x->get_hijo_derecho())) + 1));

    return x;
}

/*
Rotación LL, con un nodo.
Rotación LL del nodo con desbalance, tras insertar (arcos izquierdo-izquierdo).
Se tienen 3 nodos en esta rotación. El nodo del desbalance (nodo), su hijo izquierdo (x), y el hijo
derecho de x (y). X pasa a ser el padre de "nodo" (hijo derecho), e y pasa a ser el hijo izquierdo de nodo.
Luego se recalcula la altura de nodo y x, con el método de obtener altura, y el máximo entre sus hijos izquierda y la derecha.
*/

NodoAVL* AVL::rotacion_ll(NodoAVL* nodo){

    NodoAVL* x = nodo->get_hijo_izquierdo();
    NodoAVL* y = x->get_hijo_derecho();

    x->set_hijo_derecho(nodo);
    nodo->set_hijo_izquierdo(y);

    nodo->set_altura((int) (std::fmax(obtener_altura(nodo->get_hijo_izquierdo()), obtener_altura(nodo->get_hijo_derecho())) + 1));
    x->set_altura((int)(std::fmax(obtener_altura(x->get_hijo_izquierdo()), obtener_altura(x->get_hijo_derecho())) + 1));

    return x;
}

/*
Rotación LR, a un nodo.
Rotación LR del nodo con desbalance, tras insertar (arcos izquierdo y derecho).
Primeramente, se realiza una rotación RR al hijo izquierdo del nodo de desbalance.
El nodo padre de esta rotación se retorna del método de rotación RR, para ser el hijo izquierdo
del nodo de desbalance. Luego, se aplica un rotación LL al nodo de desbalance, y se retorna el
nodo padre resultante.
*/


NodoAVL* AVL::rotacion_lr(NodoAVL* nodo){

    nodo->set_hijo_izquierdo(rotacion_rr(nodo->get_hijo_izquierdo()));
    return rotacion_ll(nodo);
}

/*
Rotación RL, a un nodo.
Rotación RL del nodo con desbalance, tras insertar (arcos derecho e izquierdo).
Primeramente, se realiza una rotación LL al hijo derecho del nodo de desbalance.
El nodo padre de esta rotación se retorna del método de rotación LL, para ser el hijo derecho
del nodo de desbalance. Luego, se aplica un rotación RR al nodo de desbalance, y se retorna el
nodo padre resultante.
*/

NodoAVL* AVL::rotacion_rl(NodoAVL* nodo){

    nodo->set_hijo_derecho(rotacion_ll(nodo->get_hijo_derecho())); 
    return rotacion_rr(nodo);
}

/*
Método de insertar (público).
Se recibe un paquete por parámetro.
Si la raíz es nula, se inicializa un nuevo nodo con el paquete insertado.
Si no, se ejecuta el método de insertar privado, actualizando el árbol.
*/


void AVL::insertar(Paquete* paquete){

    if (this->raiz == nullptr) {
        this->raiz = new NodoAVL(paquete);
    }
    else {
        this->raiz = insertar_private(this->raiz, paquete);
    }
}

/*
Obtener raíz: se retorna el nodo raíz.
*/
NodoAVL* AVL::get_raiz()
{
    return this->raiz;
}


/*
Paquetes mayor a 24 horas (público).
Se retorna una cola creada, que es modificada por referencia en el método privado de retornar todos los
paquetes del AVL, con un tiempo de entrega mayor a 1440 (minutos).
*/
std::queue<Paquete*> AVL::paquetes_mayor_24_horas()
{
    std::queue<Paquete*> fila_mayor_24Horas;
    buscar_paquetes_mayor_24horas(this->raiz,fila_mayor_24Horas);
    return fila_mayor_24Horas;
}

/*
Obtener paquetes (privado).
Se tiene como parámetros el nodo actual, y la referencia de la fila con los paquetes.
Se comprueba en preorden, todos los nodos del árbol, directamente insertando los paquetes en la fila y
recorriendo recursivamente el árbol, primeramente hacia la izquierda, y muy después, a la derecha (preorden).
Si el nodo es nulo, se retorna.
*/

void AVL::obtener_paquetes_private(NodoAVL* nodo, std::queue <Paquete*>& cola)
{
   if (nodo == nullptr) {
       return;
   }

    cola.push(nodo->get_paquete());
    obtener_paquetes_private(nodo->get_hijo_izquierdo(),cola);
    obtener_paquetes_private(nodo->get_hijo_derecho(),cola);
}

/*
Paquetes con repartidor, privado.
Recursivamente, se recorre todo el árbol para asegurar que todos los paquetes tienen repartidor.
Si el nodo es nulo, se retorna true.
Si el campo de repartidor del paquete es una cadena vacía (""), se retorna false porque no tiene repartidor.
Se retorna la variable booleana, llamando al método con el hijo izquierdo y derecho.
*/

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

/*
Obtener todos los paquetes del AVL (público).
Se retorna una cola creada, que es modificada por referencia en el método privado de retornar todos los
paquetes del AVL.
*/

std::queue<Paquete*> AVL::obtener_todos_paquetes()
{
    std::queue <Paquete*> cola;
    obtener_paquetes_private(this->raiz, cola);
    return cola;
}

/*
Paquetes con repartidor, público.
Se retorna el valor booleano retornado a su vez, por su versión privada del método.
*/

bool AVL::paquetesConRepartidor()
{
    return paquetesConRepartidor_private(this->raiz);
}

/*
Obtener altura.
Se retorna directamente la altura del nodo, 0 si este es nulo.
*/

int AVL::obtener_altura(NodoAVL* nodo)
{
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->get_altura();
}

/*
Factor de balance.
Se retorna la resta entre las alturas del hijo izquierdo y derecho, para el factor de balance.
0, si el nodo es nulo.
*/

int AVL::factor_de_balance(NodoAVL* nodo)
{
    if (nodo == nullptr) {
        return 0;
    }
    return obtener_altura(nodo->get_hijo_izquierdo()) - obtener_altura(nodo->get_hijo_derecho());
}


/*
Cantidad de nodos, público.
Se ejecuta el método privado, y se retorna su valor.
*/

int AVL::cantidad_nodos()
{
    return cantidad_nodos_private(this->raiz);
}

/*
Suma de tiempo de paquetes con tipo de envio (público).
Se ejecuta el método privado, y se retorna su valor.
*/

int AVL::suma_paquetes_tiempo_envio(std::string tipo_envio)
{
    return suma_tiempo_envio_private(this->raiz, tipo_envio);
}

/*
Cantidad de paquetes con un tipo de envío (público).
Se ejecuta el método privado, y se retorna su valor.
*/

int AVL::cantidad_paquetes_tipo_envio(std::string tipo_envio)
{
    return cantidad_tipo_envio_private(this->raiz, tipo_envio);
}

/*
Insertar (privado).
Primeramente se realiza una inserción normal como en el ABB, pero esta vez, recursivamente.
Si el nodo es nulo (se llega al espacio a insertar), se inicializa el nodo nuevo con el paquete.
Se compara si el código de paquete es menor o mayor al del nodo actual (para ir a la izquierda o derecha,
y designar si es el hijo izquierdo o derecho), y si ya existe, se retorna el nodo directamente porque no se aceptan paquetes repetidos.
Cuando ya se agregue el nodo, el proceso del método actual se detiene y regresa a la anterior, reflejando recursividad.

Luego de insertar, se actualiza la altura del nodo actual (obteniendo el máximo entre la altura del hijo izquierdo y derecho más 1),
y se calcula su factor de balance (resta de la altura del hijo izquierdo y derecho).

En caso de que el factor de balance esté entre -1, 0 o 1, no hay problema, no hay necesidad de realizar rotaciones.
Existen 4 casos diferentes para realizar la rotación.

1) El factor de balance es menor a -1 (hacia la derecha), y el código del paquete a insertar es mayor que el del hijo derecho del 
nodo desbalanceado (Rotación RR, arcos derecho - derecho).

2) El factor de balance es mayor a 1 (hacia la izquierda), y el código del paquete a insertar es menor que el del hijo izquierdo del 
nodo desbalanceado (Rotación LL, arcos izquierdo - izquierdo).

3) El factor de balance es mayor a 1 (hacia la izquierda), y el código del paquete a insertar es mayor que el del hijo izquierdo del 
nodo desbalanceado (Rotación LR, arcos izquierdo - derecho).

4) El factor de balance es menor a -1 (hacia la derecha), y el código del paquete a insertar es menor que el del hijo derecho del 
nodo desbalanceado (Rotación RL, arcos derecho - izquierdo).

Finalmente, se retorna el nodo actual, los cambios realizados para las inserciones y rotaciones no afectan a los nodos que no están involucrados.
*/

NodoAVL* AVL::insertar_private(NodoAVL* nodo, Paquete* paquete) {

    if (nodo == nullptr) {
        return new NodoAVL(paquete);
    }
    else if (paquete->get_codigo_aduana() < nodo->get_paquete()->get_codigo_aduana()) {
        nodo->set_hijo_izquierdo(insertar_private(nodo->get_hijo_izquierdo(), paquete));
    }
    else if (paquete->get_codigo_aduana() > nodo->get_paquete()->get_codigo_aduana()) {

        nodo->set_hijo_derecho(insertar_private(nodo->get_hijo_derecho(), paquete));
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

/*
Buscar paquete (privado).
Si el nodo es nulo, se retorna un paquete nulo (no existe en el árbol).
Recursivamente, se comparan los valores del nodo actual con el codigo del paquete a encontrar.
El AVL ya está ordenado como el ABB: el hijo izquierdo posee un menor codigo de paquete que el padre,
y el derecho un código mayor que el padre. Así, se llama de manera recursiva el método, hasta encontrar
el paquete requerido. Si no se encuentra, se retorna null.
*/

Paquete* AVL::buscar_private(NodoAVL* nodo, int codigo_paquete){
    
    if (!nodo) {
        return nullptr;
    }

    if (codigo_paquete > nodo->get_paquete()->get_codigo_aduana()) {
        return buscar_private(nodo->get_hijo_derecho(), codigo_paquete);

    }else if (codigo_paquete < nodo->get_paquete()->get_codigo_aduana()) {
        return buscar_private(nodo->get_hijo_izquierdo(), codigo_paquete);
     }

    return nodo->get_paquete();
}


/*
Buscar paquete (público).
Se ejecuta el método privado de buscar un paquete, con el nodo raíz y el código de paquete.
*/

Paquete* AVL::buscar(int codigo_paquete) {
    NodoAVL* copia_raiz = this->raiz;
    return buscar_private(copia_raiz, codigo_paquete);
}

/*
Buscar paquetes con tiempo mayor a 24 horas (privado).
Se recorre recursivamente en preorden, si el paquete en un nodo tiene un tiempo de entrega mayor a 1440 minutos.
Si es así, se inserta en la cola de paquetes, que es pasado por referencia. Si el nodo es nulo, se retorna.
*/

void AVL::buscar_paquetes_mayor_24horas(NodoAVL* nodo, std::queue<Paquete*>& cola)
{
    if (nodo == nullptr) {
        return;
    }

    if (nodo->get_paquete()->get_tiempo_entrega() > 1440) {
        cola.push(nodo->get_paquete());
    }

    buscar_paquetes_mayor_24horas(nodo->get_hijo_izquierdo(), cola);
    buscar_paquetes_mayor_24horas(nodo->get_hijo_derecho(), cola);
}





