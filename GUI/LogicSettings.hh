// LogicSettings.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 1月 25 18:44:14 2023 (+0800)
// Last-Updated: 三 4月 24 21:05:19 2024 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 33
// URL: http://wuhongyi.cn 

#ifndef _LOGICSETTINGS_H_
#define _LOGICSETTINGS_H_

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

#define TABNUM_LOGICSETTINGS 6

enum class TABLOGIC
  {
    RUN = 0,
    FRONTPANEL = 1,
    VETO = 2,
    ITL = 3,
    MASK = 4,
    USERDPP = 5,
  };

#define TABMASKCOLUMNCOUNT 5

enum class TABLOGICMASK
  {
    ITLCONNECT = 0,
    CHANNELSTRIGGERMASK = 1,
    COINCIDENCEMASK = 2,
    ANTICOINCIDENCEMASK = 3,
    COINCIDENCELENGTH = 4,
  };


#define TABVETOCOLUMNCOUNT 2

enum class TABLOGICVETO
  {
    CHANNELVETOSOURCE = 0,
    ADCVETOWIDTH = 1,
  };

#define TABUSERDPPLOGICCOLUMNCOUNT 1

enum class TABLOGICUSERDPP
  {
    VALIDTRIGGERDELAY = 0,
  };


class MainWindow;

class LogicSettings : public QMainWindow
{
  Q_OBJECT
  
public:
  LogicSettings(MainWindow *parent, DeviceHandle *device);
  virtual ~LogicSettings();


private:
  void TabRun(int index);
  void TabFrontPanel(int index);
  void TabVeto(int index);
  void TabITL(int index);
  void TabMask(int index);
  void TabUserDPP(int index);
  

  void HiddenTabMaskColumn();
  void HiddenTabVetoColumn();
  void HiddenTabRunGroupScopeZLE();
  void HiddenTabUserDPPColumn();

  
private:

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
  QWidget *tab[TABNUM_LOGICSETTINGS];
  QVBoxLayout *verticalLayout[TABNUM_LOGICSETTINGS];				

  char par_name[256];
  char value[256];
  int ret = 0;
  QString stringvalue;

  TABLOGIC tablogic;
  TABLOGICMASK tablogicmask;
  TABLOGICVETO tablogicveto;
  TABLOGICUSERDPP tablogicuserdpp;

  
  //UserDPP
  QTableWidget *tableuserdpp;

  QGroupBox *groupboxuserdpp0;
  QHBoxLayout *horizontalgbuserdpp0;

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
  
  
  

  // MASK
  QTableWidget *tablemask;					   
  
  QGroupBox *groupboxmask0;
  QHBoxLayout *horizontalgbmask0;

  QGroupBox *groupboxmask1;
  QHBoxLayout *horizontalgbmask1;
  QRadioButton *rbtablemaskrow;
  QRadioButton *rbtablemaskcol;
  QRadioButton *rbtablemaskitem;
  
  QGroupBox *groupboxmask2;
  QHBoxLayout *horizontalgbmask2;
  QPushButton *pbtablemaskloadselected;
  QPushButton *pbtablemaskloadall;
  QPushButton *pbtablemaskapplyselected;
  QPushButton *pbtablemaskapplyall;

  QGroupBox *groupboxmask3;
  QHBoxLayout *horizontalgbmask3;
  QComboBox *cbmaskcopych;
  QPushButton *pbtablemaskcopy;  


  // VETO
  QTableWidget *tableveto;					   
  
  QGroupBox *groupboxveto0;
  //QHBoxLayout *horizontalgbveto0;
  QGridLayout *gridlayoutgb0;
  QLineEdit *boardvetosource;
  QLineEdit *boardvetowidth;
  QComboBox *boardvetopolarity;
  QPushButton *pbboardvetoload;
  QPushButton *pbboardvetoapply;
  
  QGroupBox *groupboxveto1;
  QHBoxLayout *horizontalgbveto1;
  QRadioButton *rbtablevetorow;
  QRadioButton *rbtablevetocol;
  QRadioButton *rbtablevetoitem;
  
  QGroupBox *groupboxveto2;
  QHBoxLayout *horizontalgbveto2;
  QPushButton *pbtablevetoloadselected;
  QPushButton *pbtablevetoloadall;
  QPushButton *pbtablevetoapplyselected;
  QPushButton *pbtablevetoapplyall;

  //QGroupBox *groupboxveto3;
  //QHBoxLayout *horizontalgbveto3;

  
  QComboBox *cbvetocopych;
  QPushButton *pbtablevetocopy; 

 
  // Front Panel
  QGroupBox *groupboxfp;
  QGridLayout *gridlayoutgbfp;
  QComboBox *cbtrgoutmode;
  QComboBox *cbgpiomode;
  QComboBox *cbsyncoutmode;
  QComboBox *cbiolevel;

  QGroupBox *groupboxlvdsdirection;
  QGridLayout *gridlayoutgblvdsdirection;
  QComboBox *cblvdsdirection[4];
  
