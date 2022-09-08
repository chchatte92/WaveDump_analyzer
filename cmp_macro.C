#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "TH1D.h"
#include "TVirtualFFT.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TMath.h"

using namespace std;

cmp_macro(){


gStyle->SetStatColor(0);
//gStyle->SetTitleColor(0);
gStyle->SetCanvasColor(0);
gStyle->SetPadColor(0);
gStyle->SetPadBorderMode(0);
gStyle->SetCanvasBorderMode(0);
gStyle->SetFrameBorderMode(0);
gStyle->SetTitleFillColor(0);

gStyle->SetOptStat(""); // No stat box
gStyle->SetOptFit(); //
gStyle->SetOptTitle(0);

gStyle->SetStatFontSize(0.03); //

gStyle->SetHistLineWidth(3);  // Default:1(GetHistLineWidth) --- Line width of histogram
gStyle->SetLineWidth(2);        // Default:1 --- Line width of axis.

gStyle->SetTitleYOffset(1.25);
//gStyle->SetLabelOffset(0.2, "X");
//gStyle->SetLabelOffset(0.3, "Y");
//gStyle->SetLabelSize(0.002, "X");
//gStyle->SetLabelSize(0.002, "Y");
//gStyle->SetLabelFont(61, "X");
//gStyle->SetLabelFont(61, "Y");

gROOT->SetStyle("Plain");


// C++ analyzer
TFile hf("adc_histos.root");

TH1D *h_noise_0 = new TH1D(*((TH1D*)hf.Get("noise_0")));
h_noise_0->SetDirectory(gROOT);
h_noise_0->SetName("cpp_noise_0");

TH1D *h_noise_1 = new TH1D(*((TH1D*)hf.Get("noise_1")));
h_noise_1->SetDirectory(gROOT);
h_noise_1->SetName("cpp_noise_1");

TH1D *h_noise_mean_0 = new TH1D(*((TH1D*)hf.Get("noise_mean_0")));
h_noise_mean_0->SetDirectory(gROOT);
h_noise_mean_0->SetName("cpp_noise_mean_0");

TH1D *h_noise_mean_1 = new TH1D(*((TH1D*)hf.Get("noise_mean_1")));
h_noise_mean_1->SetDirectory(gROOT);
h_noise_mean_1->SetName("cpp_noise_mean_1");

TH1D *h_width_0 = new TH1D(*((TH1D*)hf.Get("width_0")));
h_width_0->SetDirectory(gROOT);
h_width_0->SetName("cpp_width_0");

TH1D *h_width_1 = new TH1D(*((TH1D*)hf.Get("width_1")));
h_width_1->SetDirectory(gROOT);
h_width_1->SetName("cpp_width_1");

TH1D *h_edep_0 = new TH1D(*((TH1D*)hf.Get("edep_0")));
h_edep_0->SetDirectory(gROOT);
h_edep_0->SetName("cpp_edep_0");

TH1D *h_edep_1 = new TH1D(*((TH1D*)hf.Get("edep_1")));
h_edep_1->SetDirectory(gROOT);
h_edep_1->SetName("cpp_edep_1");

TH1D *h_edep_bkg_0 = new TH1D(*((TH1D*)hf.Get("edep_bkg_0")));
h_edep_bkg_0->SetDirectory(gROOT);
h_edep_bkg_0->SetName("cpp_edep_bkg_0");

TH1D *h_edep_bkg_1 = new TH1D(*((TH1D*)hf.Get("edep_bkg_1")));
h_edep_bkg_1->SetDirectory(gROOT);
h_edep_bkg_1->SetName("cpp_edep_bkg_1");





hf.Close();





// ROOT macro analyzer
TFile hfr("../../analyze/coin_sdw_10k.root");

TH1D *hr_noise_0 = new TH1D(*((TH1D*)hfr.Get("noise_0")));
hr_noise_0->SetDirectory(gROOT);
hr_noise_0->SetName("root_noise_0");

TH1D *hr_noise_1 = new TH1D(*((TH1D*)hfr.Get("noise_1")));
hr_noise_1->SetDirectory(gROOT);
hr_noise_1->SetName("root_noise_1");

TH1D *hr_noise_mean_0 = new TH1D(*((TH1D*)hfr.Get("noise_0m")));
hr_noise_mean_0->SetDirectory(gROOT);
hr_noise_mean_0->SetName("root_noise_mean_0");

TH1D *hr_noise_mean_1 = new TH1D(*((TH1D*)hfr.Get("noise_1m")));
hr_noise_mean_1->SetDirectory(gROOT);
hr_noise_mean_1->SetName("root_noise_mean_1");

TH1D *hr_width_0 = new TH1D(*((TH1D*)hfr.Get("width_0")));
hr_width_0->SetDirectory(gROOT);
hr_width_0->SetName("root_width_0");

TH1D *hr_width_1 = new TH1D(*((TH1D*)hfr.Get("width_1")));
hr_width_1->SetDirectory(gROOT);
hr_width_1->SetName("root_width_1");

TH1D *hr_edep_0 = new TH1D(*((TH1D*)hfr.Get("edep_0m")));
hr_edep_0->SetDirectory(gROOT);
hr_edep_0->SetName("root_edep_0");

TH1D *hr_edep_1 = new TH1D(*((TH1D*)hfr.Get("edep_1m")));
hr_edep_1->SetDirectory(gROOT);
hr_edep_1->SetName("root_edep_1");

TH1D *hr_edep_bkg_0 = new TH1D(*((TH1D*)hfr.Get("edep_bkg_0")));
hr_edep_bkg_0->SetDirectory(gROOT);
hr_edep_bkg_0->SetName("root_edep_bkg_0");

TH1D *hr_edep_bkg_1 = new TH1D(*((TH1D*)hfr.Get("edep_bkg_1")));
hr_edep_bkg_1->SetDirectory(gROOT);
hr_edep_bkg_1->SetName("root_edep_bkg_1");

hfr.Close();






//  Draw
TCanvas *c1 = new TCanvas("c1","Noise ch0");
//c1->SetLogx();
//c1->SetLogy();
c1->Update();

//hm_ch1[1]->Scale(1.05e-3); //rescale to the same initial gain
//hm_ch1[1]->GetXaxis()->SetTitle("Block number [22 mrad]");
//hm_ch1[1]->GetYaxis()->SetTitle("E_{t} [MeV]");
//hm_ch1[1]->SetAxisRange(0.0, 90.0, "x");

h_noise_0->SetLineColor(2);
h_noise_0->Draw();
hr_noise_0->SetLineWidth(1);
hr_noise_0->SetLineStyle(2);
hr_noise_0->SetLineColor(1);
hr_noise_0->Draw("SAME");

//c1->Print("tapiro_et_drift_sf_d1_sdw1.ps");


//  Draw
TCanvas *c2 = new TCanvas("c2","Noise ch1");
//c2->SetLogx();
//c2->SetLogy();
c2->Update();

h_noise_1->SetLineColor(2);
h_noise_1->Draw();
hr_noise_1->SetLineWidth(1);
hr_noise_1->SetLineStyle(2);
hr_noise_1->SetLineColor(1);
hr_noise_1->Draw("SAME");

//  Draw
TCanvas *c3 = new TCanvas("c3","Mean Noise ch0");
//c3->SetLogx();
//c3->SetLogy();
c3->Update();

h_noise_mean_0->SetLineColor(2);
h_noise_mean_0->Draw();
hr_noise_mean_0->SetLineWidth(1);
hr_noise_mean_0->SetLineStyle(2);
hr_noise_mean_0->SetLineColor(1);
hr_noise_mean_0->Draw("SAME");


//  Draw
TCanvas *c4 = new TCanvas("c4","Mean Noise ch1");
//c4->SetLogx();
//c4->SetLogy();
c4->Update();

h_noise_mean_1->SetLineColor(2);
h_noise_mean_1->Draw();
hr_noise_mean_1->SetLineWidth(1);
hr_noise_mean_1->SetLineStyle(2);
hr_noise_mean_1->SetLineColor(1);
hr_noise_mean_1->Draw("SAME");



//  Draw
TCanvas *c5 = new TCanvas("c5","Width ch0");
//c5->SetLogx();
//c5->SetLogy();
c5->Update();

h_width_0->SetLineColor(2);
h_width_0->Draw();
hr_width_0->SetLineWidth(1);
hr_width_0->SetLineStyle(2);
hr_width_0->SetLineColor(1);
hr_width_0->Draw("SAME");


//  Draw
TCanvas *c6 = new TCanvas("c6","Width ch1");
//c6->SetLogx();
//c6->SetLogy();
c6->Update();

h_width_1->SetLineColor(2);
h_width_1->Draw();
hr_width_1->SetLineWidth(1);
hr_width_1->SetLineStyle(2);
hr_width_1->SetLineColor(1);
hr_width_1->Draw("SAME");


//  Draw
TCanvas *c7 = new TCanvas("c7","Edep ch0");
//c7->SetLogx();
//c7->SetLogy();
c7->Update();

h_edep_0->SetLineColor(2);
h_edep_0->Draw();
hr_edep_0->SetLineWidth(1);
hr_edep_0->SetLineStyle(2);
hr_edep_0->SetLineColor(1);
hr_edep_0->Draw("SAME");


//  Draw
TCanvas *c8 = new TCanvas("c8","Edep ch1");
//c8->SetLogx();
//c8->SetLogy();
c8->Update();

h_edep_1->SetLineColor(2);
h_edep_1->Draw();
hr_edep_1->SetLineWidth(1);
hr_edep_1->SetLineStyle(2);
hr_edep_1->SetLineColor(1);
hr_edep_1->Draw("SAME");

//  Draw
TCanvas *c9 = new TCanvas("c9","Edep Bkg. ch0");
//c9->SetLogx();
//c9->SetLogy();
c9->Update();

h_edep_bkg_0->SetLineColor(2);
h_edep_bkg_0->Draw();
hr_edep_bkg_0->SetLineWidth(1);
hr_edep_bkg_0->SetLineStyle(2);
hr_edep_bkg_0->SetLineColor(1);
hr_edep_bkg_0->Draw("SAME");


//  Draw
TCanvas *c10 = new TCanvas("c10","Edep Bkg. ch1");
//c10->SetLogx();
//c10->SetLogy();
c10->Update();

h_edep_bkg_1->SetLineColor(2);
h_edep_bkg_1->Draw();
hr_edep_bkg_1->SetLineWidth(1);
hr_edep_bkg_1->SetLineStyle(2);
hr_edep_bkg_1->SetLineColor(1);
hr_edep_bkg_1->Draw("SAME");



}
