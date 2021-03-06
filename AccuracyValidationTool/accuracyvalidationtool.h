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
	void keyPressEvent(QKeyEvent *event); // 检测键盘事件
	bool eventFilter(QObject *obj, QEvent *event); // 事件过滤器
	void closeEvent(QCloseEvent *event); // 窗口关闭函数

private:
	void videoForward(); // 键盘右键前进
	void videoBackward(); // 键盘左键后退
	void videoPlay(); // 视频的播放和暂停
	void resetUi(); // 对Ui进行重置
	void setFocusOnVideo(); // 将焦点放在图片显示区域上
	void getQFileName(QString q_filePath); // 保存后缀替换成.csv的文件名
	void videoOpened(); // 视频打开后进行的操作
	void resetHSlider(int frameNumTotal); // 重置视频进度条
	void setHSlider(int currentFrame); // 设置进度条
	void countInPlus(); // 左击视频label区域的槽函数
	void countOutPlus(); // 右击视频label区域的槽函数
	void updateData(); // 更新最大记录帧数、计数容器大小和当前段的显示
	QImage Mat2QImage(Mat cvImg); // Mat转QImage
	bool showOneFrame(); // 将一帧放到QLabel上

private slots:
	void slot_openAVideo(); // 点击打开视频按钮的槽函数
private slots:
	void slot_setFrameRate(); // 点击设置帧率按钮的槽函数
private slots:
	void slot_setRecordInterval(); // 点击设置每次记录时长按钮的槽函数
private slots:
	void slot_setStartTime(); // 点击设置开始记录时间按钮的槽函数
private slots:
	void slot_HSliderMoved(int value); // 视频进度条被拖动的槽函数
private slots:
	void slot_HSliderReleased(); // 视频进度条滑块点击释放的槽函数
private slots:
	void slot_videoSpeed(int index); // 视频播放速度的槽函数
private slots:
	void slot_countInMinus(); // 点击进入人数-1按钮的槽函数
private slots:
	void slot_countOutMinus(); // 点击出去人数-1按钮的槽函数
private slots:
	void slot_exportFile(); // 点击导出数据按钮的槽函数
private slots:
	void slot_closeVideo(); // 点击关闭视频按钮的槽函数

private:
	Ui::AccuracyValidationToolClass ui;
	VideoCapture capture; // 视频捕捉
	int frameNumTotal = 0; // 视频的总帧数
	int fps = 0; // 视频的帧率
	double frameInterval = 0; // 视频播放速度
	int currentFrame = 0; // 视频的当前帧
	bool isVideoOpened = true; // 是否有视频被打开
	bool isVideoOn = false; // 视频是否的播放和暂停
	bool isVideoStopped = false; // 用于结束程序时判断视频是否停下来
	bool isVideoUncomplete = false; // 视频是否不完整，即获取不了总帧数
	bool isSetDone = false; // 是否初始设置完成，可以进行计数
	bool isBeenExport = false; // 当前视频是否导出过文件

	// 和导出相关的数据
	QString q_fileName; // 导出文件的文件名
	QDateTime startTime; // 设置的开始记录时间
	int frameRate = 0; // 设置的帧率
	int recordInterval = 0; // 设置的每次记录时长
	int recordFrameNum = 0; // 帧率 * 每次记录时长
	int maxFrameNum = 0; // 所记录的最大帧数
	vector<int> countIn; // 记录进入的人数
	vector<int> countOut; // 记录出去的人数
};
