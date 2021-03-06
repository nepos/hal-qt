/***
  Copyright (c) 2017 Nepos GmbH

  Authors: Pascal Huerst <pascal.huerst@gmail.com>

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

#include <QDebug>
#include <QNearFieldManager>
#include <QNdefMessage>
#include <QNdefNfcTextRecord>
#include <QNdefNfcUriRecord>
#include <QNdefFilter>
#include <QUrl>
#include <QJsonArray>
#include <QJsonObject>

#include "nfc.h"

Q_LOGGING_CATEGORY(NfcLog, "Nfc")

Nfc::Nfc(QObject *parent) :
    QObject(parent),
    manager(new QNearFieldManager(this)),
    pollingEnabled(false)
{
    if (!manager->isAvailable()) {
        qWarning(NfcLog) << "NFC not available";
        return;
    }

    QNdefFilter filter;

    filter.setOrderMatch(false);
    filter.appendRecord<QNdefNfcTextRecord>(1, UINT_MAX);
    int result = manager->registerNdefMessageHandler(filter, this,
                                                     SLOT(handleMessage(QNdefMessage, QNearFieldTarget*)));
    if (result < 0)
        qWarning(NfcLog) << "Platform does not support NDEF message handler registration";

    connect(manager, SIGNAL(targetDetected(QNearFieldTarget*)),
            this, SLOT(targetDetected(QNearFieldTarget*)));
    connect(manager, SIGNAL(targetLost(QNearFieldTarget*)),
            this, SLOT(targetLost(QNearFieldTarget*)));
}

void Nfc::targetDetected(QNearFieldTarget *target)
{
    if (!target)
        return;

    qInfo(NfcLog) << "Found Tag. uid" << target->uid()
                  << "type" << target->type()
                  << "url" << target->url()
                  << "ndef?" << target->hasNdefMessage()
                  << "processing?" << target->isProcessingCommand();

    QObject::connect(target, &QNearFieldTarget::ndefMessageRead, [this](const QNdefMessage &message) {
        QJsonArray records;

        foreach (const QNdefRecord &record, message) {
            if (record.isRecordType<QNdefNfcTextRecord>()) {
                QNdefNfcTextRecord textRecord(record);
                qInfo(NfcLog) << "Found text record!" << textRecord.text();

                records.append(QJsonObject {
                                   { "type", "text" },
                                   { "payload", textRecord.text() },
                               });
            }

            if (record.isRecordType<QNdefNfcUriRecord>()) {
                QNdefNfcUriRecord uriRecord(record);

                qInfo(NfcLog) << "Found URI record!" << uriRecord.uri();

                records.append(QJsonObject {
                                   { "type", "uri" },
                                   { "payload", uriRecord.uri().toString() },
                               });
            }
        }

        QJsonObject json {
            { "records", records },
        };

        emit tagDetected(json);
    });

    QObject::connect(target, &QNearFieldTarget::error, [this](QNearFieldTarget::Error error, const QNearFieldTarget::RequestId &id) {
        Q_UNUSED(id);
        qInfo(NfcLog) << "Error from target:" << error;
    });

    manager->setTargetAccessModes(QNearFieldManager::NdefReadTargetAccess);
    target->readNdefMessages();
}

void Nfc::targetLost(QNearFieldTarget *target)
{
    if (target) {
        qInfo(NfcLog) << "Lost Tag: " << target->uid();

        target->deleteLater();
    }

    if (pollingEnabled)
        manager->startTargetDetection();
}

void Nfc::handleMessage(QNdefMessage message, QNearFieldTarget *target)
{
    qInfo(NfcLog) << "Message Received: " << message.toByteArray();

    if (target)
        qInfo(NfcLog) << "handle Message Tag: " << target->uid();
}

bool Nfc::setPollingEnabled(bool enabled)
{
    if (enabled == pollingEnabled)
        return true;

    if (enabled) {
        if (!manager->startTargetDetection()) {
            qWarning(NfcLog) << "Can not start target Detection";
            return false;
        }
    } else
        manager->stopTargetDetection();

    pollingEnabled = enabled;

    return true;
}
