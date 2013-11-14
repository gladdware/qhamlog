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

#include "mainlogwindow.h"
#include "ui_mainlogwindow.h"
#include "adifenums.h"
#include "utils.h"
// FIXME testing
#include "adifdatatypes.h"
#include <ctime>

#include <QDebug>
//#include <QStringList>
//#include <QSqlDatabase>
//#include <QSqlQuery>

const QString MainLogWindow::UTC_DATETIME_FMT = "yyyy-MM-dd hh:mmZ";

MainLogWindow::MainLogWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainLogWindow)
{
    ui->setupUi(this);

    QDateTime curDateTimeUtc = QDateTime::currentDateTime().toTimeSpec(Qt::UTC);
    ui->qsoDateTimeOn->setDateTime(curDateTimeUtc);
    ui->qsoDateTimeOff->setDateTime(curDateTimeUtc);

    ui->statusBar->showMessage("Ready", 0);

    // add bands
    ui->qsoBandCb->setModel(adif::AdifEnums::getBandsModel());

    // add modes
    ui->qsoModeCb->setModel(adif::AdifEnums::getModesModel());

    // add countries
    ui->qsoCountryCb->setModel(adif::AdifEnums::getCountriesModel());

    // disable PAS cb for now
    ui->qsoStateCb->setEnabled(false);

    // disable SAS cb for now
    ui->qsoCountyCb->setEnabled(false);

    // setup status bar UTC date/time label
    utcTimeLbl = new QLabel(curDateTimeUtc.toString(UTC_DATETIME_FMT), this);
    utcTimeLbl->setToolTip("Current date and time (UTC)");
    ui->statusBar->addPermanentWidget(utcTimeLbl, 0);

    // start the timer to update the UTC date/time label
    // TODO is there a better way to do this?
    clockTimer = new QTimer(this);
    connect(clockTimer, SIGNAL(timeout()), this, SLOT(on_clockTimer_timeout()));
    clockTimer->start(10000);
}

MainLogWindow::~MainLogWindow()
{
    clockTimer->stop();

    delete ui;
    delete utcTimeLbl;
    delete clockTimer;
}

void MainLogWindow::on_actionLogContact_triggered()
{
    // FIXME this is all testing code!

    qDebug() << "'log contact' action triggered";

    int pk, subpk;

    if(!utils::getModelSelectedPk(&pk, ui->qsoBandCb->currentIndex(), ui->qsoBandCb->model())) {
        qCritical() << "Can't retrieve band PK";
        return;
    }

    adif::enums::Band b = adif::AdifEnums::getBand(pk);

//    if(b.isValid()) {
//        qDebug() << "Got valid band: " << QString(b.getValue().c_str());
//    } else {
//        qDebug() << "Got INVALID band";
//    }

    if(!utils::getModelSelectedPk(&pk, ui->qsoModeCb->currentIndex(), ui->qsoModeCb->model())) {
        qCritical() << "Can't retrieve mode PK";
        return;
    }

    if(!utils::getModelSelectedPk(&subpk, ui->qsoModeCb->currentIndex(), ui->qsoModeCb->model(),
                                  adif::enums::Mode::DATA_ROLE_SUBMODE_PK)) {
        qCritical() << "Cant' retrieve submode PK";
        return;
    }

    qDebug() << "@@@ mode PK=" << pk << " submode PK=" << subpk;
    adif::enums::Mode m = adif::AdifEnums::getMode(pk, subpk);

//    if(m.isValid()) {
//        qDebug() << "Got valid mode " << QString(m.getValue().c_str()) << " " << QString(m.getSubmode().c_str());
//    } else {
//        qDebug() << "Got INVALID mode";
//    }

    if(!utils::getModelSelectedPk(&pk, ui->qsoCountryCb->currentIndex(), ui->qsoCountryCb->model())) {
        qCritical() << "Can't retrieve country PK";
        return;
    }

    adif::enums::Country c = adif::enums::Country::createInvalid();
    adif::enums::PrimaryAdminSub pas = adif::enums::PrimaryAdminSub::createInvalid();
    if(pk >= 0) {
        c = adif::AdifEnums::getCountry(pk);

        // try to get PAS
        if(!utils::getModelSelectedPk(&subpk, ui->qsoStateCb->currentIndex(), ui->qsoStateCb->model())) {
            qCritical() << "Can't retrieve state PK";
            return;
        } else {
            pas = adif::AdifEnums::getPrimaryAdminSub(subpk, pk);
        }
    }

//    if(!ui->qsoCountryCb->currentText().isEmpty()) {
//        c = adif::AdifEnums::getCountry(ui->qsoCountryCb->currentText().toStdString());

//        if(c.isValid()) {
//            qDebug() << "Got valid country " << QString(c.getValue().c_str()) << " - " << c.getCode();
//        } else {
//            qDebug() << "Got INVALID country";
//        }
//    }

//    if(!ui->qsoStateCb->currentText().isEmpty()) {
//        adif::enums::PrimaryAdminSub pas = adif::AdifEnums::getPrimaryAdminSub(ui->qsoStateCb->currentText().toStdString(), c);

//        if(pas.isValid()) {
//            qDebug() << "Got valid PAS " << QString(pas.getValue().c_str()) << " - " <<
//                        QString(pas.getName().c_str());
//        } else {
//            qDebug() << "Got INVALID PAS";
//        }
//    }


    // FIXME datatype testing
    time_t now = time(NULL);
    adif::Date d(now);
    adif::Time t(now);
    adif::Number n1((float)3.14159f);
    adif::Number n2((int)599);

    qDebug() << "Datatype Testing: date: " << d.getStr().c_str()
             << " time: " << t.getStr().c_str()
             << " flt num: " << n1.getStr().c_str()
             << " int num: " << n2.getStr().c_str();
}

