#include "sistema.h"
     // para std::fixed y std::setprecision

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
    // Liberar memoria de los diccionarios y colecciones
    IIterator* it = productos->getIterator();
    IIterator* itMesas = mesas->getIterator();
    IIterator* itVentas = ventas->getIterator();
    IIterator* itVentasActivas = ventasActivas->getIterator();
    IIterator* itEmpleados = empleados->getIterator();
    IIterator* itClientes = clientes->getIterator();
    IIterator* itCantidadSimpleTemporal = cantidadSimpleTemporal->getIterator();

    while (it->hasCurrent()) {
        ICollectible* col = it->getCurrent();
        delete col; // Liberar memoria de cada producto
        it->next();
    }
    delete it;

    while (itMesas->hasCurrent()) {
        ICollectible* col = itMesas->getCurrent();
        delete col; // Liberar memoria de cada mesa
        itMesas->next();
    }
    delete itMesas;

    while (itVentas->hasCurrent()) {
        ICollectible* col = itVentas->getCurrent();
        delete col; // Liberar memoria de cada venta
        itVentas->next();
    }
    delete itVentas;

    while (itVentasActivas->hasCurrent()) {
        ICollectible* col = itVentasActivas->getCurrent();
        delete col; // Liberar memoria de cada venta activa
        itVentasActivas->next();
    }
    delete itVentasActivas;

    while (itEmpleados->hasCurrent()) {
        ICollectible* col = itEmpleados->getCurrent();
        delete col; // Liberar memoria de cada empleado
        itEmpleados->next();
    }
    delete itEmpleados;

    while (itClientes->hasCurrent()) {
        ICollectible* col = itClientes->getCurrent();
        delete col; // Liberar memoria de cada cliente
        itClientes->next();
    }
    delete itClientes;

    while (itCantidadSimpleTemporal->hasCurrent()) {
        ICollectible* col = itCantidadSimpleTemporal->getCurrent();
        delete col; // Liberar memoria de cada cantidad simple temporal
        itCantidadSimpleTemporal->next();
    }
    delete itCantidadSimpleTemporal;

    delete productos;
    delete mesas;
    delete ventas;
    delete ventasActivas;
    delete empleados;
    delete clientes;
    delete cantidadSimpleTemporal;

    // Liberar memoria de productoComun y productoTemporal
    delete productoComun;
    delete productoTemporal;

    // Liberar memoria de las instancias singleton
    if (instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

static std::string toStr(int x) {
  std::ostringstream oss;
  oss << x;
  return oss.str();
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
        throw invalid_argument("No hay un producto ingresado.");
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
        throw invalid_argument("Código o cantidad inválidos.");
    }

    // Verificar si el producto existe
    if (!productos->member(new Integer(codigo))) {
        throw invalid_argument("Producto no encontrado.");
    }

    Simple* producto = dynamic_cast<Simple*>(productos->find(new Integer(codigo)));
    CantidadSimple* cantidadSimple = new CantidadSimple(producto, cantidad);
    cantidadSimpleTemporal->add(new Integer(producto->getCodigo()), dynamic_cast<ICollectible*>(cantidadSimple));
}

void Sistema::confirmarMenu(int codigo) { //A CHEQUEAR
    // Implementación de la lógica para confirmar el menú
    if (cantidadSimpleTemporal->isEmpty() || codigo <= 0) {
        throw invalid_argument("No hay productos en el menú temporal o código inválido.");
    }

    // Verificar si el menú ya existe
    if (ventas->member(new Integer(codigo))) {
        throw invalid_argument("El menú ya existe con ese código.");
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
        }
        it->next();
    }
}

