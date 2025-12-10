// Global.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 二 10月 25 14:31:51 2022 (+0800)
// Last-Updated: 六 12月  6 17:13:26 2025 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 132
// URL: http://wuhongyi.cn 

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifdef _WIN32
#include <io.h>
#include <process.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <bitset>
#include <limits>

#include "QVector"
#include "QMutex"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define VERSIONDATE "GUI-Qt - 20251206"
#define EXPIRATIONDATE 20260606


#define ONLINEMODE


// Features customized for special users
#define DECODERONLINE


#define RECODESHA256


#define MAXMODULENUM 21
#define MAXCHANNELNUM 64

#define MAXHISTOGRAMLENGTH 65536
#define MAXSTATISTICS 4096

#define MAXDPPWAVELENGTH 16384

//MiB x 1024 x 1024 / 4
#define BUFFLENGTH 1310720
#define BUFFLENGTHSCOPE 6000000   // N x 2 = sample(max wave samples 41943040)
	       //default 6000000


//6GiB 1610612736   SHA256 ISSUE, write issue
//5GiB 1342177280   SHA256 ISSUE   
//4GiB 1073741824   SHA256 ISSUE
//3GiB  805306368
//2GiB  536870912
//1GiB  268435456
//#define LONGWAVEFORMMODE
#define LONGWAVEFORMMODEBUFFLENGTH 268435456


typedef struct RAWDATABUFFER
{
  int runno;
  int buffid;
  //unsigned char sha256[32];
  //unsigned int buff[BUFFLENGTHSCOPE];//TODO length
  unsigned int *buff;
} RAWDATABUFFER;

extern QMutex datavectordecoder_mutex[];
extern QVector<RAWDATABUFFER> datavectordecoder[];
//extern RAWDATABUFFER rawdatabuffer;

#ifdef WIN32
	#define ENDL  "\r\n"
	#define DIRSEP "/"
#else
	#define ENDL  "\n"
	#define DIRSEP "/"
#endif

#define CONFIG_DIR ".GDDAQ"
#define DEFAUL_RUN_CONFIG_FILENAME "GDDAQ_CAEN.conf"

#define DEFAULT_PARAMETERS "../pars/setting.par"



static unsigned long long value_to_ull(const char* value)
{
  char* value_end;
  const unsigned long long ret = strtoull(value, &value_end, 0);
  if (value == value_end || errno == ERANGE)
    fprintf(stderr, "strtoull error\n");
  return ret;
}

static double value_to_d(const char* value)
{
  char* value_end;
  const double ret = strtod(value, &value_end);
  if (value == value_end || errno == ERANGE)
    fprintf(stderr, "strtod error\n");
  return ret;
}



