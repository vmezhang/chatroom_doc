#include <QtGui>

#include "ChatWidget.h"
#include "OnlineList.h"

ChatWidget::ChatWidget()
{
    createWidget();
    createNetLink();
}


ChatWidget::ChatWidget(OnlineList *onlineList)
{
    this->onlineList = onlineList;
    createWidget();
    createNetLink();
    timer = new QTimer(this);
    camare = new CamaraGet();
    camare->cam   = NULL;
    camare->timer = new QTimer(this);
    connect(camare->timer, SIGNAL(timeout()), this, SLOT(sendVideo()));
    connect(timer, SIGNAL(timeout()), this, SLOT(sure()));

}

ChatWidget::~ChatWidget()
{
    delete sockServer;
}

void ChatWidget::createWidget()
{
    chatText = new QTextBrowser();
    chatText->setFocusPolicy(Qt::NoFocus);




    sendText = new QTextEdit();
    sendText->setFocusPolicy(Qt::StrongFocus);
    sendText->installEventFilter(this);
    sendText->setMaximumHeight(sendText->sizeHint().height() >> 1);

    fontSizeButton = new QPushButton(QIcon(":/res/images/fonts.png"), tr("字体"));
    connect(fontSizeButton, SIGNAL(clicked()), this, SLOT(fontSize()));
    fontBoldButton = new QPushButton(QIcon(":/res/images/textbold.png"), tr("加粗"));
    connect(fontBoldButton, SIGNAL(clicked()), this, SLOT(fontBold()));
    fontItalicButton = new QPushButton(QIcon(":/res/images/textitalic.png"), tr("斜体"));
    connect(fontItalicButton, SIGNAL(clicked()), this, SLOT(fontItalic()));
    fontUnderlineButton = new QPushButton(QIcon(":/res/images/textunderline.png"), tr("下划线"));
    connect(fontUnderlineButton, SIGNAL(clicked()), this, SLOT(fontUnderline()));
    fontColorButton = new QPushButton(QIcon(":/res/images/textcolor.png"), tr("颜色"));;
    connect(fontColorButton, SIGNAL(clicked()), this, SLOT(fontColor()));
    openVideoButton = new QPushButton(QIcon(":/res/images/openvideo.png"), tr("视频"));
    connect(openVideoButton, SIGNAL(clicked()), this, SLOT(require()));
    insertImageButton= new QPushButton(QIcon(":/res/images/insertimage.png"), tr("发送图片"));
    connect(insertImageButton, SIGNAL(clicked()), this, SLOT(insertImage()));
    saveChatInfoButton = new QPushButton(QIcon(":/res/images/save.png"), tr("保存记录"));
    connect(saveChatInfoButton, SIGNAL(clicked()), this, SLOT(saveChatInfo()));
    clearChatInfoButton = new QPushButton(QIcon(":/res/images/bin_empty.png"), tr("清楚记录"));
    connect(clearChatInfoButton, SIGNAL(clicked()), this, SLOT(clearChatInfo()));

    toolHBoxLayout1 = new QHBoxLayout;
    toolHBoxLayout2 = new QHBoxLayout;
    toolHBoxLayout1->addWidget(fontSizeButton);
    toolHBoxLayout1->addWidget(fontBoldButton);
    toolHBoxLayout1->addWidget(fontItalicButton);
    toolHBoxLayout1->addWidget(fontUnderlineButton);
    toolHBoxLayout1->addWidget(fontColorButton);
    toolHBoxLayout1->addStretch();
    toolHBoxLayout2->addWidget(openVideoButton);
    toolHBoxLayout2->addWidget(insertImageButton);
    toolHBoxLayout2->addWidget(saveChatInfoButton);
    toolHBoxLayout2->addWidget(clearChatInfoButton );
    toolHBoxLayout2->addStretch();

    sendButton = new QPushButton(tr("发送(&S)"));
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendSlot()));

    buttonHBoxLayout = new QHBoxLayout();
    buttonHBoxLayout->addStretch();
    buttonHBoxLayout->addWidget(sendButton);

    mainVBoxLayout = new QVBoxLayout();
    mainVBoxLayout->addWidget(chatText);
    mainVBoxLayout->addLayout(toolHBoxLayout1);
    mainVBoxLayout->addLayout(toolHBoxLayout2);
    mainVBoxLayout->addWidget(sendText);
    mainVBoxLayout->addLayout(buttonHBoxLayout);

    sendText->setFocus();
    setLayout(mainVBoxLayout);
     myname = getUserName();
}

