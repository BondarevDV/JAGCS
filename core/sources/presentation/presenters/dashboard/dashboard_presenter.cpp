#include "dashboard_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

using namespace presentation;

class DashboardPresenter::Impl
{
public:
    dto::VehiclePtr selectedVehicle;
    domain::VehicleService* service = serviceRegistry->vehicleService();
};

DashboardPresenter::DashboardPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    connect(d->service, &domain::VehicleService::vehicleChanged,
            this, [this](const dto::VehiclePtr& vehicle){
        if (d->selectedVehicle != vehicle) return;

        this->view()->setProperty(PROPERTY(selectedVehicle), QVariant::fromValue(*vehicle));
    });

    connect(d->service, &domain::VehicleService::vehicleRemoved,
            this, [this](const dto::VehiclePtr& vehicle){
        if (d->selectedVehicle != vehicle) return;

        this->view()->setProperty(PROPERTY(selectedVehicle), QVariant());
    });
}

DashboardPresenter::~DashboardPresenter()
{}

void DashboardPresenter::selectVehicle(int vehicleId)
{
    dto::VehiclePtr vehicle = d->service->vehicle(vehicleId);

    if (vehicle == d->selectedVehicle) return;

    d->selectedVehicle = vehicle;
    if (vehicle)
    {
        this->view()->setProperty(PROPERTY(selectedVehicle), QVariant::fromValue(*vehicle));
    }
    else
    {
        this->view()->setProperty(PROPERTY(selectedVehicle), QVariant());
    }
}
