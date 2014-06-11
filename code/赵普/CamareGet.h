#ifndef CAMAREGET_H
#define CAMAREGET_H

#include <QLabel>
#include <QtGui>


class QWidget;
class QImage;
class QTimer;

#include <highgui.h>  //包含opencv库头文件
#include <cv.h>

//QImage image;

class CamaraGet : public QLabel
{
    Q_OBJECT

public:
    CamaraGet();
    ~CamaraGet();

     void getRecvImage(QImage Image);    // 显示对方Image接口

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void openCamara();      	// 打开摄像头
    void setFrame();            // 获取当前帧信息
    QImage getSendImage();      // 当前Image传送接口

    void closeCamara();     	// 关闭摄像头

public:
    QTimer     *timer;          // 定时器信息
    QImage      image;
    QImage reImage;
     CvCapture  *cam;		// 视频获取结构， 用来作为视频获取函数的一个参数
       IplImage   *sendFrame;		// 申请IplImage类型指针，就是申请内存空间来存放待发送的每一帧图像
       //ChatWidget *chatwight;
     int flag;

private:
    //CvCapture  *cam;		// 视频获取结构， 用来作为视频获取函数的一个参数
    QImage sendImage;       // 自己摄像头抓取到的帧，转换为QImage格式
    QImage recvImage;       // 接受到对方摄像头的帧，转换为QImage格式



};

#endif // CAMAREGET_H
