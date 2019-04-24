#pragma once

#include "ui_accuracyvalidationtool.h"
#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <qpixmap.h>
#include <qdebug.h>
#include <qthread.h>
#include <qdatetime.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "CvvImage.h"

#include <string>

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
	void videoOpened(); // ��Ƶ�򿪺���еĲ���
	void resetHSlider(int frameNumTotal); // ������Ƶ������
	void setHSlider(int currentFrame); // ���ý�����
	QImage Mat2QImage(Mat cvImg); // MatתQImage
	bool showOneFrame(); // ��һ֡�ŵ�QLabel��

private slots:
	void slot_openAVideo(); // ��һ����Ƶ�Ĳۺ���
private slots:
	void slot_setFrameRate(); // ����֡�ʵĲۺ���
private slots:
	void slot_setReportInterval(); // ����ÿ�μ�¼ʱ���Ĳۺ���
private slots:
	void slot_setStartTime(); // ���ÿ�ʼ��¼ʱ��
private slots:
	void slot_HSliderMoved(int value); // ��Ƶ���������϶��Ĳۺ���
private slots:
	void slot_HSliderReleased(); // ��Ƶ�������������ͷŵĲۺ���
private slots:
	void slot_videoSpeed(int index); // ��Ƶ�����ٶȵĲۺ���

private:
	Ui::AccuracyValidationToolClass ui;
	VideoCapture vCapture; // ��Ƶ��׽
	int frameNumTotal = 0; // ��Ƶ����֡��
	int fps = 0; // ��Ƶ��֡��
	double frameInterval = 0; // ��Ƶ�����ٶ�
	int currentFrame = 0; // ��Ƶ�ĵ�ǰ֡
	bool isVideoOpened = true; // �Ƿ�����Ƶ����
	bool isVideoOn = false; // ��Ƶ�Ƿ�Ĳ��ź���ͣ
	bool isVideoStopped = false; // ���ڽ�������ʱ�ж���Ƶ�Ƿ�ͣ����
	bool isKeyRightPressed = false; // �����Ҽ��Ƿ񱻰���
	bool isKeyLeftPressed = false; // ��������Ƿ񱻰���

	// �͵�����ص�����
	int frameRate = 0; // ���õ�֡��
	int reportInterval = 0; // ���õ�ÿ�μ�¼ʱ��
	int reportFrameNum = 0; // ֡�� * ÿ�μ�¼ʱ��
	QDateTime startTime; // ���õĿ�ʼ��¼ʱ��
	int maxFrameNum = 0; // ����¼�����֡��
};
