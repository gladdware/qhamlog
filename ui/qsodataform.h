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

#ifndef QSODATAFORM_H
#define QSODATAFORM_H

#include "qsolog.h"
#include <QDateTime>
#include <QGroupBox>

namespace Ui {
class QsoDataForm;
}

class QsoDataForm : public QGroupBox
{
    Q_OBJECT

public:
    explicit QsoDataForm(QWidget *parent = 0);
    ~QsoDataForm();

    /**
     * @brief Build a QSO record based on the current state of the UI components
     * @return the built QSO record (not validated)
     */
    log::Qso buildQsoRecord();

public slots:
    /**
     * @brief Signal the start of a new QSO
     * @param time the start time of the new QSO in UTC (defaults to current time)
     */
    void startQso(const QDateTime &time = QDateTime::currentDateTimeUtc());

    /**
     * @brief Signal the end of the current QSO
     * @param time the end time of the QSO in UTC (defaults to current time)
     */
    void endQso(const QDateTime &time = QDateTime::currentDateTimeUtc());

    /**
     * @brief Clear all values from the QSO data form
     */
    void clearForm();

    /**
     * @brief Fill the form UI components based on the values in the given QSO record (the given
     *   QSO record is not validated).
     * @param qso the record to populate into the form
     */
    void fillForm(const log::Qso &qso);

private slots:
    void on_qsoCountryCb_currentIndexChanged(int index);

private:
    Ui::QsoDataForm *ui;

    /* primary key container */
    int curPrimaryKey;
};

#endif // QSODATAFORM_H
