
#pragma once

enum class EstadoVehiculo {
    EnAire = 0,        // Volando
    Aterrizando = 1,   // Descendiendo
    Frenando = 2,      // Frenando hacia la terminal
    EnTerminal = 3,     
    Despegando = 4,
    Acelerando = 5,// Detenido en la terminal
    Cayendo = 6,
    Estrellado = 7,
    Descargando = 8,
    Cargando = 9,
    Combustible = 10,
    Reabasteciendo = 11,
    Listo = 12,
    EnEspera = 13,
    Rotando = 14,
    Bajar = 15
};

