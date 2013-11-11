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
#include <QSqlQueryModel>
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
    static QSqlQueryModel *getBandsModel();
    static enums::Band getBand(const std::string &band);
    static enums::Band getBand(int bandId);

    static QSqlQueryModel *getModesModel();
    static enums::Mode getMode(const std::string &mode);
    static enums::Mode getMode(int modeId, int submodeId);

    static QSqlQueryModel *getCountriesModel(bool withDeleted = false);
    static enums::Country getCountry(const std::string &entityName);
    static enums::Country getCountry(int countryCode);

    static QSqlQueryModel *getPrimaryAdminSubModel(int countryCode);
    static enums::PrimaryAdminSub getPrimaryAdminSub(const std::string &name,
                                                     const enums::Country &country);
    static enums::PrimaryAdminSub getPrimaryAdminSub(int pasId, int countryCode);

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

    // define a data role for getting a row's primary key
    static const int DATA_ROLE_PK;

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
    friend Band AdifEnums::getBand(int bandId);

public:
    // custom data model for bands
    class Model : public QSqlQueryModel
    {
    public:
        Model(const QSqlDatabase &db, QObject *parent = NULL);
        virtual ~Model();

        virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;

        // model column names
        static const QString ID;
        static const QString BAND;
        static const QString MIN_FREQ_MHZ;
        static const QString MAX_FREQ_MHZ;
    };
};

class Mode : public Enum
{
public:
    ~Mode();

    std::string getValue() const;
    std::string getSubmode() const;

    static Mode createInvalid();

    // need an extra PK role for submode
    static const int DATA_ROLE_SUBMODE_PK;

protected:
    Mode(const std::string &mode, const std::string &submode);

    std::string mode;
    std::string submode;

    friend Mode AdifEnums::getMode(const std::string &mode);
    friend Mode AdifEnums::getMode(int modeId, int submodeId);

public:
    // custom data model for modes
    class Model : public QSqlQueryModel
    {
    public:
        Model(const QSqlDatabase &db, QObject *parent = NULL);
        virtual ~Model();

        virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;

        // model column names
        static const QString MODE_ID;
        static const QString MODE;
        static const QString SUBMODE_ID;
        static const QString SUBMODE;
    };
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
    friend Country AdifEnums::getCountry(int countryCode);

public:
    // custom data model for countries
    class Model : public QSqlQueryModel
    {
    public:
        Model(const QSqlDatabase &db, bool withDeleted = false, QObject *parent = NULL);
        virtual ~Model();

        virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;

        // model column names
        static const QString CODE;
        static const QString ENTITY_NAME;
        static const QString DELETED;

        // custom data roles
        static const int ROLE_PK;
    };
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
    friend PrimaryAdminSub AdifEnums::getPrimaryAdminSub(int pasId, int countryCode);

public:
    // custom data model for PAS
    class Model : public QSqlQueryModel
    {
    public:
        Model(const QSqlDatabase &db, int countryCode, QObject *parent = NULL);
        virtual ~Model();

        virtual QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;

        // model column names
        static const QString ID;
        static const QString CODE;
        static const QString NAME;
        static const QString COUNTRY_CODE;
    };
};

} // namespace enums

} // namespace adif

#endif // ADIFENUMS_H
