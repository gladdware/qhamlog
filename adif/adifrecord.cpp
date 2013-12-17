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

#include <QDebug>
#include <sstream>

namespace adif
{

AdifRecord::AdifRecord()
{
    // nop
}

AdifRecord::~AdifRecord()
{
    QsoFieldsIter iter;
    for(iter = getFieldsIterator(); iter != getFieldsEnd(); iter++) {
        qso::QsoField *qf = (*iter);
        delete qf;
        qf = NULL;
    }

    qsoFields.clear();
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

void AdifRecord::addField(qso::QsoField *field)
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
    QsoFieldsIter iter;
    std::stringstream ss;

    ss << "ADIF Record {\n";

    for(iter = getFieldsIterator(); iter != getFieldsEnd(); iter++) {
        qso::QsoField *cur = (*iter);
//        qDebug() << "about to print qso field; value=" << cur.getValue();
//        qDebug() << "tag=" << cur->getTag().c_str();
//        qDebug() << "ind=" << QString(cur->getValue()->getIndicator());
//        qDebug() << "val=" << cur->getValue()->getStr().c_str();
        ss << "  " << cur->getTag() << "[" << cur->getValue()->getIndicator() << "]: " << cur->getValue()->getStr() << "\n";
    }

    ss << "}";

    return ss.str();
}

} // namespace adif
