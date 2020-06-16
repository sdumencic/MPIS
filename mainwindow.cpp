#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include "APU.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include "LinijskiRastavljac.h"
#include "Prekidac.h"
#include "Rastavljac.h"
#include "RastavljacUzemljenja.h"
#include "SabirnickiRastavljac.h"
#include "Zastita.h"

//elementi-b
Prekidac p_b;
RastavljacUzemljenja ru_b;
SabirnickiRastavljac gl_sr_b;
SabirnickiRastavljac pom_sr_b;
LinijskiRastavljac lr_b;
APU apu_b;

//elementi-c
Prekidac p_c;
RastavljacUzemljenja ru_c;
SabirnickiRastavljac sr_c;
LinijskiRastavljac lr_c;
APU apu_c;

//zastita
Zastita zastita;

std::vector<Rastavljac*> rastavljaci_b, rastavljaci_c;


//postavljanje signala za ispis
QString path_b = "./signali_b.txt";
QFile signali_b(path_b);
QString path_c = "./signali_c.txt";
QFile signali_c(path_c);
bool s_b = false;
bool s_c = false;


void delay(unsigned int ms){
    QTime endtime = QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime() < endtime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void MainWindow::read_file_signali_b(){
    if(!signali_b.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&signali_b);
    QString sig_b = in.readAll();
    ui->signali_b->setText(sig_b);
    signali_b.close();
}

void MainWindow::read_file_signali_c(){
    if(!signali_c.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&signali_c);
    QString sig_c = in.readAll();
    ui->signali_c->setText(sig_c);
    signali_c.close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    rastavljaci_b.push_back(&ru_b);
    rastavljaci_b.push_back(&gl_sr_b);
    rastavljaci_b.push_back(&pom_sr_b);
    rastavljaci_b.push_back(&lr_b);

    rastavljaci_c.push_back(&ru_c);
    rastavljaci_c.push_back(&sr_c);
    rastavljaci_c.push_back(&lr_c);

    ui->setupUi(this);

    ui->signali_b->setVisible(false);
    ui->signali_c->setVisible(false);

    read_file_signali_b();
    read_file_signali_c();
}

MainWindow::~MainWindow()
{
    delete ui;
}


//gumbi-a
void MainWindow::glavni_sabirnicki_rastavljac_gumb_b(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-B: Glavni sabirnicki rastavljac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->SRastavljacA1->setPalette(p);
        linija_glavna_sabirnica_glavni_rastavljac_b(true);
        if(p_b.getStanje()){
            linija_iz_glavnog_rastavljaca_b(true);
            linija_rastavljaci_prekidac_b(true);
        }
    } else {
        ui->textBrowser->append("DV-B: Glavni sabirnicki rastavljac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->SRastavljacA1->setPalette(p);
        linija_glavna_sabirnica_glavni_rastavljac_b(false);
        linija_iz_glavnog_rastavljaca_b(false);
        if(!pom_sr_b.getStanje()){
            linija_rastavljaci_prekidac_b(false);
        }
    }
    delay(500);
}

void MainWindow::pomocni_sabirnicki_rastavljac_gumb_b(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-B: Pomocni sabirnicki rastavljac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->SRastavljacA2->setPalette(p);
        linija_pomocna_sabirnica_pomocni_rastavljac_b(true);
        if(p_b.getStanje()){
            linija_iz_pomocnog_rastavljaca_b(true);
            linija_rastavljaci_prekidac_b(true);
        }
    } else {
        ui->textBrowser->append("DV-B: Pomocni sabirnicki rastavljac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->SRastavljacA2->setPalette(p);
        linija_pomocna_sabirnica_pomocni_rastavljac_b(false);
        linija_iz_pomocnog_rastavljaca_b(false);
        if(!gl_sr_b.getStanje()){
            linija_rastavljaci_prekidac_b(false);
        }
    }
    delay(500);
}

void MainWindow::rastavljac_uzemljenja_gumb_b(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-B: Rastavljac uzemljenja ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->RUzemljenjaA->setPalette(p);
        linija_rastavljaca_uzemljenja_b(true);
    } else {
        ui->textBrowser->append("DV-B: Rastavljac uzemljenja iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->RUzemljenjaA->setPalette(p);
        linija_rastavljaca_uzemljenja_b(false);
    }
    delay(500);
}

void MainWindow::prekidac_gumb_b(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-B: Prekidac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->PrekidacA->setPalette(p);
    } else {
        ui->textBrowser->append("DV-B: Prekidac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->PrekidacA->setPalette(p);
    }
    delay(500);
}

void MainWindow::linijski_rastavljac_gumb_b(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-B: Linijski rastavljac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->LRastavljacA->setPalette(p);
        if(p_b.getStanje()){
            linija_prekidac_apu_b(true);
            linija_apu_linijski_rastavljac_b(true);
            if(lr_c.getStanje()){
                linija_linijski_rastavljaci(true);
            }
        }
    } else {
        ui->textBrowser->append("DV-B: Linijski rastavljac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->LRastavljacA->setPalette(p);
        linija_prekidac_apu_b(false);
        linija_apu_linijski_rastavljac_b(false);
        linija_linijski_rastavljaci(false);
    }
    delay(500);
}

void MainWindow::apu_gumb_b(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-B: APU ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->APU_B->setPalette(p);
    } else {
        ui->textBrowser->append("DV-B: APU iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->APU_B->setPalette(p);
    }
}


//gumbi-b
void MainWindow::sabirnicki_rastavljac_gumb_c(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-C: Sabirnicki rastavljac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->SRastavljacB->setPalette(p);
        if(p_c.getStanje()){
            linija_rastavljac_prekidac_c(true);
        }
        linija_sabirnica_rastavljac_c(true);
    } else {
        ui->textBrowser->append("DV-C: Sabirnicki rastavljac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->SRastavljacB->setPalette(p);
        linija_sabirnica_rastavljac_c(false);
        linija_rastavljac_prekidac_c(false);
    }
    delay(500);
}

void MainWindow::rastavljac_uzemljenja_gumb_c(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-C: Rastavljac uzemljenja ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->RUzemljenjaB->setPalette(p);
        linija_rastavljaca_uzemljenja_c(true);
    } else {
        ui->textBrowser->append("DV-C: Rastavljac uzemljenja iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->RUzemljenjaB->setPalette(p);
        linija_rastavljaca_uzemljenja_c(false);
    }
    delay(500);
}

void MainWindow::prekidac_gumb_c(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-C: Prekidac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->PrekidacB->setPalette(p);
    } else {
        ui->textBrowser->append("DV-C: Prekidac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->PrekidacB->setPalette(p);
    }
    delay(500);
}

void MainWindow::linijski_rastavljac_gumb_c(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-C: Linijski rastavljac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->LRastavljacB->setPalette(p);
        if(p_c.getStanje()){
            linija_prekidac_apu_c(true);
            linija_apu_linijski_rastavljac_c(true);
            if(lr_b.getStanje()) linija_linijski_rastavljaci(true);
        }
    } else {
        ui->textBrowser->append("DV-C: Linijski rastavljac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->LRastavljacB->setPalette(p);
        linija_prekidac_apu_c(false);
        linija_apu_linijski_rastavljac_c(false);
        linija_linijski_rastavljaci(false);
    }
    delay(500);
}

void MainWindow::apu_gumb_c(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-C: APU ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->APU_C->setPalette(p);
    } else {
        ui->textBrowser->append("DV-C: APU iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->APU_C->setPalette(p);
    }
    delay(500);
}


//gumb zastita
void MainWindow::zastita_gumb(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Button, Qt::green);
        ui->Zastita->setPalette(p);
    } else {
        p.setColor(QPalette::Button, Qt::red);
        ui->Zastita->setPalette(p);
    }
    delay(500);
}


