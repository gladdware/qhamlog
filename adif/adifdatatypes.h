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

/**
 * @brief Base ADIF datatype
 *
 * Every datatype must have a value that can turn into a string
 */
class BaseDatatype
{
public:
    /**
     * @brief Default constructor; sets the indicator to "invalid"
     */
    BaseDatatype();

    /**
     * @brief Constructor
     * @param indicator the indicator character to set for this datatype
     */
    BaseDatatype(const char &indicator);

    /**
     * @brief Destructor
     */
    virtual ~BaseDatatype();

    /**
     * @brief The "invalid" indicator
     */
    static const char INVALID_IND;

    /**
     * @brief Get the indicator character for this datatype
     * @return the datatype indicator
     */
    char getIndicator() const;

    /**
     * @brief Get this data type formatted as a string; this base class always returns the empty
     *   string
     * @return the empty string
     */
    virtual std::string getStr() const;

protected:
    char indicator;
};

/**
 * @brief Templated immutable datatype
 */
template <typename T>
class Datatype : public BaseDatatype
{
public:
    /**
     * @brief Destructor
     */
    virtual ~Datatype();

    /**
     * @brief see BaseDatatype.getStr()
     * @return the value of this datatype as a string
     */
    virtual std::string getStr() const = 0;

    /**
     * @brief Gets the value of this datatype
     * @return the value of this datatype
     */
    T get() const;

protected:
    /**
     * @brief Constructor
     * @param indicator the datatype indicator character
     * @param data the datatype value
     */
    Datatype(const char &indicator, const T &data);

private:
    T data;
};

/**
 * @brief Real number
 */
class Number : public Datatype<double>
{
public:
    /**
     * @brief Constructor
     * @param num the floating point datatype value
     */
    Number(double num);

    /**
     * @brief Constructor
     * @param num the integer datatype value
     */
    Number(int num);

    /**
     * @brief Destructor
     */
    virtual ~Number();

    /**
     * @brief Get this Number formatted as a string
     * @return this Number as a string
     */
    virtual std::string getStr() const;

private:
    bool isInteger;
};

/**
 * @brief Date (year, month, and day)
 */
class Date : public Datatype<time_t>
{
public:
    /**
     * @brief Constructor
     * @param date the datetime datatype value (only used for date)
     */
    Date(const time_t &date);

    /**
     * @brief Destructor
     */
    virtual ~Date();

    /**
     * @brief Get this Date formatted as a string
     * @return this Date as a string
     */
    virtual std::string getStr() const;
};

/**
 * @brief Time (hour, minute, and second)
 */
class Time : public Datatype<time_t>
{
public:
    /**
     * @brief Constructor
     * @param time the datetime datatype value (only used for time)
     */
    Time(const time_t &time);

    /**
     * @brief Destructor
     */
    virtual ~Time();

    /**
     * @brief Get this Date formatted as a string
     * @return this Date as a string
     */
    virtual std::string getStr() const;
};

/**
 * @brief String
 *
 * No multi-line strings permitted; newlines replaced with spaces
 */
class String : public Datatype<std::string>
{
public:
    /**
     * @brief Constructor
     * @param str the string datatype value (newlines converted to spaces)
     */
    String(const std::string &str);

    /**
     * @brief Destructor
     */
    virtual ~String();

    /**
     * @brief Get this String formatted as a string
     * @return this String as a string
     */
    virtual std::string getStr() const;
};

/**
 * @brief Multiline String
 */
class MultilineString : public Datatype<std::string>
{
public:
    /**
     * @brief Constructor
     * @param str the string datatype value
     */
    MultilineString(const std::string &str);

    /**
     * @brief Destructor
     */
    virtual ~MultilineString();

    /**
     * @brief Get this multiline String formatted as a string
     * @return this multiline String as a string
     */
    virtual std::string getStr() const;
};

// Enumeration
/**
 * @brief Enumeration
 *
 * Really just a string with a unique indicator
 */
class Enumeration : public Datatype<std::string>
{
public:
    /**
     * @brief Constructor
     * @param str the enumeration datatype value
     */
    Enumeration(const std::string &str);

    /**
     * @brief Destructor
     */
    virtual ~Enumeration();

    /**
     * @brief Get this Enumeration formatted as a string
     * @return this Enumeration as a string
     */
    virtual std::string getStr() const;
};

} // namespace adif

#endif // ADIFDATATYPES_H
