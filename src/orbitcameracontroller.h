#ifndef ORBITCAMERACONTROLLER_H
#define ORBITCAMERACONTROLLER_H

#include "cameracontroller.h"

class OrbitCameraController : public CameraController
{
public:
    OrbitCameraController(Camera *camera) : CameraController(camera) {}
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    
protected:
    void updateViewMatrix();
    
    QPoint oldMousePos_;
    bool mouseDragging_ = false;
    
    float angleX_ = 0;
    float angleY_ = 0;
    float zoom_ = 5;
};

#endif // ORBITCAMERACONTROLLER_H
