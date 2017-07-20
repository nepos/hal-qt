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
#include <QJsonObject>
#include <QWebSocket>
#include <QtCore/QLoggingCategory>
#include "polyphantmessage.h"

Q_DECLARE_LOGGING_CATEGORY(PolyphantConnectionLog)

class PolyphantConnection : public QObject
{
    Q_OBJECT
public:
    explicit PolyphantConnection(const QUrl &uri, QObject *parent = 0);

signals:
    void messageReceived(const PolyphantMessage &message);

public slots:
    void sendMessage(const PolyphantMessage &message);

private:
    QWebSocket socket;
};