//linije-a
void MainWindow::linija_glavna_sabirnica_glavni_rastavljac_b(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaSR1->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaSR1->setPalette(p);
    }
    delay(200);
}

void MainWindow::linija_pomocna_sabirnica_pomocni_rastavljac_b(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaSR2->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaSR2->setPalette(p);
    }
    delay(200);
}

void MainWindow::linija_iz_glavnog_rastavljaca_b(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaR1->setPalette(p);
        ui->LinijaRR1->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaR1->setPalette(p);
        ui->LinijaRR1->setPalette(p);
    }
    delay(200);
}

void MainWindow::linija_iz_pomocnog_rastavljaca_b(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaR2->setPalette(p);
        ui->LinijaRR2->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaR2->setPalette(p);
        ui->LinijaRR2->setPalette(p);
    }
    delay(200);
}

void MainWindow::linija_rastavljaci_prekidac_b(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaRP1->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaRP1->setPalette(p);
    }
    delay(200);
}

void MainWindow::linija_rastavljaca_uzemljenja_b(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaRU1->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaRU1->setPalette(p);
    }
    delay(200);
}

void MainWindow::linija_prekidac_apu_b(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaPA1->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaPA1->setPalette(p);
    }
    delay(200);
}

void MainWindow::linija_apu_linijski_rastavljac_b(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaALR1->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaALR1->setPalette(p);
    }
    delay(200);
}

