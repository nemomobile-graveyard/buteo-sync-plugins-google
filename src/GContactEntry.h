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

#ifndef GCONTACT_H
#define GCONTACT_H

#include <QObject>
#include <QContactManager>

QTM_USE_NAMESPACE

class GContactEntry : public QObject
{
    Q_OBJECT
public:

    explicit GContactEntry(bool generateXmlFlag, QObject *parent = 0);

    void setId(QString id);

    void setFullName(QString fullName);
    QString getFullName();

    void setAdditionalName(QString additionalName);
    QString getAdditionalName();

    void setFamilyName(QString familyName);
    QString getFamilyName();

    void setNamePrefix(QString namePrefix);
    QString getNamePrefix();

    void setNameSuffix(QString nameSuffix);
    QString getNameSuffix();

    void setGivenName(QString fullName);
    QString getGivenName();

    void setEmail(QString address, QString label, QString rel, bool primary);
    QString email();

    void setBillingInformation(QString billingInfo);
    QString billingInformation();

    void setBirthday(QString birthday);
    QString birthday();

    void setCalendarLink(QString href, QString label, QString rel, QString primary);
    QString calendarLink();

    void setDirectoryServer(QString dirServer);
    QString directoryServer();

    void setEvent(QString event, QString when);
    QString event();

    void setExternalId(QString externalId, QString rel, QString label=0);
    QString externalId();

    void setGender(QString gender);
    QString gender();

    void setGroupMembershipInfo(QString membershipInfo, QString deleted);
    QString groupMembershipInfo();

    void setHobby(QString hobby);
    QString hobby();

    void setInitials(QString initials);
    QString initials();

    void setJot(QString jot, QString jotType);
    QString jot();

    void setLanguage(QString language);
    QString language();

    void setMaidenName(QString maidenName);
    QString maidenName();

    void setMileage(QString mileage);
    QString mileage();

    void setNickname(QString nickname);
    QString nickname();

    void setOccupation(QString occupation);
    QString occupation();

    void setPriority(QString priority);
    QString priority();

    void setRelation(QString relativeName, QString relation);
    QString relation();

    void setSensitivity(QString sensitivity);
    QString sensitivity();

    void setShortname(QString shortname);
    QString shortname();

    void setSubject(QString subject);
    QString subject();

    void setSystemGroup(QString systemGroup);
    QString systemGroup();

    void setUserDefinedField(QString key, QString value);
    QString userDefinedField();

    void setWebsite(QString website, QString rel, QString primary="false");
    QString website();

    // gd:xxx schema handler methods
    void setComments(QString comments);
    QString comments();

    void setCountry(QString country);
    QString country();

    void setDeleted(QString deleted);
    QString deleted();

    void setEntryLink(QString link);
    QString entryLink();

    void setExtendedProperty(QString extProperty);
    QString extendedProperty();

    void setFeedLink(QString feedLink);
    QString feedLink();

    void setGeoPt(QString geoPt);
    QString geoPt();

    void setIm(QString im);
    QString im();

    void setMoney(QString money);
    QString money();

    void setOrgDepartment(QString orgDept);
    QString orgDepartment();

    void setOrgJobDescription(QString orgJobDesc);
    QString orgJobDescription();

    void setOrgName(QString orgName);
    QString orgName();

    void setOrgSymbol(QString orgSymbol);
    QString orgSymbol();

    void setOrgTitle(QString orgTitle);
    QString orgTitle();

    void setOriginalEvent(QString origEvent);
    QString originalEvent();

    void setRating(QString rating);
    QString rating();

    void setResourceId(QString resId);
    QString resourceId();

    typedef enum
    {
        AIM,
        MSN,
        YAHOO,
        SKYPE,
        QQ,
        GOOGLE_TALK,
        ICQ,
        JABBER
    } IM_PROTOCOL;

    typedef enum
    {
        assistant,
        callback,
        car,
        company_main,
        isdn,
        main,
        fax,
        home,
        home_fax,
        mobile,
        other,
        other_fax,
        radio,
        telex,
        tty_tdd,
        pager,
        work,
        work_fax,
        work_mobile,
        work_pager
    } PHONENUMBER_TYPES;

private:

    QString mId;

    QString mNote;

    QString mGivenName;
    QString mAdditionalName;
    QString mFamilyName;
    QString mNamePrefix;
    QString mNameSuffix;
    QString mFullName;

    bool mGenerateXmlFlag;

signals:

public slots:

};

#endif // GCONTACT_H