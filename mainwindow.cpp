#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPoint>
//using std::vector;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::showMaximized();
    START = true;
    side = 10;
    page = 0;
    cu = -1;
    taeller = 0;
    sideLaengde = 64;
    scene = new QGraphicsScene();

    timer.setInterval(1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(Timing()));

    QWidget::update();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Digiweave");
    msgBox.setText("Welcome to Computer Aided Weaving");
    msgBox.exec();
    readStatusFile();

}

MainWindow::~MainWindow()
{
    delete ui;
}

maskinrum *gpio = new maskinrum();

void MainWindow::openConfigFile(){
    QFile file("digiweave.cfg");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    file.close();
}

void MainWindow::writeConfigFile(){
    QFile file("digiweave.cfg");
    if(!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    QTextStream out(&file);


    out << "[FILENAME]" << '\n';
    out << "filename=" << '\n';
    out << "" << '\n';
    out << "[PAGE]" << '\n';
    out << "page=0" << '\n';
    out << "" << '\n';
    out << "[POS]" << '\n';
    out << "pos=0" << '\n';
    out << "" << '\n';
    out << "[TOTAL]" << '\n';
    out << "total=0" << '\n';


    file.close();
}

void MainWindow::readStatusFile(){
    QFile file("digiweave.status");

    if(!file.open(QIODevice::ReadOnly)) {

        QMessageBox::information(0, "error", file.errorString());
        WifFileName = "";
        openWif();


        if(!file.open(QIODevice::ReadWrite)) {
            QMessageBox::information(0, "error", file.errorString());
        }
        QTextStream out(&file);

        cu = -1;
        page = 0;
        taeller = 0;

        out << "[FILENAME]" << '\n';
        out << "filename=" << WifFileName << '\n';
        out << "" << '\n';
        out << "[PAGE]" << '\n';
        out << "page=" << 0 << '\n';
        out << "" << '\n';
        out << "[CU]" << '\n';
        out << "cu=" << -1  << '\n';
        out << "" << '\n';
        out << "[TAELLER]" << '\n';
        out << "taeller=" << 0  << '\n';
        file.close();
qDebug() << "readStatus" << page;

        return;

    }

    QTextStream in(&file);


    while(!in.atEnd()) {
        QString line = in.readLine();

        if(line.toUpper() == "[FILENAME]"){
            line = in.readLine();
            QStringList sp = line.split('=');
             WifFileName = sp[1];
        }
        if(line.toUpper() == "[PAGE]"){
            line = in.readLine();
           QStringList sp = line.split('=');
            page = sp[1].toInt();
        }
        if(line.toUpper() == "[CU]"){
            line = in.readLine();
         QStringList sp = line.split('=');
          cu = sp[1].toInt();
        }
        if(line.toUpper() == "[TAELLER]"){
            line = in.readLine();
           QStringList sp = line.split('=');
           taeller = sp[1].toInt();
        }
    }

    file.close();

qDebug() << "readStatus" << page;
    qDebug() << WifFileName;
   if(WifFileName.length()>0) openWif();


}

void MainWindow::writeStatusFile(){
    QFile file("digiweave.status");
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream out(&file);
    out << "[FILENAME]" << '\n';
    out << "filename=" << WifFileName << '\n';
    out << "" << '\n';
    out << "[PAGE]" << '\n';
    out << "page=" << page << '\n';
    out << "" << '\n';
    out << "[CU]" << '\n';
    out << "cu=" << cu << '\n';
    out << "" << '\n';
    out << "[TAELLER]" << '\n';
    out << "taeller=" << taeller << '\n';
    file.close();

}


void MainWindow::on_actionRETNING_triggered()
{
    ui->actionRETNING->setText("Loom started");
    if(TRAMPE_AKTIV == true){
        TRAMPE_AKTIV = false;
    }
    else {
        TRAMPE_AKTIV = true;
    }
}


void MainWindow::Timing()
{
    timer.stop();

    TRAMPE_AKTIV = !gpio->getInput(ACTION_SWITCH);
    if(swi == TRAMPE_AKTIV) {
        timer.start(1000);
        return;
    }
qDebug() << ".";
    swi = TRAMPE_AKTIV;



    if(TRAMPE_AKTIV){

        weave(gpio->getInput(DIRECTION_SWITCH));

    }

    timer.start(1000);

}
int on = 0;
void MainWindow::on_actionTEST_triggered(){
    gpio->setup_io();
    gpio->setBen();



    if(on == 1){
        on = 0;
        gpio->setOutput(SKAFTE_1, 1);
        gpio->setOutput(SKAFTE_2, on);
        gpio->setOutput(SKAFTE_3, 1);
        gpio->setOutput(SKAFTE_4, on);
        gpio->setOutput(SKAFTE_5, 1);
        gpio->setOutput(SKAFTE_6, on);
        gpio->setOutput(SKAFTE_7, 1);

        gpio->setOutput(SKAFTE_8, on);
        gpio->setOutput(SKAFTE_9, 1);
        gpio->setOutput(SKAFTE_10, on);
        gpio->setOutput(SKAFTE_11, 1);
        gpio->setOutput(SKAFTE_12, on);
        gpio->setOutput(SKAFTE_13, 1);
        gpio->setOutput(SKAFTE_14, on);
        gpio->setOutput(SKAFTE_15, 1);
        gpio->setOutput(SKAFTE_16, on);
    }
    else{
        on = 1;
        gpio->setOutput(SKAFTE_1, 0);
        gpio->setOutput(SKAFTE_2, on);
        gpio->setOutput(SKAFTE_3, 0);
        gpio->setOutput(SKAFTE_4, on);
        gpio->setOutput(SKAFTE_5, 0);
        gpio->setOutput(SKAFTE_6, on);
        gpio->setOutput(SKAFTE_7, 0);

        gpio->setOutput(SKAFTE_8, on);
        gpio->setOutput(SKAFTE_9, 0);
        gpio->setOutput(SKAFTE_10, on);
        gpio->setOutput(SKAFTE_11, 0);
        gpio->setOutput(SKAFTE_12, on);
        gpio->setOutput(SKAFTE_13, 0);
        gpio->setOutput(SKAFTE_14, on);
        gpio->setOutput(SKAFTE_15, 0);
        gpio->setOutput(SKAFTE_16, on);
    }
}



void MainWindow::weave(bool retning){
    if(taeller == 0) cu = -1;
    if(retning){
        taeller++;
        cu++;
        if(cu == weftThreads) cu = 0, page = 0;
        int cursor = cu % weftThreads;

        page = cursor / sideLaengde;
        //int pos = cursor % (sideLaengde);

        StofView(page, cu, retning);
      //  setSharfts(cu);
    }
    else{
        taeller--;
        if(taeller < 0){ taeller = 0; cu = -1; return;}
        cu--;
        if(cu<0) return;
        if(cu == weftThreads) {cu = 0; page = 0;}
        int cursor = cu % weftThreads;

        page = cursor / sideLaengde;
        //int pos = cursor % (sideLaengde);

        StofView(page, cu, retning);
//        setSharfts(cu);
    }
    writeStatusFile();
}


void MainWindow::on_actionFrem_triggered(){
weave(TRUE);

}

void MainWindow::on_actionTilbage_triggered(){
 weave(FALSE);
}

void MainWindow::openWif(){
    timer.stop();
    swi = !TRAMPE_AKTIV;

    gpio->setup_io();
    gpio->setBen();
    QMessageBox ms;
    ms.setDefaultButton(QMessageBox::Yes);

    if(WifFileName.length()==0){
        WifFileName = QFileDialog::getOpenFileName(this,
                                                tr("Open File"), "", tr("Weave information File (*.wif )"));
    }

    QWidget::setWindowTitle("DigiWeave " + WifFileName);
    QFile file(WifFileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    WEFT_COLORS = FALSE;
    WARP_COLORS = FALSE;
    while(!in.atEnd()) {
        QString line = in.readLine();

        if(line.toUpper() == "[WEAVING]"){
            line = in.readLine();
            QStringList sp = line.split('=');
            Shafts = sp[1].toInt();
        }

        if(line.toUpper() == "[WEFT]"){
            line = in.readLine();
            QStringList sp = line.split('=');
           weftThreads = sp[1].toInt();


            liftplan.resize(weftThreads);
            for(int i=0;i<weftThreads;i++)
                liftplan[i].resize(Shafts);
        }

        if(line.toUpper() == "[WARP]"){
            line = in.readLine();
            QStringList sp = line.split('=');
            warpThreads = sp[1].toInt();
        }

        //[THREADING]
        if(line.toUpper() == "[THREADING]"){
            threadingI.resize(warpThreads);
            threading.resize(warpThreads);
            for(int i=0;i<warpThreads;i++)
                threading[i].resize(Shafts);
            for(int i=0; i<warpThreads;i++){
                line = in.readLine();
                QStringList sp = line.split('=');
                int jj = sp[1].toInt();
                threadingI[i] = jj;
                for(int j=1;j<=Shafts;j++){
                    if(j == jj)
                        threading[i][j-1] = 1;
                    else
                       threading[i][j-1] = 0;
                }
            }
        }

        //[TIEUP]

        if(line.toUpper() == "[TREADLING]"){
            treadlingI.resize(weftThreads);
            treadling.resize(weftThreads);
            for(int i=0;i<weftThreads;i++)
                treadling[i].resize(Shafts);
            for(int i=0; i<weftThreads;i++){
                line = in.readLine();
                QStringList sp = line.split('=');
                int jj = sp[1].toInt();
                treadlingI[i] = jj;
                for(int j=1;j<=Shafts;j++){
                    if(j == jj)
                        treadling[i][j-1] = 1;
                    else
                       treadling[i][j-1] = 0;
                }
            }
        }

        if(line.toUpper() == "[LIFTPLAN]"){

            for(int i=0;i<weftThreads;i++){
                line = in.readLine();
                QStringList sp = line.split('=');
                QStringList sp1 = sp[1].split(',');

                for(int j=0; j<Shafts; j++){
                    liftplan[i][j] = 0;
                }//

               for(int k=0; k<sp1.size();k++){
                    int bit = sp1[k].toInt();
                    liftplan[i][bit-1] = 1;
               }
               QString str = "";
               for (int l=0;l<Shafts;l++){
                   str += QString::number(liftplan[i][l]) + ",";
               }
            }
        }

        if(line.toUpper() == "[COLOR PALETTE]"){

            line = in.readLine();
            QStringList sp = line.split('=');++
            ColorEntries = sp[1].toInt();
            colorTable.resize(ColorEntries);
            for(int i=0;i<ColorEntries;i++)
                colorTable[i].resize(3);
        }

        if(line.toUpper() == "[COLOR TABLE]"){

            for(int i=0; i<ColorEntries;i++){
                line = in.readLine();
                QStringList sp = line.split('=');
                QStringList sp1 = sp[1].split(',');
                for(int j=0;j<3;j++)
                    colorTable[i][j] = sp1[j].toInt();
            }
        }


        if(line.toUpper() == "[WEFT COLORS]"){
            WEFT_COLORS = TRUE;
            weftColorTable.resize(weftThreads);
             for(int i=0;i<weftThreads;i++)
                 weftColorTable[i].resize(3);
            for(int i=0;i<weftThreads;i++){
                line = in.readLine();
                QStringList sp = line.split('=');
                int color = sp[1].toInt();
                for(int j=0; j<3; j++){
                    weftColorTable[i][j] = colorTable[color][j];
                }
            }
        }

        if(line.toUpper() == "[WARP COLORS]"){
            WARP_COLORS = TRUE;
            warpColorTable.resize(warpThreads);
             for(int i=0;i<warpThreads;i++)
                 warpColorTable[i].resize(3);
            for(int i=0;i<warpThreads;i++){
                line = in.readLine();
                QStringList sp = line.split('=');
                int color = sp[1].toInt();
                for(int j=0; j<3; j++){
                    warpColorTable[i][j] = colorTable[color][j];
                }
            }
        }

    }

    file.close();
    qDebug() << "foe writeStatusFile" << page;
    writeStatusFile();
    SetupView();
 /*   if(taeller>0)
        taeller--;
    if(cu>=0)
        cu--;*/
    swi = !TRAMPE_AKTIV;
    timer.start(1);

}

void MainWindow::SetupView(){
 //   sideLaengde = 32;

    QSize s = QWidget::size(); //Størelsen af formen
    int hi = s.height();
    int wi = s.width();
    side = hi / (sideLaengde + 16 + 8);
    qDebug() << wi <<"; " << hi << "; " << side;
    ui->gv->setGeometry(0, 0,wi - 20 , hi - 50);
    height = ui->gv->height()-10 ;
    width = ui->gv->width();

    scene->setSceneRect(0, 0, width, height);
    scene->clear();
    scene->addRect(1, 1, wi,  height, QPen(Qt::white), QBrush(Qt::white, Qt::SolidPattern));
    LiftplanView(page);

    ThreadingView(1);

    ui->gv->setScene(scene);
    ui->gv->show();
    StofView(page, cu, true);

}

void MainWindow::on_actionOpenFile_triggered()
{
    taeller = 0;
    cu = 0;
    page = 0;
    WifFileName = "";
    openWif();
}

void MainWindow::LiftplanView(int sideNr){
qDebug() << "stof" << page;
    int antalSider = weftThreads / sideLaengde;
    int restSide = weftThreads % sideLaengde;
    QSize s = QWidget::size(); //Størelsen af formen

    int wi = s.width();
    scene->addRect(1, 1, wi,  height -  side * Shafts - side, QPen(Qt::white), QBrush(Qt::white, Qt::SolidPattern));

    if(sideNr < antalSider)
    {
        for(int i = (sideNr * sideLaengde) +1; i <= sideLaengde * (sideNr + 1); i++)
            for(int j = Shafts-1;j>=0;j--){
                if(liftplan[i-1][j]==1)
                    scene->addRect(width - side*(Shafts - j) - side*4 ,
                                   height - side*( i - (sideNr * sideLaengde) ) - side * Shafts - side,
                                   side*0.7,
                                   side*0.7, QPen(),QBrush(Qt::black ,Qt::SolidPattern));
                else{
                    int r =255, g = 255, b =255;
                    if(WEFT_COLORS){
                        r = weftColorTable[i-1][0];
                        g = weftColorTable[i-1][1];
                        b = weftColorTable[i-1][2];
                    }
                    scene->addRect(width - side*(Shafts - j) - side*4,
                                   height - side*(i - (sideNr * sideLaengde) ) - side * Shafts - side,
                                   side*0.7, side*0.7,
                                   QPen(),
                                   QBrush(QColor(r, g, b) ,Qt::SolidPattern));
                }
            }

    } else
    {

        for(int i = sideNr * sideLaengde + 1; i <= restSide + sideNr * sideLaengde; i++)
            for(int j = Shafts-1;j>=0;j--){
                if(liftplan[i-1][j] == 1)
                    scene->addRect(width - side*(Shafts - j) - side*4 ,
                                   height - side*( i - (sideNr * sideLaengde)) - side * Shafts - side,
                                   side*0.7,
                                   side*0.7,
                                   QPen(),
                                   QBrush(Qt::black ,Qt::SolidPattern));
                else{
                    int r =255, g = 255, b =255;
                    if(WEFT_COLORS){
                        r = weftColorTable[i-1][0];
                        g = weftColorTable[i-1][1];
                        b = weftColorTable[i-1][2];
                    }
                    scene->addRect(width - side*(Shafts - j) - side*4,
                                   height - side*(i - (sideNr * sideLaengde) ) - side * Shafts - side,
                                   side*0.7,
                                   side*0.7,

                                   QPen(),
                                   QBrush(QColor(r, g, b) ,Qt::SolidPattern));
                }
            }
    }
    stof();
}

void MainWindow::ThreadingView(int start){
    if(start < 1) start = 1;

    for(int i = warpThreads; i>=start;i--){
        for(int j = Shafts-1;j>=0;j--){
            if(threading[i-1][j]==1) {
                int r =255, g = 255, b =255;
                if(WARP_COLORS){
                    r = warpColorTable[i-1][0];
                    g = warpColorTable[i-1][1];
                    b = warpColorTable[i-1][2];
                }
                scene->addRect(width - side*( i) - side*Shafts - 6*side ,
                               height - side*(Shafts - j)/* - side*/,
                               side*0.7,
                               side*0.7,
                               QPen(),
                               QBrush(QColor(r, g, b) ,Qt::SolidPattern));
            }
            else{

                scene->addRect(width - side*( i) - side*Shafts - 6*side ,
                               height - side*(Shafts - j)/* - side*/,
                               side*0.7,
                               side*0.7,
                               QPen(),
                               QBrush(Qt::black,Qt::SolidPattern));
            }
        }
    }

}

void MainWindow::setSharfts(int pos){
    if(Shafts>=1) gpio->setOutput(SKAFTE_1, liftplan[pos][0]);
    else  gpio->setOutput(SKAFTE_1, 1);
    if(Shafts>=2) gpio->setOutput(SKAFTE_2, liftplan[pos][1]);
    else  gpio->setOutput(SKAFTE_2, 1);
    if(Shafts>=3) gpio->setOutput(SKAFTE_3, liftplan[pos][2]);
    else  gpio->setOutput(SKAFTE_3, 1);
    if(Shafts>=4) gpio->setOutput(SKAFTE_4, liftplan[pos][3]);
    else  gpio->setOutput(SKAFTE_4, 1);
    if(Shafts>=5) gpio->setOutput(SKAFTE_5, liftplan[pos][4]);
    else  gpio->setOutput(SKAFTE_5, 1);
    if(Shafts>=6) gpio->setOutput(SKAFTE_6, liftplan[pos][5]);
    else  gpio->setOutput(SKAFTE_6, 1);
    if(Shafts>=7) gpio->setOutput(SKAFTE_7, liftplan[pos][6]);
    else  gpio->setOutput(SKAFTE_7, 1);
    if(Shafts>=8) gpio->setOutput(SKAFTE_8, liftplan[pos][7]);
    else  gpio->setOutput(SKAFTE_8, 1);
    if(Shafts>=9) gpio->setOutput(SKAFTE_9, liftplan[pos][8]);
    else  gpio->setOutput(SKAFTE_9, 1);
    if(Shafts>=10) gpio->setOutput(SKAFTE_10, liftplan[pos][9]);
    else  gpio->setOutput(SKAFTE_10, 1);
    if(Shafts>=11) gpio->setOutput(SKAFTE_11, liftplan[pos][10]);
    else  gpio->setOutput(SKAFTE_11, 1);
    if(Shafts>=12) gpio->setOutput(SKAFTE_12, liftplan[pos][11]);
    else  gpio->setOutput(SKAFTE_12, 1);
    if(Shafts>=13) gpio->setOutput(SKAFTE_13, liftplan[pos][12]);
    else  gpio->setOutput(SKAFTE_13, 1);
    if(Shafts>=14) gpio->setOutput(SKAFTE_14, liftplan[pos][13]);
    else  gpio->setOutput(SKAFTE_14, 1);
    if(Shafts>=15) gpio->setOutput(SKAFTE_15, liftplan[pos][14]);
    else  gpio->setOutput(SKAFTE_15, 1);
    if(Shafts>=16) gpio->setOutput(SKAFTE_16, liftplan[pos][15]);
    else  gpio->setOutput(SKAFTE_16, 1);
}

void MainWindow::stof(){
    int antalSider = weftThreads / sideLaengde;
    int restSide = weftThreads % sideLaengde;
    int siden;
    if(page < antalSider) siden = sideLaengde;
    else siden = restSide;


    for(int pos1 = 0 + page * sideLaengde; pos1 < page * sideLaengde + siden ; pos1++){
        int j = pos1 % sideLaengde;
        for(int i = 0; i < warpThreads; i++){

            if(liftplan[pos1][ threadingI[i]-1] == 1){
                int r =255, g = 255, b =255;
                if(WEFT_COLORS){

                    r = weftColorTable[pos1][0];
                    g = weftColorTable[pos1][1];
                    b = weftColorTable[pos1][2];
                    scene->addRect(width - side*(i)  - side*Shafts - side*7,
                                   height - side*(j) - side * Shafts - side*2,// + side*0.3,
                                   side,
                                   side,//*0.2,
                                   QPen(QColor(r, g, b)),
                                   QBrush(QColor(r, g, b) ,Qt::SolidPattern));
                }else{
                    scene->addRect(width - side*(i)  - side*Shafts - side*7,
                                   height - side*(j) - side * Shafts - side*2,// + side*0.3,
                                   side,
                                   side,//*0.2,
                                   QPen(),
                                   QBrush(QColor(r, g, b) ,Qt::SolidPattern));
                }
            }else{

                int r =0, g = 0, b = 0;
                if(WARP_COLORS){

                    r = warpColorTable[i][0];
                    g = warpColorTable[i][1];
                    b = warpColorTable[i][2];
                    scene->addRect(width - side*(i)  - side*Shafts - side*7,// + side*0.2,
                                   height - side*j - side * Shafts - side*2,
                                   side,//*0.2,
                                   side,
                                   QPen(QColor(r, g, b)),
                                   QBrush(QColor(r, g, b) ,Qt::SolidPattern));
                }else{

                    scene->addRect(width - side*(i)  - side*Shafts - side*7,// + side*0.2,
                                   height - side*j - side * Shafts - side*2,
                                   side,//*0.2,
                                   side,
                                   QPen(),
                                   QBrush(QColor(r, g, b) ,Qt::SolidPattern));
                }
            }
        }
    }

}

void MainWindow::StofView(int page, int pos, bool retning){

    setSharfts(pos);
    int vPos = pos % sideLaengde;

    if(retning){
        if((pos % sideLaengde == 0)) LiftplanView(page);
    }else{
        if(pos % sideLaengde == sideLaengde -1){

            if(page > 0) LiftplanView(page-1);
            else LiftplanView(page);
        }
    }




    {
    scene->addRect(width - side*6 - side * Shafts,
                   height - side*(vPos + 1) - side * Shafts - side*2,
                   side,
                   side,
                   QPen(Qt::white),
                   QBrush(Qt::white ,Qt::SolidPattern));
    scene->addRect(width - side*6 - side * Shafts,
                   height - side*(vPos - 1) - side * Shafts - side*2,
                   side,
                   side,
                   QPen(Qt::white),
                   QBrush(Qt::white ,Qt::SolidPattern));

    scene->addEllipse(width - side*6 - side * Shafts ,
                      height - side*(vPos) - side * Shafts - side*2,
                      side,
                      side,
                      QPen(Qt::red),
                      QBrush(Qt::red ,Qt::SolidPattern));


    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setPos(width - side*4,
               height - side*(vPos) - side * Shafts - side*3);
    io->setPlainText(QString::number(pos, 10));

    scene->addItem(io);

    scene->addRect(width - side*11,  1,
                   side*10,
                   side*2,
                   QPen(Qt::white),
                   QBrush(Qt::white ,Qt::SolidPattern));
    QGraphicsTextItem * io1 = new QGraphicsTextItem;
    io1->setPos(width - side*11,  1);
    io1->setPlainText("Total: " + QString::number(taeller, 10));
    scene->addItem(io1);
    }

}



void MainWindow::on_actionConfigur_triggered()
{
    mw = new configur();
    mw->exec();
}

void MainWindow::on_actionPlus_triggered()
{
    if(sideLaengde<=128) sideLaengde+=8;
    else return;
    SetupView();
}

void MainWindow::on_actionMinus_triggered()
{
    if(sideLaengde>=32) sideLaengde-=8;
    else return;
    SetupView();
}
