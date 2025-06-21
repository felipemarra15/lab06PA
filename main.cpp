#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <iomanip>

#include "factory.h"
#include "ISistema.h"

#include "DataTypes/direccion.h"
#include "DataTypes/dtProducto.h"

using namespace std;

void cargarDatosPrueba(ISistema* sis) {
    // --- Productos comunes iniciales
    sis->ingresarProductoComun("1", "Café", 1.50f);
    sis->confirmarProducto();
    sis->ingresarProductoComun("2", "Té",   1.00f);
    sis->confirmarProducto();
    sis->ingresarProductoComun("3", "Jugo", 2.00f);
    sis->confirmarProducto();
    sis->ingresarProductoComun("4", "Medialuna", 1.20f);
    sis->confirmarProducto();
    sis->ingresarProductoComun("5", "Sándwich", 3.50f);
    sis->confirmarProducto();
    sis->ingresarProductoComun("6", "Ensalada", 4.00f);
    sis->confirmarProducto();
    sis->ingresarProductoComun("7", "Agua", 0.80f);
    sis->confirmarProducto();
    sis->ingresarProductoComun("8", "Refrigerio", 1.50f);
    sis->confirmarProducto();
    sis->ingresarProductoComun("9", "Postre", 2.75f);
    sis->confirmarProducto();

    // --- Mozos precargados
    sis->altaMozo("Luis");
    cout << "    Mozo 'Luis'    registrado con ID = 1\n";
    sis->altaMozo("Ana");
    cout << "    Mozo 'Ana'     registrado con ID = 2\n";
    sis->altaMozo("Carlos"); cout << "    Mozo 'Carlos'  registrado con ID = 3\n";

    // --- Mesas precargadas
    sis->ingresarMesa(1); 
    sis->ingresarMesa(2); 
    sis->ingresarMesa(3); 
    sis->ingresarMesa(4); 
    sis->ingresarMesa(5); 
    sis->ingresarMesa(6);
    sis->ingresarMesa(7);

    // --- Repartidores precargados
    sis->altaRepartidor("Pedro", "Moto");       cout << "    Repartidor 'Pedro'    registrado con ID = 1\n";
    sis->altaRepartidor("María", "Bicicleta");   cout << "    Repartidor 'María'    registrado con ID = 2\n";

    // --- Mozos

    // --- Clientes precargados
    direccion* dir1 = new direccion("Ciudad A", "Calle 1", "123");
    direccion* dir2 = new direccion("Ciudad B", "Calle 2", "456");
    sis->altaCliente("12345678", "Juan Pérez", "555-1234", dir1);
    sis->altaCliente("87654321", "Ana Gómez", "555-5678", dir2);

    // sis->seleccionarMesas(1);
    // sis->confirmarVenta(1);
    // sis->seleccionarMesas(2);
    // sis->confirmarVenta(2);
    //     // Venta en mesa 2: 2 Té + 2 Refrigerio
    // sis->ingresarIdentificador(2);
    // sis->seleccionarMesas(2);
    // sis->confirmarVenta(2);
    // sis->agregarProducto(2, 102, 2);
    // sis->agregarProducto(2, 108, 5);
    // sis->finalizarVenta(2);

    // // Venta en mesa 3: 1 Jugo + 1 Postre
    // sis->ingresarIdentificador(3);
    // sis->seleccionarMesas(3);
    // sis->confirmarVenta(3);
    // sis->agregarProducto(3, 103, 1);
    // sis->agregarProducto(3, 109, 1);
    // sis->finalizarVenta(3);
    
    cout << ">> Datos de prueba cargados.\n\n";
}

void mostrarProductos(ISistema* sis) {
    cout << "\n--- Lista de Productos ---\n";
    ICollection* lista = sis->listarProductos();
    IIterator* it = lista->getIterator();
    while (it->hasCurrent()) {
        dtProducto* p = dynamic_cast<dtProducto*>(it->getCurrent());
        if (p) {
            cout << "Código: " << p->getCodigo()
                 << " | Nombre: " << p->getNombre()
                 << " | Precio: $" << p->getPrecio()
                 << endl;
            // Si es menú, mostrar detalles adicionales
        }
        it->next();
    }
    delete it;
}

void mostrarClientes(ISistema* sis) {
    cout << "\n--- Lista de Clientes ---\n";
    IDictionary* lista = sis->getCliente();
    IIterator* it = lista->getIterator();
    while (it->hasCurrent()) {
        ICollectible* c = it->getCurrent();
        if (c) {
            Cliente* cliente = dynamic_cast<Cliente*>(c);
            if (cliente) {
                cout << "CI: " << cliente->getCi()
                     << " | Nombre: " << cliente->getNombre()
                     << " | Teléfono: " << cliente->getTelefono()
                     << " | Dirección: " << cliente->getDireccion()->getDireccionCompleta()
                     << endl;
            }
        }
        it->next();
    }
    delete it;
}

