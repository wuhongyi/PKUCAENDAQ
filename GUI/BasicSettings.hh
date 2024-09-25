// BasicSettings.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 10月 21 20:26:00 2022 (+0800)
// Last-Updated: 五 9月 13 00:56:54 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 88
// URL: http://wuhongyi.cn 

#ifndef _BASICSETTINGS_H_
#define _BASICSETTINGS_H_

#include "Global.hh"
#include "user_dpp_regs.hpp"
#include "DeviceHandle.hh"

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QGridLayout>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define TABNUM_BASICSETTINGS 11

enum class TABBASIC
  {
    ADC = 0,
    TRIGGER = 1,
    WAVEFORM = 2,
    RECORD = 3,
    SCOPE = 4,
    PHA = 5,
    PSD1 = 6,
    PSD2 = 7,
    ZLE = 8,
    DEBUG = 9,
    USERDPP = 10,
  };



#define TABADCCOLUMNCOUNT 9

enum class TABBASICADC
  {
    CHGAIN = 0,
    INPUTDELAY = 1,
    CHENABLE = 2,
    WAVESOURCE = 3,
    DCOFFSET = 4,
    POLARITY = 5,

    SIGNALOFFSET = 6,
    GAINFACTOR = 7,
    ADCTOVOLTS = 8,
  };

#define TABTRIGGERCOLUMNCOUNT 6

enum class TABBASICTRIGGER
  {
    WAVETRIGGERSOURCE = 0,
    EVENTTRIGGERSOURCE = 1,
    TRIGGERTHR = 2,
    SELFTRIGGERWIDTH = 3,
    TRIGGERTHRMODE = 4,
    SELFTRIGGEREDGE = 5,
 
  };

#define TABWAVEFORMCOLUMNCOUNT 15

enum class TABBASICWAVEFORM
  {
    CHPRETRIGGER = 0,
    CHRECORDLENGTH = 1,
    DOWNSAMPLINGFACTOR = 2,
    ANALOGPROBE0PHA = 3,
    ANALOGPROBE1PHA = 4,
    DIGITALPROBE0PHA = 5,
    DIGITALPROBE1PHA = 6,
    DIGITALPROBE2PHA = 7,
    DIGITALPROBE3PHA = 8,  
    ANALOGPROBE0PSD = 9,
    ANALOGPROBE1PSD = 10,
    DIGITALPROBE0PSD = 11,
    DIGITALPROBE1PSD = 12,
    DIGITALPROBE2PSD = 13,
    DIGITALPROBE3PSD = 14,
    
  };

#define TABRECORDCOLUMNCOUNT 5

enum class TABBASICRECORD
  {

    EVENTSELECTOR = 0,
    WAVESELECTOR = 1,
    ENERGYSKIMLOWDISCRIMINATOR = 2,
    ENERGYSKIMHIGHDISCRIMINATOR = 3,
    WAVESAVING = 4,

  };


#define TABSCOPECOLUMNCOUNT 4

enum class TABBASICSCOPE
  {
    SAMPLEOVERTHRESHOLD = 0,
    OVERTHRESHOLDVETOWIDTH = 1,
    CHSUPPRTHR = 2,
    CHSUPPRSAMPLESOVERTHRESHOLD = 3,
    
    // SamplesOverThreshold
    // OverThresholdVetoWidth
    // ChSupprThr
    // ChSupprSamplesOverThreshold
  };

#define TABPHACOLUMNCOUNT 12 

enum class TABBASICPHA
  {
    TRIGGERRISETIME = 0,
    RETRIGGERGUARD = 1,
    RISETIME = 5,
    FLATTOP = 6,
    PEAKINGPOSITION = 8,
    PEAKINGAVG = 9,
    POLEZERO = 7,
    FINEGAIN = 10,
    LFLIMITATION = 11,
    BASELINEAVG = 3,
    BASELINEGUARD = 4,
    PILEUPGUARD = 2,
  };


#define TABPSD1COLUMNCOUNT 8

enum class TABBASICPSD1
  {
    SMOOTHINGFACTOR = 0,
    TRIGGERSMOOTHING = 1,
    TRIGGERSELECTION = 2,
    CFDDELAY = 3,
    CFDFRACTION = 4,
    RETRIGGERGUARD = 5,
    TRIGGERHYSTERESIS = 6,
    PILEUPGAP = 7,
  };

