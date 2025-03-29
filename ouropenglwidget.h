#ifndef OUROPENGLWIDGET_H
#define OUROPENGLWIDGET_H

#include <QWidget>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include<QOpenGLFunctions>
#include<QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QApplication>
#include <QScreen>
#include <QOpenGLTexture>
#include <QImage>
#include<QMouseEvent>
class OurOpenglWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit OurOpenglWidget(QWidget *parent = nullptr);
    enum Shape{None,Rect,Circle,Triangle};
    ~OurOpenglWidget();
signals:
    // void pressevent(int x,int y);
    // void releaseevent(int x,int y);
    // void moveevent(int x,int y);
    //void w_keysolt();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    Shape m_shape;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLTexture * texturecamer;

public slots:
    void pixshow(const QImage &pixmap);
    // void mousePressEvent(QMouseEvent *event);
    // void mouseMoveEvent(QMouseEvent *event);
    // void mouseReleaseEvent(QMouseEvent *event);
private:
    qint64 lastMoveTime;
};

#endif // OUROPENGLWIDGET_H
