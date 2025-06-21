#include "sistema.h"
Sistema* Sistema::instance = NULL;
using namespace std;

Sistema * Sistema::getInstance() {
    if(instance == NULL)
        instance = new Sistema();
    return instance;
}

Sistema::Sistema() {
    this->productos = new OrderedDictionary(); //agregamos list.h en sistema.h porque marcaba error aca
    this->mesas = new OrderedDictionary();
    this->ventas = new OrderedDictionary();
    this->ventasActivas = new OrderedDictionary();
    this->mesasSeleccionadas = new List();
    this->empleados = new OrderedDictionary();
    this->clientes = new OrderedDictionary();
    this->cantidadSimpleTemporal = new OrderedDictionary();
    idMozoSeleccionado = 0;
    idMesaSeleccionada = 0;
    idProductoSeleccionado = 0;
    cantProductosSeleccionados = 0;
    idVenta = 0; // ID de la venta, se incrementa con cada nueva venta
    codigoProductoSeleccionado = 0; // Código del producto seleccionado para agregar a la venta
    cantMozos = 0; // Cantidad de mozos registrados
}

// Destructor
Sistema::~Sistema() {
    
}

IDictionary* Sistema::getCliente() {
    return clientes;
}

IDictionary* Sistema::getEmpleados() {
    return empleados;
}

IDictionary* Sistema::getProductos() {
    return productos;
}
IDictionary* Sistema::getMesas() {
    return mesas;
}
IDictionary* Sistema::getVentas() {
    return ventasActivas;
}

// Métodos de la clase Sistema
bool Sistema::hayProductos() {
    return !productos->isEmpty();
}

int Sistema::ingresarProductoComun(string codigo, string nombre, float precio) { // REVISAR
    if(codigo.empty() || nombre.empty() || precio <= 0) {
        cout << "Datos del producto inválidos." << endl;
        return 2;
    }
    
    // Verificar si el producto ya existe
    if (productos->member(new Integer(atoi(codigo.c_str())))) {
        //cout << "El producto ya existe." << endl;
        return 0;
    }

    // Crear un nuevo producto y agregarlo al diccionario
    productoComun = new dtSimple(atoi(codigo.c_str()), nombre, precio);
    return 1;
}

void Sistema::confirmarProducto() {  // REVISAR
    if (productoComun == NULL) {
        cout << "No hay un producto ingresado." << endl;
        return;
    }

    // Convertir de dtSimple a Simple antes de agregar al diccionario
    Simple* simple = new Simple(productoComun->getCodigo(), productoComun->getNombre(), productoComun->getPrecio());
    productos->add(new Integer(simple->getCodigo()), dynamic_cast<ICollectible*>(simple));
    cout << "Producto común ingresado correctamente." << endl;
    productoComun = NULL; // Evitar puntero colgante
}

void Sistema::cancelarProducto() {  // REVISAR
    // Implementación de la lógica para cancelar un producto
    delete productoComun; // Liberar memoria del producto temporal
    productoComun = NULL; // Evitar puntero colgante
}

ICollection* Sistema::listarProductosComunes() {  // REVISAR
    if (hayProductos()) {
        ICollection* listaProductos = new List();
        IIterator* it = productos->getIterator();
        while (it->hasCurrent()) {
            Simple* simple = dynamic_cast<Simple*>(it->getCurrent());
            if (simple != NULL) {
                dtProducto* dtProd = new dtProducto(simple->getCodigo(), simple->getNombre(), simple->getPrecio());
                listaProductos->add(dynamic_cast<ICollectible*>(dtProd));
            }
            it->next();
        }
        delete it;
        return listaProductos;
    } else {
        cout << "No hay productos disponibles." << endl;
        return NULL;
    }
}

void Sistema::agregarProductoAMenu(int codigo, int cantidad) { //A CHEQUEAR
    // Implementación de la lógica para agregar un producto al menú
    if (codigo <= 0 || cantidad <= 0) {
        cout << "Código o cantidad inválidos." << endl;
        return;
    }

    // Verificar si el producto existe
    if (!productos->member(new Integer(codigo))) {
        cout << "Producto no encontrado." << endl;
        return;
    }

    Simple* producto = dynamic_cast<Simple*>(productos->find(new Integer(codigo)));
    CantidadSimple* cantidadSimple = new CantidadSimple(producto, cantidad);
    cantidadSimpleTemporal->add(new Integer(producto->getCodigo()), dynamic_cast<ICollectible*>(cantidadSimple));
}

void Sistema::confirmarMenu(int codigo) { //A CHEQUEAR
    // Implementación de la lógica para confirmar el menú
    if (cantidadSimpleTemporal->isEmpty() || codigo <= 0) {
        cout << "Datos no validos" << endl;
        return;
    }

    // Verificar si el menú ya existe
    if (ventas->member(new Integer(codigo))) {
        cout << "El producto ya existe." << endl;
        return;
    }

    // Crear un nuevo menú con los productos temporales
    cout << "Ingrese descricion del menu: ";
    string descripcion;
    cin >> descripcion;
    cout << "\nIngrese precio del menu: ";
    float precio;
    cin >> precio;
    cout << "\n\n";
    Menu* nuevoMenu = new Menu(codigo, descripcion, precio, 0, cantidadSimpleTemporal);
    productos->add(new Integer(nuevoMenu->getCodigo()), dynamic_cast<ICollectible*>(nuevoMenu));
    cout << "Menú creado con éxito." << endl;
    // Limpiar el diccionario temporal
    IIterator* it = cantidadSimpleTemporal->getIterator();
    while (it->hasCurrent()) {
        ventaProducto* vp = dynamic_cast<ventaProducto*>(it->getCurrent());
        if (vp != NULL) {
            cantidadSimpleTemporal->remove(new Integer(vp->getProducto()->getCodigo())); // Eliminar del diccionario temporal
            delete vp; // Liberar memoria del objeto ventaProducto
        }
        it->next();
    }
}

void Sistema::cancelarMenu() {  // REVISAR
    IIterator* it = cantidadSimpleTemporal->getIterator();
    while (it->hasCurrent()) {
        ventaProducto* vp = dynamic_cast<ventaProducto*>(it->getCurrent());
        cantidadSimpleTemporal->remove(new Integer(vp->getProducto()->getCodigo())); // Eliminar del diccionario temporal
        delete vp;    // Borra solo el objeto ventaProducto, NO el producto base
        it->next();
    }
    delete it;
    cout << "Alta de menú cancelada y memoria liberada.\n";
}

