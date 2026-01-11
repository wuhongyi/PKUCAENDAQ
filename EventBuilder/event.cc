// event.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 6月 20 21:26:32 2024 (+0800)
// Last-Updated: 六 1月 10 21:03:29 2026 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 13
// URL: http://wuhongyi.cn 

#include "event.hh"
#include "UserDefine.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

event::event(int run)
{
  flag = false;
  nevt = 0;

  
  for (int i = 0; i < MAXMODULENUMBER; ++i)
    for (int j = 0; j < MAXCHANNELNUMBER; ++j)
      {
	flagdet[i][j] = -1;
	flagdetid[i][j] = -1;
	calia0[i][j] = 0.0;
	calia1[i][j] = 0.0;
	calia2[i][j] = 0.0;
      }



  std::ifstream readtxt;
  readtxt.open("par.dat");
  if(!readtxt.is_open())
    {
      std::cout<<"can't open file."<<std::endl;
    }

  std::string str_tmp;
  getline(readtxt,str_tmp);


  Short_t mod_tmp, ch_tmp;
  Short_t det_tmp, id_tmp;
  Double_t a0_tmp, a1_tmp, a2_tmp;
  while(!readtxt.eof())
    {
      readtxt >> mod_tmp >> ch_tmp >> det_tmp >> id_tmp >> a0_tmp >> a1_tmp >> a2_tmp;
      if(readtxt.eof()) break;
      flagdet[mod_tmp][ch_tmp] = det_tmp;
      flagdetid[mod_tmp][ch_tmp] = id_tmp;
      calia0[mod_tmp][ch_tmp] = a0_tmp;
      calia1[mod_tmp][ch_tmp] = a1_tmp;
      calia2[mod_tmp][ch_tmp] = a2_tmp;
      
      std::cout << flagdet[mod_tmp][ch_tmp] << "  " << flagdetid[mod_tmp][ch_tmp] << "  " << calia0[mod_tmp][ch_tmp] << "  " << calia1[mod_tmp][ch_tmp] << "  " << calia2[mod_tmp][ch_tmp] << "  " << std::endl;
    }
  readtxt.close();  

  
  t_in = new TChain("tree");
#ifdef WAVEFORM
  t_in->Add(TString::Format("%s%s_%04d*_wave.root",RAWFILEPATH,RAWFILENAME,run).Data());
  t_in->Add(TString::Format("%s%s_%04d*_wave_*.root",RAWFILEPATH,RAWFILENAME,run).Data());
#else
  t_in->Add(TString::Format("%s%s_%04d*_notwave.root",RAWFILEPATH,RAWFILENAME,run).Data());
#endif

  t_in->SetBranchAddress("sr", &sr, &b_sr);
  t_in->SetBranchAddress("fw", &fw, &b_fw);
  t_in->SetBranchAddress("mod", &mod, &b_mod);
  t_in->SetBranchAddress("ch", &ch, &b_ch);
  t_in->SetBranchAddress("ts", &ts, &b_ts);
  t_in->SetBranchAddress("finets", &finets, &b_finets);
  t_in->SetBranchAddress("flagslow", &flagslow, &b_flagslow);
  t_in->SetBranchAddress("flagshigh", &flagshigh, &b_flagshigh);
  t_in->SetBranchAddress("energy", &energy, &b_energy);
  t_in->SetBranchAddress("energyshort", &energyshort, &b_energyshort);
  t_in->SetBranchAddress("samples", &samples, &b_samples);
#ifdef WAVEFORM
  t_in->SetBranchAddress("analog0", &analog0, &b_analog0);
  //t_in->SetBranchAddress("analog1", &analog1, &b_analog1);
  //t_in->SetBranchAddress("digital0", &digital0, &b_digital0);
  //t_in->SetBranchAddress("digital1", &digital1, &b_digital1);
  //t_in->SetBranchAddress("digital2", &digital2, &b_digital2);
  //t_in->SetBranchAddress("digital3", &digital3, &b_digital3);
  //t_in->SetBranchAddress("analogtypes", &analogtypes, &b_analogtypes);
  //t_in->SetBranchAddress("digitaltypes", &digitaltypes, &b_digitaltypes);
#endif
  t_in->SetBranchAddress("triggerid", &triggerid, &b_triggerid);
  t_in->SetBranchAddress("nsamples", &nsamples, &b_nsamples);
#ifdef WAVEFORM
  t_in->SetBranchAddress("waveform", &waveform, &b_waveform);
#endif
  t_in->SetBranchAddress("info", &info, &b_info);
  t_in->SetBranchAddress("energyxia", &energyxia, &b_energyxia);
  t_in->SetBranchAddress("flagcfd", &flagcfd, &b_flagcfd);
  t_in->SetBranchAddress("cfdxia", &cfdxia, &b_cfdxia);
  t_in->SetBranchAddress("flagpsd", &flagpsd, &b_flagpsd);
  t_in->SetBranchAddress("psdcc", &psdcc, &b_psdcc);
  t_in->SetBranchAddress("psdcostheta", &psdcostheta, &b_psdcostheta);


  
  TotalEntry = t_in->GetEntries();
  
#ifdef WAVEFORM
  file_out = new TFile(TString::Format("%s%s_%04d_W%d_wave.root",ROOTFILEPATH,ROOTFILENAME,run,EVENTTIMEWINDOWSWIDTH).Data(),"RECREATE");
#else
  file_out = new TFile(TString::Format("%s%s_%04d_W%d_notwave.root",ROOTFILEPATH,ROOTFILENAME,run,EVENTTIMEWINDOWSWIDTH).Data(),"RECREATE");
#endif
  t_out = new TTree("tree", "GDDAQ event data.");
  t_out->Branch("event", &event_vec);


  benchmark = new TBenchmark;
}

