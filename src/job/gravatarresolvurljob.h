/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef GRAVATARRESOLVURLJOB_H
#define GRAVATARRESOLVURLJOB_H

#include "gravatar_export.h"
#include <QObject>
#include <QUrl>
#include <QPixmap>
#include <QNetworkReply>

class GravatarResolvUrlJobTest;
namespace Gravatar {
class GravatarResolvUrlJobPrivate;
class Hash;

/** Avartar lookup job. */
class GRAVATAR_EXPORT GravatarResolvUrlJob : public QObject
{
    Q_OBJECT
public:
    explicit GravatarResolvUrlJob(QObject *parent = nullptr);
    ~GravatarResolvUrlJob();

    Q_REQUIRED_RESULT bool canStart() const;
    void start();

    Q_REQUIRED_RESULT QString email() const;
    void setEmail(const QString &email);

    Q_REQUIRED_RESULT bool hasGravatar() const;

    void setSize(int size);
    Q_REQUIRED_RESULT int size() const;

    Q_REQUIRED_RESULT QPixmap pixmap() const;

    Q_REQUIRED_RESULT bool useDefaultPixmap() const;
    void setUseDefaultPixmap(bool useDefaultPixmap);

    bool useLibravatar() const;
    void setUseLibravatar(bool useLibravatar);

    bool fallbackGravatar() const;
    void setFallbackGravatar(bool fallbackGravatar);

Q_SIGNALS:
    void finished(Gravatar::GravatarResolvUrlJob *);
    void resolvUrl(const QUrl &url);

private:
    friend class ::GravatarResolvUrlJobTest;

    void slotFinishLoadPixmap(QNetworkReply *reply);
    Q_REQUIRED_RESULT QUrl generateGravatarUrl(bool useLibravatar);
    Q_REQUIRED_RESULT Hash calculatedHash() const;
    void processNextBackend();
    void startNetworkManager(const QUrl &url);
    Q_REQUIRED_RESULT QUrl createUrl(bool useLibravatar);
    Q_REQUIRED_RESULT Hash calculateHash();
    Q_REQUIRED_RESULT bool cacheLookup(const Hash &hash);
    GravatarResolvUrlJobPrivate *const d;
};
}

#endif // GRAVATARRESOLVURLJOB_H
