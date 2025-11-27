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
#include <vector>

void ePIC_Plot(Double_t TextXPos, Double_t TextYPos, Double_t LogoXPos, Double_t LogoYPos, TString BeamE){
  TLatex Text_com;
  Text_com.SetTextSize(0.04);
  Text_com.SetTextFont(42);
  Text_com.SetTextAlign(13);  //align at top
  Text_com.DrawLatexNDC(TextXPos,TextYPos-0.04,Form("e+p, %s(e)x%s(p)", ((TObjString *)((BeamE.Tokenize("on"))->At(0)))->String().Data(), ((TObjString *)((BeamE.Tokenize("on"))->At(1)))->String().Data()));
  Text_com.DrawLatexNDC(TextXPos,TextYPos-0.08,"25.10.2 Campaign");
  Text_com.DrawLatexNDC(TextXPos,TextYPos-0.12,"DEMPgen 1.2.4");
  Text_com.DrawLatexNDC(TextXPos,TextYPos-0.16,"DEMP ep#rightarrow e'n#pi^{+}");
  TLatex Text_ePIC;
  Text_ePIC.SetTextSize(0.04);
  Text_ePIC.SetTextFont(62);
  Text_ePIC.DrawLatexNDC(TextXPos,TextYPos,"ePIC Performance");  // performance plot
  //Text_ePIC.DrawLatexNDC(.15,.88,"ePIC Internal");  // for internal use only
  //Text_ePIC.DrawLatexNDC(.15,.88,"ePIC Preliminary"); // preliminary released version
  //Text_ePIC.DrawLatexNDC(.15,.88,"ePIC Work in Progress"); // work in progress to be shown outside
  //Text_ePIC.DrawLatexNDC(.15,.88,"ePIC"); // final published version
  // ===== Add ePIC logo to the figure if desired ======
  TImage *logo = TImage::Open("EPIC-logo_black_small.png");
  TPad *pad2 = new TPad("pad2", "Pad 2", LogoXPos, LogoYPos, LogoXPos + 0.13, LogoYPos + 0.13); // Create a new pad and then draw the image in it
  pad2->Draw();
  pad2->cd(); // Enter the new pad
  logo->Draw();
}

void EDT_Early_Science_Plots(string InFilename = "", TString InBeamE =""){

  gROOT->SetBatch(kTRUE); // Force script to always run without flashing up graphics
  gROOT->ProcessLine("SetePICStyle()");
  gStyle->SetOptStat(0);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  TString kp6[6] = {"#7021dd", "#9c9ca1", "#964a8b", "#e42536", "#f89c20", "#5790fc"};
  TString EDT_EarlyScience_rootFile;
  
  if(InFilename == ""){
    cout << "Enter a calorimeter filename to analyse: ";
    cin >> InFilename;
  }

  if (InBeamE == ""){
    cout << "Enter a beam energy combination in the format - XonY - where X is the electron beam energy in GeV and Y is the proton beam energy:" << endl;
    cin >> InBeamE;
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
  tMC_Dist->SetMarkerColor(TColor::GetColor(kp6[0].Data())); tMC_Dist->SetLineColor(TColor::GetColor(kp6[0].Data()));
  tMC_Dist->GetXaxis()->SetRangeUser(0, 0.5);
  tMC_Dist->GetXaxis()->SetTitleOffset(1);
  tMC_Dist->Draw("Histerr");
  tResult_Dist->SetMarkerColor(TColor::GetColor(kp6[4].Data())); tResult_Dist->SetLineColor(TColor::GetColor(kp6[4].Data()));
  tResult_Scaled_Dist->SetMarkerColor(TColor::GetColor(kp6[3].Data())); tResult_Scaled_Dist->SetLineColor(TColor::GetColor(kp6[3].Data()));
  tMCResult_Dist->SetMarkerColor(TColor::GetColor(kp6[2].Data())); tMCResult_Dist->SetLineColor(TColor::GetColor(kp6[2].Data()));
  tResult_Dist->Draw("Samehisterr");
  tResult_Scaled_Dist->Draw("Samehisterr");
  tMCResult_Dist->Draw("samehisterr");
  TLegend *t_Legend = new TLegend(0.6, 0.5, 0.8, 0.7);
  t_Legend->SetTextSize(0.04);
  t_Legend->AddEntry(tMC_Dist, "MC Truth", "l");
  t_Legend->AddEntry(tResult_Dist, "Reco Raw", "l");
  t_Legend->AddEntry(tResult_Scaled_Dist, "Reco Corr", "l");
  t_Legend->AddEntry(tMCResult_Dist, "MC Accept", "l");
  t_Legend->Draw("SAME");
  ePIC_Plot(0.35, 0.88, 0.87, 0.8, InBeamE);  
  c_tDist->Print(Output_Name+".pdf");
  c_tDist->Print(Output_Name+".png");

  TFile *OutFile = new TFile(Output_Name+".root", "RECREATE");
  tMC_Dist->Write();
  tResult_Dist->Write();
  tResult_Scaled_Dist->Write();
  tMCResult_Dist->Write();
  c_tDist->Write();
  OutFile->Close();
  InFile->Close();

}

