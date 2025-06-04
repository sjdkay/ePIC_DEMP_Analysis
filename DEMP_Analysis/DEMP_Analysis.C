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
#include "ePICStyle.C"

void FillEffRaw(PxPyPzEVector eSc_MC, PxPyPzEVector Pi_MC, PxPyPzEVector n_MC, float wgt){
  gDirectory->cd("QADists/Efficiencies");
  FillHist1D("h1_eSc_eta_eff_Raw", eSc_MC.eta(), wgt);
  FillHist1D("h1_Pi_eta_eff_Raw", Pi_MC.eta(), wgt);
  FillHist1D("h1_n_eta_eff_Raw", n_MC.eta(), wgt);
  FillHist1D("h1_eSc_p_eff_Raw", eSc_MC.P(), wgt);
  FillHist1D("h1_Pi_p_eff_Raw", Pi_MC.P(), wgt);
  FillHist1D("h1_n_p_eff_Raw", n_MC.P(), wgt);
  FillHist2D("h2_Q2t_eff_Raw", Q2_MC, t_MC, wgt);
  gDirectory->cd("../../");
}

void FillMCKin(float wgt){
  gDirectory->cd("KinematicDists/MC");
  FillHist1D("h1_Q2_MC", Q2_MC, wgt);
  FillHist1D("h1_t_MC", t_MC, wgt);
  FillHist1D("h1_W_MC", W_MC, wgt);
  FillHist1D("h1_eps_MC", eps_MC, wgt);
  FillHist1D("h1_y_MC", y_MC, wgt);
  FillHist2D("h2_Q2t_MC", Q2_MC, t_MC, wgt);
  FillHist2D("h2_WQ2_MC", W_MC, Q2_MC, wgt);
  FillHist1D("h1_Q2_MC_NoAB", Q2_MC_NoAB, wgt);
  FillHist1D("h1_t_MC_NoAB", t_MC_NoAB, wgt);
  FillHist1D("h1_W_MC_NoAB", W_MC_NoAB, wgt);
  FillHist1D("h1_eps_MC_NoAB", eps_MC_NoAB, wgt);
  FillHist1D("h1_y_MC_NoAB", y_MC_NoAB, wgt);
  FillHist2D("h2_Q2t_MC_NoAB", Q2_MC_NoAB, t_MC_NoAB, wgt);
  FillHist2D("h2_WQ2_MC_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
  gDirectory->cd("../../");
}

void FillNeutAccept(PxPyPzEVector n_Rec, PxPyPzEVector nRot_Rec, XYZVector n_Vertex, PxPyPzEVector n_MC, PxPyPzEVector n_MC_NoAB, float wgt, Bool_t ZDC, Bool_t Kin){
  gDirectory->cd("EventDists/Reco");
  FillHist2D("h2_n_pTheta_RecoAccept", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  FillHist2D("h2_nRot_pTheta_RecoAccept", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
  gDirectory->cd("../../");
  gDirectory->cd("EventDists/MC");
  FillHist2D("h2_n_pTheta_MCAccept", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAccept_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
  gDirectory->cd("../../");
  if(ZDC == kTRUE){
    gDirectory->cd("ZDCDists/MC");
    FillHist2D("h2_n_pTheta_MCAcceptZDC", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
    FillHist2D("h2_n_pTheta_MCAcceptZDC_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
    gDirectory->cd("../../");
    gDirectory->cd("ZDCDists/Reco");
    FillHist2D("h2_n_XY_RecoAccept", n_Vertex.X(), n_Vertex.Y(), wgt);
    FillHist2D("h2_n_pTheta_RecoAcceptZDC", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
    FillHist2D("h2_nRot_pTheta_RecoAcceptZDC", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
    FillHist2D("h2_nRot_XY_RecoAccept", 35000*sin(nRot_Rec.Theta())*cos(nRot_Rec.Phi()), 35000*sin(nRot_Rec.Theta())*sin(nRot_Rec.Phi()), wgt);
    gDirectory->cd("../../");
    if(Kin == kTRUE){
      gDirectory->cd("KinematicDists/MC/ZDC");
      FillHist1D("h1_Q2_MCAcceptZDC", Q2_MC, wgt);
      FillHist1D("h1_t_MCAcceptZDC", t_MC, wgt);
      FillHist1D("h1_W_MCAcceptZDC", W_MC, wgt);
      FillHist1D("h1_eps_MCAcceptZDC", eps_MC, wgt);
      FillHist1D("h1_y_MCAcceptZDC", y_MC, wgt);
      FillHist2D("h2_Q2t_MCAcceptZDC", Q2_MC, t_MC, wgt);
      FillHist2D("h2_WQ2_MCAcceptZDC", W_MC, Q2_MC, wgt);
      FillHist1D("h1_Q2_MCAcceptZDC_NoAB", Q2_MC_NoAB, wgt);
      FillHist1D("h1_t_MCAcceptZDC_NoAB", t_MC_NoAB, wgt);
      FillHist1D("h1_W_MCAcceptZDC_NoAB", W_MC_NoAB, wgt);
      FillHist1D("h1_eps_MCAcceptZDC_NoAB", eps_MC_NoAB, wgt);
      FillHist1D("h1_y_MCAcceptZDC_NoAB", y_MC_NoAB, wgt);
      FillHist2D("h2_Q2t_MCAcceptZDC_NoAB", Q2_MC_NoAB, t_MC_NoAB, wgt);
      FillHist2D("h2_WQ2_MCAcceptZDC_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
      gDirectory->cd("../../../");
    }	    
  }
}

void FillB0Accept(int nClus, int nClusAccept, PxPyPzEVector n_Rec, PxPyPzEVector nRot_Rec, XYZVector n_Vertex, PxPyPzEVector n_MC, PxPyPzEVector n_MC_NoAB, Double_t EB0, float wgt, Bool_t Kin){
  gDirectory->cd("B0Dists/Reco");
  FillHist1D("h1_B0_nClusters_AcceptRaw", nClus);
  FillHist1D("h1_B0_nClusters_Accept", nClusAccept);
  FillHist2D("h2_n_pTheta_RecoAccept", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  FillHist2D("h2_nRot_pTheta_RecoAccept", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
  FillHist2D("h2_n_ETheta_RecoAcceptB0", n_Vertex.Theta()*TMath::RadToDeg(), EB0, wgt);
  FillHist2D("h2_n_pTheta_RecoAcceptB0", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  FillHist2D("h2_nRot_pTheta_RecoAcceptB0", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
  FillHist2D("h2_B0_XY_Accept", n_Vertex.X(), n_Vertex.Y());
  FillHist2D("h2_B0_XY_AcceptWeighted", n_Vertex.X(), n_Vertex.Y(), wgt);
  gDirectory->cd("../../");
  gDirectory->cd("B0Dists/MC");
  FillHist2D("h2_n_pTheta_MCAccept", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAcceptB0", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAccept_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
  FillHist2D("h2_n_pTheta_MCAcceptB0_NoAb", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
  FillHist2D("h2_B0_XY_MCAccept",6800*sin(n_MC.Theta())*cos(n_MC.Phi()), 6800*sin(n_MC.Theta())*sin(n_MC.Phi()), wgt);
  gDirectory->cd("../../");
  if(Kin == kTRUE){
    gDirectory->cd("KinematicDists/MC/B0");
    FillHist1D("h1_Q2_MCAcceptB0", Q2_MC, wgt);
    FillHist1D("h1_t_MCAcceptB0", t_MC, wgt);
    FillHist1D("h1_W_MCAcceptB0", W_MC, wgt);
    FillHist1D("h1_eps_MCAcceptB0", eps_MC, wgt);
    FillHist1D("h1_y_MCAcceptB0", y_MC, wgt);
    FillHist2D("h2_Q2t_MCAcceptB0", Q2_MC, t_MC, wgt);
    FillHist2D("h2_WQ2_MCAcceptB0", W_MC, Q2_MC, wgt);
    FillHist1D("h1_Q2_MCAcceptB0_NoAB", Q2_MC_NoAB, wgt);
    FillHist1D("h1_t_MCAcceptB0_NoAB", t_MC_NoAB, wgt);
    FillHist1D("h1_W_MCAcceptB0_NoAB", W_MC_NoAB, wgt);
    FillHist1D("h1_eps_MCAcceptB0_NoAB", eps_MC_NoAB, wgt);
    FillHist1D("h1_y_MCAcceptB0_NoAB", y_MC_NoAB, wgt);
    FillHist2D("h2_Q2t_MCAcceptB0_NoAB", Q2_MC_NoAB, t_MC_NoAB, wgt);
    FillHist2D("h2_WQ2_MCAcceptB0_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
    gDirectory->cd("../../../");
  }	    
}

void FillEffAccept(PxPyPzEVector eSc_MC, PxPyPzEVector Pi_MC, PxPyPzEVector n_MC, float wgt, Bool_t eSc, Bool_t Pi, Bool_t n, Bool_t nZDC, Bool_t nB0){
  gDirectory->cd("QADists/Efficiencies");
  if(eSc == kTRUE){
    FillHist1D("h1_eSc_eta_eff_Accept", eSc_MC.eta(), wgt);
    FillHist1D("h1_eSc_p_eff_Accept", eSc_MC.P(), wgt);
  }
  if(Pi == kTRUE){  
    FillHist1D("h1_Pi_eta_eff_Accept", Pi_MC.eta(), wgt);
    FillHist1D("h1_Pi_p_eff_Accept", Pi_MC.P(), wgt);
  }
  if(n == kTRUE){
    FillHist1D("h1_n_eta_eff_Accept", n_MC.eta(), wgt);
    FillHist1D("h1_n_p_eff_Accept", n_MC.P(), wgt);
    if( nZDC == kTRUE){
      FillHist1D("h1_n_eta_eff_AcceptZDC", n_MC.eta(), wgt);
      FillHist1D("h1_n_p_eff_AcceptZDC", n_MC.P(), wgt);
    }
    if( nB0 == kTRUE){
      FillHist1D("h1_n_eta_eff_AcceptB0", n_MC.eta(), wgt);
      FillHist1D("h1_n_p_eff_AcceptB0", n_MC.P(), wgt);
    }
  }
  gDirectory->cd("../../");
}

void FillEffDEMPAccept(PxPyPzEVector eSc_MC, PxPyPzEVector Pi_MC, PxPyPzEVector n_MC, float wgt, Bool_t nZDC, Bool_t nB0){
  gDirectory->cd("QADists/Efficiencies");
  FillHist1D("h1_eSc_eta_eff_DEMPAccept", eSc_MC.eta(), wgt);
  FillHist1D("h1_eSc_p_eff_DEMPAccept", eSc_MC.P(), wgt);
  FillHist1D("h1_Pi_eta_eff_DEMPAccept", Pi_MC.eta(), wgt);
  FillHist1D("h1_Pi_p_eff_DEMPAccept", Pi_MC.P(), wgt);
  FillHist1D("h1_n_eta_eff_DEMPAccept", n_MC.eta(), wgt);
  FillHist1D("h1_n_p_eff_DEMPAccept", n_MC.P(), wgt);
  FillHist2D("h2_Q2t_eff_DEMPAccept", Q2_MC, t_MC, wgt);
  if( nZDC == kTRUE){
    FillHist1D("h1_n_eta_eff_DEMPAcceptZDC", n_MC.eta(), wgt);
    FillHist1D("h1_n_p_eff_DEMPAcceptZDC", n_MC.P(), wgt);
    FillHist2D("h2_Q2t_eff_DEMPAcceptZDC", Q2_MC, t_MC, wgt);
  }
  if( nB0 == kTRUE){
    FillHist1D("h1_n_eta_eff_DEMPAcceptB0", n_MC.eta(), wgt);
    FillHist1D("h1_n_p_eff_DEMPAcceptB0", n_MC.P(), wgt);
    FillHist2D("h2_Q2t_eff_DEMPAcceptB0", Q2_MC, t_MC, wgt);
  }
  gDirectory->cd("../../");
}

void FillEffDEMPCut(PxPyPzEVector eSc_MC, PxPyPzEVector Pi_MC, PxPyPzEVector n_MC, float wgt, Bool_t nZDC, Bool_t nB0){
  gDirectory->cd("QADists/Efficiencies");
  FillHist1D("h1_eSc_eta_eff_DEMPCut", eSc_MC.eta(), wgt);
  FillHist1D("h1_eSc_p_eff_DEMPCut", eSc_MC.P(), wgt);
  FillHist1D("h1_Pi_eta_eff_DEMPCut", Pi_MC.eta(), wgt);
  FillHist1D("h1_Pi_p_eff_DEMPCut", Pi_MC.P(), wgt);
  FillHist1D("h1_n_eta_eff_DEMPCut", n_MC.eta(), wgt);
  FillHist1D("h1_n_p_eff_DEMPCut", n_MC.P(), wgt);
  FillHist2D("h2_Q2t_eff_DEMPCut", Q2_MC, t_MC, wgt);
  if( nZDC == kTRUE){
    FillHist1D("h1_n_eta_eff_DEMPCutZDC", n_MC.eta(), wgt);
    FillHist1D("h1_n_p_eff_DEMPCutZDC", n_MC.P(), wgt);
    FillHist2D("h2_Q2t_eff_DEMPCutZDC", Q2_MC, t_MC, wgt);
  }
  if( nB0 == kTRUE){
    FillHist1D("h1_n_eta_eff_DEMPCutB0", n_MC.eta(), wgt);
    FillHist1D("h1_n_p_eff_DEMPCutB0", n_MC.P(), wgt);
    FillHist2D("h2_Q2t_eff_DEMPCutB0", Q2_MC, t_MC, wgt);
  }
  gDirectory->cd("../../");
}

void FillDEMPAccept_EventDists_NoCuts(PxPyPzEVector eSc_MC, PxPyPzEVector eSc_MC_NoAB, PxPyPzEVector eSc_Rec, PxPyPzEVector Pi_MC, PxPyPzEVector Pi_MC_NoAB, PxPyPzEVector Pi_Rec, PxPyPzEVector n_MC, PxPyPzEVector n_MC_NoAB, PxPyPzEVector n_Rec, PxPyPzEVector nRot_Rec, float wgt, Bool_t ZDC, Bool_t B0, Bool_t nZDC, Bool_t nB0){
  gDirectory->cd("EventDists/MC");
  FillHist2D("h2_eSc_pTheta_MCDEMPAccept_NoCuts", eSc_MC.Theta()*TMath::RadToDeg(), eSc_MC.P(), wgt);
  FillHist2D("h2_Pi_pTheta_MCDEMPAccept_NoCuts", Pi_MC.Theta()*TMath::RadToDeg(), Pi_MC.P(), wgt);
  FillHist2D("h2_n_pTheta_MCDEMPAccept_NoCuts", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
  FillHist2D("h2_eSc_pTheta_MCDEMPAccept_NoCuts_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
  FillHist2D("h2_Pi_pTheta_MCDEMPAccept_NoCuts_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
  FillHist2D("h2_n_pTheta_MCDEMPAccept_NoCuts_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);	
  gDirectory->cd("../../");
  gDirectory->cd("EventDists/Reco");
  FillHist2D("h2_eSc_pTheta_RecoDEMPAccept_NoCuts", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
  FillHist2D("h2_Pi_pTheta_RecoDEMPAccept_NoCuts", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
  FillHist2D("h2_n_pTheta_RecoDEMPAccept_NoCuts", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  FillHist2D("h2_nRot_pTheta_RecoDEMPAccept_NoCuts", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
  FillHist2D("h2_n_XY_10m_RecoDEMPAccept_NoCuts", 10000*sin(n_Rec.Theta())*cos(n_Rec.Phi()), 10000*sin(n_Rec.Theta())*sin(n_Rec.Phi()), wgt);
  gDirectory->cd("../../");
  if(ZDC == kTRUE && nZDC == kTRUE){
    gDirectory->cd("ZDCDists/MC");
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptZDC_NoCuts", eSc_MC.Theta()*TMath::RadToDeg(), eSc_MC.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptZDC_NoCuts", Pi_MC.Theta()*TMath::RadToDeg(), Pi_MC.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptZDC_NoCuts", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
    gDirectory->cd("../../");
    gDirectory->cd("ZDCDists/Reco");
    FillHist2D("h2_eSc_pTheta_RecoDEMPAcceptZDC_NoCuts", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
    FillHist2D("h2_Pi_pTheta_RecoDEMPAcceptZDC_NoCuts", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
    FillHist2D("h2_n_pTheta_RecoDEMPAcceptZDC_NoCuts", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
    FillHist2D("h2_n_XY_10m_RecoDEMPAcceptZDC_NoCuts", 10000*sin(n_Rec.Theta())*cos(n_Rec.Phi()), 10000*sin(n_Rec.Theta())*sin(n_Rec.Phi()), wgt);
    gDirectory->cd("../../");
  }
  if(B0 == kTRUE && nB0 == kTRUE){
    gDirectory->cd("B0Dists/MC");
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptB0_NoCuts", eSc_MC.Theta()*TMath::RadToDeg(), eSc_MC.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptB0_NoCuts", Pi_MC.Theta()*TMath::RadToDeg(), Pi_MC.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptB0_NoCuts", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptB0_NoCuts_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptB0_NoCuts_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptB0_NoCuts_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
    gDirectory->cd("../../");
    gDirectory->cd("B0Dists/Reco");
    FillHist2D("h2_eSc_pTheta_RecoDEMPAcceptB0_NoCuts", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
    FillHist2D("h2_Pi_pTheta_RecoDEMPAcceptB0_NoCuts", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
    FillHist2D("h2_n_pTheta_RecoDEMPAcceptB0_NoCuts", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
    FillHist2D("h2_n_XY_10m_RecoDEMPAcceptB0_NoCuts", 10000*sin(n_Rec.Theta())*cos(n_Rec.Phi()), 10000*sin(n_Rec.Theta())*sin(n_Rec.Phi()), wgt);
    gDirectory->cd("../../");
  }
}

void FillDEMPAccept_Kin_NoCuts(Bool_t ZDC, Bool_t nZDC, Bool_t B0, Bool_t nB0, float wgt){

  // Fill reconstructed Q2/W/eps/y plots for DEMP events before cuts
  gDirectory->cd("KinematicDists/Reco");
  FillHist1D("h1_Q2_Reco_NoCuts", Q2_Rec ,wgt);
  FillHist1D("h1_W_Reco_NoCuts", W_Rec, wgt);
  FillHist1D("h1_eps_Reco_NoCuts", eps_Rec, wgt);
  FillHist1D("h1_y_Reco_NoCuts", y_Rec, wgt);
  FillHist2D("h2_WQ2_Reco_NoCuts", W_Rec, Q2_Rec, wgt);
  gDirectory->cd("../../");
  // Fill MC DEMP accepted Q2/W/eps/y plots for DEMP events before cuts
  gDirectory->cd("KinematicDists/MC");
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
  gDirectory->cd("../../");
  
  if(ZDC == kTRUE && nZDC== kTRUE){
    gDirectory->cd("KinematicDists/Reco/ZDC");
    FillHist1D("h1_Q2_ZDCReco_NoCuts", Q2_Rec ,wgt);
    FillHist1D("h1_W_ZDCReco_NoCuts", W_Rec, wgt);
    FillHist1D("h1_eps_ZDCReco_NoCuts", eps_Rec, wgt);
    FillHist1D("h1_y_ZDCReco_NoCuts", y_Rec, wgt);
    FillHist2D("h2_WQ2_ZDCReco_NoCuts", W_Rec, Q2_Rec, wgt);
    gDirectory->cd("../../../");
    gDirectory->cd("KinematicDists/MC/ZDC");
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
    gDirectory->cd("../../../");
  }
  if(B0 == kTRUE && nB0 == kTRUE){
    gDirectory->cd("KinematicDists/Reco/B0");
    FillHist1D("h1_Q2_B0Reco_NoCuts", Q2_Rec ,wgt);
    FillHist1D("h1_W_B0Reco_NoCuts", W_Rec, wgt);
    FillHist1D("h1_eps_B0Reco_NoCuts", eps_Rec, wgt);
    FillHist1D("h1_y_B0Reco_NoCuts", y_Rec, wgt);
    FillHist2D("h2_WQ2_B0Reco_NoCuts", W_Rec, Q2_Rec, wgt);
    gDirectory->cd("../../../");    
    gDirectory->cd("KinematicDists/MC/B0");
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
    gDirectory->cd("../../../");
  }
}

void FillDEMPAccept_EventDists(PxPyPzEVector eSc_MC, PxPyPzEVector eSc_MC_NoAB, PxPyPzEVector eSc_Rec, PxPyPzEVector Pi_MC, PxPyPzEVector Pi_MC_NoAB, PxPyPzEVector Pi_Rec, PxPyPzEVector n_MC, PxPyPzEVector n_MC_NoAB, PxPyPzEVector n_Rec, PxPyPzEVector nRot_Rec, float wgt, Bool_t ZDC, Bool_t B0, Bool_t nZDC, Bool_t nB0){

  gDirectory->cd("EventDists/MC");
  FillHist2D("h2_eSc_pTheta_MCDEMPAccept", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
  FillHist2D("h2_Pi_pTheta_MCDEMPAccept", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
  FillHist2D("h2_n_pTheta_MCDEMPAccept", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
  FillHist2D("h2_eSc_pTheta_MCDEMPAccept_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
  FillHist2D("h2_Pi_pTheta_MCDEMPAccept_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
  FillHist2D("h2_n_pTheta_MCDEMPAccept_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
  gDirectory->cd("../../");
  gDirectory->cd("EventDists/Reco");
  FillHist2D("h2_eSc_pTheta_RecoDEMPAccept", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
  FillHist2D("h2_Pi_pTheta_RecoDEMPAccept", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
  FillHist2D("h2_n_pTheta_RecoDEMPAccept", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
  FillHist2D("h2_nRot_pTheta_RecoDEMPAccept", nRot_Rec.Theta()*TMath::RadToDeg(), nRot_Rec.P(), wgt);
  FillHist2D("h2_n_XY_10m_RecoDEMPAccept", 10000*sin(n_Rec.Theta())*cos(n_Rec.Phi()), 10000*sin(n_Rec.Theta())*sin(n_Rec.Phi()), wgt);
  gDirectory->cd("../../");
  if(ZDC == kTRUE && nZDC == kTRUE){
    gDirectory->cd("ZDCDists/MC");
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptZDC", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptZDC", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptZDC", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptZDC_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptZDC_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptZDC_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
    gDirectory->cd("../../");
    gDirectory->cd("ZDCDists/Reco");    
    FillHist2D("h2_eSc_pTheta_RecoDEMPAcceptZDC", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
    FillHist2D("h2_Pi_pTheta_RecoDEMPAcceptZDC", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
    FillHist2D("h2_n_pTheta_RecoDEMPAcceptZDC", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
    FillHist2D("h2_n_XY_10m_RecoDEMPAcceptZDC", 10000*sin(n_Rec.Theta())*cos(n_Rec.Phi()), 10000*sin(n_Rec.Theta())*sin(n_Rec.Phi()), wgt);
    gDirectory->cd("../../");
  }
  if(B0 == kTRUE && nB0 == kTRUE){
    gDirectory->cd("B0Dists/MC");
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptB0", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptB0", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptB0", n_MC.Theta()*TMath::RadToDeg(), n_MC.P(), wgt);
    FillHist2D("h2_eSc_pTheta_MCDEMPAcceptB0_NoAB", eSc_MC_NoAB.Theta()*TMath::RadToDeg(), eSc_MC_NoAB.P(), wgt);
    FillHist2D("h2_Pi_pTheta_MCDEMPAcceptB0_NoAB", Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Pi_MC_NoAB.P(), wgt);
    FillHist2D("h2_n_pTheta_MCDEMPAcceptB0_NoAB", n_MC_NoAB.Theta()*TMath::RadToDeg(), n_MC_NoAB.P(), wgt);
    gDirectory->cd("../../");
    gDirectory->cd("B0Dists/Reco");    
    FillHist2D("h2_eSc_pTheta_RecoDEMPAcceptB0", eSc_Rec.Theta()*TMath::RadToDeg(), eSc_Rec.P(), wgt);
    FillHist2D("h2_Pi_pTheta_RecoDEMPAcceptB0", Pi_Rec.Theta()*TMath::RadToDeg(), Pi_Rec.P(), wgt);
    FillHist2D("h2_n_pTheta_RecoDEMPAcceptB0", n_Rec.Theta()*TMath::RadToDeg(), n_Rec.P(), wgt);
    FillHist2D("h2_n_XY_10m_RecoDEMPAcceptB0", 10000*sin(n_Rec.Theta())*cos(n_Rec.Phi()), 10000*sin(n_Rec.Theta())*sin(n_Rec.Phi()), wgt);
    gDirectory->cd("../../");
  }  
}

void FillDEMPAccept_Kin(Bool_t ZDC, Bool_t nZDC, Bool_t B0, Bool_t nB0, float wgt){;
  gDirectory->cd("KinematicDists/Reco");
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
  FillHist1D("h1_MissMass", MMiss, wgt);
  FillHist2D("h2_Q2tBABE_Reco", Q2_Rec, t_BABE, wgt);
  FillHist2D("h2_Q2teX_Reco", Q2_Rec, t_eX, wgt);
  FillHist2D("h2_Q2teXPT_Reco", Q2_Rec, t_eXPT, wgt);
  FillHist2D("h2_Q2teXBABE_Reco", Q2_Rec, t_eXBABE, wgt);
  FillHist2D("h2_WQ2_Reco", W_Rec, Q2_Rec, wgt);
  FillHist2D("h2_DeltaThetaPhi_Reco", nTheta_Diff, nPhi_Diff, wgt);
  FillHist2D("h2_DeltaRotThetaRotPhi_Reco", nRotTheta_Diff, nRotPhi_Diff, wgt);
  gDirectory->cd("../../");
  gDirectory->cd("KinematicDists/MC");
  FillHist1D("h1_Q2_MCDEMPAccept", Q2_MC, wgt);
  FillHist1D("h1_W_MCDEMPAccept", W_MC, wgt);
  FillHist1D("h1_eps_MCDEMPAccept", eps_MC, wgt);
  FillHist1D("h1_y_MCDEMPAccept", y_MC, wgt);
  FillHist1D("h1_t_MCDEMPAccept", t_MC, wgt);
  FillHist2D("h2_WQ2_MCDEMPAccept", W_MC, Q2_MC, wgt);
  FillHist2D("h2_Q2t_MCDEMPAccept", Q2_MC, t_MC, wgt);
  FillHist1D("h1_Q2_MCDEMPAccept_NoAB", Q2_MC_NoAB, wgt);
  FillHist1D("h1_W_MCDEMPAccept_NoAB", W_MC_NoAB, wgt);
  FillHist1D("h1_eps_MCDEMPAccept_NoAB", eps_MC_NoAB, wgt);
  FillHist1D("h1_y_MCDEMPAccept_NoAB", y_MC_NoAB, wgt);	
  FillHist1D("h1_t_MCDEMPAccept_NoAB", t_MC_NoAB, wgt);
  FillHist2D("h2_WQ2_MCDEMPAccept_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
  FillHist2D("h2_Q2t_MCDEMPAccept_NoAB", Q2_MC_NoAB, t_MC_NoAB, wgt);
  gDirectory->cd("../../");
  if( ZDC == kTRUE && nZDC == kTRUE ){
    gDirectory->cd("KinematicDists/Reco/ZDC");
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
    FillHist1D("h1_MissMass_ZDCReco", MMiss, wgt);
    FillHist2D("h2_Q2tBABE_ZDCReco",Q2_Rec, t_BABE, wgt);
    FillHist2D("h2_Q2teX_ZDCReco",Q2_Rec, t_eX, wgt);
    FillHist2D("h2_Q2teXPT_ZDCReco", Q2_Rec, t_eXPT, wgt);
    FillHist2D("h2_Q2teXBABE_ZDCReco", Q2_Rec, t_eXBABE, wgt);
    FillHist2D("h2_WQ2_ZDCReco", W_Rec, Q2_Rec, wgt);
    FillHist2D("h2_DeltaThetaPhi_ZDCReco", nTheta_Diff, nPhi_Diff, wgt);
    FillHist2D("h2_DeltaRotThetaRotPhi_ZDCReco", nRotTheta_Diff, nRotPhi_Diff, wgt);
    gDirectory->cd("../../../");
    gDirectory->cd("KinematicDists/MC/ZDC");
    FillHist1D("h1_Q2_MCDEMPAcceptZDC", Q2_MC, wgt);
    FillHist1D("h1_W_MCDEMPAcceptZDC", W_MC, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptZDC", eps_MC, wgt);
    FillHist1D("h1_y_MCDEMPAcceptZDC", y_MC, wgt);
    FillHist1D("h1_t_MCDEMPAcceptZDC", t_MC, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptZDC", W_MC, Q2_MC, wgt);
    FillHist2D("h2_Q2t_MCDEMPAcceptZDC", Q2_MC, t_MC, wgt);
    FillHist1D("h1_Q2_MCDEMPAcceptZDC_NoAB", Q2_MC_NoAB, wgt);
    FillHist1D("h1_W_MCDEMPAcceptZDC_NoAB", W_MC_NoAB, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptZDC_NoAB", eps_MC_NoAB, wgt);
    FillHist1D("h1_y_MCDEMPAcceptZDC_NoAB", y_MC_NoAB, wgt);	
    FillHist1D("h1_t_MCDEMPAcceptZDC_NoAB", t_MC_NoAB, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptZDC_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
    FillHist2D("h2_Q2t_MCDEMPAcceptZDC_NoAB", Q2_MC_NoAB, t_MC_NoAB, wgt);
    gDirectory->cd("../../../");
  }
  if( B0 == kTRUE && nB0 == kTRUE ){
    gDirectory->cd("KinematicDists/Reco/B0");
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
    FillHist1D("h1_MissMass_B0Reco", MMiss, wgt);
    FillHist2D("h2_Q2tBABE_B0Reco",Q2_Rec, t_BABE, wgt);
    FillHist2D("h2_Q2teX_B0Reco",Q2_Rec, t_eX, wgt);
    FillHist2D("h2_Q2teXPT_B0Reco", Q2_Rec, t_eXPT, wgt);
    FillHist2D("h2_Q2teXBABE_B0Reco", Q2_Rec, t_eXBABE, wgt);
    FillHist2D("h2_WQ2_B0Reco", W_Rec, Q2_Rec, wgt);
    FillHist2D("h2_DeltaThetaPhi_B0Reco", nTheta_Diff, nPhi_Diff, wgt);
    FillHist2D("h2_DeltaRotThetaRotPhi_B0Reco", nRotTheta_Diff, nRotPhi_Diff, wgt);
    gDirectory->cd("../../../");
    gDirectory->cd("KinematicDists/MC/B0");
    FillHist1D("h1_Q2_MCDEMPAcceptB0", Q2_MC, wgt);
    FillHist1D("h1_W_MCDEMPAcceptB0", W_MC, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptB0", eps_MC, wgt);
    FillHist1D("h1_y_MCDEMPAcceptB0", y_MC, wgt);
    FillHist1D("h1_t_MCDEMPAcceptB0", t_MC, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptB0", W_MC, Q2_MC, wgt);
    FillHist2D("h2_Q2t_MCDEMPAcceptB0", Q2_MC, t_MC, wgt);
    FillHist1D("h1_Q2_MCDEMPAcceptB0_NoAB", Q2_MC_NoAB, wgt);
    FillHist1D("h1_W_MCDEMPAcceptB0_NoAB", W_MC_NoAB, wgt);
    FillHist1D("h1_eps_MCDEMPAcceptB0_NoAB", eps_MC_NoAB, wgt);
    FillHist1D("h1_y_MCDEMPAcceptB0_NoAB", y_MC_NoAB, wgt);	
    FillHist1D("h1_t_MCDEMPAcceptB0_NoAB", t_MC_NoAB, wgt);
    FillHist2D("h2_WQ2_MCDEMPAcceptB0_NoAB", W_MC_NoAB, Q2_MC_NoAB, wgt);
    FillHist2D("h2_Q2t_MCDEMPAcceptB0_NoAB", Q2_MC_NoAB, t_MC_NoAB, wgt);
    gDirectory->cd("../../../");
  }
}

void FillDEMPAccept_tKin_NoCuts(Bool_t ZDC, Bool_t nZDC, Bool_t B0, Bool_t nB0, float wgt){
  gDirectory->cd("KinematicDists/Reco");
  // Fill reconstructed t, Theta/phi diff and Emiss distributions for DEMP events before cuts
  FillHist1D("h1_tBABE_Reco_NoCuts", t_BABE, wgt);
  FillHist1D("h1_teX_Reco_NoCuts", t_eX, wgt);
  FillHist1D("h1_teXPT_Reco_NoCuts", t_eXPT, wgt);
  FillHist1D("h1_teXBABE_Reco_NoCuts", t_eXBABE, wgt);
  FillHist1D("h1_DeltaTheta_Reco_NoCuts", nTheta_Diff, wgt);
  FillHist1D("h1_DeltaPhi_Reco_NoCuts", nPhi_Diff, wgt);
  FillHist1D("h1_MissMass_NoCuts", MMiss , wgt);
  FillHist2D("h2_Q2tBABE_Reco_NoCuts", Q2_Rec, t_BABE, wgt);
  FillHist2D("h2_Q2teX_Reco_NoCuts", Q2_Rec, t_eX, wgt);
  FillHist2D("h2_Q2teXPT_Reco_NoCuts", Q2_Rec, t_eXPT, wgt);
  FillHist2D("h2_Q2teXBABE_Reco_NoCuts", Q2_Rec, t_eXBABE, wgt);
  FillHist2D("h2_WQ2_Reco_NoCuts", W_Rec, Q2_Rec, wgt);
  FillHist2D("h2_DeltaThetaPhi_Reco_NoCuts", nTheta_Diff, nPhi_Diff, wgt);
  FillHist2D("h2_DeltaRotThetaRotPhi_Reco_NoCuts", nRotTheta_Diff, nRotPhi_Diff, wgt);
  gDirectory->cd("../../");
  gDirectory->cd("KinematicDists/MC");
  // Fill truth t distributions for DEMP events before cuts
  FillHist1D("h1_t_MCDEMPAccept_NoCuts", t_MC, wgt);
  FillHist2D("h2_Q2t_MCDEMPAccept_NoCuts", Q2_MC, t_MC, wgt);
  FillHist1D("h1_t_MCDEMPAccept_NoCuts_NoAB", t_MC_NoAB, wgt);
  FillHist2D("h2_Q2t_MCDEMPAccept_NoCuts_NoAB", Q2_MC_NoAB, t_MC_NoAB, wgt);
  gDirectory->cd("../../");
  if(ZDC == kTRUE && nZDC == kTRUE){
    gDirectory->cd("KinematicDists/Reco/ZDC");
    FillHist1D("h1_tBABE_ZDCReco_NoCuts", t_BABE, wgt);
    FillHist1D("h1_teX_ZDCReco_NoCuts", t_eX, wgt);
    FillHist1D("h1_teXPT_ZDCReco_NoCuts", t_eXPT, wgt);
    FillHist1D("h1_teXBABE_ZDCReco_NoCuts", t_eXBABE, wgt);
    FillHist1D("h1_DeltaTheta_ZDCReco_NoCuts", nTheta_Diff, wgt);
    FillHist1D("h1_DeltaPhi_ZDCReco_NoCuts", nPhi_Diff, wgt);
    FillHist2D("h2_Q2tBABE_ZDCReco_NoCuts", Q2_Rec, t_BABE, wgt);
    FillHist1D("h1_MissMass_ZDCReco_NoCuts", MMiss , wgt);
    FillHist2D("h2_Q2teX_ZDCReco_NoCuts", Q2_Rec, t_eX, wgt);
    FillHist2D("h2_Q2teXPT_ZDCReco_NoCuts", Q2_Rec, t_eXPT, wgt);
    FillHist2D("h2_Q2teXBABE_ZDCReco_NoCuts", Q2_Rec, t_eXBABE, wgt);
    FillHist2D("h2_WQ2_ZDCReco_NoCuts", W_Rec, Q2_Rec, wgt);
    FillHist2D("h2_DeltaThetaPhi_ZDCReco_NoCuts", nTheta_Diff, nPhi_Diff, wgt);
    FillHist2D("h2_DeltaRotThetaRotPhi_ZDCReco_NoCuts", nRotTheta_Diff, nRotPhi_Diff, wgt);
    gDirectory->cd("../../../");
    gDirectory->cd("KinematicDists/MC/ZDC");
    FillHist1D("h1_t_MCDEMPAcceptZDC_NoCuts", t_MC, wgt);
    FillHist2D("h2_Q2t_MCDEMPAcceptZDC_NoCuts", Q2_MC, t_MC, wgt);
    FillHist1D("h1_t_MCDEMPAcceptZDC_NoCuts_NoAB", t_MC_NoAB, wgt);
    FillHist2D("h2_Q2t_MCDEMPAcceptZDC_NoCuts_NoAB", Q2_MC_NoAB, t_MC_NoAB, wgt);}
    gDirectory->cd("../../../");
  if(B0 == kTRUE && nB0 == kTRUE){
    gDirectory->cd("KinematicDists/Reco/B0");
    FillHist1D("h1_tBABE_B0Reco_NoCuts", t_BABE, wgt);
    FillHist1D("h1_teX_B0Reco_NoCuts", t_eX, wgt);
    FillHist1D("h1_teXPT_B0Reco_NoCuts", t_eXPT, wgt);
    FillHist1D("h1_teXBABE_B0Reco_NoCuts", t_eXBABE, wgt);
    FillHist1D("h1_DeltaTheta_B0Reco_NoCuts", nTheta_Diff, wgt);
    FillHist1D("h1_DeltaPhi_B0Reco_NoCuts", nPhi_Diff, wgt);
    FillHist1D("h1_MissMass_B0Reco_NoCuts", MMiss , wgt);
    FillHist2D("h2_Q2tBABE_B0Reco_NoCuts", Q2_Rec, t_BABE, wgt);
    FillHist2D("h2_Q2teX_B0Reco_NoCuts", Q2_Rec, t_eX, wgt);
    FillHist2D("h2_Q2teXPT_B0Reco_NoCuts", Q2_Rec, t_eXPT, wgt);
    FillHist2D("h2_Q2teXBABE_B0Reco_NoCuts", Q2_Rec, t_eXBABE, wgt);
    FillHist2D("h2_WQ2_B0Reco_NoCuts", W_Rec, Q2_Rec, wgt);
    FillHist2D("h2_DeltaThetaPhi_B0Reco_NoCuts", nTheta_Diff, nPhi_Diff, wgt);
    FillHist2D("h2_DeltaRotThetaRotPhi_B0Reco_NoCuts", nRotTheta_Diff, nRotPhi_Diff, wgt);
    gDirectory->cd("../../../");
    gDirectory->cd("KinematicDists/MC/B0");
    FillHist1D("h1_t_MCDEMPAcceptB0_NoCuts", t_MC, wgt);
    FillHist2D("h2_Q2t_MCDEMPAcceptB0_NoCuts", Q2_MC, t_MC, wgt);
    FillHist1D("h1_t_MCDEMPAcceptB0_NoCuts_NoAB", t_MC_NoAB, wgt);
    FillHist2D("h2_Q2t_MCDEMPAcceptB0_NoCuts_NoAB", Q2_MC_NoAB, t_MC_NoAB, wgt);
    gDirectory->cd("../../../");
  }
}

void FillDEMP_Results(Bool_t ZDC, Bool_t nZDC, Bool_t B0, Bool_t nB0, float wgt){
  gDirectory->cd("ResultsDists");
  FillHist1D("h1_tResult_0", t_eXBABE, wgt);
  FillHist1D("h1_Q2Result_0", Q2_Rec, wgt);
  FillHist1D("h1_WResult_0", W_Rec, wgt);
  if ( nZDC == kTRUE && ZDC == kTRUE){
    FillHist1D("h1_tResult_ZDC_0", t_eXBABE, wgt);
    FillHist1D("h1_Q2Result_ZDC_0", Q2_Rec, wgt);
    FillHist1D("h1_WResult_ZDC_0", W_Rec, wgt);
  }
  if ( nB0 == kTRUE && B0 == kTRUE){
    FillHist1D("h1_tResult_B0_0", t_eXBABE, wgt);
    FillHist1D("h1_Q2Result_B0_0", Q2_Rec, wgt);
    FillHist1D("h1_WResult_B0_0", W_Rec, wgt);
  }
  
  for(Int_t i = 0; i < 30; i++){
  //for(Int_t i = 0; i < 7; i++){
    if( Q2_Rec > Q2Vals[i] && Q2_Rec < Q2Vals[i+1]){
      FillHist1D(Form("h1_tResult_%i", i+1), t_eXBABE, wgt);
      FillHist1D(Form("h1_Q2Result_%i", i+1), Q2_Rec, wgt);
      FillHist1D(Form("h1_WResult_%i", i+1), W_Rec, wgt);
      if ( nZDC == kTRUE && ZDC == kTRUE){
	FillHist1D(Form("h1_tResult_ZDC_%i", i+1), t_eXBABE, wgt);
	FillHist1D(Form("h1_Q2Result_ZDC_%i", i+1), Q2_Rec, wgt);
	FillHist1D(Form("h1_WResult_ZDC_%i", i+1), W_Rec, wgt);
      }
      if ( nB0 == kTRUE && B0 == kTRUE){
	FillHist1D(Form("h1_tResult_B0_%i", i+1), t_eXBABE, wgt);
	FillHist1D(Form("h1_Q2Result_B0_%i", i+1), Q2_Rec, wgt);
	FillHist1D(Form("h1_WResult_B0_%i", i+1), W_Rec, wgt);
      }
    }
  }
  gDirectory->cd("../");
}

void FillDEMP_QAKin(Bool_t ZDC, Bool_t nZDC, Bool_t B0, Bool_t nB0, float wgt){
  gDirectory->cd("QADists/Kin");
  FillHist1D("h1_tBABE_Res_QA", ((t_BABE - t_MC)/t_MC)*100, wgt);
  FillHist1D("h1_teX_Res_QA", ((t_eX - t_MC)/t_MC)*100, wgt);
  FillHist1D("h1_teXPT_Res_QA", ((t_eXPT - t_MC)/t_MC)*100, wgt);
  FillHist1D("h1_teXBABE_Res_QA", ((t_eXBABE - t_MC)/t_MC)*100, wgt);
  FillHist1D("h1_Q2_Res_QA", ((Q2_Rec - Q2_MC)/Q2_MC)*100, wgt);
  FillHist1D("h1_W_Res_QA", ((W_Rec - W_MC)/W_MC)*100, wgt);
  if ( nZDC == kTRUE && ZDC == kTRUE){
    FillHist1D("h1_tBABE_Res_QA_ZDC", ((t_BABE - t_MC)/t_MC)*100, wgt);
    FillHist1D("h1_teX_Res_QA_ZDC", ((t_eX - t_MC)/t_MC)*100, wgt);
    FillHist1D("h1_teXPT_Res_QA_ZDC", ((t_eXPT - t_MC)/t_MC)*100, wgt);
    FillHist1D("h1_teXBABE_Res_QA_ZDC", ((t_eXBABE - t_MC)/t_MC)*100, wgt);
    FillHist1D("h1_Q2_Res_QA_ZDC", ((Q2_Rec - Q2_MC)/Q2_MC)*100, wgt);
    FillHist1D("h1_W_Res_QA_ZDC", ((W_Rec - W_MC)/W_MC)*100, wgt);
  }
  if ( nB0 == kTRUE && B0 == kTRUE){
    FillHist1D("h1_tBABE_Res_QA_B0", ((t_BABE - t_MC)/t_MC)*100, wgt);
    FillHist1D("h1_teX_Res_QA_B0", ((t_eX - t_MC)/t_MC)*100, wgt);
    FillHist1D("h1_teXPT_Res_QA_B0", ((t_eXPT - t_MC)/t_MC)*100, wgt);
    FillHist1D("h1_teXBABE_Res_QA_B0", ((t_eXBABE - t_MC)/t_MC)*100, wgt);
    FillHist1D("h1_Q2_Res_QA_B0", ((Q2_Rec - Q2_MC)/Q2_MC)*100, wgt);
    FillHist1D("h1_W_Res_QA_B0", ((W_Rec - W_MC)/W_MC)*100, wgt);
  }
  gDirectory->cd("../../");
  gDirectory->cd("QADists/tComp");
  FillHist2D("h2_tBABEComp", t_BABE, t_MC, wgt);
  FillHist2D("h2_teXComp", t_eX, t_MC, wgt);
  FillHist2D("h2_teXPTComp", t_eXPT, t_MC, wgt);
  FillHist2D("h2_teXBABEComp", t_eXBABE, t_MC, wgt);
  FillHist2D("h2_teXBABECompAlt", t_eXBABE, t_MC, wgt);
  if ( nZDC == kTRUE && ZDC == kTRUE){
    FillHist2D("h2_tBABEComp_ZDC", t_BABE, t_MC, wgt);
    FillHist2D("h2_teXComp_ZDC", t_eX, t_MC, wgt);
    FillHist2D("h2_teXPTComp_ZDC", t_eXPT, t_MC, wgt);
    FillHist2D("h2_teXBABEComp_ZDC", t_eXBABE, t_MC, wgt);
    FillHist2D("h2_teXBABECompAlt_ZDC", t_eXBABE, t_MC, wgt);
  }
  if ( nB0 == kTRUE && B0 == kTRUE){
    FillHist2D("h2_tBABEComp_B0", t_BABE, t_MC, wgt);
    FillHist2D("h2_teXComp_B0", t_eX, t_MC, wgt);
    FillHist2D("h2_teXPTComp_B0", t_eXPT, t_MC, wgt);
    FillHist2D("h2_teXBABEComp_B0", t_eXBABE, t_MC, wgt);
    FillHist2D("h2_teXBABECompAlt_B0", t_eXBABE, t_MC, wgt);
  }
  gDirectory->cd("../../");
}

void FillDEMP_Q2Alt(float wgt){
  gDirectory->cd("QADists/Q2_Alt");
  FillHist1D("h1_QA_Q2Rec",Q2_Rec, wgt);
  FillHist1D("h1_QA_Q2JB",Q2_JB, wgt);
  FillHist1D("h1_QA_Q2DA",Q2_DA, wgt);
  FillHist1D("h1_QA_Q2Sig",Q2_Sig, wgt);
  FillHist1D("h1_QA_yRec",y_Rec, wgt);
  FillHist1D("h1_QA_yJB",y_JB, wgt);
  FillHist1D("h1_QA_yDA",y_DA, wgt);
  FillHist1D("h1_QA_ySig",y_Sig, wgt);
  FillHist1D("h1_QA_xRec",x_Rec, wgt);
  FillHist1D("h1_QA_xJB",x_JB, wgt);
  FillHist1D("h1_QA_xDA",x_DA, wgt);
  FillHist1D("h1_QA_xSig",x_Sig, wgt);
  FillHist1D("h1_QA_Q2Rec_Res",(Q2_Rec-Q2_MC)/Q2_MC*100, wgt);
  FillHist1D("h1_QA_Q2JB_Res",(Q2_JB-Q2_MC)/Q2_MC*100, wgt);
  FillHist1D("h1_QA_Q2DA_Res",(Q2_DA-Q2_MC)/Q2_MC*100, wgt);
  FillHist1D("h1_QA_Q2Sig_Res",(Q2_Sig-Q2_MC)/Q2_MC*100, wgt);
  FillHist1D("h1_QA_yRec_Res",(y_Rec-y_MC)/y_MC*100, wgt);
  FillHist1D("h1_QA_yJB_Res",(y_JB-y_MC)/y_MC*100, wgt);
  FillHist1D("h1_QA_yDA_Res",(y_DA-y_MC)/y_MC*100, wgt);
  FillHist1D("h1_QA_ySig_Res",(y_Sig-y_MC)/y_MC*100, wgt);
  // Fill some 2D plots for the variables that look "best"
  FillHist2D("h2_QA_Q2Rec_Q2MC", Q2_Rec, Q2_MC, wgt);
  FillHist2D("h2_QA_Q2DA_Q2MC", Q2_DA, Q2_MC, wgt);
  FillHist2D("h2_QA_Q2Sig_Q2MC", Q2_Sig, Q2_MC, wgt);
  FillHist2D("h2_QA_Q2Rec_Q2Res", Q2_Rec, (Q2_Rec-Q2_MC)/Q2_MC*100, wgt);
  FillHist2D("h2_QA_Q2DA_Q2Res", Q2_DA, (Q2_DA-Q2_MC)/Q2_MC*100, wgt);
  FillHist2D("h2_QA_Q2Sig_Q2Res", Q2_Sig, (Q2_Sig-Q2_MC)/Q2_MC*100, wgt);
  FillHist2D("h2_QA_yRec_yMC", y_Rec, y_MC, wgt);
  FillHist2D("h2_QA_yDA_yMC", y_DA, y_MC, wgt);
  FillHist2D("h2_QA_ySig_yMC", y_Sig, y_MC, wgt);
  FillHist2D("h2_QA_xRec_xMC", x_Rec, x_MC, wgt);
  FillHist2D("h2_QA_xDA_xMC", x_DA, x_MC, wgt);
  FillHist2D("h2_QA_xSig_xMC", x_Sig, x_MC, wgt);
  gDirectory->cd("../../");
}

void FillDEMP_QAPartRes(PxPyPzEVector eSc_MC, PxPyPzEVector eSc_Rec, PxPyPzEVector Pi_MC, PxPyPzEVector Pi_Rec, PxPyPzEVector n_MC, PxPyPzEVector n_Rec, Bool_t ZDC, Bool_t nZDC, Bool_t B0, Bool_t nB0, float wgt){
  gDirectory->cd("QADists/PartRes");
  FillHist1D("h1_eSc_p_Res_QA", ((eSc_Rec.P()-eSc_MC.P())/eSc_MC.P())*100, wgt);
  FillHist1D("h1_Pi_p_Res_QA", ((Pi_Rec.P()-Pi_MC.P())/Pi_MC.P())*100, wgt);
  FillHist1D("h1_n_p_Res_QA", ((n_Rec.P()-n_MC.P())/n_MC.P())*100, wgt);
  FillHist1D("h1_n_Theta_Res_QA", ((n_Rec.Theta()-n_MC.Theta())/n_MC.Theta())*100, wgt);
  FillHist1D("h1_n_Phi_Res_QA", ((n_Rec.Phi()-n_MC.Phi())/n_MC.Phi())*100, wgt);
  if ( nZDC == kTRUE && ZDC == kTRUE){
    FillHist1D("h1_eSc_p_Res_QA_ZDC", ((eSc_Rec.P()-eSc_MC.P())/eSc_MC.P())*100, wgt);
    FillHist1D("h1_Pi_p_Res_QA_ZDC", ((Pi_Rec.P()-Pi_MC.P())/Pi_MC.P())*100, wgt);
    FillHist1D("h1_n_p_Res_QA_ZDC", ((n_Rec.P()-n_MC.P())/n_MC.P())*100, wgt);
    FillHist1D("h1_n_Theta_Res_QA_ZDC", ((n_Rec.Theta()-n_MC.Theta())/n_MC.Theta())*100, wgt);
FillHist1D("h1_n_Phi_Res_QA_ZDC", ((n_Rec.Phi()-n_MC.Phi())/n_MC.Phi())*100, wgt);
  }
  if ( nB0 == kTRUE && B0 == kTRUE){
    FillHist1D("h1_eSc_p_Res_QA_B0", ((eSc_Rec.P()-eSc_MC.P())/eSc_MC.P())*100, wgt);
    FillHist1D("h1_Pi_p_Res_QA_B0", ((Pi_Rec.P()-Pi_MC.P())/Pi_MC.P())*100, wgt);
    FillHist1D("h1_n_p_Res_QA_B0", ((n_Rec.P()-n_MC.P())/n_MC.P())*100, wgt);
    FillHist1D("h1_n_Theta_Res_QA_B0", ((n_Rec.Theta()-n_MC.Theta())/n_MC.Theta())*100, wgt);
    FillHist1D("h1_n_Phi_Res_QA_B0", ((n_Rec.Phi()-n_MC.Phi())/n_MC.Phi())*100, wgt);
  }
  gDirectory->cd("../../");
}

void CalcEff(Bool_t ZDC, Bool_t B0){
  gDirectory->cd("QADists/Efficiencies");
  DivideHists1D("h1_eSc_eta_eff", "h1_eSc_eta_eff_Accept", "h1_eSc_eta_eff_Raw");
  DivideHists1D("h1_eSc_eta_effDEMP", "h1_eSc_eta_eff_DEMPAccept", "h1_eSc_eta_eff_Raw");
  DivideHists1D("h1_eSc_eta_effDEMPCut", "h1_eSc_eta_eff_DEMPCut", "h1_eSc_eta_eff_Raw");
  DivideHists1D("h1_eSc_p_eff", "h1_eSc_p_eff_Accept", "h1_eSc_p_eff_Raw");
  DivideHists1D("h1_eSc_p_effDEMP", "h1_eSc_p_eff_DEMPAccept", "h1_eSc_p_eff_Raw");
  DivideHists1D("h1_eSc_p_effDEMPCut", "h1_eSc_p_eff_DEMPCut", "h1_eSc_p_eff_Raw");
  DivideHists1D("h1_Pi_eta_eff", "h1_Pi_eta_eff_Accept", "h1_Pi_eta_eff_Raw");
  DivideHists1D("h1_Pi_eta_effDEMP", "h1_Pi_eta_eff_DEMPAccept", "h1_Pi_eta_eff_Raw");
  DivideHists1D("h1_Pi_eta_effDEMPCut", "h1_Pi_eta_eff_DEMPCut", "h1_Pi_eta_eff_Raw");
  DivideHists1D("h1_Pi_p_eff", "h1_Pi_p_eff_Accept", "h1_Pi_p_eff_Raw");
  DivideHists1D("h1_Pi_p_effDEMP", "h1_Pi_p_eff_DEMPAccept", "h1_Pi_p_eff_Raw");
  DivideHists1D("h1_Pi_p_effDEMPCut", "h1_Pi_p_eff_DEMPCut", "h1_Pi_p_eff_Raw");
  DivideHists1D("h1_n_eta_eff", "h1_n_eta_eff_Accept", "h1_n_eta_eff_Raw");
  DivideHists1D("h1_n_eta_effDEMP", "h1_n_eta_eff_DEMPAccept", "h1_n_eta_eff_Raw");
  DivideHists1D("h1_n_eta_effDEMPCut", "h1_n_eta_eff_DEMPCut", "h1_n_eta_eff_Raw");
  DivideHists1D("h1_n_p_eff", "h1_n_p_eff_Accept", "h1_n_p_eff_Raw");
  DivideHists1D("h1_n_p_effDEMP", "h1_n_p_eff_DEMPAccept", "h1_n_p_eff_Raw");
  DivideHists1D("h1_n_p_effDEMPCut", "h1_n_p_eff_DEMPCut", "h1_n_p_eff_Raw");
  DivideHists2D("h2_Q2t_effDEMP", "h2_Q2t_eff_DEMPAccept", "h2_Q2t_eff_Raw");
  DivideHists2D("h2_Q2t_effDEMPCut", "h2_Q2t_eff_DEMPCut", "h2_Q2t_eff_Raw");
  if( ZDC == kTRUE){
    DivideHists1D("h1_n_eta_eff_ZDC", "h1_n_eta_eff_AcceptZDC", "h1_n_eta_eff_Raw");
    DivideHists1D("h1_n_eta_effDEMP_ZDC", "h1_n_eta_eff_DEMPAcceptZDC", "h1_n_eta_eff_Raw");
    DivideHists1D("h1_n_eta_effDEMPCut_ZDC", "h1_n_eta_eff_DEMPCutZDC", "h1_n_eta_eff_Raw");
    DivideHists1D("h1_n_p_eff_ZDC", "h1_n_p_eff_AcceptZDC", "h1_n_p_eff_Raw");
    DivideHists1D("h1_n_p_effDEMP_ZDC", "h1_n_p_eff_DEMPAcceptZDC", "h1_n_p_eff_Raw");
    DivideHists1D("h1_n_p_effDEMPCut_ZDC", "h1_n_p_eff_DEMPCutZDC", "h1_n_p_eff_Raw");
    DivideHists2D("h2_Q2t_effDEMP_ZDC", "h2_Q2t_eff_DEMPAcceptZDC", "h2_Q2t_eff_Raw");
    DivideHists2D("h2_Q2t_effDEMPCut_ZDC", "h2_Q2t_eff_DEMPCutZDC", "h2_Q2t_eff_Raw");
  }
  if( B0 == kTRUE){
    DivideHists1D("h1_n_eta_eff_B0", "h1_n_eta_eff_AcceptB0", "h1_n_eta_eff_Raw");
    DivideHists1D("h1_n_eta_effDEMP_B0", "h1_n_eta_eff_DEMPAcceptB0", "h1_n_eta_eff_Raw");
    DivideHists1D("h1_n_eta_effDEMPCut_B0", "h1_n_eta_eff_DEMPCutB0", "h1_n_eta_eff_Raw");
    DivideHists1D("h1_n_p_eff_B0", "h1_n_p_eff_AcceptB0", "h1_n_p_eff_Raw");
    DivideHists1D("h1_n_p_effDEMP_B0", "h1_n_p_eff_DEMPAcceptB0", "h1_n_p_eff_Raw");
    DivideHists1D("h1_n_p_effDEMPCut_B0", "h1_n_p_eff_DEMPCutB0", "h1_n_p_eff_Raw");
    DivideHists2D("h2_Q2t_effDEMP_B0", "h2_Q2t_eff_DEMPAcceptB0", "h2_Q2t_eff_Raw");
    DivideHists2D("h2_Q2t_effDEMPCut_B0", "h2_Q2t_eff_DEMPCutB0", "h2_Q2t_eff_Raw");
  }
  gDirectory->cd("../../");
}

void DEMP_Analysis(TString BeamE = "", TString Date = "", TString BeamConfig = "", TString part = ""){
  
  gROOT->SetBatch(kTRUE);
  gROOT->ProcessLine("SetePICStyle()");
  gStyle->SetOptStat(0);
  
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

  // Note, from April 2025 onwards, MCParticles and EventHeader are no longer floats, they are doubles, change if needed
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
  // Get Before Afterburned information
  TTreeReaderArray<int>    NoABPartGenStat(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.generatorStatus");
  TTreeReaderArray<float>  NoABPartMomX(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.x");
  TTreeReaderArray<float>  NoABPartMomY(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.y");
  TTreeReaderArray<float>  NoABPartMomZ(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.z");
  TTreeReaderArray<int>    NoABPartPdg(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.PDG");
  TTreeReaderArray<double> NoABPartMass(tree_reader,"MCParticlesHeadOnFrameNoBeamFX.mass");
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

  auto OutDir = Form("%s_%s_%s_%s_Results", part.Data(), BeamE.Data(), Date.Data(), BeamConfig.Data());
  if(gSystem->AccessPathName(OutDir) == kTRUE){
    gSystem->mkdir(OutDir);
  }
  
  TFile *ofile = TFile::Open(Form("%s/%s_%s_%s_%s_OutputHists.root", OutDir, part.Data(), BeamE.Data(), BeamConfig.Data(), Date.Data()),"RECREATE");
  
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
  // Set directories in file ahead of defining histograms
  SetDirectories(EventDistPlots, KinPlots, ZDCPlots, B0Plots, QAPlots, ResultsPlots);
  //Define histograms using BeamE value and series of true false flags
  DefHists(BeamE, EventDistPlots, KinPlots, ZDCPlots, B0Plots, QAPlots, ResultsPlots);

  //Int_t EscapeEvent = 1000;
  while(tree_reader.Next()) { // Loop over all events
    EventCounter++;
    if ( EventCounter % ( nEntries / 10 ) == 0 ) {
      cout << "Processed " << setw(4) << ceil(((1.0*EventCounter)/(1.0*nEntries))*100.0) << " % of events" << endl;	  
    }
    // if (EventCounter > EscapeEvent){
    //   continue;
    // }
    Good_eSc_Track = kFALSE, Good_Pi_Track = kFALSE, Good_nRec = kFALSE, nZDCHit = kFALSE, nB0Hit = kFALSE, DEMP_PassCuts = kFALSE;
    gDirectory->cd("EventDists/MC");
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
    gDirectory->cd("../../");
    if(QAPlots == kTRUE){
      FillEffRaw(Vec_eSc_MC, Vec_Pi_MC, Vec_n_MC, weight[0]);
    }
    gDirectory->cd("EventDists/MC");
    
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
    gDirectory->cd("../../");
    // Fill kinematics plots with MC truth info
    if(KinPlots == kTRUE){
      FillMCKin(weight[0]);
    }
    // Loop over reconstructed particles, looking for associations
    for(unsigned int i = 0; i < ChargedSim_Assoc.GetSize(); i++){
      if (ChargedSim_Assoc[i] == eSc_Index){ // If matching track for electron found, assign reconstructed pion 4 vector
	Vec_eSc_Rec.SetPxPyPzE(trackMomX[ChargedRec_Assoc[i]], trackMomY[ChargedRec_Assoc[i]], trackMomZ[ChargedRec_Assoc[i]], trackE[ChargedRec_Assoc[i]]);
	gDirectory->cd("EventDists/MC");	    
	FillHist2D("h2_eSc_pTheta_MCMatched", Vec_eSc_MC.Theta()*TMath::RadToDeg(), Vec_eSc_MC.P(), weight[0]);
	FillHist2D("h2_eSc_pTheta_MCMatched_NoAB", Vec_eSc_MC_NoAB.Theta()*TMath::RadToDeg(), Vec_eSc_MC_NoAB.P(), weight[0]);
	gDirectory->cd("../../");
	gDirectory->cd("EventDists/Reco");
	FillHist2D("h2_eSc_pTheta_Reco", Vec_eSc_Rec.Theta()*TMath::RadToDeg(), Vec_eSc_Rec.P(), weight[0]);
	gDirectory->cd("../../");
	if(trackCharge[ChargedRec_Assoc[i]] < 0 && trackMomZ[ChargedRec_Assoc[i]] < 0){ // Check if track LOOKS like an electron
	  Good_eSc_Track = kTRUE;
	  gDirectory->cd("EventDists/MC");	
	  FillHist2D("h2_eSc_pTheta_MCAccept", Vec_eSc_MC.Theta()*TMath::RadToDeg(), Vec_eSc_MC.P(), weight[0]);
	  FillHist2D("h2_eSc_pTheta_MCAccept_NoAB", Vec_eSc_MC_NoAB.Theta()*TMath::RadToDeg(), Vec_eSc_MC_NoAB.P(), weight[0]);
	  gDirectory->cd("../../");
	  gDirectory->cd("EventDists/Reco");
	  FillHist2D("h2_eSc_pTheta_RecoAccept", Vec_eSc_Rec.Theta()*TMath::RadToDeg(), Vec_eSc_Rec.P(), weight[0]);
	  gDirectory->cd("../../");
	}
      }
      else if(ChargedSim_Assoc[i] == pi_Index){ // If matching track for pion found, assign reconstructed pion 4 vector
	Vec_Pi_Rec.SetPxPyPzE(trackMomX[ChargedRec_Assoc[i]], trackMomY[ChargedRec_Assoc[i]], trackMomZ[ChargedRec_Assoc[i]], trackE[ChargedRec_Assoc[i]]);
	gDirectory->cd("EventDists/MC");
	FillHist2D("h2_Pi_pTheta_MCMatched", Vec_Pi_MC.Theta()*TMath::RadToDeg(), Vec_Pi_MC.P(), weight[0]);
	FillHist2D("h2_Pi_pTheta_MCMatched_NoAB", Vec_Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Vec_Pi_MC_NoAB.P(), weight[0]);
	gDirectory->cd("../../");
	gDirectory->cd("EventDists/Reco");
	FillHist2D("h2_Pi_pTheta_Reco", Vec_Pi_Rec.Theta()*TMath::RadToDeg(), Vec_Pi_Rec.P(), weight[0]);
	gDirectory->cd("../../");	
	if(trackCharge[ChargedRec_Assoc[i]] > 0 && trackMomZ[ChargedRec_Assoc[i]] > 0){ // Check if track LOOKS like an electron
	  Good_Pi_Track = kTRUE;
	  gDirectory->cd("EventDists/MC");
	  FillHist2D("h2_Pi_pTheta_MCAccept", Vec_Pi_MC.Theta()*TMath::RadToDeg(), Vec_Pi_MC.P(), weight[0]);
	  FillHist2D("h2_Pi_pTheta_MCAccept_NoAB", Vec_Pi_MC_NoAB.Theta()*TMath::RadToDeg(), Vec_Pi_MC_NoAB.P(), weight[0]);
	  gDirectory->cd("../../");
	  gDirectory->cd("EventDists/Reco");
	  FillHist2D("h2_Pi_pTheta_RecoAccept", Vec_Pi_Rec.Theta()*TMath::RadToDeg(), Vec_Pi_Rec.P(), weight[0]);
	  gDirectory->cd("../../");
	}
      }
    } // End loop over charged particle associations

    // Check ZDC info to find neutrons
    for(unsigned int i=0; i<neutE.GetSize(); i++) { // Loop over zdc neutrons
      Vec_n_Rec.SetPxPyPzE(neutMomX[i],neutMomY[i],neutMomZ[i], neutE[i]);
      Vec_nRot_Rec = rot*Vec_n_Rec; // Rotation wrt proton axis
      Vec_n_Vertex.SetXYZ(neutPosX[i],neutPosY[i],neutPosZ[i]);
      gDirectory->cd("EventDists/Reco");
      FillHist2D("h2_n_pTheta_Reco", Vec_n_Rec.Theta()*TMath::RadToDeg(), Vec_n_Rec.P(), weight[0]);
      FillHist2D("h2_nRot_pTheta_Reco", Vec_nRot_Rec.Theta()*TMath::RadToDeg(), Vec_nRot_Rec.P(), weight[0]);
      gDirectory->cd("../../");
      if(ZDCPlots == kTRUE){
	gDirectory->cd("ZDCDists/Reco");
	FillHist2D("h2_n_XY_Reco", Vec_n_Vertex.X(), Vec_n_Vertex.Y(), weight[0]);
	FillHist2D("h2_nRot_XY_Reco", 35000*sin(Vec_nRot_Rec.Theta())*cos(Vec_nRot_Rec.Phi()), 35000*sin(Vec_nRot_Rec.Theta())*sin(Vec_nRot_Rec.Phi()), weight[0]);
	gDirectory->cd("../../");
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
      gDirectory->cd("B0Dists/Reco");
      FillHist1D("h1_B0_nClusters", E_B0.GetSize());
      FillHist2D("h2_n_pTheta_MC_B0", Vec_n_MC.Theta()*TMath::RadToDeg(), Vec_n_MC.P(), weight[0]);
      gDirectory->cd("../../");
      for (Int_t i = 0; i < E_B0.GetSize(); i++){
	gDirectory->cd("B0Dists/Reco");
	FillHist2D("h2_B0_XY_Raw", PosX_B0[i],PosY_B0[i]);
	FillHist2D("h2_B0_XY_Raw_EWeight", PosX_B0[i],PosY_B0[i], E_B0[i]);
	gDirectory->cd("../../");
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
	  gDirectory->cd("B0Dists/Reco");
	  FillHist2D("h2_n_pTheta_Reco", Vec_n_Rec.Theta()*TMath::RadToDeg(), Vec_n_Rec.P(), weight[0]);
	  gDirectory->cd("../../");
	  if(ESum_B0 > 10*B0_ECut){ // Ignore low energy junk events, assign vectors, fill histograms
	    Vec_n_Vertex.SetXYZ(tmpB0PosX/ESum_B0, tmpB0PosY/ESum_B0, tmpB0PosZ/ESum_B0);
	    if ( sqrt(pow((Vec_n_Vertex.X())+180,2) + pow(Vec_n_Vertex.Y() ,2)) > 55){ // Exclude the central region of the B0, addition of 180 is to remove x axis offset of the ZDC
		Good_nRec = kTRUE;
		nB0Hit = kTRUE;
		Vec_nRot_Rec = rot*Vec_n_Rec; // Rotation wrt proton axis
		FillB0Accept(E_B0.GetSize(), B0_ClusAccept, Vec_n_Rec, Vec_nRot_Rec, Vec_n_Vertex, Vec_n_MC, Vec_n_MC_NoAB, ESum_B0, weight[0], KinPlots);
	    }
	  }
	}
      }
    } // End loop over B0 info
    if(QAPlots == kTRUE){
      FillEffAccept(Vec_eSc_MC, Vec_Pi_MC, Vec_n_MC, weight[0], Good_eSc_Track, Good_Pi_Track, Good_nRec, nZDCHit, nB0Hit);
    }
    // Now, check for coin events, calculate quantities and fill relevant histograms
    if ( Good_eSc_Track == kTRUE && Good_Pi_Track == kTRUE && Good_nRec == kTRUE){
      CalculateBasicKinematics_DEMPRec(Vec_eSc_Rec, Vec_Pi_Rec, Vec_e_beam, Vec_p_beam); // Calculate Q2/W/eps/y for reconstructed DEMP events. Calculate some quantities multiple ways
      if(QAPlots == kTRUE){
	FillEffDEMPAccept(Vec_eSc_MC, Vec_Pi_MC, Vec_n_MC, weight[0], nZDCHit, nB0Hit);
      }
      
      if(EventDistPlots == kTRUE){
	FillDEMPAccept_EventDists_NoCuts(Vec_eSc_MC, Vec_eSc_MC_NoAB, Vec_eSc_Rec, Vec_Pi_MC, Vec_Pi_MC_NoAB, Vec_Pi_Rec, Vec_n_MC, Vec_n_MC_NoAB, Vec_n_Rec, Vec_nRot_Rec, weight[0], ZDCPlots, B0Plots, nZDCHit, nB0Hit);
      }
      
      if(KinPlots == kTRUE){
	FillDEMPAccept_Kin_NoCuts(ZDCPlots, nZDCHit, B0Plots, nB0Hit, weight[0]);
      }
      CorrectNeutronTrack(Vec_eSc_Rec, Vec_Pi_Rec, Vec_n_Rec, Vec_e_beam, Vec_p_beam); // Calculate the corrected neutron track, also sets PMiss/PMissRot
      CalculateKinematics_Q2Alt_DEMPRec(Vec_eSc_Rec, Vec_Pi_Rec, Vec_n_RecCorr, Vec_e_beam, Vec_p_beam);
      if (QAPlots == kTRUE){
	FillDEMP_Q2Alt(weight[0]);
      }
      if (Q2_Rec > 5 && Q2_Rec < 35){ //Cut on reconstructed Q2
	Calculate_t_DEMPRec(Vec_eSc_Rec, Vec_Pi_Rec, Vec_n_Rec, Vec_n_RecCorr, Vec_e_beam, Vec_p_beam); // Calculate -t
	nTheta_Diff = (Vec_PMiss_Rec.Theta() - Vec_n_Rec.Theta())*TMath::RadToDeg();
	nRotTheta_Diff = ( Vec_PMissRot_Rec.Theta() - Vec_nRot_Rec.Theta())*TMath::RadToDeg();
	nPhi_Diff = (Vec_PMiss_Rec.Phi() - Vec_n_Rec.Phi())*TMath::RadToDeg();
	nRotPhi_Diff = ( Vec_PMissRot_Rec.Phi() - Vec_nRot_Rec.Phi())*TMath::RadToDeg();
	MMiss = Vec_PMiss_Rec.M();

	if(KinPlots == kTRUE){
	  FillDEMPAccept_tKin_NoCuts(ZDCPlots, nZDCHit, B0Plots, nB0Hit, weight[0]);
	}

	if (nZDCHit == kTRUE && t_eXBABE > 0 && t_eXBABE < 1.4 && nRotTheta_Diff > ZDCDeltaTheta_Min && nRotTheta_Diff < ZDCDeltaTheta_Max && nRotPhi_Diff > ZDCDeltaPhi_Min && nRotPhi_Diff < ZDCDeltaPhi_Max && W_Rec > W_Tol){
	  DEMP_PassCuts = kTRUE;
	}
	else if (nB0Hit == kTRUE &&  t_eXBABE > 0 && t_eXBABE < 1.4 && nRotTheta_Diff > B0DeltaTheta_Min && nRotTheta_Diff < B0DeltaTheta_Max && nRotPhi_Diff > B0DeltaPhi_Min && nRotPhi_Diff < B0DeltaPhi_Max && W_Rec > W_Tol){
	  DEMP_PassCuts = kTRUE;	  
	}

	if(DEMP_PassCuts == kTRUE){
	  // Fill lots of plots and fill histograms
	  if(QAPlots == kTRUE){
	    FillEffDEMPCut(Vec_eSc_MC, Vec_Pi_MC, Vec_n_MC, weight[0], nZDCHit, nB0Hit);
	  }
	  if(EventDistPlots == kTRUE){
	    FillDEMPAccept_EventDists(Vec_eSc_MC, Vec_eSc_MC_NoAB, Vec_eSc_Rec, Vec_Pi_MC, Vec_Pi_MC_NoAB, Vec_Pi_Rec, Vec_n_MC, Vec_n_MC_NoAB, Vec_n_Rec, Vec_nRot_Rec, weight[0], ZDCPlots, B0Plots, nZDCHit, nB0Hit);
	  }
	  if(KinPlots == kTRUE){
	    FillDEMPAccept_Kin(ZDCPlots, nZDCHit, B0Plots, nB0Hit, weight[0]);
	  }
	  if(QAPlots == kTRUE){
	    FillDEMPAccept_Kin(ZDCPlots, nZDCHit, B0Plots, nB0Hit, weight[0]);
	  }
	  // Fill result plots binned in Q2
	  if( ResultsPlots == kTRUE) {
	    // Fill result histograms
	    FillDEMP_Results(ZDCPlots, nZDCHit, B0Plots, nB0Hit, weight[0]);
	    FillDEMP_QAKin(ZDCPlots, nZDCHit, B0Plots, nB0Hit, weight[0]);
	    FillDEMP_QAPartRes(Vec_eSc_MC, Vec_eSc_Rec, Vec_Pi_MC, Vec_Pi_Rec, Vec_n_MC, Vec_n_Rec, ZDCPlots, nZDCHit, B0Plots, nB0Hit, weight[0]);
	  }
	} // End main cut loop	
      } //end Q2 cut loop
    } // End of loop over DEMP events
  } // End of event while loop

  // Function to write rates to csv file, comment out if unwanted
  if (ResultsPlots == kTRUE){
    WriteCSV(BeamE, Date, BeamConfig, part, ZDCPlots, B0Plots);
  }
  if(QAPlots == kTRUE){
    CalcEff(ZDCPlots, B0Plots);
  }

  // Function to draw plots and make pdf
  WritePDF(BeamE, Date, BeamConfig, part, EventDistPlots, KinPlots, ZDCPlots, B0Plots, QAPlots, ResultsPlots);
  WritePlots(BeamE, Date, BeamConfig, part, EventDistPlots, KinPlots, ZDCPlots, B0Plots, QAPlots, ResultsPlots);
  WritePlotsKin(BeamE, Date, BeamConfig, part, EventDistPlots, KinPlots, ZDCPlots, B0Plots, QAPlots, ResultsPlots);
  WritePlotsQA(BeamE, Date, BeamConfig, part, EventDistPlots, KinPlots, ZDCPlots, B0Plots, QAPlots, ResultsPlots);
  
  ofile->Write(); // Write histograms to file
  ofile->Close(); // Close output file  
}