#define TABPSD2COLUMNCOUNT 13

enum class TABBASICPSD2
  {
    BASELINEAVG = 0,
    ABSOLUTEBASELINE = 1,
    BASELINEGUARD = 2,
    CHARGESMOOTHING = 3,
    GATELONG = 4,
    GATESHORT = 5,
    GATEOFFSET = 6,
    LONGPEDESTAL = 7,
    SHORTPEDESTAL = 8,
    ENERGYGAIN = 9,
    NEUTRONTHRESHOLD = 10,
    EVENTNEUTRONREJECT = 11,
    WAVENEUTRONREJECT = 12,
  };


#define TABZLECOLUMNCOUNT 7

enum class TABBASICZLE
  {
    PRETRIGGER = 0,
    SUPPERTHR = 1,
    LOOKBACK = 2,
    LOOKFORWARD = 3,
    ENZLESUPPR = 4,
    VALUESOURCE = 5,
    VALUEREGISTER = 6,
  };


#define TABUSERDPPCOLUMNCOUNT 17

enum class TABBASICUSERDPP
  {
    POLARITY = 0,
    XIAFL = 1,
    XIAFLFG = 2,
    THRESHOLD = 3,
    PRETRIGGER = 4,
    WAVELENGTH = 5,
    DATAFORMAT = 6,
    QOFFSET = 7,
    QSHORT = 8,
    QLONG = 9,
    BL2N = 10,
    BLHOLD = 11,
    RTOFFSET = 12,
    RTGATE = 13,
    XIAOFFSET = 14,
    XIASL = 15,
    XIASG = 16,
  };





class MainWindow;

class BasicSettings : public QMainWindow
{
  Q_OBJECT

public:
  BasicSettings(MainWindow *parent, DeviceHandle *device);
  virtual ~BasicSettings();

private:
  void TabADC(int index);
  void TabTrigger(int index);
  void TabWaveform(int index);
  void TabRecord(int index);
  void TabScope(int index);
  void TabPHA(int index);
  void TabPSD1(int index);
  void TabPSD2(int index);
  void TabZLE(int index);
  void TabDebug(int index);
  void TabUserDPP(int index);

  
  void HiddenTabADCColumn();
  void HiddenTabADC2745VGAGain();
  void HiddenTabTriggerColumn();
  void HiddenTabWaveformColumn();
  void HiddenTabRecordColumn();
  void HiddenTaScopebGroupScope();
  void HiddenTabScopeColumn();
  void HiddenTabPHAColumn();
  void HiddenTabPSD1Column();
  void HiddenTabPSD2Column();
  void HiddenTabZLEColumn();
  void HiddenTabUserDPPColumn();
  

private:

  // QGridLayout 网格化布局
  // QVBoxLayout 上下排列
  // QHBoxLayout 水平排列
  
  MainWindow * const mMainWindow;
  DeviceHandle *mDevice = nullptr;
  
  QWidget *centralWidget;
  QSplitter *splitter;// 左右区域分割
  QToolBox *toolBox;// 内部装 QWidget page
  QTabWidget *tabWidget; // 内部装 QWidget tab

  QStatusBar *statusbar;
  QLabel *statusinfo;
  
  // QToolBox
  QWidget *pagemod[MAXMODULENUM];
  QGridLayout *gridpagemod[MAXMODULENUM];//

  // QTabWidget
  QWidget *tab[TABNUM_BASICSETTINGS];
  QVBoxLayout *verticalLayout[TABNUM_BASICSETTINGS];


  char par_name[256];
  char value[256];
  int ret = 0;
  QString stringvalue;


  TABBASIC tabbasic;
  TABBASICADC tabbasicadc;
  TABBASICTRIGGER tabbasictrigger;
  TABBASICWAVEFORM tabbasicwaveform;
  TABBASICRECORD tabbasicrecord;
  TABBASICSCOPE tabbasicscope;
  TABBASICPHA tabbasicpha;
  TABBASICPSD1 tabbasicpsd1;
  TABBASICPSD2 tabbasicpsd2;
  TABBASICZLE tabbasiczle;
  TABBASICUSERDPP tabbasicuserdpp;

  // UserDPP
  QTableWidget *tableuserdpp;

