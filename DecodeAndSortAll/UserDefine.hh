// UserDefine.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 2月 18 01:13:12 2024 (+0800)
// Last-Updated: 二 8月 27 11:22:16 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 18
// URL: http://wuhongyi.cn 

#ifndef _USERDEFINE_H_
#define _USERDEFINE_H_


// #define ONLYPHA
// #define ONLYPSD
// #define ONLYZLE
// #define ONLYSCOPE


#define ROOTFILEPATH "./"  //The path to generate the ROOT file
#define ROOTFILENAME "data"
#define TimesHist 3600  // second

#define TIMEBUFF 1000000000  //1s
#define PROCESSBUFF 0.9 //(0,1.0]
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define RAWFILEPATH "/home/wuhongyi/data/"   //Path to the original binary
#define RAWFILENAME "data"                   //The file name of the original file
#define MODNUMBER 3   //Number of modules used in this crate
const unsigned short SamplingRate[MODNUMBER] = {125, 0, 500};//Specify the sampling rate of each modules separately; 125/500/1000 sampling rates; 0 to skip the module
const unsigned short Firmware[MODNUMBER] = {0, 0, 2};//DPP_PHA=0 DPP_ZLE=1 DPP_PSD=2 DPP_DAW=3 OPEN=4 Scope=5



#endif /* _USERDEFINE_H_ */
// 
// UserDefine.hh ends here














