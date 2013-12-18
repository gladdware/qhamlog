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

#ifndef ADIF_H
#define ADIF_H

#include <QString>
#include <string>

namespace adif
{

/*
 * Amateur Data Interchange Format (ADIF)
 * http://adif.org
 *
 * We currently implement the following ADIF versions:
 * v3.0.4
 */
class Adif
{
public:
    // enum for implemented ADIF versions
    enum Version {
        VER_3_0_4
    };

    /**
     * @brief Get a version string for the given version identifier
     * @param ver the version identifier
     * @return the version in a string format
     */
    static QString versionString(enum Version ver);

    // format strings for QT
    static const std::string QT_DATEFORMAT;
    static const std::string QT_TIMEFORMAT;

    virtual ~Adif();

protected:
    Adif();
};

} // namespace adif

#endif // ADIF_H
