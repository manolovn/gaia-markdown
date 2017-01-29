/*
Copyright (C) %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License or (at your option) version 3 or any later version
accepted by the membership of KDE e.V. (or its successor approved
by the membership of KDE e.V.), which shall act as a proxy 
defined in Section 14 of version 3 of the license.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "gaiaview.h"
#include "gaiaSettings.h"

gaiaView::gaiaView(QWidget *parent) : QWidget(parent)
{
    m_ui.setupUi(this);
    slotSettingsChanged();
}

gaiaView::~gaiaView()
{
}

void gaiaView::slotSwitchColors()
{
    QColor color = gaiaSettings::color_background();
    gaiaSettings::setColor_background(gaiaSettings::color_foreground());
    gaiaSettings::setColor_foreground(color);

    slotSettingsChanged();
}

void gaiaView::slotSettingsChanged()
{
    qCDebug(GAIA) << "gaiaView::slotSettingsChanged()";
    QPalette palette;
    palette.setColor(QPalette::Window, gaiaSettings::color_background());
    palette.setColor(QPalette::WindowText, gaiaSettings::color_foreground());
    //m_ui.templateLabel->setPalette(palette);

    // i18n : internationalization
    //m_ui.templateLabel->setText(i18n("This project is %1 days old", gaiaSettings::val_time()));
    emit signalChangeStatusbar(i18n("Settings changed"));
}