void mostrarEmpleados(ISistema* sis) {
    cout << "\n--- Lista de Empleados ---\n";
    IDictionary* empleados = sis->getEmpleados();
    IIterator* it = empleados->getIterator();
    while (it->hasCurrent()) {
        ICollectible* c = it->getCurrent();
        if (c) {
            Empleado* empleado = dynamic_cast<Empleado*>(c);
            if (empleado) {
                cout << "ID: " << empleado->getNumero()
                     << " | Nombre: " << empleado->getNombre()
                     << endl;
                Mozo* mozo = dynamic_cast<Mozo*>(empleado);
                if (mozo) {
                    cout << "  Tipo: Mozo | ID Mozo: " << mozo->getIdMozo()
                         << " | Mesas asignadas: " << mozo->getCantMesas() << endl;
                } else {
                    Repartidor* repartidor = dynamic_cast<Repartidor*>(empleado);
                    if (repartidor) {
                        cout << "  Tipo: Repartidor | Transporte: " << repartidor->getTransporte() << endl;
                    }
                } 
            }
        }
        it->next();
    }
    delete it;
}

void mostrarMesas(ISistema* sis) {
    cout << "\n--- Lista de Mesas ---\n";
    IDictionary* mesas = sis->getMesas();
    IIterator* it = mesas->getIterator();
    while (it->hasCurrent()) {
        Mesa* mesa = dynamic_cast<Mesa*>(it->getCurrent());
        if (mesa) {
            cout << "ID: " << mesa->getidMesa()
                 << " | Estado: " << (mesa->getEstado() == Activa ? "Activa" : "Inactiva")
                 << endl;
        }
        it->next();
    }
    delete it;
}

// void mostrarVentas(ISistema* sis) {
//     cout << "\n--- Ventas Activas ---\n";

//     // Obtengo el diccionario de ventas activas
//     IDictionary* ventas = sis->getVentas();
//     IIterator* itV = ventas->getIterator();
//     while (itV->hasCurrent()) {
//         Venta* venta = dynamic_cast<Venta*>(itV->getCurrent());
//         if (venta) {
//             // Solo las ventas de local contienen mesas
//             Local* ventaLocal = dynamic_cast<Local*>(venta);
//             if (ventaLocal) {
//                 IDictionary* mesasVenta = ventaLocal->getMesa();
//                 IIterator* itMV = mesasVenta->getIterator();
//                 while (itMV->hasCurrent()) {
//                     Mesa* mesaVenta = dynamic_cast<Mesa*>(itMV->getCurrent());
//                     if (mesaVenta) {
//                         int idMesa = mesaVenta->getidMesa();
//                         string nombreMozo = "";

//                         // Busco el mozo que tiene asignada esta mesa
//                         IDictionary* empleados = sis->getEmpleados();
//                         IIterator* itE = empleados->getIterator();
//                         while (itE->hasCurrent() && nombreMozo.empty()) {
//                             Mozo* mozo = dynamic_cast<Mozo*>(itE->getCurrent());
//                             if (mozo) {
//                                 ICollection* mesasMozo = mozo->getMesa();
//                                 IIterator* itMM = mesasMozo->getIterator();
//                                 while (itMM->hasCurrent()) {
//                                     Mesa* m = dynamic_cast<Mesa*>(itMM->getCurrent());
//                                     if (m && m->getidMesa() == idMesa) {
//                                         nombreMozo = mozo->getNombre();
//                                         break;
//                                     }
//                                     itMM->next();
//                                 }
//                                 delete itMM;
//                             }
//                             itE->next();
//                         }
//                         delete itE;

//                         // Imprimo cabecera de la venta
//                         cout << "ID Venta: " << venta->getIdVenta()
//                              << " | Descuento: " << venta->getDescuento()
//                              << " | ID Mesa: "    << idMesa
//                              << " | Estado: "     << (mesaVenta->getEstado() == Activa ? "Activa" : "Inactiva")
//                              << " | Mozo: "       << nombreMozo
//                              << endl;

//                         // Imprimo los productos de la venta
//                         ICollection* productos = venta->getVentaProductos();
//                         IIterator* itP = productos->getIterator();
//                         while (itP->hasCurrent()) {
//                             dtVentaProducto* vp = dynamic_cast<dtVentaProducto*>(itP->getCurrent());
//                             if (vp) {
//                                 cout << "  Producto: " << vp->getProducto()->getNombre()
//                                      << " | Cantidad: " << vp->getCantidad()
//                                      << endl;
//                             }
//                             itP->next();
//                         }
//                         delete itP;
//                     }
//                     itMV->next();
//                 }
//                 delete itMV;
//             }
//         }
//         itV->next();
//     }
//     delete itV;
// }

