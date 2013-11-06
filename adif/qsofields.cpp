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

/*** QSO Field base type ***/

template <typename T> QsoField<T>::QsoField(const std::string &tag, const T &value)
    : tag(tag),
      value(value)
{
    // nop
}

template <typename T> QsoField<T>::~QsoField()
{
    // nop
}

template <typename T> std::string QsoField<T>::getTag()
{
    return tag;
}

template <typename T> T QsoField<T>::getValue()
{
    return value;
}

/*** QSO Fields Tags ***/
QsoFieldTag::QsoFieldTag() {}
QsoFieldTag::~QsoFieldTag() {}

const std::string QsoFieldTag::CALL = "CALL";
const std::string QsoFieldTag::QSO_DATE = "QSO_DATE";
const std::string QsoFieldTag::QSO_DATE_OFF = "QSO_DATE_OFF";
const std::string QsoFieldTag::TIME_ON = "TIME_ON";
const std::string QsoFieldTag::TIME_OFF = "TIME_OFF";
const std::string QsoFieldTag::BAND = "BAND";
const std::string QsoFieldTag::MODE = "MODE";
const std::string QsoFieldTag::SUBMODE = "SUBMODE";
const std::string QsoFieldTag::FREQ = "FREQ";
const std::string QsoFieldTag::TX_PWR = "TX_PWR";
const std::string QsoFieldTag::RST_SENT = "RST_SENT";
const std::string QsoFieldTag::RST_RCVD = "RST_RCVD";
const std::string QsoFieldTag::QTH = "QTH";
const std::string QsoFieldTag::COUNTRY = "COUNTRY";
const std::string QsoFieldTag::STATE = "STATE";
const std::string QsoFieldTag::CNTY = "CNTY";
const std::string QsoFieldTag::COMMENT = "COMMENT";
const std::string QsoFieldTag::QSLMSG = "QSLMSG";

} // namespace qso

} // namespace adif
