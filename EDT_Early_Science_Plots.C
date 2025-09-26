// 26/09/25 - Stephen JD Kay, University of York

// A script to make some quick plots of the -t distribution from an input file
// Execute via root -l 'EDT_Early_Science_Plots.C("Input_File.root")'
#define EDT_Early_Science_Plots_cxx
          
// Include relevant stuff
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TGaxis.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>
#include <TTree.h>
#include <TArc.h>
#include <TH1.h>
#include <TH2.h>
#include <TLatex.h>
#include <TLegend.h>
#include "ePICStyle.C"

void EDT_Early_Science_Plots(string InFilename = ""){

  gROOT->SetBatch(kTRUE); // Force script to always run without flashing up graphics
  //gROOT->ProcessLine("SetECCEStyle()");
  gStyle->SetOptStat(0);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  TString EDT_EarlyScience_rootFile;

  if(InFilename == ""){
    cout << "Enter a calorimeter filename to analyse: ";
    cin >> InFilename;
  }
  
  TString TInFilename = InFilename;
  EDT_EarlyScience_rootFile = TInFilename;

  if(gSystem->AccessPathName(EDT_EarlyScience_rootFile) == kTRUE){
    cerr << "!!!!! ERROR !!!!!" << endl << EDT_EarlyScience_rootFile << " not found" << endl << "!!!!! ERROR !!!!!" << endl;
    exit(0);
  }
  else{
    cout << "Opening " << EDT_EarlyScience_rootFile << endl;
  }
  
  TFile *InFile = new TFile(EDT_EarlyScience_rootFile);
  
  // Somewhat tedious, but manually grab each
  TH1F* tMC_Dist = (TH1F*)(((TH1F*)InFile->Get("ResultsDists/tEff_Plots/h1_tMC_Truth_0")))->Clone("tMC_Dist"); tMC_Dist->Sumw2();
  TH1F* tResult_Dist = (TH1F*)(((TH1F*)InFile->Get("ResultsDists/h1_tResult_0")))->Clone("tResult_Dist"); tResult_Dist->Sumw2();
  TH1F* tMCResult_Dist = (TH1F*)(((TH1F*)InFile->Get("ResultsDists/tEff_Plots/h1_tMC_Result_0")))->Clone("tMCResult_Dist"); tMCResult_Dist->Sumw2();
  TH1F* tEff_Dist = (TH1F*)(((TH1F*)InFile->Get("ResultsDists/tEff_Plots/h1_tMC_Eff_0")))->Clone("tEff_Dist"); tEff_Dist->Sumw2();
  TH1F* tResult_Scaled_Dist = (TH1F*)(((TH1F*)InFile->Get("ResultsDists/h1_tResult_0")))->Clone("tResult_Scaled_Dist"); tResult_Scaled_Dist->Sumw2();

  double InitialContent;
  for(int bin = 0; bin < tResult_Scaled_Dist->GetNbinsX(); bin++){
    InitialContent = tResult_Scaled_Dist->GetBinContent(bin);
    if(tEff_Dist->GetBinContent(bin) != 0){
      tResult_Scaled_Dist->SetBinContent(bin, InitialContent*(1/(tEff_Dist->GetBinContent(bin))));
    }
    if(tEff_Dist->GetBinContent(bin) < 0.02){
      tResult_Scaled_Dist->SetBinContent(bin, 0);
    }
  }
  
  TString Output_Name;
  TObjArray *tmp_Name_arr;
  // If input file name is provided as a path with / included - chop
  if(TInFilename.Contains("/")){
    tmp_Name_arr = TInFilename.Tokenize("/");
    Output_Name = (((TObjString *)(tmp_Name_arr->At(tmp_Name_arr->GetLast())))->String()).ReplaceAll(".root","");
  }
  else{
    Output_Name = TInFilename.ReplaceAll(".root","");
  }
  
  TCanvas *c_tDist = new TCanvas("c_tDist", "t Distribution", 100, 0, 2560, 1920);
  tMC_Dist->SetMarkerColor(1); tMC_Dist->SetLineColor(1);
  tMC_Dist->GetXaxis()->SetRangeUser(0, 0.5);
  tMC_Dist->Draw("Histerr");
  tResult_Dist->SetMarkerColor(2); tResult_Dist->SetLineColor(2);
  tResult_Scaled_Dist->SetMarkerColor(4); tResult_Scaled_Dist->SetLineColor(4);
  tMCResult_Dist->SetMarkerColor(8); tMCResult_Dist->SetLineColor(8);
  tResult_Dist->Draw("Samehisterr");
  tResult_Scaled_Dist->Draw("Samehisterr");
  tMCResult_Dist->Draw("samehisterr");
  TLegend *t_Legend = new TLegend(0.6, 0.65, 0.8, 0.85);
  t_Legend->SetTextSize(0.04);
  t_Legend->AddEntry(tMC_Dist, "MC Truth", "l");
  t_Legend->AddEntry(tResult_Dist, "Reco Raw", "l");
  t_Legend->AddEntry(tResult_Scaled_Dist, "Reco Corr", "l");
  t_Legend->AddEntry(tMCResult_Dist, "MC Accept", "l");
  t_Legend->Draw("SAME");
  
  c_tDist->Print(Output_Name+".pdf");

  TFile *OutFile = new TFile(Output_Name+".root", "RECREATE");
  tMC_Dist->Write();
  tResult_Dist->Write();
  tResult_Scaled_Dist->Write();
  tMCResult_Dist->Write();
  c_tDist->Write();
  OutFile->Close();
  InFile->Close();

}
