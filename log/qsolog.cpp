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

#include "qsolog.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>

namespace log
{

QsoLog *QsoLog::instance = NULL;

QsoLog::QsoLog()
    : SqliteDbProvider("qso_log")
{
    // nop
}

QsoLog::~QsoLog()
{
    // nop
}

bool QsoLog::init(const std::string &dbPath)
{
    if(instance == NULL) {
        qDebug() << "Creating QSO log instance";
        instance = new QsoLog();
    }

    if(!instance->openDb(QString(dbPath.c_str()))) {
        qCritical() << "Failed to open DB file for qso log";
        return false;
    } else {
        return true;
    }
}

void QsoLog::destroy()
{
    if(instance != NULL) {
        delete instance;
        instance = NULL;
    }
}

QsoLog::Model *QsoLog::getModel()
{
    if(instance == NULL) {
        qCritical() << "QSO log not initialized";
        return NULL;
    }

    return new Model(instance->db);
}

QsoLog::QsoList QsoLog::getQsoList()
{
    QsoList result;

    if(instance == NULL) {
        qCritical() << "QSO Log DB: not initialized";
        return result;
    }

    // build query
    QSqlQuery q(instance->db);

    // exec query
    if(!q.exec("select * from qso_log")) {
        qCritical() << "QSO Log DB: failed to exec 'getQsoList' query: " << q.lastError();
        return result;
    } else {
        // for each result, build and add a record
        while(q.next()) {
            Qso curQso;

            if(!fillQsoRecord(q, curQso)) {
                qWarning() << "QSO Log DB: couldn't fill record for PK " << q.record().value(Model::ID);
            } else {
                // add to list
                result.push_back(curQso);
            }
        }

        return result;
    }
}

Qso QsoLog::getQso(int qsoPk)
{
    if(instance == NULL) {
        qCritical() << "QSO log not initialized";
        return Qso();
    }

    // prepare query
    QSqlQuery q(instance->db);
    q.prepare("select * from qso_log where id=?");

    // bind pk
    q.bindValue(0, qsoPk);

    // exec query
    if(!q.exec() || !q.next()) {
        qCritical() << "Failed to exec 'getQso' query: " << q.lastError();
        return Qso();
    } else {
        Qso result;

        if(!fillQsoRecord(q, result)) {
            return Qso();
        } else {
            return result;
        }
    }
}

bool QsoLog::addQso(const Qso &qso)
{
    if(instance == NULL) {
        qCritical() << "QSO log not initialized";
        return false;
    }

    QVariant timeOnS, timeOffS;

    // get the real time on
    if(!qso.timeOnUtc.isNull()) {
        timeOnS = QVariant((uint)qso.timeOnUtc.toTime_t());
    }

    // get the real time off
    if(!qso.timeOffUtc.isNull()) {
        timeOffS = QVariant((uint)qso.timeOffUtc.toTime_t());
    }

    // prepare the query
    QSqlQuery q(instance->db);
    q.prepare("insert into qso_log (callsign, time_on_utc, time_off_utc, band, mode, submode, "
              "freq_mhz, power_w, rst_sent, rst_recv, city, country, primary_admin_sub, "
              "secondary_admin_sub, comments, qso_msg) "
              "values "
              "(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    // bind values
    q.bindValue(0, qso.callsign);
    q.bindValue(1, timeOnS);
    q.bindValue(2, timeOffS);
    q.bindValue(3, qso.band);
    q.bindValue(4, qso.mode);
    q.bindValue(5, qso.submode);
    q.bindValue(6, qso.freqMhz);
    q.bindValue(7, qso.powerWatts);
    q.bindValue(8, qso.rstSent);
    q.bindValue(9, qso.rstRecv);
    q.bindValue(10, qso.city);
    q.bindValue(11, qso.country);
    q.bindValue(12, qso.primaryAdminSub);
    q.bindValue(13, qso.secondaryAdminSub);
    q.bindValue(14, qso.comments);
    q.bindValue(15, qso.qsoMsg);

    // execute the insert
    if(!q.exec()) {
        qCritical() << "Failed to insert new QSO record: " << q.lastError();
        return false;
    } else {
        qDebug() << "Inserted new QSO record";
        return true;
    }
}

bool QsoLog::updateQso(const Qso &qso)
{
    if(instance == NULL) {
        qCritical() << "QSO log not initialized";
        return false;
    } else if(qso.id.isNull()) {
        qCritical() << "Can't update QSO with NULL ID";
        return false;
    }

    QVariant timeOnS, timeOffS;

    // get the real time on
    if(!qso.timeOnUtc.isNull()) {
        timeOnS = QVariant((uint)qso.timeOnUtc.toTime_t());
    }

    // get the real time off
    if(!qso.timeOffUtc.isNull()) {
        timeOffS = QVariant((uint)qso.timeOffUtc.toTime_t());
    }

    // prepare the query
    QSqlQuery q(instance->db);
    q.prepare("update qso_log set callsign=?, time_on_utc=?, time_off_utc=?, band=?, mode=?, "
              "submode=?, freq_mhz=?, power_w=?, rst_sent=?, rst_recv=?, city=?, country=?, "
              "primary_admin_sub=?, secondary_admin_sub=?, comments=?, qso_msg=? "
              "where id=?");

    // bind values
    q.bindValue(0, qso.callsign);
    q.bindValue(1, timeOnS);
    q.bindValue(2, timeOffS);
    q.bindValue(3, qso.band);
    q.bindValue(4, qso.mode);
    q.bindValue(5, qso.submode);
    q.bindValue(6, qso.freqMhz);
    q.bindValue(7, qso.powerWatts);
    q.bindValue(8, qso.rstSent);
    q.bindValue(9, qso.rstRecv);
    q.bindValue(10, qso.city);
    q.bindValue(11, qso.country);
    q.bindValue(12, qso.primaryAdminSub);
    q.bindValue(13, qso.secondaryAdminSub);
    q.bindValue(14, qso.comments);
    q.bindValue(15, qso.qsoMsg);
    q.bindValue(16, qso.id);

    // execute the update
    if(!q.exec()) {
        qCritical() << "Failed to update QSO record: " << q.lastError();
        return false;
    } else {
        qDebug() << "Updated QSO record " << qso.id;
        return true;
    }
}

bool QsoLog::removeQso(const Qso &qso)
{
    if(instance == NULL) {
        qCritical() << "QSO log not initialized";
        return false;
    } else if(qso.id.isNull()) {
        qCritical() << "Can't update QSO with NULL ID";
        return false;
    }

    // prepare the query
    QSqlQuery q(instance->db);
    q.prepare("delete from qso_log where id=?");

    // bind id
    q.bindValue(0, qso.id);

    // exec delete
    if(!q.exec()) {
        qCritical() << "Failed to delete QSO record: " << q.lastError();
        return false;
    } else {
        qDebug() << "Deleted QSO record " << qso.id;
        return true;
    }
}

bool QsoLog::fillQsoRecord(QSqlQuery &query, Qso &qso)
{
    if(!query.isActive() || !query.isSelect()) {
        qCritical() << "QSO Log DB: can't fill QSO record with invalid query";
        return false;
    }

    const QSqlRecord sqlrec = query.record();

    // required values
    QVariant qval;
    QVariant id;
    QString call;
    QDateTime timeOn;
    QString band;
    QString mode;

    // get required values
    qval = sqlrec.value(Model::ID);
    if(!qval.isValid() || qval.isNull()) {
        qCritical() << "QSO Log DB: can't build record with no ID";
        return false;
    } else {
        id = qval;
    }

    qval = sqlrec.value(Model::CALLSIGN);
    if(!qval.isValid() || qval.isNull()) {
        qCritical() << "QSO Log DB: can't build record with no callsign";
        return false;
    } else {
        call = qval.toString();
    }

    qval = sqlrec.value(Model::TIME_ON_UTC);
    if(!qval.isValid() || qval.isNull()) {
        qCritical() << "QSO Log DB: can't build record with no time on";
        return false;
    } else {
        timeOn = QDateTime::fromTime_t(qval.toUInt()).toUTC();
    }

    qval = sqlrec.value(Model::BAND);
    if(!qval.isValid() || qval.isNull()) {
        qCritical() << "QSO Log DB: can't build record with no band";
        return false;
    } else {
        band = qval.toString();
    }

    qval = sqlrec.value(Model::MODE);
    if(!qval.isValid() || qval.isNull()) {
        qCritical() << "QSO Log DB: can't build record with no mode";
        return false;
    } else {
        mode = qval.toString();
    }

    // set required values now
    qso.id = id;
    qso.callsign = call;
    qso.timeOnUtc = timeOn;
    qso.band = band;
    qso.mode = mode;

    // try to get optional values
    qval = sqlrec.value(Model::TIME_OFF_UTC);
    if(!qval.isNull()) {
        qso.timeOffUtc = QDateTime::fromTime_t(qval.toUInt()).toUTC();
    }

    qval = sqlrec.value(Model::SUBMODE);
    if(!qval.isNull()) {
        qso.submode = qval.toString();
    }

    qval = sqlrec.value(Model::FREQ_MHZ);
    if(!qval.isNull()) {
        qso.freqMhz = QVariant(qval.toDouble());
    }

    qval = sqlrec.value(Model::POWER_W);
    if(!qval.isNull()) {
        qso.powerWatts = QVariant(qval.toDouble());
    }

    qval = sqlrec.value(Model::RST_SENT);
    if(!qval.isNull()) {
        qso.rstSent = QVariant(qval.toInt());
    }

    qval = sqlrec.value(Model::RST_RECV);
    if(!qval.isNull()) {
        qso.rstRecv = QVariant(qval.toInt());
    }

    qval = sqlrec.value(Model::CITY);
    if(!qval.isNull()) {
        qso.city = qval.toString();
    }

    qval = sqlrec.value(Model::COUNTRY);
    if(!qval.isNull()) {
        qso.country = qval.toString();
    }

    qval = sqlrec.value(Model::PRIMARY_SUB);
    if(!qval.isNull()) {
        qso.primaryAdminSub = qval.toString();
    }

    qval = sqlrec.value(Model::SECONDARY_SUB);
    if(!qval.isNull()) {
        qso.secondaryAdminSub = qval.toString();
    }

    qval = sqlrec.value(Model::COMMENTS);
    if(!qval.isNull()) {
        qso.comments = qval.toString();
    }

    qval = sqlrec.value(Model::QSO_MSG);
    if(!qval.isNull()) {
        qso.qsoMsg = qval.toString();
    }

    return true;
}

const int QsoLog::Model::DATA_ROLE_PK = Qt::UserRole + 1;

const QString QsoLog::Model::ID = "id";
const QString QsoLog::Model::CALLSIGN = "callsign";
const QString QsoLog::Model::TIME_ON_UTC = "time_on_utc";
const QString QsoLog::Model::TIME_OFF_UTC = "time_off_utc";
const QString QsoLog::Model::BAND = "band";
const QString QsoLog::Model::MODE = "mode";
const QString QsoLog::Model::SUBMODE = "submode";
const QString QsoLog::Model::FREQ_MHZ = "freq_mhz";
const QString QsoLog::Model::POWER_W = "power_w";
const QString QsoLog::Model::RST_SENT = "rst_sent";
const QString QsoLog::Model::RST_RECV = "rst_recv";
const QString QsoLog::Model::CITY = "city";
const QString QsoLog::Model::COUNTRY = "country";
const QString QsoLog::Model::PRIMARY_SUB = "primary_admin_sub";
const QString QsoLog::Model::SECONDARY_SUB = "secondary_admin_sub";
const QString QsoLog::Model::COMMENTS = "comments";
const QString QsoLog::Model::QSO_MSG = "qso_msg";

const QString QsoLog::Model::DATETIME_DISPLAY_FMT = "yyyy/MM/dd hh:mm";

QsoLog::Model::Model(const QSqlDatabase &db, QObject *parent)
    : QSqlQueryModel(parent),
      modelDb(db)
{
    refresh();

    // set header names
    setHeaderLabel(ID, "ID");
    setHeaderLabel(CALLSIGN, "Callsign");
    setHeaderLabel(TIME_ON_UTC, "Time On (UTC)");
    setHeaderLabel(TIME_OFF_UTC, "Time Off (UTC)");
    setHeaderLabel(BAND, "Band");
    setHeaderLabel(MODE, "Mode");
    setHeaderLabel(SUBMODE, "Submode");
    setHeaderLabel(FREQ_MHZ, "Frequency (MHz)");
    setHeaderLabel(POWER_W, "Power (Watts)");
    setHeaderLabel(RST_SENT, "RST Sent");
    setHeaderLabel(RST_RECV, "RST Received");
    setHeaderLabel(CITY, "QTH (City)");
    setHeaderLabel(COUNTRY, "Country");
    setHeaderLabel(PRIMARY_SUB, "Primary Subdivision");
    setHeaderLabel(SECONDARY_SUB, "Secondary Subdivision");
}

QsoLog::Model::~Model()
{
    clear();
}

QVariant QsoLog::Model::data(const QModelIndex &item, int role) const
{
    QVariant result;

    switch(role) {
    case Qt::DisplayRole: {
        QSqlRecord rec = record(item.row());
        QString colName = rec.fieldName(item.column());
        // deal with special formatting
        if(colName == TIME_ON_UTC || colName == TIME_OFF_UTC) {
            // datetime on (required to be non-null)
            QDateTime dt = QDateTime::fromTime_t(rec.value(colName).toUInt()).toUTC();
            result = dt.toString(DATETIME_DISPLAY_FMT);
        } else if(colName == TIME_OFF_UTC) {
            // datetime off (may be null)
            bool ok;
            uint tOff = rec.value(colName).toUInt(&ok);

            if(!ok) {
                // return null
                result = QVariant();
            } else {
                QDateTime dt = QDateTime::fromTime_t(tOff).toUTC();
                result = dt.toString(DATETIME_DISPLAY_FMT);
            }
        } else if(colName == FREQ_MHZ) {
            // add extra precision to freq
            bool ok;
            double freq = rec.value(colName).toDouble(&ok);

            if(!ok) {
                // return null
                result = QVariant();
            } else {
                result = QString::number(freq, 'f', 6);
            }
        }
        // TODO more?
        else {
            result = QSqlQueryModel::data(item, role);
        }
        break;
    }

    case DATA_ROLE_PK:
        result = record(item.row()).value(ID);
        break;

    default:
        result = QSqlQueryModel::data(item, role);
    }

    return result;
}

void QsoLog::Model::refresh()
{
    // just re-set the query
    setQuery("select id, callsign, time_on_utc, time_off_utc, band, mode, "
             "submode, freq_mhz, power_w, rst_sent, rst_recv, city, "
             "country, primary_admin_sub, secondary_admin_sub "
             "from qso_log order by id asc", modelDb);
}

void QsoLog::Model::setHeaderLabel(const QString &fieldName, const QString &label)
{
    // try to get field index
    int hid = record().indexOf(fieldName);

    // set the label if we can
    if(hid < 0) {
        qWarning() << "qso log model: can't set label for field " << fieldName;
    } else {
        if(!setHeaderData(hid, Qt::Horizontal, label)) {
            qWarning() << "qso log model: set header data failed for field " << fieldName;
        }
    }
}

Qso::Qso()
    : callsign(QString()),
      timeOnUtc(QDateTime()),
      timeOffUtc(QDateTime()),
      band(QString()),
      mode(QString()),
      submode(QString()),
      freqMhz(QVariant()),
      powerWatts(QVariant()),
      rstSent(QVariant()),
      rstRecv(QVariant()),
      city(QString()),
      country(QString()),
      primaryAdminSub(QString()),
      secondaryAdminSub(QString()),
      comments(QString()),
      qsoMsg(QString()),
      id(QVariant())
{
    // nop
}

Qso::Qso(const QString &callsign, const QDateTime &timeOnUtc, const QString &band, const QString &mode)
    : callsign(callsign),
      timeOnUtc(timeOnUtc),
      timeOffUtc(QDateTime::fromTime_t(0)),
      band(band),
      mode(mode),
      submode(QString()),
      freqMhz(QVariant()),
      powerWatts(QVariant()),
      rstSent(QVariant()),
      rstRecv(QVariant()),
      city(QString()),
      country(QString()),
      primaryAdminSub(QString()),
      secondaryAdminSub(QString()),
      comments(QString()),
      qsoMsg(QString()),
      id(QVariant())
{
    // nop
}

Qso::~Qso()
{
    // nop
}

int Qso::getId() const
{
    if(!isValidExistingRecord()) {
        return -1;
    } else {
        return id.toInt();
    }
}

void Qso::setId(int setId)
{
    id = QVariant(setId);
}

bool Qso::isValidExistingRecord() const
{
    return !id.isNull();
}

} // namespace log
