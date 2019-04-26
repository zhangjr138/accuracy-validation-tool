/********************************************************************************
** Form generated from reading UI file 'accuracyvalidationtool.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCURACYVALIDATIONTOOL_H
#define UI_ACCURACYVALIDATIONTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AccuracyValidationToolClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label_video;
    QSlider *horizontalSlider;
    QComboBox *comboBox_speed;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_frameRate;
    QSpinBox *spinBox_frameRate;
    QPushButton *pushButton_frameRate;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_recordInterval;
    QSpinBox *spinBox_recordInterval;
    QPushButton *pushButton_recordInterval;
    QHBoxLayout *horizontalLayout;
    QLabel *label_startTime;
    QDateTimeEdit *dateTimeEdit_startTime;
    QPushButton *pushButton_startTime;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_countIn;
    QSpinBox *spinBox_countIn;
    QPushButton *pushButton_inMinusOne;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_countOut;
    QSpinBox *spinBox_countOut;
    QPushButton *pushButton_outMinusOne;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_open;
    QPushButton *pushButton_export;
    QPushButton *pushButton_close;

    void setupUi(QMainWindow *AccuracyValidationToolClass)
    {
        if (AccuracyValidationToolClass->objectName().isEmpty())
            AccuracyValidationToolClass->setObjectName(QStringLiteral("AccuracyValidationToolClass"));
        AccuracyValidationToolClass->resize(1070, 767);
        centralWidget = new QWidget(AccuracyValidationToolClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(12);
        label_video = new QLabel(centralWidget);
        label_video->setObjectName(QStringLiteral("label_video"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_video->sizePolicy().hasHeightForWidth());
        label_video->setSizePolicy(sizePolicy);
        label_video->setFrameShape(QFrame::Box);
        label_video->setScaledContents(true);

        gridLayout->addWidget(label_video, 0, 0, 1, 8);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 1, 0, 1, 7);

        comboBox_speed = new QComboBox(centralWidget);
        comboBox_speed->setObjectName(QStringLiteral("comboBox_speed"));

        gridLayout->addWidget(comboBox_speed, 1, 7, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_frameRate = new QLabel(centralWidget);
        label_frameRate->setObjectName(QStringLiteral("label_frameRate"));

        horizontalLayout_3->addWidget(label_frameRate);

        spinBox_frameRate = new QSpinBox(centralWidget);
        spinBox_frameRate->setObjectName(QStringLiteral("spinBox_frameRate"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinBox_frameRate->sizePolicy().hasHeightForWidth());
        spinBox_frameRate->setSizePolicy(sizePolicy1);
        spinBox_frameRate->setMinimum(1);
        spinBox_frameRate->setValue(15);

        horizontalLayout_3->addWidget(spinBox_frameRate);

        pushButton_frameRate = new QPushButton(centralWidget);
        pushButton_frameRate->setObjectName(QStringLiteral("pushButton_frameRate"));

        horizontalLayout_3->addWidget(pushButton_frameRate);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_recordInterval = new QLabel(centralWidget);
        label_recordInterval->setObjectName(QStringLiteral("label_recordInterval"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_recordInterval->sizePolicy().hasHeightForWidth());
        label_recordInterval->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_recordInterval);

        spinBox_recordInterval = new QSpinBox(centralWidget);
        spinBox_recordInterval->setObjectName(QStringLiteral("spinBox_recordInterval"));
        sizePolicy1.setHeightForWidth(spinBox_recordInterval->sizePolicy().hasHeightForWidth());
        spinBox_recordInterval->setSizePolicy(sizePolicy1);
        spinBox_recordInterval->setMinimum(1);
        spinBox_recordInterval->setMaximum(10000);
        spinBox_recordInterval->setValue(5);

        horizontalLayout_4->addWidget(spinBox_recordInterval);

        pushButton_recordInterval = new QPushButton(centralWidget);
        pushButton_recordInterval->setObjectName(QStringLiteral("pushButton_recordInterval"));

        horizontalLayout_4->addWidget(pushButton_recordInterval);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_startTime = new QLabel(centralWidget);
        label_startTime->setObjectName(QStringLiteral("label_startTime"));

        horizontalLayout->addWidget(label_startTime);

        dateTimeEdit_startTime = new QDateTimeEdit(centralWidget);
        dateTimeEdit_startTime->setObjectName(QStringLiteral("dateTimeEdit_startTime"));
        sizePolicy1.setHeightForWidth(dateTimeEdit_startTime->sizePolicy().hasHeightForWidth());
        dateTimeEdit_startTime->setSizePolicy(sizePolicy1);
        dateTimeEdit_startTime->setCalendarPopup(true);

        horizontalLayout->addWidget(dateTimeEdit_startTime);

        pushButton_startTime = new QPushButton(centralWidget);
        pushButton_startTime->setObjectName(QStringLiteral("pushButton_startTime"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_startTime->sizePolicy().hasHeightForWidth());
        pushButton_startTime->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(pushButton_startTime);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 3, 0, 3, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(12);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(20);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_countIn = new QLabel(centralWidget);
        label_countIn->setObjectName(QStringLiteral("label_countIn"));

        horizontalLayout_5->addWidget(label_countIn);

        spinBox_countIn = new QSpinBox(centralWidget);
        spinBox_countIn->setObjectName(QStringLiteral("spinBox_countIn"));
        spinBox_countIn->setEnabled(false);
        sizePolicy3.setHeightForWidth(spinBox_countIn->sizePolicy().hasHeightForWidth());
        spinBox_countIn->setSizePolicy(sizePolicy3);
        spinBox_countIn->setMaximum(10000);

        horizontalLayout_5->addWidget(spinBox_countIn);

        pushButton_inMinusOne = new QPushButton(centralWidget);
        pushButton_inMinusOne->setObjectName(QStringLiteral("pushButton_inMinusOne"));

        horizontalLayout_5->addWidget(pushButton_inMinusOne);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(20);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_countOut = new QLabel(centralWidget);
        label_countOut->setObjectName(QStringLiteral("label_countOut"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_countOut->sizePolicy().hasHeightForWidth());
        label_countOut->setSizePolicy(sizePolicy4);

        horizontalLayout_6->addWidget(label_countOut);

        spinBox_countOut = new QSpinBox(centralWidget);
        spinBox_countOut->setObjectName(QStringLiteral("spinBox_countOut"));
        spinBox_countOut->setEnabled(false);
        sizePolicy3.setHeightForWidth(spinBox_countOut->sizePolicy().hasHeightForWidth());
        spinBox_countOut->setSizePolicy(sizePolicy3);
        spinBox_countOut->setMaximum(10000);

        horizontalLayout_6->addWidget(spinBox_countOut);

        pushButton_outMinusOne = new QPushButton(centralWidget);
        pushButton_outMinusOne->setObjectName(QStringLiteral("pushButton_outMinusOne"));

        horizontalLayout_6->addWidget(pushButton_outMinusOne);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(20);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        pushButton_open = new QPushButton(centralWidget);
        pushButton_open->setObjectName(QStringLiteral("pushButton_open"));
        sizePolicy3.setHeightForWidth(pushButton_open->sizePolicy().hasHeightForWidth());
        pushButton_open->setSizePolicy(sizePolicy3);

        horizontalLayout_7->addWidget(pushButton_open);

        pushButton_export = new QPushButton(centralWidget);
        pushButton_export->setObjectName(QStringLiteral("pushButton_export"));
        sizePolicy3.setHeightForWidth(pushButton_export->sizePolicy().hasHeightForWidth());
        pushButton_export->setSizePolicy(sizePolicy3);

        horizontalLayout_7->addWidget(pushButton_export);

        pushButton_close = new QPushButton(centralWidget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));

        horizontalLayout_7->addWidget(pushButton_close);


        verticalLayout_2->addLayout(horizontalLayout_7);


        gridLayout->addLayout(verticalLayout_2, 3, 3, 3, 5);

        AccuracyValidationToolClass->setCentralWidget(centralWidget);

        retranslateUi(AccuracyValidationToolClass);
        QObject::connect(pushButton_open, SIGNAL(clicked()), AccuracyValidationToolClass, SLOT(slot_openAVideo()));
        QObject::connect(comboBox_speed, SIGNAL(currentIndexChanged(int)), AccuracyValidationToolClass, SLOT(slot_videoSpeed(int)));
        QObject::connect(horizontalSlider, SIGNAL(sliderMoved(int)), AccuracyValidationToolClass, SLOT(slot_HSliderMoved(int)));
        QObject::connect(horizontalSlider, SIGNAL(sliderReleased()), AccuracyValidationToolClass, SLOT(slot_HSliderReleased()));
        QObject::connect(pushButton_frameRate, SIGNAL(clicked()), AccuracyValidationToolClass, SLOT(slot_setFrameRate()));
        QObject::connect(pushButton_recordInterval, SIGNAL(clicked()), AccuracyValidationToolClass, SLOT(slot_setRecordInterval()));
        QObject::connect(pushButton_startTime, SIGNAL(clicked()), AccuracyValidationToolClass, SLOT(slot_setStartTime()));
        QObject::connect(pushButton_inMinusOne, SIGNAL(clicked()), AccuracyValidationToolClass, SLOT(slot_countInMinus()));
        QObject::connect(pushButton_outMinusOne, SIGNAL(clicked()), AccuracyValidationToolClass, SLOT(slot_countOutMinus()));
        QObject::connect(pushButton_export, SIGNAL(clicked()), AccuracyValidationToolClass, SLOT(slot_exportFile()));
        QObject::connect(pushButton_close, SIGNAL(clicked()), AccuracyValidationToolClass, SLOT(slot_closeVideo()));

        comboBox_speed->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(AccuracyValidationToolClass);
    } // setupUi

    void retranslateUi(QMainWindow *AccuracyValidationToolClass)
    {
        AccuracyValidationToolClass->setWindowTitle(QApplication::translate("AccuracyValidationToolClass", "AccuracyValidationTool", Q_NULLPTR));
        label_video->setText(QString());
        comboBox_speed->clear();
        comboBox_speed->insertItems(0, QStringList()
         << QApplication::translate("AccuracyValidationToolClass", "x0.5", Q_NULLPTR)
         << QApplication::translate("AccuracyValidationToolClass", "x1.0", Q_NULLPTR)
         << QApplication::translate("AccuracyValidationToolClass", "x2.0", Q_NULLPTR)
         << QApplication::translate("AccuracyValidationToolClass", "x4.0", Q_NULLPTR)
        );
        label_frameRate->setText(QApplication::translate("AccuracyValidationToolClass", " Frame Rate:     ", Q_NULLPTR));
        pushButton_frameRate->setText(QApplication::translate("AccuracyValidationToolClass", "Set", Q_NULLPTR));
        label_recordInterval->setText(QApplication::translate("AccuracyValidationToolClass", " Report Interval:", Q_NULLPTR));
        pushButton_recordInterval->setText(QApplication::translate("AccuracyValidationToolClass", "Set", Q_NULLPTR));
        label_startTime->setText(QApplication::translate("AccuracyValidationToolClass", " Start Time:     ", Q_NULLPTR));
        dateTimeEdit_startTime->setDisplayFormat(QApplication::translate("AccuracyValidationToolClass", "yyyy/MM/dd HH:mm:ss", Q_NULLPTR));
        pushButton_startTime->setText(QApplication::translate("AccuracyValidationToolClass", "Set", Q_NULLPTR));
        label_countIn->setText(QApplication::translate("AccuracyValidationToolClass", " Count of In: ", Q_NULLPTR));
        pushButton_inMinusOne->setText(QApplication::translate("AccuracyValidationToolClass", "      -1       ", Q_NULLPTR));
        label_countOut->setText(QApplication::translate("AccuracyValidationToolClass", " Count of Out:", Q_NULLPTR));
        pushButton_outMinusOne->setText(QApplication::translate("AccuracyValidationToolClass", "      -1       ", Q_NULLPTR));
        pushButton_open->setText(QApplication::translate("AccuracyValidationToolClass", " Open a Video  ", Q_NULLPTR));
        pushButton_export->setText(QApplication::translate("AccuracyValidationToolClass", "  Export File  ", Q_NULLPTR));
        pushButton_close->setText(QApplication::translate("AccuracyValidationToolClass", "  Close Video  ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AccuracyValidationToolClass: public Ui_AccuracyValidationToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCURACYVALIDATIONTOOL_H
