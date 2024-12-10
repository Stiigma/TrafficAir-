#pragma once

#include "raylib.h"
#include <string>
#include "AvionChico.h"
#include  "Terminal.h"
#include <stack>
class TrafficAir {
protected:
    int anchoVentana;
    int altoVentana;
    int rondaActual;
    int maxRondas;
    float duracionRonda;
    float tiempoInicioRonda;
    float tiempoUltimaExtraccion;
    std::string titulo;
    bool juegoCorriendo;
    Terminal* terminal;
    std::stack<VehiculoAereo*> pilaAviones;
    std::stack<VehiculoAereo*> avionesProcesados;
    std::vector<VehiculoAereo*> avionesActivos;
    Texture2D backgroundTexture; // Textura para la imagen de fondo

public:
    // Constructor
    TrafficAir(int ancho, int alto);

    // Destructor
    ~TrafficAir();

    // Inicialización
    void Inicializar();

    // Finalización
    void Finalizar();

    // Dibujar la pantalla
    void Dibujar();

    // Ciclo principal del juego
    void Ejecutar();

    void FinalizarRonda();

    void HacerAterrizarAvionSeleccionado();

    void IniciarRonda();
    void CargarAvionesEnPila(int cantidad);


};