void ChatWidget::createNetLink()
{
    sockServer = new QUdpSocket();
    listen_port = 9527;

    sockServer->bind(listen_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(sockServer, SIGNAL(readyRead()), this, SLOT(recvMessage()));
    sendMessage(UserLogin);
}

void ChatWidget::sendMessage(MessageType type, QString ipAddr)
{
    QByteArray data;
    QDataStream sendData(&data, QIODevice::WriteOnly);
    QDataStream send(&data, QIODevice::WriteOnly);
    QString videodata = "video1";

    QByteArray ba;
    QBuffer buffer(&ba);

    // 消息依次是 消息类型-用户名-主机名-IP地址-（发送消息）
    sendData << type << getUserName() << QHostInfo::localHostName() << getIP();

    switch (type) {
        case Message:
            sendData << getMessage();
            break;
        case IamOnline:
            sockServer->writeDatagram(data, data.length(), QHostAddress(ipAddr), listen_port);
            return;
        // do nothing
        case other:
        sendData << videodata;
        break;
        case videoyes:
        sendData << videodata;
        break;
        case videono:
        sendData << "no";
        break;
        case videook:
        sendData << "ok";
        break;
        case video:
        send << type << videodata << QHostInfo::localHostName() << getIP();

        buffer.open(QIODevice::ReadWrite);
        image.save(&buffer, "JPG");
        send <<ba;
        break;
        case UserLogin:
        case Userleft:
        case AskWhoOnline:
            break;
    }
    /*
     * QHostAddress::Broadcast	1
     * The IPv4 broadcast address. Equivalent to QHostAddress("255.255.255.255")
     */
    sockServer->writeDatagram(data, data.length(), QHostAddress::Broadcast, listen_port);
}

void ChatWidget::recvMessage()
{
    // 循环读取，读完为止
    while (sockServer->hasPendingDatagrams()) {
        QByteArray datagram;
        QByteArray data;
        datagram.resize(sockServer->pendingDatagramSize());
        sockServer->readDatagram(datagram.data(), datagram.size());
        QDataStream recvData(&datagram, QIODevice::ReadOnly);

        int messageType;
        QString username, hostname, ipAddr, message;
        QImage recvimage;

        recvData >> messageType >> username >> hostname >> ipAddr;

        switch (messageType) {
            case Message:
                recvData >> message;
                addUserChatInfoOnce(username, message);
                break;
            case UserLogin:
            case IamOnline:
                disUserLogin(username, hostname, ipAddr);
                break;
            case Userleft:
                disUserLeft(username, hostname, ipAddr);
                break;
            case AskWhoOnline:
                sendMessage(IamOnline, ipAddr);
                break;
            case other:
                recvData >> message;
                requirevideo(username,message);
                break;
            case videoyes:
                //addUserChatInfoOnce(username, "链接建立");
                recvData >> message;
                recvVideoMessage(username);
                break;
            case videono:
                addUserChatInfoOnce(username, "对方拒绝与您视频！");
                break;
            case videook:
                recvData>>message;
                sendVideoMessage(username,message);
                break;
            case video:
                recvData >> data;
                 //camare->getRecvImage(recvimage);
                recvVideo(username,data);
                break;


        }
    }
}

QString ChatWidget::getIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    foreach (QHostAddress address, list) {
        // 只获取 IPv4 协议地址
        if (address.protocol() == QAbstractSocket::IPv4Protocol
            && address.toString() != "127.0.0.1") {
            return address.toString();
        }
    }

    return 0;
}

