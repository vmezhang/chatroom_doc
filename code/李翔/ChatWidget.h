#ifndef CHATWIDGET_H_
#define CHATWIDGET_H_

#include <QWidget>
#include <QtNetwork>
#include <QLabel>
#include <QtGui>


class QVBoxLayout;
class QHBoxLayout;
class QSplitter;
class QTextBrowser;
class QTextEdit;
class QListView;
class QPushButton;
class OnlineList;
class QTimer;
class QWidget;
class QImage;

#include <highgui.h>  //包含opencv库头文件
#include <cv.h>
#include "CamareGet.h"

// 用户消息类型的枚举变量
enum MessageType {
    Message      = 0,
    UserLogin    = 1,
    Userleft     = 2,
    AskWhoOnline = 3,
    IamOnline    = 4,
    other        = 5,
    videono      = 6,
    videoyes     = 7,
    videook      = 8,
    video        = 9
};

class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    ChatWidget();
    ChatWidget(OnlineList *onlineList);
    ~ChatWidget();

    void createWidget();
    void createNetLink();
public:
    //    QTimer    *timer_send;
    QTimer     *timer;          // 定时器信息
    QImage      image;
    QImage reImage;
    CvCapture  *cam;		// 视频获取结构， 用来作为视频获取函数的一个参数
    IplImage   *sendFrame;		// 申请IplImage类型指针，就是申请内存空间来存放待发送的每一帧图像
    QImage sendImage;       // 自己摄像头抓取到的帧，转换为QImage格式
    QImage recvImage;       // 接受到对方摄像头的帧，转换为QImage格式

protected:
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *target, QEvent *event);
   //

public slots:
    void fontSize();
    void fontBold();
    void fontItalic();
    void fontUnderline();
    void fontColor();
    void require();             // 需要李翔完成的函数
    void sendVideo();               // 需要李翔完成的函数
    void insertImage();
    void saveChatInfo();
    void clearChatInfo();
    void sendSlot();
    void sure();
     void closeCamara();     // 关闭摄像头

    // 发送数据包
    void sendMessage(MessageType type, QString ipAddr = "");
    // 接收处理数据包
    void recvMessage();

private:
    // 获取IP地址
    QString getIP();
    // 获取用户名
    QString getUserName();
    // 获取输入信息
    QString getMessage();

    void requirevideo(QString username,QString vidoedata);         //回复是否视频

    // 聊天框添加一条聊天信息
    void addUserChatInfoOnce(QString username, QString message);

    // 处理用户上线
    void disUserLogin(QString username, QString hostname, QString ipAddr);
    // 处理用户离线
    void disUserLeft(QString username, QString hostname, QString ipAddr);
    void sendVideoMessage(QString username,QString message); // 需要李翔完成的函数
    void recvVideoMessage(QString videodata);
    void openVideo();
    void recvVideo(QString username,QByteArray data);
void recvVideo1(QString username,QString data);


private:
    QUdpSocket *sockServer;
    qint16      listen_port;

    OnlineList *onlineList;

    // 视频聊天所用的摄像头类
    CamaraGet   *camare;

    QString     myname;

    QVBoxLayout  *mainVBoxLayout;
    QHBoxLayout  *toolHBoxLayout1;
    QHBoxLayout  *toolHBoxLayout2;
    QHBoxLayout  *buttonHBoxLayout;

    QTextBrowser *chatText;
    QTextEdit    *sendText;

    QPushButton  *closeButton;
    QPushButton  *sendButton;

    QPushButton  *fontSizeButton;
    QPushButton  *fontBoldButton;
    QPushButton  *fontItalicButton;
    QPushButton  *fontUnderlineButton;
    QPushButton  *fontColorButton;
    QPushButton  *openVideoButton;
    QPushButton  *insertImageButton;
    QPushButton  *saveChatInfoButton;
    QPushButton  *clearChatInfoButton;
};

#endif // CHATWIDGET_H_
