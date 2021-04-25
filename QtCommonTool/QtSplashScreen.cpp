#include "QtSplashScreen.h"
#include <QPainter>
#include <QTime>
#include <QApplication>

QtSplashScreen::QtSplashScreen(const QPixmap & pixmap)
	: QSplashScreen(pixmap), m_pMovie(nullptr), m_pTimer(nullptr)
{
}

QtSplashScreen::QtSplashScreen(const QString strGifPath)
	: QSplashScreen()
{
	SetGif(strGifPath);
	QTimer::singleShot(0, this, SLOT(slotDelay()));
}

QtSplashScreen::~QtSplashScreen()
{
	if(m_pTimer)
		m_pTimer->deleteLater();
	m_pTimer = nullptr;
}

void QtSplashScreen::slotUpdate()
{
	setPixmap(m_pMovie->currentPixmap());
	repaint();
}

void QtSplashScreen::slotDelay()
{
	QTime t;
	t.start();
	int nTimeOut = 3000;
	if (m_pMovie)
		nTimeOut = m_pMovie->speed() * m_pMovie->frameCount();
	while (t.elapsed() < nTimeOut)
	{
		QApplication::processEvents();
	}
}

void QtSplashScreen::SetGif(QString strFilePath)
{
	m_pMovie = new QMovie(strFilePath);
	m_pMovie->start();

	m_pTimer = new QTimer(this);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(slotUpdate()));
	m_pTimer->start(m_pMovie->speed());
}

void QtSplashScreen::drawContents(QPainter * painter)
{
	QSplashScreen::drawContents(painter);
}
