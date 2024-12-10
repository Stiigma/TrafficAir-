
#pragma once
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include "Enums.h"
class VehiculoAereo {
protected:
    Vector2 posicion;    
    float velocidad;   
    Vector2 dimension;        
    EstadoVehiculo estado;
    float tiempoInicio;
    float tiempoReabastecimiento;
    float anguloRotacion;
    std::string nombre;
    float tiempoEnAire;
    Vector2 Estacion;
public:
    // Constructor
    VehiculoAereo();


     // Métodos abstractos
    virtual void Aterrizar(Vector2 inicio, Vector2 fin);
    virtual void Despegar(Vector2 inicio, Vector2 fin);
    bool HaTerminadoProcedimiento();
    virtual void Actualizar();
    float getTiempoRestanteVuelo();
    virtual void Dibujar();
    virtual void Reabastecimiento();
    virtual void EnAire();
    std::vector<std::string> get_atributoStr();
    std::string getEstadoStr();
    void AsignarEstacion(Vector2 estacion);
    void ReiniciarTiempoInicio();
    float getPosicionX() { return posicion.x; }
    float getPosicionY() { return posicion.x; }
    Vector2 getPosicion() { return posicion; }
    void getPosicionX(float x) { posicion.x = x; }
    void getPosicionY(float y) { posicion.y = y; }
    void getPosicion(Vector2 posicion) { this -> posicion = posicion; }
    virtual EstadoVehiculo getEstado() { return estado; }
    void setEstado(EstadoVehiculo nuevo_estado) { estado = nuevo_estado; }
    std::string getNombre() { return nombre; }
    virtual ~VehiculoAereo() {}
};


