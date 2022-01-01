/*
   SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "gravatar_export.h"
#include <QWidget>

#include <memory>

namespace Gravatar
{
class GravatarConfigWidgetPrivate;

/** Gravatar configuration widget. */
class GRAVATAR_EXPORT GravatarConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GravatarConfigWidget(QWidget *parent = nullptr);
    ~GravatarConfigWidget() override;

    void save();
    void doLoadFromGlobalSettings();
    void doResetToDefaultsOther();

Q_SIGNALS:
    void configChanged(bool);

private:
    void slotGravatarEnableChanged(bool state);
    void slotConfigureSettings();
    void updateWidgetState(bool state);

    std::unique_ptr<GravatarConfigWidgetPrivate> const d;
};
}

