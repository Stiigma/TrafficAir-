#pragma once

#include "raylib.h"
#include <string>
#include <vector>
#include "InformacionAvion.h"
#include <iostream>
using std::vector;
constexpr auto DIF_EST_X = 12.0f;;
constexpr auto ESTGENERAL_Y = 1080.0f;;
constexpr auto Est1_XF = 55.0f;;
constexpr auto EST2_XF = 300.0f;;
constexpr auto EST3_XF = 842.0f;;
constexpr auto EST4_XF = 1125.0f;;
constexpr auto EST5_XF = 1520.0f;;
constexpr auto EST6_XF = 1680.0f;;
constexpr auto Est1_YF = 400.0f;;
constexpr auto EST2_YF = 460.0f;;
constexpr auto EST3_YF = 485.0f;;
constexpr auto EST4_YF = 580.0f;;
constexpr auto EST5_YF = 450.0f;;
constexpr auto EST6_YF = 230.0f;;

#include "VehiculoAereo.h"

class Terminal {
protected:
    vector<InformacionAvion> cuadros;
    vector<Rectangle> botones;
    int numeroSeleccionado;
    int cuadroSeleccionado;
    std::vector<VehiculoAereo*> aviones;
    vector<Rectangle> cuadrosSeleccion;
    vector<bool> cuadrosActivos;
    VehiculoAereo* avionSeleccionado;
    vector<bool> estacionesOcupadas;
    bool boton7Presionado;
public:
    Terminal() : numeroSeleccionado(0), cuadroSeleccionado(-1), avionSeleccionado(nullptr) {

        float xInicio = 490.0f;
        float yInicio = 811.0f;


        float anchoCuadro = 264.0f;
        float altoCuadro = 120.0f;


        float offsetHorizontal = 275.0f;
        float offsetVertical = 130.0f;

        botones = {
            {1290, 725, 45, 45},
            {1350, 723, 50, 50},
            {1416, 723, 50, 50},
            {1479, 724, 50, 50},
            {1542, 723, 50, 50},
            {1606, 721, 50, 50},
            {1690, 704, 85, 85},
            {1803, 704, 85, 85}
        };
        for (int fila = 0; fila < 3; fila++) {
            for (int columna = 0; columna < 5; columna++) {
                if (cuadrosSeleccion.size() >= 10) break;
                float x = xInicio + columna * offsetHorizontal;
                float y = yInicio + fila * offsetVertical;
                cuadrosSeleccion.emplace_back(Rectangle{ x, y, anchoCuadro, altoCuadro });
                cuadrosActivos.push_back(false);
                aviones.push_back(nullptr);
                cuadros.emplace_back(
                    x, y, anchoCuadro, altoCuadro,
                    std::vector<std::string>{
                    " ",
                        " ",
                        " ",
                        " ",
                        " "
                },
                    LIGHTGRAY
                );

                estacionesOcupadas.push_back(false);
            }
        }
        
    }


    void DibujarInformacionAvionSeleccionado() {
        if (avionSeleccionado) { // Si hay un avión seleccionado
            std::vector<std::string> datosAvion = avionSeleccionado->get_atributoStr();

            // Dimensiones del cuadro de información
            float xInicio = 872.0f;
            float yInicio = 700.0f;
            float anchoCuadro = 220.0f;
            float altoCuadro = 106.0f;



            // Definir offsets para los textos
            std::vector<float> offsetsX = { 97.0f, 147.0f, 100.0f, 88.0f, 160.0f }; // Todos alineados a la izquierda
            std::vector<float> offsetsY = { 10.0f, 25.0f, 38.0f, 50.0f, 78.0f }; // Posiciones verticales predefinidas


            // Dibujar cada línea con su offset
            for (size_t i = 0; i < datosAvion.size(); ++i) {
                DrawText(
                    (datosAvion[i]).c_str(),
                    xInicio + offsetsX[i],              // Offset horizontal
                    yInicio + offsetsY[i],              // Offset vertical
                    9,                                 // Tamaño del texto
                    BLACK                               // Color del texto
                );
            }
        }
        else {
            // Mostrar mensaje si no hay avión seleccionado
            DrawText("No hay avion seleccionado", 50, 50, 20, RED);
        }
    }

