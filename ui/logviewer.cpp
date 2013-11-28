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

LogViewer::LogViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogViewer)
{
    ui->setupUi(this);

    ui->qsoLogTable->setModel(log::QsoLog::getModel());
    ui->qsoLogTable->verticalHeader()->setVisible(false);
    ui->qsoLogTable->resizeColumnsToContents();

    ui->statusLbl->setText("Loaded QSO log");

    // TODO figure out how to show number of records
//    QString msg("Loaded ");
//    msg.append(QString(ui->qsoLogTable->model()->rowCount()));
//    msg.append(" records");
//
//    ui->statusLbl->setText(msg);
}

LogViewer::~LogViewer()
{
    delete ui;
}
