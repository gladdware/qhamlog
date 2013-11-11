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

    // FIXME testing stuff (remove later)
//    QStringList bandList = (QStringList()<<"70cm"<<"2m"<<"6m"<<"10m"<<"20m"<<"40m");
//    ui->qsoBandCb->addItems(bandList);

    QDateTime curDateTimeUtc = QDateTime::currentDateTime().toTimeSpec(Qt::UTC);
    ui->qsoDateTimeOn->setDateTime(curDateTimeUtc);
    ui->qsoDateTimeOff->setDateTime(curDateTimeUtc);

    ui->statusBar->showMessage("Ready", 5000);

//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("/Users/agladd/.qhamlog/bands.db");
//    if(!db.open()) {
//        qDebug() << "Failed to open bands DB!";
//    } else {
//        qDebug() << "Successfully opened bands DB";

//        // get bands
//        QStringList bandList;
//        QSqlQuery bandQuery = db.exec("select band from bands");
//        while(bandQuery.next()) {
//            bandList << bandQuery.value(0).toString();
//        }

//        db.close();

//        ui->qsoBandCb->addItems(bandList);
//    }
    // END testing stuff

    // add bands
//    ui->qsoBandCb->addItems(adif::AdifEnums::getBands());
    ui->qsoBandCb->setModel(adif::AdifEnums::getBandsModel());
    ui->qsoBandCb->setModelColumn(1);

    // add modes
//    ui->qsoModeCb->addItems(adif::AdifEnums::getModes());
    ui->qsoModeCb->setModel(adif::AdifEnums::getModesModel());

    // add countries
    ui->qsoCountryCb->setModel(adif::AdifEnums::getCountriesModel());
//    ui->qsoCountryCb->addItem("");
//    ui->qsoCountryCb->addItems(adif::AdifEnums::getCountries());

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

    adif::enums::Band b = adif::AdifEnums::getBand(ui->qsoBandCb->currentText().toStdString());

    if(b.isValid()) {
        qDebug() << "Got valid band: " << QString(b.getValue().c_str());
    } else {
        qDebug() << "Got INVALID band";
    }

    adif::enums::Mode m = adif::AdifEnums::getMode(ui->qsoModeCb->currentText().toStdString());

    if(m.isValid()) {
        qDebug() << "Got valid mode " << QString(m.getValue().c_str()) << " " << QString(m.getSubmode().c_str());
    } else {
        qDebug() << "Got INVALID mode";
    }

    adif::enums::Country c = adif::enums::Country::createInvalid();
    if(!ui->qsoCountryCb->currentText().isEmpty()) {
        c = adif::AdifEnums::getCountry(ui->qsoCountryCb->currentText().toStdString());

        if(c.isValid()) {
            qDebug() << "Got valid country " << QString(c.getValue().c_str()) << " - " << c.getCode();
        } else {
            qDebug() << "Got INVALID country";
        }
    }

    if(!ui->qsoStateCb->currentText().isEmpty()) {
        adif::enums::PrimaryAdminSub pas = adif::AdifEnums::getPrimaryAdminSub(ui->qsoStateCb->currentText().toStdString(), c);

        if(pas.isValid()) {
            qDebug() << "Got valid PAS " << QString(pas.getValue().c_str()) << " - " <<
                        QString(pas.getName().c_str());
        } else {
            qDebug() << "Got INVALID PAS";
        }
    }
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

    QModelIndex i = ui->qsoCountryCb->model()->index(index, 0);
    QVariant ccVar = ui->qsoCountryCb->model()->data(i, adif::enums::Enum::DATA_ROLE_PK);

    bool ok = false;
    int countryCode = ccVar.toInt(&ok);

    if(!ok) {
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
