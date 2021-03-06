#include "mission_edit_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "mission_service.h"

#include "mission.h"
#include "mission_item.h"

using namespace presentation;

class MissionEditPresenter::Impl
{
public:
    domain::MissionService* const service = serviceRegistry->missionService();

    dto::MissionPtr mission;
    dto::MissionItemPtr item;
};

MissionEditPresenter::MissionEditPresenter(QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    connect(d->service, &domain::MissionService::missionChanged, this,
            [this](const dto::MissionPtr& mission) {
        if (mission == d->mission) this->updateMission();
    });
}

MissionEditPresenter::~MissionEditPresenter()
{}

void MissionEditPresenter::setMission(int id)
{
    d->mission = d->service->mission(id);

    this->updateMission();
}

void MissionEditPresenter::setItem(int id)
{
    d->item = d->service->missionItem(id);

    this->updateItem();
}

void MissionEditPresenter::selectItem(int sequence)
{
    if (d->mission.isNull()) return;

    d->item = d->service->missionItem(d->mission->id(), sequence);

    this->updateItem();
}

void MissionEditPresenter::updateMission()
{
    this->setViewProperty(PROPERTY(count), d->mission ? d->mission->count() : 0);
    this->setViewProperty(PROPERTY(name), d->mission ? d->mission->name() : QString());
}

void MissionEditPresenter::updateItem()
{
    this->setViewProperty(PROPERTY(selectedItemId), d->item ? d->item->id() : 0);
    this->setViewProperty(PROPERTY(sequence), d->item ? d->item->sequence() : -1);
}

void MissionEditPresenter::removeItem()
{
    if (d->item.isNull()) return;

    int sequence = d->item->sequence();
    d->service->remove(d->item);

    if (sequence > 0)
    {
        this->selectItem(sequence - 1);
    }
    else
    {
        this->selectItem(d->mission->count() > 0 ? sequence : -1);
        if (d->item && d->item->command() != dto::MissionItem::Home)
        {
            d->item->setCommand(dto::MissionItem::Home);
            d->service->save(d->item);
        }
    }
}

void MissionEditPresenter::addItem(dto::MissionItem::Command command,
                                   const QGeoCoordinate& coordinate)
{
    if (d->mission.isNull()) return;

    int seq = d->item ? d->item->sequence() + 1 : 0;
    d->item = d->service->addNewMissionItem(d->mission->id(), command, seq, coordinate);

    this->updateItem();
}

void MissionEditPresenter::changeSequence(int sequence)
{
    if (d->item.isNull()) return;

    dto::MissionItemPtr other = d->service->missionItem(d->mission->id(), sequence);
    if (other.isNull()) return;

    d->service->swapItems(d->item, other);
    this->selectItem(sequence);
}

