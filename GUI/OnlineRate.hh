// OnlineRate.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 3月 11 16:34:28 2023 (+0800)
// Last-Updated: 六 1月 13 11:12:05 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 17
// URL: http://wuhongyi.cn 

#ifndef _ONLINERATE_H_
#define _ONLINERATE_H_


#include "Global.hh"
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

class MainWindow;
class ModuleRate;

class OnlineRate : public QMainWindow
{
  Q_OBJECT
  
public:
  OnlineRate(MainWindow *parent, DeviceHandle *device);
  virtual ~OnlineRate();

  // scope ZLE PHA PSD
  void UpdateOnlineRateSelfTrgRate(unsigned short mod,unsigned short ch, QString value);

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


  /*
  void UpdateOnlineRateInput(unsigned short mod, unsigned short ch, double value);
  void UpdateOnlineRateOutput(unsigned short mod, unsigned short ch, double value);
  */
  void UpdateOutputDataSize(unsigned short mod, unsigned long value);

  
private:

  MainWindow * const mMainWindow;
  DeviceHandle *mDevice = nullptr;

  QWidget *centralWidget;

  ModuleRate *mModuleRate[MAXMODULENUM];
  QPushButton *ratebt[MAXMODULENUM];
private:

  QTableWidget *tableonline;
  QVBoxLayout *verticalLayout;

			     
private slots:
  void VisibleModuleRate();
  
};


#define ONLINERATECOLUMN 6
#define ONLINERATEPERSECTIONCH 16

class ModuleRate : public QWidget
{
  Q_OBJECT
  
public:
  ModuleRate(QWidget *parent, DeviceHandle *device, unsigned short mod);
  virtual ~ModuleRate();


  void UpdateSelfTrgRate(unsigned short ch, QString value);
  void UpdateChRealtimeMonitor(unsigned short ch, QString value);
  void UpdateChDeadtimeMonitor(unsigned short ch, QString value);
  void UpdateChTriggerCnt(unsigned short ch, QString value);
  void UpdateChSavedEventCnt(unsigned short ch, QString value);
  void UpdateChWaveCnt(unsigned short ch, QString value);

  void UpdateModRealtime(QString value);
  void UpdateModDeadtime(QString value);
  void UpdateModLivetime(QString value);



  
  /*
  void UpdateInput(unsigned short ch, double value);
  void UpdateOutput(unsigned short ch, double value);
  */
  
private:
  DeviceHandle *mDevice = nullptr;
  unsigned short mMod;
  unsigned short mGroup;
  QTableWidget *tablerate;

private slots:
  void VisibleRate();
  
};

#endif /* _ONLINERATE_H_ */

// 
// OnlineRate.hh ends here