ICollection* Sistema::listarProductos() { // REVISAR
    ICollection* listaProductos = new List();
    IIterator* it = productos->getIterator();
    while (it->hasCurrent()) {
        Producto* prod = dynamic_cast<Producto*>(it->getCurrent());
        if (prod != NULL) {
            dtProducto* dtProd = new dtProducto(prod->getCodigo(), prod->getNombre(), prod->getPrecio());
            listaProductos->add(dynamic_cast<ICollectible*>(dtProd));
        }
        it->next();
    }
    delete it;
    return listaProductos;
}

int Sistema::seleccionarProducto(string codigo) { //REVISAR
    IKey* key = new Integer(atoi(codigo.c_str()));
    if (productos->member(key)) {
        Producto* prod = dynamic_cast<Producto*>(productos->find(key));
        if (prod != NULL) {
            codigoProductoSeleccionado = prod->getCodigo();
            delete key; // Liberar memoria del key
            return 1;
        }
    }
    delete key; // Liberar memoria del key
    //cout << "Producto no encontrado." << endl;
    return 0;
}

void Sistema::eliminarProducto() { // REVISAR
    if(codigoProductoSeleccionado == 0) {
        cout << "No se ha seleccionado ningún producto para eliminar." << endl;
        return;
    }

    // Verificar si el producto está en uso en alguna venta activa
    IKey* key = new Integer(codigoProductoSeleccionado);
    
    IIterator* itVA = ventasActivas->getIterator();
    while (itVA->hasCurrent()) {
        Local* local = dynamic_cast<Local*>(itVA->getCurrent());
        if (local != NULL) {
            ICollection* ventaProductos = local->getVentaProductos();
            IIterator* itVP = ventaProductos->getIterator();
            while (itVP->hasCurrent()) {
                ventaProducto* vp = dynamic_cast<ventaProducto*>(itVP->getCurrent());
                if (vp != NULL && vp->getProducto()->getCodigo() == codigoProductoSeleccionado) {
                    cout << "El producto no puede ser eliminado porque está en uso en una venta activa." << endl;
                    delete key; // Liberar memoria del key
                    delete itVP; // Liberar memoria del iterador de productos en la venta
                    delete vp;
                    delete itVA; // Liberar memoria del iterador de ventas activas
                    return;
                }
                itVP->next();
            }
            delete itVP; // Liberar memoria del iterador de productos en la venta
        }
        itVA->next();
    }
    delete itVA; // Liberar memoria del iterador de ventas activas
    
    // Buscamos el producto en menu
    IIterator* itMenu = ventas->getIterator();
    while (itMenu->hasCurrent()) {
        Menu* menu = dynamic_cast<Menu*>(itMenu->getCurrent());
        if (menu != NULL) {
            IIterator* itCantidad = menu->getCantidadSimple()->getIterator();
            IIterator* aux = menu->getCantidadSimple()->getIterator();
            while (itCantidad->hasCurrent()) {
                CantidadSimple* cantidadSimple = dynamic_cast<CantidadSimple*>(itCantidad->getCurrent());
                if (cantidadSimple != NULL && cantidadSimple->getProducto()->getCodigo() == codigoProductoSeleccionado) {
                    cantidadSimple->~CantidadSimple();
                    delete cantidadSimple; // Liberar memoria del objeto CantidadSimple
                }
                itCantidad->next();
            }

            // Verificar si el menú queda vacío después de eliminar el producto
            if(aux->getCurrent() == NULL) { // Si el menú queda vacío
                ventas->remove(new Integer(menu->getCodigo())); // Eliminar el menú del diccionario
                delete menu; // Liberar memoria del menú
            }

        }
        itMenu->next();
    }
    
    // Eliminamos el producto del diccionario
    if (productos->member(key)) {
        productos->remove(key);
        cout << "Producto eliminado correctamente." << endl;
    } else {
        cout << "Producto no encontrado." << endl;
    }
    delete key; // Liberar memoria del key
    codigoProductoSeleccionado = 0; // Reiniciar el código del producto seleccionado    
}

void Sistema::cancelarBajaProducto(){ // REVISAR
    codigoProductoSeleccionado = 0;
    cout << "Baja de producto cancelada." << endl;
}

bool Sistema::ingresarIdentificador(int idMozo) {
    IIterator* it = empleados->getIterator();
    while (it->hasCurrent()) {
        Mozo* mozo = dynamic_cast<Mozo*>(it->getCurrent());
        if (mozo && mozo->getIdMozo() == idMozo) {
            idMozoSeleccionado = idMozo; // Asignar el ID del mozo seleccionado
            delete it;
            return true;
        }
        it->next();
    }
    delete it;
    return false;
}

ICollection* Sistema::mostrarMesasAsignadasSinVenta() {
    ICollection* mesasSinVenta = new List(); // Lista a retornar
    IIterator* it = mesas->getIterator();    // Iterador sobre el diccionario de mesas

    while (it->hasCurrent()) {
        Mesa* mesa = dynamic_cast<Mesa*>(it->getCurrent());  // Obtener la mesa actual
        if (mesa != NULL && mesa->getEstado() != Activa) {
            mesasSinVenta->add(new Integer(mesa->getidMesa()));  // Solo agregamos si no tiene venta activa
        }
        it->next();
    }

    delete it;  // Liberamos el iterador
    return mesasSinVenta;
}

bool Sistema::seleccionarMesas(int idMesa) {
    // 1) Compruebo que la mesa esté realmente disponible
    ICollection* disp = mostrarMesasAsignadasSinVenta();
    IIterator* itD = disp->getIterator();
    bool encontrada = false;
    while (itD->hasCurrent()) {
        Integer* key = dynamic_cast<Integer*>(itD->getCurrent());
        if (key && key->getValue() == idMesa) {
            encontrada = true;
            break;
        }
        itD->next();
    }
    delete itD;
    delete disp;
    if (!encontrada) {
        cout << "Mesa " << idMesa << " no está disponible para iniciar venta.\n";
        return false;
    }

    // 2) Localizo el objeto Mesa* en mi diccionario global de mesas
    IKey* k = new Integer(idMesa);
    Mesa* m = dynamic_cast<Mesa*>(mesas->find(k));
    delete k;
    if (!m) {
        cout << "Error interno: no encuentro la mesa " << idMesa << ".\n";
        return false;
    }

    // 3) Verifico que no esté ya en mesasSeleccionadas
    IIterator* itS = mesasSeleccionadas->getIterator();
    bool ya = false;
    while (itS->hasCurrent()) {
        Mesa* existente = dynamic_cast<Mesa*>(itS->getCurrent());
        if (existente && existente->getidMesa() == idMesa) {
            ya = true;
            break;
        }
        itS->next();
    }
    delete itS;
    if (ya) {
        cout << "Mesa " << idMesa << " ya estaba seleccionada.\n";
        return false;
    }

    // 4) La agrego (solo un parámetro, el ICollectible*)
    mesasSeleccionadas->add(dynamic_cast<ICollectible*>(m));
    cout << "Mesa " << idMesa << " agregada a la venta.\n";
    return true;
}

