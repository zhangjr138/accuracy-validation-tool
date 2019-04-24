#include "accuracyvalidationtool.h"

AccuracyValidationTool::AccuracyValidationTool(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// 设置焦点策略
	this->setFocusPolicy(Qt::ClickFocus);

	// 先重置Ui
	resetUi();

	qDebug() << ui.dateTimeEdit_startTime->dateTime() << endl;
	qDebug() << ui.dateTimeEdit_startTime->dateTime().addSecs(100) << endl;
	qDebug() << ui.dateTimeEdit_startTime->dateTime().addSecs(100).toString("yyyy-MM-dd HH:mm:ss") << endl;
}


AccuracyValidationTool::~AccuracyValidationTool()
{
	// 等待视频播放跳出循环
	while (isVideoOn)
	{
		QThread::msleep(10);
		QCoreApplication::processEvents();
	}
}


// 检测键盘按下事件
void AccuracyValidationTool::keyPressEvent(QKeyEvent *event)
{
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


// 事件过滤器
bool AccuracyValidationTool::eventFilter(QObject *obj, QEvent *event)
{ // 特别注意控件处理的最终返回值
  // return true: 告诉Qt已经处理的这个事件
  // return false: Qt会把这个事件传递给它的父窗口部件来处理

	return QMainWindow::eventFilter(obj, event);
}


// 窗口关闭函数
void AccuracyValidationTool::closeEvent(QCloseEvent *event)
{ // 继承的函数，为点击窗口关闭按键时所执行的函数
  // 关闭时如果视频正在播放则先将视频停下，避免死循环
  
	QMainWindow::closeEvent(event);
	if (isVideoOn)
	{
		isVideoOn = false;
	}
}


// 键盘右键前进
void AccuracyValidationTool::videoForward()
{
	if (isVideoOpened && currentFrame < frameNumTotal && showOneFrame())
	{
		currentFrame++;
	}
}


// 键盘左键后退
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


// 视频的播放和暂停
void AccuracyValidationTool::videoPlay()
{
	isVideoStopped = false;
	while (isVideoOpened && isVideoOn && currentFrame < frameNumTotal && showOneFrame())
	{
		currentFrame++;
		waitKey(frameInterval);
		QCoreApplication::processEvents();
	}
	isVideoOn = false;
	isVideoStopped = true;
}


// 对Ui进行重置
void AccuracyValidationTool::resetUi()
{ // 将控件设置为不可用，除打开视频控件外

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


// 视频打开后进行的操作
void AccuracyValidationTool::videoOpened()
{ // 获取视频的一些相关信息并将第一张图片放到label上
  // 将帧率的设置变为可用

	// 获取视频信息并显示第一张图片
	isVideoOpened = true;
	frameNumTotal = vCapture.get(CV_CAP_PROP_FRAME_COUNT);
	fps = vCapture.get(CV_CAP_PROP_FPS);
	frameRate = fps;
	resetHSlider(frameNumTotal);
	showOneFrame();
	currentFrame++;

	// ui相关设置
	ui.pushButton_open->setDisabled(true);
	ui.pushButton_frameRate->setEnabled(true);
	ui.spinBox_frameRate->setEnabled(true);
	ui.spinBox_frameRate->setValue(frameRate);
}


// 重置视频进度条
void AccuracyValidationTool::resetHSlider(int frameNumTotal)
{
	ui.horizontalSlider->setMinimum(0);
	ui.horizontalSlider->setMaximum(frameNumTotal - 1);
	ui.horizontalSlider->setSingleStep(1);
	ui.horizontalSlider->setValue(0);
}


// 设置视频进度条
void AccuracyValidationTool::setHSlider(int currentFrame)
{ // 范围为0到视频总帧率之间，步进为1，每个值和图片当前帧数相对应

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


// Mat转QImage
QImage AccuracyValidationTool::Mat2QImage(Mat cvImg)
{
	QImage qImg;
	if (cvImg.channels() == 3)
	{ // 三通道彩色图像
		cvtColor(cvImg, cvImg, CV_BGR2RGB);
		qImg = QImage((const unsigned char*)(cvImg.data), cvImg.cols, cvImg.rows, cvImg.cols*cvImg.channels(), QImage::Format_RGB888);
	}
	else if (cvImg.channels() == 1)
	{ // 单通道（灰度图）
		qImg = QImage((const unsigned char*)(cvImg.data), cvImg.cols, cvImg.rows, cvImg.cols*cvImg.channels(), QImage::Format_Indexed8);

		QVector<QRgb> colorTable;
		for (int k = 0; k < 256; ++k)
		{
			colorTable.push_back(qRgb(k, k, k));
		}

		// 把qImg的颜色按像素点的颜色给设置
		qImg.setColorTable(colorTable);
	}
	else
	{
		qImg = QImage((const unsigned char*)(cvImg.data), cvImg.cols, cvImg.rows, cvImg.cols*cvImg.channels(), QImage::Format_RGB888);
	}

	return qImg;
}


// 将一帧放到QLabel上
bool AccuracyValidationTool::showOneFrame()
{
	Mat frame;
	if (vCapture.read(frame))
	{
		qDebug() << currentFrame;
		QImage qImg = Mat2QImage(frame);
		QPixmap pixmap = QPixmap::fromImage(qImg);
		ui.label_video->setPixmap(pixmap);

		// 每放一张图片，进度条相应改变
		setHSlider(currentFrame);
		return true;
	}
	return false;
}


// 打开一个视频的槽函数
void AccuracyValidationTool::slot_openAVideo()
{
	QString q_fileName = QFileDialog::getOpenFileName(this, "Open Document", QDir::currentPath(), "All files(*.*)");
	if (!q_fileName.isNull())
	{ // 用户选择了文件
	    // 打开视频文件
		string fileName = q_fileName.toStdString();
		vCapture.open(fileName);

		if (!vCapture.isOpened())
		{ // 视频文件打开失败
			QMessageBox::critical(this, "critical", "Failed to open the video!", QMessageBox::Ok);
			return;
		}

		// 视频打开后进行的操作，将设置控件逐渐变为可用
		videoOpened();
	}
	else 
	{ // 用户取消选择
		// 提示先打开视频
		QMessageBox::warning(this, "warning", "Please open a video first!", QMessageBox::Ok);
	}
	//int a = ui.dateTimeEdit_startTime->time().hour();
	//qDebug() << a << endl;
}


// 设置帧率的槽函数
void AccuracyValidationTool::slot_setFrameRate()
{ // 设置帧率后将相关设置控件变为不可用，将设置每次记录时长相关控件设为可用

	frameRate = ui.spinBox_frameRate->value();
	frameInterval = 1000.0 / double(frameRate);

	ui.spinBox_frameRate->setDisabled(true);
	ui.pushButton_frameRate->setDisabled(true);
	ui.spinBox_reportInterval->setEnabled(true);
	ui.pushButton_reportInterval->setEnabled(true);
}


// 设置每次记录时长的槽函数
void AccuracyValidationTool::slot_setReportInterval()
{ // 设置每次记录时长后将相关设置控件变为不可用，将设置开始时间相关控件设为可用

	reportInterval = ui.spinBox_reportInterval->value();
	reportFrameNum = frameRate * reportInterval;

	ui.spinBox_reportInterval->setDisabled(true);
	ui.pushButton_reportInterval->setDisabled(true);
	ui.dateTimeEdit_startTime->setEnabled(true);
	ui.pushButton_startTime->setEnabled(true);
}


// 设置开始记录时间
void AccuracyValidationTool::slot_setStartTime()
{ // 设置开始记录时间后将相关设置控件变为不可用，将视频操作相关控件变为可用

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


// 视频进度条被拖动的槽函数
void AccuracyValidationTool::slot_HSliderMoved(int value)
{
	currentFrame = value;
	vCapture.set(CV_CAP_PROP_POS_FRAMES, currentFrame);
	showOneFrame();
	currentFrame++;
}


// 视频进度条滑块点击释放的槽函数
void AccuracyValidationTool::slot_HSliderReleased() 
{ // 释放后将焦点设在label上，避免键盘按左右键时焦点在进度条上

	ui.label_video->setFocus();
}


// 视频播放速度的槽函数
void AccuracyValidationTool::slot_videoSpeed(int index)
{
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
