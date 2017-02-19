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

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;


class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor ( QWidget *parent = 0 );

    void lineNumberAreaPaintEvent ( QPaintEvent *event );
    int lineNumberAreaWidth();

protected:
    void resizeEvent ( QResizeEvent *event ) override;

private slots:
    void updateLineNumberAreaWidth ( int newBlockCount );
    void highlightCurrentLine();
    void updateLineNumberArea ( const QRect &, int );

private:
    QWidget *lineNumberArea;
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea ( CodeEditor *editor ) : QWidget ( editor ) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize ( codeEditor->lineNumberAreaWidth(), 0 );
    }

protected:
    void paintEvent ( QPaintEvent *event ) override {
        codeEditor->lineNumberAreaPaintEvent ( event );
    }

private:
    CodeEditor *codeEditor;
};


#endif