void Sistema::mostrarMesasSeleccionadas() {
    if (mesasSeleccionadas == NULL || mesasSeleccionadas->isEmpty()) {
        cout << "No hay mesas seleccionadas actualmente." << endl;
        return;
    }

    cout << "Mesas seleccionadas:" << endl;

    IIterator* it = mesasSeleccionadas->getIterator();
    while (it->hasCurrent()) {
        Mesa* mesa = dynamic_cast<Mesa*>(it->getCurrent());
        if (mesa != NULL) {
            cout << " - Mesa ID: " << mesa->getidMesa() << endl;
        }
        it->next();
    }
    delete it;
}

bool Sistema::sinVenta() {
    // Iterador sobre todas las ventas activas
    IIterator* it = ventasActivas->getIterator();

    // Recorro cada venta activa
    while (it->hasCurrent()) {
        // Solo interesa a las ventas locales (las que atienden mesas)
        Local* loc = dynamic_cast<Local*>(it->getCurrent());
        if (loc != NULL) {
            // esMesa() devuelve true si esta venta local atiende idMesaSeleccionada
            if (loc->esMesa(idMesaSeleccionada)) {
                delete it;
                return false;  // ¡Tiene ya una venta!
            }
        }
        it->next();
    }

    // Si llegamos hasta acá, nunca encontramos esa mesa en ventas locales
    delete it;
    return true;  // Está “sin venta”
}

void Sistema::confirmarVenta(int idMozo) { // REVISAR
    // 1) Verifico que haya mesas seleccionadas
    if (mesasSeleccionadas->isEmpty()) {
        cout << "No hay mesas seleccionadas para confirmar la venta." << endl;
        return;
    }

    // 2) Creo la colección inicial de VentaProducto (vacía)
    ICollection* ventaProductos = new List();

    // 3) Pido fecha y hora
    cout << "Ingrese la fecha de la venta (dd/mm/yyyy): ";
    int dia, mes, anio;
    char sep;
    // cin >> dia >> sep >> mes >> sep >> anio;
    dia = 10;
    mes = 10;
    anio = 2025;
    fecha* f = new fecha(dia, mes, anio);

    cout << "Ingrese la hora de la venta (hh:mm): ";
    int hh, mm;
    // cin >> hh >> sep >> mm;
    hh = 12;
    mm = 30;
    hora* h = new hora(hh, mm);

    // 4) Creo la factura
    Factura* factura = new Factura(f, h, 22);  // IVA 22%

    // 5) Armo el diccionario de mesas para la nueva venta
    IDictionary* mesasDict = new OrderedDictionary();
    IIterator* itM = mesasSeleccionadas->getIterator();
    while (itM->hasCurrent()) {
        Mesa* m = dynamic_cast<Mesa*>(itM->getCurrent());
        if (m) {
            mesasDict->add(new Integer(m->getidMesa()), dynamic_cast<ICollectible*>(m));
        }
        itM->next();
    }
    delete itM;

    // 6) Creo la venta local con ID, descuento 0, lista vacía, factura y mesas
    Local* nuevaVenta = new Local(
        ++idVenta,       // post-incremento
        0.0f,            // descuento
        ventaProductos,  // colección vacía
        factura,         // factura creada
        mesasDict        // mesas seleccionadas
    );

    // 7) Agrego la venta activa al sistema
    IKey* keyVenta = new Integer(nuevaVenta->getIdVenta());
    ventasActivas->add(keyVenta, dynamic_cast<ICollectible*>(nuevaVenta));

    // 8) Asigno la mesa al mozo
    IIterator* itEmpleados = empleados->getIterator();
    Mozo* mozo = NULL;
    while (itEmpleados->hasCurrent()) {
        Mozo* m = dynamic_cast<Mozo*>(itEmpleados->getCurrent());
        if (m && m->getIdMozo() == idMozo) {
            mozo = m;
            mozo->setMesa(mesasSeleccionadas);
            mozo->setCantMesas(mesasSeleccionadas->getSize()); 
            break;
        }
        itEmpleados->next();
    }

    // 9) Marco cada Mesa como Activa y le asigno la venta
    IIterator* itSel = mesasSeleccionadas->getIterator();
    while (itSel->hasCurrent()) {
        Mesa* m = dynamic_cast<Mesa*>(itSel->getCurrent());
        if (m) {
            Integer* key = new Integer(m->getidMesa());
            Mesa* mesaEnSistema = dynamic_cast<Mesa*>(mesas->find(key));
            delete key;

            if (mesaEnSistema) {
                mesaEnSistema->setEstado(Activa);
                mesaEnSistema->setLocal(nuevaVenta);
            }
        }
        itSel->next();
    }
    delete itSel;

    // Limpiar la lista de mesas seleccionadas después de confirmar la venta
    delete mesasSeleccionadas;
    mesasSeleccionadas = new List(); // Reiniciar la colección de mesas seleccionadas

    
    cout << "Venta confirmada exitosamente." << endl;
}

void Sistema::cancelarVenta() {
    int idVenta;
    cout << "Ingrese el ID de la venta que desea cancelar: ";
    cin >> idVenta;

    // Buscar la venta en el diccionario
    IKey* key = new Integer(idVenta);
    if (!ventas->member(key)) {
        cout << "La venta con ID " << idVenta << " no existe." << endl;
        delete key;
        //return;
    }

    Venta* venta = dynamic_cast<Venta*>(ventas->find(key));

    // Eliminar la venta del diccionario de ventas
    ventas->remove(key);

    // Eliminar de ventasActivas si está ahí
    IIterator* it = ventasActivas->getIterator();
    while (it->hasCurrent()) {
        Venta* v = dynamic_cast<Venta*>(it->getCurrent());
        if (v->getIdVenta() == idVenta) {
            ventasActivas->remove(new Integer(v->getIdVenta())); // Eliminar la venta activa
            break;
        }
        it->next();
    }
    delete it;
    delete venta;
    delete key;

    cout << "La venta ha sido cancelada exitosamente." << endl;
}

void Sistema::cancelarVentaActiva() {
    // Descartamos cualquier venta en curso y limpiamos la selección de mesas
    delete mesasSeleccionadas;
    mesasSeleccionadas = new List();
    cout << "Venta en curso cancelada.\nMesas seleccionadas limpias.\n";
}

