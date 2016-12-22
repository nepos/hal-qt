/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: 
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DBUS_FI_W1_WPA_SUPPLICANT1_BSS_H
#define DBUS_FI_W1_WPA_SUPPLICANT1_BSS_H

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
 * Proxy class for interface fi.w1.wpa_supplicant1.BSS
 */
class FiW1Wpa_supplicant1BSSInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "fi.w1.wpa_supplicant1.BSS"; }

public:
    FiW1Wpa_supplicant1BSSInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~FiW1Wpa_supplicant1BSSInterface();

    Q_PROPERTY(uint Age READ age)
    inline uint age() const
    { return qvariant_cast< uint >(property("Age")); }

    Q_PROPERTY(QByteArray BSSID READ bSSID)
    inline QByteArray bSSID() const
    { return qvariant_cast< QByteArray >(property("BSSID")); }

    Q_PROPERTY(ushort Frequency READ frequency)
    inline ushort frequency() const
    { return qvariant_cast< ushort >(property("Frequency")); }

    Q_PROPERTY(QByteArray IEs READ iEs)
    inline QByteArray iEs() const
    { return qvariant_cast< QByteArray >(property("IEs")); }

    Q_PROPERTY(QString Mode READ mode)
    inline QString mode() const
    { return qvariant_cast< QString >(property("Mode")); }

    Q_PROPERTY(bool Privacy READ privacy)
    inline bool privacy() const
    { return qvariant_cast< bool >(property("Privacy")); }

    Q_PROPERTY(StringByteArrayMap RSN READ rSN)
    inline StringByteArrayMap rSN() const
    { return qvariant_cast< StringByteArrayMap >(property("RSN")); }

    Q_PROPERTY(UnsignedIntList Rates READ rates)
    inline UnsignedIntList rates() const
    { return qvariant_cast< UnsignedIntList >(property("Rates")); }

    Q_PROPERTY(QByteArray SSID READ sSID)
    inline QByteArray sSID() const
    { return qvariant_cast< QByteArray >(property("SSID")); }

    Q_PROPERTY(short Signal READ signal)
    inline short signal() const
    { return qvariant_cast< short >(property("Signal")); }

    Q_PROPERTY(StringByteArrayMap WPA READ wPA)
    inline StringByteArrayMap wPA() const
    { return qvariant_cast< StringByteArrayMap >(property("WPA")); }

    Q_PROPERTY(StringByteArrayMap WPS READ wPS)
    inline StringByteArrayMap wPS() const
    { return qvariant_cast< StringByteArrayMap >(property("WPS")); }

public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
    void PropertiesChanged(const QVariantMap &properties);
};

namespace fi {
  namespace w1 {
    namespace wpa_supplicant1 {
      typedef ::FiW1Wpa_supplicant1BSSInterface BSS;
    }
  }
}
#endif
