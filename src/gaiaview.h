/*
Copyright (C) 2017 by Manuel Vera <manolo.vn@gmail.com>

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

#ifndef GAIAVIEW_H
#define GAIAVIEW_H

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(GAIA)

#include "ui_gaiaViewBase.h"

/**
 * This class serves as the main window for gaia.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author Manuel Vera Manuel Vera
 * @version %{VERSION}
 */
class gaiaView : public QWidget
{
    Q_OBJECT
public:
    explicit gaiaView(QWidget *parent);

    virtual ~gaiaView();

private slots:
    void slotSettingsChanged();

signals:
    void signalChangeStatusbar(const QString& text);

    void signalChangeCaption(const QString& text);

private:
    Ui::gaiaViewBase m_ui;
};

#endif // GAIAVIEW_H
