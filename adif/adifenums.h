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
class PrimaryAdminSub;
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

    /*
     * For each enumeration type we need two functions: 1) to populate UI components, and 2) to
     * retrieve a specific enum data structure based on user selection.
     */
    static QStringList getBands();
    static enums::Band getBand(const std::string &band);

    static QStringList getModes();
    static enums::Mode getMode(const std::string &mode);

    static QStringList getCountries();
    static enums::Country getCountry(const std::string &entityName);

    static QStringList getPrimaryAdminSubs(const enums::Country &country);
    static enums::PrimaryAdminSub getPrimaryAdminSub(const std::string &name,
                                                     const enums::Country &country);

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

    virtual std::string getValue() const = 0;

    bool isValid() const;

protected:
    Enum();

    bool valid;

    friend class AdifEnums;
};

class Band : public Enum
{
public:
    ~Band();

    std::string getValue() const;

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

    std::string getValue() const;
    std::string getSubmode() const;

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

    std::string getValue() const;
    unsigned getCode() const;

    static Country createInvalid();

protected:
    Country(unsigned code, const std::string &entityName, bool deleted);

    unsigned code;
    std::string entityName;
    bool deleted;

    friend Country AdifEnums::getCountry(const std::string &entityName);
};

class PrimaryAdminSub : public Enum
{
public:
    ~PrimaryAdminSub();

    std::string getValue() const;
    std::string getName() const;

    static PrimaryAdminSub createInvalid();

protected:
    PrimaryAdminSub(const std::string &code, const std::string &name, unsigned countryCode);

    std::string code;
    std::string name;
    unsigned countryCode;

    friend PrimaryAdminSub AdifEnums::getPrimaryAdminSub(const std::string &name,
                                                         const Country &country);
};

} // namespace enums

} // namespace adif

#endif // ADIFENUMS_H
