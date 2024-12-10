#include "AvionMediano.h"

void AvionMediano::Actualizar()
{
    if (estado == EstadoVehiculo::Rotando) {
        Rectangle fuente = { 0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height };
        Rectangle destino = { posicion.x, posicion.y, dimension.x, dimension.y };

        DrawTexturePro(backgroundTexture, fuente, destino, { dimension.x / 2, dimension.y / 2 }, 180.0f, WHITE);

        estado = EstadoVehiculo::EnTerminal;
    }
    Reabastecimiento();
    VehiculoAereo::Actualizar();
}

void AvionMediano::Reabastecimiento()
{
    if (estado == EstadoVehiculo::Reabasteciendo) {
        estado = EstadoVehiculo::Descargando;
    }
    if (estado == EstadoVehiculo::Descargando) {
        descargarPersonas();
    }
    else if (estado == EstadoVehiculo::Combustible) {
        cargarCombustible();
    }
    else if (estado == EstadoVehiculo::Cargando) {
        cargarPersonas();
    }

    if (tiempoReabastecimiento < 0) {
        tiempoReabastecimiento = 0;
    }
}

void AvionMediano::Dibujar()
{
    if (this != nullptr) {
        if (backgroundTexture.id != 0) {
            Rectangle fuente = { 0, 0, (float)backgroundTexture.width, (float)backgroundTexture.height };
            Rectangle destino = { posicion.x, posicion.y, dimension.x, dimension.y };

            DrawTexturePro(backgroundTexture, fuente, destino, { dimension.x / 2, dimension.y / 2 }, anguloRotacion, WHITE);
        }
        else {
            DrawText("Error: Textura no cargada", posicion.x, posicion.y - 20, 20, RED);
        }
    }
}

void AvionMediano::descargarPersonas()
{
    if (estado == EstadoVehiculo::Descargando) {
        if (tiempoInicioDescarga == 0.0f) {
            tiempoInicioDescarga = GetTime();
        }

        float tiempoTranscurrido = GetTime() - tiempoInicioDescarga;
        tiempoReabastecimiento = tiempoCargarCombustible + tiempoCargarPersonas + tiempoDescargarPersonas - tiempoTranscurrido;

        float porcentajeCompletado = tiempoTranscurrido / tiempoDescargarPersonas;
        personasActuales = capacidadPersonas - static_cast<int>(capacidadPersonas * porcentajeCompletado);

        if (personasActuales < 0) {
            personasActuales = 0;
        }

        if (tiempoTranscurrido >= tiempoDescargarPersonas) {
            tiempoInicioDescarga = 0.0f;
            estado = EstadoVehiculo::Combustible;
        }
    }
}

void AvionMediano::cargarCombustible()
{
    if (estado == EstadoVehiculo::Combustible) {
        if (tiempoInicioCombustible == 0.0f) {
            tiempoInicioCombustible = GetTime();
        }

        float tiempoTranscurrido = GetTime() - tiempoInicioCombustible;
        tiempoReabastecimiento = tiempoCargarCombustible + tiempoCargarPersonas - tiempoTranscurrido;
        float porcentajeCompletado = tiempoTranscurrido / tiempoCargarCombustible;

        combustibleActual = static_cast<int>(combustibleMaximo * porcentajeCompletado);

        if (combustibleActual > combustibleMaximo) {
            combustibleActual = combustibleMaximo;
        }

        DrawText(TextFormat("Cargando combustible: %d", combustibleActual), posicion.x, posicion.y - 40, 30, ORANGE);

        if (tiempoTranscurrido >= tiempoCargarCombustible) {
            tiempoInicioCombustible = 0.0f;
            estado = EstadoVehiculo::Cargando;
        }
    }
}

void AvionMediano::cargarPersonas()
{
    if (estado == EstadoVehiculo::Cargando) {
        if (tiempoInicioCarga == 0.0f) {
            tiempoInicioCarga = GetTime();
        }

        float tiempoTranscurrido = GetTime() - tiempoInicioCarga;
        tiempoReabastecimiento = tiempoCargarPersonas - tiempoTranscurrido;
        float porcentajeCompletado = tiempoTranscurrido / tiempoCargarPersonas;

        personasActuales = static_cast<int>(capacidadPersonas * porcentajeCompletado);

        if (personasActuales > capacidadPersonas) {
            personasActuales = capacidadPersonas;
        }

        DrawText(TextFormat("Cargando personas: %d", personasActuales), posicion.x, posicion.y - 60, 30, BLUE);

        if (tiempoTranscurrido >= tiempoCargarPersonas) {
            tiempoInicioCarga = 0.0f;
            estado = EstadoVehiculo::Listo;
        }
    }
}

void AvionMediano::CargarTextura(const std::string& ruta)
{
    if (backgroundTexture.id == 0) {
        backgroundTexture = LoadTexture(ruta.c_str());
    }
}

void AvionMediano::DescargarTextura()
{
    if (backgroundTexture.id != 0) {
        UnloadTexture(backgroundTexture);
        backgroundTexture = { 0 };
    }
}



Texture2D AvionMediano::backgroundTexture = { 0 };



