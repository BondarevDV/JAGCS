#include "db_manager.h"

// Qt
#include <QFileInfo>
#include <QSqlError>
#include <QDebug>

// Internal
#include "db_migrator.h"

namespace
{
    const QString connectionType = "QSQLITE";
}

using namespace db;

DbManager::DbManager(QObject* parent):
    QObject(parent),
    m_db(QSqlDatabase::contains() ? QSqlDatabase::database() :
                                    QSqlDatabase::addDatabase(::connectionType))
{
    DbMigrationFactory factory;
    m_migrator = new DbMigrator(&factory, this);

    connect(m_migrator, &DbMigrator::message, this, &DbManager::onMigratorMessage);
}

DbManager::~DbManager()
{}

bool DbManager::open(const QString& dbName)
{
    QFileInfo file(dbName);
    bool exist = file.exists();

    m_db.setDatabaseName(dbName);
    bool ok = m_db.open();

    if (ok && exist)
    {
        ok = m_migrator->clarifyVersion();
    }

    if (!ok)
    {
        this->onMigratorMessage(m_db.lastError().text());
        return false;
    }

    return m_migrator->migrate();
}

bool DbManager::migrateLastVersion()
{
    return m_migrator->migrate();
}

bool DbManager::drop()
{
    this->close();
    return m_migrator->drop();
}

void DbManager::clarify()
{
    m_migrator->clarifyVersion();
}

void DbManager::close()
{
    m_migrator->reset();
    m_db.close();
}

void DbManager::clearLog()
{
    m_dbLog.clear();
    emit logChanged(m_dbLog);
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

QDateTime DbManager::migrationVersion() const
{
    return m_migrator->version();
}

void DbManager::onMigratorMessage(const QString& error)
{
    m_dbLog << error;
    emit logChanged(m_dbLog);
}

QStringList DbManager::dbLog() const
{
    return m_dbLog;
}
