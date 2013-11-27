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
        return false;
    }

    // time on must be non-null
    if(qso.timeOnUtc.date().isNull() || qso.timeOnUtc.time().isNull()) {
        qCritical() << "qso validator: invalid date/time on " << qso.timeOnUtc;
        return false;
    }

    // TODO should we validate band/mode against official enumerations?

    // band must be non-null and non-empty
    if(qso.band.isNull() || qso.band.isEmpty()) {
        qCritical() << "qso validator: invalid band " << qso.band;
        return false;
    }

    // mode must be non-null and non-empty
    if(qso.mode.isNull() || qso.mode.isEmpty()) {
        qCritical() << "qso validator: invalid mode " << qso.mode;
    }

    // we made it!
    return true;
}

} // namespace log
