#pragma once

#include <QString>
#include <QFile>
#include <QMutex>

enum LogType
{
	LOG_INFO = 0,
	LOG_WARNING,
	LOG_ERROR
};

//////////////////////////////////////////////////////////////////////////
//宏定义
#define  LOGINFO(strLog) QtLog::GetInstance()->WriteLog(strLog, LOG_INFO);
#define  LOGWARNING(strLog) QtLog::GetInstance()->WriteLog(strLog, LOG_WARNING);
#define  LOGERROR(strLog) QtLog::GetInstance()->WriteLog(strLog, LOG_ERROR);

class QtLog
{
private:
	QtLog();
	static QtLog* m_pQtLogInstance;//单例

public:
	~QtLog();

	static QtLog* GetInstance();//获取单例
	void WriteLog(QString strLog, LogType eLogType);//写日志

private:
	QString GenLogFileName();//生成日志的文件名
	bool OpenFile();//打开文件

private:
	QMutex m_mutex;//写内容时的锁
	QFile m_fileLog;
	QString m_strLogPath;
	QString m_strLogFileName;//最新的日志文件名，用做判断，如果程序长时间不关闭会往一个日志文件里写，每一天需要换一个日志文件写
};

