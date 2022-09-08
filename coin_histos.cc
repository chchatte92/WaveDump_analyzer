#include "root_stuff.h"
#include "coin_histos.h"

void coin_histos() {

/* Edep histos */
//edep_coin[0] = new TH1D("edep_coin_0","",400,0.,10000.);
edep_coin[0] = new TH1D("edep_coin_0","",1000,0.,10000.);
edep_coin[0]->GetXaxis()->CenterTitle();
edep_coin[0]->GetXaxis()->SetTitle("Edep [keV]");
edep_coin[0]->GetYaxis()->CenterTitle();
edep_coin[0]->GetYaxis()->SetTitle("Events");

//edep_coin[1] = new TH1D("edep_coin_1","",400,0.,10000.);
edep_coin[1] = new TH1D("edep_coin_1","",1000,0.,10000.);
edep_coin[1]->GetXaxis()->CenterTitle();
edep_coin[1]->GetXaxis()->SetTitle("Edep [keV]");
edep_coin[1]->GetYaxis()->CenterTitle();
edep_coin[1]->GetYaxis()->SetTitle("Events");

//edep_xor[0] = new TH1D("edep_xor_0","",400,0.,10000.);
edep_xor[0] = new TH1D("edep_xor_0","",1000,0.,10000.);
edep_xor[0]->GetXaxis()->CenterTitle();
edep_xor[0]->GetXaxis()->SetTitle("Edep [keV]");
edep_xor[0]->GetYaxis()->CenterTitle();
edep_xor[0]->GetYaxis()->SetTitle("Events");

//edep_xor[1] = new TH1D("edep_xor_1","",400,0.,10000.);
edep_xor[1] = new TH1D("edep_xor_1","",1000,0.,10000.);
edep_xor[1]->GetXaxis()->CenterTitle();
edep_xor[1]->GetXaxis()->SetTitle("Edep [keV]");
edep_xor[1]->GetYaxis()->CenterTitle();
edep_xor[1]->GetYaxis()->SetTitle("Events");

edep_tot_coin = new TH1D("edep_tot_coin","",400,0.,10000.);
edep_tot_coin->GetXaxis()->CenterTitle();
edep_tot_coin->GetXaxis()->SetTitle("Edep [keV]");
edep_tot_coin->GetYaxis()->CenterTitle();
edep_tot_coin->GetYaxis()->SetTitle("Events");

edep_n = new TH1D("edep_n","",1000,-3500.,6500.);
edep_n->GetXaxis()->CenterTitle();
edep_n->GetXaxis()->SetTitle("En [keV]");
edep_n->GetYaxis()->CenterTitle();
edep_n->GetYaxis()->SetTitle("Events");

//edep_cor = new TH2D("edep_cor","",30,0.0,3000.0,30,0.0,3000.0);
//edep_cor = new TH2D("edep_cor","",85,0.0,8500.0,85,0.0,8500.0);
//edep_cor = new TH2D("edep_cor","",100,600.0,3100.0,100,600.0,3100.0);
edep_cor = new TH2D("edep_cor","",80,1000.0,8000.0,80,1000.0,8000.0);
edep_cor->GetXaxis()->CenterTitle();
edep_cor->GetXaxis()->SetTitle("E_{dep}^{CVD 1} [keV]");
edep_cor->GetYaxis()->CenterTitle();
edep_cor->GetYaxis()->SetTitle("E_{dep}^{CVD 2} [keV]");

//edep_dt_cor[0] = new TH2D("edep_dt_cor_0","",30,0.0,3000.0,20,-14.0,-6.0);
//edep_dt_cor[0] = new TH2D("edep_dt_cor_0","",85,0.0,8500.0,20,15.0,26.0);
//edep_dt_cor[0] = new TH2D("edep_dt_cor_0","",100,600.0,3100.0,48,-1.4,1.4); // 50 ps per bin
//edep_dt_cor[0] = new TH2D("edep_dt_cor_0","",100,600.0,3100.0,60,-1.2,1.2); // 40 ps per bin
edep_dt_cor[0] = new TH2D("edep_dt_cor_0","",100,1000.0,8000.0,180,-2.7,2.7); // 30 ps per bin
edep_dt_cor[0]->GetXaxis()->CenterTitle();
edep_dt_cor[0]->GetXaxis()->SetTitle("E_{dep}^{CVD 1} [keV]");
edep_dt_cor[0]->GetYaxis()->CenterTitle();
edep_dt_cor[0]->GetYaxis()->SetTitle("#Delta t ns");

//edep_dt_cor[1] = new TH2D("edep_dt_cor_1","",30,0.0,3000.0,20,-14.0,-6.0);
//edep_dt_cor[1] = new TH2D("edep_dt_cor_1","",85,0.0,8500.0,20,15.0,26.0);
//edep_dt_cor[1] = new TH2D("edep_dt_cor_1","",100,600.0,3100.0,48,-1.4,1.4); // 50 ps per bin
//edep_dt_cor[1] = new TH2D("edep_dt_cor_1","",100,600.0,3100.0,60,-1.2,1.2); // 40 ps per bin
edep_dt_cor[1] = new TH2D("edep_dt_cor_1","",100,1000.0,8000.0,180,-2.7,2.7); // 30 ps per bin
edep_dt_cor[1]->GetXaxis()->CenterTitle();
edep_dt_cor[1]->GetXaxis()->SetTitle("E_{dep}^{CVD 2} [keV]");
edep_dt_cor[1]->GetYaxis()->CenterTitle();
edep_dt_cor[1]->GetYaxis()->SetTitle("#Delta t ns");


dt = new TH1D("dt","",1280,-64.,64.);
dt->GetXaxis()->CenterTitle();
dt->GetXaxis()->SetTitle("#Delta t ns");
dt->GetYaxis()->CenterTitle();
dt->GetYaxis()->SetTitle("Events");

dt_ts = new TH1D("dt_ts","",1280,-64.,64.);
dt_ts->GetXaxis()->CenterTitle();
dt_ts->GetXaxis()->SetTitle("#Delta t ns");
dt_ts->GetYaxis()->CenterTitle();
dt_ts->GetYaxis()->SetTitle("Events");

dt_gpx_stop = new TH1D("dt_gpx_stop","",1280,-64.,64.);
dt_gpx_stop->GetXaxis()->CenterTitle();
dt_gpx_stop->GetXaxis()->SetTitle("#Delta t ns");
dt_gpx_stop->GetYaxis()->CenterTitle();
dt_gpx_stop->GetYaxis()->SetTitle("Events");

dt_gpx_ts = new TH1D("dt_gpx_ts","",1280,-64.,64.);
dt_gpx_ts->GetXaxis()->CenterTitle();
dt_gpx_ts->GetXaxis()->SetTitle("#Delta t ns");
dt_gpx_ts->GetYaxis()->CenterTitle();
dt_gpx_ts->GetYaxis()->SetTitle("Events");

dt_gpx_1 = new TH1D("dt_gpx_1","",1280,-64.,64.);
dt_gpx_1->GetXaxis()->CenterTitle();
dt_gpx_1->GetXaxis()->SetTitle("#Delta t ns");
dt_gpx_1->GetYaxis()->CenterTitle();
dt_gpx_1->GetYaxis()->SetTitle("Events");

dt_gpx_2 = new TH1D("dt_gpx_2","",1280,-64.,64.);
dt_gpx_2->GetXaxis()->CenterTitle();
dt_gpx_2->GetXaxis()->SetTitle("#Delta t ns");
dt_gpx_2->GetYaxis()->CenterTitle();
dt_gpx_2->GetYaxis()->SetTitle("Events");

dt_gpx = new TH1D("dt_gpx","",1280,-64.,64.);
dt_gpx->GetXaxis()->CenterTitle();
dt_gpx->GetXaxis()->SetTitle("#Delta t ns");
dt_gpx->GetYaxis()->CenterTitle();
dt_gpx->GetYaxis()->SetTitle("Events");




}
