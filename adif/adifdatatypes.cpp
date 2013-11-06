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

    qDebug() << "Replacing newlines in \"" << str.c_str() << "\"";

#ifdef PLAT_WIN
    // search for CRNL
    while((pos = result.find(crnl, pos)) != std::string::npos) {
        // replace with a space
        qDebug() << "  at pos " << pos;
        result.replace(pos, crnl.size(), rep);
    }
#endif

#ifdef PLAT_NIX
    // search for
    while((pos = result.find(nl, pos)) != std::string::npos) {
        // replace with a space
        qDebug() << "  at pos " << pos;
        result.replace(pos, nl.size(), rep);
    }
#endif

    return result;
}

template <typename T> Datatype<T>::Datatype(const char &indicator, const T &data)
    : indicator(indicator),
      data(data)
{
    // nop
}

template <typename T> Datatype<T>::~Datatype()
{
    // nop
}

template <typename T> T Datatype<T>::get()
{
    return data;
}

Number::Number(float num)
    : Datatype<float>('N', num)
{
    // nop
}

Number::~Number()
{
    // nop
}

Date::Date(const time_t &dt)
    : Datatype<time_t>('D', dt)
{
    // nop
}

Date::~Date()
{
    // nop
}

Time::Time(const time_t &dt)
    : Datatype<time_t>('T', dt)
{
    // nop
}

Time::~Time()
{
    // nop
}

String::String(const std::string &str)
    : Datatype<std::string>('S', replaceNewlines(str))
{
    // nop
}

String::~String()
{
    // nop
}

MultilineString::MultilineString(const std::string &str)
    : Datatype<std::string>('M', str)
{
    // nop
}

MultilineString::~MultilineString()
{
    // nop
}

}
