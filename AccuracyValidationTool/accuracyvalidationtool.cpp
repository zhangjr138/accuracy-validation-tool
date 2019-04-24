#include "accuracyvalidationtool.h"

AccuracyValidationTool::AccuracyValidationTool(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// ���ý������
	this->setFocusPolicy(Qt::ClickFocus);

	// ������Ui
	resetUi();

	qDebug() << ui.dateTimeEdit_startTime->dateTime() << endl;
	qDebug() << ui.dateTimeEdit_startTime->dateTime().addSecs(100) << endl;
	qDebug() << ui.dateTimeEdit_startTime->dateTime().addSecs(100).toString("yyyy-MM-dd HH:mm:ss") << endl;
}


AccuracyValidationTool::~AccuracyValidationTool()
{ // �ڳ������ǰ�ͷ�vCapture
	
}


// �����̰����¼�
void AccuracyValidationTool::keyPressEvent(QKeyEvent *event)
{ // �ո������/ֹͣ��Ƶ
  // ���Ҽ�������һ֡����������ǰ�����ţ�
  // �����������һ֡�������������˲��ţ�

	switch (event->key())
	{
	case Qt::Key_Space:
		isVideoOn = !isVideoOn;
		videoPlay();
		break;
	case Qt::Key_Right:
		videoForward();
		break;
	case Qt::Key_Left:
		videoBackward();
		break;
	default:
		break;
	}
}


// �¼�������
bool AccuracyValidationTool::eventFilter(QObject *obj, QEvent *event)
{ // �����Ƶlabel����countIn+1���һ�countOut+1
  // �ر�ע��ؼ���������շ���ֵ
  // return true: ����Qt�Ѿ����������¼�
  // return false: Qt�������¼����ݸ����ĸ����ڲ���������

	if (obj == ui.label_video)
	{
		if (event->type() == QEvent::MouseButtonRelease)
		{
			QMouseEvent *mevent = (QMouseEvent*)(event);

			// ���countIn+1
			if (mevent->button() == Qt::LeftButton)
			{
				countInPlus();
			}

			// �һ�countOut+1
			else if (mevent->button() == Qt::RightButton)
			{
				countOutPlus();
			}

			return false;
		}
	}

	return QMainWindow::eventFilter(obj, event);
}


// ���ڹرպ���
void AccuracyValidationTool::closeEvent(QCloseEvent *event)
{ // �̳еĺ�����Ϊ������ڹرհ���ʱ��ִ�еĺ���
  // �ر�ʱ�����Ƶ���ڲ������Ƚ���Ƶͣ�£�������ѭ��
  
	QMainWindow::closeEvent(event);
	if (isVideoOn)
	{
		isVideoOn = false;
	}
}


// �����Ҽ�ǰ��
void AccuracyValidationTool::videoForward()
{
	if (isVideoOpened && currentFrame < frameNumTotal && showOneFrame())
	{
		currentFrame++;
	}
}


// �����������
void AccuracyValidationTool::videoBackward()
{
	if (isVideoOpened && currentFrame > 1)
	{
		currentFrame -= 2;
		vCapture.set(CV_CAP_PROP_POS_FRAMES, currentFrame);
		showOneFrame();
		currentFrame++;
	}
}


// ��Ƶ�Ĳ��ź���ͣ
void AccuracyValidationTool::videoPlay()
{ // ֻҪ�ܶ���ͼƬ��һֱִ�в���ѭ������������ѭ��������֡��Ϊ���õ�֡��
  // ���ŵ�ʱ��Ҳһֱ�ڼ��ϵͳ�źţ�һ�����ű�־isVideoOn����false��ֹͣ������ѭ��

	while (isVideoOpened && isVideoOn && currentFrame < frameNumTotal && showOneFrame())
	{
		currentFrame++;
		waitKey(frameInterval);
		QCoreApplication::processEvents();
	}
	isVideoOn = false;
}


// ��Ui��������
void AccuracyValidationTool::resetUi()
{ // ���ؼ�����Ϊ�����ã�������Ƶ�ؼ���

	ui.pushButton_output->setDisabled(true);
	ui.pushButton_close->setDisabled(true);
	ui.horizontalSlider->setDisabled(true);
	ui.comboBox_speed->setDisabled(true);
	ui.spinBox_frameRate->setDisabled(true);
	ui.pushButton_frameRate->setDisabled(true);
	ui.spinBox_reportInterval->setDisabled(true);
	ui.pushButton_reportInterval->setDisabled(true);
	ui.dateTimeEdit_startTime->setDisabled(true);
	ui.pushButton_startTime->setDisabled(true);
	ui.pushButton_inMinusOne->setDisabled(true);
	ui.pushButton_outMinusOne->setDisabled(true);
}