//linije-b
void MainWindow::linija_sabirnica_rastavljac_c(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaSR3->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaSR3->setPalette(p);
    }
    delay(200);
}

void MainWindow::linija_rastavljac_prekidac_c(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaRP2->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaRP2->setPalette(p);
    }
    delay(200);
}

void MainWindow::linija_rastavljaca_uzemljenja_c(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaRU2->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaRU2->setPalette(p);
    }
    delay(200);
}

void MainWindow::linija_prekidac_apu_c(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaPA2->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaPA2->setPalette(p);
    }
    delay(200);
}

void MainWindow::linija_apu_linijski_rastavljac_c(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaALR2->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaALR2->setPalette(p);
    }
    delay(200);
}

//linija izmedu a i b
void MainWindow::linija_linijski_rastavljaci(bool prorada){
    QPalette p;
    if(prorada){
        p.setColor(QPalette::Window, Qt::green);
        ui->LinijaLL->setPalette(p);
    } else {
        p.setColor(QPalette::Window, Qt::red);
        ui->LinijaLL->setPalette(p);
    }
    delay(200);
}


//prorada prekidaca
void MainWindow::prorada_prekidaca_b(bool prorada){
    if(prorada){
        ui->textBrowser->append("DV-B: Ukljucujem polje...");

        prekidac_gumb_b(true);

        rastavljac_uzemljenja_gumb_b(false);

        if(!gl_sr_b.getStanje() && !pom_sr_b.getStanje()){
            glavni_sabirnicki_rastavljac_gumb_b(true);
            linija_glavna_sabirnica_glavni_rastavljac_b(true);
            linija_iz_glavnog_rastavljaca_b(true);
            linija_rastavljaci_prekidac_b(true);

        } else if(gl_sr_b.getStanje()){
            linija_iz_glavnog_rastavljaca_b(true);
            linija_rastavljaci_prekidac_b(true);

            if(pom_sr_b.getStanje()){
                pomocni_sabirnicki_rastavljac_gumb_b(false);
                linija_pomocna_sabirnica_pomocni_rastavljac_b(false);
                linija_iz_pomocnog_rastavljaca_b(false);
            }

        } else if(pom_sr_b.getStanje()){
            linija_iz_pomocnog_rastavljaca_b(true);
            linija_rastavljaci_prekidac_b(true);
        }

        linijski_rastavljac_gumb_b(true);
        linija_prekidac_apu_b(true);
        linija_apu_linijski_rastavljac_b(true);
        if(lr_c.getStanje()) linija_linijski_rastavljaci(true);

        ui->textBrowser->append("DV-B: Polje ukljuceno");
    } else {
        ui->textBrowser->append("DV-B: Iskljucujem polje...");

        prekidac_gumb_b(false);

        rastavljac_uzemljenja_gumb_b(true);

        glavni_sabirnicki_rastavljac_gumb_b(false);
        linija_glavna_sabirnica_glavni_rastavljac_b(false);
        linija_iz_glavnog_rastavljaca_b(false);
        linija_rastavljaci_prekidac_b(false);

        pomocni_sabirnicki_rastavljac_gumb_b(false);
        linija_pomocna_sabirnica_pomocni_rastavljac_b(false);
        linija_iz_pomocnog_rastavljaca_b(false);
        linija_rastavljaci_prekidac_b(false);

        linijski_rastavljac_gumb_b(false);
        linija_prekidac_apu_b(false);
        linija_apu_linijski_rastavljac_b(false);
        linija_linijski_rastavljaci(false);

        ui->textBrowser->append("DV-B: Polje iskljuceno");
    }
}

