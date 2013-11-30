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

#include "qsodataform.h"
#include "ui_qsodataform.h"

#include "adifenums.h"
#include "utils.h"
#include <QDebug>

QsoDataForm::QsoDataForm(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::QsoDataForm)
{
    ui->setupUi(this);

    curPrimaryKey = -1;

    // set current time (UTC) into the date/time fields
    QDateTime curDateTimeUtc = QDateTime::currentDateTimeUtc();
    ui->qsoDateTimeOn->setDateTime(curDateTimeUtc);
    ui->qsoDateTimeOff->setDateTime(curDateTimeUtc);

    // add bands
    ui->qsoBandCb->setModel(adif::AdifEnums::getBandsModel());

    // add modes
    ui->qsoModeCb->setModel(adif::AdifEnums::getModesModel());

    // add countries
    ui->qsoCountryCb->setModel(adif::AdifEnums::getCountriesModel());

    // disable PAS cb for now
    ui->qsoPriAdminCb->setEnabled(false);

    // disable SAS cb for now
    ui->qsoSecAdminCb->setEnabled(false);
}

QsoDataForm::~QsoDataForm()
{
    delete ui;
}

log::Qso QsoDataForm::buildQsoRecord() {
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
        qCritical() << "QSO Form: build QSO - Can't retrieve band PK for " << ui->qsoBandCb->currentText();
    } else {
        band = adif::AdifEnums::getBand(pk);
    }

    // get mode/submode PKs
    if(!utils::getModelSelectedPk(&pk, ui->qsoModeCb->currentIndex(), ui->qsoModeCb->model())) {
        qCritical() << "QSO Form: build QSO - Can't retrieve mode PK for " << ui->qsoModeCb->currentText();
    } else {
        if(!utils::getModelSelectedPk(&subpk, ui->qsoModeCb->currentIndex(), ui->qsoModeCb->model(),
                                      adif::enums::Mode::DATA_ROLE_SUBMODE_PK)) {
            qCritical() << "QSO Form: build QSO - Cant' retrieve submode PK for " << ui->qsoModeCb->currentText();
        } else {
            mode = adif::AdifEnums::getMode(pk, subpk);
        }
    }

    // get country pk
    if(!utils::getModelSelectedPk(&pk, ui->qsoCountryCb->currentIndex(), ui->qsoCountryCb->model())) {
        qWarning() << "QSO Form: build QSO - Can't retrieve country PK for " << ui->qsoCountryCb->currentText();
    } else if(pk >= 0) {
        country = adif::AdifEnums::getCountry(pk);

        // try to get PAS
        if(!utils::getModelSelectedPk(&subpk, ui->qsoPriAdminCb->currentIndex(), ui->qsoPriAdminCb->model())) {
            qWarning() << "QSO Form: build QSO - Can't retrieve primary admin sub PK for " << ui->qsoPriAdminCb->currentText();
        } else {
            pas = adif::AdifEnums::getPrimaryAdminSub(subpk, pk);
        }
    }

    // TODO get secondary admin subdivision PK...

    // fill in qso record
    if(ui->qsoCallsignTxt->text().trimmed() != "") {
        record.callsign = ui->qsoCallsignTxt->text().trimmed().toUpper();
    }

    record.timeOnUtc = ui->qsoDateTimeOn->dateTime();
    record.timeOffUtc = ui->qsoDateTimeOff->dateTime();

    if(!band.isValid()) {
        qCritical() << "QSO Form: build QSO - band enum is invalid";
    } else {
        record.band = QString(band.getValue().c_str());
    }

    if(!mode.isValid()) {
        qCritical() << "QSO Form: build QSO - mode enum is invalid";
    } else {
        record.mode = QString(mode.getValue().c_str());

        if(mode.getSubmode() != "") {
            record.submode = QString(mode.getSubmode().c_str());
        }
    }

    fval = ui->qsoFreqMhzTxt->text().trimmed().toFloat(&ok);
    if(ok) {
        record.freqMhz = QVariant(fval);
    }

    fval = ui->qsoPowerWattsTxt->text().trimmed().toFloat(&ok);
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

    if(ui->qsoMessageTxt->toPlainText().trimmed() != "") {
        record.qsoMsg = ui->qsoMessageTxt->toPlainText().trimmed();
    }

    return record;
}

void QsoDataForm::startQso(const QDateTime &time)
{
    qDebug() << "QSO Form: starting new QSO at time " << time;

    // clear the form
    ui->qsoCallsignTxt->clear();
    ui->qsoQthTxt->clear();
    ui->qsoRstSentTxt->clear();
    ui->qsoRstRecvTxt->clear();
    ui->qsoCountryCb->setCurrentIndex(0);
    ui->qsoCommentsTxt->clear();
    ui->qsoMessageTxt->clear();

    // set both times to the given time
    ui->qsoDateTimeOn->setDateTime(time);
    ui->qsoDateTimeOff->setDateTime(time);
}

void QsoDataForm::endQso(const QDateTime &time)
{
    qDebug() << "QSO Form: ending QSO at time " << time;

    // set time off to the given time
    ui->qsoDateTimeOff->setDateTime(time);
}

void QsoDataForm::fillForm(const log::Qso &qso)
{
    int cbIndex;

    // save the id value
    curPrimaryKey = qso.getId();

    // populate required values
    ui->qsoCallsignTxt->setText(qso.callsign);
    ui->qsoDateTimeOn->setDateTime(qso.timeOnUtc);

    cbIndex = ui->qsoBandCb->findData(qso.band, Qt::DisplayRole);
    if(cbIndex == -1) {
        qWarning() << "QSO Form: can't find band: " << qso.band;
    } else {
        ui->qsoBandCb->setCurrentIndex(cbIndex);
    }

    // TODO continue....
}

void QsoDataForm::on_qsoCountryCb_currentIndexChanged(int index)
{
    qDebug() << "QSO Form: country CB index changed to " << index;

    // clear current items
    ui->qsoPriAdminCb->clear();

    if(index < 0) {
        ui->qsoPriAdminCb->setEnabled(false);
        return;
    }

    int countryCode;

    if(!utils::getModelSelectedPk(&countryCode, index, ui->qsoCountryCb->model())) {
        // the result we got is not an integer
        qCritical() << "QSO Form: failed to retrieve country code from Country model";
        ui->qsoPriAdminCb->setEnabled(false);
    } else if(countryCode >= 0) {
        // should be a good country code
        qDebug() << "QSO Form: got country code from model: " << countryCode;
        ui->qsoPriAdminCb->setEnabled(true);
        ui->qsoPriAdminCb->setModel(adif::AdifEnums::getPrimaryAdminSubModel(countryCode));
    } else {
        // probably the "blank" country with code -1
        qDebug() << "QSO Form: got unusable country code from model: " << countryCode;
        ui->qsoPriAdminCb->setEnabled(false);
    }
}
