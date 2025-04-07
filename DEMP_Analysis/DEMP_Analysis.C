// Stephen JD Kay - University of York
// Stephen.Kay@york.ac.uk
// 28/03/25
// New DEMP Analysis script based upon Love's earlier work, segmented code out into functions and tried to make it more generic
// Need to make sub folders for output file
// Far too many 
using namespace ROOT::Math;

#include "TString.h"
#include "DEMP_Analysis.h"
#include "DEMP_Hists.h"

void FillMCKin(float wgt){
  FillHist1D("h1_Q2_MC", Q2_MC, wgt);
  FillHist1D("h1_t_MC", t_MC, wgt);
  FillHist1D("h1_W_MC", W_MC, wgt);
  FillHist1D("h1_eps_MC", eps_MC, wgt);
  FillHist1D("h1_y_MC", y_MC, wgt);
  FillHist2D("h2_tQ2_MC", t_MC, Q2_MC, wgt);
  FillHist2D("h2_WQ2_MC", W_MC, Q2_MC, wgt);

  FillHist1D("h1_Q2_MC_NoAB", Q2_MC_NoAB, wgt);
  FillHist1D("h1_t_MC_NoAB", t_MC_NoAB, wgt);
  FillHist1D("h1_W_MC_NoAB", W_MC_NoAB, wgt);
  FillHist1D("h1_eps_MC_NoAB", eps_MC_NoAB, wgt);
  FillHist1D("h1_y_MC_NoAB", y_MC_NoAB, wgt);
  FillHist2D("h2_tQ2_MC_NoAB", t_MC_NoAB, Q2_MC_NoAB, wgt);
  FillHist2D("h2_WQ2_MC_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
}

void FillNeutAccept(PxPyPzEVector n_Rec, PxPyPzEVector nRot_Rec, XYZVector n_Vertex, PxPyPzEVector n_MC, PxPyPzEVector n_MC_NoAB, float wgt, Bool_t ZDC, Bool_t Kin){
  FillHist2D("h2_n_pTheta_RecoAccept", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  FillHist2D("h2_nRot_pTheta_RecoAccept", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAccept", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAccept_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAcceptZDC", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAcceptZDC_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
  if(ZDC == kTRUE){
    FillHist2D("h2_n_XY_RecoAccept", n_Vertex.X(), n_Vertex.Y(), wgt);
    FillHist2D("h2_n_pTheta_RecoAcceptZDC", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
    FillHist2D("h2_nRot_pTheta_RecoAcceptZDC", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
    FillHist2D("h2_nRot_XY_RecoAccept", 35000*sin(nRot_Rec.Theta())*cos(nRot_Rec.Phi()), 35000*sin(nRot_Rec.Theta())*sin(nRot_Rec.Phi()), wgt);
    if(Kin == kTRUE){
      FillHist1D("h1_Q2_MCAcceptZDC", Q2_MC, wgt);
      FillHist1D("h1_t_MCAcceptZDC", t_MC, wgt);
      FillHist1D("h1_W_MCAcceptZDC", W_MC, wgt);
      FillHist1D("h1_eps_MCAcceptZDC", eps_MC, wgt);
      FillHist1D("h1_y_MCAcceptZDC", y_MC, wgt);
      FillHist2D("h2_tQ2_MCAcceptZDC", t_MC, Q2_MC, wgt);
      FillHist2D("h2_WQ2_MCAcceptZDC", W_MC, Q2_MC, wgt);
      FillHist1D("h1_Q2_MCAcceptZDC_NoAB", Q2_MC_NoAB, wgt);
      FillHist1D("h1_t_MCAcceptZDC_NoAB", t_MC_NoAB, wgt);
      FillHist1D("h1_W_MCAcceptZDC_NoAB", W_MC_NoAB, wgt);
      FillHist1D("h1_eps_MCAcceptZDC_NoAB", eps_MC_NoAB, wgt);
      FillHist1D("h1_y_MCAcceptZDC_NoAB", y_MC_NoAB, wgt);
      FillHist2D("h2_tQ2_MCAcceptZDC_NoAB", t_MC_NoAB, Q2_MC_NoAB, wgt);
      FillHist2D("h2_WQ2_MCAcceptZDC_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
    }	    
  }
}

void FillB0Accept(int nClus, int nClusAccept, PxPyPzEVector n_Rec, PxPyPzEVector nRot_Rec, XYZVector n_Vertex, PxPyPzEVector n_MC, PxPyPzEVector n_MC_NoAB, Double_t EB0, float wgt, Bool_t Kin){
  FillHist1D("h1_B0_nClusters_AcceptRaw", nClus);
  FillHist1D("h1_B0_nClusters_Accept", nClusAccept);
  FillHist2D("h2_n_pTheta_RecoAccept", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  FillHist2D("h2_nRot_pTheta_RecoAccept", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
  FillHist2D("h2_n_ETheta_RecoAcceptB0", n_Vertex.Theta()*TMath::RadToDeg(), EB0, wgt);
  FillHist2D("h2_n_pTheta_RecoAcceptB0", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  FillHist2D("h2_nRot_pTheta_RecoAcceptB0", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAccept", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAcceptB0", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAccept_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAcceptB0_NoAb", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
  FillHist2D("h2_B0_XY_Accept", n_Vertex.X(), n_Vertex.Y());
  FillHist2D("h2_B0_XY_AcceptWeighted", n_Vertex.X(), n_Vertex.Y(), wgt);
  FillHist2D("h2_B0_XY_MCAccept",6800*sin(n_MC.Theta())*cos(n_MC.Phi()), 6800*sin(n_MC.Theta())*sin(n_MC.Phi()), wgt);
  if(Kin == kTRUE){
    FillHist1D("h1_Q2_MCAcceptB0", Q2_MC, wgt);
    FillHist1D("h1_t_MCAcceptB0", t_MC, wgt);
    FillHist1D("h1_W_MCAcceptB0", W_MC, wgt);
    FillHist1D("h1_eps_MCAcceptB0", eps_MC, wgt);
    FillHist1D("h1_y_MCAcceptB0", y_MC, wgt);
    FillHist2D("h2_tQ2_MCAcceptB0", t_MC, Q2_MC, wgt);
    FillHist2D("h2_WQ2_MCAcceptB0", W_MC, Q2_MC, wgt);

    FillHist1D("h1_Q2_MCAcceptB0_NoAB", Q2_MC_NoAB, wgt);
    FillHist1D("h1_t_MCAcceptB0_NoAB", t_MC_NoAB, wgt);
    FillHist1D("h1_W_MCAcceptB0_NoAB", W_MC_NoAB, wgt);
    FillHist1D("h1_eps_MCAcceptB0_NoAB", eps_MC_NoAB, wgt);
    FillHist1D("h1_y_MCAcceptB0_NoAB", y_MC_NoAB, wgt);
    FillHist2D("h2_tQ2_MCAcceptB0_NoAB", t_MC_NoAB, Q2_MC_NoAB, wgt);
    FillHist2D("h2_WQ2_MCAcceptB0_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
  }	    
}

void FillDEMPAccept_EventDists_NoCuts(PxPyPzEVector eSc_MC, PxPyPzEVector eSc_MC_NoAB, PxPyPzEVector eSc_Rec, PxPyPzEVector Pi_MC, PxPyPzEVector Pi_MC_NoAB, PxPyPzEVector Pi_Rec, PxPyPzEVector n_MC, PxPyPzEVector n_MC_NoAB, PxPyPzEVector n_Rec, PxPyPzEVector nRot_Rec, float wgt, Bool_t ZDC, Bool_t B0, Bool_t nZDC, Bool_t nB0){
  FillHist2D("h2_eSc_pTheta_MCDEMPAccept_NoCuts", eSc_MC.Theta()*TMath::RadToDeg(), eSc_MC.P(), wgt);
  FillHist2D("h2_Pi_pTheta_MCDEMPAccept_NoCuts", Pi_MC.Theta()*TMath::RadToDeg(), Pi_MC.P(), wgt);
  FillHist2D("h2_n_pTheta_MCDEMPAccept_NoCuts", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
  FillHist2D("h2_eSc_pTheta_MCDEMPAccept_NoCuts_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
  FillHist2D("h2_Pi_pTheta_MCDEMPAccept_NoCuts_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
  FillHist2D("h2_n_pTheta_MCDEMPAccept_NoCuts_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);	
  FillHist2D("h2_eSc_pTheta_RecoDEMPAccept_NoCuts", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
  FillHist2D("h2_Pi_pTheta_RecoDEMPAccept_NoCuts", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
  FillHist2D("h2_n_pTheta_RecoDEMPAccept_NoCuts", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  FillHist2D("h2_nRot_pTheta_RecoDEMPAccept_NoCuts", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
  if(ZDC == kTRUE && nZDC == kTRUE){
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptZDC_NoCuts", eSc_MC.Theta()*TMath::RadToDeg(), eSc_MC.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptZDC_NoCuts", Pi_MC.Theta()*TMath::RadToDeg(), Pi_MC.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptZDC_NoCuts", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
    FillHist2D("h2_eSc_pTheta_RecoDEMPAcceptZDC_NoCuts", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
    FillHist2D("h2_Pi_pTheta_RecoDEMPAcceptZDC_NoCuts", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
    FillHist2D("h2_n_pTheta_RecoDEMPAcceptZDC_NoCuts", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  }
  if(B0 == kTRUE && nB0 == kTRUE){
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptB0_NoCuts", eSc_MC.Theta()*TMath::RadToDeg(), eSc_MC.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptB0_NoCuts", Pi_MC.Theta()*TMath::RadToDeg(), Pi_MC.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptB0_NoCuts", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptB0_NoCuts_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptB0_NoCuts_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptB0_NoCuts_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
    FillHist2D("h2_eSc_pTheta_RecoDEMPAcceptB0_NoCuts", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
    FillHist2D("h2_Pi_pTheta_RecoDEMPAcceptB0_NoCuts", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
    FillHist2D("h2_n_pTheta_RecoDEMPAcceptB0_NoCuts", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  }
}

void FillDEMPAccept_Kin_NoCuts(Bool_t ZDC, Bool_t nZDC, Bool_t B0, Bool_t nB0, float wgt){

  // Fill reconstructed Q2/W/eps/y plots for DEMP events before cuts
  FillHist1D("h1_Q2_Reco_NoCuts", Q2_Rec ,wgt);
  FillHist1D("h1_W_Reco_NoCuts", W_Rec, wgt);
  FillHist1D("h1_eps_Reco_NoCuts", eps_Rec, wgt);
  FillHist1D("h1_y_Reco_NoCuts", y_Rec, wgt);
  FillHist2D("h2_WQ2_Reco_NoCuts", W_Rec, Q2_Rec, wgt);
      
  // Fill MC DEMP accepted Q2/W/eps/y plots for DEMP events before cuts
  FillHist1D("h1_Q2_MCDEMPAccept_NoCuts", Q2_MC, wgt);
  FillHist1D("h1_W_MCDEMPAccept_NoCuts", W_MC, wgt);
  FillHist1D("h1_eps_MCDEMPAccept_NoCuts", eps_MC, wgt);
  FillHist1D("h1_y_MCDEMPAccept_NoCuts", y_MC, wgt);
  FillHist2D("h2_WQ2_MCDEMPAccept_NoCuts", W_MC, Q2_MC, wgt);
  FillHist1D("h1_Q2_MCDEMPAccept_NoCuts_NoAB", Q2_MC_NoAB, wgt);
  FillHist1D("h1_W_MCDEMPAccept_NoCuts_NoAB", W_MC_NoAB, wgt);
  FillHist1D("h1_eps_MCDEMPAccept_NoCuts_NoAB", eps_MC_NoAB, wgt);
  FillHist1D("h1_y_MCDEMPAccept_NoCuts_NoAB", y_MC_NoAB, wgt);
  FillHist2D("h2_WQ2_MCDEMPAccept_NoCuts_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
  if(ZDC == kTRUE && nZDC== kTRUE){
    FillHist1D("h1_Q2_ZDCReco_NoCuts", Q2_Rec ,wgt);
    FillHist1D("h1_W_ZDCReco_NoCuts", W_Rec, wgt);
    FillHist1D("h1_eps_ZDCReco_NoCuts", eps_Rec, wgt);
    FillHist1D("h1_y_ZDCReco_NoCuts", y_Rec, wgt);
    FillHist2D("h2_WQ2_ZDCReco_NoCuts", W_Rec, Q2_Rec, wgt);

    FillHist1D("h1_Q2_MCDEMPAcceptZDC_NoCuts", Q2_MC, wgt);
    FillHist1D("h1_W_MCDEMPAcceptZDC_NoCuts", W_MC, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptZDC_NoCuts", eps_MC, wgt);
    FillHist1D("h1_y_MCDEMPAcceptZDC_NoCuts", y_MC, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptZDC_NoCuts", W_MC, Q2_MC, wgt);
    FillHist1D("h1_Q2_MCDEMPAcceptZDC_NoCuts_NoAB", Q2_MC_NoAB, wgt);
    FillHist1D("h1_W_MCDEMPAcceptZDC_NoCuts_NoAB", W_MC_NoAB, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptZDC_NoCuts_NoAB", eps_MC_NoAB, wgt);
    FillHist1D("h1_y_MCDEMPAcceptZDC_NoCuts_NoAB", y_MC_NoAB, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptZDC_NoCuts_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
  }
  if(B0 == kTRUE && nB0 == kTRUE){
    FillHist1D("h1_Q2_B0Reco_NoCuts", Q2_Rec ,wgt);
    FillHist1D("h1_W_B0Reco_NoCuts", W_Rec, wgt);
    FillHist1D("h1_eps_B0Reco_NoCuts", eps_Rec, wgt);
    FillHist1D("h1_y_B0Reco_NoCuts", y_Rec, wgt);
    FillHist2D("h2_WQ2_B0Reco_NoCuts", W_Rec, Q2_Rec, wgt);

    FillHist1D("h1_Q2_MCDEMPAcceptB0_NoCuts", Q2_MC, wgt);
    FillHist1D("h1_W_MCDEMPAcceptB0_NoCuts", W_MC, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptB0_NoCuts", eps_MC, wgt);
    FillHist1D("h1_y_MCDEMPAcceptB0_NoCuts", y_MC, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptB0_NoCuts", W_MC, Q2_MC, wgt);
    FillHist1D("h1_Q2_MCDEMPAcceptB0_NoCuts_NoAB", Q2_MC_NoAB, wgt);
    FillHist1D("h1_W_MCDEMPAcceptB0_NoCuts_NoAB", W_MC_NoAB, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptB0_NoCuts_NoAB", eps_MC_NoAB, wgt);
    FillHist1D("h1_y_MCDEMPAcceptB0_NoCuts_NoAB", y_MC_NoAB, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptB0_NoCuts_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
  }
}

void FillDEMPAccept_EventDists(PxPyPzEVector eSc_MC, PxPyPzEVector eSc_MC_NoAB, PxPyPzEVector eSc_Rec, PxPyPzEVector Pi_MC, PxPyPzEVector Pi_MC_NoAB, PxPyPzEVector Pi_Rec, PxPyPzEVector n_MC, PxPyPzEVector n_MC_NoAB, PxPyPzEVector n_Rec, PxPyPzEVector nRot_Rec, float wgt, Bool_t ZDC, Bool_t B0, Bool_t nZDC, Bool_t nB0){

  FillHist2D("h2_eSc_pTheta_MCDEMPAccept", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
  FillHist2D("h2_Pi_pTheta_MCDEMPAccept", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
  FillHist2D("h2_n_pTheta_MCDEMPAccept", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
  FillHist2D("h2_eSc_pTheta_MCDEMPAccept_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
  FillHist2D("h2_Pi_pTheta_MCDEMPAccept_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
  FillHist2D("h2_n_pTheta_MCDEMPAccept_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
  FillHist2D("h2_eSc_pTheta_RecoDEMPAccept", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
  FillHist2D("h2_Pi_pTheta_RecoDEMPAccept", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
  FillHist2D("h2_n_pTheta_RecoDEMPAccept", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  FillHist2D("h2_nRot_pTheta_RecoDEMPAccept", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
  if(ZDC == kTRUE && nZDC == kTRUE){
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptZDC", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptZDC", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptZDC", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptZDC_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptZDC_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptZDC_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
    FillHist2D("h2_eSc_pTheta_RecoDEMPAcceptZDC", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
    FillHist2D("h2_Pi_pTheta_RecoDEMPAcceptZDC", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
    FillHist2D("h2_n_pTheta_RecoDEMPAcceptZDC", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  }
  if(B0 == kTRUE && nB0 == kTRUE){
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptB0", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptB0", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptB0", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptB0_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptB0_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptB0_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
    FillHist2D("h2_eSc_pTheta_RecoDEMPAcceptB0", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
    FillHist2D("h2_Pi_pTheta_RecoDEMPAcceptB0", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
    FillHist2D("h2_n_pTheta_RecoDEMPAcceptB0", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  }  
}

void FillDEMPAccept_Kin(Bool_t ZDC, Bool_t nZDC, Bool_t B0, Bool_t nB0, float wgt){;

  FillHist1D("h1_Q2_Reco", Q2_Rec, wgt);
  FillHist1D("h1_tBABE_Reco", t_BABE, wgt);
  FillHist1D("h1_teX_Reco", t_eX, wgt);
  FillHist1D("h1_teXPT_Reco", t_eXPT, wgt);
  FillHist1D("h1_teXBABE_Reco", t_eXBABE, wgt);
  FillHist1D("h1_W_Reco", W_Rec, wgt);
  FillHist1D("h1_eps_Reco", eps_Rec, wgt);
  FillHist1D("h1_y_Reco", y_Rec, wgt);
  FillHist1D("h1_DeltaTheta_Reco", nTheta_Diff, wgt);
  FillHist1D("h1_DeltaPhi_Reco", nPhi_Diff, wgt);
  FillHist2D("h2_tBABEQ2_Reco", t_BABE, Q2_Rec, wgt);
  FillHist2D("h2_teXQ2_Reco", t_eX, Q2_Rec, wgt);
  FillHist2D("h2_teXPTQ2_Reco", t_eXPT, Q2_Rec, wgt);
  FillHist2D("h2_teXBABEQ2_Reco", t_eXBABE, Q2_Rec, wgt);
  FillHist2D("h2_WQ2_Reco", W_Rec, Q2_Rec, wgt);
  FillHist2D("h2_DeltaThetaPhi_Reco", nTheta_Diff, nPhi_Diff, wgt);

  FillHist1D("h1_Q2_MCDEMPAccept", Q2_MC, wgt);
  FillHist1D("h1_W_MCDEMPAccept", W_MC, wgt);
  FillHist1D("h1_eps_MCDEMPAccept", eps_MC, wgt);
  FillHist1D("h1_y_MCDEMPAccept", y_MC, wgt);
  FillHist1D("h1_t_MCDEMPAccept", t_MC, wgt);
  FillHist2D("h2_WQ2_MCDEMPAccept", W_MC, Q2_MC, wgt);
  FillHist2D("h2_tQ2_MCDEMPAccept", t_MC, Q2_MC, wgt);
  FillHist1D("h1_Q2_MCDEMPAccept_NoAB", Q2_MC_NoAB, wgt);
  FillHist1D("h1_W_MCDEMPAccept_NoAB", W_MC_NoAB, wgt);
  FillHist1D("h1_eps_MCDEMPAccept_NoAB", eps_MC_NoAB, wgt);
  FillHist1D("h1_y_MCDEMPAccept_NoAB", y_MC_NoAB, wgt);	
  FillHist1D("h1_t_MCDEMPAccept_NoAB", t_MC_NoAB, wgt);
  FillHist2D("h2_WQ2_MCDEMPAccept_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
  FillHist2D("h2_tQ2_MCDEMPAccept_NoAB", t_MC_NoAB, Q2_MC_NoAB, wgt);
  if( ZDC == kTRUE && nZDC == kTRUE ){
    FillHist1D("h1_Q2_ZDCReco", Q2_Rec, wgt);
    FillHist1D("h1_tBABE_ZDCReco", t_BABE, wgt);
    FillHist1D("h1_teX_ZDCReco", t_eX, wgt);
    FillHist1D("h1_teXPT_ZDCReco", t_eXPT, wgt);
    FillHist1D("h1_teXBABE_ZDCReco", t_eXBABE, wgt);
    FillHist1D("h1_W_ZDCReco", W_Rec, wgt);
    FillHist1D("h1_eps_ZDCReco", eps_Rec, wgt);
    FillHist1D("h1_y_ZDCReco", y_Rec, wgt);
    FillHist1D("h1_DeltaTheta_ZDCReco", nTheta_Diff, wgt);
    FillHist1D("h1_DeltaPhi_ZDCReco", nPhi_Diff, wgt);
    FillHist2D("h2_tBABEQ2_ZDCReco", t_BABE, Q2_Rec, wgt);
    FillHist2D("h2_teXQ2_ZDCReco", t_eX, Q2_Rec, wgt);
    FillHist2D("h2_teXPTQ2_ZDCReco", t_eXPT, Q2_Rec, wgt);
    FillHist2D("h2_teXBABEQ2_ZDCReco", t_eXBABE, Q2_Rec, wgt);
    FillHist2D("h2_WQ2_ZDCReco", W_Rec, Q2_Rec, wgt);
    FillHist2D("h2_DeltaThetaPhi_ZDCReco", nTheta_Diff, nPhi_Diff, wgt);
    
    FillHist1D("h1_Q2_MCDEMPAcceptZDC", Q2_MC, wgt);
    FillHist1D("h1_W_MCDEMPAcceptZDC", W_MC, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptZDC", eps_MC, wgt);
    FillHist1D("h1_y_MCDEMPAcceptZDC", y_MC, wgt);
    FillHist1D("h1_t_MCDEMPAcceptZDC", t_MC, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptZDC", W_MC, Q2_MC, wgt);
    FillHist2D("h2_tQ2_MCDEMPAcceptZDC", t_MC, Q2_MC, wgt);
    FillHist1D("h1_Q2_MCDEMPAcceptZDC_NoAB", Q2_MC_NoAB, wgt);
    FillHist1D("h1_W_MCDEMPAcceptZDC_NoAB", W_MC_NoAB, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptZDC_NoAB", eps_MC_NoAB, wgt);
    FillHist1D("h1_y_MCDEMPAcceptZDC_NoAB", y_MC_NoAB, wgt);	
    FillHist1D("h1_t_MCDEMPAcceptZDC_NoAB", t_MC_NoAB, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptZDC_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
    FillHist2D("h2_tQ2_MCDEMPAcceptZDC_NoAB", t_MC_NoAB, Q2_MC_NoAB, wgt);
  }
  if( B0 == kTRUE && nB0 == kTRUE ){
    FillHist1D("h1_Q2_B0Reco", Q2_Rec, wgt);
    FillHist1D("h1_tBABE_B0Reco", t_BABE, wgt);
    FillHist1D("h1_teX_B0Reco", t_eX, wgt);
    FillHist1D("h1_teXPT_B0Reco", t_eXPT, wgt);
    FillHist1D("h1_teXBABE_B0Reco", t_eXBABE, wgt);
    FillHist1D("h1_W_B0Reco", W_Rec, wgt);
    FillHist1D("h1_eps_B0Reco", eps_Rec, wgt);
    FillHist1D("h1_y_B0Reco", y_Rec, wgt);
    FillHist1D("h1_DeltaTheta_B0Reco", nTheta_Diff, wgt);
    FillHist1D("h1_DeltaPhi_B0Reco", nPhi_Diff, wgt);
    FillHist2D("h2_tBABEQ2_B0Reco", t_BABE, Q2_Rec, wgt);
    FillHist2D("h2_teXQ2_B0Reco", t_eX, Q2_Rec, wgt);
    FillHist2D("h2_teXPTQ2_B0Reco", t_eXPT, Q2_Rec, wgt);
    FillHist2D("h2_teXBABEQ2_B0Reco", t_eXBABE, Q2_Rec, wgt);
    FillHist2D("h2_WQ2_B0Reco", W_Rec, Q2_Rec, wgt);
    FillHist2D("h2_DeltaThetaPhi_B0Reco", nTheta_Diff, nPhi_Diff, wgt);

    FillHist1D("h1_Q2_MCDEMPAcceptB0", Q2_MC, wgt);
    FillHist1D("h1_W_MCDEMPAcceptB0", W_MC, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptB0", eps_MC, wgt);
    FillHist1D("h1_y_MCDEMPAcceptB0", y_MC, wgt);
    FillHist1D("h1_t_MCDEMPAcceptB0", t_MC, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptB0", W_MC, Q2_MC, wgt);
    FillHist2D("h2_tQ2_MCDEMPAcceptB0", t_MC, Q2_MC, wgt);
    FillHist1D("h1_Q2_MCBDEMPAcceptB0_NoAB", Q2_MC_NoAB, wgt);
    FillHist1D("h1_W_MCDEMPAcceptB0_NoAB", W_MC_NoAB, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptB0_NoAB", eps_MC_NoAB, wgt);
    FillHist1D("h1_y_MCDEMPAcceptB0_NoAB", y_MC_NoAB, wgt);
    FillHist1D("h1_t_MCDEMPAcceptB0_NoAB", t_MC_NoAB, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptB0_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
    FillHist2D("h2_tQ2_MCDEMPAcceptB0_NoAB", t_MC_NoAB, Q2_MC_NoAB, wgt);
  }
}

void FillDEMPAccept_tKin_NoCuts(Bool_t ZDC, Bool_t nZDC, Bool_t B0, Bool_t nB0, float wgt){
  
  // Fill reconstructed t, Theta/phi diff and Emiss distributions for DEMP events before cuts
  FillHist1D("h1_tBABE_Reco_NoCuts", t_BABE, wgt);
  FillHist1D("h1_teX_Reco_NoCuts", t_eX, wgt);
  FillHist1D("h1_teXPT_Reco_NoCuts", t_eXPT, wgt);
  FillHist1D("h1_teXBABE_Reco_NoCuts", t_eXBABE, wgt);
  FillHist1D("h1_DeltaTheta_Reco_NoCuts", nTheta_Diff, wgt);
  FillHist1D("h1_DeltaPhi_Reco_NoCuts", nPhi_Diff, wgt);
  FillHist2D("h2_tBABEQ2_Reco_NoCuts", t_BABE, Q2_Rec, wgt);
  FillHist2D("h2_teXQ2_Reco_NoCuts", t_eX, Q2_Rec, wgt);
  FillHist2D("h2_teXPTQ2_Reco_NoCuts", t_eXPT, Q2_Rec, wgt);
  FillHist2D("h2_teXBABEQ2_Reco_NoCuts", t_eXBABE, Q2_Rec, wgt);
  FillHist2D("h2_WQ2_Reco_NoCuts", W_Rec, Q2_Rec, wgt);
  FillHist2D("h2_DeltaThetaPhi_Reco_NoCuts", nTheta_Diff, nPhi_Diff, wgt);

  // Fill truth t distributions for DEMP events before cuts
  FillHist1D("h1_t_MCDEMPAccept_NoCuts", t_MC, wgt);
  FillHist2D("h2_tQ2_MCDEMPAccept_NoCuts", t_MC, Q2_MC, wgt);
  FillHist1D("h1_t_MCDEMPAccept_NoCuts_NoAB", t_MC_NoAB, wgt);
  FillHist2D("h2_tQ2_MCDEMPAccept_NoCuts_NoAB", t_MC_NoAB, Q2_MC_NoAB, wgt);

  if(ZDC == kTRUE && nZDC == kTRUE){
    FillHist1D("h1_tBABE_ZDCReco_NoCuts", t_BABE, wgt);
    FillHist1D("h1_teX_ZDCReco_NoCuts", t_eX, wgt);
    FillHist1D("h1_teXPT_ZDCReco_NoCuts", t_eXPT, wgt);
    FillHist1D("h1_teXBABE_ZDCReco_NoCuts", t_eXBABE, wgt);
    FillHist1D("h1_DeltaTheta_ZDCReco_NoCuts", nTheta_Diff, wgt);
    FillHist1D("h1_DeltaPhi_ZDCReco_NoCuts", nPhi_Diff, wgt);
    FillHist2D("h2_tBABEQ2_ZDCReco_NoCuts", t_BABE, Q2_Rec, wgt);
    FillHist2D("h2_teXQ2_ZDCReco_NoCuts", t_eX, Q2_Rec, wgt);
    FillHist2D("h2_teXPTQ2_ZDCReco_NoCuts", t_eXPT, Q2_Rec, wgt);
    FillHist2D("h2_teXBABEQ2_ZDCReco_NoCuts", t_eXBABE, Q2_Rec, wgt);
    FillHist2D("h2_WQ2_ZDCReco_NoCuts", W_Rec, Q2_Rec, wgt);
    FillHist2D("h2_DeltaThetaPhi_ZDCReco_NoCuts", nTheta_Diff, nPhi_Diff, wgt);

    FillHist1D("h1_t_MCDEMPAcceptZDC_NoCuts", t_MC, wgt);
    FillHist2D("h2_tQ2_MCDEMPAcceptZDC_NoCuts", t_MC, Q2_MC, wgt);
    FillHist1D("h1_t_MCDEMPAcceptZDC_NoCuts_NoAB", t_MC_NoAB, wgt);
    FillHist2D("h2_tQ2_MCDEMPAcceptZDC_NoCuts_NoAB", t_MC_NoAB, Q2_MC_NoAB, wgt);}
  if(B0 == kTRUE && nB0 == kTRUE){
    FillHist1D("h1_tBABE_B0Reco_NoCuts", t_BABE, wgt);
    FillHist1D("h1_teX_B0Reco_NoCuts", t_eX, wgt);
    FillHist1D("h1_teXPT_B0Reco_NoCuts", t_eXPT, wgt);
    FillHist1D("h1_teXBABE_B0Reco_NoCuts", t_eXBABE, wgt);
    FillHist1D("h1_DeltaTheta_B0Reco_NoCuts", nTheta_Diff, wgt);
    FillHist1D("h1_DeltaPhi_B0Reco_NoCuts", nPhi_Diff, wgt);
    FillHist2D("h2_tBABEQ2_B0Reco_NoCuts", t_BABE, Q2_Rec, wgt);
    FillHist2D("h2_teXQ2_B0Reco_NoCuts", t_eX, Q2_Rec, wgt);
    FillHist2D("h2_teXPTQ2_B0Reco_NoCuts", t_eXPT, Q2_Rec, wgt);
    FillHist2D("h2_teXBABEQ2_B0Reco_NoCuts", t_eXBABE, Q2_Rec, wgt);
    FillHist2D("h2_WQ2_B0Reco_NoCuts", W_Rec, Q2_Rec, wgt);
    FillHist2D("h2_DeltaThetaPhi_B0Reco_NoCuts", nTheta_Diff, nPhi_Diff, wgt);

    FillHist1D("h1_t_MCDEMPAcceptB0_NoCuts", t_MC, wgt);
    FillHist2D("h2_tQ2_MCDEMPAcceptB0_NoCuts", t_MC, Q2_MC, wgt);
    FillHist1D("h1_t_MCDEMPAcceptB0_NoCuts_NoAB", t_MC_NoAB, wgt);
    FillHist2D("h2_tQ2_MCDEMPAcceptB0_NoCuts_NoAB", t_MC_NoAB, Q2_MC_NoAB, wgt);
  }
}

void DEMP_Analysis(TString BeamE = "", TString Date = "", TString BeamConfig = "", TString part = ""){
  
  gROOT->SetBatch(kTRUE);

  if (BeamE == ""){
    cout << "Enter a beam energy combination in the format - XonY - where X is the electron beam energy in GeV and Y is the proton beam energy:" << endl;
    cin >> BeamE;
  }
  if (Date == ""){
    cout << "Enter a date in the format DD_MM_YYYY:" << endl;
    cin >> Date;
  }
  // If date entered as DD/MM/YYYY, switch slashes to _ instead in string automatically
  if (Date.Contains("/")){
    Date.ReplaceAll("/","_");
  }

  if(BeamConfig == ""){
    BeamConfig = "10x100_hiacc";
  }

  if(part == ""){
    part = "Pi+";
  }

  TString InputFiles[3]={ConstructFileName(BeamE, part, "3_10", BeamConfig, Date), ConstructFileName(BeamE, part, "10_20", BeamConfig, Date), ConstructFileName(BeamE, part, "20_35", BeamConfig, Date)};

  if(CheckFiles(InputFiles) == kFALSE){ // Check files exist, can be opened and contain tree with fn
    exit(1);
  }

  TChain *AnalysisChain = new TChain("events");
  for (Int_t i = 0; i <3; i++){
    AnalysisChain->Add(InputFiles[i]);  // Add valid file to the chain
  }
	
  // Initialize reader
  TTreeReader tree_reader(AnalysisChain);
  // Get weight information
  TTreeReaderArray<float> weight(tree_reader, "EventHeader.weight");
  // Get Particle Information
  TTreeReaderArray<int>    PartGenStat(tree_reader, "MCParticles.generatorStatus");
  TTreeReaderArray<float>  PartMomX(tree_reader, "MCParticles.momentum.x");
  TTreeReaderArray<float>  PartMomY(tree_reader, "MCParticles.momentum.y");
  TTreeReaderArray<float>  PartMomZ(tree_reader, "MCParticles.momentum.z");
  TTreeReaderArray<int>    PartPdg(tree_reader, "MCParticles.PDG");
  TTreeReaderArray<double> PartMass(tree_reader,"MCParticles.mass");
  // Get Reconstructed Track Information
  TTreeReaderArray<float> trackMomX(tree_reader,"ReconstructedChargedParticles.momentum.x"); 
  TTreeReaderArray<float> trackMomY(tree_reader,"ReconstructedChargedParticles.momentum.y");
  TTreeReaderArray<float> trackMomZ(tree_reader,"ReconstructedChargedParticles.momentum.z");
  TTreeReaderArray<float> trackE(tree_reader,"ReconstructedChargedParticles.energy");
  TTreeReaderArray<int>   trackPdg(tree_reader,"ReconstructedChargedParticles.PDG");
  TTreeReaderArray<float> trackMass(tree_reader,"ReconstructedChargedParticles.mass");
  TTreeReaderArray<float> trackCharge(tree_reader,"ReconstructedChargedParticles.charge");
  // ZDC Neutrons
  TTreeReaderArray<float> neutE(tree_reader, "ReconstructedFarForwardZDCNeutrals.energy");
  TTreeReaderArray<float> neutMomX(tree_reader, "ReconstructedFarForwardZDCNeutrals.momentum.x");
  TTreeReaderArray<float> neutMomY(tree_reader, "ReconstructedFarForwardZDCNeutrals.momentum.y");
  TTreeReaderArray<float> neutMomZ(tree_reader, "ReconstructedFarForwardZDCNeutrals.momentum.z");
  TTreeReaderArray<float> neutPosX(tree_reader, "ReconstructedFarForwardZDCNeutrals.referencePoint.x");
  TTreeReaderArray<float> neutPosY(tree_reader, "ReconstructedFarForwardZDCNeutrals.referencePoint.y");
  TTreeReaderArray<float> neutPosZ(tree_reader, "ReconstructedFarForwardZDCNeutrals.referencePoint.z");
  TTreeReaderArray<unsigned int> neutClus(tree_reader, "ReconstructedFarForwardZDCNeutrals.clusters_end");
  // Get Before Afterburned information
  TTreeReaderArray<int>    NoABPartGenStat(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.generatorStatus");
  TTreeReaderArray<float>  NoABPartMomX(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.x");
  TTreeReaderArray<float>  NoABPartMomY(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.y");
  TTreeReaderArray<float>  NoABPartMomZ(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.z");
  TTreeReaderArray<int>    NoABPartPdg(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.PDG");
  TTreeReaderArray<double> NoABPartMass(tree_reader,"MCParticlesHeadOnFrameNoBeamFX.mass");
  // B0ECalClusters
  TTreeReaderArray<float> PosX_B0(tree_reader, "B0ECalClusters.position.x");
  TTreeReaderArray<float> PosY_B0(tree_reader, "B0ECalClusters.position.y");
  TTreeReaderArray<float> PosZ_B0(tree_reader, "B0ECalClusters.position.z");
  TTreeReaderArray<float> E_B0(tree_reader, "B0ECalClusters.energy");
  // Get Associations Between MCParticles and Reconstructed(Charged)Particles
  TTreeReaderArray<unsigned int> Rec_Assoc(tree_reader, "ReconstructedParticleAssociations.recID");
  TTreeReaderArray<unsigned int> Sim_Assoc(tree_reader, "ReconstructedParticleAssociations.simID");
  TTreeReaderArray<unsigned int> ChargedRec_Assoc(tree_reader, "ReconstructedChargedParticleAssociations.recID");
  TTreeReaderArray<unsigned int> ChargedSim_Assoc(tree_reader, "ReconstructedChargedParticleAssociations.simID");
  
  TFile *ofile = TFile::Open(Form("%s_%s_OutputHists.root", part.Data(), BeamE.Data()),"RECREATE");

  Double_t ElecE = ((TObjString *)((BeamE.Tokenize("on"))->At(0)))->String().Atof();
  Double_t HadE = ((TObjString *)((BeamE.Tokenize("on"))->At(1)))->String().Atof();
  
  Bool_t EventDistPlots = kTRUE;
  Bool_t KinPlots = kTRUE;
  Bool_t ZDCPlots = kTRUE;
  Bool_t B0Plots = kTRUE;
  Bool_t QAPlots = kTRUE;
  Bool_t ResultsPlots = kTRUE;

  // Set cut values depending upon beam energy combination
  SetCutVals(HadE);
  //Define histograms using BeamE value and series of true false flags
  DefHists(BeamE, EventDistPlots, KinPlots, ZDCPlots, B0Plots, QAPlots, ResultsPlots);
  
  while(tree_reader.Next()) { // Loop over all events
    Good_eSc_Track = kFALSE, Good_Pi_Track = kFALSE, Good_nRec = kFALSE, nZDCHit = kFALSE, nB0Hit = kFALSE;
    // Loop over MC particles, assign e'/pi/n info - Segment into function?
    for (unsigned int i = 0; i < PartGenStat.GetSize(); i++){ 
      PartE = sqrt(pow(PartMomX[i],2) + pow(PartMomY[i],2) + pow(PartMomZ[i],2) + pow(PartMass[i],2)); // Energy of MC Particle
     // Assign beam 4 vectors
      if(PartGenStat[i] == 4 && PartPdg[i] == 11){ Vec_e_beam.SetPxPyPzE(PartMomX[i], PartMomY[i], PartMomZ[i], PartE);}
      if(PartGenStat[i] == 4 && PartPdg[i] == 2212){ Vec_p_beam.SetPxPyPzE(PartMomX[i], PartMomY[i], PartMomZ[i], PartE);}
      // Select stable thrown particles
      if(PartGenStat[i] == 1){
	if(PartPdg[i] == 11){
	  eSc_Index = i;
	  Vec_eSc_MC.SetPxPyPzE(PartMomX[i], PartMomY[i], PartMomZ[i], PartE);
	  FillHist2D("h2_eSc_pTheta_MC", Vec_eSc_MC.Theta()*TMath::RadToDeg(), Vec_eSc_MC.P(), weight[0]);
	}
	else if(PartPdg[i] == 211){
	  pi_Index = i;
	  Vec_Pi_MC.SetPxPyPzE(PartMomX[i], PartMomY[i], PartMomZ[i], PartE);
	  FillHist2D("h2_Pi_pTheta_MC", Vec_Pi_MC.Theta()*TMath::RadToDeg(), Vec_Pi_MC.P(), weight[0]);
	}
	else if(PartPdg[i] == 2112){
	  n_Index = i;
	  Vec_n_MC.SetPxPyPzE(PartMomX[i], PartMomY[i], PartMomZ[i], PartE);
	  FillHist2D("h2_n_pTheta_MC", Vec_n_MC.Theta()*TMath::RadToDeg(), Vec_n_MC.P(), weight[0]);
	}
      }
    } // End of MC particle assignment loop
    CalculateKinematicsMC(Vec_eSc_MC, Vec_Pi_MC, Vec_n_MC, Vec_e_beam, Vec_p_beam);

    // Loop over MC NoABParticles without beam effects, assign e'/pi/n info - Segment into function?
    for (unsigned int i = 0; i < NoABPartGenStat.GetSize(); i++){
	NoABPartE = sqrt(pow(NoABPartMomX[i],2) + pow(NoABPartMomY[i],2) + pow(NoABPartMomZ[i],2) + pow(NoABPartMass[i],2)); // Energy of MC Non Afterbruned particle
	// Assign beam 4 vectors
	if(NoABPartGenStat[i] == 4 && NoABPartPdg[i] == 11){Vec_e_beam_NoAB.SetPxPyPzE(NoABPartMomX[i], NoABPartMomY[i], NoABPartMomZ[i], NoABPartE);}
	if(NoABPartGenStat[i] == 4 && NoABPartPdg[i] == 2212){Vec_p_beam_NoAB.SetPxPyPzE(NoABPartMomX[i], NoABPartMomY[i], NoABPartMomZ[i], NoABPartE);}
	 // Select stable thrown NoABParticles
      if(NoABPartGenStat[i] == 1){
	if(NoABPartPdg[i] == 11){
	  Vec_eSc_MC_NoAB.SetPxPyPzE(NoABPartMomX[i], NoABPartMomY[i], NoABPartMomZ[i], NoABPartE);
	  FillHist2D("h2_eSc_pTheta_MC_NoAB", Vec_eSc_MC_NoAB.Theta()*TMath::RadToDeg(), Vec_eSc_MC_NoAB.P(), weight[0]);
	}
	else if(NoABPartPdg[i] == 211){
	  Vec_Pi_MC_NoAB.SetPxPyPzE(NoABPartMomX[i], NoABPartMomY[i], NoABPartMomZ[i], NoABPartE);
	  FillHist2D("h2_Pi_pTheta_MC_NoAB", Vec_Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Vec_Pi_MC_NoAB.P(), weight[0]);
	}
	else if(NoABPartPdg[i] == 2112){
	  Vec_n_MC_NoAB.SetPxPyPzE(NoABPartMomX[i], NoABPartMomY[i], NoABPartMomZ[i], NoABPartE);
	  FillHist2D("h2_n_pTheta_MC_NoAB", Vec_n_MC_NoAB.Theta()*TMath::RadToDeg(), Vec_n_MC_NoAB.P(), weight[0]);
	}
      }
    } // End of MC NoABParticle (no beam effects) assignment loop
    CalculateKinematicsMCNoAB(Vec_eSc_MC_NoAB, Vec_Pi_MC_NoAB, Vec_n_MC_NoAB, Vec_e_beam_NoAB, Vec_p_beam_NoAB);
    
    // Fill kinematics plots with MC truth info
    if(KinPlots == kTRUE){
      FillMCKin(weight[0]);
    }

    // Loop over reconstructed particles, looking for associations
    for(unsigned int i = 0; i < ChargedSim_Assoc.GetSize(); i++){
      if (ChargedSim_Assoc[i] == eSc_Index){ // If matching track for electron found, assign reconstructed pion 4 vector
	Vec_eSc_Rec.SetPxPyPzE(trackMomX[ChargedRec_Assoc[i]], trackMomY[ChargedRec_Assoc[i]], trackMomZ[ChargedRec_Assoc[i]], trackE[ChargedRec_Assoc[i]]);
	FillHist2D("h2_eSc_pTheta_MCMatched", Vec_eSc_MC.Theta()*TMath::RadToDeg(), Vec_eSc_MC.P(), weight[0]);
	FillHist2D("h2_eSc_pTheta_MCMatched_NoAB", Vec_eSc_MC_NoAB.Theta()*TMath::RadToDeg(), Vec_eSc_MC_NoAB.P(), weight[0]);
	FillHist2D("h2_eSc_pTheta_Reco", Vec_eSc_Rec.Theta()*TMath::RadToDeg(), Vec_eSc_Rec.P(), weight[0]);
	if(trackCharge[ChargedRec_Assoc[i]] < 0 && trackMomZ[ChargedRec_Assoc[i]] < 0){ // Check if track LOOKS like an electron
	  Good_eSc_Track = kTRUE;
	  FillHist2D("h2_eSc_pTheta_MCAccept", Vec_eSc_MC.Theta()*TMath::RadToDeg(), Vec_eSc_MC.P(), weight[0]);
	  FillHist2D("h2_eSc_pTheta_MCAccept_NoAB", Vec_eSc_MC_NoAB.Theta()*TMath::RadToDeg(), Vec_eSc_MC_NoAB.P(), weight[0]);
	  FillHist2D("h2_eSc_pTheta_RecoAccept", Vec_eSc_Rec.Theta()*TMath::RadToDeg(), Vec_eSc_Rec.P(), weight[0]);
	}
      }
      else if(ChargedSim_Assoc[i] == pi_Index){ // If matching track for pion found, assign reconstructed pion 4 vector
	Vec_Pi_Rec.SetPxPyPzE(trackMomX[ChargedRec_Assoc[i]], trackMomY[ChargedRec_Assoc[i]], trackMomZ[ChargedRec_Assoc[i]], trackE[ChargedRec_Assoc[i]]);
	FillHist2D("h2_Pi_pTheta_MCMatched", Vec_Pi_MC.Theta()*TMath::RadToDeg(), Vec_Pi_MC.P(), weight[0]);
	FillHist2D("h2_Pi_pTheta_MCMatched_NoAB", Vec_Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Vec_Pi_MC_NoAB.P(), weight[0]);
	FillHist2D("h2_Pi_pTheta_Reco", Vec_Pi_Rec.Theta()*TMath::RadToDeg(), Vec_Pi_Rec.P(), weight[0]);
	if(trackCharge[ChargedRec_Assoc[i]] > 0 && trackMomZ[ChargedRec_Assoc[i]] > 0){ // Check if track LOOKS like an electron
	  Good_Pi_Track = kTRUE;
	  FillHist2D("h2_Pi_pTheta_MCAccept", Vec_Pi_MC.Theta()*TMath::RadToDeg(), Vec_Pi_MC.P(), weight[0]);
	  FillHist2D("h2_Pi_pTheta_MCAccept_NoAB", Vec_Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Vec_Pi_MC_NoAB.P(), weight[0]);
	  FillHist2D("h2_Pi_pTheta_RecoAccept", Vec_Pi_Rec.Theta()*TMath::RadToDeg(), Vec_Pi_Rec.P(), weight[0]);
	}
      }
    } // End loop over charged particle associations

    // Check ZDC info to find neutrons
    for(unsigned int i=0; i<neutE.GetSize(); i++) { // Loop over zdc neutrons
      Vec_n_Rec.SetPxPyPzE(neutMomX[i],neutMomY[i],neutMomZ[i], neutE[i]);
      Vec_nRot_Rec = rot*Vec_n_Rec; // Rotation wrt proton axis
      Vec_n_Vertex.SetXYZ(neutPosX[i],neutPosY[i],neutPosZ[i]);
      FillHist2D("h2_n_pTheta_Reco", Vec_n_Rec.Theta()*TMath::RadToDeg(), Vec_n_Rec.P(), weight[0]);
      FillHist2D("h2_nRot_pTheta_Reco", Vec_nRot_Rec.Theta()*TMath::RadToDeg(), Vec_nRot_Rec.P(), weight[0]);
      if(ZDCPlots == kTRUE){
	FillHist2D("h2_n_XY_Reco", Vec_n_Vertex.X(), Vec_n_Vertex.Y(), weight[0]);
	FillHist2D("h2_nRot_XY_Reco", 35000*sin(Vec_nRot_Rec.Theta())*cos(Vec_nRot_Rec.Phi()), 35000*sin(Vec_nRot_Rec.Theta())*sin(Vec_nRot_Rec.Phi()), weight[0]);
      }
      if(Vec_nRot_Rec.Theta()*1000 < ThetaStar_Max && Vec_nRot_Rec.E() > n_Emin){
	Good_nRec = kTRUE;
	nZDCHit = kTRUE; 
	FillNeutAccept(Vec_n_Rec, Vec_nRot_Rec, Vec_n_Vertex, Vec_n_MC, Vec_n_MC_NoAB, weight[0], ZDCPlots, KinPlots);
      }
    }// End loop over ZDC info
    
    // Check B0 too - If enabled and ZDC doesn't find anything! Could be improved with combinatorics
    if(B0Plots == kTRUE && Good_nRec == kFALSE && E_B0.GetSize() != 0){ // Explicitly only check B0 if enabled AND no neutron hit in the ZDC
      // Determine the index of the highest energy hit in the B0
      Int_t MaxB0_E_Index = 0;
      // Fill some hits with raw B0 info
      FillHist1D("h1_B0_nClusters", E_B0.GetSize());
      FillHist2D("h2_n_pTheta_MC_B0", Vec_n_MC.Theta()*TMath::RadToDeg(), Vec_n_MC.P(), weight[0]);
      for (Int_t i = 0; i < E_B0.GetSize(); i++){
	FillHist2D("h2_B0_XY_Raw", PosX_B0[i],PosY_B0[i]);
	FillHist2D("h2_B0_XY_Raw_EWeight", PosX_B0[i],PosY_B0[i], E_B0[i]);
	if (E_B0[MaxB0_E_Index] < E_B0[i]){{ 
	    MaxB0_E_Index = i;
	  }
	}
	if( E_B0[MaxB0_E_Index] > B0_ECut){ // If the highest energy value exceeds our energy cut condition, do a rudimentary cluster formation
	  Int_t B0_ClusAccept=0;
	  Double_t ESum_B0 = 0; Double_t tmpB0PosX = 0; Double_t tmpB0PosY = 0; Double_t tmpB0PosZ = 0;
	  // Check all B0 clusters BUT only include those exceeding the energy cut and close to the largest energy hit in the sum
	  for(Int_t i = 0; i < E_B0.GetSize(); i++){
	    if ( E_B0[i] > B0_ECut && abs(PosX_B0[i] - PosX_B0[MaxB0_E_Index]) < B0_XYTol && abs(PosY_B0[i] - PosY_B0[MaxB0_E_Index]) < B0_XYTol){
	      B0_ClusAccept+=1;
	      ESum_B0+=E_B0[i];
	      tmpB0PosX+=(E_B0[i]*PosX_B0[i]); // Energy weighted position values
	      tmpB0PosY+=(E_B0[i]*PosY_B0[i]);
	      tmpB0PosZ+=(E_B0[i]*PosZ_B0[i]);
	    }
	  }
	  Vec_n_Rec.SetPxPyPzE((sqrt((ESum_B0*ESum_B0)+(neutMass*neutMass)))*sin(Vec_n_Vertex.Theta())*cos(Vec_n_Vertex.Phi()), (sqrt((ESum_B0*ESum_B0)+(neutMass*neutMass)))*sin(Vec_n_Vertex.Theta())*sin(Vec_n_Vertex.Phi()),(sqrt((ESum_B0*ESum_B0)+(neutMass*neutMass)))*cos(Vec_n_Vertex.Theta()), ESum_B0);
	  FillHist2D("h2_n_pTheta_Reco", Vec_n_Rec.Theta()*TMath::RadToDeg(), Vec_n_Rec.P(), weight[0]);
	  if(ESum_B0 > 10*B0_ECut){ // Ignore low energy junk events, assign vectors, fill histograms
	    Good_nRec = kTRUE;
	    nB0Hit = kTRUE;
	    Vec_n_Vertex.SetXYZ(tmpB0PosX/ESum_B0, tmpB0PosY/ESum_B0, tmpB0PosZ/ESum_B0);
	    Vec_nRot_Rec = rot*Vec_n_Rec; // Rotation wrt proton axis
	    FillB0Accept(E_B0.GetSize(), B0_ClusAccept, Vec_n_Rec, Vec_nRot_Rec, Vec_n_Vertex, Vec_n_MC, Vec_n_MC_NoAB, ESum_B0, weight[0], KinPlots);
	  }
	}
      }
    } // End loop over B0 info
    // Now, check for coin events, calculate quantities and fill relevant histograms
    if ( Good_eSc_Track == kTRUE && Good_Pi_Track == kTRUE && Good_nRec == kTRUE){
      CalculateBasicKinematics_DEMPRec(Vec_eSc_Rec, Vec_Pi_Rec, Vec_e_beam, Vec_p_beam); // Calculate Q2/W/eps/y for reconstructed DEMP events. Calculate some quantities multiple ways
      
      if(EventDistPlots == kTRUE){
	FillDEMPAccept_EventDists_NoCuts(Vec_eSc_MC, Vec_eSc_MC_NoAB, Vec_eSc_Rec, Vec_Pi_MC, Vec_Pi_MC_NoAB, Vec_Pi_Rec, Vec_n_MC, Vec_n_MC_NoAB, Vec_n_Rec, Vec_nRot_Rec, weight[0], ZDCPlots, B0Plots, nZDCHit, nB0Hit);
      }
      
      if(KinPlots == kTRUE){
	FillDEMPAccept_Kin_NoCuts(ZDCPlots, nZDCHit, B0Plots, nB0Hit, weight[0]);
      }
      
      if (Q2_Rec > 5 && Q2_Rec < 35){ //Cut on reconstructed Q2
	CorrectNeutronTrack(Vec_eSc_Rec, Vec_Pi_Rec, Vec_n_Rec, Vec_e_beam, Vec_p_beam); // Calculate the corrected neutron track, also sets PMiss/PMissRot
	Calculate_t_DEMPRec(Vec_eSc_Rec, Vec_Pi_Rec, Vec_n_Rec, Vec_n_RecCorr, Vec_e_beam, Vec_p_beam); // Calculate -t
	nTheta_Diff = (Vec_PMiss_Rec.Theta() - Vec_n_Rec.Theta())*TMath::RadToDeg();
	nPhi_Diff = (Vec_PMiss_Rec.Phi() - Vec_n_Rec.Phi())*TMath::RadToDeg();
	MMiss = Vec_PMiss_Rec.M();

	if(KinPlots == kTRUE){
	  FillDEMPAccept_tKin_NoCuts(ZDCPlots, nZDCHit, B0Plots, nB0Hit, weight[0]);
	}

	if( t_eXBABE > 0 && t_eXBABE < 1.4 && nTheta_Diff > DeltaTheta_Min && nTheta_Diff < DeltaTheta_Max && nPhi_Diff > DeltaPhi_Min && nPhi_Diff < DeltaPhi_Max){

	  if(EventDistPlots == kTRUE){
	    FillDEMPAccept_EventDists(Vec_eSc_MC, Vec_eSc_MC_NoAB, Vec_eSc_Rec, Vec_Pi_MC, Vec_Pi_MC_NoAB, Vec_Pi_Rec, Vec_n_MC, Vec_n_MC_NoAB, Vec_n_Rec, Vec_nRot_Rec, weight[0], ZDCPlots, B0Plots, nZDCHit, nB0Hit);
	  }
	  
	  // Fill lots of plots and fill histograms
	  if(KinPlots == kTRUE){
	    FillDEMPAccept_Kin(ZDCPlots, nZDCHit, B0Plots, nB0Hit, weight[0]);
	  }
	  
	// Fill result plots binned in Q2
	  if( ResultsPlots == kTRUE) {
	    for(Int_t i = 0; i < 7; i++){
	      if( Q2_Rec > Q2Vals[i] && Q2_Rec < Q2Vals[i+1]){
		// Fill result histograms
	      }
	    } // End loop over Q2 values
	  }// End result filling loop
	} // End main cut loop
      } //end Q2 cut loop
    } // End of loop over DEMP events
  } // End of event while loop

  ofile->Write(); // Write histograms to file
  ofile->Close(); // Close output file

  // Function to draw plots and make pdf
  //WritePDF(BeamE, EventDistPlots, KinPlots, ZDCPlots, B0Plots, TrackingPlots, QAPlots, ResultsPlots);
  // Function to write rates to csv file, enale/disable as needed
  //if ( ResultsPlots == kTRUE){
    //WriteCSV();
    //}
  
}
