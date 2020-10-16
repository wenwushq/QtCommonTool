#include "QtConfig.h"
#include <QDir>
#include <QCoreApplication>

QtConfig* QtConfig::m_pQtConfigInstance = new QtConfig();

QtConfig::QtConfig()
{
	QDir dirApp(QCoreApplication::applicationDirPath());
	QString strAppPath = dirApp.absolutePath();

	QString strConfigName = strAppPath + "/conf.ini";
	m_pSettings = new QSettings(strConfigName, QSettings::IniFormat);
}

QtConfig::~QtConfig()
{
	if (m_pSettings)
	{
		delete m_pSettings;
		m_pSettings = nullptr;
	}
}

QtConfig * QtConfig::GetInstance()
{
	return m_pQtConfigInstance;
}

QVariant QtConfig::GetValue(QString strGroup, QString strKey, QVariant varDefaultValue)
{
	m_mutex.lock();
	m_pSettings->beginGroup(strGroup);
	QVariant varRet = m_pSettings->value(strKey);
	if (!varRet.isValid())
	{
		m_pSettings->setValue(strKey, varDefaultValue);
		varRet = varDefaultValue;
	}
	m_pSettings->endGroup();
	m_mutex.unlock();
	return varRet;
}

void QtConfig::SetValue(QString strGroup, QString strKey, QVariant varValue)
{
	m_mutex.lock();
	m_pSettings->beginGroup(strGroup);
	m_pSettings->setValue(strKey, varValue);
	m_pSettings->endGroup();
	m_mutex.unlock();
}