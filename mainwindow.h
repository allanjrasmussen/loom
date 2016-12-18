/* Digiweave is a program for controling a digital loom
 * Programmer: Allan Rasmussen
 * Date: may 2015
 *
 *  Raspberry Pi v/2
 *
*
 *;============Begin Minimum Section Requirements============

[WIF]
Version=1.1                 ;required constant (real)
Date=April 20, 1997         ;required constant (ASCII string)
Developers=wif@mhsoft.com   ;required (ASCII string) (current email contact)
Source Program=             ;required (ASCII string)
Source Version=             ;optional (ASCII string)

[CONTENTS]
; only sections which exist in the file are required

;==============end minimum requirements=================

; Informational sections
COLOR PALETTE=       ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WARP SYMBOL PALETTE= ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WEFT SYMBOL PALETTE= ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
TEXT=                ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WEAVING=             ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WARP=                ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WEFT=                ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
;-   bitmap support not implemented but keywords reserved for future
;-   BITMAP IMAGE=   ;reserved (boolean) ({true,on,yes,1} {false,off,no,0})
;-   BITMAP FILE=    ;reserved (boolean) ({true,on,yes,1} {false,off,no,0})

;Beginning of Data Sections
NOTES=               ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
TIEUP=               ;optional (boolean) ({true,on,yes,1} {false,off,no,0})

; Color and Symbol tables
COLOR TABLE=         ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WARP SYMBOL TABLE=   ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WEFT SYMBOL TABLE=   ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
; Warp Data Sections
THREADING=           ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WARP THICKNESS=      ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WARP THICKNESS ZOOM= ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WARP SPACING=        ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WARP SPACING ZOOM=   ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WARP COLORS=         //;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WARP SYMBOLS=        ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
; Weft Data Sections
TREADLING=           ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
LIFTPLAN=            ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WEFT THICKNESS=      ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WEFT THICKNESS ZOOM= ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WEFT SPACING=        ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WEFT SPACING ZOOM=   ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WEFT COLORS=         ;optional (boolean) ({true,on,yes,1} {false,off,no,0})
WEFT SYMBOLS=        ;optional (boolean) ({true,on,yes,1} {false,off,no,0})

;-    Bitmap Data not implemented.  Keyword reserved for future.
;-    BITMAP IMAGE DATA=   ;reserved (boolean) ({true,on,yes,1} {false,off,no,0})

PRIVATE <SourceID> <SectionName>=

 *
 */



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QImage>
#include <QPainter>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QFileDialog>
#include <vector>
#include <maskinrum.h>
#include <configur.h>
//#include <grafik.h>
using std::vector;
#define DIRECTION_SWITCH 2
#define ACTION_SWITCH 4

#define SKAFTE_1  26
#define SKAFTE_2  25
#define SKAFTE_3  24
#define SKAFTE_4  23
#define SKAFTE_5  22
#define SKAFTE_6  21
#define SKAFTE_7  19
#define SKAFTE_8  20
#define SKAFTE_9  17
#define SKAFTE_10 18
#define SKAFTE_11 15
#define SKAFTE_12 16
#define SKAFTE_13 13
#define SKAFTE_14 14
#define SKAFTE_15 11
#define SKAFTE_16 12

#define SIDELAENGDE 64

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ThreadingView(int start);
    void LiftplanView(int sideNr);
    void SetupView();
    void StofView(int start, int pos, bool);
    void stof();
    void setSharfts(int pos);
    void openWif();

protected:

private slots:
    void on_actionOpenFile_triggered();
    void on_actionFrem_triggered();
    void on_actionTilbage_triggered();
    void on_actionTEST_triggered();

    void Timing();
   //void on_lwWeft_itemSelectionChanged();



    void on_actionRETNING_triggered();

    void on_actionConfigur_triggered();

    void on_actionPlus_triggered();

    void on_actionMinus_triggered();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    QGraphicsScene *scene;
    bool START;
    bool TRAMPE_AKTIV;
    bool swi;
    bool FREM_AKTIV;
    int side;

    int sideLaengde;
    long taeller;
    QString WifFileName;
    int cu;
    int page;

    // Pattern
    long ends;                              // Antal tråde i trenden i mønstret
    long picks;                             // Antal islæt i mønstret

    // Loom -----
    bool liftplanB;                         // Hvis liftplanB er FALSK vises Tie-up and Treadling
    long Shafts;                            // Antal skafter

    int width;
    int height;


    long warpThreads;                       // Antal islæt tråde
    long weftThreads;                       // Antal trend tråde
    long ColorEntries;
    vector<vector<int> > treadling;         // antal trendtråde x skafter 0'er og et ettal.
    vector<int> treadlingI;                 // antal trendtråde værdien angiver true skaft
    vector<vector<int> > threading;         // antal trendtråde x skafter 0'er og et ettal.
    vector<int> threadingI;                 // antal trendtråde værdien angiver true skaft

    vector<vector<long> > liftplan;         // islættråde x skafter
    vector<vector<long> > colorTable;       // antal farver x 3 (rgb)
    vector<vector<long> > weftColorTable;   // islættråde x 3
    vector<vector<long> > warpColorTable;   // trendtråde x 3
    bool WEFT_COLORS;
    bool WARP_COLORS;

    void weave(bool);
    void openConfigFile();
    void writeConfigFile();

    void readStatusFile();
    void writeStatusFile();

    configur *mw;

    QGraphicsTextItem *tekst;
};

#endif // MAINWINDOW_H