  QGroupBox *groupboxuserdpp0;
  QHBoxLayout *horizontalgbuserdpp0;
  QLineEdit *userdppdebugreg;
  QLineEdit *userdppdebugvalue;
  QPushButton *pbuserdppdebugregread;
  QPushButton *pbuserdppdebugregwrite;

  
  QGroupBox *groupboxuserdpp1;
  QHBoxLayout *horizontalgbuserdpp1;
  QRadioButton *rbtableuserdpprow;
  QRadioButton *rbtableuserdppcol;
  QRadioButton *rbtableuserdppitem;
  
  QGroupBox *groupboxuserdpp2;
  QHBoxLayout *horizontalgbuserdpp2;
  QPushButton *pbtableuserdpploadselected;
  QPushButton *pbtableuserdpploadall;
  QPushButton *pbtableuserdppapplyselected;
  QPushButton *pbtableuserdppapplyall;

  QGroupBox *groupboxuserdpp3;
  QHBoxLayout *horizontalgbuserdpp3;
  QComboBox *cbuserdppcopych;
  QPushButton *pbtableuserdppcopy;     
  
  // ADC
  QTableWidget *tableadc;					   
  
  QGroupBox *groupboxadc0;
  QHBoxLayout *horizontalgbadc0;
  QLineEdit *adcvgagain2745[4];

  
  QGroupBox *groupboxadc1;
  QHBoxLayout *horizontalgbadc1;
  QRadioButton *rbtableadcrow;
  QRadioButton *rbtableadccol;
  QRadioButton *rbtableadcitem;
  
  QGroupBox *groupboxadc2;
  QHBoxLayout *horizontalgbadc2;
  QPushButton *pbtableadcloadselected;
  QPushButton *pbtableadcloadall;
  QPushButton *pbtableadcapplyselected;
  QPushButton *pbtableadcapplyall;

  QGroupBox *groupboxadc3;
  QHBoxLayout *horizontalgbadc3;
  QComboBox *cbadccopych;
  QPushButton *pbtableadccopy;  

  // trigger
  QTableWidget *tabletrigger;					   
  
  QGroupBox *groupboxtrigger0;
  QHBoxLayout *horizontalgbtrigger0;

  QGroupBox *groupboxtrigger1;
  QHBoxLayout *horizontalgbtrigger1;
  QRadioButton *rbtabletriggerrow;
  QRadioButton *rbtabletriggercol;
  QRadioButton *rbtabletriggeritem;
  
  QGroupBox *groupboxtrigger2;
  QHBoxLayout *horizontalgbtrigger2;
  QPushButton *pbtabletriggerloadselected;
  QPushButton *pbtabletriggerloadall;
  QPushButton *pbtabletriggerapplyselected;
  QPushButton *pbtabletriggerapplyall;

  QGroupBox *groupboxtrigger3;
  QHBoxLayout *horizontalgbtrigger3;
  QComboBox *cbtriggercopych;
  QPushButton *pbtabletriggercopy;    

  // record
  QTableWidget *tablerecord;		   
  
  QGroupBox *groupboxrecord0;
  QHBoxLayout *horizontalgbrecord0;
  QComboBox *cbrecordendatareduction;
  
  
  QGroupBox *groupboxrecord1;
  QHBoxLayout *horizontalgbrecord1;
  QRadioButton *rbtablerecordrow;
  QRadioButton *rbtablerecordcol;
  QRadioButton *rbtablerecorditem;
  
  QGroupBox *groupboxrecord2;
  QHBoxLayout *horizontalgbrecord2;
  QPushButton *pbtablerecordloadselected;
  QPushButton *pbtablerecordloadall;
  QPushButton *pbtablerecordapplyselected;
  QPushButton *pbtablerecordapplyall;

  QGroupBox *groupboxrecord3;
  QHBoxLayout *horizontalgbrecord3;
  QComboBox *cbrecordcopych;
  QPushButton *pbtablerecordcopy;  

  // Wave
  QTableWidget *tablewaveform;					   
  
  QGroupBox *groupboxwaveform0;
  QHBoxLayout *horizontalgbwaveform0;


  
  QGroupBox *groupboxwaveform1;
  QHBoxLayout *horizontalgbwaveform1;
  QRadioButton *rbtablewaveformrow;
  QRadioButton *rbtablewaveformcol;
  QRadioButton *rbtablewaveformitem;
  
