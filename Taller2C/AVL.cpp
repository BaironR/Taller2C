#include "AVL.h"

/*
Constructor del AVL.
Se inicializa el nodo ra�z como nulo.
*/

AVL::AVL(){
    this->raiz = nullptr;
}

/*
Eliminar nodos.
Recursivamente, en postorden, se eliminan cada uno de los nodos del �rbol, si el nodo actual no es nulo.
La ra�z es el �ltimo nodo en eliminarse, del AVL.
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
Recursivamente, se recorre todo el AVL para realizar el conteo de nodos en el �rbol.
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
Suma de tiempo de env�o (privado).
Como par�metro, se recibe el nodo actual y el tipo de env�o espec�fico.
Si el nodo es nulo, se retorna 0. En cambio, si el paquete del nodo actual corresponde con el tipo
de env�o indicado, la variable de tiempo se obtiene del paquete. En caso de que el tiempo sea -1, 
es porque a�n no est� definido su tiempo de entrega. 
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
Se realiza el conteo de paquetes con el tipo de env�o especificado.
Si el nodo es nulo, se retorna 0. Si el paquete del nodo corresponde con el tipo de env�o,
el contador aumenta a 1. Recursivamente se recorre el �rbol para retornar la suma total de paquetes
con el tipo de env�o.
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
Se ejecuta el m�todo de eliminar nodos recursivamente, tomando como base el nodo ra�z.
*/

AVL::~AVL()
{
    destruirAVLRecurs(this->raiz);
}

/*
Rotaci�n RR, con un nodo.
Rotaci�n RR del nodo con desbalance, tras insertar (arcos derecho-derecho).
Se tienen 3 nodos en esta rotaci�n. El nodo del desbalance (nodo), su hijo derecho (x), y el hijo
izquierdo de x (y). X pasa a ser el padre de "nodo" (hijo izquierdo), e y pasa a ser el hijo derecho de nodo.
Luego se recalcula la altura de nodo y x, con el m�todo de obtener altura, y el m�ximo entre sus hijos izquierda y la derecha.
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
Rotaci�n LL, con un nodo.
Rotaci�n LL del nodo con desbalance, tras insertar (arcos izquierdo-izquierdo).
Se tienen 3 nodos en esta rotaci�n. El nodo del desbalance (nodo), su hijo izquierdo (x), y el hijo
derecho de x (y). X pasa a ser el padre de "nodo" (hijo derecho), e y pasa a ser el hijo izquierdo de nodo.
Luego se recalcula la altura de nodo y x, con el m�todo de obtener altura, y el m�ximo entre sus hijos izquierda y la derecha.
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
Rotaci�n LR, a un nodo.
Rotaci�n LR del nodo con desbalance, tras insertar (arcos izquierdo y derecho).
Primeramente, se realiza una rotaci�n RR al hijo izquierdo del nodo de desbalance.
El nodo padre de esta rotaci�n se retorna del m�todo de rotaci�n RR, para ser el hijo izquierdo
del nodo de desbalance. Luego, se aplica un rotaci�n LL al nodo de desbalance, y se retorna el
nodo padre resultante.
*/


NodoAVL* AVL::rotacion_lr(NodoAVL* nodo){

    nodo->set_hijo_izquierdo(rotacion_rr(nodo->get_hijo_izquierdo()));
    return rotacion_ll(nodo);
}

/*
Rotaci�n RL, a un nodo.
Rotaci�n RL del nodo con desbalance, tras insertar (arcos derecho e izquierdo).
Primeramente, se realiza una rotaci�n LL al hijo derecho del nodo de desbalance.
El nodo padre de esta rotaci�n se retorna del m�todo de rotaci�n LL, para ser el hijo derecho
del nodo de desbalance. Luego, se aplica un rotaci�n RR al nodo de desbalance, y se retorna el
nodo padre resultante.
*/

NodoAVL* AVL::rotacion_rl(NodoAVL* nodo){

    nodo->set_hijo_derecho(rotacion_ll(nodo->get_hijo_derecho())); 
    return rotacion_rr(nodo);
}

/*
M�todo de insertar (p�blico).
Se recibe un paquete por par�metro.
Si la ra�z es nula, se inicializa un nuevo nodo con el paquete insertado.
Si no, se ejecuta el m�todo de insertar privado, actualizando el �rbol.
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
Obtener ra�z: se retorna el nodo ra�z.
*/
NodoAVL* AVL::get_raiz()
{
    return this->raiz;
}


