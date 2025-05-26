// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 2月 18 01:19:10 2024 (+0800)
// Last-Updated: 日 5月 25 16:10:30 2025 (+0900)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 7
// URL: http://wuhongyi.cn 

#include "UserDefine.hh"
#include "r2root.hh"

#include "TString.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const char gVERSION[] = "Version: DecodeAndSortAll - 2025.05.25";

int main(int argc, char *argv[])
{
  std::cout << gVERSION << std::endl;
  std::cout << "Copyright @ Hongyi Wu (wuhongyi@qq.com/wuhongyi@pku.edu.cn)" << std::endl;

  if(argc != 2)
    {
      std::cout<<"error(argc != 2)      "<<argv[0]<<" [RunNumber]"<<std::endl;
      return 0;
    }

  
  int runnumber;
  TString RunNumber(argv[1]);
  runnumber = RunNumber.Atoi();
  
  r2root *r2r = new r2root(runnumber);
  r2r->Process();
  delete r2r;
  
  return 0;
}


// 
// main.cc ends here
