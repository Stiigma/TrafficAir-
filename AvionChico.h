#pragma once
#include "VehiculoAereo.h"
class AvionChico : public VehiculoAereo {
protected:
    int capacidadPersonas;
    int combustibleMaximo;
    float tiempoMaximoEnAire;
    float tiempoDescargarPersonas;
    float tiempoInicioDescarga;
    int combustibleActual;
    float tiempoCargarCombustible;
    float tiempoInicioCombustible;
    int personasActuales;
    float tiempoCargarPersonas;
    float tiempoInicioCarga;
    static Texture2D backgroundTexture; 

public:
    AvionChico();
    ~AvionChico(); 

    void Actualizar() override;
    void Reabastecimiento() override;
    void Dibujar() override;
    static void CargarTextura(const std::string& ruta); 
    static void DescargarTextura(); 
    int getPerActuales() { return personasActuales; }
    void descargarPersonas();
    void cargarCombustible();
    void cargarPersonas();
};

