#include "CamareGet.h"

CamaraGet::CamaraGet()
{

    cam   = NULL;
    flag  =1;
    timer = new QTimer(this);

    // 时间到，读取当前摄像头信息
    connect(timer, SIGNAL(timeout()), this, SLOT(setFrame()));
}

CamaraGet::~CamaraGet()
{
    closeCamara();
}

void CamaraGet::openCamara()
{
    if (!this) {
        return;
    }

    // 打开摄像头，从摄像头中获取视频
    cam = cvCreateCameraCapture(0);
    // 开始计时，超时则发出timeout()信号
    timer->start(80);
}

void CamaraGet::setFrame()
{
    // 从摄像头中抓取并返回每一帧
    sendFrame = cvQueryFrame(cam);
    // rgb转成bgr
    cvConvertImage(sendFrame, sendFrame, CV_CVTIMG_SWAP_RB);

    // 将获取到的帧，转换为QImage格式
     recvImage = QImage ((const uchar*)sendFrame->imageData, sendFrame->width, sendFrame->height, QImage::Format_RGB888);
    image = recvImage;
    //image.save("kk.png");
    this->setPixmap(QPixmap::fromImage(recvImage));
}
QImage CamaraGet::getSendImage()
{
    // 返回要发送的图像
    return sendImage;
}

void CamaraGet::getRecvImage(QImage Image)
{
    // 将对方传来的Image赋值给recvImage
    recvImage = Image;
    // 将对方传来图片显示到label上
    this->setPixmap(QPixmap::fromImage(recvImage));
}

void CamaraGet::closeCamara()
{
    // 停止读取数据

    timer->stop();

    // opencv 释放内存
    cvReleaseCapture(&cam);
    flag = 0;

}

void CamaraGet::closeEvent(QCloseEvent *event)
{
    int res = QMessageBox::question(NULL, this->windowTitle(),
        tr("是否退出视频？"), QMessageBox::Yes | QMessageBox::No);
    if (res == QMessageBox::Yes) {
        event->accept();
        closeCamara();
    } else{
        event->ignore();
    }
}
