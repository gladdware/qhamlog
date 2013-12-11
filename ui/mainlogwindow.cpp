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
#include <QMessageBox>
//#include <QStringList>
//#include <QSqlDatabase>
//#include <QSqlQuery>

const QString MainLogWindow::UTC_DATETIME_FMT = "yyyy-MM-dd hh:mmZ";

MainLogWindow::MainLogWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainLogWindow)
{
    ui->setupUi(this);

    ui->qsoForm->setTitle("QSO Data");

    // setup status bar UTC date/time label
    utcTimeLbl = new QLabel(QDateTime::currentDateTimeUtc().toString(UTC_DATETIME_FMT), this);
    utcTimeLbl->setToolTip("Current date and time (UTC)");
    ui->statusBar->addPermanentWidget(utcTimeLbl, 0);

    // set correct sizing
    setMinimumSize(minimumSizeHint());
    resize(minimumSizeHint());

    // start the timer to update the UTC date/time label
    // TODO is there a better way to do this?
    clockTimer = new QTimer(this);
    connect(clockTimer, SIGNAL(timeout()), this, SLOT(on_clockTimer_timeout()));
    clockTimer->start(10000);

    // create the log view window
    logViewer = new LogViewer();

    // connect action signals
    connect(ui->actionStartContact, SIGNAL(triggered()), ui->qsoForm, SLOT(startQso()));
    connect(ui->actionEndContact, SIGNAL(triggered()), ui->qsoForm, SLOT(endQso()));

    // ready for action!
    ui->statusBar->showMessage("Ready", 5000);
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
    log::Qso record = ui->qsoForm->buildQsoRecord();

    // validate the record
    if(!log::QsoValidator::validateQso(record)) {
        // TODO eventually show a pop-up warning or something
        qCritical() << "Main Log: QSO record invalid";

        utils::popup("Can't log contact: QSO record not valid",
                     QMessageBox::Warning,
                     QMessageBox::Ok, QMessageBox::Ok,
                     this,
                     log::QsoValidator::getLastError());
    } else {
        // try to insert the record
        if(!log::QsoLog::addQso(record)) {
            qCritical() << "Main Log: Failed to log QSO record!";

            utils::popup("Can't log contact: database failure",
                         QMessageBox::Critical,
                         QMessageBox::Ok, QMessageBox::Ok,
                         this);
        } else {
            qDebug() << "Main Log: Successfully logged QSO record!";

            // prepare for for new qso
            ui->qsoForm->startQso();

            // refresh the log viewer
            logViewer->refreshLog();
        }
    }
}

void MainLogWindow::on_actionView_Log_triggered()
{
    // show the log viewer and bring to front
    if(!logViewer->isVisible()) {
        logViewer->show();
    }

    logViewer->raise();
    logViewer->activateWindow();
}

void MainLogWindow::on_actionExport_Log_triggered()
{
    qDebug() << "Main Log: export log triggered";

    log::QsoLog::QsoList qsoList = log::QsoLog::getQsoList();

    qDebug () << "Export: got " << QString::number(qsoList.size()) << " records from log";
}

void MainLogWindow::on_clockTimer_timeout()
{
//    qDebug() << "got clock timeout";

    QDateTime curDateTimeUtc = QDateTime::currentDateTimeUtc();
    utcTimeLbl->setText(curDateTimeUtc.toString(UTC_DATETIME_FMT));
}
