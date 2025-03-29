#include "ouropenglwidget.h"


unsigned int VBO, VAO,EBO;
//unsigned int shaderProgram;
QImage image;


//三次绑定 1vao vbo 2shader 纹理
float vertices[] = {
    // positions      // colors        // texture coords
    1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
    1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
    -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
};


unsigned int indices[] = { // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3 // second triangle
};


OurOpenglWidget::OurOpenglWidget(QWidget *parent) : QOpenGLWidget(parent)
{

 //grabMouse(); // 捕获鼠标
//releaseMouse();
}

OurOpenglWidget::~OurOpenglWidget()
{
    makeCurrent();
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&VAO);
    doneCurrent();


}

void OurOpenglWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //创建VBO和VAO对象，并赋予ID
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //绑定VBO和VAO对象
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);



    //绑定
    //为当前绑定到target的缓冲区对象创建一个新的数据存储。
    //如果data不是NULL，则使用来自此指针的数据初始化数据存储
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //告知显卡如何解析缓冲里的属性值
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);



    //解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    bool success;
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shades/shape.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shades/shape.frag");
    success=shaderProgram.link();
    if(!success)
        qDebug()<<"ERR:"<<shaderProgram.log();




    //indices调整顺序
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 获取屏幕截图
    QScreen *screen = QApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0);
    image = pixmap.toImage();
    image= image.scaled(width()*5, height()*5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    texturecamer=new QOpenGLTexture(image.mirrored());
    // 设置纹理过滤模式为最近邻过滤
    // texturecamer->setMinificationFilter(QOpenGLTexture::Nearest);
    // texturecamer->setMagnificationFilter(QOpenGLTexture::Nearest);



    shaderProgram.bind();
    shaderProgram.setUniformValue("texturecamer",0);



    glBindVertexArray(0);
}
#include<QDebug>
void OurOpenglWidget::resizeGL(int w, int h)
{
    qDebug()<<w<<h;
}

void OurOpenglWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    shaderProgram.bind();
    glBindVertexArray(VAO);
    texturecamer->bind(0);


    //glDrawArrays(GL_TRIANGLES, 0, 4);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

}

void OurOpenglWidget::pixshow(const QImage &pixmap)
{


    texturecamer=new QOpenGLTexture(pixmap.mirrored());
   repaint();

}


