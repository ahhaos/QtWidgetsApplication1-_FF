#pragma once


#ifndef SERIALPORT_H
#define SERIALPORT_H


#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSettings>
#include <qdebug.h>
#include <QTextCodec> 
#include <QThread>





class serialport :public QObject
{
	Q_OBJECT

public:

	serialport();
	~serialport();
	void stopThread();
	bool getportstate();

	void portInit(QString portName, int baudRate);
	void HAOYI_DT_Data_Receive_Prepare(quint8 data);
	void HAOYI_DT_Data_Receive_Anl(quint8 *data_buf, quint8 num);
	void sendData(char *TxData, int num);
	void sendText(QString str);

	QSerialPort *myCom;                 //串口对象变量



	struct serialportDataStruct
	{
		quint16 week = 0;
		quint64 second = 0;
		long long int L = 0;
		long long int B = 0;
		int H = 0;
		int Vnorth = 0;
		int Veast = 0;
		int Vland = 0;
		int phi = 0;
		int theta = 0;
		int psi = 0;
		int accX = 0;
		int accY = 0;
		int accZ = 0;
		int angleAccX = 0;
		int angleAccY = 0;
		int angleAccZ = 0;


	};

	void sendSerialportData(serialportDataStruct serialportData);

	public slots:
	void run();





Q_SIGNALS:

	void receiveText(QString str);


private:

	bool comStart = true;




};






#endif // SERIALPORT_H
