#include <QtGui>

#include "MainWindow.h"
#include "ChatWidget.h"
#include "OnlineList.h"

MainWindow::MainWindow()
{
	createMainWeiget();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMainWeiget()
{
    // 加载背景图片
    QPixmap bgPixmap(":/res/images/background.png");
    // 定义画刷
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(bgPixmap));

    // 控件安装画刷
    this->setAutoFillBackground(true);
    this->setPalette(palette);

	onlineList = new OnlineList();
	chatWidget = new ChatWidget(onlineList);

	listLayout = new QVBoxLayout();
	listLayout->addWidget(onlineList);

	QWidget *listWidget = new QWidget();
	listWidget->setLayout(listLayout);

	mainSplitter = new QSplitter(Qt::Horizontal);
	mainSplitter->addWidget(chatWidget);
	mainSplitter->addWidget(listWidget);

	setCentralWidget(mainSplitter);
	setWindowIcon(QIcon(":/res/images/logo.png"));
	resize(800, 550);
    setWindowTitle(tr("kakaotalk"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	
	int res = QMessageBox::question(NULL, this->windowTitle(),
		tr("您真的要退出本程序吗？"), QMessageBox::Yes | QMessageBox::No);
	if (res == QMessageBox::Yes) {
		event->accept();
        chatWidget->sendMessage(Userleft);
	} else{
		event->ignore();
	}
}

