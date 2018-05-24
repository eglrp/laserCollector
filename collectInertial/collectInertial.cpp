//
// Created by jianping on 18-5-24.
//

#include <iostream>
#include <string.h>
#include <fstream>
#include <common.hpp>
#include <rawDataSaver.h>
#include <QtCore>




int main(int argc, char** argv)
{
    QCoreApplication application(argc, argv);
    //load sysconfig
    common::sysConfig config;
    if(!common::readConfig(config))
    {
        std::cout<<"read config failed\n";
        return -1;
    }
    std::cout<<"the inertial folder is :"<<config.inertialPath<<std::endl;

    std::ofstream ofs(config.inertialPath,std::ios_base::out|std::ios_base::binary);

    rawDataSaver saver(config.IMUport);
    while (1){
        QByteArray b_str;
        saver.readData(b_str);

        ofs.write(b_str.data(),b_str.size());
    }

//    IMU::InertialDivice device(config.IMUport);
//    unsigned char messageID;
//    std::vector<unsigned char> data;
//    std::ofstream ofs(config.inertialPath,std::ios_base::out|std::ios_base::binary);
//    int count =0;
//    while(1)
//    {
//        if(!device.read_msg(messageID,data))
//        {
//            continue;
//        }
//        timeval tv;
//        gettimeofday(&tv,NULL);
//        device.parse_MTData2(data);
//        ofs << device.m_inertialData;
//        std::cout<<device.m_inertialData.accZ<<std::endl;
//        std::cout<<device.m_inertialData.accY<<std::endl;
//        std::cout<<device.m_inertialData.accX<<std::endl;
//
//        count ++;
//        if(count == 400)
//        {
//            ofs.flush();
//        }
//    }
    application.exec();
    return 0;
}