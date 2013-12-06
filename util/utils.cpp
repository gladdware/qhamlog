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

#include "utils.h"

#include <QDebug>
#include <QModelIndex>

namespace utils
{

bool getModelSelectedPk(int *pk, int selectedIndex, const QAbstractItemModel *model, int role)
{
    QModelIndex idx = model->index(selectedIndex, 0);
    return getModelSelectedPk(pk, idx, model, role);
}

bool getModelSelectedPk(int *pk, const QModelIndex &index, const QAbstractItemModel *model, int role)
{
    if(pk == NULL) {
        qWarning() << "get model PK: bad pk pointer";
        return false;
    } else if(model == NULL) {
        qWarning() << "get model PK: bad model pointer";
        return false;
    }

    QVariant var = model->data(index, role);

    bool ok = false;
    int result = var.toInt(&ok);

    if(!ok) {
        qWarning() << "get model PK: can't convert retrieved value to INT: " << var;
        return false;
    } else {
        *pk = result;
        return true;
    }
}

int popup(const QString &msg,
          QMessageBox::Icon icon,
          QMessageBox::StandardButtons buttons,
          QMessageBox::StandardButton defaultButton,
          QWidget *parent,
          const QString &infoMsg)
{
    QMessageBox mb(parent);

    mb.setText(msg);
    mb.setInformativeText(infoMsg);
    mb.setStandardButtons(buttons);
    mb.setDefaultButton(defaultButton);
    mb.setIcon(icon);

#ifdef PLAT_MAC
    // set window modality so the dialog shows up as a Qt::Sheet if we have a parent
    if(parent != NULL) {
        mb.setWindowModality(Qt::WindowModal);
    }
#endif

    return mb.exec();
}

} // namespace utils
