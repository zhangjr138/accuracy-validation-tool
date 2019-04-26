#include "accuracyvalidationtool.h"

AccuracyValidationTool::AccuracyValidationTool(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// 设置焦点策略
	this->setFocusPolicy(Qt::ClickFocus);

	// 为显示图片的label安装事件过滤器
	ui.label_video->installEventFilter(this);

	// 先重置Ui
	resetUi();
}


AccuracyValidationTool::~AccuracyValidationTool()
{ // 在程序结束前释放capture

	if (capture.isOpened())
	{
		capture.release();
	}
}


// 检测键盘按下事件
void AccuracyValidationTool::keyPressEvent(QKeyEvent *event)
{ // 空格键播放/停止视频
  // 向右键播放下一帧（长按连续前进播放）
  // 向左键播放上一帧（长按连续后退播放）

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
{ // 左击视频label区域countIn+1，右击countOut+1
  // 特别注意控件处理的最终返回值
  // return true: 告诉Qt已经处理的这个事件
  // return false: Qt会把这个事件传递给它的父窗口部件来处理

	if (obj == ui.label_video)
	{
		if (event->type() == QEvent::MouseButtonRelease)
		{
			QMouseEvent *mevent = (QMouseEvent*)(event);

			// 左击countIn+1
			if (mevent->button() == Qt::LeftButton)
			{
				countInPlus();
			}

			// 右击countOut+1
			else if (mevent->button() == Qt::RightButton)
			{
				countOutPlus();
			}

			return false;
		}
	}

	return QMainWindow::eventFilter(obj, event);
}


// 窗口关闭函数
void AccuracyValidationTool::closeEvent(QCloseEvent *event)
{ // 继承的函数，为点击窗口关闭按键时所执行的函数
  // 关闭时如果视频正在播放则先将视频停下，避免死循环

	if (0 == QMessageBox::question(this, "Confirm Exit", "Are you sure you want to exit AccuracyValidationTool?",
		"Exit", "Cancel", 0, 1, 1))
	{
		QMainWindow::closeEvent(event);
		if (isVideoOn)
		{
			isVideoOn = false;
		}
		event->accept();
	}
	else
	{
		event->ignore();
	}
}


// 键盘右键前进
void AccuracyValidationTool::videoForward()
{
	if (isVideoOpened && currentFrame < frameNumTotal && showOneFrame())
	{
		currentFrame++;
		updateData();
	}
}


// 键盘左键后退
void AccuracyValidationTool::videoBackward()
{
	if (isVideoOpened && currentFrame > 1)
	{
		currentFrame -= 2;
		capture.set(CV_CAP_PROP_POS_FRAMES, currentFrame);
		showOneFrame();
		currentFrame++;
		updateData();
	}
}


// 视频的播放和暂停
void AccuracyValidationTool::videoPlay()
{ // 只要能读到图片则一直执行播放循环，否则跳出循环，播放帧率为设置的帧率
  // 播放的时候也一直在检测系统信号，一旦播放标志isVideoOn变以false则停止，跳出循环

	while (isVideoOpened && isVideoOn && currentFrame < frameNumTotal && showOneFrame())
	{
		currentFrame++;
		updateData();
		waitKey(frameInterval);
		QCoreApplication::processEvents();
	}
	isVideoOn = false;
}


// 对Ui进行重置
void AccuracyValidationTool::resetUi()
{ // 将控件设置为不可用，除打开视频控件外
  // 将进度条、计数等清零，清除label上的图片残留

	ui.pushButton_open->setEnabled(true);
	ui.pushButton_export->setDisabled(true);
	ui.pushButton_close->setDisabled(true);
	ui.horizontalSlider->setValue(0);
	ui.horizontalSlider->setDisabled(true);
	ui.comboBox_speed->setCurrentIndex(1);
	ui.comboBox_speed->setDisabled(true);
	ui.spinBox_frameRate->setDisabled(true);
	ui.pushButton_frameRate->setDisabled(true);
	ui.spinBox_recordInterval->setDisabled(true);
	ui.pushButton_recordInterval->setDisabled(true);
	ui.dateTimeEdit_startTime->setDisabled(true);
	ui.pushButton_startTime->setDisabled(true);
	ui.pushButton_inMinusOne->setDisabled(true);
	ui.pushButton_outMinusOne->setDisabled(true);
	ui.spinBox_countIn->setValue(0);
	ui.spinBox_countOut->setValue(0);
	ui.label_video->clear();
	setFocusOnVideo();
}


// 将焦点放在图片显示区域上
void AccuracyValidationTool::setFocusOnVideo()
{ // 将焦点放在label上，以避免在点击按钮或拖动进度条之后检测不到键盘按键

	ui.label_video->setFocus();
}


// 保存后缀替换成.csv的文件名
void AccuracyValidationTool::getQFileName(QString q_filePath)
{ // 根据路径获得带后缀文件名和后缀名
  // 将后缀名前加.后替换成.csv

	QFileInfo q_fileInfo = QFileInfo(q_filePath);
	QString q_fileSuffix, q_dotFileSuffix;
	q_fileName = q_fileInfo.fileName();
	q_fileSuffix = q_fileInfo.suffix();
	q_dotFileSuffix = "." + q_fileSuffix;
	q_fileName.replace(q_dotFileSuffix, ".csv");
}


// 视频打开后进行的操作
void AccuracyValidationTool::videoOpened()
{ // 获取视频的一些相关信息并将第一张图片放到label上
  // 将帧率的设置变为可用

	// 获取视频信息并显示第一张图片
	isVideoOpened = true;
	frameNumTotal = capture.get(CV_CAP_PROP_FRAME_COUNT);
	fps = capture.get(CV_CAP_PROP_FPS);
	frameRate = fps;
	resetHSlider(frameNumTotal);
	showOneFrame();
	currentFrame++;
	maxFrameNum = currentFrame;

	// 将开始记录人数记为0
	countIn.push_back(0);
	countOut.push_back(0);

	// ui相关设置
	ui.pushButton_open->setDisabled(true);
	ui.pushButton_frameRate->setEnabled(true);
	ui.spinBox_frameRate->setEnabled(true);
	ui.spinBox_frameRate->setValue(frameRate);
}


// 重置视频进度条
void AccuracyValidationTool::resetHSlider(int frameNumTotal)
{ // 进度条范围为[0, frameNumTotal]，步进值为1，初始值为0

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


// 左击视频label区域的槽函数
void AccuracyValidationTool::countInPlus()
{ // 当前记录时间段进入人数+1
  // 如果+1前人数为0则-1按钮恢复可用

	// 如果没有打开视频或未完成初始设置则什么也不干
	if (!isVideoOpened || !isSetDone)
	{
		return;
	}

	countIn[(currentFrame - 1) / recordFrameNum]++;
	updateData();
}


// 右击视频label区域的槽函数
void AccuracyValidationTool::countOutPlus()
{ // 当前记录时间段出去人数+1
  // 如果+1前人数为0则-1按钮恢复可用

	// 如果没有打开视频或未完成初始设置则什么也不干
	if (!isVideoOpened || !isSetDone)
	{
		return;
	}

	countOut[(currentFrame - 1) / recordFrameNum]++;
	updateData();
}


// 更新最大记录帧数、计数容器大小和当前段的显示
void AccuracyValidationTool::updateData()
{
	// 更新最大记录帧数
	if (currentFrame > maxFrameNum)
	{
		maxFrameNum = currentFrame;
	}

	// 更新计数容器的大小
	if ((currentFrame - 1) / recordFrameNum + 1 > countIn.size())
	{
		countIn.resize((currentFrame - 1) / recordFrameNum + 1, 0);
		countIn[(currentFrame - 1) / recordFrameNum] = 0;
		countOut.resize((currentFrame - 1) / recordFrameNum + 1, 0);
		countOut[(currentFrame - 1) / recordFrameNum] = 0;
	}

	// 更新当前段的显示
	ui.spinBox_countIn->setValue(countIn[(currentFrame - 1) / recordFrameNum]);
	ui.spinBox_countOut->setValue(countOut[(currentFrame - 1) / recordFrameNum]);
}


// Mat转QImage
QImage AccuracyValidationTool::Mat2QImage(Mat cvImg)
{ // 针对不同格式的图片将Mat格式的图片转成QImage格式，以便于显示到QLabel上

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
{ // 将一张图片显示到QLabel上，如果读得到图片则返回true，否则返回false

	Mat frame;
	if (capture.read(frame))
	{
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
{ // 打开“打开文件”窗口，选择视频
  // 没有选择视频则提示先打开视频
  // 视频打开不成功则报错

	QString q_filePath = QFileDialog::getOpenFileName(this, "Open Document", QDir::currentPath(), "All files(*.*)");

	if (!q_filePath.isNull())
	{ // 用户选择了文件
	    // 打开视频文件

		string filePath = q_filePath.toStdString();
		capture.open(filePath);

		if (!capture.isOpened())
		{ // 视频文件打开失败
			QMessageBox::critical(this, "critical", "Failed to open the video!", QMessageBox::Ok);
			return;
		}

		// 保存后缀替换成.csv的文件名
		getQFileName(q_filePath);

		// 视频打开后进行的操作，将设置控件逐渐变为可用
		videoOpened();
	}
	else 
	{ // 用户取消选择
		// 提示先打开视频

		QMessageBox::warning(this, "warning", "Please open a video first!", QMessageBox::Ok);
	}
}


// 设置帧率的槽函数
void AccuracyValidationTool::slot_setFrameRate()
{ // 设置帧率后将相关设置控件变为不可用，将设置每次记录时长相关控件设为可用

	frameRate = ui.spinBox_frameRate->value();
	frameInterval = 1000.0 / double(frameRate);

	ui.spinBox_frameRate->setDisabled(true);
	ui.pushButton_frameRate->setDisabled(true);
	ui.spinBox_recordInterval->setEnabled(true);
	ui.pushButton_recordInterval->setEnabled(true);
}


// 设置每次记录时长的槽函数
void AccuracyValidationTool::slot_setRecordInterval()
{ // 设置每次记录时长后将相关设置控件变为不可用，将设置开始时间相关控件设为可用

	recordInterval = ui.spinBox_recordInterval->value();
	recordFrameNum = frameRate * recordInterval;

	ui.spinBox_recordInterval->setDisabled(true);
	ui.pushButton_recordInterval->setDisabled(true);
	ui.dateTimeEdit_startTime->setEnabled(true);
	ui.pushButton_startTime->setEnabled(true);
}


// 设置开始记录时间
void AccuracyValidationTool::slot_setStartTime()
{ // 设置开始记录时间后将相关设置控件变为不可用，将视频操作相关控件变为可用
  // 令isSetDone=true，表示可以开始进行计数了

	startTime = ui.dateTimeEdit_startTime->dateTime();

	ui.dateTimeEdit_startTime->setDisabled(true);
	ui.pushButton_startTime->setDisabled(true);
	ui.horizontalSlider->setEnabled(true);
	ui.comboBox_speed->setEnabled(true);
	ui.pushButton_inMinusOne->setEnabled(true);
	ui.pushButton_outMinusOne->setEnabled(true);
	ui.pushButton_export->setEnabled(true);
	ui.pushButton_close->setEnabled(true);

	isSetDone = true;
}


// 视频进度条被拖动的槽函数
void AccuracyValidationTool::slot_HSliderMoved(int value)
{ // 视频进度条被拖动时更改当前帧的值，并将对应图片显示出来

	currentFrame = value;
	capture.set(CV_CAP_PROP_POS_FRAMES, currentFrame);
	showOneFrame();
	currentFrame++;
	updateData();
}


// 视频进度条滑块点击释放的槽函数
void AccuracyValidationTool::slot_HSliderReleased() 
{ // 释放后将焦点设在label上，避免键盘按左右键时焦点仍停留在进度条上

	setFocusOnVideo();
}


// 视频播放速度的槽函数
void AccuracyValidationTool::slot_videoSpeed(int index)
{ // x0.5，x1.0，x2.0，x4.0四种播放速度，设定后更改相邻两张图片显示的间隔

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
	setFocusOnVideo();
}


// 点击进入人数-1按钮的槽函数
void AccuracyValidationTool::slot_countInMinus()
{ // 当前记录时间段进入人数-1
  // 如果人数减到0则-1按钮变为不可用

	if (countIn[(currentFrame - 1) / recordFrameNum] > 0)
	{
		countIn[(currentFrame - 1) / recordFrameNum]--;
	}
	updateData();
	setFocusOnVideo();
}


// 点击出去人数-1按钮的槽函数
void AccuracyValidationTool::slot_countOutMinus()
{ // 当前记录时间段出去人数-1
  // 如果人数减到0则-1按钮变为不可用

	if (countOut[(currentFrame - 1) / recordFrameNum] > 0)
	{
		countOut[(currentFrame - 1) / recordFrameNum]--;
	}
	updateData();
	setFocusOnVideo();
}


// 点击导出数据按钮的槽函数
void AccuracyValidationTool::slot_exportFile()
{ // 截止到所记录的最大帧数值将记录数据导出为csv文件

	QString q_filePath = "outputFile/" + q_fileName;
	QFile file(q_filePath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::critical(this, "critical", "Failed to open file for writing!", QMessageBox::Ok);
		return;
	}
	QTextStream out(&file);

	// 写表头
	out << "start time," << "end time," << "In," << "Out" << endl;

	// 写数据
	for (int i = 0; i < countIn.size(); i++)
	{
		out << startTime.addSecs(i * recordInterval).toString("yyyy-MM-dd HH:mm:ss") << ","
			<< startTime.addSecs((i + 1) * recordInterval - 1).toString("yyyy-MM-dd HH:mm:ss")
			<< "," << QString::number(countIn[i]) << "," << QString::number(countOut[i]) << endl;
	}
	
	isBeenExport = true;
	setFocusOnVideo();
}


// 点击关闭视频按钮的槽函数
void AccuracyValidationTool::slot_closeVideo()
{ // 关闭视频后将重置Ui界面，变为刚打开程序时的状态
  // 如果当前视频没有导出过文件，关闭前先导出文件
  // 关闭视频前进行提示确认，避免误点

	if (0 == QMessageBox::question(this, "Confirm Close", "Are you sure you want to close the video?",
		"Close", "Cancel", 0, 1, 1))
	{
		if (!isBeenExport)
		{
			slot_exportFile();
		}

		// 对相关变量进行重置
		currentFrame = 0;
		isVideoOn = false;
		isVideoOpened = false;
		isVideoStopped = false;
		isSetDone = false;
		isBeenExport = false;
		countIn.clear();
		countOut.clear();
		capture.release();

		// 对Ui进行重置
		resetUi();
	}
}