void MainWindow::prorada_prekidaca_c(bool prorada){
    if(prorada){
        ui->textBrowser->append("DV-C: Ukljucujem polje...");

        prekidac_gumb_c(true);

        rastavljac_uzemljenja_gumb_c(false);

        sabirnicki_rastavljac_gumb_c(true);
        linija_sabirnica_rastavljac_c(true);
        linija_rastavljac_prekidac_c(true);

        linijski_rastavljac_gumb_c(true);
        linija_prekidac_apu_c(true);
        linija_apu_linijski_rastavljac_c(true);
        if(lr_b.getStanje()) linija_linijski_rastavljaci(true);

        ui->textBrowser->append("DV-C: Polje ukljuceno");
    } else {
        ui->textBrowser->append("DV-C: Iskljucujem polje...");
        prekidac_gumb_c(false);

        rastavljac_uzemljenja_gumb_c(true);

        sabirnicki_rastavljac_gumb_c(false);
        linija_sabirnica_rastavljac_c(false);
        linija_rastavljac_prekidac_c(false);

        linijski_rastavljac_gumb_c(false);
        linija_prekidac_apu_c(false);
        linija_linijski_rastavljaci(false);

        ui->textBrowser->append("DV-C: Polje iskljuceno");
    }
}


//prorada zastite
void MainWindow::prorada_zastite(bool prorada){
    if(prorada){
        ui->textBrowser->append("Zastita ukljucena");
        zastita_gumb(true);
        if(p_b.getStanje() && apu_b.getStanje()) p_b.setBioUpaljen(true);
        if(p_c.getStanje() && apu_c.getStanje()) p_c.setBioUpaljen(true);
        if(p_b.getStanje()) prorada_prekidaca_b(false);
        if(p_c.getStanje()) prorada_prekidaca_c(false);
    } else {
        ui->textBrowser->append("Zastita iskljucena");
        zastita_gumb(false);
        if(p_b.getBioUpaljen() && apu_b.getStanje()) prorada_prekidaca_b(true);
        if(p_c.getBioUpaljen() && apu_c.getStanje()) prorada_prekidaca_c(true);
    }
}


//blokada gumbi
void MainWindow::enable_dv_b(bool stanje){
    ui->SRastavljacA1->setEnabled(stanje);
    ui->SRastavljacA2->setEnabled(stanje);
    ui->PrekidacA->setEnabled(stanje);
    ui->RUzemljenjaA->setEnabled(stanje);
    ui->APU_B->setEnabled(stanje);
    ui->LRastavljacA->setEnabled(stanje);
}

