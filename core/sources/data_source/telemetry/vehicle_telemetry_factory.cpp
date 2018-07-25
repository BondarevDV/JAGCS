#include "vehicle_telemetry_factory.h"

// Qt
#include <QCoreApplication>

// Internal
#include "telemetry.h"

using namespace data_source;

VehicleTelemetryFactory::VehicleTelemetryFactory():
    ITelemetryFactory()
{}

Telemetry* VehicleTelemetryFactory::create()
{
    Telemetry* root = new Telemetry(Telemetry::Root);

    new Telemetry(Telemetry::System, root);
    new Telemetry(Telemetry::Position, root);
    new Telemetry(Telemetry::HomePosition, root);
    Telemetry* ahrs = new Telemetry(Telemetry::Ahrs, root);
    new Telemetry(Telemetry::Accel, ahrs);
    new Telemetry(Telemetry::Gyro, ahrs);
    new Telemetry(Telemetry::Compass, ahrs);
    new Telemetry(Telemetry::Satellite, root);
    new Telemetry(Telemetry::Barometric, root);
    new Telemetry(Telemetry::Pitot, root);
    new Telemetry(Telemetry::Radalt, root);
    new Telemetry(Telemetry::Navigator, root);
    new Telemetry(Telemetry::FlightControl, root);
    new Telemetry(Telemetry::PowerSystem, root);
    new Telemetry(Telemetry::Battery, root);
    new Telemetry(Telemetry::Wind, root);

    return root;
}
