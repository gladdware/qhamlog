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

#include "adifenums.h"

#include <QDebug>

namespace adif
{

AdifEnums *AdifEnums::instance = NULL;

AdifEnums::AdifEnums()
    : SqliteDbProvider("adif_enums")
{
}

AdifEnums::~AdifEnums()
{
    // nop
}

bool AdifEnums::init(const std::string &dbPath)
{
    if(instance == NULL) {
        qDebug() << "Creating ADIF enums instance";
        instance = new AdifEnums();
    }

    if(!instance->openDb(QString(dbPath.c_str()))) {
        qCritical() << "Failed to open memory DB for enums";
        return false;
    } else {
        return true;
    }
}

void AdifEnums::destroy()
{
    if(instance != NULL) {
        delete instance;
    }
}

QStringList AdifEnums::getBands()
{
    QStringList bandList;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized!";
        return bandList;
    }

    qDebug() << "Querying for ADIF bands";
    QSqlQuery q(instance->db);

    if(!q.exec("select band from bands order by min_freq_mhz asc")) {
        qCritical() << "ADIF bands query failed: " << q.lastError();
    } else {
        while(q.next()) {
            bandList << q.value(0).toString();
        }
    }

    return bandList;
}

enums::Band AdifEnums::getBand(const std::string &band)
{
    std::string vBand;
    float vMinFreq, vMaxFreq;

//    qDebug() << "Trying to get band for val " << QString(band.c_str());

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return enums::Band::createInvalid();
    }

    QSqlQuery q(instance->db);
    q.prepare("select band, min_freq_mhz, max_freq_mhz from bands where band=?");
    q.bindValue(0, QString(band.c_str()));

    if(!q.exec() || !q.next()) {
        qCritical() << "Failed to exec 'getBand' query: " << q.lastError();
        return enums::Band::createInvalid();
    } else {
        vBand = q.value(0).toString().toStdString();
        vMinFreq = q.value(1).toFloat();
        vMaxFreq = q.value(2).toFloat();

        return enums::Band(vBand, vMinFreq, vMaxFreq);
    }
}

QStringList AdifEnums::getModes()
{
    QStringList modeList;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized!";
        return modeList;
    }

    qDebug() << "Querying for ADIF modes";

    QSqlQuery q(instance->db);

    if(!q.exec("select m.mode, sm.submode from modes m "
               "left outer join submodes sm on (sm.parent_mode = m.id) "
               "order by m.mode asc, sm.submode asc")) {
        qCritical() << "ADIF modes query failed: " << q.lastError();
    } else {
        while(q.next()) {
            if(q.value(1).isNull()) {
                // submode is null, so just use mode
                modeList << q.value(0).toString();
            } else {
                // we have a submode, so use it
                modeList << q.value(1).toString();
            }
        }
    }

    return modeList;
}

enums::Mode AdifEnums::getMode(const std::string &mode)
{
    std::string vMode, vSubmode;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return enums::Mode::createInvalid();
    }

    QSqlQuery q(instance->db);
    q.prepare("select m.mode, sm.submode from modes m left outer join submodes sm on (sm.parent_mode = m.id) "
              "where m.mode=? or sm.submode=?");
    q.bindValue(0, QString(mode.c_str()));
    q.bindValue(1, QString(mode.c_str()));

    if(!q.exec() || !q.next()) {
        qCritical() << "Failed to exec 'getMode' query: " << q.lastError();
        return enums::Mode::createInvalid();
    } else {
        vMode = q.value(0).toString().toStdString();
        vSubmode = q.value(1).toString().toStdString();

        return enums::Mode(vMode, vSubmode);
    }
}

