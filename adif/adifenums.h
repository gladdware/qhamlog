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

#ifndef ADIFENUMS_H
#define ADIFENUMS_H

#include "sqlitedbprovider.h"

#include <QStringList>
#include <list>
#include <string>

namespace adif
{

// forward decls
namespace enums
{
class Enum;
class Band;
class Mode;
class Country;
}

/*
 * AdifEnums defines and manages SQLite storage for static ADIF enumerations
 */
class AdifEnums : public SqliteDbProvider
{
public:
    virtual ~AdifEnums();

    static bool init(const std::string &dbPath);

    static void destroy();

    static QStringList getBands();
    static enums::Band getBand(const std::string &band);

    static QStringList getModes();
    static enums::Mode getMode(const std::string &mode);

    static QStringList getCountries();
    static enums::Country getCountry(const std::string &entityName);

protected:
    AdifEnums();

    static AdifEnums *instance;

private:
//    static bool buildEnumTable(const std::string &createTable, const std::list<std::string> &inserts);

};

namespace enums
{

/*
 * Pure virtual enumeration class
 */
class Enum
{
public:
    virtual ~Enum();

    virtual std::string getValue() = 0;

    bool isValid();

protected:
    Enum();

    bool valid;

    friend class AdifEnums;
};

class Band : public Enum
{
public:
    ~Band();

    std::string getValue();

    static Band createInvalid();

protected:
    Band(const std::string &band, float minMhz, float maxMhz);

private:
    std::string band;
    float minMhz;
    float maxMhz;

    friend Band AdifEnums::getBand(const std::string &band);
};

class Mode : public Enum
{
public:
    ~Mode();

    std::string getValue();
    std::string getSubmode();

    static Mode createInvalid();

protected:
    Mode(const std::string &mode, const std::string &submode);

    std::string mode;
    std::string submode;

    friend Mode AdifEnums::getMode(const std::string &mode);
};

class Country : public Enum
{
public:
    ~Country();

    std::string getValue();
    unsigned getCode();

    static Country createInvalid();

protected:
    Country(unsigned code, const std::string &entityName, bool deleted);

    unsigned code;
    std::string entityName;
    bool deleted;

    friend Country AdifEnums::getCountry(const std::string &entityName);
};

} // namespace enums

} // namespace adif

#endif // ADIFENUMS_H
