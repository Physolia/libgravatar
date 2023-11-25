/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "gravatarconfiguresettingsdialog.h"
#include "gravatarconfiguresettingswidget.h"
#include "misc/gravatarcache.h"

#include "gravatarsettings.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
using namespace Gravatar;

GravatarConfigureSettingsDialog::GravatarConfigureSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure Gravatar"));
    auto topLayout = new QVBoxLayout(this);
    topLayout->setObjectName(QLatin1StringView("toplayout"));

    mGravatarConfigureSettings = new GravatarConfigureSettingsWidget(this);
    mGravatarConfigureSettings->setObjectName(QLatin1StringView("gravatarconfiguresettings"));
    topLayout->addWidget(mGravatarConfigureSettings);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults, this);
    buttonBox->setObjectName(QLatin1StringView("buttonbox"));
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &GravatarConfigureSettingsDialog::save);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &GravatarConfigureSettingsDialog::reject);
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &GravatarConfigureSettingsDialog::slotRestoreDefault);
    okButton->setDefault(true);

    topLayout->addWidget(buttonBox);
    load();
}

GravatarConfigureSettingsDialog::~GravatarConfigureSettingsDialog() = default;

void GravatarConfigureSettingsDialog::slotRestoreDefault()
{
    mGravatarConfigureSettings->load();
}

void GravatarConfigureSettingsDialog::save()
{
    mGravatarConfigureSettings->save();
    accept();
}

void GravatarConfigureSettingsDialog::load()
{
    mGravatarConfigureSettings->load();
}

#include "moc_gravatarconfiguresettingsdialog.cpp"
