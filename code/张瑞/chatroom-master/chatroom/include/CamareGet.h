#ifndef CAMAREGET_H
#define CAMAREGET_H

#include <QLabel>

class QWidget;
class QImage;
class QTimer;

#include <highgui.h>  //包含opencv库头文件
#include <cv.h>

class CamaraGet : public QLabel
{
    Q_OBJECT

public:
    CamaraGet();
    ~CamaraGet();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void openCamara();      	// 打开摄像头
    void readFarme();       	// 读取当前帧信息
    void closeCamara();     	// 关闭摄像头

private:
    QTimer     *timer;
    CvCapture  *cam;		// 视频获取结构， 用来作为视频获取函数的一个参数
    IplImage   *frame;		// 申请IplImage类型指针，就是申请内存空间来存放每一帧图像
};

#endif // CAMAREGET_H
