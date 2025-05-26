// r2root.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 2月 18 01:23:28 2024 (+0800)
// Last-Updated: 日 5月 25 16:00:14 2025 (+0900)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 27
// URL: http://wuhongyi.cn 

#include "r2root.hh"
#include "UserDefine.hh"

#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

r2root::r2root(int run)
{
  Run = run;

  benchmark = new TBenchmark;
  
  rawdec = new decoder[MAXMODULENUMBER];

  for (int i = 0; i < MAXMODULENUMBER; ++i)
    for (int j = 0; j < MAXCHANNELNUMBER; ++j)
      {
	timeoffset[i][j] = 0;
	chlow[i][j] = 0;
	chhigh[i][j] = 65535;

	sl[i][j] = 375;
	sg[i][j] = 30;
	tau[i][j] = 100000;
      }

  std::ifstream readtxt;
  std::string str_tmp;
  Short_t mod_tmp;
  Short_t ch_tmp;
  Short_t offset_tmp;
  UShort_t chlow_tmp;
  UShort_t chhigh_tmp;
  unsigned int sl_tmp;
  unsigned int sg_tmp;
  unsigned int tau_tmp;
  readtxt.open("par.dat");
  if(!readtxt.is_open()) { std::cout << "can't open file par.dat." << std::endl; }
  getline(readtxt, str_tmp);
  while(!readtxt.eof())
    {
      readtxt >> mod_tmp >> ch_tmp >> offset_tmp >> chlow_tmp >> chhigh_tmp;
      if(readtxt.eof()) break;
      timeoffset[mod_tmp][ch_tmp] = offset_tmp;
      chlow[mod_tmp][ch_tmp] = chlow_tmp;
      chhigh[mod_tmp][ch_tmp] = chhigh_tmp;
    }
  readtxt.close();


  readtxt.open("parfdk.dat");
  if(!readtxt.is_open()) { std::cout << "can't open file parfdk.dat." << std::endl; }
  getline(readtxt, str_tmp);
  while(!readtxt.eof())
    {
      readtxt >> mod_tmp >> ch_tmp >> sl_tmp >> sg_tmp >> tau_tmp;
      if(readtxt.eof()) break;
      sl[mod_tmp][ch_tmp] = sl_tmp;
      sg[mod_tmp][ch_tmp] = sg_tmp;
      tau[mod_tmp][ch_tmp] = tau_tmp;
    }
  readtxt.close();


  for (int i = 0; i < MAXMODULENUMBER; ++i)
    for (int j = 0; j < MAXCHANNELNUMBER; ++j)
      {
	rawdec[i].SetFDKSL(j, sl[i][j]);
	rawdec[i].SetFDKSG(j, sg[i][j]);
	rawdec[i].SetFDKTAU(j, tau[i][j]);
      }
  

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  char tempfilename[1024];
  for (int i = 0; i < MODNUMBER; ++i)
    {
      if(SamplingRate[i] == 125 || SamplingRate[i] == 500)
	{
	  sprintf(tempfilename, "%s%04d/%s_R%04d_M%02d.bin",RAWFILEPATH, Run, RAWFILENAME, Run, i);
	  if(!IsFileExists(tempfilename))
	    {
	      std::cout << "can't find raw data: " << tempfilename << std::endl;
	      exit(1);
	    }
	  
	  rawdec[i].setsamplerate(SamplingRate[i]);
	  rawdec[i].setfirmware(Firmware[i]);
	  rawdec[i].openfile(tempfilename);
	}
      else
	{
	  rawdec[i].setsamplerate(0);
	}

      havedata[i] = false;
    }


  sprintf(tempfilename, "%s%s_%04d.root", ROOTFILEPATH, ROOTFILENAME, Run);
  
  file = new TFile(tempfilename, "RECREATE");
  t = new TTree("tree","GDDAQ - CAEN sort Data");
  // t->Branch("tsflag", &tsflag, "tsflag/L");
  t->Branch("sr", &sr, "sr/s");
  t->Branch("fw", &fw, "fw/s");
  t->Branch("mod", &mod, "mod/s");
  t->Branch("ch", &ch, "ch/s");
  t->Branch("ts", &ts, "ts/L");

  t->Branch("finets", &finets, "finets/s");
  t->Branch("flagslow", &flagslow, "flagslow/s");
  t->Branch("flagshigh", &flagshigh, "flagshigh/s");

  t->Branch("energy", &energy, "energy/s");
  t->Branch("energyshort", &energyshort, "energyshort/s");
  
  t->Branch("samples", &samples, "samples/s");
  t->Branch("analog0", &analog0, "analog0[samples]/I");
  t->Branch("analog1", &analog1, "analog1[samples]/I");
  t->Branch("digital0", &digital0, "digital0[samples]/O");
  t->Branch("digital1", &digital1, "digital1[samples]/O");
  t->Branch("digital2", &digital2, "digital2[samples]/O");
  t->Branch("digital3", &digital3, "digital3[samples]/O");

  t->Branch("analogtypes", &analogtypes, "analogtypes[2]/s");
  t->Branch("digitaltypes", &digitaltypes, "digitaltypes[4]/s");
  
  t->Branch("triggerid", &triggerid, "triggerid/i");

  t->Branch("nsamples", &nsamples, "nsamples/i");
  t->Branch("waveform", &waveform, "waveform[nsamples]/s");


  t->Branch("energyxia", &energyxia, "energyxia/s");
}