  QGroupBox *groupboxlvdsmode;
  QGridLayout *gridlayoutgblvdsmode;
  QComboBox *cblvdsmode[4];

  QGroupBox *groupboxlvdstrgmask;
  QGridLayout *gridlayoutgblvdstrgmask;
  QLineEdit *cblvdtrgmask[16];

  QGroupBox *groupboxlvdsioreg;
  QGridLayout *gridlayoutgblvdsioreg;
  QLineEdit *cblvdioreg;

  QGroupBox *groupboxfpbt;
  QHBoxLayout *horizontalgbfpbt;
  QPushButton *pbfploadall;
  QPushButton *pbfpapplyall;

  // run
  QGroupBox *groupboxrun;
  QGridLayout *gridlayoutgbrun;
  QLineEdit *cbstartsource;
  QLineEdit *cbtriggersource;
  QComboBox *cbenautodisarmacq;
  QLineEdit *cbrundelay;
  QComboBox *cbbusyinsource;
  
  QGroupBox *groupboxrunscopezle;
  QGridLayout *gridlayoutgbrunscopezle;
  QLineEdit *cbtstampresetsource;
  QComboBox *cbpausetimestamp;
  QComboBox *cbtriggeridmode;
  QComboBox *cbentriggeroverlap;
  QComboBox *cbenmultiwindowrun;

  QGroupBox *groupboxrunclocksource;
  QGridLayout *gridlayoutgbrunclocksource;
  QComboBox *cbclocksource;
  QComboBox *cbenclockoutfp;
  
  QGroupBox *groupboxrunclock;
  QGridLayout *gridlayoutgbrunclock;
  QLineEdit *cbvolatileclockoutdelay;
  QLineEdit *cbpermanentclockoutdelay;
  
  QGroupBox *groupboxrunbt;
  QHBoxLayout *horizontalgbrunbt;
  QPushButton *pbrunloadall;
  QPushButton *pbrunapplyall;

  //itl
  QGroupBox *groupboxitl[2];
  QGridLayout *gridlayoutgbitl[2];
  QLineEdit *cbitlmask[2];
  QComboBox *cbitlpairlogic[2];
  QComboBox *cbitlmainlogic[2];
  QLineEdit *cbitlmajpritylev[2];
  QLineEdit *cbitlgatewidth[2];
  QComboBox *cbitlpolarity[2];
  QComboBox *cbitlenretrigger[2];

  
  QGroupBox *groupboxitlbt;
  QHBoxLayout *horizontalgbitlbt;
  QPushButton *pbitlloadall;
  QPushButton *pbitlapplyall;
  

private:

  void ApplyMask(unsigned short row, unsigned short column);
  void LoadMask(unsigned short row, unsigned short column);

  void ApplyVeto(unsigned short row, unsigned short column);
  void LoadVeto(unsigned short row, unsigned short column);
  void ApplyBoardVeto();
  void LoadBoardVeto();
							  

  void ApplyUserDPP(unsigned short row, unsigned short column);
  void LoadUserDPP(unsigned short row, unsigned short column);

		      
			      
private slots:
  void on_toolBox_currentChanged(int index); //ToolBox当前组变化时，显示TabWidget相应的页面
  void on_tabWidget_currentChanged(int index);  

  //userdpp
  void on_rbtableuserdpprow_clicked(); 
  void on_rbtableuserdppitem_clicked();
  void on_rbtableuserdppcol_clicked();

  void on_pbtableuserdpploadselected_clicked();
  void on_pbtableuserdpploadall_clicked();
  void on_pbtableuserdppapplyselected_clicked();
  void on_pbtableuserdppapplyall_clicked();

  void on_pbtableuserdppcopy_clicked();
  
  
  // mask
  void on_rbtablemaskrow_clicked(); 
  void on_rbtablemaskitem_clicked();
  void on_rbtablemaskcol_clicked();

  void on_pbtablemaskloadselected_clicked();
  void on_pbtablemaskloadall_clicked();
  void on_pbtablemaskapplyselected_clicked();
  void on_pbtablemaskapplyall_clicked();

  void on_pbtablemaskcopy_clicked();


  // veto
  void on_rbtablevetorow_clicked(); 
  void on_rbtablevetoitem_clicked();
  void on_rbtablevetocol_clicked();

  void on_pbtablevetoloadselected_clicked();
  void on_pbtablevetoloadall_clicked();
  void on_pbtablevetoapplyselected_clicked();
  void on_pbtablevetoapplyall_clicked();

  void on_pbtablevetocopy_clicked();


  void on_pbboardvetoload_clicked();
  void on_pbboardvetoapply_clicked();

  // front panel
  void on_pbfploadall_clicked();
  void on_pbfpapplyall_clicked();

  //run
  void on_pbrunloadall_clicked();
  void on_pbrunapplyall_clicked();

  //itl
  void on_pbitlloadall_clicked();
  void on_pbitlapplyall_clicked();
  
  
};

#endif /* _LOGICSETTINGS_H_ */

// 
// LogicSettings.hh ends here
