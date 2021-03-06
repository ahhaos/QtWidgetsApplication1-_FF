#include "dialog_initsetting.h"
#include "ui_dialog_initsetting.h"
#include <QDialog>
#include "global.h"
#include <QString>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "math.h"
#include "QFile"
#include "wgs_conversions.h"
#ifndef PI
#define PI 3.1415926535892932384626
#endif

using namespace std;
Dialog_initsetting::Dialog_initsetting(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Dialog_initsetting)
{
	ui->setupUi(this);

	ui->lineEdit_Lontitude->setText(QString::number(data_origin_L0,10,4));
	ui->lineEdit_Latitude->setText(QString::number(data_origin_B0, 10, 4));
	ui->lineEdit_Altitude->setText(QString::number(data_origin_H0, 10, 4));

	//ui->lineEdit_X->setText(QString::number(data_origin_X, 10, 4));
	//ui->lineEdit_Y->setText(QString::number(data_origin_Y, 10, 4));
	//ui->lineEdit_Z->setText(QString::number(data_origin_Z, 10, 4));




	ui->lineEdit_V->setText(QString::number(data_origin_V, 10, 4));
	ui->lineEdit_Chi->setText(QString::number(data_origin_Chi, 10, 4));
	ui->lineEdit_Gama->setText(QString::number(data_origin_Gama, 10, 4));

	//translator = new CRead_txt;

	ui->widget_hide1->hide();
	ui->pushButton_Debug->hide();
	ui->pushButton_saveTargeNode->hide();

	settings=new QSettings(settingFileName, QSettings::IniFormat);

	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		qDebug() << "Name        : " << info.portName();
		qDebug() << "Description : " << info.description();
		qDebug() << "Manufacturer: " << info.manufacturer();

		// Example use QSerialPort
		QSerialPort serial;
		serial.setPort(info);
		if (serial.open(QIODevice::ReadWrite))
		{

			ui->comboBox_serialPortName->addItem(info.portName());
			serial.close();
		}
	}

	ui->lineEdit_Latitude->setToolTip(QString::fromLocal8Bit("初始经纬高为航路点序列的第一个点，可在targetNodes.txt中修改。"));
	ui->lineEdit_Lontitude->setToolTip(QString::fromLocal8Bit("初始经纬高为航路点序列的第一个点，可在targetNodes.txt中修改。"));
	ui->lineEdit_Altitude->setToolTip(QString::fromLocal8Bit("初始经纬高为航路点序列的第一个点，可在targetNodes.txt中修改。"));

	On_pushButton_loadSettings_clicked();
	On_pushButton_saveTargeNode_clicked();
}
Dialog_initsetting::~Dialog_initsetting()
{
	delete ui;
}

void Dialog_initsetting::On_ok_button_clicked()
{
	data_origin_L0 = ui->lineEdit_Lontitude->text().toDouble();
	data_origin_B0 = ui->lineEdit_Latitude->text().toDouble();
	data_origin_H0 = ui->lineEdit_Altitude->text().toDouble();



	


	data_origin_V = ui->lineEdit_V->text().toDouble();


	serialPortName = ui->comboBox_serialPortName->currentText().toStdString();
	udpSendTargetIP = ui->lineEdit_targetIP->text().toStdString();
	udpSendTargetPort = ui->lineEdit_targetPort->text().toInt();
	

	emit stateInit();
	//Dialog_initsetting::On_pushButton_saveTargeNode_clicked();

	Dialog_initsetting::~Dialog_initsetting();
}


