/***
  Copyright (c) 2017 Nepos GmbH

  Authors: Daniel Mack <daniel@nepos.io>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
***/

#pragma once

#include <QObject>
#include <QSocketNotifier>
#include <QtCore/QLoggingCategory>

#include <libudev.h>
#include "udevdevice.h"

Q_DECLARE_LOGGING_CATEGORY(UDevMonitorLog)

class UDevMonitor : public QObject
{
    Q_OBJECT
public:
    explicit UDevMonitor(QObject *parent = 0);
    ~UDevMonitor();

    bool addMatchSubsystem(const QString &subsystem);

signals:
    void deviceAdded(const UDevDevice &UDevMonitor);
    void deviceRemoved(const UDevDevice &UDevMonitor);

private:
    struct udev *udev;
    struct udev_monitor *monitor;

    QSocketNotifier *notifier;

    QList<UDevDevice *> devices;
};
