/*
 * This file is part of buteo-gcontact-plugin package
 *
 * Copyright (C) 2013 Jolla Ltd. and/or its subsidiary(-ies).
 *
 * Contributors: Sateesh Kavuri <sateesh.kavuri@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#ifndef GAUTH_H
#define GAUTH_H

#include <QObject>

#include <SyncCommonDefs.h>
#include <SyncProfile.h>
#include <SignOn/AuthService>
#include <SignOn/Identity>

#include <Accounts/Account>

class GAuth : public QObject
{
    Q_OBJECT
public:
    explicit GAuth(const quint32 accountId, const QString scope, QObject *parent = 0);

    /**
      *! \brief Performs authentication using oauth2
      */
    void authenticate();

    /**
      *! \brief Returns the token obtained after authenticating
      *! \return the token
      */
    const QString token();

    /**
      *! \brief Initializes GAuth
      */
    bool init();

    /**
      *! \brief Returns the token from file. Only for testing purposes
      *! \return the token
      */
    static const QString tokenFromFile();

signals:
    void success();
    void failed();

private:
    void getToken();

    void processTokenResponse(const QByteArray tokenJSON);

    void deviceAuth();

    void processDeviceCode(const QByteArray deviceCodeJSON);

    QString	iDeviceCode;

    QString iUserCode;

    QString iVerificationURL;

    QString iToken;

    QString storedKeyValue(const char *provider, const char *service, const char *keyName);

public slots:

    void credentialsStored(const quint32);

    void error(const SignOn::Error &);

    void sessionResponse(const SignOn::SessionData &);

private:
    SignOn::Identity    *mIdentity;
    SignOn::AuthSession *mSession;
    Accounts::Account   *mAccount;
    QString mToken;
    QString mScope;
};

#endif // GAUTH_H