event::~event()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void event::Process()
{
  benchmark->Start("event");//计时开始
  // TotalEntry = 1000000;
  for (Long64_t entry = 0; entry < TotalEntry; ++entry)
    {
      if(entry % 10000 == 0)
	{
	  std::cout << "\r" << "Total: " << TotalEntry << "  |  Entry: " << entry << "  |  Event: " << nevt+1;
	  std::cout << std::flush;
	}
      
      // file_in->cd();
      t_in->GetEvent(entry);

      if(flagdet[mod][ch] < 0) continue;
      
      if(flag)
	{
	  tsnow = ts;

	  if(TMath::Abs(tsnow-inittime) <= Long64_t(EVENTTIMEWINDOWSWIDTH))
	    {
	      ProcessEntry();
	    }
	  else
	    {
	      EndEvent();
	      InitEvent();
	    }
	}
      else
	{//event header
	  InitEvent();
	  flag = true;
	}

    }

  std::cout << std::endl;

  file_out = t_out->GetCurrentFile();
  file_out->cd();
  t_out->Write();
  file_out->Close();

  benchmark->Show("event");//计时结束并输出时间
}



void event::InitEvent()
{
  inittime = ts;

  ProcessEntry();
}

void event::ProcessEntry()
{
  double rawch;
 
  if(fw == 4)
    rawch = gRandom->Rndm()+energyxia;
  else
    rawch = gRandom->Rndm()+energy;

  
  hit.det = flagdet[mod][ch];
  hit.id = flagdetid[mod][ch];
  hit.sr = sr;
  hit.fw = fw;
  hit.ts = ts;
  hit.finets = finets;

  hit.energy = energy;
  hit.energyshort = energyshort;

  hit.info = info;
  hit.energyxia = energyxia;
  hit.flagcfd = flagcfd;
  hit.cfdxia = cfdxia;
  hit.flagpsd = flagpsd;
  hit.psdcc = psdcc;
  hit.psdcostheta = psdcostheta;
  
  
  hit.e = calia0[mod][ch]+calia1[mod][ch]*rawch+calia2[mod][ch]*rawch*rawch;
  

#ifdef WAVEFORM
  hit.samples = samples;
  hit.analog0.clear();
  if(hit.samples > 0)
    {
      hit.analog0.insert(hit.analog0.begin(), analog0, analog0+hit.samples);
    }

  hit.nsamples = nsamples;
  hit.waveform.clear();
  if(hit.nsamples > 0)
    {
      hit.waveform.insert(hit.waveform.begin(), waveform, waveform+hit.nsamples);
    }
#endif
  
  event_vec.push_back(hit);
}

void event::EndEvent()
{
  file_out = t_out->GetCurrentFile();
  file_out->cd();
  t_out->Fill();

  event_vec.clear();
  nevt++;
}



// 
// event.cc ends here
