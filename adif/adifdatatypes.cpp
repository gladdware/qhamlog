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

#include "adifdatatypes.h"

#include <QDebug>
#include <iomanip>
#include <sstream>

namespace adif
{

/*
 * Platform-specific newline replacement routine
 */
std::string replaceNewlines(const std::string &str)
{
    static const std::string nl = "\n";
    static const std::string crnl = "\r\n";
    static const std::string rep = " ";

    size_t pos = 0;
    std::string result = str;

//    qDebug() << "Replacing newlines in \"" << str.c_str() << "\"";

#ifdef PLAT_WIN
    // search for CRNL
    while((pos = result.find(crnl, pos)) != std::string::npos) {
        // replace with a space
        qDebug() << "  at pos " << pos;
        result.replace(pos, crnl.size(), rep);
    }
#endif

#ifdef PLAT_NIX
    // search for NL
    while((pos = result.find(nl, pos)) != std::string::npos) {
        // replace with a space
        qDebug() << "  at pos " << pos;
        result.replace(pos, nl.size(), rep);
    }
#endif

    return result;
}

const char BaseDatatype::INVALID_IND = 'X';
const std::string BaseDatatype::INVALID_STR = "**INVALID**";

BaseDatatype::BaseDatatype()
    : indicator(INVALID_IND),
      value(INVALID_STR)
{
    // nop
}

BaseDatatype::BaseDatatype(const char &indicator)
    : indicator(indicator),
      value(INVALID_STR)
{
    // nop
}

BaseDatatype::BaseDatatype(const char &indicator, const std::string &value)
    : indicator(indicator),
      value(value)
{
    // nop
}

BaseDatatype::~BaseDatatype()
{
    // nop
}

char BaseDatatype::getIndicator() const
{
    return indicator;
}

std::string BaseDatatype::getStr() const
{
    return value;
}

void BaseDatatype::setValue(const std::string &val)
{
    value = val;
}

Number::Number(double num)
    : BaseDatatype('N')
{
    std::ostringstream ss;

    ss << std::setprecision(10);
    ss << num;

    setValue(ss.str());
}

Number::Number(int num)
    : BaseDatatype('N')
{
    std::ostringstream ss;

    ss << std::setprecision(0);
    ss << num;

    setValue(ss.str());
}

Number::~Number()
{
    // nop
}

Date::Date(const time_t &dt)
    : BaseDatatype('D')
{
    char fmtTime[9] = { '\0' };
    time_t date = dt;
    tm *utcTime = gmtime(&date);

    strftime(fmtTime, 9, "%Y%m%d", utcTime);

    setValue(std::string(fmtTime));
}

Date::~Date()
{
    // nop
}

Time::Time(const time_t &dt)
    : BaseDatatype('T')
{
    char fmtTime[7] = { '\0' };
    time_t time = dt;
    tm *utcTime = gmtime(&time);

    strftime(fmtTime, 7, "%H%M%S", utcTime);

    setValue(std::string(fmtTime));
}

Time::~Time()
{
    // nop
}

String::String(const std::string &str)
    : BaseDatatype('S', replaceNewlines(str))
{
    // nop
}

String::~String()
{
    // nop
}

MultilineString::MultilineString(const std::string &str)
    : BaseDatatype('M', str)
{
    // nop
}

MultilineString::~MultilineString()
{
    // nop
}

Enumeration::Enumeration(const std::string &str)
    : BaseDatatype('E', str)
{
    // nop
}

Enumeration::~Enumeration()
{
    // nop
}

}
