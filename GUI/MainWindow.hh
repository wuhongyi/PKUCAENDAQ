// MainWindow.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 12月 17 15:18:35 2021 (+0800)
// Last-Updated: 六 5月 24 21:06:15 2025 (+0900)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 78
// URL: http://wuhongyi.cn 

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "ControlPanel.hh"

#include "DeviceHandle.hh"
#include "ReadoutThread.hh"
#include "RateThread.hh"
#include "RealDecoderThread.hh"
#include "BasicSettings.hh"
#include "LogicSettings.hh"
#include "OnlineRate.hh"
#include "Debug.hh"

#include "QtWidgets/QMainWindow"
#include "QtWidgets"
#include "QStringList"
#include "QString"
#include "QtConcurrent/QtConcurrentRun"

#include "nlohmann/json.hpp"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef struct OPENDPP_PARS
{
  unsigned int SL[MAXMODULENUM][MAXCHANNELNUM];
  unsigned int SG[MAXMODULENUM][MAXCHANNELNUM];
  unsigned int TAU[MAXMODULENUM][MAXCHANNELNUM];
} OPENDPP_PARS;



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  MainWindow(QWidget *parent = Q_NULLPTR);
  virtual ~MainWindow();

  
  void LoadConfigure();
  nlohmann::json GetJSON();

  void SetOutputSettings(QString folder, QString prefix, QString run, bool saved);
  void GetOutputSettings(QString &folder, QString &prefix, QString &run, bool &saved);
  void ShowOutputSettings();
  void SaveOutputSettings();

  bool DAQRunning() {return mReadoutThread->IsRunning();}


  
  // scope ZLE PHA PSD
  void UpdateOnlineRateSelfTrgRate(unsigned short mod,unsigned short ch, QString value);
  void UpdateOnlineRateSelfTrgRateOpen(unsigned short mod,unsigned short ch, QString value);
  void UpdateOnlineRateOutputRateOpen(unsigned short mod,unsigned short ch, QString value);
  
  // PHA PSD
  void UpdateOnlineRateChRealtimeMonitor(unsigned short mod, unsigned short ch, QString value);
  void UpdateOnlineRateChDeadtimeMonitor(unsigned short mod, unsigned short ch, QString value);
  void UpdateOnlineRateChTriggerCnt(unsigned short mod, unsigned short ch, QString value);
  void UpdateOnlineRateChSavedEventCnt(unsigned short mod, unsigned short ch, QString value);
  void UpdateOnlineRateChWaveCnt(unsigned short mod, unsigned short ch, QString value);

  // scope
  void UpdateOnlineRateModRealtime(unsigned short mod, QString value);
  void UpdateOnlineRateModDeadtime(unsigned short mod, QString value);
  void UpdateOnlineRateModLivetime(unsigned short mod, QString value);



  
  void UpdateOutputDataSize(unsigned short mod, unsigned long value);
  void UpdateOutputDataFlowSize(unsigned short mod, unsigned long value);


  void UpdateDecoderOPENDPPSL(unsigned short mod, unsigned short ch, unsigned int sl);
  void UpdateDecoderOPENDPPSG(unsigned short mod, unsigned short ch, unsigned int sg);
  void UpdateDecoderOPENDPPTAU(unsigned short mod, unsigned short ch, unsigned int tau);


  unsigned int ReadDecoderOPENDPPSL(unsigned short mod, unsigned short ch);
  unsigned int ReadDecoderOPENDPPSG(unsigned short mod, unsigned short ch);
  unsigned int ReadDecoderOPENDPPTAU(unsigned short mod, unsigned short ch);

  
private:

  void PopulateToolBar();
  void PopulateMenu();
    
  void LoadConfigureFile(QString filename);
  void SaveParameters(QString filename);			  
			     
private slots:


public slots:
  void AboutSoftware();
  void ConnectModule();
  void OpenOutputSettings();
  void SendTriggerForAllModule();
  
  void ShowBasicSettings();
  void ShowLogicSettings();
  void ShowOnlineRate();
  void ShowDebug();
  
  void StartAcquisition();
  void StopAcquisition();


  void SaveDefaultParameters();
  void SaveAsParameters();  
  void LoadParameters();
  
private:

  QWidget *mCenterWidget;

  QToolBar *mMainToolBar;
  QStatusBar *mMainStatusBar;
  QPushButton* mStatusLED;
  QProgressBar *mMainProgressBar;
  QLabel *mMainStatusBarText;
  
  QString mTmpConfigFileName;
  QSettings *mConfigFile;
  QString mConfigFileName;


  ControlPanel *mControlPanel;
  void CreateDockWindows(int width);

  QMenu *mFileMenu;
  // QMenu *mConfigMenu;
  // QMenu *mExpertLogicMenu;
  // QMenu *mDebugMenu;
  QMenu *mHelpMenu;
  
  QAction *mExitAct;
  QAction *mExitMenuAct;
  QAction *mAboutAct;
  QAction *mBasicSettingsAct;
  QAction *mLogicSettingsAct;
  QAction *mOnlineRateAct;
  QAction *mDebugAct;

  
  QAction *mConnectMenuAct;
  QAction *mLoadMenuAct;
  QAction *mSaveMenuAct;
  QAction *mInfoMenuAct;
  QAction *mSaveasMenuAct;
  QAction *mOpenSettingsMenuAct;
  QAction *mOutputConfigMenuAct;
  QAction *mSWTriggerMenuAct;
  
  DeviceHandle *mDevice = nullptr;
  ReadoutThread *mReadoutThread = nullptr;
  RateThread *mRateThread = nullptr;
  RealDecoderThread *mRealDecoderThread = nullptr;
  BasicSettings *mBasicSettings = nullptr;
  LogicSettings *mLogicSettings = nullptr;
  OnlineRate *mOnlineRate = nullptr;
  Debug *mDebug = nullptr;

  
  
  nlohmann::json  json;

  // Data Save Global Variable
  QString mOutput_folder;
  QString mOutput_prefix;
  QString mOutput_run;
  //bool mOutput_Saved;
  
  QLineEdit *leFolder;
  QLineEdit *lePrefix;
  QLineEdit *leRun;
  QCheckBox *leSaved;


  OPENDPP_PARS opendpppars;
  
}; 

#endif /* _MAINWINDOW_H_ */

// 
// MainWindow.hh ends here
