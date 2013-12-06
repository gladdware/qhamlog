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

#include "qsovalidator.h"

#include <QDebug>

namespace log
{

QString QsoValidator::lastError = "";

QsoValidator::QsoValidator()
{
    // nop
}

QsoValidator::~QsoValidator()
{
    // nop
}

bool QsoValidator::validateQso(const Qso &qso)
{
    /*
     * The minimum set of data fields we need for a "valid" record are:
     *   -Callsign
     *   -Date/Time on
     *   -Band
     *   -Mode
     */

    // callsign must be non-null and non-empty
    if(qso.callsign.isNull() || qso.callsign.isEmpty()) {
        qCritical() << "qso validator: invalid callsign " << qso.callsign;
        setLastError("Callsign must be at least three characters");
        return false;
    }

    // time on must be non-null
    if(qso.timeOnUtc.date().isNull() || qso.timeOnUtc.time().isNull()) {
        qCritical() << "qso validator: invalid date/time on " << qso.timeOnUtc;
        setLastError("Time on (date and time) must be defined");
        return false;
    }

    // TODO should we validate band/mode against official enumerations?

    // band must be non-null and non-empty
    if(qso.band.isNull() || qso.band.isEmpty()) {
        qCritical() << "qso validator: invalid band " << qso.band;
        setLastError("Band must be selected");
        return false;
    }

    // mode must be non-null and non-empty
    if(qso.mode.isNull() || qso.mode.isEmpty()) {
        qCritical() << "qso validator: invalid mode " << qso.mode;
        setLastError("Mode must be selected");
        return false;
    }

    // we made it!
    return true;
}

QString QsoValidator::getLastError()
{
    return lastError;
}

void QsoValidator::setLastError(const QString &errMsg)
{
    lastError.clear();
    lastError.append(errMsg);
}

} // namespace log
