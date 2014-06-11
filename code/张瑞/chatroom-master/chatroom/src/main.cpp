#include <QtGui>
#include <QApplication>
#include <QTest>
#include <QSplashScreen>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
	// 处理中文乱码问题
	QTextCodec *codec = QTextCodec::codecForName("system");

	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	
	QApplication app(argc, argv);

	//加载Qt自带的控件汉化文件
	QTranslator translator;

	translator.load(":/res/language/qt_zh_CN.qm");
	app.installTranslator(&translator);

   /* // 使用共享内存的方法确保本程序只运行一个实例
    QSystemSemaphore sema("xylchat_key", 1, QSystemSemaphore::Open);
	sema.acquire();

	QSharedMemory mem("xylchat_lock");
	if (!mem.create(1)) {
        QMessageBox::information(0, "chatroom", "本程序只允许运行一个实例哦～亲");
		sema.release();
		return 0;   
    } */

    // 启动画面
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/res/images/splash.png"));
    splash->show();
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::black);
    QTest::qSleep(3000);

	MainWindow *mainwindow = new MainWindow();
	
    splash->showMessage(QObject::tr("Loading modules..."), topRight, Qt::black);
    QTest::qSleep(3000);

	// 窗口显示在屏幕正中间
	mainwindow->move((QApplication::desktop()->width() - mainwindow->width()) >> 1,
				(QApplication::desktop()->height() - mainwindow->height()) >> 1);
	mainwindow->show();

    splash->finish(mainwindow);
    delete splash;

    //sema.release();

	return app.exec();
}