void Dialog_initsetting::On_pushButton_saveTargeNode_clicked()
{
	targetNode_L_B_H.clear();
	targetNode_X_Y_Z.clear();
	targetNode_Name.clear();
	ui->textBrowser_targetNodes->clear();


	QFile file("targetNodes.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Can't open the targetNodes.txt!" << endl;
	}
	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		QString str(line);

		vector<double>temp;
		//读入目标序列的经纬高
		temp.clear();
		QString tmpstr;
		int indx = 0;
		if(str[indx]=='#')
			continue;
		while (indx < str.size() && str[indx] != ' ' && str[indx] != '\\')			//目标点名
		{
			tmpstr += str[indx];
			indx++;
		}
		targetNode_Name.push_back(tmpstr.toStdString());
		tmpstr.clear();
		while (indx < str.size() && str[indx] == ' ')
		{
			indx++;
		}


		while (indx < str.size() && str[indx] != ' ' && str[indx] != '\\'&& str[indx] != '\n')   //目标经度
		{
			tmpstr += str[indx];
			indx++;
		}
		temp.push_back(tmpstr.toDouble());
		tmpstr.clear();
		while (indx < str.size() && str[indx] == ' ')
		{
			indx++;
		}

		while (indx < str.size() && str[indx] != ' ' && str[indx] != '\\'&& str[indx] != '\n')   //目标纬度
		{
			tmpstr += str[indx];
			indx++;
		}
		temp.push_back(tmpstr.toDouble());
		tmpstr.clear();
		while (indx < str.size() && str[indx] == ' ')
		{
			indx++;
		}

		while (indx < str.size() && str[indx] != ' ' && str[indx] != '\\'&& str[indx] != '\n')   //目标高度
		{
			tmpstr += str[indx];
			indx++;
		}
		temp.push_back(tmpstr.toDouble());
		tmpstr.clear();
		while (indx < str.size() && str[indx] == ' ')
		{
			indx++;
		}
		targetNode_L_B_H.push_back(temp);
		QString appendStr = QString::fromStdString(targetNode_Name.back())+" " +QString::number(targetNode_L_B_H.back()[0], 'f', 3) + " " + QString::number(targetNode_L_B_H.back()[1], 'f', 3) + " " + QString::number(targetNode_L_B_H.back()[2], 'f', 3);
		ui->textBrowser_targetNodes->append(appendStr);
	}


	//将第一个点作为初始点的经纬高
	data_origin_L0 = targetNode_L_B_H[0][0];
	data_origin_B0 = targetNode_L_B_H[0][1];
	data_origin_H0 = targetNode_L_B_H[0][2];

	data_origin_X = 0;
	data_origin_Y = 0;
	data_origin_Z = data_origin_H0;
	// 初始经纬高改变
	L = data_origin_L0;
	B = data_origin_B0;//纬度
	H = data_origin_H0;

	// 初始化东北天ENU的坐标原点
	lla_ref[0] = data_origin_B0;
	lla_ref[1] = data_origin_L0;
	lla_ref[2] = 0;

	ui->lineEdit_Lontitude->setText(QString::number(data_origin_L0, 10, 4));
	ui->lineEdit_Latitude->setText(QString::number(data_origin_B0, 10, 4));
	ui->lineEdit_Altitude->setText(QString::number(data_origin_H0, 10, 4));
	
	




	vector<vector<double>>::iterator it=targetNode_L_B_H.begin();
	WgsConversions wgs_enuConv;

	while (it != targetNode_L_B_H.end())
	{
		double enuXYZ[3];
		double lla[3] = { (*it)[1],(*it)[0] ,(*it)[2] };
		wgs_enuConv.lla2enu(enuXYZ, lla, lla_ref);
		vector<double> tmp = { enuXYZ[0],enuXYZ[1],enuXYZ[2] };
		targetNode_X_Y_Z.push_back(tmp);
		it++;

	}
	it = targetNode_X_Y_Z.begin();
	while (it != targetNode_X_Y_Z.end())
	{
		qDebug() << "X:" << (*it)[0] << "Y:" << (*it)[1] << "Z:" << (*it)[2];
		it++;
	}


	//设置初始航向
	double temp_ = (targetNode_X_Y_Z[1][1] - targetNode_X_Y_Z[0][1]) / (targetNode_X_Y_Z[1][0] - targetNode_X_Y_Z[0][0]);

	if (targetNode_X_Y_Z[1][0] - targetNode_X_Y_Z[0][0] < 0)
	{
		data_origin_Chi = PI + atan(temp_);

	}
	else
	{
		data_origin_Chi = atan(temp_);
	}
	if (data_origin_Chi < -PI)
		data_origin_Chi += (2 * PI);
	if (data_origin_Chi > PI)
		data_origin_Chi -= (2 * PI);



	// 读取刨面信息
	QFile file_2("info.txt");
	if (!file_2.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Can't open the info.txt!" << endl;
	}
	while (!file_2.atEnd())
	{
		QByteArray line = file_2.readLine();
		QString str(line);
		qDebug() << str;
		vector<double>temp;
		//读入目标序列的经纬高
		temp.clear();
		QString tmpstr;
		int indx = 0;
		if (str[indx] == '#')
			continue;
		while (indx < str.size() && str[indx] != ' ' && str[indx] != '\\'&& str[indx] != '\n')   //刨面距离
		{
			tmpstr += str[indx];
			indx++;
		}
		temp.push_back(tmpstr.toDouble());
		tmpstr.clear();
		while (indx < str.size() && str[indx] == ' ')
		{
			indx++;
		}

		while (indx < str.size() && str[indx] != ' ' && str[indx] != '\\'&& str[indx] != '\n')   //该距离对应的高度
		{
			tmpstr += str[indx];
			indx++;
		}
		temp.push_back(tmpstr.toDouble());
		tmpstr.clear();
		while (indx < str.size() && str[indx] == ' ')
		{
			indx++;
		}
		landingPlaningInfo.push_back(temp);
	}
	//for (auto obj : landingPlaningInfo)
	//{
	//	qDebug() << obj[0] << obj[1];
	//}

}

