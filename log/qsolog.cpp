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

bool QsoLog::addQso(const Qso &qso)
{
    if(instance == NULL) {
        qCritical() << "QSO log not initialized";
        return false;
    }



    QSqlQuery q(instance->db);
    q.prepare("insert into qso_log (callsign, time_on_utc, time_off_utc, band, mode, submode, "
              "freq_mhz, power_w, rst_sent, rst_recv, city, country, primary_admin_sub, "
              "secondary_admin_sub, comments, qso_msg) "
              "values "
              "(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
}

bool QsoLog::updateQso(const Qso &qso)
{
    return false;
}

bool QsoLog::removeQso(const Qso &qso)
{
    return false;
}

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

QsoLog::Model::Model(const QSqlDatabase &db, QObject *parent)
    : QSqlQueryModel(parent)
{
    setQuery("select id, callsign, time_on_utc, time_off_utc, band, mode, "
             "submode, freq_mhz, power_w, rst_sent, rst_recv, city, "
             "country, primary_admin_sub, secondary_admin_sub "
             "from qso_log order by id asc", db);

    // set header names
    setHeaderLabel(ID, "ID");
    setHeaderLabel(CALLSIGN, "Callsign");
    setHeaderLabel(TIME_ON_UTC, "Time On (UTC)");
    setHeaderLabel(TIME_OFF_UTC, "Time Off (UTC)");
    setHeaderLabel(BAND, "Band");
    setHeaderLabel(MODE, "Mode");
    setHeaderLabel(SUBMODE, "Submode");
    setHeaderLabel(FREQ_MHZ, "Frequency (MHz)");
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

} // namespace log
