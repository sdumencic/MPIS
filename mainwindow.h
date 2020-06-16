#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //datoteke za signale
    void read_file_signali_b();
    void read_file_signali_c();

    //gumbi-b
    void glavni_sabirnicki_rastavljac_gumb_b(bool);
    void pomocni_sabirnicki_rastavljac_gumb_b(bool);
    void rastavljac_uzemljenja_gumb_b(bool);
    void prekidac_gumb_b(bool prorada);
    void linijski_rastavljac_gumb_b(bool);
    void apu_gumb_b(bool);

    //gumbi-c
    void sabirnicki_rastavljac_gumb_c(bool);
    void rastavljac_uzemljenja_gumb_c(bool);
    void prekidac_gumb_c(bool);
    void linijski_rastavljac_gumb_c(bool);
    void apu_gumb_c(bool);

    //linije-b
    void linija_glavna_sabirnica_glavni_rastavljac_b(bool);
    void linija_pomocna_sabirnica_pomocni_rastavljac_b(bool);
    void linija_iz_glavnog_rastavljaca_b(bool);
    void linija_iz_pomocnog_rastavljaca_b(bool);
    void linija_rastavljaci_prekidac_b(bool);
    void linija_rastavljaca_uzemljenja_b(bool);
    void linija_prekidac_apu_b(bool);
    void linija_apu_linijski_rastavljac_b(bool);

    //linije-c
    void linija_sabirnica_rastavljac_c(bool);
    void linija_rastavljac_prekidac_c(bool);
    void linija_rastavljaca_uzemljenja_c(bool);
    void linija_prekidac_apu_c(bool);
    void linija_apu_linijski_rastavljac_c(bool);

    //linija izmedu
    void linija_linijski_rastavljaci(bool);


    void zastita_gumb(bool);

    void prorada_prekidaca_b(bool);
    void prorada_prekidaca_c(bool);

    void prorada_gl_sabirnickog_rastavljaca_b(bool);
    void prorada_pom_sabirnickog_rastavljaca_b(bool);

    void prorada_zastite(bool);

    void enable_dv_b(bool);
    void enable_dv_c(bool);

    void enable_upravljanje(bool);


private slots:
    void on_PrekidacA_clicked();

    void on_RUzemljenjaA_clicked();

    void on_SRastavljacA1_clicked();

    void on_SRastavljacA2_clicked();

    void on_LRastavljacA_clicked();

    void on_APU_B_clicked();


    void on_PrekidacB_clicked();

    void on_RUzemljenjaB_clicked();

    void on_SRastavljacB_clicked();

    void on_LRastavljacB_clicked();

    void on_APU_C_clicked();


    void on_Zastita_clicked();

    void on_promjenaUpravljanja_clicked();

    void on_prikaz_signala_b_clicked();

    void on_prikaz_signala_c_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