QString ChatWidget::getUserName()
{
    QStringList envVariables;
    envVariables << "USERNAME.*" << "USER.*" << "USERDOMAIN.*" << "HOSTNAME.*" << "DOMAINNAME.*";
    QStringList environment = QProcess::systemEnvironment();

    foreach (QString string, envVariables) {
        int index = environment.indexOf(QRegExp(string));
        if (index != -1) {
            QStringList stringList = environment.at(index).split('=');
            if (stringList.size() == 2) {
                return stringList.at(1);
            }
        }
    }

    return NULL;
}

QString ChatWidget::getMessage()
{
    QString msg = sendText->toHtml();

    sendText->clear();
    sendText->setFocus();

    return msg;
}

void ChatWidget::addUserChatInfoOnce(QString username, QString message)
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    chatText->setTextColor(Qt::blue);
    chatText->setCurrentFont(QFont("Times New Roman", 12));
    chatText->append(username + " " + time);
    chatText->append(message);
    chatText->verticalScrollBar()->setValue(chatText->verticalScrollBar()->maximum());
}

void ChatWidget::disUserLogin(QString username, QString hostname, QString ipAddr)
{
    chatText->setTextColor(Qt::gray);
    chatText->setCurrentFont(QFont("Times New Roman", 10));
    chatText->append(tr("%1 [ %2 ] 加入了聊天室。").arg(username).arg(ipAddr));
    onlineList->insertUserInfo(username, hostname, ipAddr);
}

void ChatWidget::disUserLeft(QString username, QString hostname, QString ipAddr)
{
    chatText->setTextColor(Qt::gray);
    chatText->setCurrentFont(QFont("Times New Roman", 10));
    chatText->append(tr("%1 [ %2 ] 离开了聊天室。").arg(username).arg(ipAddr));
    onlineList->removeUserInfo(hostname);
}

/*void ChatWidget::closeEvent(QCloseEvent *)
{
    sendMessage(Userleft);
}*/

bool ChatWidget::eventFilter(QObject *target, QEvent *event)
{
    if (target == sendText) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *k = static_cast<QKeyEvent *>(event);
            if (k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter) {
                sendSlot();
                return true;
            }
        }
    }

    return QWidget::eventFilter(target, event);
}

void ChatWidget::fontSize()
{
    bool isGet;
    QFont font = QFontDialog::getFont(&isGet, QFont("Times", 12), this);

    if (isGet) {
        sendText->setCurrentFont(font);
    }

    sendText->setFocus();
}

void ChatWidget::fontBold()
{
    static bool isBold = false;

    if (isBold) {
        sendText->setFontWeight(QFont::Normal);
        isBold = false;
    } else {
        sendText->setFontWeight(QFont::Bold);
        isBold = true;
    }

    sendText->setFocus();
}

void ChatWidget::fontItalic()
{
    static bool isItali = false;

    if (isItali) {
        sendText->setFontItalic(false);
        isItali = false;
    } else {
        sendText->setFontItalic(true);
        isItali = true;
    }

    sendText->setFocus();
}

void ChatWidget::fontUnderline()
{
    static bool isUnderline = false;

    if (isUnderline) {
        sendText->setFontUnderline(false);
        isUnderline = false;
    } else {
        sendText->setFontUnderline(true);
        isUnderline = true;
    }

    sendText->setFocus();
}

void ChatWidget::fontColor()
{
    static QColor oldColor;

    QColor color = QColorDialog::getColor(oldColor, this);
    if (color.isValid()) {
        sendText->setTextColor(color);
        oldColor = color;
    }

    sendText->setFocus();
}

