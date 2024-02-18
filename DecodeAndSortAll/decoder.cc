// decoder.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 2月 17 23:04:21 2024 (+0800)
// Last-Updated: 日 2月 18 15:02:17 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 37
// URL: http://wuhongyi.cn 

#include "decoder.hh"


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
      n = read(fd, &buff, 24);
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
      n = read(fd, &buff, 24);
      if(n <= 0) return false;
      decodephapsd();
      if(n <= 0) return false;
      break;
    case 3://daw
      printf("DAW not impl...\n");
      break;
    case 4://open
      printf("OPEN not impl...\n");
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

  analog_probes_type[0] = (buff[5] &0x1F);
  analog_probes_type[1] = (buff[5] &0x3E0) >> 5;
  digital_probes_type[0] = (buff[5] &0x7C00) >> 10;
  digital_probes_type[1] = (buff[5] &0xF8000) >> 15;
  digital_probes_type[2] = (buff[5] &0x1F00000) >> 20;
  digital_probes_type[3] = (buff[5] &0x3E000000) >> 25;

  // std::cout << mod << "  " << ch << "  " << samples << std::endl;
  if(samples > 0)
    {
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
    }//if
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
  nsamples = (buff[0] & 0xFFFF0000) >> 16;

  timestamp = ((uint64_t)(buff[2] & 0xFFFF) << 32)+buff[1];
  trigger_id = buff[3];

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




// 
// decoder.cc ends here
