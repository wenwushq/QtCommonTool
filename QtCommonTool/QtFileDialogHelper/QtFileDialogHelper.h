#pragma once

#include <QString>
#include <QFileDialog>

class QtFileDialogHelper
{

public:
	QtFileDialogHelper();
	~QtFileDialogHelper();

	//参数dir不能为空，为配置文件中的key，可以读取并保存用户最后一次打开文件的位置
	static QString GetExistingDirectory(QWidget *parent = nullptr, const QString &caption = QString(), const QString &dir = QString(), QFileDialog::Options options = QFileDialog::ShowDirsOnly);
	static QString GetOpenFileName(QWidget *parent = nullptr, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString *selectedFilter = nullptr, QFileDialog::Options options = QFileDialog::Options());
	static QStringList GetOpenFileNames(QWidget *parent = nullptr, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString *selectedFilter = nullptr, QFileDialog::Options options = QFileDialog::Options());
	static QString GetSaveFileName(QWidget *parent = nullptr, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString *selectedFilter = nullptr, QFileDialog::Options options = QFileDialog::Options());

private:
	static QString GetSettingValue(QString strKey);
	static void SetSettingValue(QString strKey, QString strValue);
	static QString GetSettingPath();
	static QString GetPath(QString strValue);
};

