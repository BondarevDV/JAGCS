#ifndef INIT_MIGRATION_H
#define INIT_MIGRATION_H

#include "db_migration.h"

namespace db
{
    class InitMigration: public DbMigration
    {
    public:
        bool up() override;
        bool down() override;

        QDateTime version() const override;
    };
}

#endif // INIT_MIGRATION_H
