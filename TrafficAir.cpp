#include "TrafficAir.h"
#include "AvionChico.h"
#include "AvionMediano.h"
#include <algorithm>


// Constructor
TrafficAir::TrafficAir(int ancho, int alto)
    : anchoVentana(ancho), altoVentana(alto), titulo("TrafficAir"), juegoCorriendo(true), rondaActual(1), maxRondas(3) {
    terminal = new Terminal();
    Inicializar();
}

// Destructor
TrafficAir::~TrafficAir() {
    Finalizar();
    delete terminal;

    // Liberar memoria de la pila de aviones
    while (!pilaAviones.empty()) {
        delete pilaAviones.top();
        pilaAviones.pop();
    }

    for (auto& avion : avionesActivos) {
        delete avion;
    }
}


void TrafficAir::Inicializar() {
    InitWindow(anchoVentana, altoVentana, titulo.c_str());
    ToggleFullscreen();
    SetTargetFPS(60);
   
    AvionChico::CargarTextura("assets/AvionChico.png");
    AvionMediano::CargarTextura("assets/AvionMediano.png");
    backgroundTexture = LoadTexture("assets/FondoPrevio.png");
}


void TrafficAir::Finalizar() {
    UnloadTexture(backgroundTexture); 
    AvionChico::DescargarTextura();
    AvionMediano::DescargarTextura();
    CloseWindow();
}

void TrafficAir::Dibujar() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(backgroundTexture, 0, 0, WHITE);
    for (auto& avion : avionesActivos)
    {
        if (avion != nullptr)
        {
            avion->Dibujar();
                    if (avion->getEstado() == EstadoVehiculo::Descargando) {
                        DrawText("Proceso: Descargando Personas", 50, 50, 100, GREEN);
                    }
                    else if (avion->getEstado() == EstadoVehiculo::Combustible) {
                        DrawText("Proceso: Cargando Combustible", 50, 50, 100, ORANGE);
                    }
                    else if (avion->getEstado() == EstadoVehiculo::Cargando) {
                        DrawText("Proceso: Cargando Personas", 50, 50, 100, BLUE);
                    }
        }
        
    }
    terminal->Dibujar();
    if (terminal->GetAvionSeleccionado() != nullptr) {
        DrawText("Avión seleccionado", 50, 40, 20, GREEN);
    }
    else {
        DrawText("Selecciona un avión", 50, 60, 20, RED);
    }

    if (terminal->ObtenerNumeroSeleccionado() > 0) {
        DrawText("Estación seleccionada", 50, 80, 20, GREEN);
    }
    else {
        DrawText("Selecciona una estación", 50, 100, 20, RED);
    }


    
    float tiempoActual = GetTime();
    int segundosRestantes = static_cast<int>(duracionRonda - (tiempoActual - tiempoInicioRonda));
    if (segundosRestantes < 0) {
        segundosRestantes = 0; 
    }

    DrawText(TextFormat("Tiempo restante: %ds", segundosRestantes), 50, 120, 20, BLACK);

    EndDrawing();
}


