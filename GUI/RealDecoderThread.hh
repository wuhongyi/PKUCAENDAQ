// RealDecoderThread.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 3月 12 21:04:39 2023 (+0800)
// Last-Updated: 日 9月  8 10:33:39 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 21
// URL: http://wuhongyi.cn 

#ifndef _REALDECODERTHREAD_H_
#define _REALDECODERTHREAD_H_

#include "Global.hh"

#include <QVector>
#include <QFile>
#include <QTextStream>
//#include <QWaitCondition>
#include <QThread>
//#include <QMutex>
#include <QElapsedTimer>

#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MainWindow;
class DeviceHandle;

class RealDecoderThread : public QThread
{
  Q_OBJECT
  
public:
  RealDecoderThread(MainWindow *w, DeviceHandle *dev);
  virtual ~RealDecoderThread();

protected:
  
  void run();


private:
  
  MainWindow *mMainWindow = nullptr;
  DeviceHandle *mDevice = nullptr;

  unsigned int buff[BUFFLENGTHSCOPE];//TODO length
  int buffid;
  int runno[MAXMODULENUM], runno_d[MAXMODULENUM];

  
  unsigned int tmpbuff[6];
  int tmpid;
  unsigned int tmpwave[BUFFLENGTHSCOPE];//TODO length
  
  uint64_t timestamp;
  unsigned short finets;
  unsigned int samples;
  unsigned short ch;
  unsigned short mod;
  uint16_t energy;//PHA PSD
  uint16_t energy_short;// PSD


  bool firstbuffhit[MAXMODULENUM][MAXCHANNELNUM];
};

#endif /* _REALDECODERTHREAD_H_ */
// 
// RealDecoderThread.hh ends here








