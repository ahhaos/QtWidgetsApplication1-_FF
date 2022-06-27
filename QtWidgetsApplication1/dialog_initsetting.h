#pragma once

#ifndef DIALOG_INITSETTING_H
#define DIALOG_INITSETTING_H
#include <QDialog>
#include "ui_dialog_initsetting.h"
#include <QSettings>
#include "Read_txt.h"
//namespace Ui {
//	class Dialog_initsetting;
//}

class Dialog_initsetting :public QDialog
{
	Q_OBJECT
public :
	explicit Dialog_initsetting(QWidget *parent = 0);
	~Dialog_initsetting();
	//CRead_txt* translator;
	QString settingFileName = QCoreApplication::applicationDirPath() + "/Settings.ini";
	QSettings* settings; 



	public slots:
	void On_ok_button_clicked();
	void On_pushButton_saveTargeNode_clicked();
	void On_pushButton_saveSettings_clicked();
	void On_pushButton_loadSettings_clicked();

	void On_pushButton_Debug_clicked();

	

private:
	//Ui::Dialog *ui;
	Ui::Dialog_initsetting *ui;

signals:
	void stateInit();


};


#endif