void Sistema::cancelarMenu() {  // REVISAR
    IIterator* it = cantidadSimpleTemporal->getIterator();
    while (it->hasCurrent()) {
        ventaProducto* vp = dynamic_cast<ventaProducto*>(it->getCurrent());
        cantidadSimpleTemporal->remove(new Integer(vp->getProducto()->getCodigo())); // Eliminar del diccionario temporal
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
        throw invalid_argument("No se ha seleccionado un producto para eliminar.");
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
                    delete key; // Liberar memoria del key
                    delete itVP; // Liberar memoria del iterador de productos en la venta
                    delete itVA; // Liberar memoria del iterador de ventas activas
                    throw invalid_argument("El producto no puede ser eliminado porque está en uso en una venta activa.");
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

        if (mesa != NULL && mesa->getEstado() != Activa) 
            mesasSinVenta->add(new Integer(mesa->getidMesa()));  // Solo agregamos si no tiene venta activa
        
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
        throw invalid_argument("No hay mesas seleccionadas.");
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
        throw invalid_argument("No hay mesas seleccionadas para la venta.");
    }

    // 2) Creo la colección inicial de VentaProducto (vacía)
    ICollection* ventaProductos = new List();

    // 3) Pido fecha y hora
    cout << "Ingrese la fecha de la venta (dd/mm/yyyy): ";
    int dia, mes, anio;
    char sep;
     cin >> dia >> sep >> mes >> sep >> anio;
    //  dia = 12; mes = 10; anio = 2023; // Para pruebas, fecha fija
    fecha* f = new fecha(dia, mes, anio);
    cout << "Ingrese la hora de la venta (hh:mm): ";
    int hh, mm;
    cin >> hh >> sep >> mm;
    // hh = 14; mm = 30; // Para pruebas, hora fija
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

    // 1) Busco al mozo en mi colección de empleados
    Mozo* mozo = NULL;
    IIterator* itE = empleados->getIterator();
    while (itE->hasCurrent()) {
        Mozo* m = dynamic_cast<Mozo*>(itE->getCurrent());
        if (m && m->getIdMozo() == idMozo) { mozo = m; break; }
        itE->next();
    }
    delete itE;
    if (!mozo) {
        throw invalid_argument("Mozo con ID " + toStr(idMozo) + " no encontrado.");
    }

    // 6) Creo la venta local con ID, descuento 0, lista vacía, factura y mesas
    Local* nuevaVenta = new Local(
        ++idVenta,       // post-incremento
        0.0f,            // descuento
        ventaProductos,  // colección vacía
        factura,         // factura creada
        mesasDict,       // mesas seleccionadas
        mozo             // mozo asignado
    );

    // 7) Agrego la venta activa al sistema
    IKey* keyVenta = new Integer(nuevaVenta->getIdVenta());
    ventasActivas->add(keyVenta, dynamic_cast<ICollectible*>(nuevaVenta));

    // 8) Asigno la mesa al mozo
    IIterator* itEmpleados = empleados->getIterator();
    //Mozo* mozo = NULL;
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
    IIterator* itVieja = mesasSeleccionadas->getIterator();
    while (itVieja->hasCurrent()) {
        Mesa* m = dynamic_cast<Mesa*>(itVieja->getCurrent());
        if (m) {
            mesasSeleccionadas->remove(new Integer(m->getidMesa())); // Eliminar de la colección anterior
        }
        itVieja->next();
    }
    delete itVieja;
    mesasSeleccionadas = new List(); // Reiniciar la lista de mesas seleccionadas
    
    cout << "Venta confirmada exitosamente." << endl;
}

