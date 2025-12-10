// DeviceHandle.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 6月 22 09:55:01 2022 (+0800)
// Last-Updated: 六 12月  6 17:12:04 2025 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 19
// URL: http://wuhongyi.cn 


#ifndef _DEVICEHANDLE_H_
#define _DEVICEHANDLE_H_

#include "Global.hh"

#include <string>
#include <cstring>
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


class DeviceHandle
{
public:
  DeviceHandle();
  virtual ~DeviceHandle();

  // void SYNCH();
  void StartAcquisition();
  void StopAcquisition();
  bool GetAcqStatus();
  
  unsigned short GetNumberOfDevice();
  void SetNumberOfDevice(unsigned short num);
  
  // void ClearDevice();
  // void AddDevice(unsigned short slot);
  void SendSWTrigger(unsigned short mod);


  int Open(const char* url, unsigned short mod);
  int Close(unsigned short mod);

  int GetHandle(const char* path, unsigned short mod);
  int GetParentHandle(const char* path, unsigned short mod);

  int GetValue(unsigned short mod, const char* path, char value[256]);
  int SetValue(unsigned short mod, const char* path, const char* value);
  
  int GetUserRegister(unsigned short mod, uint32_t address, uint32_t* value);
  int SetUserRegister(unsigned short mod, uint32_t address, uint32_t value);

  int SendCommand(unsigned short mod, const char* path);
  //int SetReadDataFormat(unsigned short mod, const char* jsonString);

  int ReadData(unsigned short mod, int timeout, ...);
  int HasData(unsigned short mod, int timeout);


  int SetReadDataFormat(unsigned short mod);

  

  

  // after open
  void GetModuleInfo(unsigned short mod);
  bool ReadModuleInfoAll();
  unsigned short GetFamily(unsigned short mod);
  unsigned short GetNumberOfChannels(unsigned short mod);
  unsigned short GetADCBitResolution(unsigned short mod);
  unsigned short GetADCSamplingFrequency(unsigned short mod);
  unsigned int GetSerialNumber(unsigned short mod);
  char * GetFwType(unsigned short mod);
  char * GetLicenseStatus(unsigned short mod);
  // unsigned short GetSlot(unsigned short num);

  void ConfigUDP(unsigned short mod);

private:
  

private:

  uint64_t dev_handle[MAXMODULENUM];
  uint64_t ep_handle[MAXMODULENUM];
  uint64_t ep_folder_handle[MAXMODULENUM];

  
  int mHandle;
  unsigned short mNumberOfDevice;
  // std::vector<unsigned short> slot_def;
  // unsigned short crateid;
  // bool runstatus;
  // unsigned short slotmap[MAXMODULENUM];

  // Module information
  struct ModuleInfo {
    unsigned short Family;
    unsigned int SerNum;
    unsigned short ADCBits;
    unsigned short ADCMSPS;
    unsigned short Channels;
    char FwType[256];//DPP_PHA   DPP_ZLE   DPP_PSD   DPP_DAW   DPP_OPEN   Scope  SCOPE_OPEN
    char LicenseStatus[256];
  };

  ModuleInfo ModuleInformation[MAXMODULENUM];

};

#endif /* _DEVICEHANDLE_H_ */
// 
// DeviceHandle.hh ends here