  QGroupBox *groupboxwaveform2;
  QHBoxLayout *horizontalgbwaveform2;
  QPushButton *pbtablewaveformloadselected;
  QPushButton *pbtablewaveformloadall;
  QPushButton *pbtablewaveformapplyselected;
  QPushButton *pbtablewaveformapplyall;

  QGroupBox *groupboxwaveform3;
  QHBoxLayout *horizontalgbwaveform3;
  QComboBox *cbwaveformcopych;
  QPushButton *pbtablewaveformcopy;  

  // scope
  QTableWidget *tablescope;			 
 
  QGroupBox *groupboxscope0;
  QHBoxLayout *horizontalgbscope0;
  QComboBox *cbscopeenchsuppr;

  QGroupBox *groupboxscope3;
  QHBoxLayout *horizontalgbscope3;
  QComboBox *cbscopedecimationfactor;
  QLineEdit *scopepretrigger;
  QLineEdit *scoperecordlength;
  QLineEdit *scopetriggerdelay;
  
  
  QGroupBox *groupboxscope1;
  QHBoxLayout *horizontalgbscope1;
  QRadioButton *rbtablescoperow;
  QRadioButton *rbtablescopecol;
  QRadioButton *rbtablescopeitem;
  
  QGroupBox *groupboxscope2;
  QHBoxLayout *horizontalgbscope2;
  QPushButton *pbtablescopeloadselected;
  QPushButton *pbtablescopeloadall;
  QPushButton *pbtablescopeapplyselected;
  QPushButton *pbtablescopeapplyall;



  
  QComboBox *cbscopecopych;
  QPushButton *pbtablescopecopy;  


  
  // PHA
  QTableWidget *tablepha;					   
  
  QGroupBox *groupboxpha0;
  QHBoxLayout *horizontalgbpha0;

  QGroupBox *groupboxpha1;
  QHBoxLayout *horizontalgbpha1;
  QRadioButton *rbtablepharow;
  QRadioButton *rbtablephacol;
  QRadioButton *rbtablephaitem;
  
  QGroupBox *groupboxpha2;
  QHBoxLayout *horizontalgbpha2;
  QPushButton *pbtablephaloadselected;
  QPushButton *pbtablephaloadall;
  QPushButton *pbtablephaapplyselected;
  QPushButton *pbtablephaapplyall;

  QGroupBox *groupboxpha3;
  QHBoxLayout *horizontalgbpha3;
  QComboBox *cbphacopych;
  QPushButton *pbtablephacopy;  



  // PSD1
  QTableWidget *tablepsd1;					   
  
  QGroupBox *groupboxpsd10;
  QHBoxLayout *horizontalgbpsd10;

  QGroupBox *groupboxpsd11;
  QHBoxLayout *horizontalgbpsd11;
  QRadioButton *rbtablepsd1row;
  QRadioButton *rbtablepsd1col;
  QRadioButton *rbtablepsd1item;
  
  QGroupBox *groupboxpsd12;
  QHBoxLayout *horizontalgbpsd12;
  QPushButton *pbtablepsd1loadselected;
  QPushButton *pbtablepsd1loadall;
  QPushButton *pbtablepsd1applyselected;
  QPushButton *pbtablepsd1applyall;

  QGroupBox *groupboxpsd13;
  QHBoxLayout *horizontalgbpsd13;
  QComboBox *cbpsd1copych;
  QPushButton *pbtablepsd1copy;  


  // PSD2
  QTableWidget *tablepsd2;					   
  
  QGroupBox *groupboxpsd20;
  QHBoxLayout *horizontalgbpsd20;

  QGroupBox *groupboxpsd21;
  QHBoxLayout *horizontalgbpsd21;
  QRadioButton *rbtablepsd2row;
  QRadioButton *rbtablepsd2col;
  QRadioButton *rbtablepsd2item;
  
  QGroupBox *groupboxpsd22;
  QHBoxLayout *horizontalgbpsd22;
  QPushButton *pbtablepsd2loadselected;
  QPushButton *pbtablepsd2loadall;
  QPushButton *pbtablepsd2applyselected;
  QPushButton *pbtablepsd2applyall;

