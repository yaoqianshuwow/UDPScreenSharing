#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QPixmap>
#include <QMainWindow>
#include<udpserver.h>
#include<QThreadPool>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SendClearButton_clicked();
    void on_ClearButton_clicked();
    // void displaypix(const QPixmap &message) ;
    // void displayPictureInfo(const QPixmap pixmap);
    // void displaypixis();
    void on_fillwindowaction_triggered();
    // void presseventsolt(int x,int y);
    // void releaseeventsolt(int x,int y);
    // void moveeventsolt(int x,int y);
    //void w_keysolt();
private:
    Ui::MainWindow *ui;
    int threadsize;
    UDPServer *server;
    QThread *serverThread;


};
#endif // MAINWINDOW_H