int Sistema::finalizarVenta(int idMesa) {
    // 1) Itero sobre ventas activas (que son Venta*, no Mesa*)
    IIterator* it = ventasActivas->getIterator();
    while (it->hasCurrent()) {
        Venta* venta = dynamic_cast<Venta*>(it->getCurrent());
        Local* local = dynamic_cast<Local*>(venta);
        // local->getMesa() es un IDictionary* que mapea Integer->Mesa*
        if (local != NULL && local->getMesa()->member(new Integer(idMesa))) {
            // 2) Quito de activas
            IKey* keyVenta = new Integer(venta->getIdVenta());
            ventasActivas->remove(keyVenta);
            delete keyVenta;

            // 3) Lo paso a histórico
            ventas->add(new Integer(venta->getIdVenta()), venta);

            // 4) Marco la mesa como libre
            //    Recupero el objeto Mesa* desde el diccionario
            Integer* keyMesa = new Integer(idMesa);
            Mesa* mesa = dynamic_cast<Mesa*>( local->getMesa()->find(keyMesa) );
            delete keyMesa;
            if (mesa) {
                mesa->setEstado(Finalizada);  // o el enum que uses para “libre”
            }

            // 5) Guarda ID para mostrar factura luego
            idVenta = venta->getIdVenta();

            delete it;
            return idVenta;
        }
        it->next();
    }
    delete it;
    // Si no encontró ninguna venta activa para esa mesa
    cout << "No hay venta activa para la mesa " << idMesa << ".\n";
    return -1;
}

ICollection* Sistema::mostrarVenta(int idMesa) {
    IIterator* it = ventasActivas->getIterator();
    while (it->hasCurrent()) {
        Local* local = dynamic_cast<Local*>(it->getCurrent());
        if (local && local->esMesa(idMesa)) {
            ICollection* resultado = new List();
            ICollection* productos = local->getVentaProductos(); 
            IIterator* itProd = productos->getIterator();
            while (itProd->hasCurrent()) {
                dtVentaProducto* prod = dynamic_cast<dtVentaProducto*>(itProd->getCurrent());
                if (prod) 
                    resultado->add(prod);
                itProd->next();
            }
            delete itProd;
            delete it; // Liberar el iterador de ventas
            return resultado; // Retornar la colección de productos de la venta
        }
        it->next();
    }
    delete it;
    return NULL; // No se encontró la venta o producto
}

void Sistema::ingresarDescuento(float porcentaje, int idVenta) {
    IIterator* it = ventasActivas->getIterator();
    while (it->hasCurrent()) {
        Venta* v = dynamic_cast<Venta*>(it->getCurrent());
        if (v != NULL && v->getIdVenta() == idVenta) {
            v->setDescuento(porcentaje);
            break; // Se encontró y aplicó el descuento, no es necesario seguir
        }
        it->next();
    }
    delete it; // Liberar el iterador
}

dtVenta* Sistema::mostrarFactura(int idVenta, int idMozo) {
    if(ventasActivas->member(new Integer(idVenta))) {
        Venta* venta = dynamic_cast<Venta*>(ventasActivas->find(new Integer(idVenta)));
        if (venta != NULL) {
            // Crear un objeto dtVenta con los datos de la venta
            dtVenta* factura = venta->mostrarFactura();
            return factura; // Retornar la representación de la venta
        }
    }
    return NULL; // Si no se encontró la venta o no es válida
}

bool Sistema::ingresarVenta(int idMesa) {
    IIterator* it = ventasActivas->getIterator();
    bool mesaEncontrada = false;

    while (it->hasCurrent()) {
        Local* local = dynamic_cast<Local*>(it->getCurrent());
        if (local && local->esMesa(idMesa)) {
            idMesaSeleccionada = idMesa; // Recuerda el id de la mesa seleccionada
            mesaEncontrada = true;
            break;
        }
        it->next();
    }
    delete it;
    if (!mesaEncontrada) 
        cout << "No se encontró la mesa con ID: " << idMesa << endl;
    return mesaEncontrada; // Retorna true si se encontró la mesa, false en caso contrario
}

ICollection* Sistema::mostrarProductosDisponibles() {
    ICollection* resultado = new List();  // Lista donde se devuelven los DtProducto

    IIterator* it = productos->getIterator();
    while (it->hasCurrent()) {
        Producto* prod = dynamic_cast<Producto*>(it->getCurrent());

        // Obtener su representación dtProducto (virtual/polimórfico)
        dtProducto* dtProd = new dtProducto(prod->getCodigo(), prod->getNombre(), prod->getPrecio());
        resultado->add(dtProd); // Agregar el código del producto

        // Si es un menú, agregar también los productos simples internos con su cantidad
        Menu* menu = dynamic_cast<Menu*>(prod);
        if (menu != NULL) {
            IDictionary* simples = menu->getCantidadSimple();  // contiene CantidadSimple*
            IIterator* itSimples = simples->getIterator();

            while (itSimples->hasCurrent()) {
                CantidadSimple* cs = dynamic_cast<CantidadSimple*>(itSimples->getCurrent());
                if (cs != NULL) {
                    Producto* dtSimp = cs->getProducto();  // ya es un DTO
                    int cantidad = cs->getCantidad();

                    resultado->add(new dtCantidadSimple(dtSimp, cantidad));
                }
                itSimples->next();
            }

            delete itSimples;
        }

        it->next();
    }

    delete it;
    return resultado;
}
/*
void Sistema::seleccionarProducto(string codigo, int cantidad) {
    IIterator *it = productos->getIterator();

    while (it->hasCurrent()) {
        Producto *prod = dynamic_cast<Producto *>(it->getCurrent());
        if (prod != NULL && prod->getCodigo() == atoi(codigo.c_str())){
            idProductoSeleccionado = prod->getCodigo();
            cantProductosSeleccionados = cantidad;
            dtProducto* aux = new dtProducto(prod->getCodigo(), prod->getNombre(), prod->getPrecio());
            if (productoTemporal != NULL) {
                delete productoTemporal;
                productoTemporal = NULL;
            }
            productoTemporal = new dtVentaProducto(aux, cantidad);
            break;
        } 
        it->next();
    }
    delete it; // Liberar el iterador
}
*/
void Sistema::agregarProducto(int idMesa, int idProducto, int cantidad) {
    // 1) Buscar el Producto en el diccionario
    Integer* claveProd = new Integer(idProducto);
    Producto* p = dynamic_cast<Producto*>(productos->find(claveProd));
    delete claveProd;
    char paprobar = 'a';
    cout << "Producto encontrado: " << (p->getNombre()) << endl;
    if (p == NULL) 
        return;  // Si no existe, salgo

    // 2) Recorrer todas las ventas activas hasta encontrar la mesa
    IIterator* it = ventasActivas->getIterator();
    bool ok = false;

    while (it->hasCurrent() && !ok) {
        cout << "Revisando venta activa..." << endl;
        Venta* venta = dynamic_cast<Venta*>(it->getCurrent());
        if (venta != NULL && venta->esMesa(idMesa)) {
            // 3) Aquí tengo la Venta Local correcta
            Local* local = dynamic_cast<Local*>(venta);
            if (local != NULL) {
                cout << "Venta Local encontrada para la mesa: " << idMesa << endl;
                // 4.1) Crear el ventaProducto
                //    - El constructor de ventaProducto toma (string cantidad, Producto* prod)
                ventaProducto* vp = new ventaProducto(cantidad, p);

                // 4.2) Agregarlo a la colección de la venta
                // if (productosVenta == NULL) {
                //     cout << "No hay productos en la venta, creando nueva colección." << endl;
                //     productosVenta = new List();
                // }
                // productosVenta->add(vp);
                // local->setVentaProductos(productosVenta);
                local->agregarProducto(vp);
                ICollection* productosVenta = local->getVentaProductos();
                IIterator* itVP = productosVenta->getIterator();
                while (itVP->hasCurrent()) {
                    // cin>> paprobar; // Para pausar y ver los productos
                    ventaProducto* vpExistente = dynamic_cast<ventaProducto*>(itVP->getCurrent());
                    cout << vpExistente->getProducto() << endl;
                    itVP->next();
                }
                ok = true;
            }
        }
        it->next();
    }
    cout << "Producto agregado a la venta." <<endl;
    delete it;
    codigoProductoSeleccionado = 0; // Reiniciar el código del producto seleccionado
}

