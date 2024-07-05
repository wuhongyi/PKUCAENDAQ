// r2root.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 2月 18 01:22:59 2024 (+0800)
// Last-Updated: 四 7月  4 23:55:37 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 7
// URL: http://wuhongyi.cn 

#ifndef _R2ROOT_H_
#define _R2ROOT_H_

#include "decoder.hh"

#include "TString.h"
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TBenchmark.h"
#include "TH1.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h> 
#include <cstring>
#include <string>
#include <map>
#include <vector>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define MAXMODULENUMBER 100

struct eventdata
{
  Long64_t tsflag;
  
  UShort_t fw;//
  UShort_t sr;//
  
  Long64_t ts;//
  UShort_t ch;//
  UShort_t mod;//
  
  UShort_t finets;//
  UShort_t flagslow;//
  UShort_t flagshigh;//
  
  UShort_t energy;//
  UShort_t energyshort;//
  
  UShort_t samples;//
  int *analog0;
  int *analog1;
  bool *digital0;
  bool *digital1;
  bool *digital2;
  bool *digital3;
  uint8_t analogtype[2];//
  uint8_t digitaltype[4];//
  
  unsigned int triggerid;
  int nsamples;
  UShort_t *waveform;
};


class r2root
{
public:
  r2root(int run);
  virtual ~r2root();

  void Process();
  

  
private:  
  bool IsFileExists(const char *name);//判断文件是否存在

  
private:  
  decoder *rawdec;
  bool  havedata[MAXMODULENUMBER];//如果还有数据则为true
  int   flagcrate[MAXMODULENUMBER];
  Int_t nevt;
 

  TFile *file;
  TTree *t;
  TBenchmark *benchmark;
  int Run;
  TString FileName;

  std::map<Long64_t,eventdata> sortdata;
  std::map<Long64_t,eventdata>::iterator itkey;

  Long64_t flagkey;
  eventdata mapvalue;

private:
  Long64_t tsflag;
  
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
  int analog0[10000];
  int analog1[10000];
  bool digital0[10000];
  bool digital1[10000];
  bool digital2[10000];
  bool digital3[10000];
  uint8_t analogtype[2];
  uint8_t digitaltype[4];

  UShort_t analogtypes[2];
  UShort_t digitaltypes[4];
  
  unsigned int triggerid;
  int nsamples;
  UShort_t waveform[10485760];
};

#endif /* _R2ROOT_H_ */
// 
// r2root.hh ends here
