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

#include "ParseStream.h"

#include "Atom.h"
#include <LogMacros.h>

ParseStream::ParseStream(QObject *parent) :
    QObject(parent)
{
    initFunctionMap ();
}

ParseStream::ParseStream(QByteArray xmlStream)
{
    mXml = new QXmlStreamReader (xmlStream);
    mAtom = new Atom (false);

    initFunctionMap ();
}

void
ParseStream::initFunctionMap ()
{
    // Initialize the function map
    mAtomFunctionMap.insert ("updated", &ParseStream::handleAtomUpdated);
    mAtomFunctionMap.insert ("category", &ParseStream::handleAtomCategory);
    mAtomFunctionMap.insert ("author", &ParseStream::handleAtomAuthor);
    mAtomFunctionMap.insert ("totalResults", &ParseStream::handleAtomOpenSearch);
    mAtomFunctionMap.insert ("startIndex", &ParseStream::handleAtomOpenSearch);
    mAtomFunctionMap.insert ("itemsPerPage", &ParseStream::handleAtomOpenSearch);
    mAtomFunctionMap.insert ("entry", &ParseStream::handleAtomEntry);

    mContactFunctionMap.insert ("id", &ParseStream::handleEntryId);
    mContactFunctionMap.insert ("gContact:billingInformation", &ParseStream::handleEntryBillingInformation);
    mContactFunctionMap.insert ("gContact:birthday", &ParseStream::handleEntryBirthday);
    mContactFunctionMap.insert ("gContact:calendarLink", &ParseStream::handleEntryCalendarLink);
    mContactFunctionMap.insert ("gContact:directoryServer", &ParseStream::handleEntryDirectoryServer);
    mContactFunctionMap.insert ("gContact:event", &ParseStream::handleEntryEvent);
    mContactFunctionMap.insert ("gContact:externalId", &ParseStream::handleEntryExternalId);
    mContactFunctionMap.insert ("gcontact::gender", &ParseStream::handleEntryGender);
    mContactFunctionMap.insert ("gcontact:groupMembershipInfo", &ParseStream::handleEntryGroupMembershipInfo);
    mContactFunctionMap.insert ("gContact:hobby", &ParseStream::handleEntryHobby);
    mContactFunctionMap.insert ("gContact:initials", &ParseStream::handleEntryInitials);
    mContactFunctionMap.insert ("gContact:jot", &ParseStream::handleEntryJot);
    mContactFunctionMap.insert ("gContact:language", &ParseStream::handleEntryLanguage);
    mContactFunctionMap.insert ("gContact:maidenName", &ParseStream::handleEntryMaidenName);
    mContactFunctionMap.insert ("gContact:mileage", &ParseStream::handleEntryMileage);
    mContactFunctionMap.insert ("gContact:nickname", &ParseStream::handleEntryNickname);
    mContactFunctionMap.insert ("gContact:occupation", &ParseStream::handleEntryOccupation);
    mContactFunctionMap.insert ("gContact:priority", &ParseStream::handleEntryPriority);
    mContactFunctionMap.insert ("gContact:relation", &ParseStream::handleEntryRelation);
    mContactFunctionMap.insert ("gContact:sensitivity", &ParseStream::handleEntrySensitivity);
    mContactFunctionMap.insert ("gContact:shortName", &ParseStream::handleEntryShortname);
    mContactFunctionMap.insert ("gContact:subject", &ParseStream::handleEntrySubject);
    mContactFunctionMap.insert ("gContact:systemGroup", &ParseStream::handleEntrySystemGroup);
    mContactFunctionMap.insert ("gContact:userDefinedField", &ParseStream::handleEntryUserDefinedField);
    mContactFunctionMap.insert ("gContact:website", &ParseStream::handleEntryWebsite);

    mContactFunctionMap.insert ("gd:additionalName", &ParseStream::handleEntryAdditionalName);
    mContactFunctionMap.insert ("gd:comments", &ParseStream::handleEntryComments);
    mContactFunctionMap.insert ("gd:country", &ParseStream::handleEntryCountry);
    mContactFunctionMap.insert ("gd:deleted", &ParseStream::handleEntryDeleted);
    mContactFunctionMap.insert ("gd:email", &ParseStream::handleEntryEmail);
    mContactFunctionMap.insert ("gd:entryLink", &ParseStream::handleEntryEntryLink);
    mContactFunctionMap.insert ("gd:extendedProperty", &ParseStream::handleEntryExtendedProperty);
    mContactFunctionMap.insert ("gd:familyName", &ParseStream::handleEntryFamilyName);
    mContactFunctionMap.insert ("gd:feedLink", &ParseStream::handleEntryFeedLink);
    mContactFunctionMap.insert ("gd:geoPt", &ParseStream::handleEntryGeoPt);
    mContactFunctionMap.insert ("gd:givenName", &ParseStream::handleEntryGivenName);
    mContactFunctionMap.insert ("gd:im", &ParseStream::handleEntryIm);
    mContactFunctionMap.insert ("gd:money", &ParseStream::handleEntryMoney);
    mContactFunctionMap.insert ("gd:name", &ParseStream::handleEntryName);
    mContactFunctionMap.insert ("gd:organization", &ParseStream::handleEntryOrganization);
    mContactFunctionMap.insert ("gd:originalEvent", &ParseStream::handleEntryOriginalEvent);
    mContactFunctionMap.insert ("gd:phoneNumber", &ParseStream::handleEntryPhoneNumber);
    mContactFunctionMap.insert ("gd:rating", &ParseStream::handleEntryRating);
    mContactFunctionMap.insert ("gd:resourceId", &ParseStream::handleEntryResourceId);
    mContactFunctionMap.insert ("gd:structuredPostalAddress", &ParseStream::handleEntryStructuredPostalAddress);

}

