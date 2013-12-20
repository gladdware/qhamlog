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

#include "logwriter.h"

#include <QDebug>

namespace log
{

LogWriter::LogWriter(const QString &filename)
    : ready(false),
      outFile(NULL),
      outStream(NULL)
{
    // try to open the file
    outFile = new QFile(filename);

    if(outFile->open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        // initialize the output stream
        outStream = new QTextStream(outFile);

        ready = true;
    }
}

LogWriter::~LogWriter()
{
    ready = false;

    if(outStream != NULL) {
        outStream->flush();

        delete outStream;
        outStream = NULL;
    }

    if(outFile != NULL) {
        delete outFile;
        outFile = NULL;
    }
}

bool LogWriter::write(const QsoLog::QsoList &qsoList)
{
    QsoLog::QsoListIterator iter = qsoList.begin();
    bool result = true;

    while(iter != qsoList.end()) {
        if(!write((*iter))) {
            result = false;
            break;
        }

        iter++;
    }

    return result;
}

} // namespace log
