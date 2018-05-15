#include "map_settings_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "settings_provider.h"

using namespace presentation;

MapSettingsPresenter::MapSettingsPresenter(QObject* parent):
    BasePresenter(parent)
{}

void MapSettingsPresenter::updateView()
{
    this->setViewProperty(PROPERTY(plugin),
                          settings::Provider::value(settings::map::plugin));
    this->setViewProperty(PROPERTY(osmActiveMapType),
                          settings::Provider::value(settings::map::osmActiveMapType));
    this->setViewProperty(PROPERTY(mapBoxActiveMapType),
                          settings::Provider::value(settings::map::mapBoxActiveMapType));
    this->setViewProperty(PROPERTY(esriActiveMapType),
                          settings::Provider::value(settings::map::esriActiveMapType));
    this->setViewProperty(PROPERTY(cacheSize),
                          settings::Provider::value(settings::map::cacheSize));
    this->setViewProperty(PROPERTY(highdpiTiles),
                          settings::Provider::value(settings::map::highdpiTiles));
    this->setViewProperty(PROPERTY(trackLength),
                          settings::Provider::value(settings::map::trackLength));

    this->setViewProperty(PROPERTY(changed), false);
}

void MapSettingsPresenter::save()
{
    settings::Provider::setValue(settings::map::plugin,
                                 this->viewProperty(PROPERTY(plugin)));
    settings::Provider::setValue(settings::map::osmActiveMapType,
                                 this->viewProperty(PROPERTY(osmActiveMapType)));
    settings::Provider::setValue(settings::map::mapBoxActiveMapType,
                                 this->viewProperty(PROPERTY(mapBoxActiveMapType)));
    settings::Provider::setValue(settings::map::esriActiveMapType,
                                 this->viewProperty(PROPERTY(esriActiveMapType)));
    settings::Provider::setValue(settings::map::cacheSize,
                                 this->viewProperty(PROPERTY(cacheSize)));
    settings::Provider::setValue(settings::map::highdpiTiles,
                                 this->viewProperty(PROPERTY(highdpiTiles)));
    settings::Provider::setValue(settings::map::trackLength,
                                 this->viewProperty(PROPERTY(trackLength)).toInt());

    this->setViewProperty(PROPERTY(changed), false);
}

void MapSettingsPresenter::connectView(QObject* view)
{
#ifdef WITH_MAPBOXGL
    view->setProperty(PROPERTY(plugins), QStringList({ "OSM", "MapBox GL", "Esri" }));
#else
    view->setProperty(PROPERTY(plugins), QStringList({ "OSM", "MapBox", "Esri" }));
#endif
}