void TrafficAir::Ejecutar() {
    while (!WindowShouldClose() && juegoCorriendo) {
        
        IniciarRonda();

        
        float tiempoInicioRonda = GetTime();

        
        while (!WindowShouldClose() && juegoCorriendo) {
            Dibujar();

            
            float tiempoActual = GetTime();
            if (tiempoActual - tiempoUltimaExtraccion >= 5.0f && !pilaAviones.empty()) {
               
                bool avionAsignado = false;
                for (int i = 0; i < avionesActivos.size(); i++) {
                    if (avionesActivos[i] == nullptr && !pilaAviones.empty()) {
                        VehiculoAereo* nuevoAvion = pilaAviones.top();
                        pilaAviones.pop();
                        avionesActivos[i] = nuevoAvion;

                        
                        terminal->AsignarAvionACuadro(i, nuevoAvion);

                        tiempoUltimaExtraccion = tiempoActual; 
                        avionAsignado = true;
                        break; 
                    }
                }

                
                if (!avionAsignado && avionesActivos.size() < 10) {
                    VehiculoAereo* nuevoAvion = pilaAviones.top();
                    pilaAviones.pop();
                    avionesActivos.push_back(nuevoAvion);
                    nuevoAvion->ReiniciarTiempoInicio();
                
                    terminal->AsignarAvionACuadro(avionesActivos.size() - 1, nuevoAvion);

                    tiempoUltimaExtraccion = tiempoActual; 
                }
            }

            
            for (int i = 0; i < avionesActivos.size(); i++) {
                if (avionesActivos[i] != nullptr) {
                    std::vector<std::string> datosAvion = avionesActivos[i]->get_atributoStr();
                    terminal->ActualizarCuadro(i, datosAvion);
                    avionesActivos[i]->Actualizar();

            
                    
                    if (avionesActivos[i]->getEstado() == EstadoVehiculo::EnTerminal) {
                        terminal->LiberarEstacion(i + 1);
                        avionesProcesados.push(avionesActivos[i]);
                        avionesActivos[i] = nullptr; 
                    }
                }
            }

            
            terminal->DetectarBotonPresionado();
            terminal->DetectarCuadroSeleccionado();

            if (terminal->ObtenerNumeroSeleccionado() > 0 && terminal->GetAvionSeleccionado() != nullptr) {
                if (IsKeyPressed(KEY_SEVEN)) {
                    HacerAterrizarAvionSeleccionado();
                }
            }

            terminal->LiberarEstacionesOcupadas();

            
            if (GetTime() - tiempoInicioRonda >= 120.0f || avionesProcesados.size() >= rondaActual * 10) {
                break;
            }
        }

        
        FinalizarRonda();

        rondaActual++;
        if (rondaActual > 3) {
            juegoCorriendo = false;
        }
    }
}


void TrafficAir::FinalizarRonda() {
    std::cout << "Finalizando ronda " << rondaActual << std::endl;

    // Vaciar la pila de aviones procesados
    while (!avionesProcesados.empty()) {
        delete avionesProcesados.top();
        avionesProcesados.pop();
    }

    // Vaciar los aviones activos
    for (size_t i = 0; i < avionesActivos.size(); i++) {
        if (avionesActivos[i] != nullptr) {
            delete avionesActivos[i];
            avionesActivos[i] = nullptr;
        }
    }
    avionesActivos.clear(); 

    terminal->ReiniciarTerminal();
}


void TrafficAir::HacerAterrizarAvionSeleccionado() {
    if (terminal->GetAvionSeleccionado() != nullptr) {
        VehiculoAereo* avionSeleccionado = terminal->GetAvionSeleccionado();

        if (avionSeleccionado->getEstado() == EstadoVehiculo::EnAire) {
            int numeroEstacion = terminal->ObtenerNumeroSeleccionado();
            if (numeroEstacion >= 1 && numeroEstacion <= 6) {
                if (!terminal->EsEstacionOcupada(numeroEstacion)) {
                    Vector2 posicionEstacion = terminal->ObtenerPosicionEstacion(numeroEstacion);
                    avionSeleccionado->AsignarEstacion(posicionEstacion);
                    avionSeleccionado->setEstado(EstadoVehiculo::Bajar);
                    terminal->OcuparEstacion(numeroEstacion); 
                }
                else {
                    std::cout << "La estación " << numeroEstacion << " está ocupada." << std::endl;
                }
            }
            else {
                std::cout << "Estación seleccionada inválida." << std::endl;
            }
        }
        else {
            std::cout << "El avión no está en el aire, no puede aterrizar." << std::endl;
        }
    }
    else {
        std::cout << "No hay avión seleccionado." << std::endl;
    }
}


void TrafficAir::IniciarRonda() {
    if (rondaActual > maxRondas) {
        std::cout << "El juego ha terminado. No hay más rondas." << std::endl;
        juegoCorriendo = false;
        return;
    }

    int cantidadAviones = rondaActual * 10;
    CargarAvionesEnPila(cantidadAviones);

    tiempoInicioRonda = GetTime(); // Registrar el tiempo de inicio de la ronda
    duracionRonda = 120.0f;        // Duración máxima de la ronda en segundos (4 minutos)

    std::cout << "Iniciando ronda " << rondaActual << " con " << cantidadAviones << " aviones." << std::endl;
}




void TrafficAir::CargarAvionesEnPila(int cantidad) {
   
    for (int i = 0; i < cantidad; i++) {
        int random = GetRandomValue(0, 1);
        if(random)
            pilaAviones.push(new AvionChico());
        else
            pilaAviones.push(new AvionMediano());
    }
}