void mostrarVentas(ISistema* sis) {
    cout << "\n--- Ventas Activas ---\n";
    IDictionary* ventas = sis->getVentas();
    IDictionary* mesas = sis->getMesas();
    IDictionary* empleados = sis->getEmpleados();
    IIterator* it = ventas->getIterator();
    while (it->hasCurrent()) {
        Venta* venta = dynamic_cast<Venta*>(it->getCurrent());
        IIterator* itM = mesas->getIterator();
        while(itM->hasCurrent()) {
            Mesa* mesa = dynamic_cast<Mesa*>(itM->getCurrent());
            if (mesa && venta->esMesa(mesa->getidMesa())) {
                IIterator* itE = empleados->getIterator();
                while(itE->hasCurrent()) {
                    Mozo* empleado = dynamic_cast<Mozo*>(itE->getCurrent());
                    Mesa* mesaActual = dynamic_cast<Mesa*>(empleado->getMesa());
                    if (empleado && mesaActual && mesaActual->getidMesa() == mesa->getidMesa()) {
                        cout << "Mozo: " << empleado->getNombre() << endl;
                        break; // Salgo del bucle de empleados
                    }
                    itE->next();
                }
                delete itE;
                cout << "ID Venta: " << venta->getIdVenta()
                     << " | Descuento: " << venta->getDescuento()
                     << " | ID Mesa: " << mesa->getidMesa()
                     << " | Estado: " << (mesa->getEstado() == Activa ? "Activa" : "Inactiva")
                     << endl;
                ICollection* productos = venta->getVentaProductos();
                IIterator* itP = productos->getIterator();
                while (itP->hasCurrent()) {
                    ventaProducto* vp = dynamic_cast<ventaProducto*>(itP->getCurrent());
                    if (vp) {
                        cout << "  Producto: " << vp->getProducto()->getNombre()
                             << " | Cantidad: " << vp->getCantidad() << endl;
                    }
                    itP->next();
                }
                delete itP;
            }
            itM->next();
        }
        delete itM;
        it->next();
    }
    delete it;
}

void informacionProducto(ISistema* sis) {
    cout << "\n=== INFORMACIÓN DE UN PRODUCTO ===\n";

    while (true) {
        // 1) Mostrar listados de productos
        cout << "\nProductos disponibles:\n";
        // Listo sólo los productos comunes; si quieres menús también, añade listarMenus()
        ICollection* lista = sis->listarProductosComunes();
        IIterator* itp = lista->getIterator();
        while (itp->hasCurrent()) {
            dtProducto* dp = dynamic_cast<dtProducto*>(itp->getCurrent());
            cout << "  " << dp->getCodigo()
                 << " - " << dp->getNombre() << "\n";
            itp->next();
        }
        delete itp;

        // 2) Pido código a consultar
        cout << "\nIngrese código de producto (0 para cancelar): ";
        int codigo;
        cin >> codigo;
        if (codigo == 0) {
            cout << ">> Consulta cancelada.\n\n";
            break;
        }

        // 3) Consulto el DTO del producto
        dtProducto* dto = sis->informacionProducto(codigo);
        if (!dto) {
            cout << "¡Código inválido! Por favor reintente.\n";
            continue;  // vuelve a pedir código
        }

        // 4) Muestro datos básicos
        cout << "\nDatos actuales del producto:\n";
        cout << "  Código:      " << dto->getCodigo() << "\n";
        //cout << "  Descripción: " << dto->getDescripcion() << "\n";
        cout << "  Precio:      $" << dto->getPrecio() << "\n";


        ICollection* todasVentas = sis->listarVentas();

        // // 2) Imprime cuántas hay
        // cout << "Ventas en histórico: " 
        //     << todasVentas->getSize() 
        //     << endl;

        // 3) Itera con IIterator
        IIterator* itV = todasVentas->getIterator();
        // while (itV->hasCurrent()) {
        //     Venta* v = dynamic_cast<Venta*>( itV->getCurrent() );
        //     if (v) {
        //         // Cada Venta sabe cuántos ítems tiene
        //         int nItems = v->getVentaProductos()->getSize();
        //         cout << "  Venta " << v->getIdVenta() 
        //             << " tiene " << nItems 
        //             << " ítems\n";
        //     }
        //     itV->next();
        // }
        // delete itV;
        // 5) Calcular unidades vendidas (recojo todas las ventas confirmadas)
        int totalVend = 0;
        ICollection* ventas = sis->listarVentas();  
        IIterator* iv = ventas->getIterator();
        //cout << " antes del while" << endl;
        while (iv->hasCurrent()) {
            //cout << " dentro del while" << endl;
            Venta* v = dynamic_cast<Venta*>(iv->getCurrent());
            ICollection* items = v->getVentaProductos();
            IIterator* ii = items->getIterator();
            //cout << "antes del 2nd while" << endl;
            while (ii->hasCurrent()) {
                //cout << " dentro del 2nd while" << endl;
                ventaProducto* vp = dynamic_cast<ventaProducto*>(ii->getCurrent());
                // IIterator* ii = items->getIterator();
                // while (ii->hasCurrent()) {
                //     // 1) Intento castear a ventaProducto
                //     ventaProducto* vp = dynamic_cast<ventaProducto*>(ii->getCurrent());
                //     if (!vp) {
                //         cout << "[ERROR] elemento en venta no es ventaProducto, salto\n";
                //         ii->next();
                //         continue;
                //     }
                //     // 2) Compruebo que el puntero a Producto sea válido
                //     Producto* prod = vp->getProducto();
                //     if (!prod) {
                //         cout << "[ERROR] ventaProducto sin Producto asociado, salto\n";
                //         ii->next();
                //         continue;
                //     }
                //     // 3) Ahora ya puedo acceder con seguridad
                //     cout << "llega?" << endl;
                //     if (prod->getCodigo() == codigo) {
                //         cout << "[DEBUG] contando unidad, cantidad=" << vp->getCantidad() << "\n";
                //         totalVend += vp->getCantidad();
                //     }
                //     ii->next();
                // }
                // delete ii;
                if (vp->getProducto()->getCodigo() == codigo) {
                    //cout << "cuento <<" << endl;
                    //cout << vp->getCantidad() << endl;
                    totalVend += (vp->getCantidad());
                    //cout << vp->getCantidad() << endl;
                     //ESTO NO ESTARIA ANDANDO
                }
                ii->next();
            }
            delete ii;
            iv->next();
        }
        delete iv;
        cout << "  Unidades vendidas: " << totalVend << "\n";

        // 6) ¿Es un Menú? Distingo por dynamic_cast
        Producto* base = sis->buscarProducto(codigo);
        Menu* m = dynamic_cast<Menu*>(base);
        if (m) {
            cout << "\nDetalle del MENÚ (productos incluidos):\n";
            IDictionary* det = m->getCantidadSimple(); 
            IIterator* id = det->getIterator();
            while (id->hasCurrent()) {
                ventaProducto* vp = dynamic_cast<ventaProducto*>(id->getCurrent());
                Producto* p2 = vp->getProducto();
                cout << "    " << p2->getCodigo()
                     << " - " << p2->getNombre()
                     << "  x" << vp->getCantidad() << "\n";
                id->next();
            }
            delete id;
        }

        cout << "\n>> Fin de consulta.\n\n";
        break;
    }
}

