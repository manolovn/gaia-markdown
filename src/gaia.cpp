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

#include "gaia.h"

#include <QFileDialog>

#include <KActionCollection>
#include <KMessageBox>
#include <KConfigDialog>
#include <KIO/Job>

gaia::gaia() : KXmlGuiWindow() {
    m_gaiaView = new gaiaView ( this );
    setCentralWidget ( m_gaiaView );

    m_textInput = m_gaiaView->findChild<QTextEdit*> ( "textEdit_input" );
    connect ( m_textInput, SIGNAL ( textChanged() ), this, SLOT ( renderMarkdown() ) );

    m_exportHtmlAction = actionCollection()->addAction ( QStringLiteral ( "file_export_html" ), this, SLOT ( slotSwitchColors() ) );
    m_exportHtmlAction->setText ( i18n ( "HTML" ) );

    m_exportPdfAction = actionCollection()->addAction ( QStringLiteral ( "file_export_pdf" ), this, SLOT ( slotSwitchColors() ) );
    m_exportPdfAction->setText ( i18n ( "PDF" ) );

    actionCollection()->setDefaultShortcut ( m_exportHtmlAction, Qt::CTRL + Qt::Key_H );
    actionCollection()->setDefaultShortcut ( m_exportPdfAction, Qt::CTRL + Qt::Key_P );

    KStandardAction::openNew ( this, SLOT ( fileNew() ), actionCollection() );
    KStandardAction::open ( this, SLOT ( fileOpen() ), actionCollection() );
    KStandardAction::openRecent ( this, SLOT ( fileOpenRecent() ), actionCollection() );
    KStandardAction::save ( this, SLOT ( saveFile() ), actionCollection() );
    KStandardAction::preferences ( this, SLOT ( settingsConfigure() ), actionCollection() );
    KStandardAction::quit ( qApp, SLOT ( closeAllWindows() ), actionCollection() );

    setupGUI();
}

gaia::~gaia() {
}

void gaia::renderMarkdown() {
    m_textOutput = m_gaiaView->findChild<QTextEdit*> ( "textEdit_output" );

    QString textInput = m_textInput->toPlainText();
    QByteArray ba = textInput.toLatin1();
    const char *c = ba.data();

    auto m = mkd_string ( c, textInput.size(), 0 );
    mkd_compile ( m, 0 );

    char* text;
    mkd_document ( m, &text );

    QString html ( text );

    QTextDocument *mTextDocument = new QTextDocument ( 0 );
    mTextDocument->setDefaultStyleSheet ( QString::fromUtf8 ( "h1{color: red;}" ) );
    QTextCursor *_cursor = new QTextCursor ( mTextDocument );
    m_textOutput->setDocument ( mTextDocument );

    _cursor->insertHtml ( html );

    mkd_cleanup ( m );
}

void gaia::fileNew() {
    qCDebug ( GAIA ) << "gaia::fileNew()";
    m_textInput->clear();
}

void gaia::fileOpen() {
    QString filter = "Markdown files (*.md)";
    QUrl fileNameFromDialog = QFileDialog::getOpenFileUrl ( this, i18n ( "Open File" ), QUrl ( "/home" ), filter );

    if ( !fileNameFromDialog.isEmpty() ) {
        KIO::Job* job = KIO::storedGet ( fileNameFromDialog );
        fileName = fileNameFromDialog.toLocalFile();

        connect ( job, SIGNAL ( result ( KJob* ) ), this, SLOT ( downloadFinished ( KJob* ) ) );

        job->exec();
    }
}

void gaia::downloadFinished ( KJob* job ) {
    if ( job->error() ) {
        KMessageBox::error ( this, job->errorString() );
        fileName.clear();
        return;
    }

    KIO::StoredTransferJob* storedJob = ( KIO::StoredTransferJob* ) job;
    m_textInput->setPlainText ( QTextStream ( storedJob->data(), QIODevice::ReadOnly ).readAll() );
}

void gaia::fileOpenRecent() {

}

void gaia::saveFile() {

}

void gaia::settingsConfigure() {
    qCDebug ( GAIA ) << "gaia::settingsConfigure()";
    if ( KConfigDialog::showDialog ( QStringLiteral ( "settings" ) ) ) {
        return;
    }
    KConfigDialog *dialog = new KConfigDialog ( this, QStringLiteral ( "settings" ), gaiaSettings::self() );

    QWidget *generalSettingsDialog = new QWidget;
    settingsBase.setupUi ( generalSettingsDialog );
    dialog->addPage ( generalSettingsDialog, i18n ( "General" ), QStringLiteral ( "package_setting" ) );

    QWidget *cssSettingsDialog = new QWidget;
    settingsCSS.setupUi ( cssSettingsDialog );
    settingsCSS.kcfg_css_theme->addItem ( "Github" );
    settingsCSS.kcfg_css_theme->addItem ( "Bootstrap" );
    settingsCSS.kcfg_css_theme->addItem ( "Solarized Dark" );
    dialog->addPage ( cssSettingsDialog, i18n ( "CSS" ), QStringLiteral ( "package_setting" ) );

    QWidget *editorSettingsDialog = new QWidget;
    settingsEditor.setupUi ( editorSettingsDialog );
    dialog->addPage ( editorSettingsDialog, i18n ( "Editor" ), QStringLiteral ( "package_setting" ) );

    connect ( dialog, SIGNAL ( settingsChanged ( QString ) ), m_gaiaView, SLOT ( slotSettingsChanged() ) );
    dialog->setAttribute ( Qt::WA_DeleteOnClose );
    dialog->show();
}
