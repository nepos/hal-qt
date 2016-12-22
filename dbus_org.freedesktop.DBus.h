/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: 
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DBUS_ORG_FREEDESKTOP_DBUS_H
#define DBUS_ORG_FREEDESKTOP_DBUS_H

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
 * Proxy class for interface org.freedesktop.DBus.Introspectable
 */
class OrgFreedesktopDBusIntrospectableInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.DBus.Introspectable"; }

public:
    OrgFreedesktopDBusIntrospectableInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgFreedesktopDBusIntrospectableInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QString> Introspect()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("Introspect"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

/*
 * Proxy class for interface org.freedesktop.DBus.Properties
 */
class OrgFreedesktopDBusPropertiesInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.DBus.Properties"; }

public:
    OrgFreedesktopDBusPropertiesInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgFreedesktopDBusPropertiesInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QDBusVariant> Get(const QString &interface, const QString &propname)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(interface) << QVariant::fromValue(propname);
        return asyncCallWithArgumentList(QStringLiteral("Get"), argumentList);
    }

    inline QDBusPendingReply<QVariantMap> GetAll(const QString &interface)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(interface);
        return asyncCallWithArgumentList(QStringLiteral("GetAll"), argumentList);
    }

    inline QDBusPendingReply<> Set(const QString &interface, const QString &propname, const QDBusVariant &value)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(interface) << QVariant::fromValue(propname) << QVariant::fromValue(value);
        return asyncCallWithArgumentList(QStringLiteral("Set"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace org {
  namespace freedesktop {
    namespace DBus {
      typedef ::OrgFreedesktopDBusIntrospectableInterface Introspectable;
      typedef ::OrgFreedesktopDBusPropertiesInterface Properties;
    }
  }
}
#endif
