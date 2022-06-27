#include "serialPort.h"


#include<QDateTime>
#define byte unsigned char


//将数据拆分成单字节发送
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )
#define BYTE4(dwTemp)       ( *( (char *)(&dwTemp) + 4) )
#define BYTE5(dwTemp)       ( *( (char *)(&dwTemp) + 5) )
#define BYTE6(dwTemp)       ( *( (char *)(&dwTemp) + 6) )
#define BYTE7(dwTemp)       ( *( (char *)(&dwTemp) + 7) )


char data_to_send[50];





serialport::serialport()
{

	myCom = new QSerialPort();
	comStart = true;

}





serialport::~serialport()
{

	delete myCom;
}

void serialport::stopThread()
{
	comStart = false;
	QByteArray temp = myCom->readAll();//清除缓冲区数据
	if (myCom->isOpen())
	{
		myCom->close();


	}
}

bool serialport::getportstate()
{
	if (myCom->isOpen())
	{
		return true;
	}
	else
	{
		return false;
	}
}



void serialport::run()
{

	QByteArray tempStr;
	char *ch;
	int bytenum = 0;//用于储存串口缓存区的数据
					//qDebug()<<"+++";
	if (myCom->isOpen())
	{

		bytenum = myCom->bytesAvailable();//获得串口储存区的数据
										  //            qDebug()<<bytenum;
		if (bytenum >= 1)              //限制频繁进行数据读取
		{
			tempStr = myCom->read(bytenum);
			ch = tempStr.data();
			for (int i = 0; i < bytenum; i++)
			{
				//qDebug()<<"running";
				HAOYI_DT_Data_Receive_Prepare(*(ch + i));

			}
		}

	}

}





void serialport::portInit(QString portName, int baudRate)
{



	if (myCom->isOpen())
	{

		myCom->close();
	}

	comStart = true;
	myCom->setPortName(portName);
	myCom->open(QIODevice::ReadWrite);
	myCom->setBaudRate(baudRate);
	myCom->setDataBits(QSerialPort::Data8);//数据位8位
	myCom->setParity(QSerialPort::NoParity);//无奇偶校验
	myCom->setStopBits(QSerialPort::OneStop);//停止位1位
	myCom->setFlowControl(QSerialPort::NoFlowControl);//无流控制
	qDebug() << baudRate << portName;

}


///////////////////////////////////////////////////////////////////////////////////////
////Data_Receive_Prepare函数是协议预解析，根据协议的格式，将收到的数据进行一次格式性解析，格式正确的话再进行数据解析
////移植时，此函数应由用户根据自身使用的通信方式自行调用，比如串口每收到一字节数据，则调用此函数一次
////此函数解析出符合格式的数据帧后，会自行调用数据解析函数

void serialport::HAOYI_DT_Data_Receive_Prepare(quint8 data)
{

	//一次最大接收数据120个
	static quint8 RxBuffer[120];
	static quint8 _data_len = 0, _data_cnt = 0;
	static quint8 state = 0;      //一定得用static
	if (state == 0 && data == 0xAA)
	{

		state = 1;
		RxBuffer[0] = data;

	}
	else if ((state == 1) && (data == 0xAA))
	{

		state = 2;
		RxBuffer[1] = data;

	}
	else if (state == 2 && (data == 0X01))
	{

		state = 3;
		RxBuffer[2] = data;

	}
	else if (state == 3 && data < 60)
	{
		state = 4;
		RxBuffer[3] = data;    //数据长度
		_data_len = data;
		_data_cnt = 0;

	}
	else if (state == 4 && _data_len > 0)
	{
		_data_len--;
		RxBuffer[4 + _data_cnt++] = data;  //存储数据，_data_len中不包括帧头、帧尾校验和
		if (_data_len == 0) { state = 5; }

	}
	else if (state == 5)
	{
		state = 0;
		RxBuffer[4 + _data_cnt] = data; //应该是最后一个数据,校验和
		HAOYI_DT_Data_Receive_Anl(RxBuffer, _data_cnt + 5);

	}
	else
		state = 0;
}