void MainLogWindow::on_actionStartContact_triggered()
{
    qDebug() << "'start contact' action triggered";

    // TODO clear the form

    // set both times to the current time
    QDateTime curDateTimeUtc = QDateTime::currentDateTime().toTimeSpec(Qt::UTC);
    ui->qsoDateTimeOn->setDateTime(curDateTimeUtc);
    ui->qsoDateTimeOff->setDateTime(curDateTimeUtc);
}

void MainLogWindow::on_actionEndContact_triggered()
{
    qDebug() << "'end contact' action triggered";

    // set the end time to the current time
    QDateTime curDateTimeUtc = QDateTime::currentDateTime().toTimeSpec(Qt::UTC);
    ui->qsoDateTimeOff->setDateTime(curDateTimeUtc);
}

void MainLogWindow::on_clockTimer_timeout()
{
//    qDebug() << "got clock timeout";

    QDateTime curDateTimeUtc = QDateTime::currentDateTime().toTimeSpec(Qt::UTC);
    utcTimeLbl->setText(curDateTimeUtc.toString(UTC_DATETIME_FMT));
}

void MainLogWindow::on_qsoCountryCb_currentIndexChanged(int index)
{
    qDebug() << "QSO country CB index changed to " << index;

    // clear current items
    ui->qsoStateCb->clear();

    if(index < 0) {
        ui->qsoStateCb->setEnabled(false);
        return;
    }

    int countryCode;

    if(!utils::getModelSelectedPk(&countryCode, index, ui->qsoCountryCb->model())) {
        // the result we got is not an integer
        qCritical() << "Failed to retrieve country code from Country model";
        ui->qsoStateCb->setEnabled(false);
    } else if(countryCode >= 0) {
        // should be a good country code
        qDebug() << "Got country code from model: " << countryCode;
        ui->qsoStateCb->setEnabled(true);
        ui->qsoStateCb->setModel(adif::AdifEnums::getPrimaryAdminSubModel(countryCode));
    } else {
        // probably the "blank" country with code -1
        qDebug() << "Got unusable country code from model: " << countryCode;
        ui->qsoStateCb->setEnabled(false);
    }
}