QStringList AdifEnums::getCountries()
{
    QStringList countryList;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized!";
        return countryList;
    }

    qDebug() << "Querying for ADIF countries";

    QSqlQuery q(instance->db);

    if(!q.exec("select entity_name from countries where deleted is null or deleted != 'Y' "
               "order by entity_name asc")) {
        qCritical() << "ADIF countries query failed: " << q.lastError();
    } else {
        while(q.next()) {
            countryList << q.value(0).toString();
        }
    }

    return countryList;
}

enums::Country AdifEnums::getCountry(const std::string &entityName)
{
    std::string vEntityName;
    unsigned vCode;
    bool vDeleted;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return enums::Country::createInvalid();
    }

    QSqlQuery q(instance->db);
    q.prepare("select code, entity_name, deleted from countries where entity_name=?");
    q.bindValue(0, QString(entityName.c_str()));

    if(!q.exec() || !q.next()) {
        qCritical() << "Failed to exec 'getCountry' query: " << q.lastError();
        return enums::Country::createInvalid();
    } else {
        vCode = q.value(0).toUInt();
        vEntityName = q.value(1).toString().toStdString();

        if(q.value(2).isNull()) {
            vDeleted = false;
        } else if(q.value(2).toString() == "Y") {
            vDeleted = true;
        } else {
            vDeleted = false;
        }

        return enums::Country(vCode, vEntityName, vDeleted);
    }
}

/*** Enum definitions *****************************************************************************/

namespace enums
{

Enum::Enum()
    : valid(true)
{
    // nop
}

Enum::~Enum()
{
    // nop
}

bool Enum::isValid()
{
    return valid;
}

Band::Band(const std::string &band, float minMhz, float maxMhz)
    : Enum(),
      band(band),
      minMhz(minMhz),
      maxMhz(maxMhz)
{
    // nop
}

Band::~Band()
{
    // nop
}

std::string Band::getValue()
{
    return band;
}

Band Band::createInvalid()
{
    Band b("", 0.0, 0.0);
    b.valid = false;
    return b;
}

Mode::Mode(const std::string &mode, const std::string &submode)
    : Enum(),
      mode(mode),
      submode(submode)
{
    // nop
}

Mode::~Mode()
{
    // nop
}

std::string Mode::getValue()
{
    return mode;
}

std::string Mode::getSubmode()
{
    return submode;
}

Mode Mode::createInvalid()
{
    Mode m("", "");
    m.valid = false;
    return m;
}

Country::Country(unsigned code, const std::string &entityName, bool deleted)
    : Enum(),
      code(code),
      entityName(entityName),
      deleted(deleted)
{
    // nop
}

Country::~Country()
{
    // nop
}

std::string Country::getValue()
{
    return entityName;
}

unsigned Country::getCode()
{
    return code;
}

Country Country::createInvalid()
{
    Country c(0, "", true);
    c.valid = false;
    return c;
}

//bool AdifEnums::buildEnumTable(const std::string &createTable, const std::list<std::string> &inserts)
//{
//    bool result = true;

//    // assume caller has checked our instance

//    // execute the create statement
//    QSqlQuery create(instance->db);
//    if(!create.exec(QString(createTable.c_str()))) {
//        qCritical() << "Failed to execute create table statement: " << createTable.c_str();
//        return false;
//    }

//    // execute each insert statement
//    std::list<std::string>::const_iterator iter;
//    for(iter = inserts.begin(); iter != inserts.end(); iter++) {
//        std::string cur = (*iter);
//        QSqlQuery insert(instance->db);

//        if(!insert.exec(QString(cur.c_str()))) {
//            qCritical() << "Failed to execute insert statement: " << cur.c_str();
//            result = false;
//            break;
//        }
//    }

//    return result;
//}

//bool AdifEnums::setupBands()
//{
//    std::string createTable =
//            "create table bands ("
//            "id INTEGER PRIMARY KEY,"
//            "band TEXT,"
//            "min_freq_mhz REAL,"
//            "max_freq_mhz REAL"
//            ")";

//    std::list<std::string> inserts;

//}

} // namespace enums

} // namespace adif
