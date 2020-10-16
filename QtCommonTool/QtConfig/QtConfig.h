#pragma once

#include <QString>
#include <QMutex>
#include <QSettings>

class QtConfig
{
private:
	QtConfig();
	static QtConfig* m_pQtConfigInstance;//单例

public:
	~QtConfig();

	static QtConfig* GetInstance();//获取单例

	QVariant GetValue(QString strGroup, QString strKey, QVariant varDefaultValue = QVariant());
	void SetValue(QString strGroup, QString strKey, QVariant varValue);
private:
	QMutex m_mutex;//写内容时的锁
	QSettings *m_pSettings;
};

