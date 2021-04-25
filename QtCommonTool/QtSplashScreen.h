#pragma once

#include <QSplashScreen>
#include <QMovie>
#include <QTimer>

class QtSplashScreen : public QSplashScreen
{
	Q_OBJECT

public:
	QtSplashScreen(const QPixmap & pixmap);
	QtSplashScreen(const QString strGifPath);
	~QtSplashScreen();

protected:
	virtual void drawContents(QPainter *painter);

private slots:
	void slotUpdate();
	void slotDelay();

private:
	void SetGif(QString strFilePath);

	QMovie *m_pMovie;
	QTimer *m_pTimer;
};
