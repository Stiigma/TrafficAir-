#pragma once
#include "VehiculoAereo.h"
class AvionMediano : public VehiculoAereo
{
protected: 
    static Texture2D backgroundTexture; 
    int capacidadPersonas;
    int combustibleMaximo;
    float tiempoMaximoEnAire;
    float tiempoDescargarPersonas;
    float tiempoCargarCombustible;
    float tiempoCargarPersonas;
    int personasActuales;
    int combustibleActual;
    float tiempoInicioDescarga;
    float tiempoInicioCombustible;
    float tiempoInicioCarga;


public:
    // Constructor
    AvionMediano()
        : VehiculoAereo(),
        capacidadPersonas(50),
        combustibleMaximo(200),
        tiempoMaximoEnAire(10.0f),
        tiempoDescargarPersonas(7.0f),
        tiempoCargarCombustible(7.0f),
        tiempoCargarPersonas(7.0f),
        personasActuales(50),
        combustibleActual(0),
        tiempoInicioDescarga(0.0f),
        tiempoInicioCombustible(0.0f),
        tiempoInicioCarga(0.0f) {
        velocidad = 60.0f; // Puedes ajustar si es necesario
        nombre = "Avion Mediano";
        tiempoReabastecimiento = tiempoDescargarPersonas + tiempoCargarCombustible + tiempoCargarPersonas;
    }

    // Destructor
    ~AvionMediano() {}
    void Actualizar() override;
    void Reabastecimiento() override;
    void Dibujar() override;
    void descargarPersonas();
    void cargarCombustible();
    void cargarPersonas();
    static void CargarTextura(const std::string& ruta);
    static void DescargarTextura();
};
