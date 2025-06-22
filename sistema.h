#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

#include "DataTypes/dtProducto.h"
#include "DataTypes/dtVenta.h"
#include "DataTypes/dtLocal.h"
#include "DataTypes/dtVentaProducto.h"
#include "DataTypes/dtCantidadSimple.h"
#include "DataTypes/dtMenu.h"
#include "DataTypes/direccion.h"
#include "DataTypes/dtSimple.h"
#include "DataTypes/dtDomicilio.h"
#include "ICollection/interfaces/IDictionary.h"
#include "ICollection/interfaces/ICollection.h"
#include "ICollection/collections/OrderedDictionary.h"
#include "ICollection/collections/List.h"
#include "ICollection/Integer.h"
#include "ICollection/String.h"
#include "ISistema.h"
#include "mesa.h"
#include "menu.h"
#include "venta.h"
#include "simple.h"
#include "cantidadSimple.h"
#include "cliente.h"
#include "mozo.h"
#include "repartidor.h"
#include "domicilio.h"
#include "local.h"

#include <typeinfo>
#include <iomanip> // Para std::setprecision

using namespace std;

class Sistema : public ISistema {
    private:
        Sistema();
        static Sistema* instance;
        IDictionary* productos;
        IDictionary* mesas;
        IDictionary* ventas;
        IDictionary* ventasActivas;
        IDictionary* empleados;    //los que tienen id deberian de ser iDictionary para no recorrer uno por uno
        IDictionary* clientes; //los clientes que se pueden agregar a una venta
        IDictionary* cantidadSimpleTemporal; // Cantidad simple temporal para agregar a un menú
        ICollection* mesasSeleccionadas; //para las mesas que se seleccionan para una venta
        dtSimple* productoComun;
        dtVentaProducto* productoTemporal; // Venta producto temporal para quitar a una venta
        int idMozoSeleccionado;
        int idMesaSeleccionada;
        int idProductoSeleccionado;
        int cantProductosSeleccionados;
        int idVenta; // ID de la venta, se incrementa con cada nueva venta
        int codigoProductoSeleccionado; // Código del producto seleccionado para agregar a la venta
        int cantMozos; // Cantidad de mozos registrados
        fecha fechaConsulta;
    public:
        static Sistema * getInstance();
        ~Sistema();
        IDictionary* getCliente();
        IDictionary* getEmpleados();
        IDictionary* getProductos();
        IDictionary* getMesas();
        IDictionary* getVentas();
        bool hayProductos();
        int ingresarProductoComun(string codigo, string nombre, float precio);
        void confirmarProducto();
        void cancelarProducto();
        ICollection* listarProductosComunes();
        void agregarProductoAMenu(int codigo, int cantidad);
        void confirmarMenu(int codigo);
        void cancelarMenu();
        ICollection* listarProductos();
        //void seleccionarProducto(string codigo, int cantidad ;
        void eliminarProducto();
        void cancelarBajaProducto();
        bool ingresarIdentificador(int idMozo);
        ICollection* mostrarMesasAsignadasSinVenta();
        bool seleccionarMesas(int idMesa);
        void mostrarMesasSeleccionadas();
        bool sinVenta();
        void confirmarVenta(int idMozo);
        void cancelarVenta();
        void cancelarVentaActiva();
        int finalizarVenta(int idMesa);
        ICollection* mostrarVenta(int idMesa);
        void ingresarDescuento(float porcentaje, int idVenta);
        dtVenta* mostrarFactura(int idVenta, int idMozo);
        bool ingresarVenta(int idMesa);
        ICollection* mostrarProductosDisponibles();
        int seleccionarProducto(string codigo);
        void agregarProducto(int idMesa,int idProducto, int cantidad);
        void agregarProductoDomicilio(ICollection* vp, int idVenta);
        void aumentarCantProducto(int idMesa, int idProducto , int cantidad);
        void salir();
        void ingresarMesa(int idMesa);
        ICollection* mostrarProductosEnVenta();
        void SeleccionarProductoYCantidad(string producto, int cantidad);
        void EliminarProducto(int idVenta);
        void cancelarAccion();
        //void mostrarSeleccionadas();
        void mostrarConfirmacion();
        int altaCliente(string ci, string nombre, string telefono, direccion* direccion);
        void altaMozo(string nombre);
        void altaRepartidor(string nombre, string transporte);
        void asignarMesaAMozo();
        dtProducto* informacionProducto(int codigoProducto);
        ICollection* ventasDeMozo(int idMozo);
        dtVenta* ventaDomicilio(const string& ciCliente, bool retira, int idRepartidor, ICollection* items);
        void resumenFacturacion(string fechaISO);
        void asignarMesaAMozo(int numeroMesa, int idMozo);
        Producto* buscarProducto(int codigo);
        bool productoEnVenta(int idProducto, int idMesa); // Verifica si un producto está en venta, opcionalmente en una mesa específica
        ICollection* listarVentas();
        // funciones para parte 12
        void solicitarConsultaFacturacionDia(fecha f);
        ICollection* obtenerDatosFacturacion(fecha f);
        ICollection* obtenerDatosVentaDomicilio(fecha f);
        void mostrarInforme(ICollection* ventas, float total);
        void listarRepartidor();
        bool existeCliente(const string& ciCliente);
        void mostrarInfoRepartidor(int idRepartidor);
        ICollection* listarMozos();
        ICollection* ventasDeMozo(int idMozo, fecha* desde, fecha* hasta);
        ICollection* obtenerVentasDelDia(fecha f);
};


#endif //SISTEMA_H