Atom*
ParseStream::atom ()
{
    return mAtom;
}

void
ParseStream::parse ()
{
    while (!mXml->atEnd () && !mXml->hasError ())
    {
        if (mXml->readNextStartElement ())
        {
            Handler handler = mAtomFunctionMap.value (mXml->name ().toString ());
            if (handler)
                (*this.*handler) ();

            if (mXml->isEndElement () && mXml->name () == "feed")
            {
                LOG_DEBUG("End of reading feed");
            }
        }
    }
}

void
ParseStream::handleAtomUpdated ()
{
    mXml->readNext ();
    mAtom->setUpdated (mXml->text ().toString ());
}

void
ParseStream::handleAtomCategory ()
{
    QXmlStreamAttributes attributes = mXml->attributes ();
    for (int i=0; i<attributes.size (); i++)
    {
        QXmlStreamAttribute attr = mXml->attributes ().at (i);
        if (attr.name () == "schema")
            mAtom->setCategorySchema (attr.value ().toString ());
        else if (attr.name () == "term")
            mAtom->setCategoryTerm (attr.value ().toString ());
    }
}

void
ParseStream::handleAtomAuthor ()
{
    mXml->readNextStartElement ();
    if (mXml->name () == "name")
    {
        mAtom->setAuthorName (mXml->readElementText ());
    }
    mXml->readNextStartElement ();
    mXml->readNextStartElement ();
    if (mXml->name () == "email")
    {
        mAtom->setAuthorEmail (mXml->readElementText ());
    }

}

void
ParseStream::handleAtomOpenSearch ()
{
    if (mXml->name() == "totalResults")
        mAtom->setTotalResults (mXml->readElementText ().toInt ());
    else if (mXml->name() == "startIndex")
        mAtom->setStartIndex (mXml->readElementText ().toInt ());
    else if (mXml->name () == "itemsPerPage")
        mAtom->setItemsPerPage (mXml->readElementText ().toInt ());
}

void
ParseStream::handleAtomEntry ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->name () == "entry");

    while (!(mXml->tokenType () == QXmlStreamReader::EndElement &&
             mXml->name () == "entry"))
    {
        if (mXml->tokenType () == QXmlStreamReader::StartElement)
        {
            Handler handler = mContactFunctionMap.value (mXml->name ().toString ());
            if (handler)
                (*this.*handler) ();

            mXml->readNextStartElement ();
        }
    }
}

void
ParseStream::handleEntryId ()
{
    QString idUrl = mXml->readElementText ();
    mContactEntry->setId (idUrl.right (idUrl.lastIndexOf ('/')));
}

void
ParseStream::handleEntryBillingInformation ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:billingInformation");

    mContactEntry->setBillingInformation (mXml->readElementText ());
}

void
ParseStream::handleEntryBirthday ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:birthday");

    mContactEntry->setBirthday (mXml->attributes ().value ("when").toString ());
}

void
ParseStream::handleEntryCalendarLink ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:calendarLink");
    QXmlStreamAttributes attrs = mXml->attributes ();
    QString label, rel, href, primary;
    if (attrs.hasAttribute ("label"))
    {
        label = attrs.value ("label").toString ();
    } else if (attrs.hasAttribute ("rel"))
    {
        rel = attrs.value ("rel").toString ();
    }

    if (attrs.hasAttribute ("primary"))
    {
        primary = attrs.value ("primary").toString ();
    }

    href = attrs.value ("href").toString ();

    mContactEntry->setCalendarLink (href, label, rel, primary);
}

void
ParseStream::handleEntryDirectoryServer ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:directoryServer");

    mContactEntry->setDirectoryServer (mXml->readElementText ());
}

void
ParseStream::handleEntryEvent ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:event");

    QXmlStreamAttributes attrs = mXml->attributes ();
    QString eventType;
    if (attrs.hasAttribute ("label"))
        eventType = attrs.value ("label").toString ();
    else if (attrs.hasAttribute ("rel"))
        eventType = attrs.value ("rel").toString ();

    QString when = attrs.value ("when").toString ();

    mContactEntry->setEvent (eventType, when);
}

