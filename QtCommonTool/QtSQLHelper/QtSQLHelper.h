#pragma once

#include <QString>
#include <QMutex>
#include <QSqlDatabase>
#include <QSqlQuery>

enum DATABASE_TYPE
{
	UNDEFINED,
	QDB2,
	QMYSQL,//mysql
	QOCI,//oracle
	QODBC,
	QPSQL,//postgres
	QSQLITE,
	QTDS
};

class QtSQLHelper
{
private:
	QtSQLHelper();
	static QtSQLHelper* m_pQtSQLHelperInstance;//单例

public:
	~QtSQLHelper();
	static QtSQLHelper* GetInstance();//获取单例
	void SetConnectParam(QString strHostName, QString strPort, QString strDbName, 
		QString strUserName, QString strPwd, DATABASE_TYPE eType);//设置数据库链接属性值

	QString GetLastError() { return m_strError; }

	bool ExecuteQuery(QString strSql, QSqlQuery &sqlQuery);//执行SQL语句
private:
	void DatabaseDisConnect();//关闭数据库
	
private:
	QMutex m_mutex;//写内容时的锁
	QSqlDatabase m_database;//database的实例
	QString m_strError;
};

