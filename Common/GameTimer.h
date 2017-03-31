#ifndef GAMETIMER_H
#define GAMETIMER_H

class GameTimer
{
public:
	GameTimer();
	float TotalTime() const;//���ض�ʱ���Ӽ�ʱ��ʼ�����ڵ���ʱ�䣬��������ͣʱ��
	float DeltaTime() const;//���ر��μ�ʱ���ϴμ�ʱ֮���ʱ���

	void Reset();//����
	void Start();//��ͣ��ָ���ʱ
	void Stop();//��ͣ
	void Tick();//��ʱһ�Σ�ÿһ֡����

private:
	double m_secondsPerCount;//ϵͳ��أ�ϵͳ���μ���֮���ʱ���Ƕ�ʱ����ʱ��ת��Ϊs�Ļ�׼
	double m_deltaTime;//�����ϴμ�ʱ��ʱ���

	__int64 m_baseTime;//��ʱ����ʼ������ʱ���
	__int64 m_pausedTime;//��ͣ����ʱ��
	__int64 m_stopTime;//��ͣ�Ŀ�ʼʱ��
	__int64 m_prevTime;//�ϴμ�ʱ��ʱ���
	__int64 m_currTime;//���μ�ʱ��ʱ���

	bool m_isStopped;//�Ƿ���ͣ
};

#endif	//GAMETIMER_H