void Dialog_initsetting::On_pushButton_saveSettings_clicked()
{
	settings->setValue("initial_L", ui->lineEdit_Lontitude->text());
	settings->setValue("initial_B", ui->lineEdit_Latitude->text());
	settings->setValue("initial_H", ui->lineEdit_Altitude->text());
	settings->setValue("initial_V", ui->lineEdit_V->text());
	settings->setValue("initial_Chi", ui->lineEdit_Chi->text());
	settings->setValue("initial_Gama", ui->lineEdit_Gama->text());


	settings->setValue("targetIP", ui->lineEdit_targetIP->text());
	settings->setValue("targetPort", ui->lineEdit_targetPort->text());

}


void Dialog_initsetting::On_pushButton_loadSettings_clicked()
{
	ui->lineEdit_Lontitude->setText(settings->value("initial_L").toString());
	ui->lineEdit_Latitude->setText(settings->value("initial_B").toString());
	ui->lineEdit_Altitude->setText(settings->value("initial_H").toString());
	ui->lineEdit_V->setText(settings->value("initial_V").toString());
	ui->lineEdit_Chi->setText(settings->value("initial_Chi").toString());
	ui->lineEdit_Gama->setText(settings->value("initial_Gama").toString());

	ui->lineEdit_targetIP->setText(settings->value("targetIP").toString());
	ui->lineEdit_targetPort->setText(settings->value("targetPort").toString());

}

void Dialog_initsetting::On_pushButton_Debug_clicked()
{


	targetNode_L_B_H.clear();
	targetNode_X_Y_Z.clear();
	targetNode_Name.clear();

	QFile file("targetNodes.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Can't open the targetNodes.txt!" << endl;
	}
	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		QString str(line);
		qDebug() << str;
		ui->textBrowser_targetNodes->append(str);

		vector<double>temp; 

		//读入目标序列的经纬高
		temp.clear();
		QString tmpstr;
		int indx = 0;
		while (indx<str.size()&& str[indx] != ' ' && str[indx] != '\\')			//目标点名
		{
			tmpstr += str[indx];
			indx++;
		}
		targetNode_Name.push_back(tmpstr.toStdString());
		tmpstr.clear();
		while (indx < str.size()&& str[indx] == ' ')
		{
			indx++;
		}


		while (indx < str.size() && str[indx] != ' ' && str[indx] != '\\'&& str[indx] != '\n')   //目标经度
		{
			tmpstr += str[indx];
			indx++;
		}
		temp.push_back(tmpstr.toDouble());
		tmpstr.clear();
		while (indx < str.size() && str[indx] == ' ')
		{
			indx++;
		}

		while (indx < str.size() && str[indx] != ' ' && str[indx] != '\\'&& str[indx] != '\n')   //目标纬度
		{
			tmpstr += str[indx];
			indx++;
		}
		temp.push_back(tmpstr.toDouble());
		tmpstr.clear();
		while (indx < str.size() && str[indx] == ' ')
		{
			indx++;
		}

		while (indx < str.size() && str[indx] != ' ' && str[indx] != '\\'&& str[indx] != '\n')   //目标高度
		{
			tmpstr += str[indx];
			indx++;
		}
		temp.push_back(tmpstr.toDouble());
		tmpstr.clear();
		while (indx < str.size() && str[indx] == ' ')
		{
			indx++;
		}
		targetNode_L_B_H.push_back(temp);
	}


	QFile file_2("info.txt");
	if (!file_2.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Can't open the info.txt!" << endl;
	}
	while (!file_2.atEnd())
	{
		QByteArray line = file_2.readLine();
		QString str(line);
		qDebug() << str;
		ui->textBrowser_targetNodes->append(str);

		vector<double>temp;

		//读入目标序列的经纬高
		temp.clear();
		QString tmpstr;
		int indx = 0;
		while (indx < str.size() && str[indx] != ' ' && str[indx] != '\\'&& str[indx] != '\n')   //刨面距离
		{
			tmpstr += str[indx];
			indx++;
		}
		temp.push_back(tmpstr.toDouble());
		tmpstr.clear();
		while (indx < str.size() && str[indx] == ' ')
		{
			indx++;
		}

		while (indx < str.size() && str[indx] != ' ' && str[indx] != '\\'&& str[indx] != '\n')   //该距离对应的高度
		{
			tmpstr += str[indx];
			indx++;
		}
		temp.push_back(tmpstr.toDouble());
		tmpstr.clear();
		while (indx < str.size() && str[indx] == ' ')
		{
			indx++;
		}
		landingPlaningInfo.push_back(temp);
	}
	for (auto obj : landingPlaningInfo)
	{
		qDebug() << obj[0] << obj[2];
	}

}