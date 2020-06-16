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
Prekidac p_a;
RastavljacUzemljenja ru_a;
SabirnickiRastavljac gl_sr_a;
SabirnickiRastavljac pom_sr_a;
LinijskiRastavljac lr_a;
APU apu_a;

//elementi-c
Prekidac p_b;
RastavljacUzemljenja ru_b;
SabirnickiRastavljac sr_b;
LinijskiRastavljac lr_b;
APU apu_b;

//zastita
Zastita zastita;

std::vector<Rastavljac*> rastavljaci_a, rastavljaci_b;


//postavljanje signala za ispis
QString path_a = "./signali_b.txt";
QFile signali_a(path_a);
QString path_b = "./signali_c.txt";
QFile signali_b(path_b);
bool s_a = false;
bool s_b = false;


void delay(unsigned int ms){
    QTime endtime = QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime() < endtime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void MainWindow::read_file_signali_a(){
    if(!signali_a.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&signali_a);
    QString sig_a = in.readAll();
    ui->signali_a->setText(sig_a);
    signali_a.close();
}

void MainWindow::read_file_signali_b(){
    if(!signali_b.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&signali_b);
    QString sig_b = in.readAll();
    ui->signali_b->setText(sig_b);
    signali_b.close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    rastavljaci_a.push_back(&ru_a);
    rastavljaci_a.push_back(&gl_sr_a);
    rastavljaci_a.push_back(&pom_sr_a);
    rastavljaci_a.push_back(&lr_a);

    rastavljaci_b.push_back(&ru_b);
    rastavljaci_b.push_back(&sr_b);
    rastavljaci_b.push_back(&lr_b);

    ui->setupUi(this);

    ui->signali_a->setVisible(false);
    ui->signali_b->setVisible(false);

    read_file_signali_a();
    read_file_signali_b();
}

MainWindow::~MainWindow()
{
    delete ui;
}


//gumbi-a
void MainWindow::glavni_sabirnicki_rastavljac_gumb_a(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-B: Glavni sabirnicki rastavljac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->SRastavljacA1->setPalette(p);
        linija_glavna_sabirnica_glavni_rastavljac_a(true);
        if(p_a.getStanje()){
            linija_iz_glavnog_rastavljaca_a(true);
            linija_rastavljaci_prekidac_a(true);
        }
    } else {
        ui->textBrowser->append("DV-B: Glavni sabirnicki rastavljac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->SRastavljacA1->setPalette(p);
        linija_glavna_sabirnica_glavni_rastavljac_a(false);
        linija_iz_glavnog_rastavljaca_a(false);
        if(!pom_sr_a.getStanje()){
            linija_rastavljaci_prekidac_a(false);
        }
    }
    delay(500);
}

void MainWindow::pomocni_sabirnicki_rastavljac_gumb_a(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-B: Pomocni sabirnicki rastavljac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->SRastavljacA2->setPalette(p);
        linija_pomocna_sabirnica_pomocni_rastavljac_a(true);
        if(p_a.getStanje()){
            linija_iz_pomocnog_rastavljaca_a(true);
            linija_rastavljaci_prekidac_a(true);
        }
    } else {
        ui->textBrowser->append("DV-B: Pomocni sabirnicki rastavljac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->SRastavljacA2->setPalette(p);
        linija_pomocna_sabirnica_pomocni_rastavljac_a(false);
        linija_iz_pomocnog_rastavljaca_a(false);
        if(!gl_sr_a.getStanje()){
            linija_rastavljaci_prekidac_a(false);
        }
    }
    delay(500);
}

void MainWindow::rastavljac_uzemljenja_gumb_a(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-B: Rastavljac uzemljenja ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->RUzemljenjaA->setPalette(p);
        linija_rastavljaca_uzemljenja_a(true);
    } else {
        ui->textBrowser->append("DV-B: Rastavljac uzemljenja iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->RUzemljenjaA->setPalette(p);
        linija_rastavljaca_uzemljenja_a(false);
    }
    delay(500);
}

void MainWindow::prekidac_gumb_a(bool prorada){
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

void MainWindow::linijski_rastavljac_gumb_a(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-B: Linijski rastavljac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->LRastavljacA->setPalette(p);
        if(p_a.getStanje()){
            linija_prekidac_apu_a(true);
            linija_apu_linijski_rastavljac_a(true);
            if(lr_b.getStanje()){
                linija_linijski_rastavljaci(true);
            }
        }
    } else {
        ui->textBrowser->append("DV-B: Linijski rastavljac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->LRastavljacA->setPalette(p);
        linija_prekidac_apu_a(false);
        linija_apu_linijski_rastavljac_a(false);
        linija_linijski_rastavljaci(false);
    }
    delay(500);
}

void MainWindow::apu_gumb_a(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-B: APU ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->APUA->setPalette(p);
    } else {
        ui->textBrowser->append("DV-B: APU iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->APUA->setPalette(p);
    }
}


//gumbi-b
void MainWindow::sabirnicki_rastavljac_gumb_b(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-C: Sabirnicki rastavljac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->SRastavljacB->setPalette(p);
        if(p_b.getStanje()){
            linija_rastavljac_prekidac_b(true);
        }
        linija_sabirnica_rastavljac_b(true);
    } else {
        ui->textBrowser->append("DV-C: Sabirnicki rastavljac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->SRastavljacB->setPalette(p);
        linija_sabirnica_rastavljac_b(false);
        linija_rastavljac_prekidac_b(false);
    }
    delay(500);
}

void MainWindow::rastavljac_uzemljenja_gumb_b(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-C: Rastavljac uzemljenja ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->RUzemljenjaB->setPalette(p);
        linija_rastavljaca_uzemljenja_b(true);
    } else {
        ui->textBrowser->append("DV-C: Rastavljac uzemljenja iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->RUzemljenjaB->setPalette(p);
        linija_rastavljaca_uzemljenja_b(false);
    }
    delay(500);
}

void MainWindow::prekidac_gumb_b(bool prorada){
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

void MainWindow::linijski_rastavljac_gumb_b(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-C: Linijski rastavljac ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->LRastavljacB->setPalette(p);
        if(p_b.getStanje()){
            linija_prekidac_apu_b(true);
            linija_apu_linijski_rastavljac_b(true);
            if(lr_a.getStanje()) linija_linijski_rastavljaci(true);
        }
    } else {
        ui->textBrowser->append("DV-C: Linijski rastavljac iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->LRastavljacB->setPalette(p);
        linija_prekidac_apu_b(false);
        linija_apu_linijski_rastavljac_b(false);
        linija_linijski_rastavljaci(false);
    }
    delay(500);
}

void MainWindow::apu_gumb_b(bool prorada){
    QPalette p;
    if(prorada){
        ui->textBrowser->append("DV-C: APU ukljucen");
        p.setColor(QPalette::Button, Qt::green);
        ui->APUB->setPalette(p);
    } else {
        ui->textBrowser->append("DV-C: APU iskljucen");
        p.setColor(QPalette::Button, Qt::red);
        ui->APUB->setPalette(p);
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
void MainWindow::linija_glavna_sabirnica_glavni_rastavljac_a(bool prorada){
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

void MainWindow::linija_pomocna_sabirnica_pomocni_rastavljac_a(bool prorada){
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

void MainWindow::linija_iz_glavnog_rastavljaca_a(bool prorada){
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

void MainWindow::linija_iz_pomocnog_rastavljaca_a(bool prorada){
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

void MainWindow::linija_rastavljaci_prekidac_a(bool prorada){
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

void MainWindow::linija_rastavljaca_uzemljenja_a(bool prorada){
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

void MainWindow::linija_prekidac_apu_a(bool prorada){
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

void MainWindow::linija_apu_linijski_rastavljac_a(bool prorada){
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
void MainWindow::linija_sabirnica_rastavljac_b(bool prorada){
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

void MainWindow::linija_rastavljac_prekidac_b(bool prorada){
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

void MainWindow::linija_rastavljaca_uzemljenja_b(bool prorada){
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

void MainWindow::linija_prekidac_apu_b(bool prorada){
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

void MainWindow::linija_apu_linijski_rastavljac_b(bool prorada){
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
void MainWindow::prorada_prekidaca_a(bool prorada){
    if(prorada){
        ui->textBrowser->append("DV-B: Ukljucujem polje...");

        prekidac_gumb_a(true);

        rastavljac_uzemljenja_gumb_a(false);

        if(!gl_sr_a.getStanje() && !pom_sr_a.getStanje()){
            glavni_sabirnicki_rastavljac_gumb_a(true);
            linija_glavna_sabirnica_glavni_rastavljac_a(true);
            linija_iz_glavnog_rastavljaca_a(true);
            linija_rastavljaci_prekidac_a(true);

        } else if(gl_sr_a.getStanje()){
            linija_iz_glavnog_rastavljaca_a(true);
            linija_rastavljaci_prekidac_a(true);

            if(pom_sr_a.getStanje()){
                pomocni_sabirnicki_rastavljac_gumb_a(false);
                linija_pomocna_sabirnica_pomocni_rastavljac_a(false);
                linija_iz_pomocnog_rastavljaca_a(false);
            }

        } else if(pom_sr_a.getStanje()){
            linija_iz_pomocnog_rastavljaca_a(true);
            linija_rastavljaci_prekidac_a(true);
        }

        linijski_rastavljac_gumb_a(true);
        linija_prekidac_apu_a(true);
        linija_apu_linijski_rastavljac_a(true);
        if(lr_b.getStanje()) linija_linijski_rastavljaci(true);

        ui->textBrowser->append("DV-B: Polje ukljuceno");
    } else {
        ui->textBrowser->append("DV-B: Iskljucujem polje...");

        prekidac_gumb_a(false);

        rastavljac_uzemljenja_gumb_a(true);

        glavni_sabirnicki_rastavljac_gumb_a(false);
        linija_glavna_sabirnica_glavni_rastavljac_a(false);
        linija_iz_glavnog_rastavljaca_a(false);
        linija_rastavljaci_prekidac_a(false);

        pomocni_sabirnicki_rastavljac_gumb_a(false);
        linija_pomocna_sabirnica_pomocni_rastavljac_a(false);
        linija_iz_pomocnog_rastavljaca_a(false);
        linija_rastavljaci_prekidac_a(false);

        linijski_rastavljac_gumb_a(false);
        linija_prekidac_apu_a(false);
        linija_apu_linijski_rastavljac_a(false);
        linija_linijski_rastavljaci(false);

        ui->textBrowser->append("DV-B: Polje iskljuceno");
    }
}

void MainWindow::prorada_prekidaca_b(bool prorada){
    if(prorada){
        ui->textBrowser->append("DV-C: Ukljucujem polje...");

        prekidac_gumb_b(true);

        rastavljac_uzemljenja_gumb_b(false);

        sabirnicki_rastavljac_gumb_b(true);
        linija_sabirnica_rastavljac_b(true);
        linija_rastavljac_prekidac_b(true);

        linijski_rastavljac_gumb_b(true);
        linija_prekidac_apu_b(true);
        linija_apu_linijski_rastavljac_b(true);
        if(lr_a.getStanje()) linija_linijski_rastavljaci(true);

        ui->textBrowser->append("DV-C: Polje ukljuceno");
    } else {
        ui->textBrowser->append("DV-C: Iskljucujem polje...");
        prekidac_gumb_b(false);

        rastavljac_uzemljenja_gumb_b(true);

        sabirnicki_rastavljac_gumb_b(false);
        linija_sabirnica_rastavljac_b(false);
        linija_rastavljac_prekidac_b(false);

        linijski_rastavljac_gumb_b(false);
        linija_prekidac_apu_b(false);
        linija_linijski_rastavljaci(false);

        ui->textBrowser->append("DV-C: Polje iskljuceno");
    }
}


//prorada zastite
void MainWindow::prorada_zastite(bool prorada){
    if(prorada){
        ui->textBrowser->append("Zastita ukljucena");
        zastita_gumb(true);
        if(p_a.getStanje() && apu_a.getStanje()) p_a.setBioUpaljen(true);
        if(p_b.getStanje() && apu_b.getStanje()) p_b.setBioUpaljen(true);
        if(p_a.getStanje()) prorada_prekidaca_a(false);
        if(p_b.getStanje()) prorada_prekidaca_b(false);
    } else {
        ui->textBrowser->append("Zastita iskljucena");
        zastita_gumb(false);
        if(p_a.getBioUpaljen() && apu_a.getStanje()) prorada_prekidaca_a(true);
        if(p_b.getBioUpaljen() && apu_b.getStanje()) prorada_prekidaca_b(true);
    }
}


//blokada gumbi
void MainWindow::enable_dv_b(bool stanje){
    ui->SRastavljacA1->setEnabled(stanje);
    ui->SRastavljacA2->setEnabled(stanje);
    ui->PrekidacA->setEnabled(stanje);
    ui->RUzemljenjaA->setEnabled(stanje);
    ui->APUA->setEnabled(stanje);
    ui->LRastavljacA->setEnabled(stanje);
}

void MainWindow::enable_dv_c(bool stanje){
    ui->SRastavljacB->setEnabled(stanje);
    ui->PrekidacB->setEnabled(stanje);
    ui->RUzemljenjaB->setEnabled(stanje);
    ui->APUB->setEnabled(stanje);
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
    enable_dv_b(false);
    enable_upravljanje(false);
    if(!p_a.getStanje()){
        prorada_prekidaca_a(true);
        p_a.upaliSve(rastavljaci_a);
    } else {
        prorada_prekidaca_a(false);
        p_a.ugasiSve(rastavljaci_a);
    }
    enable_dv_b(true);
    enable_upravljanje(true);
}

void MainWindow::on_RUzemljenjaA_clicked()
{
    ui->textBrowser->append("DV-B: Nije moguce proizvoljno upravljati rastavljacem uzemljenja");
}

void MainWindow::on_SRastavljacA1_clicked()
{
    enable_dv_b(false);
    if(p_a.getStanje()){
        ui->textBrowser->append("DV-B: Nije moguce upaliti glavni sabirnicki rastavljac ako je prekidac ukljucen");
        enable_dv_b(true);
        return;
    }
    if(!gl_sr_a.getStanje()){
        glavni_sabirnicki_rastavljac_gumb_a(true);
        gl_sr_a.setStanje(true);
    } else {
        glavni_sabirnicki_rastavljac_gumb_a(false);
        gl_sr_a.setStanje(false);
    }
    enable_dv_b(true);
}

void MainWindow::on_SRastavljacA2_clicked()
{
    enable_dv_b(false);
    if(p_a.getStanje()){
        ui->textBrowser->append("DV-B: Nije moguce upaliti pomocni sabirnicki rastavljac ako je prekidac ukljucen");
        enable_dv_b(true);
        return;
    }
    if(!pom_sr_a.getStanje()){
        pomocni_sabirnicki_rastavljac_gumb_a(true);
        pom_sr_a.setStanje(true);
    } else {
        pomocni_sabirnicki_rastavljac_gumb_a(false);
        pom_sr_a.setStanje(false);
    }
    enable_dv_b(true);
}

void MainWindow::on_LRastavljacA_clicked()
{
    enable_dv_b(false);
    if(p_a.getStanje()){
        ui->textBrowser->append("DV-B: Nije moguce upaliti linijski rastavljac ako je prekidac ukljucen");
        enable_dv_b(true);
        return;
    }
    if(!lr_a.getStanje()){
        linijski_rastavljac_gumb_a(true);
        lr_a.setStanje(true);
    } else {
        linijski_rastavljac_gumb_a(false);
        lr_a.setStanje(false);
    }
    enable_dv_b(true);
}

void MainWindow::on_APUA_clicked()
{
    if(!apu_a.getStanje()){
        apu_gumb_a(true);
        apu_a.setStanje(true);
    } else {
        p_a.setBioUpaljen(false);
        apu_gumb_a(false);
        apu_a.setStanje(false);
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

void MainWindow::on_RUzemljenjaB_clicked()
{
    ui->textBrowser->append("DV-C: Nije moguce proizvoljno upravljati rastavljacem uzemljenja");
}

void MainWindow::on_SRastavljacB_clicked()
{
    enable_dv_c(false);
    if(p_b.getStanje()){
        ui->textBrowser->append("DV-C: Nije moguce upaliti sabirnicki rastavljac ako je prekidac ukljucen");
        enable_dv_c(true);
        return;
    }
    if(!sr_b.getStanje()){
        sabirnicki_rastavljac_gumb_b(true);
        sr_b.setStanje(true);
    } else {
        sabirnicki_rastavljac_gumb_b(false);
        sr_b.setStanje(false);
    }
    enable_dv_c(true);
}

void MainWindow::on_LRastavljacB_clicked()
{
    enable_dv_c(false);
    if(p_b.getStanje()){
        ui->textBrowser->append("DV-C: Nije moguce upaliti linijski rastavljac ako je prekidac ukljucen");
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

void MainWindow::on_APUB_clicked()
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



//upravljanje zastitom
void MainWindow::on_Zastita_clicked()
{
    enable_dv_b(false);
    enable_dv_c(false);
    if(!zastita.getStanje()){
        prorada_zastite(true);
        zastita.upaliZastitu(rastavljaci_a, p_a);
        zastita.upaliZastitu(rastavljaci_b, p_b);
    } else {
        prorada_zastite(false);
        zastita.ugasiZastitu(apu_a, rastavljaci_a, p_a);
        zastita.ugasiZastitu(apu_b, rastavljaci_b, p_b);
        if(p_a.getStanje() && p_b.getStanje()){
            linija_linijski_rastavljaci(true);
        }
    }
    if(p_a.getUpravljanje() && p_b.getUpravljanje()){
        enable_dv_b(true);
        enable_dv_c(true);
    }
}

void MainWindow::on_promjenaUpravljanja_clicked()
{
    if(p_a.getUpravljanje() && p_b.getUpravljanje()){
        ui->textBrowser->append("Ukljuceno lokalno upravljanje: Upozorenje! Nije moguce upravljati poljima!");
        ui->promjenaUpravljanja->setText("Lokalno");
        p_a.setUpravljanje(false);
        p_b.setUpravljanje(false);
        enable_dv_b(false);
        enable_dv_c(false);
    } else{
        ui->textBrowser->append("Ukljuceno daljinsko upravljanje");
        ui->promjenaUpravljanja->setText("Daljinsko");
        p_a.setUpravljanje(true);
        p_b.setUpravljanje(true);
        enable_dv_b(true);
        enable_dv_c(true);
    }
}

void MainWindow::on_prikaz_signala_a_clicked()
{
    if(!s_a){
        s_a = true;
        ui->signali_a->setVisible(true);
    } else {
        s_a = false;
        ui->signali_a->setVisible(false);
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