  QGroupBox *groupboxpsd23;
  QHBoxLayout *horizontalgbpsd23;
  QComboBox *cbpsd2copych;
  QPushButton *pbtablepsd2copy;  


  // ZLE
  QTableWidget *tablezle;					   
  
  QGroupBox *groupboxzle0;
  QHBoxLayout *horizontalgbzle0;
  QLineEdit *zlerecordlength;

  
  QGroupBox *groupboxzle1;
  QHBoxLayout *horizontalgbzle1;
  QRadioButton *rbtablezlerow;
  QRadioButton *rbtablezlecol;
  QRadioButton *rbtablezleitem;
  
  QGroupBox *groupboxzle2;
  QHBoxLayout *horizontalgbzle2;
  QPushButton *pbtablezleloadselected;
  QPushButton *pbtablezleloadall;
  QPushButton *pbtablezleapplyselected;
  QPushButton *pbtablezleapplyall;

  QGroupBox *groupboxzle3;
  QHBoxLayout *horizontalgbzle3;
  QComboBox *cbzlecopych;
  QPushButton *pbtablezlecopy;


  // Debug
  QGroupBox *groupboxtest;
  QGridLayout *gridlayoutgbtest;
  QLineEdit *testpulseperiod;
  QLineEdit *testpulsewidth;
  QLineEdit *testpulselowlevel;
  QLineEdit *testpulsehighlevel;
  
  QGroupBox *groupboxdac;
  QGridLayout *gridlayoutgbdac;
  QComboBox *dacmode;
  QLineEdit *dacstaticlevel;
  QLineEdit *dacchselect;

  QGroupBox *groupboxipe;
  QGridLayout *gridlayoutgbipe;
  QLineEdit *ipeamplitude;
  QLineEdit *ipebaseline;
  QLineEdit *ipedecaytime;
  QLineEdit *iperate;
  QComboBox *ipetimemode;
  
  
  QGroupBox *groupboxdebug;
  QHBoxLayout *horizontalgbdebug;
  QPushButton *pbdebugloadall;
  QPushButton *pbdebugapplyall;



  

  
  
private:

  void ApplyADC(unsigned short row, unsigned short column);
  void LoadADC(unsigned short row, unsigned short column);

  void ApplyTrigger(unsigned short row, unsigned short column);
  void LoadTrigger(unsigned short row, unsigned short column);


  void ApplyWaveform(unsigned short row, unsigned short column);
  void LoadWaveform(unsigned short row, unsigned short column);
  
  void ApplyRecord(unsigned short row, unsigned short column);
  void LoadRecord(unsigned short row, unsigned short column);


  void ApplyScope(unsigned short row, unsigned short column);
  void LoadScope(unsigned short row, unsigned short column);
  
  
  void ApplyPHA(unsigned short row, unsigned short column);
  void LoadPHA(unsigned short row, unsigned short column);


  
  void ApplyPSD1(unsigned short row, unsigned short column);
  void LoadPSD1(unsigned short row, unsigned short column);
			     
  void ApplyPSD2(unsigned short row, unsigned short column);
  void LoadPSD2(unsigned short row, unsigned short column);

  void ApplyZLE(unsigned short row, unsigned short column);
  void LoadZLE(unsigned short row, unsigned short column);

  void ApplyDebug();
  void LoadDebug();
  
  void ApplyUserDPP(unsigned short row, unsigned short column);
  void LoadUserDPP(unsigned short row, unsigned short column);



		  
							 
private slots:
  void on_toolBox_currentChanged(int index); //ToolBox当前组变化时，显示TabWidget相应的页面
  void on_tabWidget_currentChanged(int index);


  // userdpp
  void on_rbtableuserdpprow_clicked(); 
  void on_rbtableuserdppitem_clicked();
  void on_rbtableuserdppcol_clicked();

  void on_pbtableuserdpploadselected_clicked();
  void on_pbtableuserdpploadall_clicked();
  void on_pbtableuserdppapplyselected_clicked();
  void on_pbtableuserdppapplyall_clicked();

  void on_pbtableuserdppcopy_clicked();

  void on_pbuserdppdebugregread_clicked();
  void on_pbuserdppdebugregwrite_clicked();

  
  // adc
  void TableADCCheckState(int row, int column);
  
  void on_rbtableadcrow_clicked(); 
  void on_rbtableadcitem_clicked();
  void on_rbtableadccol_clicked();

