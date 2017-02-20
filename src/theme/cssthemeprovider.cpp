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

#include "cssthemeprovider.h"
#include "gaiaSettings.h"

#include <QDir>
#include <QStandardPaths>

CssThemeProvider::CssThemeProvider() {

}

CssThemeProvider::~CssThemeProvider() {

}

CssTheme* CssThemeProvider::getCurrentTheme() {
    qCDebug(GAIA) << "current css theme " << gaiaSettings::css_theme().toInt();
    
    QList<CssTheme*> themes = this->themes();
    return themes.at(gaiaSettings::css_theme().toInt());
}

QList<CssTheme*> CssThemeProvider::themes() {
    QList<CssTheme*> themes;
    
    QStringList dirs = QStandardPaths::locateAll ( QStandardPaths::AppDataLocation, QString ( "cssthemes" ), QStandardPaths::LocateDirectory );
    Q_FOREACH ( const QString &dir, dirs ) {
        const QStringList fileNames = QDir ( dir ).entryList ( QStringList() << QStringLiteral ( "*.css" ) );
        Q_FOREACH ( const QString &file, fileNames ) {
	    CssTheme* theme = new CssTheme;
	    theme->setLocation(dir + '/' + file);
	    theme->setName(file);
	    themes.append(theme);
        }
    }
    
    return themes;
}

