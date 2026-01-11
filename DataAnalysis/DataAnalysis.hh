// DataAnalysis.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 5月 30 13:13:11 2025 (+0900)
// Last-Updated: 六 1月 10 21:11:09 2026 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 6
// URL: http://wuhongyi.cn 

#ifndef _DATAANALYSIS_H_
#define _DATAANALYSIS_H_

#include "UserDefine.hh"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom3.h"
#include "TCutG.h"
#include "TBenchmark.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef struct DATAEVENT
{
  Short_t det;//探测器类型
  Short_t id;//探测器编号

  UShort_t fw;
  UShort_t sr;

  Long64_t ts;
  UShort_t finets;

  UShort_t energy;//
  UShort_t energyshort;//

  // FDK
  UShort_t info;
  UShort_t energyxia;
  bool flagcfd;
  double cfdxia;
  bool flagpsd;
  double psdcc;
  double psdcostheta;

  //cal
  double e;

#ifdef WAVEFORM
  UShort_t samples;
  std::vector<int> analog0;

  unsigned int nsamples;
  std::vector<UShort_t> waveform;
#endif

} DATAEVENT;

typedef struct dets
{
  Short_t det;
  Short_t id;
  Double_t e;
  Double_t raw;
  Long64_t ts;
  Double_t subts;

#ifdef WAVEFORM
  std::vector<float> analog0;

  std::vector<float> waveform;
#endif

  // add info

  
} dets;



class DataAnalysis
{
 public:
 
  DataAnalysis()
  {
    ipt = NULL;
    opt = NULL;
  }
  DataAnalysis(TTree *ipt_)
  {
    ipt = ipt_;
    Init();
  }

  void Init();
  void Loop(TTree *opt_);
  void BranchOpt();

private:
  std::vector<DATAEVENT>* br_event;
  TRandom3 gr;
  TBenchmark *benchmark;
  TTree *ipt;
  TTree *opt;

  // --------------------------------------------
  
  // 0 ref, 



  TCutG *psd[4];

  

  dets det;
  std::vector<dets> vref, vge, vlabr, vsi;
  std::vector<dets> vsi1a, vsi1b, vsi2a, vsi2b, vsi3a, vsi3b;
};

#endif /* _DATAANALYSIS_H_ */

// 
// DataAnalysis.hh ends here
