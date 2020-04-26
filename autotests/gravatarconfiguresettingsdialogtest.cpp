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

#include "gravatarconfiguresettingsdialogtest.h"
#include "../src/widgets/gravatarconfiguresettingsdialog.h"
#include "../src/widgets/gravatarconfiguresettingswidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>

GravatarConfigureSettingsDialogTest::GravatarConfigureSettingsDialogTest(QObject *parent)
    : QObject(parent)
{
}

GravatarConfigureSettingsDialogTest::~GravatarConfigureSettingsDialogTest()
{
}

void GravatarConfigureSettingsDialogTest::shouldHaveDefaultValue()
{
    Gravatar::GravatarConfigureSettingsDialog dlg;
    Gravatar::GravatarConfigureSettingsWidget *configurewidget = dlg.findChild<Gravatar::GravatarConfigureSettingsWidget *>(QStringLiteral("gravatarconfiguresettings"));
    QVERIFY(configurewidget);

    QVBoxLayout *topLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("toplayout"));
    QVERIFY(topLayout);

    QLabel *lab = dlg.findChild<QLabel *>(QStringLiteral("gravatarcachesizelabel"));
    QVERIFY(lab);

    KPluralHandlingSpinBox *gravatarCacheSize = dlg.findChild<KPluralHandlingSpinBox *>(QStringLiteral("gravatarcachesize"));
    QVERIFY(gravatarCacheSize);

    QCheckBox *useLibravatar = dlg.findChild<QCheckBox *>(QStringLiteral("uselibravatarcheckbox"));
    QVERIFY(useLibravatar);
    QVERIFY(useLibravatar->isEnabled());

    QCheckBox *fallbackGravatar = dlg.findChild<QCheckBox *>(QStringLiteral("fallbackgravatar"));
    QVERIFY(fallbackGravatar);
    QVERIFY(!fallbackGravatar->isEnabled());

    KSeparator *separator = dlg.findChild<KSeparator *>(QStringLiteral("separator"));
    QVERIFY(separator);

    KSeparator *separator2 = dlg.findChild<KSeparator *>(QStringLiteral("separator2"));
    QVERIFY(separator2);
}

QTEST_MAIN(GravatarConfigureSettingsDialogTest)