void ChatWidget::require()
{
    sendMessage(other);
}
void ChatWidget::requirevideo(QString username,QString videodata)
{

    if(myname != username){
        QMessageBox message(QMessageBox::Warning,"Information","是否接受视频？",QMessageBox::Yes|QMessageBox::No,NULL);
                if (message.exec()==QMessageBox::Yes) {
                     sendMessage(videoyes);
                      addUserChatInfoOnce(username, "链接建立1");
                      openVideo();
                }
                else{
                sendMessage(videono);
                }
    }


}

void ChatWidget::sendVideoMessage(QString username,QString message)
{
    addUserChatInfoOnce(username,"lian jie yi guan bi");
}

void ChatWidget::recvVideoMessage(QString username)
{
    if(myname != username){
    addUserChatInfoOnce(username, "链接建立2");
       openVideo();
  }
}

void ChatWidget::openVideo()
{
    // 打开摄像头，从摄像头中获取视频
    camare->cam = cvCreateCameraCapture(0);
    // 开始计时，超时则发出timeout()信号
    camare->timer->start(80);
    timer->start(50);
    camare->resize(600, 450);
    camare->show();
}

void ChatWidget::sendVideo()
{
    // 从摄像头中抓取并返回每一帧
    sendFrame = cvQueryFrame(camare->cam);
    // rgb转成bgr
    cvConvertImage(sendFrame, sendFrame, CV_CVTIMG_SWAP_RB);
    // 将获取到的帧，转换为QImage格式
     image = QImage ((const uchar*)sendFrame->imageData, sendFrame->width, sendFrame->height, QImage::Format_RGB888);
    camare->setPixmap(QPixmap::fromImage(image));
    sendMessage(video);
}
void ChatWidget:: recvVideo(QString username,QByteArray data)
{
     if(myname != username){
    recvImage.loadFromData(data);
    camare->setPixmap(QPixmap::fromImage(recvImage));
     }
}


void ChatWidget::insertImage()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "pic/", tr("Images (*.png *.jpg)"));
    QUrl fileUrl(QString("file://%1").arg(file));
    QImage image = QImageReader(file).read();
    QTextDocument * textDocument = sendText->document();
    textDocument->addResource(QTextDocument::ImageResource,fileUrl, QVariant(image));
    QTextCursor cursor = sendText->textCursor();
    QTextImageFormat imageFormat;

    imageFormat.setWidth(image.width());
    imageFormat.setHeight(image.height());
    imageFormat.setName(fileUrl.toString());
    cursor.insertImage(imageFormat);
    sendText->setFocus();
}

void ChatWidget::saveChatInfo()
{
    if (chatText->document()->isEmpty()) {
        QMessageBox::information(NULL, tr("友情提醒"),
                    tr("聊天记录为空，无法保存。"), QMessageBox::Ok);
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                    tr("保存聊天记录"), tr("聊天记录"), tr("文本(*.txt);;All File(*.*)"));
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (!file.open(QFile::WriteOnly | QFile::Text)) {
                QMessageBox::warning(this,tr("保存文件"),
                    tr("无法保存文件 %1:\n %2").arg(fileName).arg(file.errorString()));
            }
            QTextStream outFile(&file);
            outFile << chatText->toPlainText();
        }
    }
}

void ChatWidget::clearChatInfo()
{
    chatText->clear();
}

void ChatWidget::sendSlot()
{
    if (sendText->toPlainText() == "") {
        QMessageBox::information(NULL, tr("友情提醒"), tr("请输入文字！"), QMessageBox::Ok);
    } else {
        sendMessage(Message);
    }
}
void ChatWidget::sure()
{
    if(camare->flag == 0)
    {
        sendMessage(videook);
        camare->flag = 1;
        timer->stop();
    }
}
void ChatWidget::closeCamara()
{
    // 停止读取数据
    timer->stop();

    // opencv 释放内存
    cvReleaseCapture(&cam);
}
void ChatWidget::closeEvent(QCloseEvent *event)
{
    sendMessage(Userleft);
}

