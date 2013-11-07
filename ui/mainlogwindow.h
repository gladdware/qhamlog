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

#ifndef MAINLOGWINDOW_H
#define MAINLOGWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainLogWindow;
}

class MainLogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainLogWindow(QWidget *parent = 0);
    ~MainLogWindow();

private slots:
    void on_actionLogContact_triggered();

    void on_actionStartContact_triggered();

    void on_actionEndContact_triggered();

    void on_clockTimer_timeout();

    void on_qsoCountryCb_currentTextChanged(const QString &arg1);

private:
    Ui::MainLogWindow *ui;
    QLabel *utcTimeLbl;
    QTimer *clockTimer;

    static const QString UTC_DATETIME_FMT;
};

#endif // MAINLOGWINDOW_H
