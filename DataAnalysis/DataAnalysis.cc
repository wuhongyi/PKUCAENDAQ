// DataAnalysis.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 5月 30 13:16:46 2025 (+0900)
// Last-Updated: 六 1月 10 21:14:27 2026 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 16
// URL: http://wuhongyi.cn 

#include "DataAnalysis.hh"

#include "UserDefine.hh"
#include "TMath.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DataAnalysis::Init()
{
  if(ipt == NULL) return;
  ipt->SetBranchAddress("event", &br_event);

  benchmark = new TBenchmark;
  
  // init TH1/TH2

  


}

void DataAnalysis::Loop(TTree *opt_)
{
  if(opt_ == NULL) return;

  opt = opt_;    
  BranchOpt();
  Long64_t TotalEntry = ipt->GetEntries();

  benchmark->Start("dataana");//计时开始
  
  for(Long64_t jentry = 0; jentry  < TotalEntry; jentry++)
    {
      ipt->GetEntry(jentry);
      // clear vector for new event data
      // vref.clear();
      vge.clear();
      vlabr.clear();
      vsi.clear();

      vsi1a.clear();
      vsi1b.clear();
      vsi2a.clear();
      vsi2b.clear();
      vsi3a.clear();
      vsi3b.clear();

      

      for(int i = 0; i < br_event->size(); i++) 
	{
	  int flag = (*br_event)[i].det;
	  det.det = (*br_event)[i].det;
	  det.id = (*br_event)[i].id;
	  if((*br_event)[i].fw == 4)
	    det.raw = (*br_event)[i].energyxia;
	  else
	    det.raw = (*br_event)[i].energy;
	  det.e = (*br_event)[i].e;
	  
	  det.ts = (*br_event)[i].ts;

	  
	 
	  det.subts = 0.0;
	  if((*br_event)[i].fw == 4)//FDK
	    {
	      if((*br_event)[i].info == 1)
		det.subts = (*br_event)[i].cfdxia;
	    }
	  else if((*br_event)[i].fw == 2)//PSD
	    {
	      if((*br_event)[i].sr == 125)
		{
		  det.subts = (*br_event)[i].finets/1024.0*8;
		}
	      else if((*br_event)[i].sr == 500)
		{
		  det.subts = (*br_event)[i].finets/1024.0*2;
		}
	      else if((*br_event)[i].sr == 1000)
		{
		  det.subts = (*br_event)[i].finets/1024.0;
		}
	    }


	  // FDK PSD
	  // psdcc  psdcostheta
	  

#ifdef WAVEFORM
	  det.analog0.clear();
	  if((*br_event)[i].samples > 0)
	    {
	      det.analog0.assign((*br_event)[i].analog0.begin(),(*br_event)[i].analog0.end());
	    }

	  det.waveform.clear();
	  if((*br_event)[i].nsamples > 0)
	    {
	      det.waveform.assign((*br_event)[i].waveform.begin(),(*br_event)[i].waveform.end());
	    }
#endif
	  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

	  
	  if(flag == 0 && det.id == 0) //ref for beam bursts
	    {
	      //vref.clear();
	      vsi1a.push_back(det);
	    }
	  
	  if(flag == 0 && det.id == 1)  
	    {
	      
	      vsi1b.push_back(det);
	    }
	  
	  if(flag == 4)
	    {
	      vsi2a.push_back(det);
	    }

	  if(flag == 5)
	    {
	      vsi2b.push_back(det);
	    }

	  if(flag == 2)
	    {
	      vsi3a.push_back(det);
	    }

	  if(flag == 3)
	    {
	      vsi3b.push_back(det);
	    }
	  


	}// br_event->size()

      //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

      // 

      // if(vref.size() > 0 && vppac.size() > 0 && (vls.size() > 0 || vli.size() > 0))
      //  	{
      //  	  for(int i = 0; i < vppac.size(); i++)
      //  	    {
      //  	      ppacref[vppac[i].id]->Fill((vppac[i].ts-vref[0].ts)/1000.0);
      //  
      //  	      double dt = vppac[i].ts+vppac[i].subts-vref[0].ts-vref[0].subts;
      //  	      double ne = TMath::Power(72.3*55/(dt), 2);
      //  	      if(dt > 0)
      //  		nppac[vppac[i].id]->Fill(ne, 1.0/nppac[vppac[i].id]->GetBinWidth(nppac[vppac[i].id]->FindBin(ne)));
      //  	      
      //  	    }
      //  	}

      if((vsi1a.size()>0 && vsi1b.size() > 0) ||  (vsi2a.size()>0 && vsi2b.size() > 0)  ||  (vsi3a.size()>0 && vsi3b.size() > 0)  )
	opt->Fill();




      // if(vref.size()>0 || vge.size()>0 || vlabr.size()>0 || vsi.size()>0) 
      // opt->Fill();

	   if((jentry) % 10000 == 0) 
	     {
	       std::cout << jentry << "/" << TotalEntry << "  process: " <<double(jentry)/TotalEntry << std::endl;
	     }
    }// loop for entry
  std::cout << std::endl;





  // TH1/TH2 write
  opt->Write();

  benchmark->Show("dataana");//计时结束并输出时间
}

void DataAnalysis::BranchOpt()
{
  br_event = 0;

  // opt->Branch("ref", &vref);
  // opt->Branch("ge", &ge);
  // opt->Branch("labr", &labr);
  // opt->Branch("si", &vsi);

  opt->Branch("si1a", &vsi1a);
  opt->Branch("si1b", &vsi1b);
  opt->Branch("si2a", &vsi2a);
  opt->Branch("si2b", &vsi2b);
  opt->Branch("si3a", &vsi3a);
  opt->Branch("si3b", &vsi3b);


  
}

// 
// DataAnalysis.cc ends here
