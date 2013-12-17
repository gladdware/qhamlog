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

#include "logconverter.h"

#include <QString>
#include <QDebug>
//#include <QtCore/qmath.h>

namespace utils
{

LogConverter::LogConverter()
{
    // nop
}

LogConverter::~LogConverter()
{
    // nop
}

bool LogConverter::qsoToAdif(adif::AdifRecord &adifRecord, const log::Qso &qso)
{
    bool ok;

    // don't assume the qso is valid; just fill in what we have

    // callsign
    if(!qso.callsign.isNull() && !qso.callsign.isEmpty()) {
        adif::qso::QsoField *call = new adif::qso::QsoField(adif::qso::CALL, new adif::String(qso.callsign.toStdString()));

        adifRecord.addField(call);
    }

    // date/time on
    if(qso.timeOnUtc.isValid()) {
        adif::qso::QsoField *dOn = new adif::qso::QsoField(adif::qso::QSO_DATE, new adif::Date(qso.timeOnUtc.toTime_t()));
        adif::qso::QsoField *tOn = new adif::qso::QsoField(adif::qso::TIME_ON, new adif::Time(qso.timeOnUtc.toTime_t()));

        adifRecord.addField(dOn);
        adifRecord.addField(tOn);
    }

    // date/time off
    if(qso.timeOffUtc.isValid()) {
        adif::qso::QsoField *dOff = new adif::qso::QsoField(adif::qso::QSO_DATE_OFF, new adif::Date(qso.timeOffUtc.toTime_t()));
        adif::qso::QsoField *tOff = new adif::qso::QsoField(adif::qso::TIME_OFF, new adif::Time(qso.timeOffUtc.toTime_t()));

        adifRecord.addField(dOff);
        adifRecord.addField(tOff);
    }

    // band
    if(!qso.band.isNull() && !qso.band.isEmpty()) {
        adif::qso::QsoField *band = new adif::qso::QsoField(adif::qso::BAND, new adif::Enumeration(qso.band.toStdString()));

        adifRecord.addField(band);
    }

    // mode
    if(!qso.mode.isNull() && !qso.mode.isEmpty()) {
        adif::qso::QsoField *mode = new adif::qso::QsoField(adif::qso::MODE, new adif::Enumeration(qso.mode.toStdString()));

        adifRecord.addField(mode);
    }

    // submode
    if(!qso.submode.isNull() && !qso.submode.isEmpty()) {
        adif::qso::QsoField *sMode = new adif::qso::QsoField(adif::qso::SUBMODE, new adif::String(qso.submode.toStdString()));

        adifRecord.addField(sMode);
    }

    // freq
    if(qso.freqMhz.isValid()) {
        double val = qso.freqMhz.toDouble(&ok);
        if(ok) {
            adif::qso::QsoField *freq = new adif::qso::QsoField(adif::qso::FREQ, new adif::Number(val));

            adifRecord.addField(freq);
        }
    }

    // power
    if(qso.powerWatts.isValid()) {
        double val = qso.powerWatts.toDouble(&ok);
        if(ok) {
//            int iVal = qFloor(val);
//            if((double)iVal == val) {
//                // use an integer
//                adif::qso::QsoField powI(adif::qso::TX_PWR, adif::Number(iVal));
//                adifRecord.addField(powI);
//            } else {
                // use a real
                adif::qso::QsoField *powR = new adif::qso::QsoField(adif::qso::TX_PWR, new adif::Number(val));
                adifRecord.addField(powR);
//            }
        }
    }

    // rst sent
    if(qso.rstSent.isValid()) {
        uint val = qso.rstSent.toUInt(&ok);
        adif::qso::QsoField *rstS = new adif::qso::QsoField(adif::qso::RST_SENT, new adif::String(QString::number(val).toStdString()));

        adifRecord.addField(rstS);
    }

    // rst recv
    if(qso.rstRecv.isValid()) {
        uint val = qso.rstRecv.toUInt(&ok);
        adif::qso::QsoField *rstR = new adif::qso::QsoField(adif::qso::RST_RCVD, new adif::String(QString::number(val).toStdString()));

        adifRecord.addField(rstR);
    }

    // city
    if(!qso.city.isNull() && !qso.city.isEmpty()) {
        adif::qso::QsoField *city = new adif::qso::QsoField(adif::qso::QTH, new adif::String(qso.city.toStdString()));

        adifRecord.addField(city);
    }

    // country
    if(!qso.country.isNull() && !qso.country.isEmpty()) {
        adif::qso::QsoField *cntry = new adif::qso::QsoField(adif::qso::COUNTRY, new adif::String(qso.country.toStdString()));

        adifRecord.addField(cntry);
    }

    // primary admin sub (state)
    if(!qso.primaryAdminSub.isNull() && !qso.primaryAdminSub.isEmpty()) {
        adif::qso::QsoField *pas = new adif::qso::QsoField(adif::qso::STATE, new adif::Enumeration(qso.primaryAdminSub.toStdString()));

        adifRecord.addField(pas);
    }

    // TODO secondary admin sub

    // comments
    if(!qso.comments.isNull() && !qso.comments.isEmpty()) {
        adif::qso::QsoField *cmmts = new adif::qso::QsoField(adif::qso::COMMENT, new adif::String(qso.comments.toStdString()));

        adifRecord.addField(cmmts);
    }

    // qso msg
    if(!qso.qsoMsg.isNull() && !qso.qsoMsg.isEmpty()) {
        adif::qso::QsoField *qMsg = new adif::qso::QsoField(adif::qso::QSLMSG, new adif::MultilineString(qso.qsoMsg.toStdString()));

        adifRecord.addField(qMsg);
    }


    return true;
}

} // namespace utils