r2root::~r2root()
{
  delete [] rawdec;
}
	       


void r2root::Process()
{
  benchmark->Start("r2root");//计时开始
  
  int mark = -1; 
  Long64_t timestamp;
  bool flagdata = false;
  unsigned int sizelen;
  nevt = 0;
  
  for (int i = 0; i < MODNUMBER; ++i)
    {
      if(rawdec[i].getsamplerate() != 0)
	havedata[i] = rawdec[i].getnextevt();
    }

  Long64_t deltat = TIMEBUFF;
  while(true)
    {
      timestamp = LLONG_MAX;
      for (int i = 0; i < MODNUMBER; ++i)
	{
	  while(havedata[i])
	    {
	      if(rawdec[i].getfirmware() == 5 || rawdec[i].getfirmware() == 4)//open-fdk
		{
		  timestamp = 8*rawdec[i].getts();
		}
	      else
		{
		  if(rawdec[i].getsamplerate() == 125)
		    {
		      timestamp = 8*rawdec[i].getts();
		    }
		  else if(rawdec[i].getsamplerate() == 500)
		    {
		      timestamp = 2*rawdec[i].getts();
		    }
		  else
		    {// TODO
		      timestamp = rawdec[i].getts();
		    }
		}

	      if(timestamp < deltat)
		{
		  mark = i;
		  mapvalue.fw = rawdec[mark].getfirmware();
		  mapvalue.samples = 0;
		  mapvalue.nsamples = 0;

		  mapvalue.sr = rawdec[mark].getsamplerate();
		  mapvalue.ch = rawdec[mark].getch();
		  mapvalue.mod = rawdec[mark].getmod();
		  mapvalue.ts = timestamp+timeoffset[mapvalue.mod][mapvalue.ch];

		  
		  mapvalue.energy = 0;
		  mapvalue.energyshort = 0;
		  mapvalue.energyxia = 0;
		  
		  switch(mapvalue.fw)
		    {
		    case 0://pha
		    case 2://psd
		      {
			mapvalue.finets = rawdec[mark].getfinets();
			mapvalue.flagslow = rawdec[mark].getflagslow();
			mapvalue.flagshigh = rawdec[mark].getflagshigh();
			mapvalue.energy = rawdec[mark].getenergy();
			mapvalue.energyshort = rawdec[mark].getenergyshort();

			
			
			rawdec[mark].getanalogtype(analogtype);
			memcpy(mapvalue.analogtype, analogtype, sizeof(uint8_t)*2);
			rawdec[mark].getdigitaltype(digitaltype);
			memcpy(mapvalue.digitaltype, digitaltype, sizeof(uint8_t)*4);
			
			mapvalue.samples = rawdec[mark].getsamples();
			if(mapvalue.samples > 0)
			  {
			    mapvalue.analog0 = new int [mapvalue.samples];
			    rawdec[mark].getanalog0(mapvalue.analog0);
			    mapvalue.analog1 = new int [mapvalue.samples];
			    rawdec[mark].getanalog1(mapvalue.analog1);

			    mapvalue.digital0 = new bool [mapvalue.samples];
			    rawdec[mark].getdigital0(mapvalue.digital0);
			    mapvalue.digital1 = new bool [mapvalue.samples];
			    rawdec[mark].getdigital1(mapvalue.digital1);
			    mapvalue.digital2 = new bool [mapvalue.samples];
			    rawdec[mark].getdigital2(mapvalue.digital2);
			    mapvalue.digital3 = new bool [mapvalue.samples];
			    rawdec[mark].getdigital3(mapvalue.digital3);
			  }

		      }
		      break;
		    case 1://zle
		    case 5://scope
		      {
			mapvalue.triggerid = rawdec[mark].gettriggerid();
			mapvalue.nsamples = rawdec[mark].getnsamples();
			if(mapvalue.nsamples > 0)
			  {
			    mapvalue.waveform = new UShort_t [mapvalue.nsamples];
			    rawdec[mark].getwaveform(mapvalue.waveform);
			  }
		      }
		      break;
		    case 3://daw
		      printf("DAW not impl...\n");
		      break;
		    case 4://open
		      mapvalue.energyxia = rawdec[mark].getenergyxia();
		      mapvalue.nsamples = rawdec[mark].getnsamples();
		      if(mapvalue.nsamples > 0)
			{
			  mapvalue.waveform = new UShort_t [mapvalue.nsamples];
			  rawdec[mark].getwaveform(mapvalue.waveform);
			}
		      break;
		    default:
		      printf("firmware type error...\n");
		      break;
		    }



		  havedata[mark] = rawdec[mark].getnextevt();


		  mapvalue.tsflag = mapvalue.ts;
		  //if(mapvalue.sr == 125)
		  //  {
		  //    mapvalue.tsflag = mapvalue.ts*8;
		  //  }
		  //else
		  //  {// TODO
		  //    mapvalue.tsflag = mapvalue.ts*8;
		  //  }


		  flagkey = ((((mapvalue.tsflag)<<6)+mapvalue.mod)<<6)+mapvalue.ch;

		  if(mapvalue.fw == 0 || mapvalue.fw == 2)
		    {
		      if(mapvalue.energy < chlow[mapvalue.mod][mapvalue.ch] || mapvalue.energy > chhigh[mapvalue.mod][mapvalue.ch])
			{
			  if(mapvalue.samples > 0)
			    {
			      delete[] mapvalue.analog0;
			      delete[] mapvalue.analog1;
			      delete[] mapvalue.digital0;
			      delete[] mapvalue.digital1;
			      delete[] mapvalue.digital2;
			      delete[] mapvalue.digital3;
			    }			  
			  continue;
			}
		    }
		  if(mapvalue.fw == 4)
		    {
		      if(mapvalue.energyxia < chlow[mapvalue.mod][mapvalue.ch] || mapvalue.energy > chhigh[mapvalue.mod][mapvalue.ch])
			{
			  if(mapvalue.nsamples > 0)
			    {
			      delete[] mapvalue.waveform;
			    }
			  continue;
			}
		    }
		    
		  sortdata.insert(std::make_pair(flagkey, mapvalue));
		}
	      else
		break;
	    }//while

	}//for
      
      deltat += TIMEBUFF;//

      sizelen = sortdata.size() * PROCESSBUFF;
      for (unsigned int i = 0; i < sizelen; ++i)
	{
	  itkey = sortdata.begin();
	  tsflag = itkey->second.tsflag;

	  sr = itkey->second.sr;
	  fw = itkey->second.fw;
	  ts = itkey->second.ts;
	  ch = itkey->second.ch;
	  mod = itkey->second.mod;

	  nsamples = 0;
	  samples = 0;
	  
	  switch(fw)
	    {
	    case 0://pha
	    case 2://psd
	      {
		finets = itkey->second.finets;
		flagslow = itkey->second.flagslow;
		flagshigh = itkey->second.flagshigh;
		energy = itkey->second.energy;
		energyshort = itkey->second.energyshort;
		analogtypes[0] = itkey->second.analogtype[0];
		analogtypes[1] = itkey->second.analogtype[1];
		digitaltypes[0] = itkey->second.digitaltype[0];
		digitaltypes[1] = itkey->second.digitaltype[1];
		digitaltypes[2] = itkey->second.digitaltype[2];
		digitaltypes[3] = itkey->second.digitaltype[3];
		samples = itkey->second.samples;
		if(samples > 0)
		  {
		    memcpy(analog0, itkey->second.analog0, sizeof(int)*samples);
		    delete itkey->second.analog0;
		    memcpy(analog1, itkey->second.analog1, sizeof(int)*samples);
		    delete itkey->second.analog1;

		    memcpy(digital0, itkey->second.digital0, sizeof(bool)*samples);
		    delete itkey->second.digital0;
		    memcpy(digital1, itkey->second.digital1, sizeof(bool)*samples);
		    delete itkey->second.digital1;
		    memcpy(digital2, itkey->second.digital2, sizeof(bool)*samples);
		    delete itkey->second.digital2;
		    memcpy(digital3, itkey->second.digital3, sizeof(bool)*samples);
		    delete itkey->second.digital3;		    
		  }
	      }
	      break;
	    case 1://zle
	    case 5://scope
	      {
		triggerid = itkey->second.triggerid;
		nsamples = itkey->second.nsamples;
		if(nsamples > 0)
		  {
		    memcpy(waveform, itkey->second.waveform, sizeof(UShort_t)*nsamples);
		    delete itkey->second.waveform;
		  }	    
	      }
	      break;
	    case 3://daw
	      printf("DAW not impl...\n");
	      break;
	    case 4://open
	      energyxia = itkey->second.energyxia;
	      nsamples = itkey->second.nsamples;
	      if(nsamples > 0)
		{
		  memcpy(waveform, itkey->second.waveform, sizeof(UShort_t)*nsamples);
		  delete itkey->second.waveform;
		}
	      break;
	    default:
	      printf("firmware type error...\n");
	      break;
	    }

	  sortdata.erase(itkey);
	  file = t->GetCurrentFile();
	  file->cd();
	  t->Fill();
	}

      nevt++;
      std::cout<<"\r"<<"nt: "<<nevt;
      std::cout << std::flush;


      flagdata = false;
      for (int i = 0; i < MODNUMBER; ++i)
	flagdata += havedata[i];

      if(!flagdata)
	{
	  while(sortdata.size() > 0)
	    {
	      itkey = sortdata.begin();
	      tsflag = itkey->second.tsflag;

	      sr = itkey->second.sr;
	      fw = itkey->second.fw;
	      ts = itkey->second.ts;
	      ch = itkey->second.ch;
	      mod = itkey->second.mod;

	      nsamples = 0;
	      samples = 0;
	      
	      switch(fw)
		{
		case 0://pha
		case 2://psd
		  {
		    finets = itkey->second.finets;
		    flagslow = itkey->second.flagslow;
		    flagshigh = itkey->second.flagshigh;
		    energy = itkey->second.energy;
		    energyshort = itkey->second.energyshort;
		    analogtypes[0] = itkey->second.analogtype[0];
		    analogtypes[1] = itkey->second.analogtype[1];
		    digitaltypes[0] = itkey->second.digitaltype[0];
		    digitaltypes[1] = itkey->second.digitaltype[1];
		    digitaltypes[2] = itkey->second.digitaltype[2];
		    digitaltypes[3] = itkey->second.digitaltype[3];
		    samples = itkey->second.samples;
		    if(samples > 0)
		      {
			memcpy(analog0, itkey->second.analog0, sizeof(int)*samples);
			delete itkey->second.analog0;
			memcpy(analog1, itkey->second.analog1, sizeof(int)*samples);
			delete itkey->second.analog1;

			memcpy(digital0, itkey->second.digital0, sizeof(bool)*samples);
			delete itkey->second.digital0;
			memcpy(digital1, itkey->second.digital1, sizeof(bool)*samples);
			delete itkey->second.digital1;
			memcpy(digital2, itkey->second.digital2, sizeof(bool)*samples);
			delete itkey->second.digital2;
			memcpy(digital3, itkey->second.digital3, sizeof(bool)*samples);
			delete itkey->second.digital3;		    
		      }
		  }
		  break;
		case 1://zle
		case 5://scope
		  {
		    triggerid = itkey->second.triggerid;
		    nsamples = itkey->second.nsamples;
		    if(nsamples > 0)
		      {
			memcpy(waveform, itkey->second.waveform, sizeof(UShort_t)*nsamples);
			delete itkey->second.waveform;
		      }	    
		  }
		  break;
		case 3://daw
		  printf("DAW not impl...\n");
		  break;
		case 4://open
		  energyxia = itkey->second.energyxia;
		  nsamples = itkey->second.nsamples;
		  if(nsamples > 0)
		    {
		      memcpy(waveform, itkey->second.waveform, sizeof(UShort_t)*nsamples);
		      delete itkey->second.waveform;
		    }
		  break;
		default:
		  printf("firmware type error...\n");
		  break;
		}

	      sortdata.erase(itkey);
	      file = t->GetCurrentFile();
	      file->cd();
	      t->Fill();
	    }//while
	  break;
	}//if
      
    }
  
  std::cout<<std::endl;

  file = t->GetCurrentFile();
  file->cd();
  t->Write();
  file->Close();
  benchmark->Show("r2root");//计时结束并输出时间

}

bool r2root::IsFileExists(const char *name)
{
  if((access(name,F_OK)) != -1)  
    {  
      return true;
    }  
  else  
    {  
      return false;
    } 
}

// 
// r2root.cc ends here
