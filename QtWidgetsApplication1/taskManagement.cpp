#include "taskManagement.h"
#include <math.h>

#include <QDebug>



taskManagement::taskManagement(CCloseLoopModel* clm_control)
{
	wgs_enuConversion = new WgsConversions;
	//txt_transmit = new CRead_txt;
	clm_control_task = clm_control;								//���ջ�����ϵͳָ��������ֱ࣬���ڸ�����ʵ�ֱջ�ϵͳ����
	currentMode	= Mode_default;									//Ĭ�Ϸ���״̬Ϊ����͸߶ȱ���
	//defaultStatus.Vxyz = data_origin_V;							//��÷ɻ��ĳ�ʼ�ٶ���Ϊ�������ĳ�ʼ�����ٶ�
	//defaultStatus.Vx = data_origin_V*cos(data_origin_Chi);		//������������������ٶ�
	//defaultStatus.Vy = data_origin_V*sin(data_origin_Chi);		//������������������ٶ�
	//defaultStatus.dZ = data_origin_Z;							//���ֳ�ʼ�߶�
	//�ڷ����ʼ��(��һ����������)ʱm_fst.m_Vx��m_fst.m_Vy...��Ϊ0,����ֱ��ʹ��taskManagement::Update()�еļ��㷽�����㣬��Ҫ�ø÷�����������Ĭ��ֵ���Թ���ʼ������״̬
	X_c = clm_control_task->m_fst.m_dX;
	Y_c = clm_control_task->m_fst.m_dY;
	Z_c = clm_control_task->m_fst.m_dZ;

	PID_Chi = new Pid_control;
	PID_Chi->outPutLimit = 45;
	PID_Chi->Kp0 = 0.2;
	PID_Chi->Kd0 = 0.04;
	PID_Chi->Ki0 = 0.05;

	PID_H= new Pid_control;
	PID_H->Kp0 = 1;
	PID_H->Ki0 = 0.0;
	PID_H->Kd0 = 0.0;
	PID_H->interLimit = 50;
	PID_H->outPutLimit = 10;
	//trackGenerator = new trackGeneration(data_time);

}
taskManagement::~taskManagement()
{

}

