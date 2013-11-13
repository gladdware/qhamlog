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
#include "adifenums.h"
#include <list>
#include <string>

namespace adif
{

class AdifRecord
{
public:
    AdifRecord();
    virtual ~AdifRecord();

    /**
     * @brief Alias for a const iterator derived from our fields list
     */
    typedef std::list<qso::QsoField>::const_iterator QsoFieldsIter;

    /**
     * @brief Get the number of QSO fields in this record
     * @return the number of QSO fields in this record
     */
    unsigned getNumFields();

    /**
     * @brief Retrieve the const iterator for this record's QSO fields
     * @return Const iterator for this record's QSO fields
     */
    QsoFieldsIter getFieldsIterator() const;

    /**
     * @brief Retrieve the 'end' iterator for this record's QSO fields
     * @return Const iterator for the end of this record's QSO fields
     */
    QsoFieldsIter getFieldsEnd() const;

    /**
     * @brief Adds a QSO field to this record
     * @param field the QSO field to add
     */
    void addField(const qso::QsoField &field);

    /**
     * @brief Check if this record has the minimum set of QSO fields
     * @return true if this record contains the minimum set of QSO fields
     */
    bool isValid() const;

    /**
     * @brief Format this record as a string (e.g., for logging)
     * @return this record formatted as a string
     */
    std::string toString() const;

protected:
    /**
     * @brief The set of QSO fields that make up this record
     */
    std::list<qso::QsoField> qsoFields;
};

} // namespace adif

#endif // ADIFRECORD_H