///////////////////////////////////////////////////////////////////////////////////////
////Data_Receive_Anl函数是协议数据解析函数，函数参数是符合协议格式的一个数据帧，该函数会首先对协议数据进行校验
////校验通过后对数据进行解析，实现相应功能
////此函数可以不用用户自行调用，由函数Data_Receive_Prepare自动调用
void serialport::HAOYI_DT_Data_Receive_Anl(quint8 *data_buf, quint8 num)
{


	quint8 sum = 0;
	for (qint8 i = 0; i < (num - 1); i++)
		sum += *(data_buf + i);
	if (!(sum == *(data_buf + num - 1)))		return;		//判断sum
	if (!(*(data_buf) == 0xAA && *(data_buf + 1) == 0xAA))		return;		//判断帧头
	if (*(data_buf + 2) == 0X01)
	{

		char ch;
		QString messagestr = NULL;
		int j;
		for (int i = 0; i < *(data_buf + 3); i++)
		{
			j = 4 + i;

			ch = *(data_buf + j);
			messagestr = messagestr + ch;
			//qDebug()<<messagestr<<"***";
		}

		qDebug() << messagestr;

		Q_EMIT receiveText(messagestr);





	}


}

void serialport::sendData(char *TxData, int num)
{
	myCom->write(TxData, num);
}

void serialport::sendText(QString str)
{


	char* ch;
	QByteArray ba = str.toLatin1();
	ch = ba.data();
	int num = strlen(ch);
	if (!myCom->isOpen())
	{

		return;
	}
	//qDebug()<<"do not return!";
	int _cnt = 0;
	byte sum = 0;

	data_to_send[_cnt++] = 0xAA;
	data_to_send[_cnt++] = 0xAA;
	data_to_send[_cnt++] = 0x01;
	data_to_send[_cnt++] = 0;            //待写入数据长度

	for (int i = num; i > 0; i--)
	{
		data_to_send[_cnt++] = *(ch++);
	}

	data_to_send[3] = _cnt - 4;       //写入数据长度


	for (int i = 0; i < _cnt; i++)         //写入校验和
	{
		sum += data_to_send[i];
	}
	data_to_send[_cnt++] = sum;

	sendData(data_to_send, _cnt);
}


