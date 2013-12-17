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

#ifndef LOGCONVERTER_H
#define LOGCONVERTER_H

#include "adifrecord.h"
#include "qsolog.h"

namespace utils
{

class LogConverter
{
public:
    /**
     * @brief Destructor
     */
    virtual ~LogConverter();

    /**
     * @brief Convert the given QSO to an ADIF record, saving into the one given
     * @param adifRecord The record to save values into
     * @param qso The QSO to pull record data from
     * @return true if the conversion is successful
     */
    static bool qsoToAdif(adif::AdifRecord &adifRecord, const log::Qso &qso);

protected:
    /**
     * @brief Constructor (don't need to instantiate)
     */
    LogConverter();
};

} // namespace utils

#endif // LOGCONVERTER_H
