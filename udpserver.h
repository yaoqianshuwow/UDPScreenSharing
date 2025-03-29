// UDPServer.h
#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QEventLoop>
#include <QThread>
#include <QUdpSocket>
#include<QVector>
#include<QMutex>
class UDPServer : public QThread {
    Q_OBJECT

public:
    explicit UDPServer(QObject *parent = nullptr);
    int tempport;
    void run()override;

public slots:
    void startServer(int port);


signals:
    void pixReceived(const QImage &message);
    void pictureReceived( QPixmap &pixmap);
    void is();

private:
    QUdpSocket *udpsocket;
    QByteArray pix;
    QEventLoop* q;
    QVector<QByteArray>vec;
    QMutex mutex;

};

#endif // UDPSERVER_H
