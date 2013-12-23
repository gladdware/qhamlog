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

#ifndef SQLITEDBPROVIDER_H
#define SQLITEDBPROVIDER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class SqliteDbProvider
{
public:
    SqliteDbProvider(const QString &name);
    virtual ~SqliteDbProvider();

protected:
    static const QString SQLITE_DRIVER;
    static const QString DEFAULT_NAME;

    bool openDb(const QString &dbFilename);

    QSqlQuery exec(const QString &query);

    QSqlDatabase db;

private:
    QString connName;
};

#endif // SQLITEDBPROVIDER_H
