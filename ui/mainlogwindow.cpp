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
#include "adifrecord.h"
#include "qsovalidator.h"
#include "utils.h"
#include "adiflogwriter.h"
#include "version.h"
#include "aboutdialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

const QString MainLogWindow::UTC_DATETIME_FMT = "yyyy-MM-dd hh:mmZ";

MainLogWindow::MainLogWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainLogWindow)
{
    ui->setupUi(this);

    // set title from version params
    QString verTitle;
    verTitle.append(QHAMLOG_APP_NAME);
    verTitle.append(" ");
    verTitle.append(QHAMLOG_APP_VER);
    verTitle.append(" (");
    verTitle.append(QHAMLOG_APP_REV);
    verTitle.append(")");

    setWindowTitle(verTitle);

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
    qDebug() << "Main Log: 'log contact' action triggered";

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

    qDebug() << "Export: got " << QString::number(qsoList.size()) << " records from log";

    QString adifFileName = QFileDialog::getSaveFileName(this, "Export ADIF File", "/Users/agladd/",
                                                        "ADIF Files (*.adi)");

    // only write out if we got a non-empty filename
    if(!adifFileName.isEmpty()) {
        adif::AdifLogWriter writer(adifFileName);

        if(!writer.write(qsoList)) {
            qCritical() << "Export: failure writing full log";
        } else {
            qDebug() << "Export: successfully wrote ADIF log export to " << adifFileName;
        }
    }
}

void MainLogWindow::on_actionAbout_triggered()
{
    AboutDialog *d = new AboutDialog(this);

    // we don't care about the return value
    d->exec();

    // dispose the dialog
    delete d;
}

void MainLogWindow::on_clockTimer_timeout()
{
//    qDebug() << "got clock timeout";

    QDateTime curDateTimeUtc = QDateTime::currentDateTimeUtc();
    utcTimeLbl->setText(curDateTimeUtc.toString(UTC_DATETIME_FMT));
}
