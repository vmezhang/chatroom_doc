#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

class ChatWidget;
class OnlineList;
class QSplitter;
class QVBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void createMainWeiget(); 	// 创建主窗口控件

private:
    ChatWidget *chatWidget; 	// 主窗口聊天控件
    QVBoxLayout *listLayout;    // 在线用户的布局管理
    OnlineList *onlineList;     // 在线用户列表
    QSplitter * mainSplitter;   // 主窗口分割条
};

#endif // MAIN_WINDOW_H_
