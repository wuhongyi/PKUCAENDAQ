// HttpServer.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 5月 25 14:13:31 2024 (+0800)
// Last-Updated: 四 12月 11 20:32:28 2025 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 28
// URL: http://wuhongyi.cn 

#ifndef _HTTPSERVER_H_
#define _HTTPSERVER_H_

#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TSystem.h"
#include "TString.h"

#include "Global.hh"
#include "DeviceHandle.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HttpServer
{
public:
  static HttpServer* Instance(DeviceHandle *dev);
  
  void FillADC(unsigned short mod, unsigned short ch, double raw);
  void FillPSD(unsigned short mod, unsigned short ch, double raw, double p);
  void FillPSDCOS(unsigned short mod, unsigned short ch, double raw, double p);
  void FillRate(unsigned short mod, unsigned short ch, double ts);
  void FillCFD(unsigned short mod, unsigned short ch, unsigned short raw);

  void FillBL(unsigned short mod, unsigned short ch, int raw);
  void FillWAVEHIGH(unsigned short mod, unsigned short ch, int raw);
  
  void DrawWave0(unsigned short mod, unsigned short ch, unsigned short len, unsigned int *wave);
  void DrawWave1(unsigned short mod, unsigned short ch, unsigned short len, unsigned int *wave);

  void DrawWave(unsigned short mod, unsigned short ch, unsigned int len, unsigned int *wave);

  void ClearADC(unsigned short mod);
  void ClearPSD(unsigned short mod);
  void ClearPSDCOS(unsigned short mod);
  void ClearRATE(unsigned short mod);
  void ClearCFD(unsigned short mod);
  void ClearBL(unsigned short mod);
  void ClearWAVEHIGH(unsigned short mod);
  
protected:
  HttpServer(DeviceHandle *dev);
  virtual ~HttpServer();


  

private:
  TH1I *adc[MAXMODULENUM][MAXCHANNELNUM];
  TH2I *adc_ch[MAXMODULENUM];
  TH1I *rate[MAXMODULENUM][MAXCHANNELNUM];
  TH1I *cfd[MAXMODULENUM][MAXCHANNELNUM];
  TH2I *psd[MAXMODULENUM][MAXCHANNELNUM];
  TH2I *psdcos[MAXMODULENUM][MAXCHANNELNUM];
  TGraph *wave0[MAXMODULENUM][MAXCHANNELNUM];
  TGraph *wave1[MAXMODULENUM][MAXCHANNELNUM];

  TH2I *bl_ch[MAXMODULENUM];
  TH1I *wavehigh[MAXMODULENUM][MAXCHANNELNUM];

  
  THttpServer* serv;
  DeviceHandle *mDevice;

  static HttpServer *wuHttpServer;
};

#endif /* _HTTPSERVER_H_ */
// 
// HttpServer.hh ends here
