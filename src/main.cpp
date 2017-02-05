/*
Copyright (C) %{CURRENT_YEAR} by Manuel Vera <manolo.vn@gmail.com>

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

#include "gaia.h"

#include <KAboutData>
#include <KLocalizedString>

#include <QApplication>
#include <QCommandLineParser>
#include <QIcon>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(GAIA)
Q_LOGGING_CATEGORY(GAIA, "gaia")
int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    KLocalizedString::setApplicationDomain("gaia");
    KAboutData aboutData( QStringLiteral("gaia"),
                          i18n("Gaia - Markdown editor"),
                          QStringLiteral("%{VERSION}"),
                          i18n("Markdown editor"),
                          KAboutLicense::GPL,
                          i18n("(c) %{CURRENT_YEAR}, Manuel Vera <manolo.vn@gmail.com>"));

    aboutData.addAuthor(i18n("Manuel Vera"),i18n("Developer"), QStringLiteral("manolo.vn@gmail.com"));
    application.setWindowIcon(QIcon::fromTheme("gaia"));
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    aboutData.setupCommandLine(&parser);
    parser.process(application);
    aboutData.processCommandLine(&parser);
    KAboutData::setApplicationData(aboutData);

    gaia *appwindow = new gaia;
    appwindow->show();
    return application.exec();
}
