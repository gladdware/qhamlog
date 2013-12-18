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

#include "adiflogwriter.h"

#include "adif.h"
#include "adifrecord.h"
#include "logconverter.h"
#include "qsofields.h"
#include "version.h"
#include <QDateTime>
#include <QDebug>

namespace adif
{

const QString AdifLogWriter::HDR_ADIF_VER = "ADIF_VER";
const QString AdifLogWriter::HDR_TIMESTAMP = "CREATED_TIMESTAMP";
const QString AdifLogWriter::HDR_PROGRAM_ID = "PROGRAMID";
const QString AdifLogWriter::HDR_PROGRAM_VER = "PROGRAMVERSION";
const QString AdifLogWriter::TIMESTAMP_FMT = "yyyyMMdd HHmmss";

AdifLogWriter::AdifLogWriter(const QString &filename)
    : log::LogWriter(filename)
{
    // write ADIF header info to file
    // header must start with something other than a "<"

    QDateTime now = QDateTime::currentDateTimeUtc();

    if(ready) {
        // begin header
        *outStream << "# ADIF logfile written by " << QHAMLOG_APP_NAME << endl;
        *outStream << "# Generated on " << now.toString(Adif::QT_DATEFORMAT.c_str())
                  << " at " << now.toString(Adif::QT_TIMEFORMAT.c_str()) << "Z" << endl << endl;

        // write header fields
        writeField(HDR_ADIF_VER, Adif::versionString(Adif::VER_3_0_4));
        writeField(HDR_TIMESTAMP, now.toString(TIMESTAMP_FMT));
        writeField(HDR_PROGRAM_ID, QHAMLOG_APP_NAME);
        writeField(HDR_PROGRAM_VER, QHAMLOG_APP_VER);

        // write end-of-header
        *outStream << "<EOH>" << endl << endl;
    }
}

AdifLogWriter::~AdifLogWriter()
{
    // nop
}

bool AdifLogWriter::write(const log::Qso &qso)
{
    if(!ready) {
        qWarning() << "Adif LogWriter: can't write qso list; not ready";
        return false;
    }

    AdifRecord r;

    if(!utils::LogConverter::qsoToAdif(r, qso)) {
        qWarning() << "Adif LogWriter: can't build ADIF record from QSO";
        return false;
    }

    AdifRecord::QsoFieldsIter fieldsIter;

    // write each field
    for(fieldsIter = r.getFieldsIterator(); fieldsIter != r.getFieldsEnd(); fieldsIter++) {
        qso::QsoField *curField = (*fieldsIter);

        writeField(QString(curField->getTag().c_str()),
                   QString(curField->getValue()->getStr().c_str()),
                   curField->getValue()->getIndicator());
    }

    // write end-of-record
    *outStream << "<EOR>" << endl << endl;

    return true;
}

bool AdifLogWriter::write(const log::QsoLog::QsoList &qsoList)
{
    return log::LogWriter::write(qsoList);
}

void AdifLogWriter::writeField(const QString &tag, const QString &value, const char &indicator)
{
    uint len = (uint)value.length();

    // write the first part of the field tag
    *outStream << "<" << tag << ":" << len;

    // see if we should write the type indicator
    if(indicator != BaseDatatype::INVALID_IND) {
        *outStream << ":" << indicator;
    }

    // complete the tag
    *outStream << ">";

    // write the value and complete the line
    *outStream << value << endl;
}

}
