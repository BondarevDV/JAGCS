#ifndef VEHICLE_MAP_ITEM_MODEL_H
#define VEHICLE_MAP_ITEM_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class TelemetryService;
    class Position;
    class Sns;
}

namespace presentation
{
    class VehicleMapItemModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum VehicleMapItemRoles
        {
            CoordinateRole = Qt::UserRole + 1,
            DirectionRole,
            MarkRole,
            VehicleIdRole,
            TrackRole,
            HdopRadius
        };

        VehicleMapItemModel(db::DbFacade* dbFacade,
                            domain::TelemetryService* telemetryService,
                            QObject* parent = nullptr);
        ~VehicleMapItemModel() override;

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void onVehicleAdded(const db::VehiclePtr& vehicle);
        void onVehicleRemoved(const db::VehiclePtr& vehicle);

    protected:
        QHash<int, QByteArray> roleNames() const override;

        QModelIndex vehicleIndex(int vehicleId) const;
        void onVehicleTelemetryChanged(int vehicleId, const QStringList& parameters);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // VEHICLE_MAP_ITEM_MODEL_H