/*
Paquetes mayor a 24 horas (p�blico).
Se retorna una cola creada, que es modificada por referencia en el m�todo privado de retornar todos los
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
Se tiene como par�metros el nodo actual, y la referencia de la fila con los paquetes.
Se comprueba en preorden, todos los nodos del �rbol, directamente insertando los paquetes en la fila y
recorriendo recursivamente el �rbol, primeramente hacia la izquierda, y muy despu�s, a la derecha (preorden).
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
Recursivamente, se recorre todo el �rbol para asegurar que todos los paquetes tienen repartidor.
Si el nodo es nulo, se retorna true.
Si el campo de repartidor del paquete es una cadena vac�a (""), se retorna false porque no tiene repartidor.
Se retorna la variable booleana, llamando al m�todo con el hijo izquierdo y derecho.
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
Obtener todos los paquetes del AVL (p�blico).
Se retorna una cola creada, que es modificada por referencia en el m�todo privado de retornar todos los
paquetes del AVL.
*/

std::queue<Paquete*> AVL::obtener_todos_paquetes()
{
    std::queue <Paquete*> cola;
    obtener_paquetes_private(this->raiz, cola);
    return cola;
}

/*
Paquetes con repartidor, p�blico.
Se retorna el valor booleano retornado a su vez, por su versi�n privada del m�todo.
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
Cantidad de nodos, p�blico.
Se ejecuta el m�todo privado, y se retorna su valor.
*/

int AVL::cantidad_nodos()
{
    return cantidad_nodos_private(this->raiz);
}

/*
Suma de tiempo de paquetes con tipo de envio (p�blico).
Se ejecuta el m�todo privado, y se retorna su valor.
*/

int AVL::suma_paquetes_tiempo_envio(std::string tipo_envio)
{
    return suma_tiempo_envio_private(this->raiz, tipo_envio);
}

/*
Cantidad de paquetes con un tipo de env�o (p�blico).
Se ejecuta el m�todo privado, y se retorna su valor.
*/

int AVL::cantidad_paquetes_tipo_envio(std::string tipo_envio)
{
    return cantidad_tipo_envio_private(this->raiz, tipo_envio);
}

/*
Insertar (privado).
Primeramente se realiza una inserci�n normal como en el ABB, pero esta vez, recursivamente.
Si el nodo es nulo (se llega al espacio a insertar), se inicializa el nodo nuevo con el paquete.
Se compara si el c�digo de paquete es menor o mayor al del nodo actual (para ir a la izquierda o derecha,
y designar si es el hijo izquierdo o derecho), y si ya existe, se retorna el nodo directamente porque no se aceptan paquetes repetidos.
Cuando ya se agregue el nodo, el proceso del m�todo actual se detiene y regresa a la anterior, reflejando recursividad.

Luego de insertar, se actualiza la altura del nodo actual (obteniendo el m�ximo entre la altura del hijo izquierdo y derecho m�s 1),
y se calcula su factor de balance (resta de la altura del hijo izquierdo y derecho).

En caso de que el factor de balance est� entre -1, 0 o 1, no hay problema, no hay necesidad de realizar rotaciones.
Existen 4 casos diferentes para realizar la rotaci�n.

1) El factor de balance es menor a -1 (hacia la derecha), y el c�digo del paquete a insertar es mayor que el del hijo derecho del 
nodo desbalanceado (Rotaci�n RR, arcos derecho - derecho).

2) El factor de balance es mayor a 1 (hacia la izquierda), y el c�digo del paquete a insertar es menor que el del hijo izquierdo del 
nodo desbalanceado (Rotaci�n LL, arcos izquierdo - izquierdo).

3) El factor de balance es mayor a 1 (hacia la izquierda), y el c�digo del paquete a insertar es mayor que el del hijo izquierdo del 
nodo desbalanceado (Rotaci�n LR, arcos izquierdo - derecho).

4) El factor de balance es menor a -1 (hacia la derecha), y el c�digo del paquete a insertar es menor que el del hijo derecho del 
nodo desbalanceado (Rotaci�n RL, arcos derecho - izquierdo).

Finalmente, se retorna el nodo actual, los cambios realizados para las inserciones y rotaciones no afectan a los nodos que no est�n involucrados.
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
Si el nodo es nulo, se retorna un paquete nulo (no existe en el �rbol).
Recursivamente, se comparan los valores del nodo actual con el codigo del paquete a encontrar.
El AVL ya est� ordenado como el ABB: el hijo izquierdo posee un menor codigo de paquete que el padre,
y el derecho un c�digo mayor que el padre. As�, se llama de manera recursiva el m�todo, hasta encontrar
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
Buscar paquete (p�blico).
Se ejecuta el m�todo privado de buscar un paquete, con el nodo ra�z y el c�digo de paquete.
*/

Paquete* AVL::buscar(int codigo_paquete) {
    NodoAVL* copia_raiz = this->raiz;
    return buscar_private(copia_raiz, codigo_paquete);
}

/*
Buscar paquetes con tiempo mayor a 24 horas (privado).
Se recorre recursivamente en preorden, si el paquete en un nodo tiene un tiempo de entrega mayor a 1440 minutos.
Si es as�, se inserta en la cola de paquetes, que es pasado por referencia. Si el nodo es nulo, se retorna.
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