void Sistema::cancelarVenta() {
    int idVenta;
    cout << "Ingrese el ID de la venta que desea cancelar: ";
    cin >> idVenta;

    IKey* key = new Integer(idVenta);

    if (!ventas->member(key)) {
        cout << "La venta con ID " << idVenta << " no existe." << endl;
        delete key;
        return;
    }

    Venta* venta = dynamic_cast<Venta*>(ventas->find(key));

    // Si es una venta local, desasociar mesas
    Local* local = dynamic_cast<Local*>(venta);
    if (local) {
        IIterator* itMesas = local->getMesa()->getIterator();
        while (itMesas->hasCurrent()) {
            Mesa* m = dynamic_cast<Mesa*>(itMesas->getCurrent());
            if (m) {
                m->setEstado(Finalizada); // Cambiar estado a Finalizada
                m->setLocal(NULL);
            }
            itMesas->next();
        }
        delete itMesas;
    }

    // Eliminar la venta de 'ventas'
    ventas->remove(key);

    // También de ventasActivas si está
    IIterator* it = ventasActivas->getIterator();
    while (it->hasCurrent()) {
        Venta* v = dynamic_cast<Venta*>(it->getCurrent());
        if (v && v->getIdVenta() == idVenta) {
            ventasActivas->remove(new Integer(idVenta));
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
    IIterator* itVieja = mesasSeleccionadas->getIterator();
    while (itVieja->hasCurrent()) {
        Mesa* m = dynamic_cast<Mesa*>(itVieja->getCurrent());
        if (m) {
            mesasSeleccionadas->remove(m); // remueve el objeto, no una clave
        }
        itVieja->next();
    }
    delete itVieja;
    delete mesasSeleccionadas; 
    mesasSeleccionadas = new List(); // nueva lista vacía
}

int Sistema::finalizarVenta(int idMesa) {
    IIterator* it = ventasActivas->getIterator();

    while (it->hasCurrent()) {
        Venta* vent = dynamic_cast<Venta*>(it->getCurrent());
        Local* local = dynamic_cast<Local*>(vent);
        
        if (local != NULL) {
            Integer* keyMesa = new Integer(idMesa);

            if (local->getMesa()->member(keyMesa)) {
                // 1) Eliminar de ventasActivas
                IKey* keyVenta = new Integer(vent->getIdVenta());
                ventasActivas->remove(keyVenta);
                delete keyVenta; // Liberar memoria del key

                // 2) Agregar a histórico
                ventas->add(new Integer(vent->getIdVenta()), vent);

                // 3) Marcar la mesa como libre
                Mesa* mesa = dynamic_cast<Mesa*>(local->getMesa()->find(keyMesa));
                if (mesa != NULL) {
                    mesa->setEstado(Finalizada);
                    mesa->setLocal(NULL);
                }

                int id = vent->getIdVenta();
                delete keyMesa;
                delete it;

                return id;
            }

            delete keyMesa;
        }

        it->next();
    }

    delete it;
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
        throw invalid_argument("No hay venta activa para la mesa " + toStr(idMesa) + ".");
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

void Sistema::agregarProducto(int idMesa, int idProducto, int cantidad) {
    // 1) Buscar el Producto en el diccionario
    Integer* claveProd = new Integer(idProducto);
    Producto* p = dynamic_cast<Producto*>(productos->find(claveProd));
    delete claveProd;

    if (p == NULL) {
        throw invalid_argument("Producto con ID " + toStr(idProducto) + " no encontrado.");
    }

    cout << "Producto encontrado: " << p->getNombre() << endl;

    // 2) Recorrer todas las ventas activas hasta encontrar la mesa
    IIterator* it = ventasActivas->getIterator();
    bool ok = false;

    while (it->hasCurrent() && !ok) {
        cout << "Revisando venta activa..." << endl;
        Venta* venta = dynamic_cast<Venta*>(it->getCurrent());
        if (venta != NULL && venta->esMesa(idMesa)) {
            // 3) Aquí tengo la Venta Local correcta
            Local* local = dynamic_cast<Local*>(venta);
            if (local) {
                cout << "Venta Local encontrada para la mesa: " << idMesa << endl;

                // 4) Crear el ventaProducto (Producto* ya fue validado)
                ventaProducto* vp = new ventaProducto(cantidad, p);
                
                // 5) Agregarlo a la colección de la venta

                ICollection * v = venta->getVentaProductos();
                IIterator* itVt = v->getIterator();
                while (itVt->hasCurrent()) {
                    ventaProducto* vpExistente = dynamic_cast<ventaProducto*>(itVt->getCurrent());
                    itVt->next();
                }

                cout << "Producto agregado a la venta." << endl;

                // Debug: listar productos actuales
                ICollection* productosVenta = local->getVentaProductos();
                IIterator* itVP = productosVenta->getIterator();
                while (itVP->hasCurrent()) {
                    ventaProducto* vpExistente = dynamic_cast<ventaProducto*>(itVP->getCurrent());
                    if (vpExistente && vpExistente->getProducto())
                    itVP->next();
                }
                delete itVP;

                ok = true;
            }
        }
        it->next();
    }
    delete it;
    codigoProductoSeleccionado = 0; // Reiniciar el código del producto seleccionado
}

void Sistema::agregarProductoDomicilio(ICollection* vp, int idVenta) {
    // 1) Buscar el Producto en el diccionario

    Venta* v = dynamic_cast<Venta*>(ventas->find(new Integer(idVenta)));
    IIterator* it = vp->getIterator();
    ICollection* productosVenta = new List(); // Colección de productos de la venta
    
    while(it->hasCurrent()){
        dtVentaProducto* dtProd = dynamic_cast<dtVentaProducto*>(it->getCurrent());
        Producto* p = dynamic_cast<Producto*>(productos->find(new Integer(dtProd->getProducto()->getCodigo())));
        productosVenta->add(new ventaProducto(dtProd->getCantidad(), p ));
        it->next();
    }

    delete it;

    v->setVentaProductos(productosVenta); // Asignar la colección de productos a la venta
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
        throw invalid_argument("El ID de la mesa debe ser un número valido.");
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

    delete it; // Liberar memoria del iterador de ventas
    return productosEnVenta; // Retornar la colección de productos en la venta
}

void Sistema::SeleccionarProductoYCantidad(string producto, int cantidad) { //REVISAR
    if(producto.empty() || cantidad <= 0) {
        throw invalid_argument("Datos del producto inválidos. Asegúrese de ingresar un código de producto válido y una cantidad positiva.");
    }
    // Verificar si el producto existe
    IKey* key = new Integer(atoi(producto.c_str()));
    if (!productos->member(key)) {
        delete key; // Liberar memoria del key
        throw invalid_argument("Producto con código " + producto + " no encontrado.");
    }
    Producto* prod = dynamic_cast<Producto*>(productos->find(key));
    dtProducto* dtProd = new dtProducto(prod->getCodigo(), prod->getNombre(), prod->getPrecio());
    productoTemporal = new dtVentaProducto(dtProd, cantidad); // Asignar el ID del producto seleccionado

    delete key; // Liberar memoria del key
}

void Sistema::EliminarProducto(int idVenta) { // REVISAR
    if(idVenta <= 0 || !ventasActivas->member(new Integer(idVenta)) || productoTemporal == NULL) {
        throw invalid_argument("Datos inválidos. Asegúrese de ingresar un ID de venta válido y haber seleccionado un producto.");
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
    delete productoTemporal;
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
        throw invalid_argument("Nombre del mozo no puede estar vacío.");
    }
    
    int num = empleados->getSize()+1;

    // Crear un nuevo mozo y agregarlo al diccionario
    Mozo* nuevoMozo = new Mozo(num, nombre, cantMozos++ +1);
    empleados->add(new Integer(num), dynamic_cast<ICollectible*>(nuevoMozo));
}

void Sistema::altaRepartidor(string nombre, string transporte){
    if(nombre.empty() || transporte.empty()) {
        throw invalid_argument("Nombre y transporte del repartidor no pueden estar vacíos.");
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
        cout << "Producto con código " << codigoProducto << " no encontrado." << endl;
        return NULL;  // Retorno NULL si no se encuentra el producto
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
        throw invalid_argument("No se puede asignar mesas mientras hay ventas activas.");
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
        delete listaMozos;
        throw invalid_argument("No hay mozos o mesas disponibles para asignar.");
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

dtVenta* Sistema::ventaDomicilio(const string& ciCliente, bool retira, int idRepartidor, ICollection* items) {
    // 1) Cliente: lo busco o creo
    ICollectible* colC = clientes->find(new String(ciCliente.c_str()));
    if(colC == NULL) {
        cout << "Error: Cliente " << ciCliente << " no encontrado." << endl;
        return NULL; // o podrías crear un nuevo cliente aquí
    }
    Cliente* cli;
    
    cli = dynamic_cast<Cliente*>(colC);
    bool repa = idRepartidor > 0; // si es positivo, hay repartidor
    Repartidor* rep = NULL;
    if(rep){
        ICollectible* colR = empleados->find(new Integer(idRepartidor));
        if (colR == NULL) {
            cout << "Error: Repartidor " << idRepartidor << " no existe." << endl;
            return NULL;
        }
        rep = dynamic_cast<Repartidor*>(colR);
    }


    // 3) Armo la venta
    int nuevoId = ++idVenta;

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

    Domicilio* dom = NULL; // Inicializo el puntero a Domicilio

    IIterator* it = items->getIterator();
    ICollection* productosVenta = new List(); // Colección de productos de la venta

    while(it->hasCurrent()){
        dtVentaProducto* dtProd = dynamic_cast<dtVentaProducto*>(it->getCurrent());
        Producto* p = dynamic_cast<Producto*>(productos->find(new Integer(dtProd->getProducto()->getCodigo())));
        productosVenta->add(new ventaProducto(dtProd->getCantidad(), p ));
        it->next();
    }

    Factura* fact = new Factura(f, h, 22);  // IVA 22%
    if(repa == false)
        dom = new Domicilio(nuevoId, 0, retira, productosVenta, fact, cli);
    else 
        dom = new Domicilio(nuevoId, 0, retira, productosVenta, fact, cli, rep);

    ventas->add(new Integer(nuevoId), dom); // Agrego la venta al diccionario de ventas

    agregarProductoDomicilio(items, dom->getIdVenta());

    // 4) Finalizo
    //dom->calcularTotal();
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
        throw invalid_argument("Mesa " + toStr(numeroMesa) + " no existe.");
    }
    Mesa* mesa = dynamic_cast<Mesa*>(colMe);

    // 2) Recupero mozo
    ICollectible* colMo = empleados->find(new Integer(idMozo));
    if (colMo == NULL) {
        throw invalid_argument("Mozo con ID " + toStr(idMozo) + " no existe.");
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
    IIterator* itVA = ventasActivas->getIterator();
    bool encontrado = false;

    while (itVA->hasCurrent() && !encontrado) {
        Local* local = dynamic_cast<Local*>(itVA->getCurrent());
        if (local && local->esMesa(idMesa)) {
            ICollection* productosVenta = local->getVentaProductos();
            if (!productosVenta) break;

            IIterator* itProd = productosVenta->getIterator();
            while (itProd->hasCurrent() && !encontrado) {
                // 1) Obtenemos el collectible y casteamos con seguridad
                ICollectible* col = itProd->getCurrent();
                ventaProducto* vp = dynamic_cast<ventaProducto*>(col);

                if (vp && vp->getProducto()) {
                    // 2) Sólo ahora estamos seguros de llamar a getProducto()
                    if (vp->getProducto()->getCodigo() == idProducto) {
                        encontrado = true;
                    }
                }
                itProd->next();
            }
            delete itProd;
            break;  // ya procesamos la venta de esta mesa
        }
        itVA->next();
    }

    delete itVA;
    return encontrado;
}


Producto* Sistema::buscarProducto(int codigo) {
    // 1) Construyo la clave
    Integer* key = new Integer(codigo);
    // 2) Busco en el diccionario (devuelve ICollectible* o NULL)
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
void Sistema::solicitarConsultaFacturacionDia(fecha f) {
    fechaConsulta = f;
    cout << "Consultando facturación para el día: "
         << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << endl;
}



ICollection* Sistema::obtenerDatosVentaDomicilio(fecha f) {
    ICollection* ventasDelDia = new List();
    IIterator* it = ventas->getIterator();

    while (it->hasCurrent()) {
        Domicilio* lol = dynamic_cast<Domicilio*>(it->getCurrent());
        if (lol) {
            fecha* fechaVenta = lol->getFactura()->getFecha();
            if (fechaVenta->getDia() == f.getDia() &&
                fechaVenta->getMes() == f.getMes() &&
                fechaVenta->getAnio() == f.getAnio()) {
                // Si la fecha de la venta coincide con la fecha buscada
                ventasDelDia->add(lol); // Obtener el DTO de la factura
                }
            }
            it->next();
        }

    delete it;
    return ventasDelDia;
}

void Sistema::listarRepartidor(){
    if(!empleados->isEmpty()){
        IIterator* it = empleados->getIterator();
        while(it->hasCurrent()){
            Repartidor* rep = dynamic_cast<Repartidor*>(it->getCurrent());
            if(rep != NULL) {
                cout << "ID: (" << rep->getNumero() 
                     << ") Nombre: " << rep->getNombre() 
                     << " | Transporte: " << rep->getTransporte() 
                     << endl;
            }
            it->next();
        }
    }
}

bool Sistema::existeCliente(const string& ciCliente) {
    // 1) Busco en el diccionario de clientes
    ICollectible* col = clientes->find(new String(ciCliente.c_str()));
    if (col == NULL)
        return false; // No existe
    return true; // Existe
}

void Sistema::mostrarInfoRepartidor(int idRepartidor) {
    // 1) Buscar el repartidor por ID
    ICollectible* col = empleados->find(new Integer(idRepartidor));
    if (col == NULL) {
        return;
    }
    Repartidor* rep = dynamic_cast<Repartidor*>(col);
    
    // 2) Mostrar información
    cout << ", Nombre: " << rep->getNombre() 
         << ", Transporte: " << rep->getTransporte() 
         << endl;
}

ICollection* Sistema::listarMozos() {
    List* resultado = new List();
    IIterator* it = empleados->getIterator();
    while (it->hasCurrent()) {
        Mozo* m = dynamic_cast<Mozo*>(it->getCurrent());
        if (m) resultado->add(m);
        it->next();
    }
    delete it;
    return resultado;
}

ICollection* Sistema::ventasDeMozo(int idMozo, fecha* desde, fecha* hasta) {
    List* resultado = new List();
    IIterator* it = ventas->getIterator(); // ventas históricas
    while (it->hasCurrent()) {
        Local* loc = dynamic_cast<Local*>(it->getCurrent());
        if (loc && loc->getMozo()->getIdMozo() == idMozo) {
            fecha* f = loc->getFactura()->getFecha();
            // comprobamos desde ≤ f ≤ hasta
            bool geDesde = 
                (f->getAnio() > desde->getAnio())
             || (f->getAnio() == desde->getAnio() &&
                (f->getMes() > desde->getMes() ||
                 (f->getMes() == desde->getMes() && f->getDia() >= desde->getDia())));
            bool leHasta =
                (f->getAnio() < hasta->getAnio())
             || (f->getAnio() == hasta->getAnio() &&
                (f->getMes() < hasta->getMes() ||
                 (f->getMes() == hasta->getMes() && f->getDia() <= hasta->getDia())));
            if (geDesde && leHasta) {
                // mostramos la factura (dtLocal hereda de dtVenta)
                resultado->add(loc->mostrarFactura());
            }
        }
        it->next();
    }
    delete it;
    return resultado;
}


void Sistema::mostrarInforme(ICollection* ventas, float totalSistema) {
    cout << "\n--- Resumen de Facturación del Día ---\n";

    IIterator* it = ventas->getIterator();
    while (it->hasCurrent()) {
        dtVenta* v = dynamic_cast<dtVenta*>(it->getCurrent());
        if (v == NULL) {
            it->next();
            continue;
        }

        // Mostrar info disponible desde el DTO
    cout << "  Venta " << v->getIdVenta()
     << " | Fecha: " << v->getFactura()->getFecha()->getDia()
     << "/" << v->getFactura()->getFecha()->getMes()
     << "/" << v->getFactura()->getFecha()->getAnio()
     << " | Descuento: " << v->getDescuento() << "%\n";

        it->next();
    }
    delete it;

    cout << "\nTOTAL FACTURADO (con IVA): $" << totalSistema << endl;
}


ICollection* Sistema::obtenerDatosFacturacion(fecha f) {
    ICollection* ventasDelDia = new List();
    IIterator* it = ventas->getIterator();

    while (it->hasCurrent()) {
        Local* lol = dynamic_cast<Local*>(it->getCurrent());
        if (lol) {
            fecha* fechaVenta = lol->getFactura()->getFecha();
            if (fechaVenta->getDia() == f.getDia() &&
                fechaVenta->getMes() == f.getMes() &&
                fechaVenta->getAnio() == f.getAnio()) {
                // Si la fecha de la venta coincide con la fecha buscada
                ventasDelDia->add(lol); // Obtener el DTO de la factura
            }
        }
        it->next();
    }

    delete it;
    return ventasDelDia;
}

bool Sistema::esMesaEnVentaActiva(int idMesa){
    Mesa* m = dynamic_cast<Mesa*>(mesas->find(new Integer(idMesa)));
    if (m == NULL)
        return false; // Mesa no encontrada
    return true;
}

void Sistema::retirarElemento(int idMesa, int codigoProducto, int cantidad) {
    // 1) Validaciones iniciales
    IKey* kMesa = new Integer(idMesa);
    Mesa* mesa = dynamic_cast<Mesa*>(mesas->find(kMesa));
    delete kMesa;
    if (!mesa) return;

    Local* venta = mesa->getLocal();
    if (!venta) {
        throw invalid_argument("La mesa no tiene una venta activa.");
    }

    // 2) ¡Aquí va el cambio clave!

    ICollection* vpList = venta->getVentaProductos();
    if (!vpList) {
        throw invalid_argument("La venta no tiene productos asociados.");
    }

    IIterator* debugIt = vpList->getIterator();
    int index = 0;

    IIterator* it = vpList->getIterator();
    while (it->hasCurrent()) {
        ICollectible* current = it->getCurrent();
        ventaProducto* linea = dynamic_cast<ventaProducto*>(current);

        Producto* prod = linea->getProducto();

        if (prod->getCodigo() == codigoProducto) {
            cout << "Producto encontrado: " << prod->getNombre() << endl;
            int actual = linea->getCantidad();
            it->next();  // avanzamos antes de modificar la lista

            if (actual <= cantidad) {
                vpList->remove(linea);
                cout << "Producto removido completamente." << endl;
            } else {
                linea->setCantidad(actual - cantidad);
                cout << "Cantidad reducida a " << (actual - cantidad) << endl;
            }
            break;
        }
        it->next();
    }
    delete it;
}