void Sistema::agregarProductoDomicilio(int idVenta, int idProducto, int cantidad) {
    // 1) Buscar el Producto en el diccionario
    Integer* claveProd = new Integer(idProducto);
    Producto* p = dynamic_cast<Producto*>( productos->find(claveProd) );
    delete claveProd;
    if (p == NULL) 
        return;  // si no existe, salgo

    // 2) Recorrer todas las ventas activas hasta encontrar la venta domicilio
    IIterator* it = ventasActivas->getIterator();
    bool ok = false;
    while ( it->hasCurrent() && !ok ) {
        Venta* venta = dynamic_cast<Venta*>( it->getCurrent() );
        // 2.1) Comparo por ID de venta genérico
        if (venta != NULL && venta->getIdVenta() == idVenta) {
            // 3) Encontré la venta domicilio correcta
            Domicilio* dom = dynamic_cast<Domicilio*>(venta);
            if (dom != NULL) {
                // 4.1) Crear el ventaProducto (constructor: string cantidad, Producto*)
                //     Si tu entorno no tiene std::to_string, usa stringstream:
                    // Convertir 'cantidad' a string en C++98
                ventaProducto* vp = new ventaProducto(cantidad, p);

                // 4.2) Agregarlo a la colección de la venta domicilio
                ICollection* productosVenta = dom->getVentaProductos();
                productosVenta->add(vp);

                ok = true;
            }
        }
        it->next();
    }
    delete it;

    delete productoTemporal; // Liberar memoria del producto temporal
    productoTemporal = NULL; // Evitar puntero colgante

}

void Sistema::aumentarCantProducto(int idMesa, int idProducto, int cantidad) {
    // 1. Recorro ventas activas hasta la Local de la mesa
    IIterator* it   = ventasActivas->getIterator();
    bool encontrado = false;
    while (it->hasCurrent() && !encontrado) {
        Venta* v = dynamic_cast<Venta*>(it->getCurrent());
        if (v && v->esMesa(idMesa)) {
            Local* loc = dynamic_cast<Local*>(v);
            if (loc) {
                // 2. Recorro los VentaProducto de esa venta
                IIterator* itVP = loc->getVentaProductos()->getIterator();
                while (itVP->hasCurrent()) {
                    ventaProducto* vp = dynamic_cast<ventaProducto*>(itVP->getCurrent());
                    if (vp && vp->getProducto()->getCodigo() == idProducto) {
                        // 3. Si coincide el ID, actualizo la cantidad
                        int nuevaCant = vp->getCantidad() + cantidad;
                        // Convertir 'nuevaCant' a string en C++98
                        vp->setCantidad(nuevaCant);
                        encontrado = true;
                        break;
                    }
                    itVP->next();
                }
                delete itVP;
            }
        }
        it->next();
    }
    delete it;

    delete productoTemporal; // Liberar memoria del producto temporal
    productoTemporal = NULL; // Evitar puntero colgante

}

void Sistema::salir() {
    // liberar productos
    IIterator* itP = productos->getIterator();
    while (itP->hasCurrent()) {
        delete itP->getCurrent();
        itP->next();
    }
    delete itP;
    delete productos;

    // liberar ventasActivas
    IIterator* itV = ventasActivas->getIterator();
    while (itV->hasCurrent()) {
        delete itV->getCurrent();
        itV->next();
    }
    delete itV;
    delete ventasActivas;

    // ... liberar mesas, clientes, mozos, etc.

    return;
}

void Sistema::mostrarConfirmacion() {
    cout << "\n=== Confirmación de la Venta (Mesa " << idMesaSeleccionada << ") ===\n";

    // 1) Busco la venta local que atiende idMesaSeleccionada
    IIterator* itV = ventasActivas->getIterator();
    while (itV->hasCurrent()) {
        Local* loc = dynamic_cast<Local*>(itV->getCurrent());
        if (loc && loc->esMesa(idMesaSeleccionada)) {
            // 2) Muestro todos los productos agregados a esa venta
            IIterator* itVP = loc->getVentaProductos()->getIterator();
            while (itVP->hasCurrent()) {
                ventaProducto* vp = dynamic_cast<ventaProducto*>(itVP->getCurrent());
                if (vp) {
                    int cant = vp->getCantidad(); // Cantidad del producto
                    Producto* prod = vp->getProducto();
                    float precio = prod->getPrecio();
                    float subtotal= cant * precio;

                    cout << " • " 
                         << prod->getNombre()
                         << "  x" << cant
                         << "  @ $" << precio
                         << "  = $" << subtotal
                         << "\n";
                }
                itVP->next();
            }
            delete itVP;
            break;
        }
        itV->next();
    }
    delete itV;

    cout << "=====================================\n\n";
}

