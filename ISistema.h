#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <iostream>
#include <string>

#include "DataTypes/dtProducto.h"
#include "DataTypes/dtVenta.h"
#include "DataTypes/dtVentaProducto.h"
#include "producto.h"
#include "DataTypes/direccion.h"
#include "ICollection/interfaces/ICollection.h"
#include "ICollection/interfaces/IDictionary.h"

using namespace std;

class ISistema {
    public:
        ~ISistema();
        virtual IDictionary* getCliente() = 0;
        virtual IDictionary* getEmpleados() = 0;
        virtual IDictionary* getMesas() = 0;
        virtual IDictionary* getProductos() = 0;
        virtual IDictionary* getVentas() = 0;
        virtual bool hayProductos() = 0;
        virtual int ingresarProductoComun(string codigo, string nombre, float precio) = 0;
        virtual void confirmarProducto() = 0;
        virtual void cancelarProducto() = 0; 
        virtual ICollection* listarProductosComunes() = 0;
        virtual void agregarProductoAMenu(int codigo, int cantidad) = 0;
        virtual void confirmarMenu(int codigo) = 0;
        virtual void cancelarMenu() = 0;
        virtual ICollection* listarProductos() = 0;
        virtual int seleccionarProducto(string codigo) = 0;
        virtual void eliminarProducto() = 0;
        virtual void cancelarBajaProducto() = 0;
        virtual bool ingresarIdentificador(int idMozo) = 0;
        virtual ICollection* mostrarMesasAsignadasSinVenta() = 0;
        virtual bool seleccionarMesas(int idMesa) = 0;
        virtual void mostrarMesasSeleccionadas() = 0;
        virtual bool sinVenta() = 0;
        virtual void confirmarVenta(int idMozo) = 0;
        virtual void cancelarVenta() = 0;
        virtual void cancelarVentaActiva() = 0;
        virtual int finalizarVenta(int idMesa) = 0;
        virtual ICollection* mostrarVenta(int idMesa) = 0;
        virtual void ingresarDescuento(float porcentaje, int idVenta) = 0;
        virtual dtVenta* mostrarFactura(int idVenta, int idMozo) = 0;
        virtual bool ingresarVenta(int idMesa) = 0;
        virtual ICollection* mostrarProductosDisponibles() = 0;
        //virtual void seleccionarProducto(int codigo,int cantidad) = 0;
        virtual void agregarProducto(int idMesa,int idProducto, int cantidad) = 0;
        virtual void agregarProductoDomicilio(ICollection* vp, int idVenta) = 0;
        virtual void aumentarCantProducto(int idMesa, int idProducto , int cantidad) = 0;
        virtual void salir() = 0;
        virtual void mostrarConfirmacion() = 0;
        virtual void ingresarMesa(int idMesa) = 0;
        virtual ICollection* mostrarProductosEnVenta() = 0;
        virtual void SeleccionarProductoYCantidad(string producto, int cantidad) = 0;
        virtual void EliminarProducto(int idVenta) = 0;
        virtual void cancelarAccion() = 0;
        //virtual void mostrarSeleccionadas() = 0;S
        virtual int altaCliente(string ci, string nombre, string telefono, direccion* direccion) = 0;
        virtual void altaMozo(string nombre) = 0;
        virtual void altaRepartidor(string nombre, string transporte) = 0;
        virtual void asignarMesaAMozo() = 0;
        virtual dtProducto* informacionProducto(int codigoProducto) = 0;
        virtual ICollection* ventasDeMozo(int idMozo) = 0;
        virtual dtVenta* ventaDomicilio(const string& ciCliente, bool retira, int idRepartidor, ICollection* items) = 0;
        virtual void resumenFacturacion(string fechaISO) = 0;
        virtual void asignarMesaAMozo(int numeroMesa, int idMozo) = 0;
        virtual bool productoEnVenta(int idProducto, int idMesa) = 0;
        virtual Producto* buscarProducto(int codigo) = 0;
        virtual ICollection* listarVentas() = 0;
        virtual void solicitarConsultaFacturacionDia(fecha f) = 0;
        virtual ICollection* obtenerDatosFacturacion(fecha f) = 0;
        virtual ICollection* obtenerDatosVentaDomicilio(fecha f) = 0;
        virtual void mostrarInforme(ICollection* ventas, float total) = 0;
        virtual void listarRepartidor() = 0;
        virtual bool existeCliente(const string& ciCliente) = 0; // Verifica si un cliente existe por su cédula
        virtual void mostrarInfoRepartidor(int idRepartidor) = 0;
        virtual ICollection* listarMozos() = 0;
        virtual ICollection* ventasDeMozo(int idMozo, fecha* desde, fecha* hasta) = 0;
        // parte 12 la secuela
};


#endif //ISISTEMA_H