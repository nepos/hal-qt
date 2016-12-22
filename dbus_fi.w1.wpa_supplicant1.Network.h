/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: 
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DBUS_FI_W1_WPA_SUPPLICANT1_NETWORK_H
#define DBUS_FI_W1_WPA_SUPPLICANT1_NETWORK_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

#include "types.h"

/*
 * Proxy class for interface fi.w1.wpa_supplicant1.Network
 */
class FiW1Wpa_supplicant1NetworkInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "fi.w1.wpa_supplicant1.Network"; }

public:
    FiW1Wpa_supplicant1NetworkInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~FiW1Wpa_supplicant1NetworkInterface();

    Q_PROPERTY(bool Enabled READ enabled WRITE setEnabled)
    inline bool enabled() const
    { return qvariant_cast< bool >(property("Enabled")); }
    inline void setEnabled(bool value)
    { setProperty("Enabled", QVariant::fromValue(value)); }

    Q_PROPERTY(StringByteArrayMap Properties READ properties WRITE setProperties)
    inline StringByteArrayMap properties() const
    { return qvariant_cast< StringByteArrayMap >(property("Properties")); }
    inline void setProperties(StringByteArrayMap value)
    { setProperty("Properties", QVariant::fromValue(value)); }

public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
    void PropertiesChanged(const QVariantMap &properties);
};

#endif
