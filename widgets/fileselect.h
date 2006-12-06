/***** BEGIN LICENSE BLOCK *****

BSD License

Copyright (c) 2005, NIF File Format Library and Tools
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the NIF File Format Library and Tools projectmay not be
   used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

***** END LICENCE BLOCK *****/

#ifndef FILESELECT_H
#define FILESELECT_h

#include <QAction>
#include <QWidget>
#include <QBoxLayout>

class QCompleter;
class QDirModel;
class QLineEdit;

class FileSelector : public QWidget
{
	Q_OBJECT
public:
	enum Modes
	{
		LoadFile, SaveFile, Folder
	};
	
	FileSelector( Modes mode, const QString & buttonText = "browse", QBoxLayout::Direction dir = QBoxLayout::LeftToRight );
	
    Q_PROPERTY(QString file READ file WRITE setFile NOTIFY sigEdited USER true)
	
	QString text() const { return file(); }
	QString file() const;
	
	void setFilter( const QStringList & f );
	QStringList filter() const;
	
	Modes mode() const { return Mode; }
	void setMode( Modes m ) { Mode = m; }

signals:
	void sigEdited( const QString & );
	void sigActivated( const QString & );

public slots:
	void setText( const QString & );
	void setFile( const QString & );
	
	void replaceText( const QString & );
	
	void setCompletionEnabled( bool );
	
protected slots:
	void browse();
	void activate();
	
protected:
	bool eventFilter( QObject * o, QEvent * e );
	
	QAction * completionAction();
	
	Modes Mode;

	QLineEdit * line;
	QAction   * action;
	
	QDirModel * dirmdl;
	QCompleter * completer;
	QStringList fltr;
};

class CompletionAction : public QAction
{
	Q_OBJECT
public:
	CompletionAction( QObject * parent = 0 );
	~CompletionAction();
	
protected slots:
	void sltToggled( bool );
};

#endif