    void DetectarBoton7Presionado() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 posicionRaton = GetMousePosition();

            // Verifica si el ratón está sobre el botón 7
            if (botones.size() >= 7 && CheckCollisionPointRec(posicionRaton, botones[6])) {
                boton7Presionado = true; // Actualiza el estado del botón 7
            }
           
        }
    }

    bool ObtenerBitAterrizar() { return boton7Presionado; }
    void ActivarCuadro(int indice, bool activo) {
        if (indice >= 0 && indice < cuadrosActivos.size()) {
            cuadrosActivos[indice] = activo;
        }
    }

    VehiculoAereo* GetAvionSeleccionado() {
        return avionSeleccionado;
    }

    void AsignarAvionACuadro(int indice, VehiculoAereo* avion) {
        if (indice >= 0 && indice < aviones.size()) {
            aviones[indice] = avion;
            cuadrosActivos[indice] = true; // Activar el cuadro
        }
    }
    int ObtenerNumeroSeleccionado() {
        return numeroSeleccionado;
    }

    VehiculoAereo* DetectarCuadroSeleccionado() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 posicionRaton = GetMousePosition();

            for (int i = 0; i < cuadrosSeleccion.size(); i++) {
                if (cuadrosActivos[i] && CheckCollisionPointRec(posicionRaton, cuadrosSeleccion[i])) {
                    cuadroSeleccionado = i + 1;
                    avionSeleccionado = aviones[i]; // Actualizar el avión seleccionado
                    std::cout << "Avión seleccionado: " << avionSeleccionado->getNombre() << std::endl;
                    return avionSeleccionado;
                }
            }
        }
        return nullptr;
    }



    void DibujarCuadrosSeleccion() {
        for (int i = 0; i < cuadrosSeleccion.size(); i++) {
            Color color = cuadrosActivos[i] ? DARKGRAY : LIGHTGRAY;
            DrawRectangleRec(cuadrosSeleccion[i], color);

            DrawText(
                TextFormat("%d", i + 1),
                cuadrosSeleccion[i].x + cuadrosSeleccion[i].width / 2 - 10,
                cuadrosSeleccion[i].y + cuadrosSeleccion[i].height / 2 - 10,
                20,
                cuadrosActivos[i] ? WHITE : GRAY
            );
        }
    }


    void ActualizarCuadro(size_t indice, const std::vector<std::string>& datosAvion) {
        if (indice < cuadros.size()) {
            cuadros[indice].ActualizarTextoCompleto(datosAvion);
        }
    }

    void DibujarCuadros() {
        for (const auto& cuadro : cuadros) {
            cuadro.Dibujar();
        }
    }


    void Dibujar() {
        //DibujarBotones();
        DibujarCuadros();
        DibujarNumeroSeleccionado();
        //DibujarCuadrosSeleccion();
        DibujarInformacionAvionSeleccionado();
    }

    void DibujarNumeroSeleccionado() {
        Rectangle recuadro = { 1207, 700, 70, 94 };


        if (numeroSeleccionado != 0) {
            if (numeroSeleccionado < 7)
            {
                DrawText(
                    TextFormat("%d", numeroSeleccionado),
                    recuadro.x + recuadro.width / 2 - 10,
                    recuadro.y + recuadro.height / 2 - 10,
                    50,
                    WHITE
                );
            }
            else
            {
                DrawText(
                    TextFormat("%s", "N"),
                    recuadro.x + recuadro.width / 2 - 10,
                    recuadro.y + recuadro.height / 2 - 10,
                    50,
                    WHITE
                );
            }

        }
    }

    void AsignarEstacionAvionSeleccionado(int indiceEstacion) {
        if (avionSeleccionado != nullptr) {
            if (indiceEstacion >= 1 && indiceEstacion <= 6 && !estacionesOcupadas[indiceEstacion - 1]) {
                Vector2 estacion = ObtenerPosicionEstacion(indiceEstacion);
                avionSeleccionado->AsignarEstacion(estacion);
                estacionesOcupadas[indiceEstacion - 1] = true; 
                avionSeleccionado->setEstado(EstadoVehiculo::Aterrizando);

                std::cout << "Avión " << avionSeleccionado->getNombre() << " asignado a estación " << indiceEstacion << std::endl;
            }
            else {
                std::cout << "La estación " << indiceEstacion << " ya está ocupada o es inválida." << std::endl;
            }
        }
        else {
            std::cout << "No se puede asignar la estación. No hay avión seleccionado." << std::endl;
        }
    }

    void LiberarEstacionesOcupadas() {
        for (size_t i = 0; i < aviones.size(); i++) {
            if (aviones[i] != nullptr && estacionesOcupadas[i]) {
                if (aviones[i]->HaTerminadoProcedimiento()) {
                    estacionesOcupadas[i] = false; 
                    std::cout << "Estación " << (i + 1) << " liberada por el avión " << aviones[i]->getNombre() << std::endl;

                    
                    aviones[i] = nullptr;
                }
            }
        }
    }


    bool EsEstacionOcupada(int indiceEstacion) const {
        if (indiceEstacion >= 1 && indiceEstacion <= 6) {
            return estacionesOcupadas[indiceEstacion - 1];
        }
        return false;
    }

    void OcuparEstacion(int indiceEstacion) {
        if (indiceEstacion >= 1 && indiceEstacion <= 6) {
            estacionesOcupadas[indiceEstacion - 1] = true;
        }
    }


    void DetectarBotonPresionado() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 posicionRaton = GetMousePosition();

            for (int i = 0; i < 6; i++) {

                if (CheckCollisionPointRec(posicionRaton, botones[i])) {
                    numeroSeleccionado = i + 1;
                    std::cout << "Botón presionado: " << numeroSeleccionado << std::endl;
                }
            }
        }
    }

    void DibujarBotones() {
        for (int i = 0; i < botones.size(); i++) {
            DrawRectangleRec(botones[i], DARKGRAY);
            DrawText(TextFormat("%d", i + 1), botones[i].x + 15, botones[i].y + 10, 20, WHITE);
        }
    }

    void LiberarEstacion(int indiceEstacion) {
        if (indiceEstacion >= 1 && indiceEstacion <= estacionesOcupadas.size()) {
            estacionesOcupadas[indiceEstacion - 1] = false; 
            std::cout << "Estación " << indiceEstacion << " liberada." << std::endl;
        }
        else {
            std::cout << "Índice de estación inválido: " << indiceEstacion << std::endl;
        }
    }

    Vector2 ObtenerPosicionEstacion(int indice) {
        switch (indice) {
        case 1:
            return { Est1_XF, Est1_YF };
        case 2:
            return { EST2_XF, EST2_YF };
        case 3:
            return { EST3_XF, EST3_YF };
        case 4:
            return { EST4_XF, EST4_YF };
        case 5:
            return { EST5_XF, EST5_YF };
        case 6:
            return { EST6_XF, EST6_YF };
        default:
            return { 0.0f, 0.0f };
        }
    }


    void ReiniciarTerminal() {
        
        for (auto& cuadro : cuadros) {
            cuadro.ActualizarTextoCompleto(std::vector<std::string>{" ", " ", " ", " ", " "}); // Limpiar el texto
        }

        
        for (size_t i = 0; i < aviones.size(); ++i) {
            aviones[i] = nullptr; 
        }

        
        std::fill(cuadrosActivos.begin(), cuadrosActivos.end(), false);

        
        std::fill(estacionesOcupadas.begin(), estacionesOcupadas.end(), false);

        
        numeroSeleccionado = 0;
        cuadroSeleccionado = -1;
        avionSeleccionado = nullptr;

        
        boton7Presionado = false;

        std::cout << "Terminal reiniciada para una nueva ronda." << std::endl;
    }
};
