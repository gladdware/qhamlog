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
#include <QSqlRecord>

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
        qCritical() << "Failed to open DB file for enums";
        return false;
    } else {
        return true;
    }
}

void AdifEnums::destroy()
{
    if(instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

QSqlQueryModel *AdifEnums::getBandsModel() {
    QSqlQueryModel *model = NULL;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return NULL;
    }

    qDebug() << "Building ADIF bands model";

    // build the model
    model = new enums::Band::Model(instance->db);

    // prefetch all rows
    while(model->canFetchMore()) {
        model->fetchMore();
    }

    return model;
}

enums::Band AdifEnums::getBand(const std::string &band)
{
    std::string vBand;
    float vMinFreq, vMaxFreq;

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
        const QSqlRecord r = q.record();
        vBand = r.value(enums::Band::Model::BAND).toString().toStdString();
        vMinFreq = r.value(enums::Band::Model::MIN_FREQ_MHZ).toFloat();
        vMaxFreq = r.value(enums::Band::Model::MAX_FREQ_MHZ).toFloat();

        return enums::Band(vBand, vMinFreq, vMaxFreq);
    }
}

enums::Band AdifEnums::getBand(int bandId)
{
    std::string vBand;
    float vMinFreq, vMaxFreq;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return enums::Band::createInvalid();
    }

    QSqlQuery q(instance->db);
    q.prepare("select band, min_freq_mhz, max_freq_mhz from bands where id=?");
    q.bindValue(0, bandId);

    if(!q.exec() || !q.next()) {
        qCritical() << "Failed to exec 'getBand' query: " << q.lastError();
        return enums::Band::createInvalid();
    } else {
        const QSqlRecord r = q.record();
        vBand = r.value(enums::Band::Model::BAND).toString().toStdString();
        vMinFreq = r.value(enums::Band::Model::MIN_FREQ_MHZ).toFloat();
        vMaxFreq = r.value(enums::Band::Model::MAX_FREQ_MHZ).toFloat();

        return enums::Band(vBand, vMinFreq, vMaxFreq);
    }
}

QSqlQueryModel *AdifEnums::getModesModel()
{
    enums::Mode::Model *model = NULL;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return NULL;
    }

    qDebug() << "Building ADIF modes model";

    model = new enums::Mode::Model(instance->db);

    // prefetch all rows
    while(model->canFetchMore()) {
        model->fetchMore();
    }

    return model;
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
        const QSqlRecord r = q.record();
        vMode = r.value(enums::Mode::Model::MODE).toString().toStdString();
        vSubmode = r.value(enums::Mode::Model::SUBMODE).toString().toStdString();

        return enums::Mode(vMode, vSubmode);
    }
}

enums::Mode AdifEnums::getMode(int modeId, int submodeId)
{
    std::string vMode, vSubmode;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return enums::Mode::createInvalid();
    }

    QSqlQuery q(instance->db);
    if(submodeId >= 0) {
        q.prepare("select m.mode 'MODE', sm.submode 'SUBMODE' "
                  "from modes m left outer join submodes sm on (sm.parent_mode = m.id) "
                  "where m.id=? and sm.id=?");
        q.bindValue(0, modeId);
        q.bindValue(1, submodeId);
    } else {
        q.prepare("select m.mode 'MODE', sm.submode 'SUBMODE' "
                  "from modes m left outer join submodes sm on (sm.parent_mode = m.id) "
                  "where m.id=? and sm.id is null");
        q.bindValue(0, modeId);
    }

    if(!q.exec() || !q.next()) {
        qCritical() << "Failed to exec 'getMode' query: " << q.lastError();
        return enums::Mode::createInvalid();
    } else {
        const QSqlRecord r = q.record();
        vMode = r.value(enums::Mode::Model::MODE).toString().toStdString();
        vSubmode = r.value(enums::Mode::Model::SUBMODE).toString().toStdString();

        return enums::Mode(vMode, vSubmode);
    }
}

QSqlQueryModel *AdifEnums::getCountriesModel(bool withDeleted)
{
    enums::Country::Model *model = NULL;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return NULL;
    }

    qDebug() << "Building ADIF countries model";

    model = new enums::Country::Model(instance->db, withDeleted);

    // prefetch all rows
    while(model->canFetchMore()) {
        model->fetchMore();
    }

    return model;
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
        const QSqlRecord r = q.record();
        vCode = r.value(enums::Country::Model::CODE).toUInt();
        vEntityName = r.value(enums::Country::Model::ENTITY_NAME).toString().toStdString();

        if(r.value(enums::Country::Model::DELETED).isNull()) {
            vDeleted = false;
        } else if(r.value(enums::Country::Model::DELETED).toString() == "Y") {
            vDeleted = true;
        } else {
            vDeleted = false;
        }

        return enums::Country(vCode, vEntityName, vDeleted);
    }
}

