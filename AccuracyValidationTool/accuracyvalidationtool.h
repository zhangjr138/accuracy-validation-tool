#pragma once

#include "ui_accuracyvalidationtool.h"
#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <qpixmap.h>
#include <qthread.h>
#include <qdatetime.h>
#include <qtextstream.h>
#include <qdebug.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <string>
#include <vector>

using namespace std;
using namespace cv;

class AccuracyValidationTool : public QMainWindow
{
	Q_OBJECT

public:
	AccuracyValidationTool(QWidget *parent = Q_NULLPTR);
	~AccuracyValidationTool();

protected:
	void keyPressEvent(QKeyEvent *event); // �������¼�
	bool eventFilter(QObject *obj, QEvent *event); // �¼�������
	void closeEvent(QCloseEvent *event); // ���ڹرպ���

private:
	void videoForward(); // �����Ҽ�ǰ��
	void videoBackward(); // �����������
	void videoPlay(); // ��Ƶ�Ĳ��ź���ͣ
	void resetUi(); // ��Ui��������
	void setFocusOnVideo(); // ���������ͼƬ��ʾ������
	void getQFileName(QString q_filePath); // �����׺�滻��.csv���ļ���
	void videoOpened(); // ��Ƶ�򿪺���еĲ���
	void resetHSlider(int frameNumTotal); // ������Ƶ������
	void setHSlider(int currentFrame); // ���ý�����
	void countInPlus(); // �����Ƶlabel����Ĳۺ���
	void countOutPlus(); // �һ���Ƶlabel����Ĳۺ���
	void updateData(); // ��������¼֡��������������С�͵�ǰ�ε���ʾ
	QImage Mat2QImage(Mat cvImg); // MatתQImage
	bool showOneFrame(); // ��һ֡�ŵ�QLabel��

private slots:
	void slot_openAVideo(); // �������Ƶ��ť�Ĳۺ���
private slots:
	void slot_setFrameRate(); // �������֡�ʰ�ť�Ĳۺ���
private slots:
	void slot_setRecordInterval(); // �������ÿ�μ�¼ʱ����ť�Ĳۺ���
private slots:
	void slot_setStartTime(); // ������ÿ�ʼ��¼ʱ�䰴ť�Ĳۺ���
private slots:
	void slot_HSliderMoved(int value); // ��Ƶ���������϶��Ĳۺ���
private slots:
	void slot_HSliderReleased(); // ��Ƶ�������������ͷŵĲۺ���
private slots:
	void slot_videoSpeed(int index); // ��Ƶ�����ٶȵĲۺ���
private slots:
	void slot_countInMinus(); // �����������-1��ť�Ĳۺ���
private slots:
	void slot_countOutMinus(); // �����ȥ����-1��ť�Ĳۺ���
private slots:
	void slot_exportFile(); // ����������ݰ�ť�Ĳۺ���
private slots:
	void slot_closeVideo(); // ����ر���Ƶ��ť�Ĳۺ���

private:
	Ui::AccuracyValidationToolClass ui;
	VideoCapture capture; // ��Ƶ��׽
	int frameNumTotal = 0; // ��Ƶ����֡��
	int fps = 0; // ��Ƶ��֡��
	double frameInterval = 0; // ��Ƶ�����ٶ�
	int currentFrame = 0; // ��Ƶ�ĵ�ǰ֡
	bool isVideoOpened = true; // �Ƿ�����Ƶ����
	bool isVideoOn = false; // ��Ƶ�Ƿ�Ĳ��ź���ͣ
	bool isVideoStopped = false; // ���ڽ�������ʱ�ж���Ƶ�Ƿ�ͣ����
	bool isVideoUncomplete = false; // ��Ƶ�Ƿ�����������ȡ������֡��
	bool isSetDone = false; // �Ƿ��ʼ������ɣ����Խ��м���
	bool isBeenExport = false; // ��ǰ��Ƶ�Ƿ񵼳����ļ�

	// �͵�����ص�����
	QString q_fileName; // �����ļ����ļ���
	QDateTime startTime; // ���õĿ�ʼ��¼ʱ��
	int frameRate = 0; // ���õ�֡��
	int recordInterval = 0; // ���õ�ÿ�μ�¼ʱ��
	int recordFrameNum = 0; // ֡�� * ÿ�μ�¼ʱ��
	int maxFrameNum = 0; // ����¼�����֡��
	vector<int> countIn; // ��¼���������
	vector<int> countOut; // ��¼��ȥ������
};
