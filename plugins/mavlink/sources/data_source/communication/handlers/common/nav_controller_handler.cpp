#include "nav_controller_handler.h"

// MAVLink
#include <mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"

#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace data_source;
using namespace domain;

NavControllerHandler::NavControllerHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void NavControllerHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_nav_controller_output_t output;
    mavlink_msg_nav_controller_output_decode(&message, &output);

    portion.setParameter({ Telemetry::FlightControl, Telemetry::DesiredPitch }, output.nav_pitch);
    portion.setParameter({ Telemetry::FlightControl, Telemetry::DesiredRoll }, output.nav_roll);
    portion.setParameter({ Telemetry::FlightControl, Telemetry::DesiredHeading }, output.nav_bearing);
    portion.setParameter({ Telemetry::FlightControl, Telemetry::AirspeedError },
                         fixAirspeedError(output.aspd_error));
    portion.setParameter({ Telemetry::FlightControl, Telemetry::AltitudeError }, output.alt_error);

    portion.setParameter({ Telemetry::Navigator, Telemetry::TargetBearing }, output.target_bearing);
    portion.setParameter({ Telemetry::Navigator, Telemetry::Distance }, output.wp_dist);
    portion.setParameter({ Telemetry::Navigator, Telemetry::TrackError }, output.xtrack_error);
}