void taskManagement::currentModeSet(unsigned int mode)
{
	emit ModeChanged(mode);
	switch (mode)
	{
	case Mode_default:
		Command_VKH[0] = clm_control_task->m_fst.m_dV;				//����ڷ���������л���Ĭ�Ϸ���ģʽ�����Ȼ�÷������ĺ����ٶ���Ϊ�����������������ٶȣ������и߶ȱ��֡�
		Command_VKH[1] = clm_control_task->m_fst.m_dChi;
		Command_VKH[2] = clm_control_task->m_fst.m_dZ;				//����ǰ���ٶȡ����򡢸߶���ΪĬ��ֵ����ֹ����������������ɺ������»�ȡ����ָ��
		break;
	case Mode_PositionFollow:				
		//defaultStatus.Vxyz = sqrt(pow(clm_control_task->m_fst.m_Vx, 2) + pow(clm_control_task->m_fst.m_Vy, 2) + pow(clm_control_task->m_fst.m_Vz, 2));	//����ģʽ�л�ǰ���������ٶȣ���Ϊ������ˮƽ�ٶ�
		//defaultStatus.Vx = defaultStatus.Vxyz*clm_control_task->m_fst.m_Vx/ sqrt(pow(clm_control_task->m_fst.m_Vx, 2) + pow(clm_control_task->m_fst.m_Vy, 2));			//���������Ķ����ٶ�
		//defaultStatus.Vy = defaultStatus.Vxyz*clm_control_task->m_fst.m_Vy / sqrt(pow(clm_control_task->m_fst.m_Vx, 2) + pow(clm_control_task->m_fst.m_Vy, 2));			//���������ı����ٶ�		//Ŀ���Ǳ���ԭ�еĺ��򲻱�
		//defaultStatus.dZ = clm_control_task->m_fst.m_dZ;	//�����������浽�ṹ�壬�Թ�Update()ʹ��
		X_c = clm_control_task->m_fst.m_dX;
		Y_c = clm_control_task->m_fst.m_dY;
		Z_c = clm_control_task->m_fst.m_dZ;
		//double chi= clm_control_task->m_fst.m_dChi
			//XVofset=
		xiaHuaChi = clm_control_task->m_fst.m_dChi;
		break;
	case Mode_PositionFollow_V:				

		break;

	case  Mode_ManualOperation:						//���ݸ˷���ģʽ
		Command_Manual[0] = clm_control_task->m_fst.m_dV;				//����ڷ���������л���Ĭ�Ϸ���ģʽ�����Ȼ�÷������ĺ����ٶ���Ϊ�����������������ٶȣ������и߶ȱ��֡�
		Command_Manual[1] = clm_control_task->m_fst.m_dChi;
		Command_Manual[2] = clm_control_task->m_fst.m_dZ;				//����ǰ���ٶȡ����򡢸߶���ΪĬ��ֵ����ֹ����������������ɺ������»�ȡ����ָ��
		break;



	case Mode_Waypoint:
		
		targetSequence_it = targetNode_X_Y_Z.begin()+1;
		
		Command_XYZV[0] = targetSequence_it->at(0);
		Command_XYZV[1] = targetSequence_it->at(1);
		Command_XYZV[2] = targetSequence_it->at(2);
		Command_XYZV[3] = 65;
		X_c = Command_XYZV[0];
		Y_c = Command_XYZV[1];
		Z_c = Command_XYZV[2];
		if ((targetSequence_it - 1)->size() == 4)
		{
			emit targetArrived(int((targetSequence_it - 1)->at(3) + 0.5));
		}

		break;


	case Mode_Waypoint_2:
		//trackGenerator = new trackGeneration(clm_control_task->m_fst.m_dX, clm_control_task->m_fst.m_dY, clm_control_task->m_fst.m_dZ, targetNode_X_Y_Z);
		pathGenerator = new pathGeneration(clm_control_task->m_fst.m_dX, clm_control_task->m_fst.m_dY, clm_control_task->m_fst.m_dZ, targetNode_X_Y_Z, follow_V);
		pathGenerator_2 = new pathGeneration(clm_control_task->m_fst.m_dX, clm_control_task->m_fst.m_dY, clm_control_task->m_fst.m_dZ, targetNode_X_Y_Z, follow_V);
		//emit drawExpect_Z();
		//Command_VKH[0] = clm_control_task->m_fst.m_dV;
		//Command_VKH[1] = clm_control_task->m_fst.m_dChi;
		//Command_VKH[2] = clm_control_task->m_fst.m_dZ;				//����ǰ���ٶȡ����򡢸߶���ΪĬ��ֵ����ֹ����������������ɺ������»�ȡ����ָ��
		break;

	
	case Mode_ZhuoJianFangZhen:
	{
		//pathGenerator = new pathGeneration(clm_control_task->m_fst.m_dX, clm_control_task->m_fst.m_dY, clm_control_task->m_fst.m_dZ, targetNode_X_Y_Z, follow_V);
		//pathGenerator_2 = new pathGeneration(clm_control_task->m_fst.m_dX, clm_control_task->m_fst.m_dY, clm_control_task->m_fst.m_dZ, targetNode_X_Y_Z, follow_V);
		//emit drawExpect_Z();

		//asdf 
		X_c = clm_control_task->m_fst.m_dX;
		Y_c = clm_control_task->m_fst.m_dY;
		Z_c = clm_control_task->m_fst.m_dZ;
		emit drawLandingPlaning();
	}
	}
	currentMode = mode ;

}
//
void taskManagement::Update()
{
	double curZ = clm_control_task->m_fst.m_dZ;
	double step_second = data_time / 1000;
	static bool pianChaZhuojian = false;
	static int targetCnt = 0;
	
	static double zhuojianXYZV[4];
	static double hc = 0;
	double tmp;
	
	switch (currentMode)
	{
	case Mode_default:											//Ӧ��ָ������ٶȡ����򡢸߶�Command_VKH[0], Command_VKH[1], Command_VKH[2]
		SimulationTime += step_second;
		//
		if(Command_VKH[2]- curZ>100)
			clm_control_task->Input_VKH(Command_VKH[0], Command_VKH[1], clm_control_task->m_fst.m_dZ+10);
		else if (Command_VKH[2] - curZ < -100)
			clm_control_task->Input_VKH(Command_VKH[0], Command_VKH[1], clm_control_task->m_fst.m_dZ - 10);
		else {
			clm_control_task->Input_VKH(Command_VKH[0], Command_VKH[1], Command_VKH[2]);
		}
		//clm_control_task->Input_VKH(Command_VKH[0], Command_VKH[1], Command_VKH[2]);
		clm_control_task->Update();
		break;

	case Mode_PositionFollow:							//�ú��򡢸߶ȱ��ֵķ���ʹ�õ��Ǻ�·��׷�ٷ��������ɼ����Ľ�///////////////////////////////////////////////
		SimulationTime += step_second;
		if (clm_control_task->m_fst.m_dV > 1)//ʹ�÷ɻ����ٶ�С��1��Ϊֹͣ��׼
		{
			//double Command_xiaHua[3] = { 70,0,0 };				//�»�ָ��ٶȣ��Ƕȣ��Ž��߶�
			if (clm_control_task->m_fst.m_dZ >= Command_xiaHua[2]+4)//ʹ�÷ɻ�����߶Ƚӽ�0��Ϊ�жϴ�����׼
			{
				X_c += cos(xiaHuaChi)*cos(Command_xiaHua[1])*Command_xiaHua[0] * data_time / 1000;
				Y_c += sin(xiaHuaChi)*cos(Command_xiaHua[1])*Command_xiaHua[0] * data_time / 1000;
				Z_c += sin(Command_xiaHua[1])*Command_xiaHua[0] * data_time / 1000;
				//qDebug() << X_c << ";" << Y_c << ";" << Z_c << ";";
			}
			else if (clm_control_task->m_fst.m_dZ >= Command_xiaHua[2] + 2)//ʹ�÷ɻ�����߶Ƚӽ�0��Ϊ�жϴ�����׼
			{
				X_c += cos(xiaHuaChi)*cos(Command_xiaHua[1]/2)*Command_xiaHua[0] * data_time / 1000;
				Y_c += sin(xiaHuaChi)*cos(Command_xiaHua[1] / 2)*Command_xiaHua[0] * data_time / 1000;
				Z_c += sin(Command_xiaHua[1] / 2)*Command_xiaHua[0] * data_time / 1000;
				//qDebug() << X_c << ";" << Y_c << ";" << Z_c << ";";
			}
			else if (clm_control_task->m_fst.m_dZ >= Command_xiaHua[2] + 1)//ʹ�÷ɻ�����߶Ƚӽ�0��Ϊ�жϴ�����׼
			{
				X_c += cos(xiaHuaChi)*cos(Command_xiaHua[1] / 3)*Command_xiaHua[0] * data_time / 1000;
				Y_c += sin(xiaHuaChi)*cos(Command_xiaHua[1] / 3)*Command_xiaHua[0] * data_time / 1000;
				Z_c += sin(Command_xiaHua[1] / 3)*Command_xiaHua[0] * data_time / 1000;
				//qDebug() << X_c << ";" << Y_c << ";" << Z_c << ";";
			}
			else if (clm_control_task->m_fst.m_dZ >= Command_xiaHua[2] + 0.3)//ʹ�÷ɻ�����߶Ƚӽ�0��Ϊ�жϴ�����׼
			{
				X_c += cos(xiaHuaChi)*cos(-PI / 360)*Command_xiaHua[0] * data_time / 1000;
				Y_c += sin(xiaHuaChi)*cos(-PI / 360)*Command_xiaHua[0] * data_time / 1000;
				Z_c += sin(-PI / 360)*Command_xiaHua[0] * data_time / 1000;
				//qDebug() << X_c << ";" << Y_c << ";" << Z_c << ";";
			}
			else
			{
				X_c += cos(xiaHuaChi)*Command_xiaHua[0] * data_time / 1000;
				Y_c += sin(xiaHuaChi)*Command_xiaHua[0] * data_time / 1000;
				Z_c = Command_xiaHua[2];
				m_landing_bool = 1;
			}
		}
		else
		{
			//��ͣ����
			//return TRUE;
			//timeKillEvent(timer_id_simulation);
			//�����ʱ���ֱ���   
			//timeEndPeriod(1);
		}

		clm_control_task->Follow(X_c, Y_c, Z_c,0,0,0);
		clm_control_task->Update();		
		break;
	case Mode_PositionFollow_V:
		SimulationTime += step_second;
		//clm_control_task->Input_XYZ_V(Command_XYZV[0],Command_XYZV[1],Command_XYZV[2],Command_XYZV[3]);
		if (Command_XYZV[2] - curZ > 100)
		{
			clm_control_task->Input_VKH(Command_VKH[0], Command_VKH[1], clm_control_task->m_fst.m_dZ + 10);
			//clm_control_task->Input_XYZ_V(Command_XYZV[0], Command_XYZV[1], curZ + 10, Command_XYZV[3]);
			//qDebug() << 1;
		}
		else if (Command_XYZV[2] - curZ < -100)
		{
			clm_control_task->Input_VKH(Command_VKH[0], Command_VKH[1], clm_control_task->m_fst.m_dZ + 10);
			//clm_control_task->Input_XYZ_V(Command_XYZV[0], Command_XYZV[1], curZ - 10, Command_XYZV[3]);
			//qDebug() << 2;
		}
		else {
			clm_control_task->Input_XYZ_V(Command_XYZV[0], Command_XYZV[1], Command_XYZV[2], Command_XYZV[3]);
			//qDebug() << 3;
		}
		
		clm_control_task->Update();
		if (sqrt((clm_control_task->m_fst.m_dX - Command_XYZV[0])*(clm_control_task->m_fst.m_dX - Command_XYZV[0]) +
			(clm_control_task->m_fst.m_dY - Command_XYZV[1])*(clm_control_task->m_fst.m_dY - Command_XYZV[1]) +
			(clm_control_task->m_fst.m_dZ - Command_XYZV[2])*(clm_control_task->m_fst.m_dZ - Command_XYZV[2])) < arriveDistanceFlag * 100)												//�Էɻ�����Ŀ���ľ���С��һ����Ϊ�ж��Ƿ�ﵽĿ���ı�׼
		{
			
			currentModeSet(Mode_default);					//�ﵽĿ������б���
		}
		break;

	case Mode_ManualOperation:
		SimulationTime += step_second;
		//qDebug() << "0:" << Command_Manual[0] << "1:" << Command_Manual[1] << "2:" << Command_Manual[2] << "3:" << Command_Manual[3];
		clm_control_task->Input_VKH(Command_Manual[0], Command_Manual[1], Command_Manual[2]);
		clm_control_task->Update();
		break;



	case Mode_Waypoint:
		SimulationTime += step_second;
		//if (Command_XYZV[2] - curZ > 100)
		//{
		//	clm_control_task->Input_XYZ_V(Command_XYZV[0], Command_XYZV[1], curZ + 10, Command_XYZV[3]);
		//	qDebug() << 1;
		//}
		//else if (Command_XYZV[2] - curZ < -100)
		//{
		//	clm_control_task->Input_XYZ_V(Command_XYZV[0], Command_XYZV[1], curZ - 10, Command_XYZV[3]);
		//	qDebug() << 2;
		//}
		//else {
		//	clm_control_task->Input_XYZ_V(Command_XYZV[0], Command_XYZV[1], Command_XYZV[2], Command_XYZV[3]);
		//	qDebug() << 3;
		//}
		clm_control_task->Input_XYZ_V(Command_XYZV[0], Command_XYZV[1], Command_XYZV[2], Command_XYZV[3]);
		clm_control_task->Update();

		if (sqrt((clm_control_task->m_fst.m_dX - Command_XYZV[0])*(clm_control_task->m_fst.m_dX - Command_XYZV[0]) +
			(clm_control_task->m_fst.m_dY - Command_XYZV[1])*(clm_control_task->m_fst.m_dY - Command_XYZV[1]) +
			(clm_control_task->m_fst.m_dZ - Command_XYZV[2])*(clm_control_task->m_fst.m_dZ - Command_XYZV[2])) < arriveDistanceFlag
			)												//�Էɻ�����Ŀ���ľ���С��1��Ϊ�ж��Ƿ�ﵽĿ���ı�׼
		{
			if (targetSequence_it!=targetNode_X_Y_Z.end()-1)
			{
				targetSequence_it++;
				Command_XYZV[0] = targetSequence_it->at(0);
				Command_XYZV[1] = targetSequence_it->at(1);
				Command_XYZV[2] = targetSequence_it->at(2);

				X_c = Command_XYZV[0];
				Y_c = Command_XYZV[1];
				Z_c = Command_XYZV[2];
				if (targetSequence_it->size()==4)
				{
					emit targetArrived(int(targetSequence_it->at(3) + 0.5)-1);
				}
				qDebug() << X_c << ";" << Y_c << ";" << Z_c;
				
			}
			else
			{
				currentModeSet(Mode_default);					//�ﵽĿ������б���
				if (targetSequence_it->size() == 4)
				{
					emit targetArrived(int(targetSequence_it->at(3) + 0.5));
				}
			}
			//
		}
		break;

	case Mode_Waypoint_2:											
		SimulationTime += step_second;
		//qDebug() << "running";
		//Command_XYZ=trackGenerator->getNextTrackNode(80);
		haveArrivedNodeNumber = pathGenerator->getNode(X_c, Y_c, Z_c);
		if (haveArrivedNodeNumber !=-3)
		{
			emit targetArrived(haveArrivedNodeNumber);
		}
		if (haveArrivedNodeNumber==-2)
		{
			currentModeSet(Mode_default);
		}
		//
		//qDebug() << X_c << ";" << Y_c << ";" << Z_c;
/*		clm_control_task->Follow(X_c, Y_c, Z_c,0,0,0);

		clm_control_task->Update();*/
		clm_control_task->Follow(X_c, Y_c, Z_c, 0, 0, 0);
		clm_control_task->Update(X_c, Y_c, Z_c, 0, 0, 0);
		break;
	case Mode_ZhuoJianFangZhen:
		SimulationTime += step_second;

		//if (!pianChaZhuojian)
		//{
		//	haveArrivedNodeNumber = pathGenerator->getNode(X_c, Y_c, Z_c);
		//	if (haveArrivedNodeNumber != -3)
		//	{
		//		emit targetArrived(haveArrivedNodeNumber);
		//	}
		//	if (haveArrivedNodeNumber == -2)
		//	{
		//		//currentModeSet(Mode_default);
		//		pianChaZhuojian = true;
		//		X_c = clm_control_task->m_fst.m_dX;
		//		Y_c = clm_control_task->m_fst.m_dY;
		//		Z_c = clm_control_task->m_fst.m_dZ;
		//	}
		//	//
		//	//qDebug() << X_c << ";" << Y_c << ";" << Z_c;
		//	clm_control_task->Follow(X_c, Y_c, Z_c, 0, 0, 0);
		//	clm_control_task->Update(X_c, Y_c, Z_c, 0, 0, 0);
		//}
		if (!pianChaZhuojian)
		{
			Command_XYZV[0] = targetNode_X_Y_Z[targetCnt][0];
			Command_XYZV[1] = targetNode_X_Y_Z[targetCnt][1];
			Command_XYZV[2] = targetNode_X_Y_Z[targetCnt][2];
			Command_XYZV[3] = 66.6;
			//qDebug() << Command_XYZV[0] << Command_XYZV[1] << Command_XYZV[2] << Command_XYZV[3];
			if (Command_XYZV[2] - curZ > 100)
			{
				clm_control_task->Input_XYZ_V(Command_XYZV[0], Command_XYZV[1], clm_control_task->m_fst.m_dZ + 10, Command_XYZV[3]);
			}
			else if (Command_XYZV[2] - curZ < -100)
			{
				clm_control_task->Input_XYZ_V(Command_XYZV[0], Command_XYZV[1], clm_control_task->m_fst.m_dZ - 10, Command_XYZV[3]);
			}
			else {
				clm_control_task->Input_XYZ_V(Command_XYZV[0], Command_XYZV[1], Command_XYZV[2], Command_XYZV[3]);
			}

			if (sqrt((clm_control_task->m_fst.m_dX - Command_XYZV[0])*(clm_control_task->m_fst.m_dX - Command_XYZV[0]) +
				(clm_control_task->m_fst.m_dY - Command_XYZV[1])*(clm_control_task->m_fst.m_dY - Command_XYZV[1])) < arriveDistanceFlag * 10)												//�Էɻ�����Ŀ���ľ���С��һ����Ϊ�ж��Ƿ�ﵽĿ���ı�׼
			{
				emit targetArrived(targetCnt);
				targetCnt++;
				if (targetCnt >= targetNode_X_Y_Z.size())
				{
					pianChaZhuojian = true;
					baseChi_deg = (clm_control_task->m_fst.m_dChi)/PI*180;
					zhuojianXYZV[0] = clm_control_task->m_fst.m_dX + follow_V * 2 * cos(clm_control_task->m_fst.m_dChi);
					zhuojianXYZV[1] = clm_control_task->m_fst.m_dX + follow_V * 2 * sin(clm_control_task->m_fst.m_dChi);
					zhuojianXYZV[2] = clm_control_task->m_fst.m_dZ;
					hc = clm_control_task->m_fst.m_dZ;
				}
			}
			clm_control_task->Update();
		}
		else
		{
			static double lastErrorZ;
			static bool firstRun = true;
			if (YZError[0] > VY_MAXLimt)
			{
				YZError[0] = VY_MAXLimt;
			}
			else if (YZError[0] < (-VY_MAXLimt))
			{
				YZError[0] = (-VY_MAXLimt);
			}

			//if (YZError[1] > VZ_MAXLimt)
			//{
			//	YZError[1] = VZ_MAXLimt;
			//}
			//else if (YZError[1] < (-VZ_MAXLimt))
			//{
			//	YZError[1] = (-VZ_MAXLimt);
			//}
			//qDebug() << "YZError[0]" << YZError[0];
			//tmp= PID_Chi->PID_realize(YZError[0]);
			//qDebug() << "tmp" << tmp;
			//tmp += baseChi;
			//qDebug() << "tmp2" << tmp;
			// 20220704 ����PID����
			//hc += (YZError[1]*step_second);
			hc += (PID_H->PID_realize(YZError[1]) * step_second);
			//double tmpChi = PID_Chi->PID_realize(YZError[0]) + baseChi_deg;
			//qDebug() << tmpChi;
			clm_control_task->Input_VKH(follow_V, (PID_Chi->PID_realize(YZError[0]) + baseChi_deg) /180*PI, hc);
			//clm_control_task->Input_XYZ_V(follow_V, tmp / 180 * PI, 300,1);
			clm_control_task->Update();
			

		}
		break;

	default :

		break;
	}

	//double lla_ref[3] = { data_origin_B0,data_origin_L0 ,0 };
	double cur_enu[3] = { clm_control_task->m_fst.m_dX,clm_control_task->m_fst.m_dY,clm_control_task->m_fst.m_dZ };
	double cur_lla[3];
	//qDebug() << "enuX:" << cur_enu[0] << "enuY:" << cur_enu[1] << "enuZ:" << cur_enu[2];
	//qDebug() << "lla_ref" << lla_ref[0] << lla_ref[1] << lla_ref[2];
	wgs_enuConversion->enu2lla(cur_lla, cur_enu, lla_ref);
	B = cur_lla[0];
	L = cur_lla[1];
	H = cur_lla[2];



	//static int cnt = 0;
	//if (cnt>=40)
	//{
	//	qDebug() << "dZ:" << clm_control_task->m_fst.m_dZ;
	//	qDebug() << "H" << H;
	//	cnt = 0;
	//}
	//cnt++;

}



double* taskManagement::getNextTrackNode(double X_last, double Y_last, double Z_last, double V, double X_next, double Y_next, double Z_next, long long int i)
{
	static double r[3];
	double L = sqrt(pow(X_next - X_last, 2) + pow(Y_next - Y_last, 2) + pow(Z_next - Z_last, 2));
	qDebug() << X_last << ";" << Y_last << ";" << Z_last << ";" << X_next << ";" << Y_next << ";" << Z_next;
	qDebug() << "L:" << L;
	r[0] = X_last + (X_next - X_last) / L*V / 1000 * data_time*i;
	r[1] = Y_last + (Y_next - Y_last) / L*V / 1000 * data_time*i;
	r[2] = Z_last + (Z_next - Z_last) / L*V / 1000 * data_time*i;
	return r;

}


