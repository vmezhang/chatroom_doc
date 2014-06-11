#include <QtGui>

#include "CamareGet.h"

CamaraGet::CamaraGet()
{
    cam   = NULL;
    timer = new QTimer(this);

    // 时间到，读取当前摄像头信息
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));
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

void CamaraGet::readFarme()
{
    // 从摄像头中抓取并返回每一帧
    frame = cvQueryFrame(cam);

    // rgb转成bgr
    cvConvertImage(frame, frame, CV_CVTIMG_SWAP_RB);

    // 将抓取到的帧，转换为QImage格式
    QImage image((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888);

    //将图片显示到label上
    this->setPixmap(QPixmap::fromImage(image));
}

void CamaraGet::closeCamara()
{
    // 停止读取数据
    timer->stop();

    // opencv 释放内存
    cvReleaseCapture(&cam);
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
