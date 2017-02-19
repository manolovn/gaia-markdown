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

#ifndef GAIA_H
#define GAIA_H

#include <QLoggingCategory>
#include <KXmlGuiWindow>

#include "markdown.h"
#include "ui_gaiaViewBase.h"
#include "ui_settingsBase.h"
#include "ui_settingsCSS.h"
#include "ui_settingsEditor.h"
#include "gaiaSettings.h"
#include "gaiaview.h"

Q_DECLARE_LOGGING_CATEGORY ( GAIA )

class KJob;

/**
 * This class serves as the main window for gaia.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author Manuel Vera <manolo.vn@gmail.com>
 * @version %{VERSION}
 */
class gaia : public KXmlGuiWindow
{
    Q_OBJECT

public:
    gaia();

    virtual ~gaia();

private slots:
    void fileNew();
    void fileOpen();
    void fileOpenRecent();
    void downloadFinished ( KJob* job );
    
    void saveFile();
    void saveFileAs();
    void saveFileAs ( const QString &outputFileName );
    
    void cut();
    void copy();
    void paste();
    void undo();
    void redo();
    void print();
    
    void exportAsHtml();
    void exportAsPdf();

    void renderMarkdown();

    void settingsConfigure();

private:
    Ui::settingsBase settingsBase;
    Ui::settingsCSS settingsCSS;
    Ui::settingsEditor settingsEditor;

    Ui::gaiaViewBase gaiaViewBase;

    QString fileName;

    QPlainTextEdit *m_textInput;
    QWebView *m_textOutput;

    QAction *m_exportHtmlAction;
    QAction *m_exportPdfAction;

    gaiaView *m_gaiaView;
};

#endif // GAIA_H
