// decoder.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 2月 17 23:04:21 2024 (+0800)
// Last-Updated: 二 12月 16 11:55:45 2025 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 64
// URL: http://wuhongyi.cn 

#include "decoder.hh"

#include "TMath.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

decoder::decoder()
{

}

decoder::~decoder()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void decoder::clearall()
{
  samples = 0;
  nsamples = 0;
  
}


bool decoder::openfile(const char* fileN)
{
  if((fd = open(fileN, O_RDONLY)) < 0)
    {
      printf("cannot open file %s\n", fileN);
      return false;
    }
  return true;
}


bool decoder::readword()
{
  if(fd < 0)
    {
      printf("Error, no opened file found!\n");
      return false;
    }
  n = read(fd,&buff, 4);//TODO
  if(n <= 0) return false;
  //  printf("read %d bytes!\n",n);
  //  memcpy(&tmpd,buff,sizeof(char)*4);
  return true;
}

void decoder::printword()
{
  printf("0x%08x\n",buff[0]);
}

bool decoder::getnextword()
{
  return readword();
}

bool decoder::getnextevt()
{
  clearall();
  return decode();
}


bool decoder::decode()
{
  if(fd < 0)
    {
      printf("Error, no opened file found!\n");
      return false;
    }
  
  switch(firmware)
    {
    case 0://pha
      n = read(fd, &buff, 20);
      if(n <= 0) return false;
      decodephapsd();
      if(n <= 0) return false;
      break;
    case 1://zle
      n = read(fd, &buff, 12);
      if(n <= 0) return false;
      decodezle();
      if(n <= 0) return false;
      break;
    case 2://psd
      n = read(fd, &buff, 20);
      if(n <= 0) return false;
      decodephapsd();
      if(n <= 0) return false;
      break;
    case 3://daw
      printf("DAW not impl...\n");
      break;
    case 4://open
      n = read(fd, &buff, 20);
      if(n <= 0) return false;
      decodedppfdk();
      if(n <= 0) return false;
      break;
    case 5://scope
      n = read(fd, &buff, 16);
      if(n <= 0) return false;
      decodescope();
      if(n <= 0) return false;
      break;
      
    default:
      printf("firmware type error...\n");
      break;
    }
  
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void decoder::decodephapsd()
{
  ch = buff[0] & 0xFF;
  mod = (buff[0] & 0xFF00) >> 8;
  samples = (buff[0] & 0xFFFF0000) >> 16;

  timestamp = ((uint64_t)(buff[2] & 0xFFFF) << 32)+buff[1];
  fine_timestamp = (buff[2] & 0xFFFF0000) >> 16;
  energy = buff[3] & 0xFFFF;
  energy_short = (buff[3] & 0xFFFF0000) >> 16;

  flags_low_priority = buff[4] & 0xFFFF;
  flags_high_priority = (buff[4] & 0xFFFF0000) >> 16;

  nsamples = 0;

  if(samples > 0)
    {
      n = read(fd, &buff, 4);

      analog_probes_type[0] = (buff[0] &0x1F);
      analog_probes_type[1] = (buff[0] &0x3E0) >> 5;
      digital_probes_type[0] = (buff[0] &0x7C00) >> 10;
      digital_probes_type[1] = (buff[0] &0xF8000) >> 15;
      digital_probes_type[2] = (buff[0] &0x1F00000) >> 20;
      digital_probes_type[3] = (buff[0] &0x3E000000) >> 25;

      if(analog_probes_type[0] != 5)
	{
	  // std::cout << mod << "  " << ch << "  " << samples << std::endl;
	  unsigned int len = 0;
	  if(samples%8 == 0)
	    len = samples/8;
	  else
	    len = samples/8+1;
	  // std::cout << "len: " << len << std::endl;
	  n = read(fd, &buff, (2*samples+len)*4);
	  memcpy(analog_probes0, buff, sizeof(int32_t)*samples);
	  memcpy(analog_probes1, buff+samples, sizeof(int32_t)*samples);
	  // std::cout << "len: " << len << std::endl;
	  for (unsigned int i = 0; i < len; ++i)
	    for (int j = 0; j < 8; ++j)
	      {
		//std::cout << i << "  " << j << "  " << ((buff[2*samples+i] & (0x1 << (4*j))) >> (4*j)) << "  " << ((buff[2*samples+i] & (0x1 << (4*j+1))) >> (4*j+1)) << "  " << ((buff[2*samples+i] & (0x1 << (4*j+2))) >> (4*j+2)) << "  " << ((buff[2*samples+i] & (0x1 << (4*j+3))) >> (4*j+3)) << std::endl;
		digital_probes0[8*i+j] = (buff[2*samples+i] & (0x1 << (4*j))) >> (4*j);
		digital_probes1[8*i+j] = (buff[2*samples+i] & (0x1 << (4*j+1))) >> (4*j+1);
		digital_probes2[8*i+j] = (buff[2*samples+i] & (0x1 << (4*j+2))) >> (4*j+2);
		digital_probes3[8*i+j] = (buff[2*samples+i] & (0x1 << (4*j+3))) >> (4*j+3);
	      }

	  nsamples = 0;
	}
      else
	{
	  nsamples = samples;
	  samples = 0;
	  n = read(fd, &buff, nsamples/2*4);
	  for (unsigned short i = 0; i < nsamples/2; ++i)
	    {
	      waveform[2*i] = buff[i] & 0xFFFF;
	      waveform[2*i+1] = (buff[i] & 0xFFFF0000) >> 16;
	    }
	}
    }
  
}


void decoder::decodezle()
{
  // std::cout << "xxxxx" << std::endl;
  ch = buff[0] & 0xFF;
  mod = (buff[0] & 0xFF00) >> 8;
  nsamples = (buff[0] & 0xFFFF0000) >> 16;

  timestamp = ((uint64_t)(buff[2] & 0xFFFF) << 32)+buff[1];

  if(nsamples > 0)
    {
      n = read(fd, &buff, nsamples/2*4);
      for (unsigned short i = 0; i < nsamples/2; ++i)
	{
	  waveform[2*i] = buff[i] & 0xFFFF;
	  waveform[2*i+1] = (buff[i] & 0xFFFF0000) >> 16;
	}
    }
}

void decoder::decodescope()
{
  // std::cout << "TEST HEHR" << std::endl;
  ch = buff[0] & 0xFF;
  mod = (buff[0] & 0xFF00) >> 8;
  nsamples = ((buff[0] & 0xFFFF0000) >> 16) + (buff[2] & 0xFFFF0000);

  timestamp = ((uint64_t)(buff[2] & 0xFFFF) << 32)+buff[1];
  trigger_id = buff[3];
  //std::cout << mod << "  " << ch << "  " << nsamples << "  " << timestamp << "  " << trigger_id << std::endl;
  if(nsamples > 0)
    {
      n = read(fd, &buff, nsamples/2*4);
      for (int i = 0; i < nsamples/2; ++i)
	{
	  waveform[2*i] = buff[i] & 0xFFFF;
	  waveform[2*i+1] = (buff[i] & 0xFFFF0000) >> 16;
	}
    }
  // std::cout << "read" << std::endl;
}

void decoder::decodedppfdk()
{
  unsigned int userinfo = (buff[0] & 0xC0000000) >> 30;//waveform

  ch = buff[0] & 0xFF;
  mod = (buff[0] & 0xFF00) >> 8;
  nsamples = (buff[0] & 0x3FFF0000) >> 16;
  
  timestamp = ((uint64_t)(buff[2] & 0xFFFF) << 32)+buff[1];
  fine_timestamp = (buff[2] & 0x3FF0000) >> 16;
  energy = buff[3] & 0xFFFF;
  energy_short = (buff[3] & 0xFFFF0000) >> 16;

  info = buff[4] & 0xFF;
  flags_a = (buff[4] & 0xFF00) >> 8;
  flags_b = (buff[4] & 0xFFF0000) >> 16;
  
  lasttrigger = ((uint64_t)(flags_a) << 42) + ((uint64_t)(energy_short) << 26) + ((uint64_t)(fine_timestamp) << 16) + energy;

  
  energyxia = 0;
  if(userinfo > 0)
    {
      n = read(fd, &buff, 40);

      sumqs = buff[1];
      sumql = buff[0];
      //baseline = (buff[1] & 0x3FFFC00) >> 10;
      rt_accx2 = ((uint64_t)(buff[3] & 0x3FF) << 32)+buff[2];
      rt_accx = buff[4] & 0x3FFFFFF;
      xia_sl1 = buff[5] & 0x3FFFFFF;
      xia_sg = buff[6] & 0x3FFFFFF;
      xia_sl2 = buff[7] & 0x3FFFFFF;
      sumbl1 = buff[9];
      sumbl2 = buff[8];

      
      //lasttrigger = ((uint64_t)(buff[7] & 0xFFFF) << 32)+buff[6];
      double xiabl = bl[ch];
      
      double xiasl = sl[ch];
      double xiasg = sg[ch];
      double xiatau = tau[ch];

      double vdc;
      double vdc0;
      
      double b1 = TMath::Exp(-8.0/xiatau);
      double a0 = -(1-b1)*(TMath::Power(b1, xiasl))/(1-TMath::Power(b1, xiasl));
      double ag = (1-b1);
      double a1 = (1-b1)/(1-TMath::Power(b1, xiasl));

      double a_bl = (1-TMath::Power(b1, xiabl))/(TMath::Power(b1, xiabl)-TMath::Power(b1, xiabl+xiasl));
      double a_bl2 = (1-TMath::Power(b1, xiabl))/(TMath::Power(b1, xiabl)-TMath::Power(b1, xiabl+xiabl));

      double dt = timestamp - lasttrigger;
      if(dt > (xiabl+xiabl+xiasl+xiasg))
	vdc0 = (sumbl1-a_bl2*sumbl2)/(xiabl-a_bl2*xiabl);
      else if(dt > (xiabl+xiasl+xiasg))
	vdc0 = (sumbl2-a_bl*xia_sl1)/(xiabl-a_bl*xiasl);
      else
	vdc0 = vdctmp[ch];

      vdc = vdc0;
      vdctmp[ch] = vdc0;


  
      
      double en = (a0*xia_sl1+ag*xia_sg+a1*xia_sl2)-(a0*vdc*xiasl+ag*vdc*xiasg+a1*vdc*xiasl);
      if(en < 0) energyxia = 0;
      else if(en >= 65536) energyxia = 65535;
      else energyxia = uint16_t(en);

      double cc = (sumqs-vdc*qs[ch])/(sumql-vdc*ql[ch]);
      double costheta = (rt_accx-vdc*cosl[ch])/(TMath::Sqrt(cosl[ch]*(rt_accx2-2*vdc*rt_accx+cosl[ch]*vdc*vdc)));
    }


  if(nsamples > 0)
    {
      n = read(fd, &buff, nsamples/2*4);
      for (unsigned short i = 0; i < nsamples/2; ++i)
	{
	  waveform[2*i] = buff[i] & 0xFFFF;
	  waveform[2*i+1] = (buff[i] & 0xFFFF0000) >> 16;
	}
    }

}


void decoder::SetFDKBL(int ch, unsigned int value)
{
  bl[ch] = value;
}


void decoder::SetFDKSL(int ch, unsigned int value)
{
  sl[ch] = value;
}

void decoder::SetFDKSG(int ch, unsigned int value)
{
  sg[ch] = value;
}

void decoder::SetFDKTAU(int ch, unsigned int value)
{
  tau[ch] = value;
}

void decoder::SetFDKQS(int ch, unsigned int value)
{
  qs[ch] = value;
}

void decoder::SetFDKQL(int ch, unsigned int value)
{
  ql[ch] = value;
}

void decoder::SetFDKCOSL(int ch, unsigned int value)
{
  cosl[ch] = value;
}





// 
// decoder.cc ends here
