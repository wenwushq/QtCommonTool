#include "QtFileDialogHelper.h"
#include <QDir>
#include <QCoreApplication>
#include <QSettings>

QtFileDialogHelper::QtFileDialogHelper()
{
	
}

QtFileDialogHelper::~QtFileDialogHelper()
{
}

QString QtFileDialogHelper::GetExistingDirectory(QWidget *parent, const QString &caption, const QString &dir, QFileDialog::Options options)
{
	QString strDir = GetSettingValue(dir);
	QString strRet = QFileDialog::getExistingDirectory(parent, caption, strDir, options);
	if (!strRet.isEmpty())
		SetSettingValue(dir, GetPath(strRet));
	return strRet;
}

QString QtFileDialogHelper::GetOpenFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter, 
	QString *selectedFilter, QFileDialog::Options options)
{
	QString strDir = GetSettingValue(dir);
	QString strRet = QFileDialog::getOpenFileName(parent, caption, strDir, filter, selectedFilter, options);
	if (!strRet.isEmpty())
		SetSettingValue(dir, GetPath(strRet));
	return strRet;
}

QStringList QtFileDialogHelper::GetOpenFileNames(QWidget *parent, const QString &caption, const QString &dir, const QString &filter,
	QString *selectedFilter, QFileDialog::Options options)
{
	QString strDir = GetSettingValue(dir);
	QStringList strlstRet = QFileDialog::getOpenFileNames(parent, caption, strDir, filter, selectedFilter, options);
	if (!strlstRet.isEmpty())
		SetSettingValue(dir, GetPath(strlstRet.first()));
	return strlstRet;
}

QString QtFileDialogHelper::GetSaveFileName(QWidget *parent, const QString &caption, const QString &dir, const QString &filter,
	QString *selectedFilter, QFileDialog::Options options)
{
	QString strDir = GetSettingValue(dir);
	QString strRet = QFileDialog::getSaveFileName(parent, caption, strDir, filter, selectedFilter, options);
	if (!strRet.isEmpty())
		SetSettingValue(dir, strRet);
	return strRet;
}

QString QtFileDialogHelper::GetSettingValue(QString strKey)
{
	QString strFileName = GetSettingPath();
	QSettings setting(strFileName, QSettings::IniFormat);
	setting.beginGroup("FileDialog");
	QString strRet = setting.value(strKey, "/home").toString();
	setting.endGroup();
	return strRet;
}

void QtFileDialogHelper::SetSettingValue(QString strKey, QString strValue)
{
	QString strFileName = GetSettingPath();
	QSettings setting(strFileName, QSettings::IniFormat);
	setting.beginGroup("FileDialog");
	setting.setValue(strKey, strValue);
	setting.endGroup();
}

QString QtFileDialogHelper::GetSettingPath()
{
	QDir dirApp(QCoreApplication::applicationDirPath());
	QString strAppPath = dirApp.absolutePath();

	return strAppPath + "/conf.ini";
}

QString QtFileDialogHelper::GetPath(QString strValue)
{
	return strValue.left(strValue.lastIndexOf("/") - 1);
}