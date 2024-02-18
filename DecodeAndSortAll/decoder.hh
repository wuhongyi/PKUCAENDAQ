// decoder.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 2月 17 23:04:10 2024 (+0800)
// Last-Updated: 日 2月 18 13:31:06 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 9
// URL: http://wuhongyi.cn 

#ifndef _DECODER_H_
#define _DECODER_H_

#include "UserDefine.hh"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class decoder
{
public:
  decoder();
  virtual ~decoder();

  inline void setsamplerate(unsigned short sr) {samplerate = sr;}
  inline unsigned short getsamplerate() {return samplerate;}

  inline void setfirmware(unsigned short fw) {firmware = fw;}
  inline unsigned short getfirmware() {return firmware;}

  void clearall();
  bool openfile(const char*);

  void printword(); // for debug purpose
  bool getnextword(); // for debug purpose

  
  bool getnextevt();


  
  inline unsigned short getch() {return ch;}
  inline unsigned short getmod() {return mod;}
  inline uint64_t getts() {return timestamp;}
  inline uint16_t getfinets() {return fine_timestamp;} 

  inline uint16_t getenergy() {return energy;}
  inline uint16_t getenergyshort() {return energy_short;}

  inline uint16_t getflagslow() {return flags_low_priority;}
  inline uint16_t getflagshigh() {return flags_high_priority;}

  inline unsigned short getsamples() {return samples;}

  inline void getanalog0(int *da) {memcpy(da, analog_probes0, sizeof(int)*samples);}
  inline void getanalog1(int *da) {memcpy(da, analog_probes1, sizeof(int)*samples);}
  inline void getdigital0(bool *da) {memcpy(da, digital_probes0, sizeof(bool)*samples);}
  inline void getdigital1(bool *da) {memcpy(da, digital_probes1, sizeof(bool)*samples);}
  inline void getdigital2(bool *da) {memcpy(da, digital_probes2, sizeof(bool)*samples);}
  inline void getdigital3(bool *da) {memcpy(da, digital_probes3, sizeof(bool)*samples);}

  inline void getanalogtype(uint8_t *da) {memcpy(da, analog_probes_type, sizeof(uint8_t)*2);}
  inline void getdigitaltype(uint8_t *da) {memcpy(da, digital_probes_type, sizeof(uint8_t)*4);}

  inline uint32_t gettriggerid() {return trigger_id;}
  inline unsigned short getnsamples() {return nsamples;}
  inline void getwaveform(uint16_t *da) {memcpy(da, waveform, sizeof(uint16_t)*nsamples);}

  
private:
  bool readword();
  bool decode();

  void decodephapsd();
  void decodezle();
  void decodescope();
  
  int fd; // File descripter
  unsigned int buff[32768]; // buffer to read 4 buytes from file(32bit)
  size_t n;

  
  unsigned short samplerate;
  unsigned short firmware;//DPP_PHA DPP_ZLE DPP_PSD DPP_DAW OPEN Scope
  // PHA 6 + 2*SAMPLES+SAMPLE/8
  // PSD 6
  // ZLE 3 + SAMPLES/2
  // SCOPE 4 + SAMPLE/2

  unsigned short ch;
  unsigned short mod;
  uint64_t timestamp;
  
  uint16_t fine_timestamp;//PHA PSD
  uint16_t energy;//PHA PSD
  uint16_t energy_short;// PSD
  uint16_t flags_low_priority;//PHA PSD
  uint16_t flags_high_priority;//PHA PSD

  unsigned short samples;//PHA PSD
  int32_t analog_probes0[10000];
  int32_t analog_probes1[10000];
  bool digital_probes0[10000];
  bool digital_probes1[10000];
  bool digital_probes2[10000];
  bool digital_probes3[10000];
  uint8_t analog_probes_type[2];
  uint8_t digital_probes_type[4];


  uint32_t trigger_id;//SCOPE
  unsigned short nsamples;//ZLE SCOPE
  uint16_t waveform[10000];//ZLE SCOPE
  
};

#endif /* _DECODER_H_ */
// 
// decoder.hh ends here