void
ParseStream::handleEntryExternalId ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:externalId");

    QXmlStreamAttributes attrs = mXml->attributes ();
    QString label, rel, value;
    if (attrs.hasAttribute ("label"))
        label == attrs.value ("label").toString ();

    rel = attrs.value ("rel").toString ();
    value = attrs.value ("value").toString ();
    mContactEntry->setExternalId (value, rel, label);
}

void
ParseStream::handleEntryGender ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:gender");

    mContactEntry->setGender (mXml->attributes ().value ("value").toString ());
}

void
ParseStream::handleEntryGroupMembershipInfo ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:groupMembershipInfo");

    QXmlStreamAttributes attrs = mXml->attributes ();

    QString deleted, groupId = attrs.value ("href").toString ();
    if (attrs.hasAttribute ("deleted"))
        deleted = attrs.value ("deleted").toString ();

    mContactEntry->setGroupMembershipInfo (groupId, deleted);
}

void
ParseStream::handleEntryHobby ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:hobby");

    mContactEntry->setHobby (mXml->readElementText ());
}

void
ParseStream::handleEntryInitials ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:initials");

    mContactEntry->setInitials (mXml->readElementText ());
}

void
ParseStream::handleEntryJot ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:jot");

    mContactEntry->setJot (mXml->readElementText (), mXml->attributes ().value ("rel").toString ());
}

void
ParseStream::handleEntryLanguage ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:language");

    QXmlStreamAttributes attrs = mXml->attributes ();
    if (attrs.hasAttribute ("code"))
       mContactEntry->setLanguage (attrs.value ("code").toString ());
    else if (attrs.hasAttribute ("label"))
       mContactEntry->setLanguage (attrs.value ("label").toString ());
}

void
ParseStream::handleEntryMaidenName ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:maidenName");

    mContactEntry->setMaidenName (mXml->readElementText ());
}

void
ParseStream::handleEntryMileage ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:mileage");

    mContactEntry->setMileage (mXml->readElementText ());
}

void
ParseStream::handleEntryNickname ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:nickname");

    mContactEntry->setNickname (mXml->readElementText ());
}

void
ParseStream::handleEntryOccupation ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:occupation");

    mContactEntry->setOccupation (mXml->readElementText ());
}

void
ParseStream::handleEntryPriority ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:priority");

    mContactEntry->setPriority (mXml->attributes ().value ("rel").toString ());
}

void
ParseStream::handleEntryRelation ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:relation");

    QString relation;
    if (mXml->attributes ().hasAttribute ("rel"))
        relation = mXml->attributes ().value ("rel").toString ();

    mContactEntry->setRelation (mXml->readElementText (), relation);
}

void
ParseStream::handleEntrySensitivity ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:sensitivity");

    mContactEntry->setSensitivity (mXml->attributes ().value ("rel").toString ());
}

void
ParseStream::handleEntryShortname ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:shortName");

    mContactEntry->setShortname (mXml->readElementText ());
}

void
ParseStream::handleEntrySubject ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:subject");

    mContactEntry->setSubject (mXml->readElementText ());
}

void
ParseStream::handleEntrySystemGroup ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:systemGroup");

    mContactEntry->setSystemGroup (mXml->attributes ().value ("id").toString ());
}

void
ParseStream::handleEntryUserDefinedField ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:userDefinedField");

    mContactEntry->setUserDefinedField (mXml->attributes ().value ("key").toString (),
                                        mXml->attributes ().value ("value").toString ());
}

void
ParseStream::handleEntryWebsite ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gContact:website");

    mContactEntry->setWebsite (mXml->attributes ().value ("href").toString (),
                               mXml->attributes ().value ("rel").toString ());
}

void
ParseStream::handleEntryName ()
{
    Q_ASSERT(mXml->isStartElement () && mXml->qualifiedName () == "gd:name");

    while (!(mXml->tokenType () == QXmlStreamReader::EndElement &&
             mXml->qualifiedName () == "gd:name"))
    {
        if (mXml->tokenType () == QXmlStreamReader::StartElement)
        {
            if (mXml->qualifiedName () == "gd:givenName")
                mContactEntry->setGivenName (mXml->readElementText ());
            else if (mXml->qualifiedName () == "gd:additionalName")
                mContactEntry->setAdditionalName (mXml->readElementText ());
            else if (mXml->qualifiedName () == "gd:familyName")
                mContactEntry->setFamilyName (mXml->readElementText ());
            else if (mXml->qualifiedName () == "gd:namePrefix")
                mContactEntry->setNamePrefix (mXml->readElementText ());
            else if (mXml->qualifiedName () == "gd:nameSuffix")
                mContactEntry->setNameSuffix (mXml->readElementText ());
            else if (mXml->qualifiedName () == "gd:fullName")
                mContactEntry->setFullName (mXml->readElementText ());
        }
        mXml->readNextStartElement ();
    }
}