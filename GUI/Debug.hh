// Debug.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 2月 16 15:49:18 2023 (+0800)
// Last-Updated: 二 2月  4 15:10:30 2025 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 23
// URL: http://wuhongyi.cn 

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "Global.hh"
#include "DeviceHandle.hh"

#include <vector>

#include <QTime>
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

#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#define TABNUM_DEBUG 7

enum class TABDEBUG
  {
    PHAPSD = 0,
    SCOPEZLESINGLE = 1,
    SCOPEZLE015 = 2,
    SCOPEZLE1631 = 3,
    SCOPEZLE3247 = 4,
    SCOPEZLE4863 = 5,
    OPEN = 6,
  };



class MainWindow;

class Debug : public QMainWindow
{
  Q_OBJECT
  
public:
  Debug(MainWindow *parent, DeviceHandle *device);
  virtual ~Debug();

private:

  void on_toolBox_currentChanged(int index);
  void on_tabWidget_currentChanged(int index);

private:

  MainWindow * const mMainWindow;
  DeviceHandle *mDevice = nullptr;

  QWidget *centralWidget;
  QSplitter *splitter;// 左右区域分割
  QSplitter *leftsplitter;
  QToolBox *toolBox;// 内部装 QWidget page
  QTabWidget *tabWidget; // 内部装 QWidget tab


  QGroupBox *choosebutton1;
  QGridLayout *gridgroupbox1;
  QComboBox *combosourcesch;
  QPushButton *btngetonlinedebug;
  
  QStatusBar *statusbar;
  QLabel *statusinfo;
  
  // QToolBox
  QWidget *pagemod[MAXMODULENUM];
  QGridLayout *gridpagemod[MAXMODULENUM];//

  // QTabWidget
  QWidget *tab[TABNUM_DEBUG];
  QGridLayout *verticalLayout[TABNUM_DEBUG];


  TABDEBUG tabdebug;

  
  
  QChartView *chartphapsdView[3];
  QChart *chartphapsd[3];

  QChartView *chartscopezleview[MAXCHANNELNUM];
  QChart *chartscopezle[MAXCHANNELNUM];
  QChartView *chartscopezleviewsingle;
  QChart *chartscopezlesingle;

  QChartView *chartopenview;
  QChart *chartopen;
  
  
private:
  void TabPHAPSD(int index);
  void TabScopeZLESingle(int index);
  void TabScopeZLECh0_15(int index);
  void TabScopeZLECh16_31(int index);
  void TabScopeZLECh32_47(int index);
  void TabScopeZLECh48_63(int index);
  void TabOPEN(int index);

  
signals:
  void SetOnlineDebug(unsigned short mod, unsigned short ch);
			     
public slots:

  void UpdateOnlineDebugPHA(event_pha *evt_pha);
  void UpdateOnlineDebugPSD(event_psd *evt_psd);
  void UpdateOnlineDebugZLE(event_zle *evt_zle);
  void UpdateOnlineDebugScope(event_scope *evt_scope);
  void UpdateOnlineDebugOPENDPP(event_opendpp *evt_opendpp);


						     
private slots:
  
  void on_btngetonlinedebug_clicked();
  
};

#endif /* _DEBUG_H_ */  
// 
// Debug.hh ends here
