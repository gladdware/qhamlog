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

#include "qsofields.h"

namespace adif
{

namespace qso
{

const std::string CALL = "CALL";
const std::string QSO_DATE = "QSO_DATE";
const std::string QSO_DATE_OFF = "QSO_DATE_OFF";
const std::string TIME_ON = "TIME_ON";
const std::string TIME_OFF = "TIME_OFF";
const std::string BAND = "BAND";
const std::string MODE = "MODE";
const std::string SUBMODE = "SUBMODE";
const std::string FREQ = "FREQ";
const std::string TX_PWR = "TX_PWR";
const std::string RST_SENT = "RST_SENT";
const std::string RST_RCVD = "RST_RCVD";
const std::string QTH = "QTH";
const std::string COUNTRY = "COUNTRY";
const std::string STATE = "STATE";
const std::string CNTY = "CNTY";
const std::string COMMENT = "COMMENT";
const std::string QSLMSG = "QSLMSG";


/*** QSO Field base type ***/

QsoField::QsoField(const std::string &tag, const BaseDatatype &value)
    : tag(tag),
      value(value)
{
    // nop
}

QsoField::~QsoField()
{
    // nop
}

std::string QsoField::getTag()
{
    return tag;
}

BaseDatatype QsoField::getValue()
{
    return value;
}

} // namespace qso

} // namespace adif
