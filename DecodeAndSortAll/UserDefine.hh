// UserDefine.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 2月 18 01:13:12 2024 (+0800)
// Last-Updated: 日 5月 25 21:28:34 2025 (+0900)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 25
// URL: http://wuhongyi.cn 

#ifndef _USERDEFINE_H_
#define _USERDEFINE_H_


// #define ONLYPHA
// #define ONLYPSD
// #define ONLYZLE
// #define ONLYSCOPE
// #define OPEN_DPP_FDK



#define ROOTFILEPATH "./"  //The path to generate the ROOT file
#define ROOTFILENAME "data"
#define TimesHist 3600  // second

#define TIMEBUFF 1000000000  //1s
#define PROCESSBUFF 0.9 //(0,1.0]
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define RAWFILEPATH "./"   //Path to the original binary
#define RAWFILENAME "data"                   //The file name of the original file
#define MODNUMBER 3   //Number of modules used in this crate
const unsigned short SamplingRate[MODNUMBER] = {500, 500, 500};//Specify the sampling rate of each modules separately; 125/500/1000 sampling rates; 0 to skip the module
const unsigned short Firmware[MODNUMBER] = {4, 4, 4};//DPP_PHA=0 DPP_ZLE=1 DPP_PSD=2 DPP_DAW=3 DPP_OPEN=4 Scope/SCOPE_OPEN=5

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......






#endif /* _USERDEFINE_H_ */
// 
// UserDefine.hh ends here














