// ReadoutThread.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 6月 22 09:30:18 2022 (+0800)
// Last-Updated: 六 9月  7 15:37:40 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 50
// URL: http://wuhongyi.cn 

#ifndef _READOUTTHREAD_H_
#define _READOUTTHREAD_H_

#include "Global.hh"

#include <QVector>
#include <QFile>
#include <QTextStream>
//#include <QWaitCondition>
#include <QThread>
//#include <QMutex>
#include <QElapsedTimer>

// #include <fcntl.h>
// #include <unistd.h>
// #include <sys/mman.h>
// #include <sys/stat.h>
// #include <semaphore.h>

#include <iostream>
#include <cstring>
#include <string>
#ifdef RECODESHA256
#include <openssl/opensslv.h>
#if OPENSSL_VERSION_NUMBER < 0x30000000L
#include <openssl/sha.h>
#else
#include <openssl/sha.h>
#include <openssl/evp.h>
#endif
#endif

//#if OPENSSL_VERSION_NUMBER < 0x30000000L
//#else
//#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MainWindow;
class DeviceHandle;

class ReadoutThread : public QThread
{
  Q_OBJECT
  
public:
  ReadoutThread(MainWindow *w, DeviceHandle *dev);
  virtual ~ReadoutThread();

  bool IsRunning() {return mRunning;}

  void startRun();

signals:

  void OnlineDebugPHA(event_pha *evt_pha);
  void OnlineDebugPSD(event_psd *evt_psd);
  void OnlineDebugZLE(event_zle *evt_zle);
  void OnlineDebugScope(event_scope *evt_scope);
  void OnlineDebugOPEN(event_open *evt_open);

					       
public slots:
  
  void stopRun();

  void GetOnlineDebug(unsigned short mod, unsigned short ch);
  
protected:
  
  void run();
  
private:
  
  MainWindow *mMainWindow = nullptr;
  DeviceHandle *mDevice = nullptr;
  
  bool mDoRead = false;
  bool mSaving = false;// save to file
  bool mRequestStop = false;

  bool mRunning = false;
  
  QVector<QFile*> mSaveFile;
  QVector<QTextStream *> outFile;
  int runno;

  unsigned int buff[MAXMODULENUM][BUFFLENGTHSCOPE];//TODO length
  int buffid[MAXMODULENUM];
  unsigned long filesize[MAXMODULENUM];

  unsigned int buffevent[BUFFLENGTHSCOPE];//TODO length
  int buffeventid;
  
  QString folderfile;

  // signal from 
  bool onlinedebug;
  unsigned short onlinedebugmod;
  unsigned short onlinedebugch;

  
#ifdef DECODERONLINE
  
  int    shmfd_dec;  // shared memory id
  unsigned char *shmptr_dec;// pointer to shm

  
  void InitDecoderOnline();
  bool   fdecoder;
#endif

#ifdef RECODESHA256
#if OPENSSL_VERSION_NUMBER < 0x30000000L
  SHA256_CTX sha256_ctx[MAXMODULENUM];
  unsigned char SHA256result[MAXMODULENUM][32];
#else
  EVP_MD_CTX *sha256_ctx[MAXMODULENUM];
  unsigned char SHA256result[MAXMODULENUM][32];
#endif
#endif

  QElapsedTimer timerrun;
  int runtime;
  
private:

  void InitFiles();
  void CloseFile();
  void ReadDataFromModules(unsigned int thres, bool endofrun);

  void FlushBuffer(unsigned short mod);


  struct event_pha *evt_pha, *evt_pha_tmp;
  struct event_psd *evt_psd, *evt_psd_tmp;
  struct event_zle *evt_zle, *evt_zle_tmp;
  struct event_scope *evt_scope, *evt_scope_tmp;
  struct event_open *evt_open, *evt_open_tmp;

 
};


#endif /* _READOUTTHREAD_H_ */
// 
// ReadoutThread.hh ends here