void orden(ISistema* sis, int opcion) {
    
        switch(opcion) {
            case 1: {
                // --------- ALTA DE PRODUCTO ---------
                int tipo;
                // 1) Pregunta si es producto común o menú
                do {
                    cout << "\n*** ALTA DE PRODUCTO ***\n";
                    cout << "1) Producto común\n";
                    cout << "2) Menú\n";
                    cout << ">>> "; 
                    cin >> tipo;
                } while (tipo != 1 && tipo != 2);

                if (tipo == 1) {
                    // —— Producto común ——
                    string codigo, nombre;
                    float precio;
                    cout << "codigo: "; 
                    cin >> codigo;
                    cin.ignore(); 
                    cout << "Nombre: "; 
                    getline(cin, nombre);
                    cout << "Precio: "; 
                    cin >> precio;

                    // ingreso preliminar
                    sis->ingresarProductoComun(codigo, nombre, precio);

                    // confirmación o cancelación
                    int conf;
                    cout << "Confirmar alta de producto? (1=Sí, 2=No): "; 
                    cin >> conf;
                    if (conf == 1) {
                        sis->confirmarProducto();
                        cout << ">> Producto común dado de alta.\n";
                    } else {
                        sis->cancelarProducto();
                        cout << ">> Alta de producto cancelada.\n";
                    }
                }
                else {
                    // —— Menú ——
                    ICollection* prodsTemp = new List();
                    // bucle para agregar productos comunes al menú
                    bool agregar = true;
                    while (agregar) {
                        //1) Muestro productos comunes
                        cout << "\nProductos comunes disponibles:\n";
                        ICollection* lista = sis->listarProductos();
                        IIterator* it = lista->getIterator();
                        while (it->hasCurrent()) {
                            dtProducto* p = dynamic_cast<dtProducto*>(it->getCurrent());
                            cout << "  " << p->getCodigo()
                                << " - " << p->getNombre()
                                << " ($" << p->getPrecio() << ")\n";
                            it->next();
                        }
                        delete it;


                        // 2) Pido ID y cantidad
                        int idProd, cantidad;
                        cout << "ID producto a agregar: "; 
                        cin >> idProd;
                        cout << "Cantidad: "; 
                        cin >> cantidad;

                        // agrego al menú en construcción
                        sis->agregarProductoAMenu(idProd, cantidad);
                        ventaProducto* vp = new ventaProducto(cantidad, dynamic_cast<Producto*>(sis->listarProductos()));
                        prodsTemp->add(vp);
                        cout << ">> Producto agregado al menú.\n";
                        

                        // 3) ¿Sigo agregando?
                        int opc;
                        cout << "¿Agregar otro producto al menú? (1=Sí, 0=No): ";
                        cin >> opc;
                        agregar = (opc == 1);
                    }

                    // confirmo o cancel o del menú
                    int confM;
                    cout << "Confirmar alta del menú? (1=Sí, 2=No): "; 
                    cin >> confM;
                    if (confM == 1) {
                        cout << "Ingrese el ID del menú: ";
                        int idMenu;
                        cin >> idMenu;
                        sis->confirmarMenu(idMenu);
                        cout << ">> Menú dado de alta con éxito.\n";
                    } else {
                        sis->cancelarMenu();
                        cout << ">> Alta de menú cancelada.\n";
                    }
                    delete prodsTemp; // Liberar memoria de la colección temporal
                }
            } break;
            case 2: {
                string ci, nombre, telefono;
                cout << "CI: "; 
                cin >> ci;
                cin.ignore();

                cout << "Nombre: "; 
                getline(cin, nombre);

                cout << "Teléfono: "; 
                cin >> telefono;
                cin.ignore();

                // Pido la dirección como 3 campos
                string ciudad, calle, numero;
                cout << "Ciudad: "; 
                getline(cin, ciudad);

                cout << "Calle: "; 
                getline(cin, calle);

                cout << "Número: "; 
                getline(cin, numero);

                // Creo el objeto direccion y llamo al sistema
                direccion* dir = new direccion(ciudad, calle, numero);
                sis->altaCliente(ci, nombre, telefono, dir);
                cout << "Cliente dado de alta correctamente.\n";

                delete dir;  // libero la dirección
            } break;
            case 3:  {   // Alta de Empleado
                bool seguir = true;
                while (seguir) {
                    string nombre;
                    cout << "\nNombre del empleado: ";
                    // cin.clear(); // Limpiar el estado de error del cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nombre);

                    int tipo;
                    cout << "Tipo de empleado (1=Mozo, 2=Repartidor): ";
                    cin >> tipo;

                    if (tipo == 1) {
                        sis->altaMozo(nombre);
                        cout << "Mozo dado de alta correctamente.\n";
                    }
                    else if (tipo == 2) {
                        cout << "Transportes disponibles:\n";
                        cout << " - Moto\n";
                        cout << " - Bicicleta\n";
                        cout << " - Auto\n";

                        string transporte;
                        cout << "Elija tipo de transporte: ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, transporte);

                        sis->altaRepartidor(nombre, transporte);
                        cout << "Repartidor dado de alta correctamente.\n";
                    }
                    else {
                        cout << "Opción de tipo inválida.\n";
                    }

                    char resp;
                    cout << "¿Desea agregar otro empleado? (s/n): ";
                    cin >> resp;
                    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (resp != 's' && resp != 'S')
                        seguir = false;
                }
                mostrarEmpleados(sis);
            } break;
            case 4: {  // Asignar mesas a mozos
                sis->asignarMesaAMozo();
                break;
            } break;
            case 5: {
                // --------- INICIAR VENTA EN MESAS ---------
                cout << "\n*** INICIAR VENTA EN MESAS ***\n";
                int idMozo;
                cout << "ID de mozo: ";
                cin >> idMozo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // 1) Registramos al mozo
                if (!sis->ingresarIdentificador(idMozo)) {
                    cout << "ID inválido o mozo no asignado.\n";
                    break;
                }

                // 2) Mostrar mesas asignadas y sin venta
                ICollection* disp = sis->mostrarMesasAsignadasSinVenta();
                cout << "Mesas disponibles:\n";
                {
                    IIterator* it = disp->getIterator();
                    while (it->hasCurrent()) {
                        Integer* mId = dynamic_cast<Integer*>(it->getCurrent());
                        cout << "  - Mesa " << mId->getValue() << "\n";
                        it->next();
                    }
                    delete it;
                }
                delete disp;

              // 3) Bucle de selección de mesas
                char seguir = 's';
                while (seguir=='s' || seguir=='S') {
                    int idMesa;
                    cout << "ID de mesa a agregar: ";
                    cin >> idMesa;
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');

                    if (!sis->seleccionarMesas(idMesa)) {
                        // mensaje de error ya lo imprime la función
                        continue;
                    }

                    cout << "¿Agregar otra mesa? (s/n): ";
                    cin >> seguir;
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }

                // 4) Mostrar lo seleccionado
                sis->mostrarMesasSeleccionadas();

                // 5) Confirmar o cancelar
                char confirma;
                cout << "¿Confirmar venta? (s/n): ";
                cin >> confirma;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (confirma == 's' || confirma == 'S') {
                    sis->confirmarVenta(idMozo);
                } else {
                    sis->cancelarVentaActiva();
                }

                //mostrarVentas(sis); // Mostrar ventas activas después de iniciar una
            } break;
            case 6: {
                cout << "\n*** AGREGAR PRODUCTO A UNA VENTA ***\n";

                // 1) Pedir mesa y comenzar la venta
                int idMesa;
                cout << "ID de la mesa con venta activa: ";
                cin >> idMesa;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if ( !sis->ingresarVenta(idMesa) ) {
                    cout << "No hay venta activa para la mesa " << idMesa << ".\n";
                    break;
                }
                cout << "Venta iniciada para la mesa " << idMesa << ".\n";

                // 2) Mostrar productos disponibles
                ICollection* disponibles = sis->mostrarProductosDisponibles();
                cout << "\nProductos disponibles:\n";
                {
                    IIterator* it = disponibles->getIterator();
                    while (it->hasCurrent()) {
                        dtProducto* p = dynamic_cast<dtProducto*>(it->getCurrent());
                        cout << "  - Código: " << p->getCodigo()
                            << " | " << p->getNombre()
                            << " ($" << p->getPrecio() << ")\n";
                        it->next();
                    }
                    delete it;
                }
                delete disponibles;

                // 3) Bucle de selección de producto y cantidad
                char seguir = 's';
                while (seguir == 's' || seguir == 'S') {
                    string codigoProd;
                    int cantidad;
                    cout << "\nCódigo de producto a agregar: ";
                    cin >> codigoProd;
                    cout << "Cantidad: ";
                    cin >> cantidad;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if(sis->seleccionarProducto(codigoProd) == 0) {
                        cout << "Producto no encontrado. Por favor, intente nuevamente.\n";
                        continue;  // Vuelve a pedir el código
                    }
                    else
                        sis->seleccionarProducto(codigoProd);

                    // 4) Confirmar o cancelar esta línea
                    char conf = 'n';
                    cout << "Confirmar agregado? (s/n): ";
                    cin >> conf;
                    if (conf == 's' || conf == 'S') {
                        int cod = atoi(codigoProd.c_str());
                        if (!sis->productoEnVenta(cod, idMesa)) {
                            sis->agregarProducto(idMesa, cod, cantidad);
                            cout << ">> Producto agregado a la venta.\n";
                        } else {
                            sis->aumentarCantProducto(idMesa, cod, cantidad);
                            cout << ">> Cantidad de producto incrementada en la venta.\n";
                        }
                    } else {
                        cout << ">> Producto no agregado.\n";
                    }

                    cout << "¿Desea agregar otro producto? (s/n): ";
                    cin >> seguir;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                // 5) Preguntar si se desea finalizar la venta
                char fin = 'n';
                cout << "\n¿Desea finalizar la venta para la mesa " << idMesa << "? (s/n): ";
                cin >> fin;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (fin == 's' || fin == 'S') {
                    sis->finalizarVenta(idMesa);
                    cout << ">> Venta finalizada para la mesa " << idMesa << ".\n";
                } else {
                    cout << ">> Venta pendiente. Puede seguir agregando productos más tarde.\n";
                }
            } break;
            case 8: {
                cout << "\n*** FACTURACIÓN DE UNA VENTA ***\n";

                // 1) Registro del mozo
                int idMozo;
                cout << "ID de mozo: ";
                cin >> idMozo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (!sis->ingresarIdentificador(idMozo)) {
                    cout << "ID de mozo inválido o no asignado.\n";
                    break;
                }

                // 2) Finalizar la venta para la mesa
                int idMesa;
                cout << "ID de mesa a facturar: ";
                cin >> idMesa;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                sis->finalizarVenta(idMesa);  // void

                // 3) Mostrar detalle preliminar
                cout << "\nDetalle de la venta:\n";
                sis->mostrarVenta(idMesa);    // el sistema imprime líneas y subtotales

                // 4) Aplicar descuento opcional
                char aplica;
                cout << "\n¿Desea aplicar descuento? (s/n): ";
                cin >> aplica;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (aplica=='s' || aplica=='S') {
                    float pct;
                    cout << "Ingrese % de descuento (0–100): ";
                    cin >> pct;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    // Reemplazamos idVenta por idMesa
                    sis->ingresarDescuento(pct, idMesa);
                }

                // 5) Mostrar la factura final
                cout << "\n--- FACTURA FINAL ---\n";
                sis->mostrarFactura(idMesa, idMozo);
            } break;
            case 9: {
                cout << "\n*** VENTA A DOMICILIO ***\n";

                // 1) Pedir teléfono del cliente y datos (si no existe, altaCliente detectará y registrará)
                string ci, nombre, telefono;
                cout << "Cedula del cliente: ";
                cin >> ci;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if(!sis->existeCliente(ci)){
                    cout << "El cliente no esta registrado \n";
                    cout << "Nombre del cliente: ";
                    getline(cin, nombre);

                    cout << "Teléfono de contacto (repetir): ";
                    getline(cin, telefono);

                    // Dirección
                    string ciudad, calle, numero;
                    cout << "Ciudad: ";
                    getline(cin, ciudad);
                    cout << "Calle: ";
                    getline(cin, calle);
                    cout << "Número: ";
                    getline(cin, numero);

                    direccion* dir = new direccion(ciudad, calle, numero);
                    sis->altaCliente(ci, nombre, telefono, dir);

                    delete dir;  // Liberar memoria de la dirección
                }

                // 2) Bucle de agregación de productos
                ICollection* items = new List();
                char seguirProd = 's';
                while (seguirProd=='s' || seguirProd=='S') {
                    // Mostrar catálogo
                    ICollection* cat = sis->listarProductos();
                    cout << "\nProductos disponibles:\n";
                    {
                        IIterator* it = cat->getIterator();
                        while (it->hasCurrent()) {
                            dtProducto* p = dynamic_cast<dtProducto*>(it->getCurrent());
                            cout << "  - Código: " << p->getCodigo()
                                << " | " << p->getNombre()
                                << " ($" << p->getPrecio() << ")\n";
                            it->next();
                        }
                        delete it;
                    }
                    delete cat;

                    int cod, cant;
                    cout << "\nCódigo de producto a agregar: ";
                    cin >> cod;
                    cout << "Cantidad: ";
                    cin >> cant;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    // Construyo el dtProducto de línea y lo guardo
                    dtProducto* dtp = sis->informacionProducto(cod);
                    if (dtp) {
                        dtVentaProducto* vp = new dtVentaProducto(dtp, cant);
                        items->add(vp);
                        cout << "  → Agregado " << cant << "×" << dtp->getNombre() << "\n";
                    } else {
                        cout << "  !! Producto no encontrado, se omite.\n";
                    }

                    cout << "¿Agregar otro producto? (s/n): ";
                    cin >> seguirProd;
                    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                // 3) Seleccionar repartidor
                char requiereEntrega;
                cout << "\n¿Pedido a domicilio? (s/n): ";
                cin >> requiereEntrega;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                bool s = false;
                int idRepartidor = 0;
                if (requiereEntrega=='s' || requiereEntrega=='S') {
                    s = true;
                    cout << "\nRepartidores disponibles:\n";
                    sis->listarRepartidor();
                    cout << "\nSeleccione el ID del repartidor: ";
                    cin >> idRepartidor;
                }

                // 4) Confirmar o cancelar todo el pedido
                char conf;
                cout << "\nConfirmar pedido a domicilio? (s/n): ";
                cin >> conf;
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (conf=='s' || conf=='S') {
                    // 5) Llamo a la función de negocio

                    dtVenta* factura = sis->ventaDomicilio(
                        ci,             // ciCliente
                        (requiereEntrega=='s'), // retira = false → true si requiere entrega
                        idRepartidor,   // idRepartidor
                        items           // items seleccionados
                    );

                    // 6) Imprimo la factura devuelta por el sistema
                    if (factura) {
                        // ID y fecha/hora
                        cout << "\n--- FACTURA A DOMICILIO ---\n";
                        cout << "ID Venta: " << factura->getIdVenta() << "\n";
                        cout << "Fecha : " << factura->getFactura()->getFecha()->getDia() << "/"
                            << factura->getFactura()->getFecha()->getMes() << "/"
                            << factura->getFactura()->getFecha()->getAnio() << "\n"
                        << "Hora : " << factura->getFactura()->getHora()->getOra() << ":"
                        << factura->getFactura()->getHora()->getMinuto() << "\n";
                        if(s){
                            cout << "Repartidor ";
                            sis->mostrarInfoRepartidor(idRepartidor);
                        }
                        // Detalle de líneas
                        cout << left
                            << setw(20) << "Producto"
                            << setw(8)  << "Cant."
                            << setw(10) << "Precio"
                            << setw(10) << "Total\n";
                        cout << string(50,'-') << "\n";
                        IIterator* itF = items->getIterator();
                        double sub = 0;
                        
                        while (itF->hasCurrent()) {
                            dtVentaProducto* vp = dynamic_cast<dtVentaProducto*>(itF->getCurrent());
                            double pu = vp->getProducto()->getPrecio();
                            int    ct = vp->getCantidad();
                            double tl = pu * ct;
                            sub += tl;
                            cout << left
                                << setw(20) << vp->getProducto()->getNombre()
                                << setw(8)  << ct
                                << "$"      << setw(8) << fixed << setprecision(2) << pu
                                << "$"      << setw(8) << fixed << setprecision(2) << tl
                                << "\n";
                            itF->next();
                        }
                        delete itF;

                        // Totales
                        float descuento = factura->getDescuento();
                        float total = sub * (1 - descuento / 100.0);
                        float totalIVA = total * (1 + (factura->getFactura()->getIva() / 100));
                        cout << string(50,'-') << "\n"
                            << "Subtotal:    $" << fixed << setprecision(2) << sub << "\n"
                            << "Descuento:   "    << descuento << "%\n"
                            << "Total:       $" << fixed << setprecision(2) << total << "\n"
                            << "Total + IVA: $" << fixed << setprecision(2) << totalIVA << "\n\n";
                        cout << "Gracias por su compra!\n";

                        IIterator* item = items->getIterator();
                        while (item->hasCurrent()) {
                            delete item->getCurrent();
                            item->next();
                        }
                        delete item;
                        delete items; // Liberar la colección de productos
                        delete factura;
                    } else {
                        cout << "Error al generar la factura.\n";
                    }
                } else {
                    // cancelar y liberar
                    sis->cancelarAccion();
                    cout << "\nPedido cancelado.\n";
                }

                // Si no confirmamos, Items y Dir deben liberarse:
                if (!(conf=='s' || conf=='S')) {
                    IIterator* itI = items->getIterator();
                    while (itI->hasCurrent()) {
                        delete itI->getCurrent();
                        itI->next();
                    }
                    delete itI;
                    delete items;
                }
            } break;
            case 11: {
                informacionProducto(sis);
                break;
            }
            case 13: {
                cout << "\n*** BAJA DE PRODUCTO ***\n";
                // 1) Listar todos los productos
                ICollection* todos = sis->listarProductos();
                cout << "Productos disponibles:\n";
                {
                    IIterator* it = todos->getIterator();
                    while (it->hasCurrent()) {
                        dtProducto* p = dynamic_cast<dtProducto*>(it->getCurrent());
                        cout << "  - Código: " << p->getCodigo()
                            << " | " << p->getNombre()
                            << " ($" << p->getPrecio() << ")\n";
                        it->next();
                    }
                    delete it;
                }
                delete todos;


                // 2) Leer el código como string (para tu API) y convertir a int
                string codigoStr;
                cout << "Ingrese el código del producto a eliminar: ";
                cin >> codigoStr;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                int codigoInt = atoi(codigoStr.c_str());

                // 3) Verificar existencia comparando ints
                bool encontrado = false;
                todos     = sis->listarProductos();
                IIterator* it2 = todos->getIterator();
                while (it2->hasCurrent()) {
                    dtProducto* p = dynamic_cast<dtProducto*>(it2->getCurrent());
                    // p->getCodigo() es int, así que comparamos directamente
                    if (p->getCodigo() == codigoInt) {
                        encontrado = true;
                        break;
                    }
                    it2->next();
                }
                delete it2;
                delete todos;

                if (!encontrado) {
                    cout << "Producto con código " << codigoInt 
                        << " no encontrado. Operación cancelada.\n";
                    break;  // Salimos del case sin pedir confirmación
                }

                // 4) El producto existe: seleccionamos y pedimos confirmación
                sis->seleccionarProducto(codigoStr);
                int conf;
                cout << "Confirmar baja de producto? (1=Sí, 2=No): ";
                cin >> conf;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (conf == 1) {
                    sis->eliminarProducto();
                    //cout << ">> Producto eliminado correctamente.\n";
                    //cout << ">> Producto eliminado correctamente.\n";
                } else if(conf == 2) {
                    sis->cancelarBajaProducto();
                    //cout << ">> Baja de producto cancelada.\n";
                    //cout << ">> Baja de producto cancelada.\n";
                }
            } break;
            

        }
}

int main() {
    ISistema* sis = factory::getSistema();
    int opcion;
    cargarDatosPrueba(sis); // Cargar datos de prueba al inicio
    

    do {
        cout << "===== MENÚ PRINCIPAL =====\n";
        cout << "1) Alta Producto\n";   //Completo
        cout << "2) Alta Cliente\n";    //Completo
        cout << "3) Alta Empleado\n";   //Completo
        cout << "4) Asignar mesas a mozos\n";   //ANDA SI NO TIENE VENTAS ACTIVAS PRECARGADAS
        cout << "5) Iniciar venta en mesas\n";  //Revisar
        cout << "6) Agregar producto a una venta\n"; //GOD
        cout << "7) Quitar producto de una venta\n";
        cout << "8) Facturacion de una venta\n"; //Completo
        cout << "9) Venta domicilio\n"; //TESTEAR
        cout << "10) Ventas de un mozo\n";
        cout << "11) Información de un producto\n"; //ANDA
        cout << "12) Resumen de facturación de un dia\n";
        cout << "13) Baja de producto\n";   //Completo
        cout << "0) Salir\n";
        cout << ">>> "; cin >> opcion;
        
        if (opcion < 0 || opcion > 13) {
            cout << "Opción inválida. Intente nuevamente.\n";
            continue;
        }

        orden(sis, opcion);

    } while(opcion != 0);
    return 0;
}
