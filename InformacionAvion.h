#pragma once

#include <raylib.h>
#include <string>
#include <vector>
using std::vector;
using std::string;
class InformacionAvion {
private:
    Rectangle cuadro;                          // �rea del cuadro
    std::vector<std::string> lineasTexto;      // Vector de l�neas de texto
    Color colorFondo;                          // Color del fondo

public:
    // Constructor
    InformacionAvion(float x, float y, float ancho, float alto, const vector<string>& textos, Color color)
        : cuadro{ x, y, ancho, alto }, lineasTexto(textos), colorFondo(color) {
    }

    // Actualiza una l�nea de texto espec�fica
    void ActualizarTexto(size_t indice, const string& nuevoTexto) {
        if (indice < lineasTexto.size()) {
            lineasTexto[indice] = nuevoTexto;
        }
    }

    
    void Dibujar() const {
        // Si todas las cadenas de texto est�n vac�as, no dibujar nada
        bool tieneInformacion = false;
        for (const auto& texto : lineasTexto) {
            if (!texto.empty()) {
                tieneInformacion = true;
                break;
            }
        }

        if (!tieneInformacion) {
            return; // No dibujar si todas las cadenas est�n vac�as
        }

        // Definir offsets para las posiciones del texto
        std::vector<float> offsetsY = { 19.0f, 35.0f, 52.0f, 72.0f, 102.0f };
        std::vector<float> offsetsX = { 125.0f, 193.0f, 136.0f, 122.0f, 225.0f };

        for (size_t i = 0; i < lineasTexto.size(); ++i) {
            // Usar offset predefinido o generar din�mico
            float offsetX = (i < offsetsX.size()) ? offsetsX[i] : 10.0f;
            float offsetY = (i < offsetsY.size()) ? offsetsY[i] : (10.0f + i * 25.0f);

            // Dibujar cada l�nea de texto solo si no est� vac�a
            if (!lineasTexto[i].empty()) {
                DrawText(
                    lineasTexto[i].c_str(),
                    cuadro.x + offsetX,
                    cuadro.y + offsetY,
                    11, // Tama�o de la fuente
                    BLACK
                );
            }
        }
    }

    void ActualizarTextoCompleto(const std::vector<std::string>& nuevosTextos) {
        if (nuevosTextos.size() <= lineasTexto.size()) {
            for (size_t i = 0; i < nuevosTextos.size(); ++i) {
                lineasTexto[i] = nuevosTextos[i];
            }
        }
    }

    // Devuelve el �rea del cuadro
    Rectangle GetCuadro() const {
        return cuadro;
    }
};

