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

#include "logviewer.h"
#include "ui_logviewer.h"

#include "qsolog.h"
#include "utils.h"
#include <QDebug>

LogViewer::LogViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogViewer)
{
    ui->setupUi(this);

    ui->qsoLogTable->setModel(log::QsoLog::getModel());
    ui->qsoLogTable->verticalHeader()->setVisible(false);
    ui->qsoLogTable->resizeColumnsToContents();

    ui->statusLbl->setText("Loaded QSO log");

    // set correct sizing
    setMinimumSize(minimumSizeHint());
    resize(minimumSizeHint());

    // setup the qso form
    ui->qsoForm->setTitle("Edit QSO Record");
    ui->qsoForm->hide();

    // init correct button states
    ui->cancelBtn->hide();
    ui->saveBtn->hide();
    ui->editBtn->setEnabled(false);

    // TODO figure out how to show number of records

    // double-clicks start an edit
    connect(ui->qsoLogTable, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(startEdit(QModelIndex)));
}

LogViewer::~LogViewer()
{
    delete ui;
}

void LogViewer::startEdit(const QModelIndex &logTableIndex)
{
    qDebug() << "Log Viewer: start edit for idx [row=" << logTableIndex.row() << "]";

    // show the form
    ui->cancelBtn->show();
    ui->saveBtn->show();
    ui->qsoForm->show();

    // hide edit button
    ui->editBtn->hide();

    // disable the table
    ui->qsoLogTable->setEnabled(false);

    // focus the cancel button
    ui->cancelBtn->setFocus();

    // scroll so we still see the selected item
    QModelIndex scrollIndex = ui->qsoLogTable->model()->index(logTableIndex.row(), 0);
    ui->qsoLogTable->scrollTo(scrollIndex);

    // get the record PK
    int pk;
    if(!utils::getModelSelectedPk(&pk, logTableIndex, ui->qsoLogTable->model())) {
        qCritical() << "Log Viewer: failed to get PK for QSO record";
    } else {
        // TODO tell the qso form to load the given record
        qDebug() << "Log Viewer: got qso log PK: " << pk;

        log::Qso record = log::QsoLog::getQso(pk);
        if(!record.isValidExistingRecord()) {
            // invalid
            qCritical() << "Log Viewer: failed to retrieve QSO record for PK: " << pk;
        } else {
            ui->qsoForm->fillForm(record);
        }
    }
}

void LogViewer::stopEdit()
{
    // hide the form
    ui->cancelBtn->hide();
    ui->saveBtn->hide();
    ui->qsoForm->hide();

    // enable the table
    ui->qsoLogTable->setEnabled(true);

    // show edit button again
    ui->editBtn->show();
}

void LogViewer::on_editBtn_clicked()
{
    QModelIndex i = ui->qsoLogTable->currentIndex();
    startEdit(i);
}

void LogViewer::on_cancelBtn_clicked()
{
    // just stop the edit
    stopEdit();
}

void LogViewer::on_saveBtn_clicked()
{
    // TODO save the edits

    // stop the edit
    stopEdit();
}

void LogViewer::on_qsoLogTable_clicked(const QModelIndex &index)
{
    ui->editBtn->setEnabled(true);
}