void serialport::sendSerialportData(serialportDataStruct serialportData)
{

	char* ch;
	//QByteArray ba = str.toLatin1();
	//ch = ba.data();
	//int num = strlen(ch);
	//if (!myCom->isOpen())
	//{

		//return;
	//}
	//qDebug()<<"do not return!";
	int _cnt = 0;
	quint16 len = 83;
	//byte sum = 0;

	data_to_send[_cnt++] = 0xEB;
	data_to_send[_cnt++] = 0x90;		//帧头
	data_to_send[_cnt++] = 0x7A;		//帧识别码
	data_to_send[_cnt++] = 0;            //待写入数据长度
	data_to_send[_cnt++] = BYTE0(len);
	data_to_send[_cnt++] = BYTE1(len);	//写入数据长度

	data_to_send[_cnt++] = BYTE0(serialportData.week);
	data_to_send[_cnt++] = BYTE1(serialportData.week);	//周计数

	data_to_send[_cnt++] = BYTE0(serialportData.second);
	data_to_send[_cnt++] = BYTE1(serialportData.second);
	data_to_send[_cnt++] = BYTE2(serialportData.second);
	data_to_send[_cnt++] = BYTE3(serialportData.second);
	data_to_send[_cnt++] = BYTE4(serialportData.second);
	data_to_send[_cnt++] = BYTE5(serialportData.second);
	data_to_send[_cnt++] = BYTE6(serialportData.second);
	data_to_send[_cnt++] = BYTE7(serialportData.second);//秒计数

	data_to_send[_cnt++] = BYTE0(serialportData.L);
	data_to_send[_cnt++] = BYTE1(serialportData.L);
	data_to_send[_cnt++] = BYTE2(serialportData.L);
	data_to_send[_cnt++] = BYTE3(serialportData.L);
	data_to_send[_cnt++] = BYTE4(serialportData.L);
	data_to_send[_cnt++] = BYTE5(serialportData.L);
	data_to_send[_cnt++] = BYTE6(serialportData.L);
	data_to_send[_cnt++] = BYTE7(serialportData.L);		//经度

	data_to_send[_cnt++] = BYTE0(serialportData.B);
	data_to_send[_cnt++] = BYTE1(serialportData.B);
	data_to_send[_cnt++] = BYTE2(serialportData.B);
	data_to_send[_cnt++] = BYTE3(serialportData.B);
	data_to_send[_cnt++] = BYTE4(serialportData.B);
	data_to_send[_cnt++] = BYTE5(serialportData.B);
	data_to_send[_cnt++] = BYTE6(serialportData.B);
	data_to_send[_cnt++] = BYTE7(serialportData.B);		//纬度

	data_to_send[_cnt++] = BYTE0(serialportData.H);
	data_to_send[_cnt++] = BYTE1(serialportData.H);
	data_to_send[_cnt++] = BYTE2(serialportData.H);
	data_to_send[_cnt++] = BYTE3(serialportData.H);		//高程

	data_to_send[_cnt++] = BYTE0(serialportData.Vnorth);
	data_to_send[_cnt++] = BYTE1(serialportData.Vnorth);
	data_to_send[_cnt++] = BYTE2(serialportData.Vnorth);
	data_to_send[_cnt++] = BYTE3(serialportData.Vnorth);	//北向速

	data_to_send[_cnt++] = BYTE0(serialportData.Veast);
	data_to_send[_cnt++] = BYTE1(serialportData.Veast);
	data_to_send[_cnt++] = BYTE2(serialportData.Veast);
	data_to_send[_cnt++] = BYTE3(serialportData.Veast);		//东向速

	data_to_send[_cnt++] = BYTE0(serialportData.Vland);
	data_to_send[_cnt++] = BYTE1(serialportData.Vland);
	data_to_send[_cnt++] = BYTE2(serialportData.Vland);
	data_to_send[_cnt++] = BYTE3(serialportData.Vland);		//地向速

	data_to_send[_cnt++] = BYTE0(serialportData.phi);
	data_to_send[_cnt++] = BYTE1(serialportData.phi);
	data_to_send[_cnt++] = BYTE2(serialportData.phi);
	data_to_send[_cnt++] = BYTE3(serialportData.phi);		//滚转角

	data_to_send[_cnt++] = BYTE0(serialportData.theta);
	data_to_send[_cnt++] = BYTE1(serialportData.theta);
	data_to_send[_cnt++] = BYTE2(serialportData.theta);
	data_to_send[_cnt++] = BYTE3(serialportData.theta);		//俯仰角

	data_to_send[_cnt++] = BYTE0(serialportData.psi);
	data_to_send[_cnt++] = BYTE1(serialportData.psi);
	data_to_send[_cnt++] = BYTE2(serialportData.psi);
	data_to_send[_cnt++] = BYTE3(serialportData.psi);		//偏航角

	data_to_send[_cnt++] = BYTE0(serialportData.accX);
	data_to_send[_cnt++] = BYTE1(serialportData.accX);
	data_to_send[_cnt++] = BYTE2(serialportData.accX);
	data_to_send[_cnt++] = BYTE3(serialportData.accX);		//加速度X

	data_to_send[_cnt++] = BYTE0(serialportData.accY);
	data_to_send[_cnt++] = BYTE1(serialportData.accY);
	data_to_send[_cnt++] = BYTE2(serialportData.accY);
	data_to_send[_cnt++] = BYTE3(serialportData.accY);		//加速度Y

	data_to_send[_cnt++] = BYTE0(serialportData.accZ);
	data_to_send[_cnt++] = BYTE1(serialportData.accZ);
	data_to_send[_cnt++] = BYTE2(serialportData.accZ);
	data_to_send[_cnt++] = BYTE3(serialportData.accZ);		//加速度Z

	data_to_send[_cnt++] = BYTE0(serialportData.angleAccX);
	data_to_send[_cnt++] = BYTE1(serialportData.angleAccX);
	data_to_send[_cnt++] = BYTE2(serialportData.angleAccX);
	data_to_send[_cnt++] = BYTE3(serialportData.angleAccX);		//角加速度X

	data_to_send[_cnt++] = BYTE0(serialportData.angleAccY);
	data_to_send[_cnt++] = BYTE1(serialportData.angleAccY);
	data_to_send[_cnt++] = BYTE2(serialportData.angleAccY);
	data_to_send[_cnt++] = BYTE3(serialportData.angleAccY);		//角加速度Y

	data_to_send[_cnt++] = BYTE0(serialportData.angleAccZ);
	data_to_send[_cnt++] = BYTE1(serialportData.angleAccZ);
	data_to_send[_cnt++] = BYTE2(serialportData.angleAccZ);
	data_to_send[_cnt++] = BYTE3(serialportData.angleAccZ);		//角加速度Z


	qint16 sum = 0;							//写入校验和
	qint8 sumres;
	for (int i = 2; i < _cnt; i++)
	{
		sum += (qint8)data_to_send[i];
	}
	sumres = 256 - sum % 256;

	data_to_send[_cnt++] = sumres;
	data_to_send[_cnt++] = 0xED;
	data_to_send[_cnt++] = 0x03;

	//data_to_send[3] = _cnt - 4;       //写入数据长度




	//for (int i = num; i > 0; i--)
	//{
	//	data_to_send[_cnt++] = *(ch++);
	//}

	//data_to_send[3] = _cnt - 4;       //写入数据长度


	//for (int i = 0; i < _cnt; i++)         //写入校验和
	//{
	//	sum += data_to_send[i];
	//}
	//data_to_send[_cnt++] = sum;

	sendData(data_to_send, _cnt);

}