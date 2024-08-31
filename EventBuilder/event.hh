// event.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 6月 20 21:26:25 2024 (+0800)
// Last-Updated: 二 7月 23 18:34:47 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 2
// URL: http://wuhongyi.cn 

#ifndef _EVENT_H_
#define _EVENT_H_

#include "UserDefine.hh"
#include "TRandom.h"
#include "TString.h"
#include "TROOT.h"
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TBenchmark.h"

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>

typedef struct DATAEVENT
{
  Short_t      det;//探测器类型
  Short_t      id;//探测器编号

  UShort_t fw;
  UShort_t sr;

  Long64_t ts;
  UShort_t finets;

  UShort_t energy;//
  UShort_t energyshort;//

  double e;

  
} DATAEVENT;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class event
{
public:
  event(int run);
  virtual ~event();

  void Process();
  void InitEvent();
  void ProcessEntry();
  void EndEvent();

private:
  Short_t flagdet[24][64];
  Short_t flagdetid[24][64];
  double  calia0[24][64];
  double  calia1[24][64];
  double  calia2[24][64];


  DATAEVENT hit;
  std::vector<DATAEVENT> event_vec;

  bool flag;
  Long64_t inittime;
  Long64_t tsnow;
  
private:

  Int_t nevt;
  TBenchmark *benchmark;
  
  // TFile *file_in;
  // TTree *t_in;
  TChain *t_in;
  Long64_t TotalEntry;

  TFile *file_out;
  TTree *t_out;

  // branch
  TBranch *b_sr;
  TBranch *b_fw;
  TBranch *b_mod;
  TBranch *b_ch;
  TBranch *b_ts;
  TBranch *b_finets;
  TBranch *b_flagslow;
  TBranch *b_flagshigh;
  TBranch *b_energy;
  TBranch *b_energyshort;
  TBranch *b_samples;
  TBranch *b_analog0;
  TBranch *b_analog1;
  TBranch *b_digital0;
  TBranch *b_digital1;
  TBranch *b_digital2;
  TBranch *b_digital3;
  TBranch *b_analogtypes;
  TBranch *b_digitaltypes;
  TBranch *b_triggerid;
  TBranch *b_nsamples;
  TBranch *b_waveform;


  //leaf
  UShort_t fw;
  UShort_t sr;
  
  Long64_t ts;
  UShort_t ch;
  UShort_t mod;
  
  UShort_t finets;
  UShort_t flagslow;
  UShort_t flagshigh;
  
  UShort_t energy;//
  UShort_t energyshort;//
  
  UShort_t samples;
  int analog0[100000];
  int analog1[100000];
  bool digital0[100000];
  bool digital1[100000];
  bool digital2[100000];
  bool digital3[100000];
  UShort_t analogtypes[2];
  UShort_t digitaltypes[4];
  
  unsigned int triggerid;
  int nsamples;
  UShort_t waveform[100000];
  
};


#endif /* _EVENT_H_ */
// 
// event.hh ends here
