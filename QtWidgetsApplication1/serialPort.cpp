#include "serialPort.h"


#include<QDateTime>
#define byte unsigned char


//�����ݲ�ֳɵ��ֽڷ���
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
	QByteArray temp = myCom->readAll();//�������������
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
	int bytenum = 0;//���ڴ��洮�ڻ�����������
					//qDebug()<<"+++";
	if (myCom->isOpen())
	{

		bytenum = myCom->bytesAvailable();//��ô��ڴ�����������
										  //            qDebug()<<bytenum;
		if (bytenum >= 1)              //����Ƶ���������ݶ�ȡ
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
	myCom->setDataBits(QSerialPort::Data8);//����λ8λ
	myCom->setParity(QSerialPort::NoParity);//����żУ��
	myCom->setStopBits(QSerialPort::OneStop);//ֹͣλ1λ
	myCom->setFlowControl(QSerialPort::NoFlowControl);//��������
	qDebug() << baudRate << portName;

}


///////////////////////////////////////////////////////////////////////////////////////
////Data_Receive_Prepare������Э��Ԥ����������Э��ĸ�ʽ�����յ������ݽ���һ�θ�ʽ�Խ�������ʽ��ȷ�Ļ��ٽ������ݽ���
////��ֲʱ���˺���Ӧ���û���������ʹ�õ�ͨ�ŷ�ʽ���е��ã����紮��ÿ�յ�һ�ֽ����ݣ�����ô˺���һ��
////�˺������������ϸ�ʽ������֡�󣬻����е������ݽ�������

void serialport::HAOYI_DT_Data_Receive_Prepare(quint8 data)
{

	//һ������������120��
	static quint8 RxBuffer[120];
	static quint8 _data_len = 0, _data_cnt = 0;
	static quint8 state = 0;      //һ������static
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
		RxBuffer[3] = data;    //���ݳ���
		_data_len = data;
		_data_cnt = 0;

	}
	else if (state == 4 && _data_len > 0)
	{
		_data_len--;
		RxBuffer[4 + _data_cnt++] = data;  //�洢���ݣ�_data_len�в�����֡ͷ��֡βУ���
		if (_data_len == 0) { state = 5; }

	}
	else if (state == 5)
	{
		state = 0;
		RxBuffer[4 + _data_cnt] = data; //Ӧ�������һ������,У���
		HAOYI_DT_Data_Receive_Anl(RxBuffer, _data_cnt + 5);

	}
	else
		state = 0;
}

