#include "QtSQLHelper.h"
#include <QSqlError>
#include <QStringList>

QtSQLHelper* QtSQLHelper::m_pQtSQLHelperInstance = new QtSQLHelper();

QtSQLHelper::QtSQLHelper()
{
	//SetConnectParam("127.0.0.1", "", ":memory:", "", "", QSQLITE);
}

QtSQLHelper::~QtSQLHelper()
{
	DatabaseDisConnect();//关闭数据库
}

QtSQLHelper * QtSQLHelper::GetInstance()
{
	return m_pQtSQLHelperInstance;
}

//设置数据库链接属性值
void QtSQLHelper::SetConnectParam(QString strHostName, QString strPort, QString strDbName,
	QString strUserName, QString strPwd, DATABASE_TYPE eType)
{
	m_mutex.lock();
	switch (eType)
	{
	case UNDEFINED:
		break;
	case QDB2:
		m_database = QSqlDatabase::addDatabase("QDB2");
		break;
	case QMYSQL:
		m_database = QSqlDatabase::addDatabase("QMYSQL");
		break;
	case QOCI:
		m_database = QSqlDatabase::addDatabase("QOCI");
		break;
	case QODBC:
		m_database = QSqlDatabase::addDatabase("QODBC");
		break;
	case QPSQL:
		m_database = QSqlDatabase::addDatabase("QPSQL");
		break;
	case QSQLITE:
		m_database = QSqlDatabase::addDatabase("QSQLITE");
		break;
	case QTDS:
		m_database = QSqlDatabase::addDatabase("QTDS");
		break;
	default:
		break;
	}
	if (!strHostName.isEmpty())
		m_database.setHostName(strHostName);
	if (!strPort.isEmpty())
		m_database.setPort(strPort.toInt());
	if (!strDbName.isEmpty())
		m_database.setDatabaseName(strDbName);
	if (!strUserName.isEmpty())
		m_database.setUserName(strUserName);
	if (!strPwd.isEmpty())
		m_database.setPassword(strPwd);
	if (!m_database.open())
		m_strError = m_database.lastError().text();
	m_mutex.unlock();
}

//执行SQL语句
bool QtSQLHelper::ExecuteQuery(QString strSql, QSqlQuery &sqlQuery)
{
	m_mutex.lock();
	QSqlQuery sqlQueryRet;
	if (m_database.open())
		sqlQuery = m_database.exec(strSql);
	m_mutex.unlock();

	QString strError = m_database.lastError().text();
	if (!strError.isEmpty())
	{
		m_strError = strError;
		return false;
	}
	return true;
}

//关闭数据库
void QtSQLHelper::DatabaseDisConnect()
{
	m_mutex.lock();
	m_database.close();
	m_mutex.unlock();
}
