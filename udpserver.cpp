// UDPServer.cpp
#include "UDPServer.h"
#include <QBuffer>
#include <QHostAddress>
#include <QImageReader>
#include <QPixmap>
#include <QThreadPool>
UDPServer::UDPServer(QObject *parent) : QThread(parent) {
    qDebug() << "main threadid:" << QThread::currentThreadId();

    pix = "";
}
void UDPServer::run()
{
    QByteArray datagram;
    q=new QEventLoop();
    udpsocket = new QUdpSocket();
    qDebug() << "son threadid:" << QThread::currentThreadId();

    //绑定
    if (udpsocket->bind(QHostAddress("192.168.198.1"), tempport)) {
        qDebug() << udpsocket->localAddress();
        qDebug() << "Server started on port" << tempport;
    } else {
        qDebug() << "Failed to start server";
        return;
    }


    //接收信息
    //QByteArray datagram;

    while(1){
        //datagram.reserve(4000);
        while (udpsocket->hasPendingDatagrams())
        {

            mutex.lock();
            if(udpsocket->pendingDatagramSize()!=datagram.size())
            {
                datagram.clear();
                datagram.resize(udpsocket->pendingDatagramSize());
            }


            //qDebug()<<udpsocket->pendingDatagramSize();
            QHostAddress sender;
            quint16 senderPort;

            // 读取数据报
            udpsocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);


            if ((QString::fromUtf8(datagram)).endsWith("\r\n")) {


                pix.append(datagram);

                pix.chop(2);


                QBuffer buffer(&pix);

                buffer.open(QIODevice::ReadOnly);
                QImageReader imageReader(&buffer);
                QImage image = imageReader.read();
                qDebug()<<pix.size();

                datagram.reserve(1024);

                if (!image.isNull()) {
                    qDebug() << tempport << "is not empty!";
                    emit pixReceived(image);

                }else{
                    qDebug() << tempport << "is empty!";
                }

                pix="";
            }
            else{

                pix.append(datagram);
                //qDebug()<<pix.size();
            }
            mutex.unlock();
        }
    }
    //q = new QEventLoop();
    q->exec();
}

void UDPServer::startServer(int port)
{
    tempport=port;
}