void MainWindow::enable_dv_c(bool stanje){
    ui->SRastavljacB->setEnabled(stanje);
    ui->PrekidacB->setEnabled(stanje);
    ui->RUzemljenjaB->setEnabled(stanje);
    ui->APU_C->setEnabled(stanje);
    ui->LRastavljacB->setEnabled(stanje);
}

void MainWindow::enable_upravljanje(bool stanje){
    ui->promjenaUpravljanja->setEnabled(stanje);
}


//ts-a upravljanje
void MainWindow::on_PrekidacA_clicked()
{
    if(zastita.getStanje()){
        ui->textBrowser->append("DV-B: Nije moguce ukljuciti polje dok je zastita aktivna");
        return;
    }
    enable_dv_c(false);
    enable_upravljanje(false);
    if(!p_b.getStanje()){
        prorada_prekidaca_b(true);
        p_b.upaliSve(rastavljaci_b);
    } else {
        prorada_prekidaca_b(false);
        p_b.ugasiSve(rastavljaci_b);
    }
    enable_dv_c(true);
    enable_upravljanje(true);
}

void MainWindow::on_RUzemljenjaA_clicked()
{
    ui->textBrowser->append("DV-B: Nije moguce proizvoljno upravljati rastavljacem uzemljenja");
}

void MainWindow::on_SRastavljacA1_clicked()
{
    enable_dv_c(false);
    if(p_b.getStanje()){
        ui->textBrowser->append("DV-B: Nije moguce upaliti glavni sabirnicki rastavljac ako je prekidac ukljucen");
        enable_dv_c(true);
        return;
    }
    if(!gl_sr_b.getStanje()){
        glavni_sabirnicki_rastavljac_gumb_b(true);
        gl_sr_b.setStanje(true);
    } else {
        glavni_sabirnicki_rastavljac_gumb_b(false);
        gl_sr_b.setStanje(false);
    }
    enable_dv_c(true);
}

void MainWindow::on_SRastavljacA2_clicked()
{
    enable_dv_c(false);
    if(p_b.getStanje()){
        ui->textBrowser->append("DV-B: Nije moguce upaliti pomocni sabirnicki rastavljac ako je prekidac ukljucen");
        enable_dv_c(true);
        return;
    }
    if(!pom_sr_b.getStanje()){
        pomocni_sabirnicki_rastavljac_gumb_b(true);
        pom_sr_b.setStanje(true);
    } else {
        pomocni_sabirnicki_rastavljac_gumb_b(false);
        pom_sr_b.setStanje(false);
    }
    enable_dv_c(true);
}

void MainWindow::on_LRastavljacA_clicked()
{
    enable_dv_c(false);
    if(p_b.getStanje()){
        ui->textBrowser->append("DV-B: Nije moguce upaliti linijski rastavljac ako je prekidac ukljucen");
        enable_dv_c(true);
        return;
    }
    if(!lr_b.getStanje()){
        linijski_rastavljac_gumb_b(true);
        lr_b.setStanje(true);
    } else {
        linijski_rastavljac_gumb_b(false);
        lr_b.setStanje(false);
    }
    enable_dv_c(true);
}

void MainWindow::on_APU_B_clicked()
{
    if(!apu_b.getStanje()){
        apu_gumb_b(true);
        apu_b.setStanje(true);
    } else {
        p_b.setBioUpaljen(false);
        apu_gumb_b(false);
        apu_b.setStanje(false);
    }
}


//ts-b upravljanje

void MainWindow::on_PrekidacB_clicked()
{
    if(zastita.getStanje()){
        ui->textBrowser->append("DV-C: Nije moguce ukljuciti polje dok je zastita aktivna");
        return;
    }
    enable_dv_c(false);
    enable_upravljanje(false);
    if(!p_c.getStanje()){
        prorada_prekidaca_c(true);
        p_c.upaliSve(rastavljaci_c);
    } else {
        prorada_prekidaca_c(false);
        p_c.ugasiSve(rastavljaci_c);
    }
    enable_dv_c(true);
    enable_upravljanje(true);
}

