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

/*** QSO Field Tag Names **********************************************************************/
extern const std::string CALL;
extern const std::string QSO_DATE;
extern const std::string QSO_DATE_OFF;
extern const std::string TIME_ON;
extern const std::string TIME_OFF;
extern const std::string BAND;
extern const std::string MODE;
extern const std::string SUBMODE;
extern const std::string FREQ;
extern const std::string TX_PWR;
extern const std::string RST_SENT;
extern const std::string RST_RCVD;
extern const std::string QTH;
extern const std::string COUNTRY;
extern const std::string STATE;
extern const std::string CNTY;
extern const std::string COMMENT;
extern const std::string QSLMSG;

/*
 * QSO field data structure
 *   - Tag: the string tag defined in ADIF
 *   - Value: the datatype-specific value of the field
 */
class QsoField
{
public:
    QsoField(const std::string &tag, BaseDatatype *value);
    virtual ~QsoField();

    std::string getTag() const;
    BaseDatatype *getValue();

protected:
    std::string tag;
    BaseDatatype *value;
};

} // namespace qso

} // namespace adif

#endif // QSOFIELDS_H
