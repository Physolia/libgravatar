/*
   Copyright (C) 2015-2019 Laurent Montel <montel@kde.org>

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

#include "gravatarconfigwidget.h"
#include "misc/gravatarcache.h"
#include "gravatarconfiguresettingsdialog.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QPushButton>
#include <QPointer>
#include <QHBoxLayout>
#include "gravatarsettings.h"
#include "PimCommon/ConfigureImmutableWidgetUtils"

using namespace Gravatar;
using namespace PimCommon::ConfigureImmutableWidgetUtils;

class Q_DECL_HIDDEN Gravatar::GravatarConfigWidgetPrivate
{
public:
    GravatarConfigWidgetPrivate()
    {
    }

    QCheckBox *mEnableGravatarSupport = nullptr;
    QPushButton *mConfigureGravatarSetting = nullptr;
};

GravatarConfigWidget::GravatarConfigWidget(QWidget *parent)
    : QWidget(parent)
    , d(new Gravatar::GravatarConfigWidgetPrivate)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    d->mEnableGravatarSupport = new QCheckBox(i18n("Enable Gravatar Support"));
    d->mEnableGravatarSupport->setObjectName(QStringLiteral("gravatarcheckbox"));
    d->mEnableGravatarSupport->setChecked(false);
    mainLayout->addWidget(d->mEnableGravatarSupport);

    d->mConfigureGravatarSetting = new QPushButton(i18n("Configure..."));
    d->mConfigureGravatarSetting->setObjectName(QStringLiteral("configure"));
    mainLayout->addWidget(d->mConfigureGravatarSetting);
    connect(d->mConfigureGravatarSetting, &QPushButton::clicked, this, &GravatarConfigWidget::slotConfigureSettings);
    mainLayout->addStretch();

    connect(d->mEnableGravatarSupport, &QCheckBox::toggled, this, &GravatarConfigWidget::slotGravatarEnableChanged);
    updateWidgetState(false);
}

GravatarConfigWidget::~GravatarConfigWidget()
{
    delete d;
}

void GravatarConfigWidget::slotConfigureSettings()
{
    QPointer<Gravatar::GravatarConfigureSettingsDialog> dlg = new Gravatar::GravatarConfigureSettingsDialog(this);
    dlg->exec();
    delete dlg;
}

void GravatarConfigWidget::slotGravatarEnableChanged(bool state)
{
    updateWidgetState(state);
    Q_EMIT configChanged(state);
}

void GravatarConfigWidget::updateWidgetState(bool state)
{
    d->mConfigureGravatarSetting->setEnabled(state);
}

void GravatarConfigWidget::save()
{
    saveCheckBox(d->mEnableGravatarSupport, Gravatar::GravatarSettings::self()->gravatarSupportEnabledItem());
    if (!d->mEnableGravatarSupport->isChecked()) {
        Gravatar::GravatarCache::self()->clearAllCache();
    }
}

void GravatarConfigWidget::doLoadFromGlobalSettings()
{
    loadWidget(d->mEnableGravatarSupport, Gravatar::GravatarSettings::self()->gravatarSupportEnabledItem());
    updateWidgetState(d->mEnableGravatarSupport->isChecked());
}

void GravatarConfigWidget::doResetToDefaultsOther()
{
    const bool bUseDefaults = Gravatar::GravatarSettings::self()->useDefaults(true);
    doLoadFromGlobalSettings();
    Gravatar::GravatarSettings::self()->useDefaults(bUseDefaults);
}