void Sistema::ingresarMesa(int idMesa) {
    if (idMesa <= 0) {
        cout << "ID de mesa inválido." << endl;
        return;
    }

    // 1) Preparamos la clave para buscar
    IKey* key = new Integer(idMesa);

    // 2) Si ya existe, error y liberamos la clave
    if (mesas->member(key)) {
        cout << "Ya existe una mesa con ID " << idMesa << "." << endl;
        delete key;
        return;
    }

    // 3) No existía: creamos la mesa y la añadimos
    Mesa* mesa = new Mesa(idMesa);
    mesas->add(key, dynamic_cast<ICollectible*>(mesa));

    cout << "Mesa " << idMesa << " ingresada correctamente." << endl;
}


ICollection* Sistema::mostrarProductosEnVenta() {
    ICollection* productosEnVenta = new List(); // Lista a retornar
    Mesa* mesita = dynamic_cast<Mesa*>(mesas->find(new Integer(idMesaSeleccionada))); // Iterador sobre el diccionario de ventas activas
    int aux = mesita->getLocal()->getIdVenta();
    IIterator* it = ventasActivas->getIterator(); // Iterador sobre el diccionario de ventas activas

    while (it->hasCurrent()) {
        Local* local = dynamic_cast<Local*>(it->getCurrent()); // Obtener la venta actual
        if (local != NULL && local->getIdVenta() == aux) { // Verificar si es la venta de la mesa seleccionada
            productosEnVenta = local->getVentaProductos(); // Obtener los productos de la venta
        }
        it->next();
    }

    delete mesita; // Liberar memoria de la mesa
    delete it; // Liberar memoria del iterador de ventas
    return productosEnVenta; // Retornar la colección de productos en la venta
}

void Sistema::SeleccionarProductoYCantidad(string producto, int cantidad) { //REVISAR
    if(producto.empty() || cantidad <= 0) {
        cout << "Datos del producto o cantidad inválidos." << endl;
        return;
    }
    // Verificar si el producto existe
    IKey* key = new Integer(atoi(producto.c_str()));
    if (!productos->member(key)) {
        cout << "El producto con código " << producto << " no existe." << endl;
        delete key; // Liberar memoria del key
        return;
    }
    Producto* prod = dynamic_cast<Producto*>(productos->find(key));
    dtProducto* dtProd = new dtProducto(prod->getCodigo(), prod->getNombre(), prod->getPrecio());
    productoTemporal = new dtVentaProducto(dtProd, cantidad); // Asignar el ID del producto seleccionado

    delete key; // Liberar memoria del key
}

void Sistema::EliminarProducto(int idVenta) { // REVISAR
    if(idVenta <= 0 || !ventasActivas->member(new Integer(idVenta)) || productoTemporal == NULL) {
        cout << "Datos no Validos" << endl;
        return;
    }

    // Buscar la venta activa
    IIterator* it = ventasActivas->getIterator();
    while (it->hasCurrent()) {
        Local* local = dynamic_cast<Local*>(it->getCurrent());
        if (local != NULL && local->getIdVenta() == idVenta) {
            ICollection* ventaProductos = local->getVentaProductos();
            IIterator* itVP = ventaProductos->getIterator();
            while (itVP->hasCurrent()) {
                ventaProducto* vp = dynamic_cast<ventaProducto*>(itVP->getCurrent());
                if (vp != NULL && vp->getProducto()->getCodigo() == productoTemporal->getProducto()->getCodigo()) {
                    if(vp->getCantidad() <= productoTemporal->getCantidad()) {
                        // Si la cantidad del producto en la venta es menor o igual a la cantidad temporal, eliminarlo
                        ventaProductos->remove(vp);
                        delete vp; // Liberar memoria del producto eliminado
                        productoTemporal = NULL; // Liberar el producto temporal
                        cout << "Producto eliminado de la venta." << endl;
                    } else {
                        // Si la cantidad del producto en la venta es mayor, reducir la cantidad
                        int nuevaCantidad = vp->getCantidad() - productoTemporal->getCantidad();
                        // Conversión de int a string en C++98
                        vp->setCantidad(nuevaCantidad);
                        cout << "Cantidad del producto reducida en la venta." << endl;
                    }
                }
                itVP->next();
            }
            delete itVP; // Liberar memoria del iterador de productos en la venta
            break;
        }
        it->next();
    }
}

void Sistema::cancelarAccion() { // REVISAR
    productoTemporal = NULL; // Liberar el producto temporal
    cout << "Acción cancelada." << endl;
}

int Sistema::altaCliente(string ci, string nombre, string telefono, direccion* direccion){ //REVISAR
    if(ci.empty() || nombre.empty() || telefono.empty() || direccion == NULL) {
        //cout << "Datos del cliente inválidos." << endl;
        return 2; // Retornar 2 para indicar error en los datos
    }

    // Verificar si el cliente ya existe
    if (clientes->member(new String(ci.c_str()))) {
        //cout << "El cliente ya existe." << endl;
        return 0; // Retornar 0 para indicar que el cliente ya existe
    }

    // Crear un nuevo cliente y agregarlo al diccionario
    Cliente* nuevoCliente = new Cliente(ci, nombre, telefono, direccion);
    clientes->add(new String(nuevoCliente->getCi().c_str()), dynamic_cast<ICollectible*>(nuevoCliente));
    cout << nuevoCliente->getNombre() << " ha sido agregado como cliente." << endl;
    cout << "ID del cliente: " << nuevoCliente->getCi() << endl;
    cout << "Nombre del cliente: " << nuevoCliente->getNombre() << endl;
    cout << "Teléfono del cliente: " << nuevoCliente->getTelefono() << endl;
    // cout << "Dirección del cliente: " << nuevoCliente->getDireccion()->toString() << endl;
    return 1; // Retornar 1 para indicar que el cliente fue agregado exitosamente
}
 

void Sistema::altaMozo(string nombre){ //REVISAR
    if(nombre.empty()) {
        cout << "Datos del mozo inválidos." << endl;
        return;
    }
    
    int num = empleados->getSize()+1;

    // Crear un nuevo mozo y agregarlo al diccionario
    Mozo* nuevoMozo = new Mozo(num, nombre, cantMozos++ +1);
    empleados->add(new Integer(num), dynamic_cast<ICollectible*>(nuevoMozo));
}

void Sistema::altaRepartidor(string nombre, string transporte){
    if(nombre.empty() || transporte.empty()) {
        cout << "Datos del repartidor inválidos." << endl;
        return;
    }

    int num = empleados->getSize()+1;

    // Crear un nuevo repartidor y agregarlo al diccionario
    Repartidor* nuevoRepartidor = new Repartidor(num, nombre, transporte);
    empleados->add(new Integer(num), dynamic_cast<ICollectible*>(nuevoRepartidor));
}

