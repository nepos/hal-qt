/***
  Copyright (c) 2016 Nepos GmbH

  Authors: Daniel Mack <daniel@nepos.io>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  This software is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this software; If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <QObject>
#include <QFile>

class InputDevice : public QObject
{
    Q_OBJECT
public:
    explicit InputDevice(const QString &path, QObject *parent = 0);
    ~InputDevice();

    void emitCurrent();

signals:
    void inputEvent(int type, int code, int value);

private:
    QFile device;
};

#endif // INPUTDEVICE_H