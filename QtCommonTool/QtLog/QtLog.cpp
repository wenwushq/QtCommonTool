#include "QtLog.h"
#include <QDir>
#include <QCoreApplication>
#include <QDate>
#include <QTime>
#include <QTextStream>

QtLog* QtLog::m_pQtLogInstance = new QtLog();

QtLog::QtLog()
{
	QDir dirApp(QCoreApplication::applicationDirPath());
	QString strLogPath = dirApp.absolutePath() + "/log";

	//当前程序下的log目录是否存在，不存在则创建
	if (!dirApp.exists(strLogPath))
		dirApp.mkpath(strLogPath);

	QString strFileName = GenLogFileName();
	m_strLogPath = strLogPath;
	m_strLogFileName = strFileName;
	QString strLogName = strLogPath + "/" + strFileName;

	m_fileLog.setFileName(strLogName);
	OpenFile();
}

QtLog::~QtLog()
{
	if (m_fileLog.isOpen())
	{
		m_fileLog.flush();
		m_fileLog.close();
	}
}

QtLog * QtLog::GetInstance()
{
	return m_pQtLogInstance;
}

void QtLog::WriteLog(QString strLog, LogType eLogType)
{
	QString strCheckName = GenLogFileName();
	if (strCheckName != m_strLogFileName)
	{
		m_strLogFileName = strCheckName;
		QString strLogName = m_strLogPath+ "/" + m_strLogFileName;
		m_fileLog.setFileName(strLogName);
		OpenFile();
	}
	else if(!m_fileLog.isOpen())
	{
		OpenFile();
	}

	if (!m_fileLog.isOpen())
		return;

	QString strTime = QTime::currentTime().toString("hh:mm:ss");
	m_mutex.lock();

	QString strCont = strTime;
	switch (eLogType)
	{
	case LOG_INFO:
		strCont = strTime + "_INFO:";
		break;
	case LOG_WARNING:
		strCont = strTime + "_WARNING:";
		break;
	case LOG_ERROR:
		strCont = strTime + "_ERROR:";
		break;
	default:
		break;
	}
	strCont += strLog;
	QTextStream textStream(&m_fileLog);
	textStream << strCont << endl;
	textStream.flush();
	m_fileLog.flush();
	m_mutex.unlock();
}

//生成日志的文件名
QString QtLog::GenLogFileName()
{
	QString strDate = QDate::currentDate().toString("yyyy-MM-dd");
	return strDate + ".log";
}

//打开文件
bool QtLog::OpenFile()
{
	return m_fileLog.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Append);
}