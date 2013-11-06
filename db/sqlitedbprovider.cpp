/*
 * This file is part of QHamLog
 * Copyright (C) 2013 Alex Gladd
 *
 * QHamLog is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QHamLog is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QHamLog.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "sqlitedbprovider.h"

#include <QDebug>

const QString SqliteDbProvider::SQLITE_DRIVER = "QSQLITE";
const QString SqliteDbProvider::DEFAULT_NAME = QString(QSqlDatabase::defaultConnection);

SqliteDbProvider::SqliteDbProvider(const QString &name)
    : connName(name)
{
    // verify connection name
    if(connName.isEmpty() || connName.isNull()) {
        qDebug() << "Using default connection name: " << DEFAULT_NAME;
        connName = DEFAULT_NAME;
    }

    // get database ref
    db = QSqlDatabase::database(name, false);
    if(!db.isValid()) {
        // not added yet; add it
        qDebug() << "Database name " << name << " does not exist yet";
        db = QSqlDatabase::addDatabase(SQLITE_DRIVER, name);

        if(!db.isValid()) {
            // couldn't add new database
            qCritical() << "Failed to load new database connection (" << connName << ", "
                     << SQLITE_DRIVER << ")";

            // TODO this might be fatal
        } else {
            qDebug() << "New database connection " << connName << "added";
        }
    }
}

SqliteDbProvider::~SqliteDbProvider()
{
    if(db.isValid() && db.isOpen()) {
        qDebug() << "Closing database (" << connName << ")";
        db.close();
    }
}

bool SqliteDbProvider::openDb(const QString &dbFilename)
{
    if(!db.isValid()) {
        qWarning() << "Can't open " << dbFilename << " (db invalid)";
        return false;
    } else if(db.isOpen()) {
        qWarning() << "Can't open " << dbFilename << " (db already open)";
        return false;
    }

    db.setDatabaseName(dbFilename);

    if(!db.open()) {
        qCritical() << "Database " << dbFilename << " open failed (" << db.lastError().text() << ")";
        return false;
    } else {
        qDebug() << "Successfully opened database " << dbFilename;
        return true;
    }
}

QSqlQuery SqliteDbProvider::exec(const QString &query)
{
    return db.exec(query);
}
