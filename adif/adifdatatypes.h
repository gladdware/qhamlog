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

#ifndef ADIFDATATYPES_H
#define ADIFDATATYPES_H

#include <ctime>
#include <string>

namespace adif
{

/*
 * Defines the set of ADIF data types
 * http://adif.org/304/ADIF_304.htm#Data_Types
 */

/*
 * Base templated datatype
 * Should never be directly instanciated
 */
template <typename T>
class Datatype
{
public:
    virtual ~Datatype();

    T get();

protected:
    Datatype(const char &indicator, const T &data);

private:
    char indicator;
    T data;
};

// Real number
class Number : public Datatype<float>
{
public:
    Number(float num);
    virtual ~Number();
};

// Date (year, month, day)
class Date : public Datatype<time_t>
{
public:
    Date(const time_t &dt);
    virtual ~Date();
};

// Time (hour, minute, second)
class Time : public Datatype<time_t>
{
public:
    Time(const time_t &t);
    virtual ~Time();
};

// String
// No multi-line strings permitted; newlines replaced with spaces
class String : public Datatype<std::string>
{
public:
    String(const std::string &str);
    virtual ~String();
};

// Multiline string
class MultilineString : public Datatype<std::string>
{
public:
    MultilineString(const std::string &str);
    virtual ~MultilineString();
};



} // namespace adif

#endif // ADIFDATATYPES_H
