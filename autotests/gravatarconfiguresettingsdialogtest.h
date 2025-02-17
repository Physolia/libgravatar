/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GravatarConfigureSettingsDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit GravatarConfigureSettingsDialogTest(QObject *parent = nullptr);
    ~GravatarConfigureSettingsDialogTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
};