enums::Country AdifEnums::getCountry(int countryCode)
{
    std::string vEntityName;
    unsigned vCode;
    bool vDeleted;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return enums::Country::createInvalid();
    }

    QSqlQuery q(instance->db);
    q.prepare("select code, entity_name, deleted from countries where code=?");
    q.bindValue(0, countryCode);

    if(!q.exec() || !q.next()) {
        qCritical() << "Failed to exec 'getCountry' query: " << q.lastError();
        return enums::Country::createInvalid();
    } else {
        const QSqlRecord r = q.record();
        vCode = r.value(enums::Country::Model::CODE).toUInt();
        vEntityName = r.value(enums::Country::Model::ENTITY_NAME).toString().toStdString();

        if(r.value(enums::Country::Model::DELETED).isNull()) {
            vDeleted = false;
        } else if(r.value(enums::Country::Model::DELETED).toString() == "Y") {
            vDeleted = true;
        } else {
            vDeleted = false;
        }

        return enums::Country(vCode, vEntityName, vDeleted);
    }
}

QSqlQueryModel *AdifEnums::getPrimaryAdminSubModel(int countryCode)
{
    enums::PrimaryAdminSub::Model *model = NULL;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return NULL;
    }

    qDebug() << "Building ADIF PASs model";

    model = new enums::PrimaryAdminSub::Model(instance->db, countryCode);

    // prefetch all rows
    while(model->canFetchMore()) {
        model->fetchMore();
    }

    return model;
}

enums::PrimaryAdminSub AdifEnums::getPrimaryAdminSub(const std::string &name,
                                                     const enums::Country &country)
{
    std::string vCode;
    std::string vName;
    unsigned vCountryCode;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return enums::PrimaryAdminSub::createInvalid();
    } else if(!country.isValid()) {
        qWarning() << "Can't retrieve PAS with invalid country";
        return enums::PrimaryAdminSub::createInvalid();
    }

    QSqlQuery q(instance->db);
    q.prepare("select code, name, country_code from primary_admin_subdivisions where code=? and country_code=?");
    q.bindValue(0, QString(name.c_str()));
    q.bindValue(1, country.getCode());

    if(!q.exec() || !q.next()) {
        qCritical() << "Failed to exec 'getPrimaryAdminSub' query: " << q.lastError();
        return enums::PrimaryAdminSub::createInvalid();
    } else {
        const QSqlRecord r = q.record();
        vCode = r.value(enums::PrimaryAdminSub::Model::CODE).toString().toStdString();
        vName = r.value(enums::PrimaryAdminSub::Model::NAME).toString().toStdString();
        vCountryCode = r.value(enums::PrimaryAdminSub::Model::COUNTRY_CODE).toUInt();

        return enums::PrimaryAdminSub(vCode, vName, vCountryCode);
    }
}

enums::PrimaryAdminSub AdifEnums::getPrimaryAdminSub(int pasId, int countryCode)
{
    std::string vCode;
    std::string vName;
    unsigned vCountryCode;

    if(instance == NULL) {
        qCritical() << "ADIF enums not initialized";
        return enums::PrimaryAdminSub::createInvalid();
    }

    QSqlQuery q(instance->db);
    q.prepare("select code, name, country_code from primary_admin_subdivisions where id=? and country_code=?");
    q.bindValue(0, pasId);
    q.bindValue(1, countryCode);

    if(!q.exec() || !q.next()) {
        qCritical() << "Failed to exec 'getPrimaryAdminSub' query: " << q.lastError();
        return enums::PrimaryAdminSub::createInvalid();
    } else {
        const QSqlRecord r = q.record();
        vCode = r.value(enums::PrimaryAdminSub::Model::CODE).toString().toStdString();
        vName = r.value(enums::PrimaryAdminSub::Model::NAME).toString().toStdString();
        vCountryCode = r.value(enums::PrimaryAdminSub::Model::COUNTRY_CODE).toUInt();

        return enums::PrimaryAdminSub(vCode, vName, vCountryCode);
    }
}

/*** Enum definitions *****************************************************************************/