// ��Ƶ�򿪺���еĲ���
void AccuracyValidationTool::videoOpened()
{ // ��ȡ��Ƶ��һЩ�����Ϣ������һ��ͼƬ�ŵ�label��
  // ��֡�ʵ����ñ�Ϊ����

	// ��ȡ��Ƶ��Ϣ����ʾ��һ��ͼƬ
	isVideoOpened = true;
	frameNumTotal = vCapture.get(CV_CAP_PROP_FRAME_COUNT);
	fps = vCapture.get(CV_CAP_PROP_FPS);
	frameRate = fps;
	resetHSlider(frameNumTotal);
	showOneFrame();
	currentFrame++;

	// ui�������
	ui.pushButton_open->setDisabled(true);
	ui.pushButton_frameRate->setEnabled(true);
	ui.spinBox_frameRate->setEnabled(true);
	ui.spinBox_frameRate->setValue(frameRate);
}


// ������Ƶ������
void AccuracyValidationTool::resetHSlider(int frameNumTotal)
{ // ��������ΧΪ[0, frameNumTotal]������ֵΪ1����ʼֵΪ0

	ui.horizontalSlider->setMinimum(0);
	ui.horizontalSlider->setMaximum(frameNumTotal - 1);
	ui.horizontalSlider->setSingleStep(1);
	ui.horizontalSlider->setValue(0);
}


// ������Ƶ������
void AccuracyValidationTool::setHSlider(int currentFrame)
{ // ��ΧΪ0����Ƶ��֡��֮�䣬����Ϊ1��ÿ��ֵ��ͼƬ��ǰ֡�����Ӧ

	if (currentFrame > ui.horizontalSlider->maximum())
	{
		currentFrame = ui.horizontalSlider->maximum();
	}
	else if (currentFrame < ui.horizontalSlider->minimum())
	{
		currentFrame = ui.horizontalSlider->minimum();
	}

	ui.horizontalSlider->setValue(currentFrame);
}


// �����Ƶlabel����Ĳۺ���
void AccuracyValidationTool::countInPlus()
{ // ��ǰ��¼ʱ��ν�������+1
  // ���+1ǰ����Ϊ0��-1��ť�ָ�����

}


// �һ���Ƶlabel����Ĳۺ���
void AccuracyValidationTool::countOutPlus()
{ // ��ǰ��¼ʱ��γ�ȥ����+1
  // ���+1ǰ����Ϊ0��-1��ť�ָ�����

}


// MatתQImage
QImage AccuracyValidationTool::Mat2QImage(Mat cvImg)
{ // ��Բ�ͬ��ʽ��ͼƬ��Mat��ʽ��ͼƬת��QImage��ʽ���Ա�����ʾ��QLabel��

	QImage qImg;
	if (cvImg.channels() == 3)
	{ // ��ͨ����ɫͼ��
		cvtColor(cvImg, cvImg, CV_BGR2RGB);
		qImg = QImage((const unsigned char*)(cvImg.data), cvImg.cols, cvImg.rows, cvImg.cols*cvImg.channels(), QImage::Format_RGB888);
	}
	else if (cvImg.channels() == 1)
	{ // ��ͨ�����Ҷ�ͼ��
		qImg = QImage((const unsigned char*)(cvImg.data), cvImg.cols, cvImg.rows, cvImg.cols*cvImg.channels(), QImage::Format_Indexed8);

		QVector<QRgb> colorTable;
		for (int k = 0; k < 256; ++k)
		{
			colorTable.push_back(qRgb(k, k, k));
		}

		// ��qImg����ɫ�����ص����ɫ������
		qImg.setColorTable(colorTable);
	}
	else
	{
		qImg = QImage((const unsigned char*)(cvImg.data), cvImg.cols, cvImg.rows, cvImg.cols*cvImg.channels(), QImage::Format_RGB888);
	}

	return qImg;
}


// ��һ֡�ŵ�QLabel��
bool AccuracyValidationTool::showOneFrame()
{ // ��һ��ͼƬ��ʾ��QLabel�ϣ�������õ�ͼƬ�򷵻�true�����򷵻�false

	Mat frame;
	if (vCapture.read(frame))
	{
		QImage qImg = Mat2QImage(frame);
		QPixmap pixmap = QPixmap::fromImage(qImg);
		ui.label_video->setPixmap(pixmap);

		// ÿ��һ��ͼƬ����������Ӧ�ı�
		setHSlider(currentFrame);
		return true;
	}
	return false;
}


// ��һ����Ƶ�Ĳۺ���
void AccuracyValidationTool::slot_openAVideo()
{ // �򿪡����ļ������ڣ�ѡ����Ƶ
  // û��ѡ����Ƶ����ʾ�ȴ���Ƶ
  // ��Ƶ�򿪲��ɹ��򱨴�

	QString q_fileName = QFileDialog::getOpenFileName(this, "Open Document", QDir::currentPath(), "All files(*.*)");
	if (!q_fileName.isNull())
	{ // �û�ѡ�����ļ�
	    // ����Ƶ�ļ�
		string fileName = q_fileName.toStdString();
		vCapture.open(fileName);

		if (!vCapture.isOpened())
		{ // ��Ƶ�ļ���ʧ��
			QMessageBox::critical(this, "critical", "Failed to open the video!", QMessageBox::Ok);
			return;
		}

		// ��Ƶ�򿪺���еĲ����������ÿؼ��𽥱�Ϊ����
		videoOpened();
	}
	else 
	{ // �û�ȡ��ѡ��
		// ��ʾ�ȴ���Ƶ
		QMessageBox::warning(this, "warning", "Please open a video first!", QMessageBox::Ok);
	}
	//int a = ui.dateTimeEdit_startTime->time().hour();
	//qDebug() << a << endl;
}


