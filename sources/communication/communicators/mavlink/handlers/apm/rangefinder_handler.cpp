#include "rangefinder_handler.h"

// SwarmLink
#include <swarmlink/mavlink.h>

// Qt
#include <QDebug>

// Internal
#include "mavlink_protocol_helpers.h"

#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry_portion.h"

using namespace comm;
using namespace domain;

RangefinderHandler::RangefinderHandler(MavLinkCommunicator* communicator):
    AbstractMavLinkHandler(communicator),
    m_telemetryService(serviceRegistry->telemetryService())
{}

void RangefinderHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_RANGEFINDER) return;

    TelemetryPortion portion(m_telemetryService->mavNode(message.sysid));

    mavlink_rangefinder_t rangefinder;
    mavlink_msg_rangefinder_decode(&message, &rangefinder);

    portion.setParameter({ Telemetry::Radalt, Telemetry::Altitude },
                       rangefinder.distance);
    portion.setParameter({ Telemetry::Radalt, Telemetry::Voltage },
                       rangefinder.voltage);
}
