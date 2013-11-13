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
    if(pk == NULL) {
        qWarning() << "get model PK: bad pk pointer";
        return false;
    } else if(model == NULL) {
        qWarning() << "get model PK: bad model pointer";
        return false;
    }

    QModelIndex idx = model->index(selectedIndex, 0);
    QVariant var = model->data(idx, role);

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

} // namespace utils
