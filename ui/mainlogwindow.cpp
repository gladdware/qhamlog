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
#include "qsovalidator.h"
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

    // create the log view window
    logViewer = new LogViewer();
}

MainLogWindow::~MainLogWindow()
{
    clockTimer->stop();

    delete ui;
    delete utcTimeLbl;
    delete clockTimer;
    delete logViewer;
}

void MainLogWindow::on_actionLogContact_triggered()
{
    qDebug() << "'log contact' action triggered";

    // FIXME start testing stuff
//    time_t now = time(NULL);
//    adif::Date d(now);
//    adif::Time t(now);
//    adif::Number n1((float)3.14159f);
//    adif::Number n2((int)599);

//    qDebug() << "Datatype Testing: date: " << d.getStr().c_str()
//             << " time: " << t.getStr().c_str()
//             << " flt num: " << n1.getStr().c_str()
//             << " int num: " << n2.getStr().c_str();

    // qso log testing
//    log::Qso record;
//    record.callsign = ui->qsoCallTxt->text();
//    record.timeOnUtc = ui->qsoDateTimeOn->dateTime();
//    record.timeOffUtc = ui->qsoDateTimeOff->dateTime();
//    record.band = QString(b.getValue().c_str());
//    record.mode = QString(m.getValue().c_str());
//    record.submode = QString(m.getSubmode().c_str());
//    record.freqMhz = QVariant((float)ui->qsoFreqTxt->text().toFloat());
//    record.powerWatts = QVariant((float)ui->qsoPowerTxt->text().toFloat());
//    record.rstSent = QVariant((uint)ui->qsoRstSentTxt->text().toUInt());
//    record.rstRecv = QVariant((uint)ui->qsoRstRecvTxt->text().toUInt());
//    record.city = ui->qsoQthTxt->text();

//    if(c.isValid()) {
//        record.country = QString(c.getValue().c_str());
//    }

//    if(pas.isValid()) {
//        record.primaryAdminSub = QString(pas.getValue().c_str());
//    }

    // build the qso record from the ui state
    log::Qso record = buildQsoRecord();

    // validate the record
    if(!log::QsoValidator::validateQso(record)) {
        // TODO eventually show a pop-up warning or something
        qCritical() << "QSO record invalid";
    } else {
        // try to insert the record
        if(!log::QsoLog::addQso(record)) {
            qCritical() << "Failed to log QSO record!";
        } else {
            qDebug() << "Successfully logged QSO record!";
        }
    }
}

void MainLogWindow::on_actionStartContact_triggered()
{
    qDebug() << "'start contact' action triggered";

    // clear the form
    ui->qsoCallTxt->clear();
    ui->qsoQthTxt->clear();
    ui->qsoRstSentTxt->clear();
    ui->qsoRstRecvTxt->clear();
    ui->qsoCountryCb->setCurrentIndex(0);
    ui->qsoCommentsTxt->clear();
    ui->qsoMsgTxt->clear();

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

void MainLogWindow::on_actionView_Log_triggered()
{
    // show the log viewer and bring to front
    logViewer->show();
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

log::Qso MainLogWindow::buildQsoRecord() {
    int pk, subpk;
    bool ok;
    float fval;
    uint uval;

    // enum objects
    adif::enums::Band band = adif::enums::Band::createInvalid();
    adif::enums::Mode mode = adif::enums::Mode::createInvalid();
    adif::enums::Country country = adif::enums::Country::createInvalid();
    adif::enums::PrimaryAdminSub pas = adif::enums::PrimaryAdminSub::createInvalid();

    // result qso record
    log::Qso record;

    // get band PK
    if(!utils::getModelSelectedPk(&pk, ui->qsoBandCb->currentIndex(), ui->qsoBandCb->model())) {
        qCritical() << "Build QSO: Can't retrieve band PK for " << ui->qsoBandCb->currentText();
    } else {
        band = adif::AdifEnums::getBand(pk);
    }

    // get mode/submode PKs
    if(!utils::getModelSelectedPk(&pk, ui->qsoModeCb->currentIndex(), ui->qsoModeCb->model())) {
        qCritical() << "Build QSO: Can't retrieve mode PK for " << ui->qsoModeCb->currentText();
    } else {
        if(!utils::getModelSelectedPk(&subpk, ui->qsoModeCb->currentIndex(), ui->qsoModeCb->model(),
                                      adif::enums::Mode::DATA_ROLE_SUBMODE_PK)) {
            qCritical() << "Build QSO: Cant' retrieve submode PK for " << ui->qsoModeCb->currentText();
        } else {
            mode = adif::AdifEnums::getMode(pk, subpk);
        }
    }

    // get country pk
    if(!utils::getModelSelectedPk(&pk, ui->qsoCountryCb->currentIndex(), ui->qsoCountryCb->model())) {
        qWarning() << "Build QSO: Can't retrieve country PK for " << ui->qsoCountryCb->currentText();
    } else if(pk >= 0) {
        country = adif::AdifEnums::getCountry(pk);

        // try to get PAS
        if(!utils::getModelSelectedPk(&subpk, ui->qsoStateCb->currentIndex(), ui->qsoStateCb->model())) {
            qWarning() << "Build QSO: Can't retrieve primary admin sub PK for " << ui->qsoStateCb->currentText();
        } else {
            pas = adif::AdifEnums::getPrimaryAdminSub(subpk, pk);
        }
    }

    // TODO get secondary admin subdivision PK...

    // fill in qso record
    if(ui->qsoCallTxt->text().trimmed() != "") {
        record.callsign = ui->qsoCallTxt->text().trimmed();
    }

    record.timeOnUtc = ui->qsoDateTimeOn->dateTime();
    record.timeOffUtc = ui->qsoDateTimeOff->dateTime();

    if(!band.isValid()) {
        qCritical() << "Build QSO: band enum is invalid";
    } else {
        record.band = QString(band.getValue().c_str());
    }

    if(!mode.isValid()) {
        qCritical() << "Build QSO: mode enum is invalid";
    } else {
        record.mode = QString(mode.getValue().c_str());

        if(mode.getSubmode() != "") {
            record.submode = QString(mode.getSubmode().c_str());
        }
    }

    fval = ui->qsoFreqTxt->text().trimmed().toFloat(&ok);
    if(ok) {
        record.freqMhz = QVariant(fval);
    }

    fval = ui->qsoPowerTxt->text().trimmed().toFloat(&ok);
    if(ok) {
        record.powerWatts = QVariant(fval);
    }

    uval = ui->qsoRstSentTxt->text().trimmed().toUInt(&ok);
    if(ok) {
        record.rstSent = QVariant(uval);
    }

    uval = ui->qsoRstRecvTxt->text().trimmed().toUInt(&ok);
    if(ok) {
        record.rstRecv = QVariant(uval);
    }

    if(ui->qsoQthTxt->text().trimmed() != "") {
        record.city = ui->qsoQthTxt->text().trimmed();
    }

    if(country.isValid()) {
        record.country = QString(country.getValue().c_str());
    }

    if(pas.isValid()) {
        record.primaryAdminSub = QString(pas.getValue().c_str());
    }

    if(ui->qsoCommentsTxt->toPlainText().trimmed() != "") {
        record.comments = ui->qsoCommentsTxt->toPlainText().trimmed();
    }

    if(ui->qsoMsgTxt->toPlainText().trimmed() != "") {
        record.qsoMsg = ui->qsoMsgTxt->toPlainText().trimmed();
    }

    return record;
}