dtProducto* Sistema::informacionProducto(int codigoProducto) {
    // 1) Busco en el diccionario
    ICollectible* col = productos->find(new Integer(codigoProducto));
    if (col == NULL) {
        cout << "Error: Producto " << codigoProducto << " no encontrado." << endl;
        return NULL;
    }
    // 2) Convierto a dominio
    Producto* prod = dynamic_cast<Producto*>(col);
    // 3) Genero y devuelvo el DTO
    return prod->mostrarFactura();    // dtProducto*
}



// … dentro de Sistema.cpp …

void Sistema::asignarMesaAMozo() {
    // 1) Verificar que no haya ventas activas
    if (ventasActivas->getSize() > 0) {
        cout << "No se puede asignar mesas: existen ventas sin facturar." << endl;
        return;
    }

    // 2) Extraer solo los Mozo* en una lista temporal
    IIterator* itE = empleados->getIterator();
    List* listaMozos = new List();
    while (itE->hasCurrent()) {
        Mozo* m = dynamic_cast<Mozo*>(itE->getCurrent());
        if (m) listaMozos->add(m);
        itE->next();
    }
    delete itE;

    int cantMozos = listaMozos->getSize();
    int cantMesas = mesas->getSize();
    if (cantMozos == 0 || cantMesas == 0) {
        cout << "No hay mozos o mesas para asignar." << endl;
        delete listaMozos;
        return;
    }

    // 3) Volcar mozos y mesas a arrays dinámicos
    Mozo** mozosArr = new Mozo*[cantMozos];
    {
        IIterator* itM = listaMozos->getIterator();
        for (int i = 0; i < cantMozos && itM->hasCurrent(); ++i) {
            mozosArr[i] = dynamic_cast<Mozo*>(itM->getCurrent());
            itM->next();
        }
        delete itM;
    }

    Mesa** mesasArr = new Mesa*[cantMesas];
    {
        IIterator* itMe = mesas->getIterator();
        for (int i = 0; i < cantMesas && itMe->hasCurrent(); ++i) {
            mesasArr[i] = dynamic_cast<Mesa*>(itMe->getCurrent());
            itMe->next();
        }
        delete itMe;
    }

    // 4) Barajar aleatoriamente el array de mozos
    srand(static_cast<unsigned>(time(NULL)));
    for (int i = cantMozos - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Mozo* tmp = mozosArr[i];
        mozosArr[i] = mozosArr[j];
        mozosArr[j] = tmp;
    }

    // 5) Calcular reparto base y resto
    int mesasPorMozo = cantMesas / cantMozos;
    int resto        = cantMesas % cantMozos;

    // 6) Asignar mesas de forma equitativa + resto aleatorio
    int idxMesa = 0;
    for (int i = 0; i < cantMozos; ++i) {
        Mozo* m = mozosArr[i];

        // 6a) Liberar lista previa
        ICollection* vieja = m->getMesa();
        delete vieja;

        // 6b) Crear nueva lista y rellenar
        List* nueva = new List();
        // parte igual
        for (int k = 0; k < mesasPorMozo; ++k) {
            nueva->add(mesasArr[idxMesa++]);
        }
        // uno extra para los 'resto' primeros mozos del array barajado
        if (i < resto) {
            nueva->add(mesasArr[idxMesa++]);
        }

        // 6c) Actualizar en el mozo
        m->setMesa(nueva);
        m->setCantMesas(nueva->getSize());
    }

    // 7) Mostrar la asignación, en el orden original de la lista
    cout << "Asignación de mesas a mozos:\n";
    IIterator* itShow = listaMozos->getIterator();
    while (itShow->hasCurrent()) {
        Mozo* m = dynamic_cast<Mozo*>(itShow->getCurrent());
        cout << "Mozo " << m->getNombre()
             << " (ID " << m->getIdMozo() << "): ";
        if (m->getCantMesas() == 0) {
            cout << "(sin mesas asignadas)\n";
        } else {
            IIterator* itMe = m->getMesa()->getIterator();
            while (itMe->hasCurrent()) {
                Mesa* ms = dynamic_cast<Mesa*>(itMe->getCurrent());
                cout << ms->getidMesa() << " ";
                itMe->next();
            }
            delete itMe;
            cout << "\n";
        }
        itShow->next();
    }
    delete itShow;

    // 8) Liberar arrays y lista auxiliar
    delete[] mozosArr;
    delete[] mesasArr;
    delete listaMozos;
}


ICollection* Sistema::ventasDeMozo(int idMozo) {
    // 1) Recupero al mozo
    ICollectible* colM = empleados->find(new Integer(idMozo));
    if (colM == NULL) {
        cout << "Error: Mozo " << idMozo << " no encontrado." << endl;
        return NULL;
    }
    Mozo* mozo = dynamic_cast<Mozo*>(colM);

    // 2) Recorro las mesas asignadas al mozo
    ICollection* mesasMozo = mozo->getMesa();
    IIterator* it = mesasMozo->getIterator();
    List* listaVentas = new List(); // va a contener dtVenta*

    while (it->hasCurrent()) {
        Mesa* mesa = dynamic_cast<Mesa*>(it->getCurrent());
        Local* ventaLocal = mesa->getLocal();
        if (ventaLocal != NULL) {
            // pongo el DTO de la factura en la lista
            listaVentas->add(ventaLocal->mostrarFactura());
        }
        it->next();
    }
    delete it;
    return listaVentas;
}

dtVenta* Sistema::ventaDomicilio(const string& ciCliente, const string& nombreCliente, const string& telefono, direccion* dir, bool retira, int idRepartidor, ICollection* items) {
    // 1) Cliente: lo busco o creo
    ICollectible* colC = clientes->find(new String(ciCliente.c_str()));
    Cliente* cli;
    if (colC == NULL) {
        cli = new Cliente(ciCliente, nombreCliente, telefono, dir);
        clientes->add(new String(ciCliente.c_str()), cli);
    } else {
        cli = dynamic_cast<Cliente*>(colC);
    }

    // 2) Repartidor
    ICollectible* colR = empleados->find(new Integer(idRepartidor));
    if (colR == NULL) {
        cout << "Error: Repartidor " << idRepartidor << " no existe." << endl;
        return NULL;
    }
    Repartidor* rep = dynamic_cast<Repartidor*>(colR);

    // 3) Armo la venta
    int nuevoId = ventas->getSize() + 1;
    ICollection* ventaProd = new List();  // colección de ventaProducto

    // 3.1) Pido fecha y hora
    cout << "Ingrese la fecha de la venta (dd/mm/yyyy): ";
    int dia, mes, anio;
    char sep;
    cin >> dia >> sep >> mes >> sep >> anio;
    fecha* f = new fecha(dia, mes, anio);

    cout << "Ingrese la hora de la venta (hh:mm): ";
    int hh, mm;
    cin >> hh >> sep >> mm;
    hora* h = new hora(hh, mm);

    Factura* fact = new Factura(f, h, 22);  // IVA 22%
    Domicilio* dom = new Domicilio(nuevoId, 0, retira, ventaProd, fact, cli, rep);
    dom->setCliente(cli);
    // agrego cada ítem
    IIterator* it = items->getIterator();
    while (it->hasCurrent()) {
        dtVentaProducto* dtIt = dynamic_cast<dtVentaProducto*>(it->getCurrent());
        agregarProductoDomicilio(dom->getIdVenta(), dtIt->getProducto()->getCodigo(), dtIt->getCantidad());
        it->next();
    }
    delete it;

    // 4) Finalizo
    //dom->calcularTotal();
    ventas->add(new Integer(nuevoId), dom);
    return dom->mostrarFactura();  // dtDomicilio* apuntado como dtVenta*
}

