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

#ifndef ADIFLOGWRITER_H
#define ADIFLOGWRITER_H

#include "adifdatatypes.h"
#include "logwriter.h"

namespace adif
{

/**
 * @brief The AdifLogWriter class
 *
 * Writes ADIF logs in the ADI file format (http://adif.org/304/ADIF_304.htm#ADI_File_Format)
 */
class AdifLogWriter : public log::LogWriter
{
public:
    /**
     * @brief Constructor
     * @param filename the filename to write ADIF logs to
     */
    AdifLogWriter(const QString &filename);

    /**
     * @brief Destructor
     */
    virtual ~AdifLogWriter();

    /**
     * @see log::LogWriter::write(const Qso&)
     */
    virtual bool write(const log::Qso &qso);

    /**
     * @see log::LogWriter::write(const QsoList&)
     */
    virtual bool write(const log::QsoLog::QsoList &qsoList);

    // header field definitions
    static const QString HDR_ADIF_VER;
    static const QString HDR_TIMESTAMP;
    static const QString HDR_PROGRAM_ID;
    static const QString HDR_PROGRAM_VER;

    // header timestamp format
    static const QString TIMESTAMP_FMT;

protected:
    void writeField(const QString &tag, const QString &value, const char &indicator = BaseDatatype::INVALID_IND);
};

} // namespace adif

#endif // ADIFLOGWRITER_H