namespace enums
{

const int Enum::DATA_ROLE_PK = Qt::UserRole + 1;

Enum::Enum()
    : valid(true)
{
    // nop
}

Enum::~Enum()
{
    // nop
}

bool Enum::isValid() const
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

std::string Band::getValue() const
{
    return band;
}

Band Band::createInvalid()
{
    Band b("", 0.0, 0.0);
    b.valid = false;
    return b;
}

const QString Band::Model::ID = "id";
const QString Band::Model::BAND = "band";
const QString Band::Model::MIN_FREQ_MHZ = "min_freq_mhz";
const QString Band::Model::MAX_FREQ_MHZ = "max_freq_mhz";

Band::Model::Model(const QSqlDatabase &db, QObject *parent)
    : QSqlQueryModel(parent)
{
    setQuery("select * from bands order by min_freq_mhz asc", db);
}

Band::Model::~Model()
{
    clear();
}

QVariant Band::Model::data(const QModelIndex &item, int role) const
{
    QVariant result;

    switch(role) {
    case Qt::DisplayRole:
        result = record(item.row()).value(BAND).toString();
        break;

    case Enum::DATA_ROLE_PK:
        result = record(item.row()).value(ID).toInt();
        break;

    default:
        result = QSqlQueryModel::data(item, role);
    }

    return result;
}

const int Mode::DATA_ROLE_SUBMODE_PK = Enum::DATA_ROLE_PK + 1;

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

std::string Mode::getValue() const
{
    return mode;
}

std::string Mode::getSubmode() const
{
    return submode;
}

Mode Mode::createInvalid()
{
    Mode m("", "");
    m.valid = false;
    return m;
}

const QString Mode::Model::MODE_ID = "MODE_ID";
const QString Mode::Model::MODE = "MODE";
const QString Mode::Model::SUBMODE_ID = "SUBMODE_ID";
const QString Mode::Model::SUBMODE = "SUBMODE";
const QString Mode::Model::DISPLAY = "DISPLAY";

Mode::Model::Model(const QSqlDatabase &db, QObject *parent)
    : QSqlQueryModel(parent)
{
    setQuery("select m.id 'MODE_ID', m.mode 'MODE', sm.id 'SUBMODE_ID', sm.submode 'SUBMODE', "
             "coalesce(sm.submode, m.mode) 'DISPLAY' from modes m left outer join submodes sm on "
             "(sm.parent_mode = m.id) order by DISPLAY", db);
}

Mode::Model::~Model()
{
    clear();
}

QVariant Mode::Model::data(const QModelIndex &item, int role) const
{
    QVariant result;

    switch(role) {
    case Qt::DisplayRole: {
        QSqlRecord r = record(item.row());
        // decide which data to return
        result = r.value(DISPLAY).toString();
        break;
    }

    case Enum::DATA_ROLE_PK:
        result = record(item.row()).value(MODE_ID).toInt();
        break;

    case Mode::DATA_ROLE_SUBMODE_PK:
        if(record(item.row()).value(SUBMODE_ID).isNull()) {
            result = -1;
        } else {
            result = record(item.row()).value(SUBMODE_ID).toInt();
        }
        break;

    default:
        result = QSqlQueryModel::data(item, role);
    }

    return result;
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

std::string Country::getValue() const
{
    return entityName;
}

unsigned Country::getCode() const
{
    return code;
}

Country Country::createInvalid()
{
    Country c(0, "", true);
    c.valid = false;
    return c;
}

const QString Country::Model::CODE = "code";
const QString Country::Model::ENTITY_NAME = "entity_name";
const QString Country::Model::DELETED = "deleted";

Country::Model::Model(const QSqlDatabase &db, bool withDeleted, QObject *parent)
    : QSqlQueryModel(parent)
{
    if(withDeleted) {
        setQuery("select * from countries order by entity_name asc", db);
    } else {
        setQuery("select * from countries where deleted is null or deleted != 'Y' order by entity_name asc", db);
    }
}

Country::Model::~Model()
{
    clear();
}

QVariant Country::Model::data(const QModelIndex &item, int role) const
{
    QVariant result;

    switch(role) {
    case Qt::DisplayRole:
        // always display the entity name
        result = record(item.row()).value(ENTITY_NAME).toString();
        break;

    case Enum::DATA_ROLE_PK:
        result = record(item.row()).value(CODE).toInt();
        break;

    default:
        result = QSqlQueryModel::data(item, role);
    }

    return result;
}

PrimaryAdminSub::PrimaryAdminSub(const std::string &code, const std::string &name, unsigned countryCode)
    : Enum(),
      code(code),
      name(name),
      countryCode(countryCode)
{
    // nop
}

PrimaryAdminSub::~PrimaryAdminSub()
{
    // nop
}

std::string PrimaryAdminSub::getValue() const
{
    return code;
}

std::string PrimaryAdminSub::getName() const
{
    return name;
}

PrimaryAdminSub PrimaryAdminSub::createInvalid()
{
    PrimaryAdminSub pas("", "", 0);
    pas.valid = false;
    return pas;
}

const QString PrimaryAdminSub::Model::ID = "id";
const QString PrimaryAdminSub::Model::CODE = "code";
const QString PrimaryAdminSub::Model::NAME = "name";
const QString PrimaryAdminSub::Model::COUNTRY_CODE = "country_code";

PrimaryAdminSub::Model::Model(const QSqlDatabase &db, int countryCode, QObject *parent)
    : QSqlQueryModel(parent)
{
    QSqlQuery q(db);
    q.prepare("select * from primary_admin_subdivisions where country_code=? order by code asc");
    q.bindValue(0, countryCode);
    q.exec();

    setQuery(q);
}

PrimaryAdminSub::Model::~Model()
{
    qDebug() << "Clearing PAS model (destructor)";
    clear();
}

QVariant PrimaryAdminSub::Model::data(const QModelIndex &item, int role) const
{
    QVariant result;

    switch(role) {
    case Qt::DisplayRole:
        result = record(item.row()).value(CODE).toString();
        break;

    case Enum::DATA_ROLE_PK:
        result = record(item.row()).value(ID).toInt();
        break;

    default:
        result = QSqlQueryModel::data(item, role);
    }

    return result;
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
