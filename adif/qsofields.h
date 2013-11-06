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

#ifndef QSOFIELDS_H
#define QSOFIELDS_H

#include "adifdatatypes.h"
#include <string>

namespace adif
{

namespace qso
{

/*
 * QSO field data structure
 *   - Tag: the string tag defined in ADIF
 *   - Value: the datatype-specific value of the field
 */
template <typename T>
class QsoField
{
public:
    QsoField(const std::string &tag, const T &value);
    virtual ~QsoField();

    std::string getTag();
    T getValue();

protected:
    std::string tag;
    T value;
};

class QsoFieldTag
{
public:
    /*** QSO Field Tag Names **********************************************************************/
    static const std::string CALL;
    static const std::string QSO_DATE;
    static const std::string QSO_DATE_OFF;
    static const std::string TIME_ON;
    static const std::string TIME_OFF;
    static const std::string BAND;
    static const std::string MODE;
    static const std::string SUBMODE;
    static const std::string FREQ;
    static const std::string TX_PWR;
    static const std::string RST_SENT;
    static const std::string RST_RCVD;
    static const std::string QTH;
    static const std::string COUNTRY;
    static const std::string STATE;
    static const std::string CNTY;
    static const std::string COMMENT;
    static const std::string QSLMSG;

    virtual ~QsoFieldTag();

private:
    // never needs to be instantiated
    QsoFieldTag();
};

} // namespace qso

} // namespace adif

#endif // QSOFIELDS_H
