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

#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusError>
#include <QtDBus/QDBusObjectPath>
#include <QDBusMetaType>
#include <QDebug>

#include "daemon.h"

Q_LOGGING_CATEGORY(DaemonLog, "Daemon")

Daemon::Daemon(QUrl uri, QObject *parent) :
    QObject(parent),
    mixer(new ALSAMixer("hw:0", this)),
    updater(new Updater(machine, "latest", this)),
    connman(new Connman(this)),
    homeButtonLED(new LinuxLED("apq8016-sbc:green:user4", this)),
    machine(new Machine(this)),
    systemdConnection(new QDBusInterface("org.freedesktop.systemd1",
                                         "/org/freedesktop/systemd1",
                                         "org.freedesktop.systemd1.Manager",
                                         QDBusConnection::systemBus(), this)),
    redux(new ReduxProxy(uri, QStringList(), this)),
    udev(new UDevMonitor(this)),
    nfc(new Nfc(this)),
    gpio(new GPIO(8, this))
{
    // ALSA
    qInfo(DaemonLog) << "Current master volume:" << mixer->getMasterVolume();

    // Updater logic
    QObject::connect(updater, &Updater::updateAvailable, this, [this](const QString &version) {
        qInfo(DaemonLog) << "New update available, version" << version;
        updater->install();
    });

    QObject::connect(updater, &Updater::alreadyUpToDate, this, [this]() {
        qInfo(DaemonLog) << "Already up-to-date!";
    });

    QObject::connect(updater, &Updater::checkFailed, this, [this]() {
        qInfo(DaemonLog) << "Update check failed!";
    });

    QObject::connect(updater, &Updater::updateSucceeded, this, [this]() {
        qInfo(DaemonLog) << "Update succeeded!";
    });

    QObject::connect(updater, &Updater::updateFailed, this, [this]() {
        qInfo(DaemonLog) << "Update failed!";
    });


    // Connman connection
    QObject::connect(connman, &Connman::availableWifisUpdated, this, [this](const QJsonArray &list) {
        QJsonObject action {
            { "type",           "NETWORK:UPDATE_AVAILABLE_WIFIS" },
            { "availableWifis", list },
        };

        redux->dispatchAction(action);
    });

    QObject::connect(connman, &Connman::connectedWifiChanged, this, [this](const QJsonObject &wifi) {
        QJsonObject action {
            { "type", "NETWORK:CONNECTED_WIFI_CHANGED" },
            { "wifi", wifi },
        };

        redux->dispatchAction(action);
    });

    QObject::connect(connman, &Connman::goneOnline, this, [this]() {
        qInfo(DaemonLog) << "We are now online!";
        updater->check();
    });

    connman->start();

    // Redux/websocket connection
    QObject::connect(redux, &ReduxProxy::stateUpdated, this, &Daemon::reduxStateUpdated);


    // D-Bus connection
    QDBusConnection bus = QDBusConnection::systemBus();
    if (bus.isConnected())
        qInfo(DaemonLog) << "Connected to D-Bus as" << bus.baseService();
    else
        qWarning(DaemonLog) << "D-Bus connection failed:" << bus.lastError();


    // udev monitor
    udev->addMatchSubsystem("input");

    QObject::connect(udev, &UDevMonitor::deviceAdded, this, [this](const UDevDevice &d) {
        qInfo(DaemonLog) << "Linux device added:" << d.getDevPath() << "sysname" << d.getSysName();
    });

    QObject::connect(udev, &UDevMonitor::deviceRemoved, this, [this](const UDevDevice &d) {
        qInfo(DaemonLog) << "Linux device removed:" << d.getDevPath() << "sysname" << d.getSysName();
    });

    // gpio
    gpio->setEdge(GPIO::EdgeRising);
    gpio->setDirection(GPIO::DirectionIn);
    QObject::connect(gpio, &GPIO::onDataReady, this, [this](GPIO::Value v) {
        qInfo(DaemonLog) << "Interrupt on GPIO8: " << (v == GPIO::ValueHi ? "1" : "0");
    });

}

void Daemon::reduxStateUpdated(const QJsonObject &state)
{
    //qInfo() << "STATE:" << state;

    if (state.contains("Network")) {
        QJsonObject network = state["Network"].toObject();

        if (network.contains("knownWifis")) {
            QJsonArray knownWifis = network["knownWifis"].toArray();
            connman->updateKnownWifis(knownWifis);
        }
    }

    if (state.contains("hardware")) {
        QJsonObject hardware = state["hardware"].toObject();

        if (hardware.contains("homebutton")) {
            QJsonObject homebutton = hardware["homebutton"].toObject();
            homeButtonLED->setBrightness(homebutton["value"].toDouble());
        }
    }
}

Daemon::~Daemon()
{
}
