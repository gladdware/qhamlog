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
 * Every datatype must have an indicator character and a value that can turn into a string
 */
class BaseDatatype
{
public:
    /**
     * @brief Default constructor; sets the indicator and value to "invalid"
     */
    BaseDatatype();

    /**
     * @brief Constructor; sets the value to "invalid"
     * @param indicator the indicator character to set for this datatype
     */
    BaseDatatype(const char &indicator);

    /**
     * @brief Constructor
     * @param indicator the indicator character to set for this datatype
     * @param value the data value string to set
     */
    BaseDatatype(const char &indicator, const std::string &value);

    /**
     * @brief Destructor
     */
    virtual ~BaseDatatype();

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

    /**
     * @brief The "invalid" indicator
     */
    static const char INVALID_IND;

    /**
     * @brief The "invalid" value string
     */
    static const std::string INVALID_STR;

protected:
    /**
     * @brief Let derived classes set the value
     * @param value the value string to set
     */
    void setValue(const std::string &val);

    char indicator;
    std::string value;
};

/**
 * @brief Real number
 */
class Number : public BaseDatatype
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

};

/**
 * @brief Date (year, month, and day)
 */
class Date : public BaseDatatype
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

};

/**
 * @brief Time (hour, minute, and second)
 */
class Time : public BaseDatatype
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

};

/**
 * @brief String
 *
 * No multi-line strings permitted; newlines replaced with spaces
 */
class String : public BaseDatatype
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

};

/**
 * @brief Multiline String
 */
class MultilineString : public BaseDatatype
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

};

// Enumeration
/**
 * @brief Enumeration
 *
 * Really just a string with a unique indicator
 */
class Enumeration : public BaseDatatype
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

};

} // namespace adif

#endif // ADIFDATATYPES_H
