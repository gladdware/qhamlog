/*
 * QHamLog - Simple, cross-platform, ADIF-compliant Amateur Radio QSO logging application
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

#include "mainlogwindow.h"
#include "adifenums.h"
#include "qsolog.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // splash screen example: http://qt-project.org/forums/viewthread/16927

    /*
     * TODO: Do all of this initialization while displaying a splash screen. Also load up all of the
     * enumeration models now, so that the UI can just access them later.
     */

    // BEGIN INITIALIZATION

    QString appPath = QDir::homePath() + "/.qhamlog";
    QString adifEnumsDbPath = appPath + "/adif-enums.db";
    QString qsoLogDbPath = appPath + "/qso-log.db";

    // the application directory ${HOME}/.qhamlog
    QDir appDir(appPath);
    if(!appDir.exists()) {
        qDebug() << "Main: creating .qhamlog app directory: " << appPath;
        if(!appDir.mkpath(appPath)) {
            qCritical() << "Main: couldn't create .qhamlog app directory";
            return 1;
        }
    }

    // copy empty qso log if no log db file exists
    if(!QFile::exists(qsoLogDbPath)) {
        if(!QFile::copy(":/db/empty-qsolog", qsoLogDbPath)) {
            qCritical() << "Main: couldn't copy empty QSO log database to filesystem";
            return 1;
        } else {
            // set correct file permissions
            QFile logDb(qsoLogDbPath);
            QFile::Permissions perm = QFile::WriteOwner | QFile::ReadOwner | QFile::ReadGroup | QFile::ReadOther;
            if(!logDb.setPermissions(perm)) {
                qCritical() << "Main: couldn't set permissions on empty QSO log database";
                logDb.remove();
                return 1;
            }
        }
    }

    // remove any existing enum db file
    if(QFile::exists(adifEnumsDbPath) && !QFile::remove(adifEnumsDbPath)) {
        qWarning() << "Main: couldn't delete existing ADIF enums database";
    }

    // copy enum db file out
    if(!QFile::copy(":/db/adifenums", adifEnumsDbPath)) {
        qCritical() << "Main: couldn't copy new ADIF enums database to filesystem";
        return 1;
    }

    // init QSO log
    if(!log::QsoLog::init(qsoLogDbPath.toStdString())) {
        qCritical() << "Main: QSO log init failed";
        return 1;
    }

    // init ADIF enums
    if(!adif::AdifEnums::init(adifEnumsDbPath.toStdString())) {
        qCritical() << "Main: ADIF enums init failed";
        return 1;
    }

    // END INITIALIZATION

    MainLogWindow w;
    w.show();

    int r = a.exec();

    // cleanup
    log::QsoLog::destroy();
    adif::AdifEnums::destroy();

    return r;
}