void MainWindow::on_RUzemljenjaB_clicked()
{
    ui->textBrowser->append("DV-C: Nije moguce proizvoljno upravljati rastavljacem uzemljenja");
}

void MainWindow::on_SRastavljacB_clicked()
{
    enable_dv_c(false);
    if(p_c.getStanje()){
        ui->textBrowser->append("DV-C: Nije moguce upaliti sabirnicki rastavljac ako je prekidac ukljucen");
        enable_dv_c(true);
        return;
    }
    if(!sr_c.getStanje()){
        sabirnicki_rastavljac_gumb_c(true);
        sr_c.setStanje(true);
    } else {
        sabirnicki_rastavljac_gumb_c(false);
        sr_c.setStanje(false);
    }
    enable_dv_c(true);
}

void MainWindow::on_LRastavljacB_clicked()
{
    enable_dv_c(false);
    if(p_c.getStanje()){
        ui->textBrowser->append("DV-C: Nije moguce upaliti linijski rastavljac ako je prekidac ukljucen");
        enable_dv_c(true);
        return;
    }
    if(!lr_c.getStanje()){
        linijski_rastavljac_gumb_c(true);
        lr_c.setStanje(true);
    } else {
        linijski_rastavljac_gumb_c(false);
        lr_c.setStanje(false);
    }
    enable_dv_c(true);
}

void MainWindow::on_APU_C_clicked()
{
    if(!apu_c.getStanje()){
        apu_gumb_c(true);
        apu_c.setStanje(true);
    } else {
        p_c.setBioUpaljen(false);
        apu_gumb_c(false);
        apu_c.setStanje(false);
    }
}



//upravljanje zastitom
void MainWindow::on_Zastita_clicked()
{
    enable_dv_c(false);
    enable_dv_c(false);
    if(!zastita.getStanje()){
        prorada_zastite(true);
        zastita.upaliZastitu(rastavljaci_b, p_b);
        zastita.upaliZastitu(rastavljaci_c, p_c);
    } else {
        prorada_zastite(false);
        zastita.ugasiZastitu(apu_b, rastavljaci_b, p_b);
        zastita.ugasiZastitu(apu_c, rastavljaci_c, p_c);
        if(p_b.getStanje() && p_c.getStanje()){
            linija_linijski_rastavljaci(true);
        }
    }
    if(p_b.getUpravljanje() && p_c.getUpravljanje()){
        enable_dv_c(true);
        enable_dv_c(true);
    }
}

void MainWindow::on_promjenaUpravljanja_clicked()
{
    if(p_b.getUpravljanje() && p_c.getUpravljanje()){
        ui->textBrowser->append("Ukljuceno lokalno upravljanje: Upozorenje! Nije moguce upravljati poljima!");
        ui->promjenaUpravljanja->setText("Lokalno");
        p_b.setUpravljanje(false);
        p_c.setUpravljanje(false);
        enable_dv_c(false);
        enable_dv_c(false);
    } else{
        ui->textBrowser->append("Ukljuceno daljinsko upravljanje");
        ui->promjenaUpravljanja->setText("Daljinsko");
        p_b.setUpravljanje(true);
        p_c.setUpravljanje(true);
        enable_dv_c(true);
        enable_dv_c(true);
    }
}

void MainWindow::on_prikaz_signala_b_clicked()
{
    if(!s_b){
        s_b = true;
        ui->signali_b->setVisible(true);
    } else {
        s_b = false;
        ui->signali_b->setVisible(false);
    }
}

void MainWindow::on_prikaz_signala_c_clicked()
{
    if(!s_c){
        s_c = true;
        ui->signali_c->setVisible(true);
    } else {
        s_c = false;
        ui->signali_c->setVisible(false);
    }
}
