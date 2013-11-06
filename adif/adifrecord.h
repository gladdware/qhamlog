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

#ifndef ADIFRECORD_H
#define ADIFRECORD_H

#include "qsofields.h"

namespace adif
{

class AdifRecord
{
public:
    AdifRecord();
    virtual ~AdifRecord();

protected:
    /*
     * Minimum set of QSO fields:
     *   - call
     *   - qso_date
     *   - time_on
     *   - band
     *   - mode
     */
//    qso::QsoField<String> call;
//    qso::QsoField<Date> qso_date;
//    qso::QsoField<Time> time_on;
//    qso::QsoField<
};

} // namespace adif

#endif // ADIFRECORD_H