#define DATA_FORMAT_PHA " \
	[ \
		{ \"name\" : \"CHANNEL\", \"type\" : \"U8\" }, \
		{ \"name\" : \"TIMESTAMP\", \"type\" : \"U64\" }, \
		{ \"name\" : \"FINE_TIMESTAMP\", \"type\" : \"U16\" }, \
		{ \"name\" : \"ENERGY\", \"type\" : \"U16\" }, \
		{ \"name\" : \"ANALOG_PROBE_1\", \"type\" : \"I32\", \"dim\" : 1 }, \
		{ \"name\" : \"ANALOG_PROBE_2\", \"type\" : \"I32\", \"dim\" : 1 }, \
		{ \"name\" : \"DIGITAL_PROBE_1\", \"type\" : \"U8\", \"dim\" : 1 }, \
		{ \"name\" : \"DIGITAL_PROBE_2\", \"type\" : \"U8\", \"dim\" : 1 }, \
		{ \"name\" : \"DIGITAL_PROBE_3\", \"type\" : \"U8\", \"dim\" : 1 }, \
		{ \"name\" : \"DIGITAL_PROBE_4\", \"type\" : \"U8\", \"dim\" : 1 }, \
		{ \"name\" : \"ANALOG_PROBE_1_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"ANALOG_PROBE_2_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"DIGITAL_PROBE_1_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"DIGITAL_PROBE_2_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"DIGITAL_PROBE_3_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"DIGITAL_PROBE_4_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"WAVEFORM_SIZE\", \"type\" : \"SIZE_T\" }, \
		{ \"name\" : \"FLAGS_LOW_PRIORITY\", \"type\" : \"U16\"}, \
		{ \"name\" : \"FLAGS_HIGH_PRIORITY\", \"type\" : \"U16\" }, \
		{ \"name\" : \"EVENT_SIZE\", \"type\" : \"SIZE_T\" } \
	] \
"


struct event_pha {
  uint8_t channel;
  uint64_t timestamp;
  uint16_t fine_timestamp;
  uint16_t energy;
  uint16_t flags_low_priority;
  uint16_t flags_high_priority;
  size_t event_size;
  int32_t* analog_probes[2];
  uint8_t* digital_probes[4];
  uint8_t analog_probes_type[2];
  uint8_t digital_probes_type[4];
  size_t n_allocated_samples;
  size_t n_samples;
};

#define DATA_FORMAT_PSD " \
	[ \
		{ \"name\" : \"CHANNEL\", \"type\" : \"U8\" }, \
		{ \"name\" : \"TIMESTAMP\", \"type\" : \"U64\" }, \
		{ \"name\" : \"FINE_TIMESTAMP\", \"type\" : \"U16\" }, \
		{ \"name\" : \"ENERGY\", \"type\" : \"U16\" }, \
		{ \"name\" : \"ENERGY_SHORT\", \"type\" : \"U16\" }, \
		{ \"name\" : \"ANALOG_PROBE_1\", \"type\" : \"I32\", \"dim\" : 1 }, \
		{ \"name\" : \"ANALOG_PROBE_2\", \"type\" : \"I32\", \"dim\" : 1 }, \
		{ \"name\" : \"DIGITAL_PROBE_1\", \"type\" : \"U8\", \"dim\" : 1 }, \
		{ \"name\" : \"DIGITAL_PROBE_2\", \"type\" : \"U8\", \"dim\" : 1 }, \
		{ \"name\" : \"DIGITAL_PROBE_3\", \"type\" : \"U8\", \"dim\" : 1 }, \
		{ \"name\" : \"DIGITAL_PROBE_4\", \"type\" : \"U8\", \"dim\" : 1 }, \
		{ \"name\" : \"ANALOG_PROBE_1_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"ANALOG_PROBE_2_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"DIGITAL_PROBE_1_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"DIGITAL_PROBE_2_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"DIGITAL_PROBE_3_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"DIGITAL_PROBE_4_TYPE\", \"type\" : \"U8\" }, \
		{ \"name\" : \"WAVEFORM_SIZE\", \"type\" : \"SIZE_T\" }, \
		{ \"name\" : \"FLAGS_LOW_PRIORITY\", \"type\" : \"U16\"}, \
		{ \"name\" : \"FLAGS_HIGH_PRIORITY\", \"type\" : \"U16\" }, \
		{ \"name\" : \"EVENT_SIZE\", \"type\" : \"SIZE_T\" } \
	] \
"

struct event_psd {
  uint8_t channel;
  uint64_t timestamp;
  uint16_t fine_timestamp;
  uint16_t energy;
  uint16_t energy_short;
  uint16_t flags_low_priority;
  uint16_t flags_high_priority;
  size_t event_size;
  int32_t* analog_probes[2];
  uint8_t* digital_probes[4];
  uint8_t analog_probes_type[2];
  uint8_t digital_probes_type[4];
  size_t n_allocated_samples;
  size_t n_samples;
};


#define DATA_FORMAT_ZLE " \
	[ \
		{ \"name\" : \"TIMESTAMP\", \"type\" : \"U64\", \"dim\" : 0}, \
		{ \"name\" : \"RECONSTRUCTED_WAVEFORM\", \"type\" : \"U16\", \"dim\" : 2}, \
		{ \"name\" : \"RECONSTRUCTED_WAVEFORM_SIZE\", \"type\" : \"SIZE_T\", \"dim\" : 1}, \
		{ \"name\" : \"EVENT_SIZE\", \"type\" : \"U32\", \"dim\" : 0} \
	] \
"

struct event_zle {
  uint64_t timestamp;
  uint32_t event_size;
  uint16_t** waveform;
  size_t* n_samples;
  size_t* n_allocated_samples;
  size_t n_channels;
};


#define DATA_FORMAT_SCOPE " \
	[ \
		{ \"name\" : \"TIMESTAMP\", \"type\" : \"U64\" }, \
		{ \"name\" : \"TRIGGER_ID\", \"type\" : \"U32\" }, \
		{ \"name\" : \"WAVEFORM\", \"type\" : \"U16\", \"dim\" : 2 }, \
		{ \"name\" : \"WAVEFORM_SIZE\", \"type\" : \"SIZE_T\", \"dim\" : 1 }, \
		{ \"name\" : \"EVENT_SIZE\", \"type\" : \"SIZE_T\" } \
	] \
"

struct event_scope {
	uint64_t timestamp;
	uint32_t trigger_id;
	size_t event_size;
	uint16_t** waveform;
	size_t* n_samples;
	size_t* n_allocated_samples;
	size_t n_channels;
};


#define DATA_FORMAT_OPENDPP " \
	[ \
		{ \"name\" : \"CHANNEL\", \"type\" : \"U8\" }, \
		{ \"name\" : \"TIMESTAMP\", \"type\" : \"U64\" }, \
		{ \"name\" : \"FINE_TIMESTAMP\", \"type\" : \"U16\" }, \
		{ \"name\" : \"ENERGY\", \"type\" : \"U16\" }, \
                { \"name\" : \"PSD\", \"type\" : \"U16\" }, \
                { \"name\" : \"USER_INFO\", \"type\" : \"U64\", \"dim\" : 1 }, \
                { \"name\" : \"USER_INFO_SIZE\", \"type\" : \"SIZE_T\" }, \
		{ \"name\" : \"WAVEFORM\", \"type\" : \"U16\", \"dim\" : 1 }, \
		{ \"name\" : \"WAVEFORM_SIZE\", \"type\" : \"SIZE_T\" }, \
		{ \"name\" : \"EVENT_SIZE\", \"type\" : \"SIZE_T\" } \
	] \
"

struct event_opendpp {
  uint8_t channel;
  uint64_t timestamp;
  uint16_t fine_timestamp;
  uint16_t energy;
  uint16_t psd;
  uint64_t user_info[8];
  size_t user_info_size;
  size_t event_size;
  uint16_t* waveform;
  size_t n_allocated_samples;
  size_t n_samples;
};



#define ARRAY_SIZE(X)		(sizeof(X)/sizeof((X)[0]))

static struct event_pha* allocate_event_pha(size_t n_samples)
{
  struct event_pha* evt = (event_pha*)malloc(sizeof(*evt));
  if (evt == NULL)
    {
      std::cout<< "malloc failed" << std::endl;
    }
  evt->n_allocated_samples = n_samples;
  evt->n_samples = 0;
  for (size_t i = 0; i < ARRAY_SIZE(evt->analog_probes); ++i)
    {
      evt->analog_probes[i] = (int32_t *)malloc(evt->n_allocated_samples * sizeof(*evt->analog_probes[i]));
      if (evt->analog_probes[i] == NULL)
	{
	  std::cout << "malloc failed" << std::endl;
	}
    }
  for (size_t i = 0; i < ARRAY_SIZE(evt->digital_probes); ++i)
    {
      evt->digital_probes[i] = (uint8_t *)malloc(evt->n_allocated_samples * sizeof(*evt->digital_probes[i]));
      if (evt->digital_probes[i] == NULL)
	{
	  std::cout << "malloc failed" << std::endl;
	}
    }
  return evt;
}

static void free_event_pha(struct event_pha* evt)
{
  for (size_t i = 0; i < ARRAY_SIZE(evt->analog_probes); ++i)
    free(evt->analog_probes[i]);
  for (size_t i = 0; i < ARRAY_SIZE(evt->digital_probes); ++i)
    free(evt->digital_probes[i]);
  free(evt);
}

static struct event_psd* allocate_event_psd(size_t n_samples)
{
  struct event_psd* evt = (event_psd*)malloc(sizeof(*evt));
  if (evt == NULL)
    {
      std::cout<< "malloc failed" << std::endl;
    }
  evt->n_allocated_samples = n_samples;
  evt->n_samples = 0;
  for (size_t i = 0; i < ARRAY_SIZE(evt->analog_probes); ++i)
    {
      evt->analog_probes[i] = (int32_t *)malloc(evt->n_allocated_samples * sizeof(*evt->analog_probes[i]));
      if (evt->analog_probes[i] == NULL)
	{
	  std::cout << "malloc failed" << std::endl;
	}
    }
  for (size_t i = 0; i < ARRAY_SIZE(evt->digital_probes); ++i)
    {
      evt->digital_probes[i] = (uint8_t *)malloc(evt->n_allocated_samples * sizeof(*evt->digital_probes[i]));
      if (evt->digital_probes[i] == NULL)
	{
	  std::cout << "malloc failed" << std::endl;
	}
    }
  return evt;
}

static void free_event_psd(struct event_psd* evt)
{
  for (size_t i = 0; i < ARRAY_SIZE(evt->analog_probes); ++i)
    free(evt->analog_probes[i]);
  for (size_t i = 0; i < ARRAY_SIZE(evt->digital_probes); ++i)
    free(evt->digital_probes[i]);
  free(evt);
}



static struct event_zle* allocate_event_zle(size_t n_channels, size_t n_samples)
{
  struct event_zle* evt = (event_zle*)malloc(sizeof(*evt));
  if (evt == NULL)
    {
      std::cout << "malloc failed" << std::endl;
    }
  evt->n_channels = n_channels;
  evt->n_samples = (size_t*)malloc(evt->n_channels * sizeof(*evt->n_samples));
  if (evt->n_samples == NULL)
    {
      std::cout << "malloc failed" << std::endl;
    }
  evt->n_allocated_samples = (size_t*)malloc(evt->n_channels * sizeof(*evt->n_allocated_samples));
  if (evt->n_allocated_samples == NULL)
    {
      std::cout << "malloc failed" << std::endl;
    }
  evt->waveform = (uint16_t**)malloc(evt->n_channels * sizeof(*evt->waveform));
  if (evt->waveform == NULL)
    {
      std::cout << "malloc failed" << std::endl;
    }
  for (size_t i = 0; i < evt->n_channels; ++i)
    {
      evt->n_allocated_samples[i] = n_samples;
      evt->waveform[i] = (uint16_t*)malloc(evt->n_allocated_samples[i] * sizeof(*evt->waveform[i]));
      if (evt->waveform[i] == NULL)
	{
	  std::cout << "malloc failed" << std::endl;
	}
    }
  return evt;
}

static void free_event_zle(struct event_zle* evt)
{
  for (size_t i = 0; i < evt->n_channels; ++i)
    free(evt->waveform[i]);
  free(evt->waveform);
  free(evt->n_allocated_samples);
  free(evt->n_samples);
  free(evt);
}


static struct event_scope* allocate_event_scope(size_t n_channels, size_t n_samples)
{
  struct event_scope* evt = (event_scope*)malloc(sizeof(*evt));
  if (evt == NULL)
    {
      std::cout << "malloc failed" << std::endl;
    }
  evt->n_channels = n_channels;
  evt->n_samples = (size_t*)malloc(evt->n_channels * sizeof(*evt->n_samples));
  if (evt->n_samples == NULL)
    {
      std::cout << "malloc failed" << std::endl;
    }
  evt->n_allocated_samples = (size_t*)malloc(evt->n_channels * sizeof(*evt->n_allocated_samples));
  if (evt->n_allocated_samples == NULL)
    {
      std::cout << "malloc failed" << std::endl;
    }
  evt->waveform = (uint16_t**)malloc(evt->n_channels * sizeof(*evt->waveform));
  if (evt->waveform == NULL)
    {
      std::cout << "malloc failed" << std::endl;
    }
  for (size_t i = 0; i < evt->n_channels; ++i)
    {
      evt->n_allocated_samples[i] = n_samples;
      evt->waveform[i] = (uint16_t*)malloc(evt->n_allocated_samples[i] * sizeof(*evt->waveform[i]));
      if (evt->waveform[i] == NULL)
	{
	  std::cout << "malloc failed" << std::endl;
	}
    }
  return evt;
}

static void free_event_scope(struct event_scope* evt)
{
  for (size_t i = 0; i < evt->n_channels; ++i)
    free(evt->waveform[i]);
  free(evt->waveform);
  free(evt->n_allocated_samples);
  free(evt->n_samples);
  free(evt);
}

static struct event_opendpp* allocate_event_opendpp(size_t n_samples)
{
  struct event_opendpp* evt = (event_opendpp*)malloc(sizeof(*evt));
  if (evt == NULL)
    {
      std::cout << "malloc failed" << std::endl;
    }
  evt->n_allocated_samples = n_samples;
  evt->n_samples = 0;
  evt->waveform = (uint16_t*)malloc(evt->n_allocated_samples * sizeof(*evt->waveform));
  if (evt->waveform == NULL)
    {
      std::cout << "malloc failed" << std::endl;
    }
  return evt;
}

static void free_event_opendpp(struct event_opendpp* evt)
{
  free(evt->waveform);
  free(evt);
}



#endif /* _GLOBAL_H_ */

// 
// Global.hh ends here