///////////////////////////////////////////////////////////////////////////////////////
////Data_Receive_Anl������Э�����ݽ������������������Ƿ���Э���ʽ��һ������֡���ú��������ȶ�Э�����ݽ���У��
////У��ͨ��������ݽ��н�����ʵ����Ӧ����
////�˺������Բ����û����е��ã��ɺ���Data_Receive_Prepare�Զ�����
void serialport::HAOYI_DT_Data_Receive_Anl(quint8 *data_buf, quint8 num)
{


	quint8 sum = 0;
	for (qint8 i = 0; i < (num - 1); i++)
		sum += *(data_buf + i);
	if (!(sum == *(data_buf + num - 1)))		return;		//�ж�sum
	if (!(*(data_buf) == 0xAA && *(data_buf + 1) == 0xAA))		return;		//�ж�֡ͷ
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
	data_to_send[_cnt++] = 0;            //��д�����ݳ���

	for (int i = num; i > 0; i--)
	{
		data_to_send[_cnt++] = *(ch++);
	}

	data_to_send[3] = _cnt - 4;       //д�����ݳ���


	for (int i = 0; i < _cnt; i++)         //д��У���
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
	data_to_send[_cnt++] = 0x90;		//֡ͷ
	data_to_send[_cnt++] = 0x7A;		//֡ʶ����
	data_to_send[_cnt++] = 0;            //��д�����ݳ���
	data_to_send[_cnt++] = BYTE0(len);
	data_to_send[_cnt++] = BYTE1(len);	//д�����ݳ���

	data_to_send[_cnt++] = BYTE0(serialportData.week);
	data_to_send[_cnt++] = BYTE1(serialportData.week);	//�ܼ���

	data_to_send[_cnt++] = BYTE0(serialportData.second);
	data_to_send[_cnt++] = BYTE1(serialportData.second);
	data_to_send[_cnt++] = BYTE2(serialportData.second);
	data_to_send[_cnt++] = BYTE3(serialportData.second);
	data_to_send[_cnt++] = BYTE4(serialportData.second);
	data_to_send[_cnt++] = BYTE5(serialportData.second);
	data_to_send[_cnt++] = BYTE6(serialportData.second);
	data_to_send[_cnt++] = BYTE7(serialportData.second);//�����

	data_to_send[_cnt++] = BYTE0(serialportData.L);
	data_to_send[_cnt++] = BYTE1(serialportData.L);
	data_to_send[_cnt++] = BYTE2(serialportData.L);
	data_to_send[_cnt++] = BYTE3(serialportData.L);
	data_to_send[_cnt++] = BYTE4(serialportData.L);
	data_to_send[_cnt++] = BYTE5(serialportData.L);
	data_to_send[_cnt++] = BYTE6(serialportData.L);
	data_to_send[_cnt++] = BYTE7(serialportData.L);		//����

	data_to_send[_cnt++] = BYTE0(serialportData.B);
	data_to_send[_cnt++] = BYTE1(serialportData.B);
	data_to_send[_cnt++] = BYTE2(serialportData.B);
	data_to_send[_cnt++] = BYTE3(serialportData.B);
	data_to_send[_cnt++] = BYTE4(serialportData.B);
	data_to_send[_cnt++] = BYTE5(serialportData.B);
	data_to_send[_cnt++] = BYTE6(serialportData.B);
	data_to_send[_cnt++] = BYTE7(serialportData.B);		//γ��

	data_to_send[_cnt++] = BYTE0(serialportData.H);
	data_to_send[_cnt++] = BYTE1(serialportData.H);
	data_to_send[_cnt++] = BYTE2(serialportData.H);
	data_to_send[_cnt++] = BYTE3(serialportData.H);		//�߳�

	data_to_send[_cnt++] = BYTE0(serialportData.Vnorth);
	data_to_send[_cnt++] = BYTE1(serialportData.Vnorth);
	data_to_send[_cnt++] = BYTE2(serialportData.Vnorth);
	data_to_send[_cnt++] = BYTE3(serialportData.Vnorth);	//������

	data_to_send[_cnt++] = BYTE0(serialportData.Veast);
	data_to_send[_cnt++] = BYTE1(serialportData.Veast);
	data_to_send[_cnt++] = BYTE2(serialportData.Veast);
	data_to_send[_cnt++] = BYTE3(serialportData.Veast);		//������

	data_to_send[_cnt++] = BYTE0(serialportData.Vland);
	data_to_send[_cnt++] = BYTE1(serialportData.Vland);
	data_to_send[_cnt++] = BYTE2(serialportData.Vland);
	data_to_send[_cnt++] = BYTE3(serialportData.Vland);		//������

	data_to_send[_cnt++] = BYTE0(serialportData.phi);
	data_to_send[_cnt++] = BYTE1(serialportData.phi);
	data_to_send[_cnt++] = BYTE2(serialportData.phi);
	data_to_send[_cnt++] = BYTE3(serialportData.phi);		//��ת��

	data_to_send[_cnt++] = BYTE0(serialportData.theta);
	data_to_send[_cnt++] = BYTE1(serialportData.theta);
	data_to_send[_cnt++] = BYTE2(serialportData.theta);
	data_to_send[_cnt++] = BYTE3(serialportData.theta);		//������

	data_to_send[_cnt++] = BYTE0(serialportData.psi);
	data_to_send[_cnt++] = BYTE1(serialportData.psi);
	data_to_send[_cnt++] = BYTE2(serialportData.psi);
	data_to_send[_cnt++] = BYTE3(serialportData.psi);		//ƫ����

	data_to_send[_cnt++] = BYTE0(serialportData.accX);
	data_to_send[_cnt++] = BYTE1(serialportData.accX);
	data_to_send[_cnt++] = BYTE2(serialportData.accX);
	data_to_send[_cnt++] = BYTE3(serialportData.accX);		//���ٶ�X

	data_to_send[_cnt++] = BYTE0(serialportData.accY);
	data_to_send[_cnt++] = BYTE1(serialportData.accY);
	data_to_send[_cnt++] = BYTE2(serialportData.accY);
	data_to_send[_cnt++] = BYTE3(serialportData.accY);		//���ٶ�Y

	data_to_send[_cnt++] = BYTE0(serialportData.accZ);
	data_to_send[_cnt++] = BYTE1(serialportData.accZ);
	data_to_send[_cnt++] = BYTE2(serialportData.accZ);
	data_to_send[_cnt++] = BYTE3(serialportData.accZ);		//���ٶ�Z

	data_to_send[_cnt++] = BYTE0(serialportData.angleAccX);
	data_to_send[_cnt++] = BYTE1(serialportData.angleAccX);
	data_to_send[_cnt++] = BYTE2(serialportData.angleAccX);
	data_to_send[_cnt++] = BYTE3(serialportData.angleAccX);		//�Ǽ��ٶ�X

	data_to_send[_cnt++] = BYTE0(serialportData.angleAccY);
	data_to_send[_cnt++] = BYTE1(serialportData.angleAccY);
	data_to_send[_cnt++] = BYTE2(serialportData.angleAccY);
	data_to_send[_cnt++] = BYTE3(serialportData.angleAccY);		//�Ǽ��ٶ�Y

	data_to_send[_cnt++] = BYTE0(serialportData.angleAccZ);
	data_to_send[_cnt++] = BYTE1(serialportData.angleAccZ);
	data_to_send[_cnt++] = BYTE2(serialportData.angleAccZ);
	data_to_send[_cnt++] = BYTE3(serialportData.angleAccZ);		//�Ǽ��ٶ�Z


	qint16 sum = 0;							//д��У���
	qint8 sumres;
	for (int i = 2; i < _cnt; i++)
	{
		sum += (qint8)data_to_send[i];
	}
	sumres = 256 - sum % 256;

	data_to_send[_cnt++] = sumres;
	data_to_send[_cnt++] = 0xED;
	data_to_send[_cnt++] = 0x03;

	//data_to_send[3] = _cnt - 4;       //д�����ݳ���




	//for (int i = num; i > 0; i--)
	//{
	//	data_to_send[_cnt++] = *(ch++);
	//}

	//data_to_send[3] = _cnt - 4;       //д�����ݳ���


	//for (int i = 0; i < _cnt; i++)         //д��У���
	//{
	//	sum += data_to_send[i];
	//}
	//data_to_send[_cnt++] = sum;

	sendData(data_to_send, _cnt);

}