  void on_pbtableadcloadselected_clicked();
  void on_pbtableadcloadall_clicked();
  void on_pbtableadcapplyselected_clicked();
  void on_pbtableadcapplyall_clicked();

  void on_pbtableadccopy_clicked();

  // trigger
    void TableTriggerCheckState(int row, int column);

  void on_rbtabletriggerrow_clicked(); 
  void on_rbtabletriggeritem_clicked();
  void on_rbtabletriggercol_clicked();

  void on_pbtabletriggerloadselected_clicked();
  void on_pbtabletriggerloadall_clicked();
  void on_pbtabletriggerapplyselected_clicked();
  void on_pbtabletriggerapplyall_clicked();

  void on_pbtabletriggercopy_clicked();

  //waveform
  void TableWaveformCheckState(int row, int column);

  void on_rbtablewaveformrow_clicked(); 
  void on_rbtablewaveformitem_clicked();
  void on_rbtablewaveformcol_clicked();

  void on_pbtablewaveformloadselected_clicked();
  void on_pbtablewaveformloadall_clicked();
  void on_pbtablewaveformapplyselected_clicked();
  void on_pbtablewaveformapplyall_clicked();

  void on_pbtablewaveformcopy_clicked();

  // record
  void TableRecordCheckState(int row, int column);
  
  void on_rbtablerecordrow_clicked(); 
  void on_rbtablerecorditem_clicked();
  void on_rbtablerecordcol_clicked();

  void on_pbtablerecordloadselected_clicked();
  void on_pbtablerecordloadall_clicked();
  void on_pbtablerecordapplyselected_clicked();
  void on_pbtablerecordapplyall_clicked();

  void on_pbtablerecordcopy_clicked();


  //scope
  void on_rbtablescoperow_clicked(); 
  void on_rbtablescopeitem_clicked();
  void on_rbtablescopecol_clicked();

  void on_pbtablescopeloadselected_clicked();
  void on_pbtablescopeloadall_clicked();
  void on_pbtablescopeapplyselected_clicked();
  void on_pbtablescopeapplyall_clicked();

  void on_pbtablescopecopy_clicked();
  
  
  // pha
  void TablePHACheckState(int row, int column);

  
  void on_rbtablepharow_clicked(); 
  void on_rbtablephaitem_clicked();
  void on_rbtablephacol_clicked();

  void on_pbtablephaloadselected_clicked();
  void on_pbtablephaloadall_clicked();
  void on_pbtablephaapplyselected_clicked();
  void on_pbtablephaapplyall_clicked();

  void on_pbtablephacopy_clicked();

  // psd1
  void TablePSD1CheckState(int row, int column);

  
  void on_rbtablepsd1row_clicked(); 
  void on_rbtablepsd1item_clicked();
  void on_rbtablepsd1col_clicked();

  void on_pbtablepsd1loadselected_clicked();
  void on_pbtablepsd1loadall_clicked();
  void on_pbtablepsd1applyselected_clicked();
  void on_pbtablepsd1applyall_clicked();

  void on_pbtablepsd1copy_clicked();


  // psd2
  void TablePSD2CheckState(int row, int column);

  
  void on_rbtablepsd2row_clicked(); 
  void on_rbtablepsd2item_clicked();
  void on_rbtablepsd2col_clicked();

  void on_pbtablepsd2loadselected_clicked();
  void on_pbtablepsd2loadall_clicked();
  void on_pbtablepsd2applyselected_clicked();
  void on_pbtablepsd2applyall_clicked();

  void on_pbtablepsd2copy_clicked();




  // zle
  void TableZLECheckState(int row, int column);

  
  void on_rbtablezlerow_clicked(); 
  void on_rbtablezleitem_clicked();
  void on_rbtablezlecol_clicked();

  void on_pbtablezleloadselected_clicked();
  void on_pbtablezleloadall_clicked();
  void on_pbtablezleapplyselected_clicked();
  void on_pbtablezleapplyall_clicked();

  void on_pbtablezlecopy_clicked();

  //debug
  void on_pbdebugloadall_clicked();
  void on_pbdebugapplyall_clicked();
  
  
};


#endif /* _BASICSETTINGS_H_ */
// 
// BasicSettings.hh ends here
