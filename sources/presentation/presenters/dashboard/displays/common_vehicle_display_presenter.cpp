#include "common_vehicle_display_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"
#include "mission.h"
#include "mission_assignment.h"
#include "command.h"

#include "service_registry.h"
#include "vehicle_service.h"
#include "mission_service.h"
#include "command_service.h"
#include "telemetry_service.h"

#include "vehicle_types.h"

using namespace presentation;

class CommonVehicleDisplayPresenter::Impl
{
public:
    dto::VehiclePtr vehicle;
    dto::MissionAssignmentPtr assignment;
    QList<dto::CommandPtr> commands;

    domain::VehicleService* vehicleService = serviceRegistry->vehicleService();
    domain::MissionService* missionService = serviceRegistry->missionService();
    domain::CommandService* commandService = serviceRegistry->commandService();
};

CommonVehicleDisplayPresenter::CommonVehicleDisplayPresenter(QObject* parent):
    AbstractTelemetryPresenter(parent),
    d(new Impl())
{
    connect(d->vehicleService, &domain::VehicleService::vehicleChanged,
            this, [this](const dto::VehiclePtr& vehicle) {
        if (vehicle == d->vehicle) this->updateVehicle();
    });

    connect(d->missionService, &domain::MissionService::assignmentAdded, this,
            [this](const dto::MissionAssignmentPtr& assignment) {
        if (d->vehicle.isNull() || assignment->vehicleId() != d->vehicle->id()) return;

        d->assignment = assignment;
        this->updateMissionItems();
    });
    connect(d->missionService, &domain::MissionService::assignmentRemoved, this,
            [this](const dto::MissionAssignmentPtr& assignment) {
        if (d->assignment != assignment) return;

        d->assignment.clear();
        this->updateMissionItems();
    });
    connect(d->missionService, &domain::MissionService::assignmentChanged, this,
            [this](const dto::MissionAssignmentPtr& assignment) {
        if (d->assignment == assignment)
        {
            this->updateMissionItems();
        }
        else if (d->vehicle && assignment->vehicleId() != d->vehicle->id())
        {
            d->assignment = assignment;
            this->updateMissionItems();
        }
    });

    connect(d->missionService, &domain::MissionService::currentItemChanged, this,
            [this](int vehicleId, const dto::MissionItemPtr& item) {
        if (d->assignment && d->assignment->vehicleId() == vehicleId)
            this->setVehicleProperty(PROPERTY(mission), PROPERTY(current),
                                     item ? item->sequence() : -1);
    });
    connect(d->missionService, &domain::MissionService::missionChanged, this,
            [this](const dto::MissionPtr& mission) {
        if (d->assignment && d->assignment->missionId() == mission->id())
            this->updateMissionItems();
    });

    connect(d->commandService, &domain::CommandService::commandChanged,
            this, [this](const dto::CommandPtr& command) {
        if (!d->commands.contains(command)) return;

        this->invokeViewMethod(PROPERTY(updateCommandStatus), command->type(), command->status());
        if (command->isFinished()) d->commands.removeOne(command);
    });
}

CommonVehicleDisplayPresenter::~CommonVehicleDisplayPresenter()
{}

void CommonVehicleDisplayPresenter::setVehicle(int vehicleId)
{
    if (d->vehicle && d->vehicle->id() == vehicleId) return;

    d->vehicle = d->vehicleService->vehicle(vehicleId);
    this->updateVehicle();

    d->assignment = d->missionService->vehicleAssignment(vehicleId);
    this->updateMissionItems();

    this->setNode(serviceRegistry->telemetryService()->vehicleNode(vehicleId));
}

void CommonVehicleDisplayPresenter::updateVehicle()
{
    if (d->vehicle)
    {
        this->setVehicleProperty(PROPERTY(vehicleName), d->vehicle->name());
        this->setVehicleProperty(PROPERTY(vehicleType), d->vehicle->type());
        this->setVehicleProperty(PROPERTY(online), d->vehicle->isOnline());
    }
    else
    {
        this->setVehicleProperty(PROPERTY(vehicleName), QString());
        this->setVehicleProperty(PROPERTY(vehicleType), dto::Vehicle::UnknownType);
        this->setVehicleProperty(PROPERTY(online), false);
    }
}

void CommonVehicleDisplayPresenter::updateMissionItems()
{
    if (d->assignment)
    {
        this->setVehicleProperty(PROPERTY(mission), PROPERTY(count),
                                 d->missionService->mission(d->assignment->missionId())->count());

        dto::MissionItemPtr current =  d->missionService->currentWaypoint(d->assignment->vehicleId());
        if (current)
        {
            this->setVehicleProperty(PROPERTY(mission), PROPERTY(current), current->sequence());
        }
        else
        {
            this->setVehicleProperty(PROPERTY(mission), PROPERTY(current), -1);
        }
    }
    else
    {
        this->setVehicleProperty(PROPERTY(mission), PROPERTY(count), 0);
        this->setVehicleProperty(PROPERTY(mission), PROPERTY(current), -1);
    }
}

void CommonVehicleDisplayPresenter::executeCommand(int commandType, const QVariant& args)
{
    if (d->vehicle.isNull()) return;

    dto::CommandPtr command = dto::CommandPtr::create();
    command->setType(dto::Command::CommandType(commandType));
    command->setArguments(args.toList());

    d->commands.append(command);
    d->commandService->executeCommand(d->vehicle->id(), command);
}

void CommonVehicleDisplayPresenter::rejectCommand(int commandType)
{
    if (d->vehicle.isNull()) return;

    d->commandService->cancelCommand(d->vehicle->id(), dto::Command::CommandType(commandType));
}

void CommonVehicleDisplayPresenter::connectView(QObject* view)
{
    BasePresenter::connectView(view);

    this->updateVehicle();
}

void CommonVehicleDisplayPresenter::connectNode(domain::Telemetry* node)
{
    this->chainNode(node->childNode(domain::Telemetry::System),
                    std::bind(&CommonVehicleDisplayPresenter::updateSystem,
                              this, std::placeholders::_1));
}

void CommonVehicleDisplayPresenter::updateSystem(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setVehicleProperty(PROPERTY(armed), parameters.value(domain::Telemetry::Armed));
    this->setVehicleProperty(PROPERTY(guided), parameters.value(domain::Telemetry::Guided));
    this->setVehicleProperty(PROPERTY(stab), parameters.value(domain::Telemetry::Stabilized));
    this->setVehicleProperty(PROPERTY(vehicleState), parameters.value(domain::Telemetry::State));
    this->setVehicleProperty(PROPERTY(mode), parameters.value(domain::Telemetry::Mode));

    QVariantList modes;
    for (auto item: parameters.value(domain::Telemetry::AvailableModes).value<
         QList<domain::vehicle::Mode> >())
    {
        modes.append(QVariant::fromValue(item));
    }
    this->setVehicleProperty(PROPERTY(availableModes), modes);
}

void CommonVehicleDisplayPresenter::setVehicleProperty(const char* name, const QVariant& value)
{
    this->setVehicleProperty(QString(), name, value);
}

void CommonVehicleDisplayPresenter::setVehicleProperty(const QString& group, const char* name,
                                                       const QVariant& value)
{
    if (!this->view()) return;

    QObject* vehicle = this->view()->findChild<QObject*>(PROPERTY(vehicle));
    if (!vehicle) return;

    if (group.isEmpty())
    {
        vehicle->setProperty(name, value);
    }
    else
    {
         QObject* groupObject = vehicle->findChild<QObject*>(group);
         if (!groupObject) return;

         groupObject->setProperty(name, value);
    }
}
