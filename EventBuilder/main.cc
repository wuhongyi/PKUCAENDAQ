// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 6月 20 21:21:40 2024 (+0800)
// Last-Updated: 日 9月  8 15:32:23 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 2
// URL: http://wuhongyi.cn 

#include "event.hh"
#include "TString.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const char gVERSION[] = "Version: EventBuilder - 2024.09.08";

int main(int argc, char *argv[])
{
  std::cout << gVERSION << std::endl;
  std::cout << "Copyright @ Hongyi Wu (wuhongyi@qq.com/wuhongyi@pku.edu.cn)" << std::endl;
  if(argc != 2)
    {
      std::cout << "error(argc != 2)      " << argv[0] << "  [RunNnumber]" << std::endl;
      return 1;
    }

  TString RunNumber(argv[1]);
  int  runnumber = RunNumber.Atoi();

  event *tran = new event(runnumber);
  tran->Process();
  delete tran;

  return 0;
}

// 
// main.cc ends here
