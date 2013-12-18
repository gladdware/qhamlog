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

#ifndef LOGWRITER_H
#define LOGWRITER_H

#include "qsolog.h"
#include <QFile>
#include <QTextStream>

namespace log
{

class LogWriter
{
public:
    /**
     * @brief Destructor
     */
    virtual ~LogWriter();

    /**
     * @brief Write a single QSO to the file; derived classes must implement
     * @param qso the QSO to write
     * @return true if successful
     */
    virtual bool write(const log::Qso &qso) = 0;

    /**
     * @brief Write a list of QSOs to the file
     * @param qsoList the list of QSOs to write
     * @return true if successful
     */
    virtual bool write(const log::QsoLog::QsoList &qsoList);

protected:
    /**
     * @brief Constructor (should never be instantiated)
     *
     * Opens a file ready for writing based on the given filename. The open file is closed when
     * this object is disposed.
     *
     * @param filename the filename to write to
     */
    LogWriter(const QString &filename);

    bool ready;
    QFile *outFile;
    QTextStream *outStream;
};

} // namespace log

#endif // LOGWRITER_H
