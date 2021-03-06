//
// Created by jianping on 18-5-24.
//

#ifndef DATACOLLECTOR_RAWDATASAVER_H
#define DATACOLLECTOR_RAWDATASAVER_H
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QTextStream>
#include <QCoreApplication>
#include <QtCore/QTimer>
#include <QObject>
#include <QThread>
#include <QString>
#include <QDebug>
#include <memory>
#include "sys/time.h"
#include "iostream"

class rawDataSaver {
public:
    rawDataSaver(std::string port, int baudRate=115200, uint32_t timeOut=100){
        qserial = std::make_shared<QSerialPort>();
        qserial->setPortName(port.c_str());
        if (qserial->open(QIODevice::ReadWrite)) {
            //qserial->setBaudRate(QSerialPort::Baud115200);
            qserial->setBaudRate(baudRate);
            qserial->setDataBits(QSerialPort::Data8);
            qserial->setParity(QSerialPort::NoParity);
            qserial->setStopBits(QSerialPort::OneStop);
            qserial->setFlowControl(QSerialPort::NoFlowControl);

            qDebug("create IMU from port : %s \n",port.c_str());
        } else{
            qDebug("fail to create IMU from port : %s \n",port.c_str());
            //LOG(ERROR)<<"fail to create IMU from port :" <<port << "\n";
        }
        m_timeOut = timeOut;
    }

    void readData(QByteArray& b_str){
        while (waitFor(1)){
            b_str = qserial->readAll();
        }
    }
private:
    bool waitFor(int size = 1)
    {
        timeval tv_start;;
        gettimeofday(&tv_start,NULL);
        long diffTime(0);//ms

        while (qserial->bytesAvailable()<size)
        {
            qserial->waitForReadyRead(10);
            //std::cout<<"ready read "<<qserial->bytesAvailable()<<std::endl;
            timeval tv_now;
            gettimeofday(&tv_now,NULL);
            diffTime = 1000*(tv_now.tv_sec-tv_start.tv_sec)+(tv_now.tv_usec-tv_start.tv_usec)/1000;
            if(diffTime > size*m_timeOut)
            {
                //std::cout<<"time out\n";
                return false;// time out
            }
        }
        return true;
    }

    //serial
    std::shared_ptr<QSerialPort> qserial;
    int m_timeOut;
    bool bconfig;
};


#endif //DATACOLLECTOR_RAWDATASAVER_H
