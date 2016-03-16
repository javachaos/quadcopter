/********************************************************************************
 ** Form generated from reading UI file 'quadview.ui'
 **
 ** Created by: Qt User Interface Compiler version 5.2.1
 **
 ** WARNING! All changes made in this file will be lost when recompiling UI file!
 ********************************************************************************/

#ifndef UI_QUADVIEW_H
#define UI_QUADVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuadView {
public:
	QWidget *centralWidget;
	QLCDNumber *FlightTimer;
	QPushButton *pushButton;
	QGroupBox *groupBox;
	QWidget *widget;
	QHBoxLayout *horizontalLayout;
	QProgressBar *motor1Speed;
	QProgressBar *motor2Speed;
	QProgressBar *motor3Speed;
	QProgressBar *motor4Speed;
	QWidget *widget1;
	QHBoxLayout *horizontalLayout_2;
	QDial *SpeedDial1;
	QDial *SpeedDial2;
	QDial *SpeedDial3;
	QDial *SpeedDial4;
	QMenuBar *menuBar;
	QToolBar *mainToolBar;
	QStatusBar *statusBar;

	void setupUi(QMainWindow *QuadView) {
		if (QuadView->objectName().isEmpty())
			QuadView->setObjectName(QStringLiteral("QuadView"));
		QuadView->resize(756, 399);
		centralWidget = new QWidget(QuadView);
		centralWidget->setObjectName(QStringLiteral("centralWidget"));
		FlightTimer = new QLCDNumber(centralWidget);
		FlightTimer->setObjectName(QStringLiteral("FlightTimer"));
		FlightTimer->setGeometry(QRect(660, 0, 91, 31));
		FlightTimer->setSmallDecimalPoint(false);
		pushButton = new QPushButton(centralWidget);
		pushButton->setObjectName(QStringLiteral("pushButton"));
		pushButton->setGeometry(QRect(10, 310, 99, 27));
		groupBox = new QGroupBox(centralWidget);
		groupBox->setObjectName(QStringLiteral("groupBox"));
		groupBox->setGeometry(QRect(10, 0, 181, 171));
		widget = new QWidget(groupBox);
		widget->setObjectName(QStringLiteral("widget"));
		widget->setGeometry(QRect(10, 20, 171, 151));
		horizontalLayout = new QHBoxLayout(widget);
		horizontalLayout->setSpacing(6);
		horizontalLayout->setContentsMargins(11, 11, 11, 11);
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		horizontalLayout->setContentsMargins(0, 0, 0, 0);
		motor1Speed = new QProgressBar(widget);
		motor1Speed->setObjectName(QStringLiteral("motor1Speed"));
		motor1Speed->setValue(24);
		motor1Speed->setOrientation(Qt::Vertical);
		motor1Speed->setTextDirection(QProgressBar::TopToBottom);

		horizontalLayout->addWidget(motor1Speed);

		motor2Speed = new QProgressBar(widget);
		motor2Speed->setObjectName(QStringLiteral("motor2Speed"));
		motor2Speed->setValue(24);
		motor2Speed->setOrientation(Qt::Vertical);
		motor2Speed->setTextDirection(QProgressBar::TopToBottom);

		horizontalLayout->addWidget(motor2Speed);

		motor3Speed = new QProgressBar(widget);
		motor3Speed->setObjectName(QStringLiteral("motor3Speed"));
		motor3Speed->setValue(24);
		motor3Speed->setOrientation(Qt::Vertical);
		motor3Speed->setTextDirection(QProgressBar::TopToBottom);

		horizontalLayout->addWidget(motor3Speed);

		motor4Speed = new QProgressBar(widget);
		motor4Speed->setObjectName(QStringLiteral("motor4Speed"));
		motor4Speed->setValue(24);
		motor4Speed->setOrientation(Qt::Vertical);
		motor4Speed->setTextDirection(QProgressBar::TopToBottom);

		horizontalLayout->addWidget(motor4Speed);

		widget1 = new QWidget(centralWidget);
		widget1->setObjectName(QStringLiteral("widget1"));
		widget1->setGeometry(QRect(10, 210, 420, 102));
		horizontalLayout_2 = new QHBoxLayout(widget1);
		horizontalLayout_2->setSpacing(6);
		horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
		horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
		horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
		SpeedDial1 = new QDial(widget1);
		SpeedDial1->setObjectName(QStringLiteral("SpeedDial1"));

		horizontalLayout_2->addWidget(SpeedDial1);

		SpeedDial2 = new QDial(widget1);
		SpeedDial2->setObjectName(QStringLiteral("SpeedDial2"));

		horizontalLayout_2->addWidget(SpeedDial2);

		SpeedDial3 = new QDial(widget1);
		SpeedDial3->setObjectName(QStringLiteral("SpeedDial3"));

		horizontalLayout_2->addWidget(SpeedDial3);

		SpeedDial4 = new QDial(widget1);
		SpeedDial4->setObjectName(QStringLiteral("SpeedDial4"));

		horizontalLayout_2->addWidget(SpeedDial4);

		QuadView->setCentralWidget(centralWidget);
		menuBar = new QMenuBar(QuadView);
		menuBar->setObjectName(QStringLiteral("menuBar"));
		menuBar->setGeometry(QRect(0, 0, 756, 25));
		QuadView->setMenuBar(menuBar);
		mainToolBar = new QToolBar(QuadView);
		mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
		QuadView->addToolBar(Qt::TopToolBarArea, mainToolBar);
		statusBar = new QStatusBar(QuadView);
		statusBar->setObjectName(QStringLiteral("statusBar"));
		QuadView->setStatusBar(statusBar);

		retranslateUi(QuadView);

		QMetaObject::connectSlotsByName(QuadView);
	} // setupUi

	void retranslateUi(QMainWindow *QuadView) {
		QuadView->setWindowTitle(
				QApplication::translate("QuadView", "QuadView", 0));
		pushButton->setText(QApplication::translate("QuadView", "Connect", 0));
		groupBox->setTitle(
				QApplication::translate("QuadView", "Motor Stats", 0));
	} // retranslateUi

};

namespace Ui {
class QuadView: public Ui_QuadView {
};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUADVIEW_H