void Sistema::resumenFacturacion(string fechaISO) {
    float total = 0.0f;
    int   count = 0;

    // 1) Iterar sobre todas las ventas almacenadas en 'ventas'
    IIterator* it = ventas->getIterator();
    while (it->hasCurrent()) {
        Venta* v = dynamic_cast<Venta*>( it->getCurrent() );
        if (v) {
            // 2) Obtener la fecha de la factura y comparar con fechaISO (YYYY-MM-DD)
            Factura* fac = v->getFactura();
            fecha* f = fac->getFecha();

            // Extraigo año, mes y día de fechaISO
            int anio = atoi(fechaISO.substr(0,4).c_str());
            int mes = atoi(fechaISO.substr(5,2).c_str());
            int dia = atoi(fechaISO.substr(8,2).c_str());

            if ( f->getAnio() == anio && f->getMes() == mes && f->getDia() == dia) {
                // 3) Calcular total de esta venta sumando (cantidad * precio)
                ICollection* items = v->getVentaProductos();
                IIterator*    itP   = items->getIterator();
                while (itP->hasCurrent()) {
                    ventaProducto* vp = dynamic_cast<ventaProducto*>( itP->getCurrent() );
                    if (vp) {
                        float precio = vp->getProducto()->getPrecio();
                        total += vp->getCantidad() * precio;
                    }
                    itP->next();
                }
                delete itP;
                count++;
            }
        }
        it->next();
    }
    delete it;

    // 4) Imprimir resultados
    cout << "Resumen de facturación para " << fechaISO << ":" << endl;
    cout << "  Total facturado: $"   << total << endl;
    cout << "  Ventas realizadas: "  << count << endl;
}

void Sistema::asignarMesaAMozo(int numeroMesa, int idMozo) {
    // 1) Recupero mesa
    ICollectible* colMe = mesas->find(new Integer(numeroMesa));
    if (colMe == NULL) {
        cout << "Error: Mesa " << numeroMesa << " no existe." << endl;
        return;
    }
    Mesa* mesa = dynamic_cast<Mesa*>(colMe);

    // 2) Recupero mozo
    ICollectible* colMo = empleados->find(new Integer(idMozo));
    if (colMo == NULL) {
        cout << "Error: Mozo " << idMozo << " no existe." << endl;
        return;
    }
    Mozo* mozo = dynamic_cast<Mozo*>(colMo);

    // 3) Asigno
    mesa->setLocal(NULL);          // despejo venta previa si hay
    mesa->setEstado(Activa);
    mesa->setLocal(NULL);
    mesa->getLocal();                 // opcional, según tu diseño

    // 4) Agrego la mesa a la colección del mozo
    ICollection* colMesas = mozo->getMesa();
    colMesas->add(mesa);
    mozo->setCantMesas(colMesas->getSize());

    cout << "Mesa " << numeroMesa << " asignada al Mozo " << idMozo << "." << endl;
}

bool Sistema::productoEnVenta(int idProducto, int idMesa) {
    // 1) Buscar la venta activa de la mesa
    IIterator* it = ventasActivas->getIterator();
    while (it->hasCurrent()) {
        Local* local = dynamic_cast<Local*>(it->getCurrent());
        cout << "ees mesa o no" << endl;
        if (local && local->esMesa(idMesa)) {
            cout << "si es mesa pajero" << endl;
            // 2) Verificar si el producto está en la venta
            ICollection* productosVenta = local->getVentaProductos();
            if (productosVenta == NULL) {
                cout << "No hay productos en la venta." << endl;
                delete it;  // liberar iterador de ventas
                return false; // no hay productos
            }
            IIterator* itProd = productosVenta->getIterator();
            cout << "antes de entrar al while" << endl;
            while (itProd->hasCurrent()) {
                cout << "dentro del while" << endl;
                ventaProducto* vp = dynamic_cast<ventaProducto*>(itProd->getCurrent());
                cout << "a ver si esta el codigo" << endl;
                cout << "muestro cabeza " << vp->getProducto() << " ssssss" << endl;
                cout << "muestro cantidad " << vp->getCantidad() << " ssssss" << endl;
                if (vp && vp->getProducto()->getCodigo() == idProducto) {
                    cout << "si esta el codigo" << endl;
                    delete itProd;  // sólo eliminamos el iterador
                    delete it;
                    return true;    // producto encontrado
                }
                itProd->next();
            }
            delete itProd;  // liberar iterador de productos
            break;          // ya procesamos esta mesa
        }
        it->next();
    }
    delete it;  // liberar iterador de ventas
    return false;  // producto no encontrado
}

Producto* Sistema::buscarProducto(int codigo) {
    // 1) Construyo la clave
    Integer* key = new Integer(codigo);
    // 2) Busco en el diccionario (devuelve ICollectible* o nullptr)
    ICollectible* col = productos->find(key);
    // 3) Ya no necesito la clave
    delete key;
    // 4) Convierto a Producto* (dynamic_cast) y retorno
    return dynamic_cast<Producto*>(col);
}

ICollection* Sistema::listarVentas() {
    // Creas una lista vacía
    ICollection* lista = new List();
    // Iteras sobre tu diccionario de ventas
    IIterator* it = ventas->getIterator();
    while (it->hasCurrent()) {
        // cada elemento es un ICollectible* que en realidad es Venta*
        ICollectible* col = it->getCurrent();
        lista->add(col);
        it->next();
    }
    delete it;
    // Devuelves la lista de ventas
    return lista;
}
// Implementación de los métodos de la clase Sistema
// Aquí se pueden agregar más métodos según sea necesario