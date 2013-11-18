#
# This file is part of QHamLog
# Copyright (C) 2013 Alex Gladd
#
# QHamLog is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# QHamLog is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with QHamLog.  If not, see <http://www.gnu.org/licenses/>.
#
#-------------------------------------------------
#
# QHamLog - Simple, cross-platform, ADIF-compliant Amateur Radio QSO logging application
# Project created by QtCreator 2013-10-26T14:34:33
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QHamLog
TEMPLATE = app

win32 {
    DEFINES += PLAT_WIN
}

linux|macx {
    DEFINES += PLAT_NIX
}

SOURCES += main.cpp

include(util/util.pri)
include(db/db.pri)
include(adif/adif.pri)
include(log/log.pri)
include(ui/ui.pri)

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    README.md \
    sql/bands.sql \
    sql/modes.sql \
    sql/locations.sql \
    sql/qsolog.sql
