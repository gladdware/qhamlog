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
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // splash screen example: http://qt-project.org/forums/viewthread/16927

    /*
     * TODO: Do all of this initialization while displaying a splash screen. Also load up all of the
     * enumeration models now, so that the UI can just access them later.
     */

    QString appPath = QCoreApplication::applicationDirPath();
    QString adifEnumsDbPath = appPath + "/adif-enums.db";

    // remove any existing db files
    if(QFile::exists(adifEnumsDbPath) && !QFile::remove(adifEnumsDbPath)) {
        qWarning() << "Couldn't delete existing ADIF enums database";
    }

    // copy db files out
    if(!QFile::copy(":/db/adifenums", adifEnumsDbPath)) {
        qCritical() << "Couldn't copy new ADIF enums database to filesystem";
        return 1;
    }

    // init ADIF enums
    if(!adif::AdifEnums::init(adifEnumsDbPath.toStdString())) {
        qCritical() << "ADIF enums init failed";
        return 1;
    }

    MainLogWindow w;
    w.show();

    int r = a.exec();

    // cleanup
    adif::AdifEnums::destroy();

    return r;
}