// ����֡�ʵĲۺ���
void AccuracyValidationTool::slot_setFrameRate()
{ // ����֡�ʺ�������ÿؼ���Ϊ�����ã�������ÿ�μ�¼ʱ����ؿؼ���Ϊ����

	frameRate = ui.spinBox_frameRate->value();
	frameInterval = 1000.0 / double(frameRate);

	ui.spinBox_frameRate->setDisabled(true);
	ui.pushButton_frameRate->setDisabled(true);
	ui.spinBox_reportInterval->setEnabled(true);
	ui.pushButton_reportInterval->setEnabled(true);
}


// ����ÿ�μ�¼ʱ���Ĳۺ���
void AccuracyValidationTool::slot_setReportInterval()
{ // ����ÿ�μ�¼ʱ����������ÿؼ���Ϊ�����ã������ÿ�ʼʱ����ؿؼ���Ϊ����

	reportInterval = ui.spinBox_reportInterval->value();
	reportFrameNum = frameRate * reportInterval;

	ui.spinBox_reportInterval->setDisabled(true);
	ui.pushButton_reportInterval->setDisabled(true);
	ui.dateTimeEdit_startTime->setEnabled(true);
	ui.pushButton_startTime->setEnabled(true);
}


// ���ÿ�ʼ��¼ʱ��
void AccuracyValidationTool::slot_setStartTime()
{ // ���ÿ�ʼ��¼ʱ���������ÿؼ���Ϊ�����ã�����Ƶ������ؿؼ���Ϊ����

	startTime = ui.dateTimeEdit_startTime->dateTime();

	ui.dateTimeEdit_startTime->setDisabled(true);
	ui.pushButton_startTime->setDisabled(true);
	ui.horizontalSlider->setEnabled(true);
	ui.comboBox_speed->setEnabled(true);
	ui.pushButton_inMinusOne->setEnabled(true);
	ui.pushButton_outMinusOne->setEnabled(true);
	ui.pushButton_output->setEnabled(true);
	ui.pushButton_close->setEnabled(true);
}


// ��Ƶ���������϶��Ĳۺ���
void AccuracyValidationTool::slot_HSliderMoved(int value)
{ // ��Ƶ���������϶�ʱ���ĵ�ǰ֡��ֵ��������ӦͼƬ��ʾ����

	currentFrame = value;
	vCapture.set(CV_CAP_PROP_POS_FRAMES, currentFrame);
	showOneFrame();
	currentFrame++;
}


// ��Ƶ�������������ͷŵĲۺ���
void AccuracyValidationTool::slot_HSliderReleased() 
{ // �ͷź󽫽�������label�ϣ�������̰����Ҽ�ʱ������ͣ���ڽ�������

	ui.label_video->setFocus();
}


// ��Ƶ�����ٶȵĲۺ���
void AccuracyValidationTool::slot_videoSpeed(int index)
{ // x0.5��x1.0��x2.0��x4.0���ֲ����ٶȣ��趨�������������ͼƬ��ʾ�ļ��

	double speedRate = 1;
	switch (index)
	{
	case 0:
		speedRate = 0.5;
		break;
	case 1:
		speedRate = 1;
		break;
	case 2:
		speedRate = 2;
		break;
	case 3:
		speedRate = 4;
		break;
	default:
		break;
	}
	frameInterval = (1.0 / speedRate) * (1000.0 / double(frameRate));
}


// �����������-1��ť�Ĳۺ���
void AccuracyValidationTool::slot_countInMinus()
{ // ��ǰ��¼ʱ��ν�������-1
  // �����������0��-1��ť��Ϊ������

}


// �����ȥ����-1��ť�Ĳۺ���
void AccuracyValidationTool::slot_countOutMinus()
{ // ��ǰ��¼ʱ��γ�ȥ����-1
  // �����������0��-1��ť��Ϊ������

}


// ����������ݰ�ť�Ĳۺ���
void AccuracyValidationTool::slot_outputData()
{ // ��ֹ������¼�����֡��ֵ����¼���ݵ���Ϊcsv�ļ�

}


// ����ر���Ƶ��ť�Ĳۺ���
void AccuracyValidationTool::slot_closeVideo()
{ // �ر���Ƶ������Ui���棬��Ϊ�մ򿪳���ʱ��״̬

}
