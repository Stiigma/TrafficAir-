#include "VehiculoAereo.h"
#include "Terminal.h"

VehiculoAereo::VehiculoAereo()
    : estado(EstadoVehiculo::EnAire),
    posicion({ -20, ESTGENERAL_Y }),
    dimension({ 60, 100 }),
    velocidad(150.0f),
    tiempoInicio(GetTime()),
    anguloRotacion(0.0f),
    tiempoReabastecimiento(10.0f),
    nombre("Sin Nombre"),  // Valor por defecto
    tiempoEnAire(10.0f) {  // Inicializamos tiempoEnAire en 0
}



void VehiculoAereo::Aterrizar(Vector2 inicio, Vector2 fin) {
    float deltaTime = GetFrameTime(); // Obtén el tiempo entre cuadros

    if (estado == EstadoVehiculo::Bajar) {
        estado = EstadoVehiculo::Aterrizando;
        posicion = inicio;
        //velocidad = 50.0f;
    }
    if (estado == EstadoVehiculo::Aterrizando) {
        
        posicion.y -= velocidad * deltaTime;

        
        if (posicion.y <= fin.y) {
            posicion.y = fin.y; 
            estado = EstadoVehiculo::Reabasteciendo;
            velocidad = 0;
        }
    }
}

void VehiculoAereo::Despegar(Vector2 inicio, Vector2 fin) {
    float deltaTime = GetFrameTime(); 
    if (estado == EstadoVehiculo::Listo) {
        estado = EstadoVehiculo::Despegando;
        posicion = inicio;
        velocidad = 150.0f;
    }

    if (estado == EstadoVehiculo::Despegando) {
        
        posicion.y += velocidad * deltaTime;

        
        if (posicion.y >= fin.y) {
            posicion.y = fin.y; 
            estado = EstadoVehiculo::EnTerminal; 
            velocidad = 0;
        }
    }
}

bool VehiculoAereo::HaTerminadoProcedimiento()  {
    return (estado == EstadoVehiculo::EnTerminal);
}


void VehiculoAereo::Actualizar() {
    float deltaTime = GetFrameTime();

    switch (estado) {
    case EstadoVehiculo::EnAire:
        // Aquí puedes manejar lógica adicional si es necesario
        break;

    case EstadoVehiculo::Aterrizando:
    case EstadoVehiculo::Bajar:
        // Mover el avión hacia la estación asignada
        Aterrizar({ Estacion.x + DIF_EST_X , 1080 }, Estacion);
        break;

    case EstadoVehiculo::EnTerminal:
        // Lógica para cuando el avión está en la terminal
        break;

    case EstadoVehiculo::Descargando:
    case EstadoVehiculo::Cargando:
    case EstadoVehiculo::Combustible:
        // Manejar el proceso de reabastecimiento
        //Reabastecimiento();
        break;

    case EstadoVehiculo::Despegando:
    case EstadoVehiculo::Listo:
        // Mover el avión hacia el aire
        Despegar({ posicion.x, posicion.y }, { posicion.x, ESTGENERAL_Y });
        break;

    default:
        break;
    }

  
}



float VehiculoAereo::getTiempoRestanteVuelo()  {
    if (estado == EstadoVehiculo::EnAire) {
        float tiempoTranscurrido = GetTime() - tiempoInicio;
        return tiempoEnAire - tiempoTranscurrido;
    }
    return 0.0f; 
}


void VehiculoAereo::Dibujar() {
    if (this != nullptr)
    {
        DrawRectangleV(posicion, dimension, RED);

    }
}

void VehiculoAereo::Reabastecimiento()
{
    static float tiempoInicioReabastecimiento = 0; 

    if (estado == EstadoVehiculo::Reabasteciendo) {
       
        if (tiempoInicioReabastecimiento == 0) {
            tiempoInicioReabastecimiento = GetTime();
        }

        
        DrawText("Reabasteciendo...", posicion.x, posicion.y - 20, 20, GREEN);

        // Verificamos si el tiempo de reabastecimiento ha pasado
        if (GetTime() - tiempoInicioReabastecimiento >= tiempoReabastecimiento) {
            // Finaliza el reabastecimiento y cambia el estado a EnTerminal
            estado = EstadoVehiculo::EnTerminal;
            tiempoInicioReabastecimiento = 0; // Reiniciamos el temporizador
        }
    }
}


void VehiculoAereo::EnAire()
{
}


std::vector<std::string> VehiculoAereo::get_atributoStr() {
    std::vector<std::string> datos;

    datos.push_back(nombre);                               // Nombre del vehículo
    datos.push_back(TextFormat("%.1fs", getTiempoRestanteVuelo())); // Tiempo restante en vuelo
    datos.push_back(getEstadoStr());                      // Estado del vehículo
    datos.push_back("Comercial");                         // Tipo de avión
    datos.push_back(TextFormat("%.1fs", tiempoReabastecimiento)); // Tiempo en terminal

    return datos;
}





std::string VehiculoAereo::getEstadoStr()  {
    switch (estado) {
    case EstadoVehiculo::EnAire: return "En Aire";
    case EstadoVehiculo::Aterrizando: return "Aterrizando";
    case EstadoVehiculo::EnTerminal: return "En Terminal";
    case EstadoVehiculo::Descargando: return "Descargando";
    case EstadoVehiculo::Cargando: return "Cargando";
    case EstadoVehiculo::Combustible: return "Cargando Combustible";
    case EstadoVehiculo::Despegando: return "Despegando";
    default: return "Desconocido";
    }
}


void VehiculoAereo::AsignarEstacion(Vector2 estacion) {
    Estacion = estacion; // Asignar la posición de la estación
}


void VehiculoAereo::ReiniciarTiempoInicio() {
    tiempoInicio = GetTime();
}