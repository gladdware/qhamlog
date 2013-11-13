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

#include "adifrecord.h"

#include <sstream>

namespace adif
{

AdifRecord::AdifRecord()
{
    // nop
}

AdifRecord::~AdifRecord()
{
    // nop
}

unsigned AdifRecord::getNumFields()
{
    return qsoFields.size();
}

AdifRecord::QsoFieldsIter AdifRecord::getFieldsIterator() const
{
    return qsoFields.begin();
}

AdifRecord::QsoFieldsIter AdifRecord::getFieldsEnd() const
{
    return qsoFields.end();
}

void AdifRecord::addField(const qso::QsoField &field)
{
    qsoFields.push_back(field);
}

/*
 * Minimum set of QSO fields:
 *   - call
 *   - qso_date
 *   - time_on
 *   - band
 *   - mode
 *
 * http://adif.org/304/ADIF_304_Resources.htm#ADIFImplementationNotes
 */
bool AdifRecord::isValid() const
{
    // TODO
    return true;
}

std::string AdifRecord::toString() const
{
    return std::string("AdifRecord:");
}

} // namespace adif
