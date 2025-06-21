// Stephen JD Kay - University of York
// Stephen.Kay@york.ac.uk
// 28/03/25
// Header file for new DEMP Analysis script, this contains histogram definitions and filling functions

void DefHists(TString InBeamE, Bool_t EventDists, Bool_t Kinematics, Bool_t ZDC, Bool_t B0, Bool_t QA, Bool_t Results){

  // Fix number of energy, theta and phi bins in subsequent plots
  Int_t NBins_Energy = 200;
  Int_t NBins_Theta = 200;
  Int_t NBins_Phi = 200;

  Double_t ElecBeamE = ((TObjString *)((InBeamE.Tokenize("on"))->At(0)))->String().Atof();
  Double_t HadBeamE = ((TObjString *)((InBeamE.Tokenize("on"))->At(1)))->String().Atof();

  if (EventDists == kTRUE){
    gDirectory->cd("EventDists/MC");
    TH2D* h2_eSc_pTheta_MC_NoAB = new TH2D("h2_eSc_pTheta_MC_NoAB", "e' MC Truth, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCMatched_NoAB = new TH2D("h2_eSc_pTheta_MCMatched_NoAB", "e' MC Truth (matched track), No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCAccept_NoAB = new TH2D("h2_eSc_pTheta_MCAccept_NoAB", "e' MC Truth Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCDEMPAccept_NoCuts_NoAB = new TH2D("h2_eSc_pTheta_MCDEMPAccept_NoCuts_NoAB", "e' MC Truth DEMP Accepted, No Cuts, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCDEMPAccept_NoAB = new TH2D("h2_eSc_pTheta_MCDEMPAccept_NoAB", "e' MC Truth DEMP Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MC = new TH2D("h2_eSc_pTheta_MC", "e' MC Truth; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCMatched = new TH2D("h2_eSc_pTheta_MCMatched", "e' MC Truth (matched track); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCAccept = new TH2D("h2_eSc_pTheta_MCAccept", "e' MC Truth Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCDEMPAccept_NoCuts = new TH2D("h2_eSc_pTheta_MCDEMPAccept_NoCuts", "e' MC Truth DEMP Accepted, No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCDEMPAccept = new TH2D("h2_eSc_pTheta_MCDEMPAccept", "e' MC Truth DEMP Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_MC_NoAB = new TH2D("h2_Pi_pTheta_MC_NoAB", "#pi MC Truth, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCMatched_NoAB = new TH2D("h2_Pi_pTheta_MCMatched_NoAB", "#pi MC Truth (matched track), No Beam Effets; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCAccept_NoAB = new TH2D("h2_Pi_pTheta_MCAccept_NoAB", "#pi MC Truth Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCDEMPAccept_NoCuts_NoAB = new TH2D("h2_Pi_pTheta_MCDEMPAccept_NoCuts_NoAB", "#pi MC Truth DEMP Accepted, NoCuts, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCDEMPAccept_NoAB = new TH2D("h2_Pi_pTheta_MCDEMPAccept_NoAB", "#pi MC Truth DEMP Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MC = new TH2D("h2_Pi_pTheta_MC", "#pi MC Truth; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCMatched = new TH2D("h2_Pi_pTheta_MCMatched", "#pi MC Truth (matched track); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCAccept = new TH2D("h2_Pi_pTheta_MCAccept", "#pi MC Truth Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCDEMPAccept_NoCuts = new TH2D("h2_Pi_pTheta_MCDEMPAccept_NoCuts", "#pi MC Truth DEMP Accepted, No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCDEMPAccept = new TH2D("h2_Pi_pTheta_MCDEMPAccept", "#pi MC Truth DEMP Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
  // Hard coding the +50 here is a bit odd, should maybe re-define this in terms of bin widths
    TH2D* h2_n_pTheta_MC_NoAB = new TH2D("h2_n_pTheta_MC_NoAB", "Neutron MC Truth, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCAccept_NoAB = new TH2D("h2_n_pTheta_MCAccept_NoAB", "Neutron MC Truth Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCDEMPAccept_NoCuts_NoAB = new TH2D("h2_n_pTheta_MCDEMPAccept_NoCuts_NoAB", "Neutron MC Truth DEMP Accepted, No Cuts, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCDEMPAccept_NoAB = new TH2D("h2_n_pTheta_MCDEMPAccept_NoAB", "Neutron MC Truth DEMP Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MC = new TH2D("h2_n_pTheta_MC", "Neutron MC Truth; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCAccept = new TH2D("h2_n_pTheta_MCAccept", "Neutron MC Truth Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCDEMPAccept_NoCuts = new TH2D("h2_n_pTheta_MCDEMPAccept_NoCuts", "Neutron MC Truth DEMP Accepted, No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCDEMPAccept = new TH2D("h2_n_pTheta_MCDEMPAccept", "Neutron MC Truth DEMP Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    gDirectory->cd("../../");
    
    gDirectory->cd("EventDists/Reco");
    TH2D* h2_eSc_pTheta_Reco = new TH2D("h2_eSc_pTheta_Reco", "e' Reconstructed ; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_RecoAccept = new TH2D("h2_eSc_pTheta_RecoAccept", "e' Reconstructed Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_RecoDEMPAccept_NoCuts = new TH2D("h2_eSc_pTheta_RecoDEMPAccept_NoCuts", "e' Reconstructed DEMP Accepted, No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_RecoDEMPAccept = new TH2D("h2_eSc_pTheta_RecoDEMPAccept", "e' Reconstructed DEMP Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
      TH2D* h2_Pi_pTheta_Reco = new TH2D("h2_Pi_pTheta_Reco", "#pi Reconstructed; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_RecoAccept = new TH2D("h2_Pi_pTheta_RecoAccept", "#pi Reconstructed Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_RecoDEMPAccept_NoCuts = new TH2D("h2_Pi_pTheta_RecoDEMPAccept_NoCuts", "#pi Reconstructed DEMP Accepted, No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_RecoDEMPAccept = new TH2D("h2_Pi_pTheta_RecoDEMPAccept", "#pi Reconstructed DEMP Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_Reco = new TH2D("h2_n_pTheta_Reco", "Neutron Reconstructed ; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_RecoAccept = new TH2D("h2_n_pTheta_RecoAccept", "Neutron Reconstructed Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_nRot_pTheta_Reco = new TH2D("h2_nRot_pTheta_Reco", "Neutron Reconstructed (Rotated 25 mrad); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_nRot_pTheta_RecoAccept = new TH2D("h2_nRot_pTheta_RecoAccept", "Neutron Reconstructed (Rotated 25 mrad) Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_RecoDEMPAccept_NoCuts = new TH2D("h2_n_pTheta_RecoDEMPAccept_NoCuts", "Neutron Reconstructed DEMP Accepted, No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_nRot_pTheta_RecoDEMPAccept_NoCuts = new TH2D("h2_nRot_pTheta_RecoDEMPAccept_NoCuts", "Neutron Reconstructed (Rotated 25 mrad) DEMP Accepted, No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_RecoDEMPAccept = new TH2D("h2_n_pTheta_RecoDEMPAccept", "Neutron Reconstructed DEMP Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_nRot_pTheta_RecoDEMPAccept = new TH2D("h2_nRot_pTheta_RecoDEMPAccept", "Neutron Reconstructed (Rotated 25 mrad) DEMP Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_XY_10m_RecoDEMPAccept_NoCuts = new TH2D("h2_n_XY_10m_RecoDEMPAccept_NoCuts", "Neutron Reconstructed XY position (@10m); x (mm); y (mm); Rate/bin (hz)",250,-500,0,200,-200,200);
    TH2D* h2_n_XY_10m_RecoDEMPAccept = new TH2D("h2_n_XY_10m_RecoDEMPAccept", "Neutron Reconstructed XY position (@10m); x (mm); y (mm); Rate/bin (hz)",250,-500,0,200,-200,200);
    gDirectory->cd("../../");
  }
  
  if (Kinematics == kTRUE){
    gDirectory->cd("KinematicDists/MC");
    TH1D* h1_Q2_MC = new TH1D("h1_Q2_MC", "Q^{2} MC Truth; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MC = new TH1D("h1_t_MC", "-t MC Truth; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MC = new TH1D("h1_W_MC", "W MC Truth; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MC = new TH1D("h1_eps_MC", "#epsilon MC Truth; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_MC = new TH1D("h1_y_MC", "y MC Truth; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_x_MC = new TH1D("h1_x_MC", "x MC Truth; x; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MC = new TH2D("h2_Q2t_MC", "Q^{2} vs -t MC Truth; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MC = new TH2D("h2_WQ2_MC", "W vs Q^{2} MC Truth; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

    TH1D* h1_Q2_MC_NoAB = new TH1D("h1_Q2_MC_NoAB", "Q^{2} MC Truth, No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MC_NoAB = new TH1D("h1_t_MC_NoAB", "-t MC Truth, No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MC_NoAB = new TH1D("h1_W_MC_NoAB", "W MC Truth, No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MC_NoAB = new TH1D("h1_eps_MC_NoAB", "#epsilon MC Truth, No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_MC_NoAB = new TH1D("h1_y_MC_NoAB", "y MC Truth, No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_x_MC_NoAB = new TH1D("h1_x_MC_NoAB", "x MC Truth, No Beam Effects; x; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MC_NoAB = new TH2D("h2_Q2t_MC_NoAB", "Q^{2} vs -t MC Truth, No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MC_NoAB = new TH2D("h2_WQ2_MC_NoAB", "W vs Q^{2} MC Truth, No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

    TH1D* h1_Q2_MCDEMPAccept_NoCuts = new TH1D("h1_Q2_MCDEMPAccept_NoCuts", "Q^{2} MC Truth DEMP Accepted, No Cuts; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MCDEMPAccept_NoCuts = new TH1D("h1_t_MCDEMPAccept_NoCuts", "-t MC Truth DEMP Accepted, Q^{2} Cut Only; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MCDEMPAccept_NoCuts = new TH1D("h1_W_MCDEMPAccept_NoCuts", "W MC Truth DEMP Accepted, No Cuts; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MCDEMPAccept_NoCuts = new TH1D("h1_eps_MCDEMPAccept_NoCuts", "#epsilon MC Truth DEMP Accepted, No Cuts; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_x_MCDEMPAccept_NoCuts = new TH1D("h1_x_MCDEMPAccept_NoCuts", "x MC Truth DEMP Accepted, No Cuts; x; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_y_MCDEMPAccept_NoCuts = new TH1D("h1_y_MCDEMPAccept_NoCuts", "y MC Truth DEMP Accepted, No Cuts; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MCDEMPAccept_NoCuts = new TH2D("h2_Q2t_MCDEMPAccept_NoCuts", "Q^{2} vs -t MC Truth DEMP Accepted, Q^{2} Cut Only; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MCDEMPAccept_NoCuts = new TH2D("h2_WQ2_MCDEMPAccept_NoCuts", "W vs Q^{2} MC Truth DEMP Accepted, No Cuts; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

    TH1D* h1_Q2_MCDEMPAccept_NoCuts_NoAB = new TH1D("h1_Q2_MCDEMPAccept_NoCuts_NoAB", "Q^{2} MC Truth DEMP Accepted, No Cuts, No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MCDEMPAccept_NoCuts_NoAB = new TH1D("h1_t_MCDEMPAccept_NoCuts_NoAB", "-t MC Truth DEMP Accepted, Q^{2} Cut Only, No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MCDEMPAccept_NoCuts_NoAB = new TH1D("h1_W_MCDEMPAccept_NoCuts_NoAB", "W MC Truth DEMP Accepted, No Cuts, No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MCDEMPAccept_NoCuts_NoAB = new TH1D("h1_eps_MCDEMPAccept_NoCuts_NoAB", "#epsilon MC Truth DEMP Accepted, No Cuts, No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_MCDEMPAccept_NoCuts_NoAB = new TH1D("h1_y_MCDEMPAccept_NoCuts_NoAB", "y MC Truth DEMP Accepted, No Cuts, No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_x_MCDEMPAccept_NoCuts_NoAB = new TH1D("h1_x_MCDEMPAccept_NoCuts_NoAB", "x MC Truth DEMP Accepted, No Cuts, No Beam Effects; x; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MCDEMPAccept_NoCuts_NoAB = new TH2D("h2_Q2t_MCDEMPAccept_NoCuts_NoAB", "Q^{2} vs -t MC Truth DEMP Accepted, Q^{2} Cut Only, No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MCDEMPAccept_NoCuts_NoAB = new TH2D("h2_WQ2_MCDEMPAccept_NoCuts_NoAB", "W vs Q^{2} MC Truth DEMP Accepted, No Cuts, No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

    TH1D* h1_Q2_MCDEMPAccept = new TH1D("h1_Q2_MCDEMPAccept", "Q^{2} MC Truth DEMP Accepted; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MCDEMPAccept = new TH1D("h1_t_MCDEMPAccept", "-t MC Truth DEMP Accepted; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MCDEMPAccept = new TH1D("h1_W_MCDEMPAccept", "W MC Truth DEMP Accepted; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MCDEMPAccept = new TH1D("h1_eps_MCDEMPAccept", "#epsilon MC Truth DEMP Accepted; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_MCDEMPAccept = new TH1D("h1_y_MCDEMPAccept", "y MC Truth DEMP Accepted; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_x_MCDEMPAccept = new TH1D("h1_x_MCDEMPAccept", "x MC Truth DEMP Accepted; x; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MCDEMPAccept = new TH2D("h2_Q2t_MCDEMPAccept", "Q^{2} vs -t MC Truth DEMP Accepted; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MCDEMPAccept = new TH2D("h2_WQ2_MCDEMPAccept", "W vs Q^{2} MC Truth DEMP Accepted; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

    TH1D* h1_Q2_MCDEMPAccept_NoAB = new TH1D("h1_Q2_MCDEMPAccept_NoAB", "Q^{2} MC Truth DEMP Accepted, No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MCDEMPAccept_NoAB = new TH1D("h1_t_MCDEMPAccept_NoAB", "-t MC Truth DEMP Accepted, No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MCDEMPAccept_NoAB = new TH1D("h1_W_MCDEMPAccept_NoAB", "W MC Truth DEMP Accepted, No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MCDEMPAccept_NoAB = new TH1D("h1_eps_MCDEMPAccept_NoAB", "#epsilon MC Truth DEMP Accepted, No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_MCDEMPAccept_NoAB = new TH1D("h1_y_MCDEMPAccept_NoAB", "y MC Truth DEMP Accepted, No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_x_MCDEMPAccept_NoAB = new TH1D("h1_x_MCDEMPAccept_NoAB", "x MC Truth DEMP Accepted, No Beam Effects; x; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MCDEMPAccept_NoAB = new TH2D("h2_Q2t_MCDEMPAccept_NoAB", "Q^{2} vs -t MC Truth DEMP Accepted, No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MCDEMPAccept_NoAB = new TH2D("h2_WQ2_MCDEMPAccept_NoAB", "W vs Q^{2} MC Truth DEMP Accepted, No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
    gDirectory->cd("../../");

    gDirectory->cd("KinematicDists/Reco");
    TH1D* h1_Q2_Reco_NoCuts = new TH1D("h1_Q2_Reco_NoCuts", "Q^{2}_{DA} Reconstructed (No Cuts); Q^{2}_{DA} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_tBABE_Reco_NoCuts = new TH1D("h1_tBABE_Reco_NoCuts", "-t_{BABE} Reconstructed (Q^{2} Cut Only); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teX_Reco_NoCuts = new TH1D("h1_teX_Reco_NoCuts", "-t_{eX} Reconstructed (Q^{2} Cut Only); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teXPT_Reco_NoCuts = new TH1D("h1_teXPT_Reco_NoCuts", "-t_{eXPT} Reconstructed (Q^{2} Cut Only); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teXBABE_Reco_NoCuts = new TH1D("h1_teXBABE_Reco_NoCuts", "-t_{eXBABE} Reconstructed (Q^{2} Cut Only); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_Reco_NoCuts = new TH1D("h1_W_Reco_NoCuts", "W Reconstructed (No Cuts); W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_Reco_NoCuts = new TH1D("h1_eps_Reco_NoCuts", "#epsilon Reconstructed (No Cuts); #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_Reco_NoCuts = new TH1D("h1_y_Reco_NoCuts", "y_{DA} Reconstructed (No Cuts); y_{DA}; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_x_Reco_NoCuts = new TH1D("h1_x_Reco_NoCuts", "x_{DA} Reconstructed (No Cuts); x_{DA}; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_DeltaTheta_Reco_NoCuts = new TH1D("h1_DeltaTheta_Reco_NoCuts", "#Delta#theta (#theta_{pMiss} - #theta_{ZDC/B0}) Reconstructed (Q^{2} Cut Only); #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
    TH1D* h1_DeltaPhi_Reco_NoCuts = new TH1D("h1_DeltaPhi_Reco_NoCuts", "#Delta#phi (#phi_{pMiss} - #phi_{ZDC/B0}) Reconstructed (Q^{2} Cut Only); #Delta#phi (Deg); Rate/bin (Hz)", 50, -25, 25);
    TH1D* h1_MissMass_NoCuts = new TH1D("h1_MissMass_NoCuts", "Missing Mass Distribution, Reconstructed (Q^{2} Cut Only); Missing Mass (GeV/c^{2}); Rate/bin (Hz)", 100, -25, 25);
    TH2D* h2_Q2tBABE_Reco_NoCuts = new TH2D("h2_Q2tBABE_Reco_NoCuts", "Q^{2}_{DA} vs -t_{BABE} Reconstructed (Q^{2}_{DA} Cut Only); Q^{2}_{DA} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teX_Reco_NoCuts = new TH2D("h2_Q2teX_Reco_NoCuts", "Q^{2}_{DA} vs -t_{eX} Reconstructed (Q^{2}_{DA} Cut Only); Q^{2}_{DA} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teXPT_Reco_NoCuts = new TH2D("h2_Q2teXPT_Reco_NoCuts", "Q^{2}_{DA} vs -t_{eXPT} Reconstructed (Q^{2}_{DA} Cut Only); Q^{2}_{DA} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teXBABE_Reco_NoCuts = new TH2D("h2_teXBABEQ2_Reco_NoCuts", "Q^{2}_{DA} vs -t_{eXBABE} Reconstructed (Q^{2}_{DA} Cut Only);  Q^{2}_{DA} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_Reco_NoCuts = new TH2D("h2_WQ2_Reco_NoCuts", "W vs Q^{2}_{DA} Reconstructed (No Cuts); W (GeV); Q^{2}_{DA} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
    TH2D* h2_DeltaThetaPhi_Reco_NoCuts = new TH2D("h2_DeltaThetaPhi_Reco_NoCuts", "#Delta#theta  (#theta_{pMiss} - #theta_{ZDC/B0}) vs #Delta#phi (#phi_{pMiss} - #phi_{ZDC/B0}) Reconstructed (Q^{2} Cuts only); #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);
    TH2D* h2_DeltaRotThetaRotPhi_Reco_NoCuts = new TH2D("h2_DeltaRotThetaRotPhi_Reco_NoCuts", "#Delta#theta^{*}  (#theta^{*}_{pMiss} - #theta^{*}_{ZDC/B0}) vs #Delta#phi^{*} (#phi^{*}_{pMiss} - #phi^{*}_{ZDC/B0}) Reconstructed (Q^{2} Cuts only); #Delta#theta^{*} (Deg); #Delta#phi^{*} (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);
    
    TH1D* h1_Q2_Reco = new TH1D("h1_Q2_Reco", "Q^{2}_{DA} Reconstructed; Q^{2}_{DA} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_tBABE_Reco = new TH1D("h1_tBABE_Reco", "-t_{BABE} Reconstructed; -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teX_Reco = new TH1D("h1_teX_Reco", "-t_{eX} Reconstructed; -t_{eX} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teXPT_Reco = new TH1D("h1_teXPT_Reco", "-t_{eXPT} Reconstructed; -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teXBABE_Reco = new TH1D("h1_teXBABE_Reco", "-t_{eXBABE} Reconstructed; -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_Reco = new TH1D("h1_W_Reco", "W Reconstructed; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_Reco = new TH1D("h1_eps_Reco", "#epsilon Reconstructed; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_Reco = new TH1D("h1_y_Reco", "y_{DA} Reconstructed; y_{DA}; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_x_Reco = new TH1D("h1_x_Reco", "x_{DA} Reconstructed; x_{DA}; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_DeltaTheta_Reco = new TH1D("h1_DeltaTheta_Reco", "#Delta#theta (#theta_{pMiss} - #theta_{ZDC/B0}) Reconstructed; #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
    TH1D* h1_DeltaPhi_Reco = new TH1D("h1_DeltaPhi_Reco", "#Delta#phi (#phi_{pMiss} - #phi_{ZDC/B0}) Reconstructed; #Delta#phi (Deg); Rate/bin (Hz)", 200, -100, 100);
    TH1D* h1_MissMass = new TH1D("h1_MissMass", "Missing Mass Distribution; Missing Mass (GeV/c^{2}); Rate/bin (Hz)", 100, -25, 25);
    TH2D* h2_Q2tBABE_Reco = new TH2D("h2_Q2tBABE_Reco", "Q^{2}_{DA} vs -t_{BABE} Reconstructed; Q^{2}_{DA} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teX_Reco = new TH2D("h2_Q2teX_Reco", "Q^{2}_{DA} vs -t_{eX} Reconstructed; Q^{2}_{DA} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teXPT_Reco = new TH2D("h2_Q2teXPT_Reco", "Q^{2}_{DA} vs -t_{eXPT} Reconstructed; Q^{2}_{DA} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teXBABE_Reco = new TH2D("h2_Q2teXBABE_Reco", "Q^{2}_{DA} vs -t_{eXBABE} Reconstructed;  Q^{2}_{DA} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_Reco = new TH2D("h2_WQ2_Reco", "W vs Q^{2}_{DA} Reconstructed; W (GeV); Q^{2}_{DA} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
    TH2D* h2_DeltaThetaPhi_Reco = new TH2D("h2_DeltaThetaPhi_Reco", "#Delta#theta  (#theta_{pMiss} - #theta_{ZDC/B0}) vs #Delta#phi (#phi_{pMiss} - #phi_{ZDC/B0}) Recostructed; #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);
    TH2D* h2_DeltaRotThetaRotPhi_Reco = new TH2D("h2_DeltaRotThetaRotPhi_Reco", "#Delta#theta^{*}  (#theta^{*}_{pMiss} - #theta^{*}_{ZDC/B0}) vs #Delta#phi^{*} (#phi^{*}_{pMiss} - #phi^{*}_{ZDC/B0}); #Delta#theta^{*} (Deg); #Delta#phi^{*} (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);

    gDirectory->cd("../../");
    
    if (B0 == kTRUE){
      gDirectory->cd("KinematicDists/MC/B0");
      TH1D* h1_Q2_MCAcceptB0 = new TH1D("h1_Q2_MCAcceptB0", "Q^{2} MC Truth Accepted (B0 events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCAcceptB0 = new TH1D("h1_t_MCAcceptB0", "-t MC Truth Accepted (B0 events only); -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCAcceptB0 = new TH1D("h1_W_MCAcceptB0", "W MC Truth Accepted (B0 events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCAcceptB0 = new TH1D("h1_eps_MCAcceptB0", "#epsilon MC Truth Accepted (B0 events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCAcceptB0 = new TH1D("h1_y_MCAcceptB0", "y MC Truth Accepted (B0 events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCAcceptB0 = new TH1D("h1_x_MCAcceptB0", "x MC Truth Accepted (B0 events only); x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCAcceptB0 = new TH2D("h2_Q2t_MCAcceptB0", "Q^{2} vs -t MC Truth Accepted (B0 events only); Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCAcceptB0 = new TH2D("h2_WQ2_MCAcceptB0", "W vs Q^{2} MC Truth Accepted (B0 events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCAcceptB0_NoAB = new TH1D("h1_Q2_MCAcceptB0_NoAB", "Q^{2} MC Truth Accepted (B0 events only), No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCAcceptB0_NoAB = new TH1D("h1_t_MCAcceptB0_NoAB", "-t MC Truth Accepted (B0 events only), No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCAcceptB0_NoAB = new TH1D("h1_W_MCAcceptB0_NoAB", "W MC Truth Accepted (B0 events only), No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCAcceptB0_NoAB = new TH1D("h1_eps_MCAcceptB0_NoAB", "#epsilon MC Truth Accepted (B0 events only), No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCAcceptB0_NoAB = new TH1D("h1_y_MCAcceptB0_NoAB", "y MC Truth Accepted (B0 events only), No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCAcceptB0_NoAB = new TH1D("h1_x_MCAcceptB0_NoAB", "x MC Truth Accepted (B0 events only), No Beam Effects; x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCAcceptB0_NoAB = new TH2D("h2_Q2t_MCAcceptB0_NoAB", "Q^{2} vs -t MC Truth Accepted (B0 events only), No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCAcceptB0_NoAB = new TH2D("h2_WQ2_MCAcceptB0_NoAB", "W vs Q^{2} MC Truth Accepted (B0 events only), No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptB0_NoCuts = new TH1D("h1_Q2_MCDEMPAcceptB0_NoCuts", "Q^{2} MC Truth DEMP Accepted (B0 Events only), No Cuts; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptB0_NoCuts = new TH1D("h1_t_MCDEMPAcceptB0_NoCuts", "-t MC Truth DEMP Accepted (B0 Events only), Q^{2} Cut Only; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptB0_NoCuts = new TH1D("h1_W_MCDEMPAcceptB0_NoCuts", "W MC Truth DEMP Accepted (B0 Events only), No Cuts; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptB0_NoCuts = new TH1D("h1_eps_MCDEMPAcceptB0_NoCuts", "#epsilon MC Truth DEMP Accepted (B0 Events only), No Cuts; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptB0_NoCuts = new TH1D("h1_y_MCDEMPAcceptB0_NoCuts", "y MC Truth DEMP Accepted (B0 Events only), No Cuts; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCDEMPAcceptB0_NoCuts = new TH1D("h1_x_MCDEMPAcceptB0_NoCuts", "x MC Truth DEMP Accepted (B0 Events only), No Cuts; x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptB0_NoCuts = new TH2D("h2_Q2t_MCDEMPAcceptB0_NoCuts", "Q^{2} vs -t MC Truth DEMP Accepted (B0 Events only), Q^{2} Cut Only; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptB0_NoCuts = new TH2D("h2_WQ2_MCDEMPAcceptB0_NoCuts", "W vs Q^{2} MC Truth DEMP Accepted (B0 Events only), No Cuts; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptB0_NoCuts_NoAB = new TH1D("h1_Q2_MCDEMPAcceptB0_NoCuts_NoAB", "Q^{2} MC Truth DEMP Accepted (B0 Events only), No Cuts, No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptB0_NoCuts_NoAB = new TH1D("h1_t_MCDEMPAcceptB0_NoCuts_NoAB", "-t MC Truth DEMP Accepted (B0 Events only), Q^{2} Cut Only, No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptB0_NoCuts_NoAB = new TH1D("h1_W_MCDEMPAcceptB0_NoCuts_NoAB", "W MC Truth DEMP Accepted (B0 Events only), No Cuts, No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptB0_NoCuts_NoAB = new TH1D("h1_eps_MCDEMPAcceptB0_NoCuts_NoAB", "#epsilon MC Truth DEMP Accepted (B0 Events only), No Cuts, No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptB0_NoCuts_NoAB = new TH1D("h1_y_MCDEMPAcceptB0_NoCuts_NoAB", "y MC Truth DEMP Accepted (B0 Events only), No Cuts, No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCDEMPAcceptB0_NoCuts_NoAB = new TH1D("h1_x_MCDEMPAcceptB0_NoCuts_NoAB", "x MC Truth DEMP Accepted (B0 Events only), No Cuts, No Beam Effects; x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptB0_NoCuts_NoAB = new TH2D("h2_Q2t_MCDEMPAcceptB0_NoCuts_NoAB", "Q^{2} vs -t MC Truth DEMP Accepted (B0 Events only), Q^{2} Cut Only, No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptB0_NoCuts_NoAB = new TH2D("h2_WQ2_MCDEMPAcceptB0_NoCuts_NoAB", "W vs Q^{2} MC Truth DEMP Accepted (B0 Events only), No Cuts, No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      
      TH1D* h1_Q2_MCDEMPAcceptB0 = new TH1D("h1_Q2_MCDEMPAcceptB0", "Q^{2} MC Truth DEMP Accepted (B0 events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptB0 = new TH1D("h1_t_MCDEMPAcceptB0", "-t MC Truth DEMP Accepted (B0 events only); -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptB0 = new TH1D("h1_W_MCDEMPAcceptB0", "W MC Truth DEMP Accepted (B0 events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptB0 = new TH1D("h1_eps_MCDEMPAcceptB0", "#epsilon MC Truth DEMP Accepted (B0 events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptB0 = new TH1D("h1_y_MCDEMPAcceptB0", "y MC Truth DEMP Accepted (B0 events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCDEMPAcceptB0 = new TH1D("h1_x_MCDEMPAcceptB0", "x MC Truth DEMP Accepted (B0 events only); x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptB0 = new TH2D("h2_Q2t_MCDEMPAcceptB0", "Q^{2} vs -t MC Truth DEMP Accepted (B0 events only); Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptB0 = new TH2D("h2_WQ2_MCDEMPAcceptB0", "W vs Q^{2} MC Truth DEMP Accepted (B0 events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptB0_NoAB = new TH1D("h1_Q2_MCDEMPAcceptB0_NoAB", "Q^{2} MC Truth DEMP Accepted (B0 events only), No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptB0_NoAB = new TH1D("h1_t_MCDEMPAcceptB0_NoAB", "-t MC Truth DEMP Accepted (B0 events only), No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptB0_NoAB = new TH1D("h1_W_MCDEMPAcceptB0_NoAB", "W MC Truth DEMP Accepted (B0 events only), No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptB0_NoAB = new TH1D("h1_eps_MCDEMPAcceptB0_NoAB", "#epsilon MC Truth DEMP Accepted (B0 events only), No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptB0_NoAB = new TH1D("h1_y_MCDEMPAcceptB0_NoAB", "y MC Truth DEMP Accepted (B0 events only), No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCDEMPAcceptB0_NoAB = new TH1D("h1_x_MCDEMPAcceptB0_NoAB", "x MC Truth DEMP Accepted (B0 events only), No Beam Effects; x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptB0_NoAB = new TH2D("h2_Q2t_MCDEMPAcceptB0_NoAB", "Q^{2} vs -t MC Truth DEMP Accepted (B0 events only), No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptB0_NoAB = new TH2D("h2_WQ2_MCDEMPAcceptB0_NoAB", "W vs Q^{2} MC Truth DEMP Accepted (B0 events only), No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      gDirectory->cd("../../../");
      
      gDirectory->cd("KinematicDists/Reco/B0");
      TH1D* h1_Q2_B0Reco_NoCuts = new TH1D("h1_Q2_B0Reco_NoCuts", "Q^{2}_{DA} Reconstructed (No Cuts, B0 n events only); Q^{2}_{DA} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_tBABE_B0Reco_NoCuts = new TH1D("h1_tBABE_B0Reco_NoCuts", "-t_{BABE} Reconstructed (Q^{2}_{DA} Cuts Only, B0 n events only); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teX_B0Reco_NoCuts = new TH1D("h1_teX_B0Reco_NoCuts", "-t_{eX} Reconstructed (Q^{2}_{DA} Cuts Only, B0 n events only); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXPT_B0Reco_NoCuts = new TH1D("h1_teXPT_B0Reco_NoCuts", "-t_{eXPT} Reconstructed (Q^{2}_{DA} Cuts Only, B0 n events only); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXBABE_B0Reco_NoCuts = new TH1D("h1_teXBABE_B0Reco_NoCuts", "-t_{eXBABE} Reconstructed (Q^{2}_{DA} Cuts Only, B0 n events only); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_B0Reco_NoCuts = new TH1D("h1_W_B0Reco_NoCuts", "W Reconstructed (No Cuts, B0 n events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_B0Reco_NoCuts = new TH1D("h1_eps_B0Reco_NoCuts", "#epsilon Reconstructed (No Cuts, B0 n events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_B0Reco_NoCuts = new TH1D("h1_y_B0Reco_NoCuts", "y_{DA} Reconstructed (No Cuts, B0 n events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_B0Reco_NoCuts = new TH1D("h1_x_B0Reco_NoCuts", "x_{DA} Reconstructed (No Cuts, B0 n events only); x_{DA}; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_DeltaTheta_B0Reco_NoCuts = new TH1D("h1_DeltaTheta_B0Reco_NoCuts", "#Delta#theta (#theta_{pMiss} - #theta_{B0}) Reconstructed (Q^{2}_{DA} Cuts Only, B0 n events only); #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
      TH1D* h1_DeltaPhi_B0Reco_NoCuts = new TH1D("h1_DeltaPhi_B0Reco_NoCuts", "#Delta#phi (#phi_{pMiss} - #phi_{B0}) Reconstructed (Q^{2}_{DA} Cuts Only, B0 n events only); #Delta#phi (Deg); Rate/bin (Hz)", 200, -100, 100);
      TH1D* h1_MissMass_B0Reco_NoCuts = new TH1D("h1_MissMass_B0Reco_NoCuts", "Missing Mass Distribution, B0 n events only, Reconstructed (Q^{2}_{DA} Cut Only); Missing Mass (GeV/c^{2}); Rate/bin (Hz)", 100, -25, 25);
      TH2D* h2_Q2tBABE_B0Reco_NoCuts = new TH2D("h2_Q2tBABE_B0Reco_NoCuts", "Q^{2}_{DA} vs -t_{BABE} Reconstructed (Q^{2}_{DA} Cuts Only, B0 n events only); Q^{2}_{DA} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teX_B0Reco_NoCuts = new TH2D("h2_Q2teX_B0Reco_NoCuts", "Q^{2}_{DA} vs -t_{eX} Reconstructed (Q^{2}_{DA} Cuts Only, B0 n events only); Q^{2}_{DA} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXPT_B0Reco_NoCuts = new TH2D("h2_Q2teXPT_B0Reco_NoCuts", "Q^{2}_{DA} vs -t_{eXPT} Reconstructed (Q^{2}_{DA} Cuts Only, B0 n events only); Q^{2}_{DA} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXBABE_B0Reco_NoCuts = new TH2D("h2_Q2teXBABE_B0Reco_NoCuts", "Q^{2}_{DA} vs -t_{eXBABE} Reconstructed (Q^{2}_{DA} Cuts Only, B0 n events only);  Q^{2}_{DA} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_B0Reco_NoCuts = new TH2D("h2_WQ2_B0Reco_NoCuts", "W vs Q^{2}_{DA} Reconstructed (No Cuts, B0 n events only); W (GeV); Q^{2}_{DA} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      TH2D* h2_DeltaThetaPhi_B0Reco_NoCuts = new TH2D("h2_DeltaThetaPhi_B0Reco_NoCuts", "#Delta#theta  (#theta_{pMiss} - #theta_{B0}) vs #Delta#phi (#phi_{pMiss} - #phi_{B0}) Reconstructed (Q^{2}_{DA} Cuts only, B0 n events only); #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);
    TH2D* h2_DeltaRotThetaRotPhi_B0Reco_NoCuts = new TH2D("h2_DeltaRotThetaRotPhi_B0Reco_NoCuts", "#Delta#theta^{*}  (#theta^{*}_{pMiss} - #theta^{*}_{B0}) vs #Delta#phi^{*} (#phi^{*}_{pMiss} - #phi^{*}_{B0}) Reconstructed (Q^{2} Cuts only, B0 n events only); #Delta#theta^{*} (Deg); #Delta#phi^{*} (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);

      TH1D* h1_Q2_B0Reco = new TH1D("h1_Q2_B0Reco", "Q^{2}_{DA} Reconstructed (B0 n events only); Q^{2}_{DA} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_tBABE_B0Reco = new TH1D("h1_tBABE_B0Reco", "-t_{BABE} Reconstructed (B0 n events only); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teX_B0Reco = new TH1D("h1_teX_B0Reco", "-t_{eX} Reconstructed (B0 n events only); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXPT_B0Reco = new TH1D("h1_teXPT_B0Reco", "-t_{eXPT} Reconstructed (B0 n events only); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXBABE_B0Reco = new TH1D("h1_teXBABE_B0Reco", "-t_{eXBABE} Reconstructed (B0 n events only); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_B0Reco = new TH1D("h1_W_B0Reco", "W Reconstructed (B0 n events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_B0Reco = new TH1D("h1_eps_B0Reco", "#epsilon Reconstructed (B0 n events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_B0Reco = new TH1D("h1_y_B0Reco", "y_{DA} Reconstructed (B0 n events only); y_{DA}; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_B0Reco = new TH1D("h1_x_B0Reco", "x_{DA} Reconstructed (B0 n events only); x_{DA}; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_DeltaTheta_B0Reco = new TH1D("h1_DeltaTheta_B0Reco", "#Delta#theta (#theta_{pMiss} - #theta_{B0}) Reconstructed (B0 n events only); #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
      TH1D* h1_DeltaPhi_B0Reco = new TH1D("h1_DeltaPhi_B0Reco", "#Delta#phi (#phi_{pMiss} - #phi_{B0}) Reconstructed (B0 n events only); #Delta#phi (Deg); Rate/bin (Hz)", 200, -100, 100);
      TH1D* h1_MissMass_B0Reco = new TH1D("h1_MissMass_B0Reco", "Missing Mass Distribution, B0 n events only; Missing Mass (GeV/c^{2}); Rate/bin (Hz)", 100, -25, 25);
      TH2D* h2_Q2tBABE_B0Reco = new TH2D("h2_Q2tBABE_B0Reco", "Q^{2}_{DA} vs -t_{BABE} Reconstructed (B0 n events only); Q^{2}_{DA} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teX_B0Reco = new TH2D("h2_Q2teX_B0Reco", "Q^{2}_{DA} vs -t_{eX} Reconstructed (B0 n events only); Q^{2}_{DA} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXPT_B0Reco = new TH2D("h2_Q2teXPT_B0Reco", "Q^{2}_{DA} vs -t_{eXPT} Reconstructed (B0 n events only); Q^{2}_{DA} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXBABE_B0Reco = new TH2D("h2_Q2teXBABE_B0Reco", "Q^{2}_{DA} vs -t_{eXBABE} Reconstructed (B0 n events only);  Q^{2}_{DA} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_B0Reco = new TH2D("h2_WQ2_B0Reco", "W vs Q^{2}_{DA} Reconstructed (B0 n events only); W (GeV); Q^{2}_{DA} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      TH2D* h2_DeltaThetaPhi_B0Reco = new TH2D("h2_DeltaThetaPhi_B0Reco", "#Delta#theta  (#theta_{pMiss} - #theta_{B0}) vs #Delta#phi (#phi_{pMiss} - #phi_{B0}) Reconstruted (B0, n events only); #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);
      TH2D* h2_DeltaRotThetaRotPhi_B0Reco = new TH2D("h2_DeltaRotThetaRotPhi_B0Reco", "#Delta#theta^{*}  (#theta^{*}_{pMiss} - #theta^{*}_{B0}) vs #Delta#phi^{*} (#phi^{*}_{pMiss} - #phi^{*}_{B0}); #Delta#theta^{*} (Deg); #Delta#phi^{*} (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);
      gDirectory->cd("../../../");
    }
    
    if (ZDC == kTRUE){
      gDirectory->cd("KinematicDists/MC/ZDC");
      TH1D* h1_Q2_MCAcceptZDC = new TH1D("h1_Q2_MCAcceptZDC", "Q^{2} MC Truth Accepted (ZDC events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCAcceptZDC = new TH1D("h1_t_MCAcceptZDC", "-t MC Truth Accepted (ZDC events only); -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCAcceptZDC = new TH1D("h1_W_MCAcceptZDC", "W MC Truth Accepted (ZDC events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCAcceptZDC = new TH1D("h1_eps_MCAcceptZDC", "#epsilon MC Truth Accepted (ZDC events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCAcceptZDC = new TH1D("h1_y_MCAcceptZDC", "y MC Truth Accepted (ZDC events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCAcceptZDC = new TH1D("h1_x_MCAcceptZDC", "x MC Truth Accepted (ZDC events only); x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCAcceptZDC = new TH2D("h2_Q2t_MCAcceptZDC", "Q^{2} vs -t MC Truth Accepted (ZDC events only); Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCAcceptZDC = new TH2D("h2_WQ2_MCAcceptZDC", "W vs Q^{2} MC Truth Accepted (ZDC events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCAcceptZDC_NoAB = new TH1D("h1_Q2_MCAcceptZDC_NoAB", "Q^{2} MC Truth Accepted (ZDC events only), No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCAcceptZDC_NoAB = new TH1D("h1_t_MCAcceptZDC_NoAB", "-t MC Truth Accepted (ZDC events only), No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCAcceptZDC_NoAB = new TH1D("h1_W_MCAcceptZDC_NoAB", "W MC Truth Accepted (ZDC events only), No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCAcceptZDC_NoAB = new TH1D("h1_eps_MCAcceptZDC_NoAB", "#epsilon MC Truth Accepted (ZDC events only), No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCAcceptZDC_NoAB = new TH1D("h1_y_MCAcceptZDC_NoAB", "y MC Truth Accepted (ZDC events only), No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCAcceptZDC_NoAB = new TH1D("h1_x_MCAcceptZDC_NoAB", "x MC Truth Accepted (ZDC events only), No Beam Effects; x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCAcceptZDC_NoAB = new TH2D("h2_Q2t_MCAcceptZDC_NoAB", "Q^{2} vs -t MC Truth Accepted (ZDC events only), No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCAcceptZDC_NoAB = new TH2D("h2_WQ2_MCAcceptZDC_NoAB", "W vs Q^{2} MC Truth Accepted (ZDC events only), No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptZDC_NoCuts = new TH1D("h1_Q2_MCDEMPAcceptZDC_NoCuts", "Q^{2} MC Truth DEMP Accepted (ZDC Events only), No Cuts; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptZDC_NoCuts = new TH1D("h1_t_MCDEMPAcceptZDC_NoCuts", "-t MC Truth DEMP Accepted (ZDC Events only), Q^{2} Cut Only; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptZDC_NoCuts = new TH1D("h1_W_MCDEMPAcceptZDC_NoCuts", "W MC Truth DEMP Accepted (ZDC Events only), No Cuts; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptZDC_NoCuts = new TH1D("h1_eps_MCDEMPAcceptZDC_NoCuts", "#epsilon MC Truth DEMP Accepted (ZDC Events only), No Cuts; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptZDC_NoCuts = new TH1D("h1_y_MCDEMPAcceptZDC_NoCuts", "y MC Truth DEMP Accepted (ZDC Events only), No Cuts; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCDEMPAcceptZDC_NoCuts = new TH1D("h1_x_MCDEMPAcceptZDC_NoCuts", "x MC Truth DEMP Accepted (ZDC Events only), No Cuts; x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptZDC_NoCuts = new TH2D("h2_Q2t_MCDEMPAcceptZDC_NoCuts", "Q^{2} vs -t MC Truth DEMP Accepted (ZDC Events only), Q^{2} Cut Only; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptZDC_NoCuts = new TH2D("h2_WQ2_MCDEMPAcceptZDC_NoCuts", "W vs Q^{2} MC Truth DEMP Accepted (ZDC Events only), No Cuts; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptZDC_NoCuts_NoAB = new TH1D("h1_Q2_MCDEMPAcceptZDC_NoCuts_NoAB", "Q^{2} MC Truth DEMP Accepted (ZDC Events only), No Cuts, No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptZDC_NoCuts_NoAB = new TH1D("h1_t_MCDEMPAcceptZDC_NoCuts_NoAB", "-t MC Truth DEMP Accepted (ZDC Events only), Q^{2} Cut Only, No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptZDC_NoCuts_NoAB = new TH1D("h1_W_MCDEMPAcceptZDC_NoCuts_NoAB", "W MC Truth DEMP Accepted (ZDC Events only), No Cuts, No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptZDC_NoCuts_NoAB = new TH1D("h1_eps_MCDEMPAcceptZDC_NoCuts_NoAB", "#epsilon MC Truth DEMP Accepted (ZDC Events only), No Cuts, No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptZDC_NoCuts_NoAB = new TH1D("h1_y_MCDEMPAcceptZDC_NoCuts_NoAB", "y MC Truth DEMP Accepted (ZDC Events only), No Cuts, No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCDEMPAcceptZDC_NoCuts_NoAB = new TH1D("h1_x_MCDEMPAcceptZDC_NoCuts_NoAB", "x MC Truth DEMP Accepted (ZDC Events only), No Cuts, No Beam Effects; x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptZDC_NoCuts_NoAB = new TH2D("h2_Q2t_MCDEMPAcceptZDC_NoCuts_NoAB", "Q^{2} vs -t MC Truth DEMP Accepted (ZDC Events only), Q^{2} Cut Only, No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptZDC_NoCuts_NoAB = new TH2D("h2_WQ2_MCDEMPAcceptZDC_NoCuts_NoAB", "W vs Q^{2} MC Truth DEMP Accepted (ZDC Events only), No Cuts, No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      
      TH1D* h1_Q2_MCDEMPAcceptZDC = new TH1D("h1_Q2_MCDEMPAcceptZDC", "Q^{2} MC Truth DEMP Accepted (ZDC events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptZDC = new TH1D("h1_t_MCDEMPAcceptZDC", "-t MC Truth DEMP Accepted (ZDC events only); -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptZDC = new TH1D("h1_W_MCDEMPAcceptZDC", "W MC Truth DEMP Accepted (ZDC events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptZDC = new TH1D("h1_eps_MCDEMPAcceptZDC", "#epsilon MC Truth DEMP Accepted (ZDC events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptZDC = new TH1D("h1_y_MCDEMPAcceptZDC", "y MC Truth DEMP Accepted (ZDC events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCDEMPAcceptZDC = new TH1D("h1_x_MCDEMPAcceptZDC", "x MC Truth DEMP Accepted (ZDC events only); x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptZDC = new TH2D("h2_Q2t_MCDEMPAcceptZDC", "Q^{2} vs -t MC Truth DEMP Accepted (ZDC events only); Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptZDC = new TH2D("h2_WQ2_MCDEMPAcceptZDC", "W vs Q^{2} MC Truth DEMP Accepted (ZDC events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptZDC_NoAB = new TH1D("h1_Q2_MCDEMPAcceptZDC_NoAB", "Q^{2} MC Truth DEMP Accepted (ZDC events only), No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptZDC_NoAB = new TH1D("h1_t_MCDEMPAcceptZDC_NoAB", "-t MC Truth DEMP Accepted (ZDC events only), No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptZDC_NoAB = new TH1D("h1_W_MCDEMPAcceptZDC_NoAB", "W MC Truth DEMP Accepted (ZDC events only), No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptZDC_NoAB = new TH1D("h1_eps_MCDEMPAcceptZDC_NoAB", "#epsilon MC Truth DEMP Accepted (ZDC events only), No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptZDC_NoAB = new TH1D("h1_y_MCDEMPAcceptZDC_NoAB", "y MC Truth DEMP Accepted (ZDC events only), No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_MCDEMPAcceptZDC_NoAB = new TH1D("h1_x_MCDEMPAcceptZDC_NoAB", "x MC Truth DEMP Accepted (ZDC events only), No Beam Effects; x; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptZDC_NoAB = new TH2D("h2_Q2t_MCDEMPAcceptZDC_NoAB", "Q^{2} vs -t MC Truth DEMP Accepted (ZDC events only), No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptZDC_NoAB = new TH2D("h2_WQ2_MCDEMPAcceptZDC_NoAB", "W vs Q^{2} MC Truth DEMP Accepted (ZDC events only), No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      gDirectory->cd("../../../");
      
      gDirectory->cd("KinematicDists/Reco/ZDC");
      TH1D* h1_Q2_ZDCReco_NoCuts = new TH1D("h1_Q2_ZDCReco_NoCuts", "Q^{2} Reconstructed (No Cuts, ZDC n events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_tBABE_ZDCReco_NoCuts = new TH1D("h1_tBABE_ZDCReco_NoCuts", "-t_{BABE} Reconstructed (Q^{2} Cuts Only, ZDC n events only); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teX_ZDCReco_NoCuts = new TH1D("h1_teX_ZDCReco_NoCuts", "-t_{eX} Reconstructed (Q^{2} Cuts Only, ZDC n events only); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXPT_ZDCReco_NoCuts = new TH1D("h1_teXPT_ZDCReco_NoCuts", "-t_{eXPT} Reconstructed (Q^{2} Cuts Only, ZDC n events only); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXBABE_ZDCReco_NoCuts = new TH1D("h1_teXBABE_ZDCReco_NoCuts", "-t_{eXBABE} Reconstructed (Q^{2} Cuts Only, ZDC n events only); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_ZDCReco_NoCuts = new TH1D("h1_W_ZDCReco_NoCuts", "W Reconstructed (No Cuts, ZDC n events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_ZDCReco_NoCuts = new TH1D("h1_eps_ZDCReco_NoCuts", "#epsilon Reconstructed (No Cuts, ZDC n events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_ZDCReco_NoCuts = new TH1D("h1_y_ZDCReco_NoCuts", "y_{DA} Reconstructed (No Cuts, ZDC n events only); y_{DA}; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_ZDCReco_NoCuts = new TH1D("h1_x_ZDCReco_NoCuts", "x_{DA} Reconstructed (No Cuts, ZDC n events only); x_{DA}; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_DeltaTheta_ZDCReco_NoCuts = new TH1D("h1_DeltaTheta_ZDCReco_NoCuts", "#Delta#theta (#theta_{pMiss} - #theta_{ZDC}) Reconstructed (Q^{2} Cuts Only, ZDC n events only); #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
      TH1D* h1_DeltaPhi_ZDCReco_NoCuts = new TH1D("h1_DeltaPhi_ZDCReco_NoCuts", "#Delta#phi (#phi_{pMiss} - #phi_{ZDC}) Reconstructed (Q^{2} Cuts Only, ZDC n events only); #Delta#phi (Deg); Rate/bin (Hz)", 200, -100, 100);
      TH1D* h1_MissMass_ZDCReco_NoCuts = new TH1D("h1_MissMass_ZDCReco_NoCuts", "Missing Mass Distribution, ZDC n events only, Reconstructed (Q^{2} Cut Only); Missing Mass (GeV/c^{2}); Rate/bin (Hz)", 100, -25, 25);
      TH2D* h2_Q2tBABE_ZDCReco_NoCuts = new TH2D("h2_Q2tBABE_ZDCReco_NoCuts", "Q^{2} vs -t_{BABE} Reconstructed (Q^{2} Cuts Only, ZDC n events only); Q^{2} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teX_ZDCReco_NoCuts = new TH2D("h2_Q2teX_ZDCReco_NoCuts", "Q^{2} vs -t_{eX} Reconstructed (Q^{2} Cuts Only, ZDC n events only); Q^{2} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXPT_ZDCReco_NoCuts = new TH2D("h2_Q2teXPT_ZDCReco_NoCuts", "Q^{2} vs -t_{eXPT} Reconstructed (Q^{2} Cuts Only, ZDC n events only); Q^{2} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXBABE_ZDCReco_NoCuts = new TH2D("h2_Q2teXBABE_ZDCReco_NoCuts", "Q^{2} vs -t_{eXBABE} Reconstructed (Q^{2} Cuts Only, ZDC n events only);  Q^{2} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_ZDCReco_NoCuts = new TH2D("h2_WQ2_ZDCReco_NoCuts", "W vs Q^{2} Reconstructed (No Cuts, ZDC n events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      TH2D* h2_DeltaThetaPhi_ZDCReco_NoCuts = new TH2D("h2_DeltaThetaPhi_ZDCReco_NoCuts", "#Delta#theta  (#theta_{pMiss} - #theta_{ZDC}) vs #Delta#phi (#phi_{pMiss} - #phi_{ZDC}) Reconstructed (Q^{2} Cuts only, ZDC n events only); #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);
      TH2D* h2_DeltaRotThetaRotPhi_ZDCReco_NoCuts = new TH2D("h2_DeltaRotThetaRotPhi_ZDCReco_NoCuts", "#Delta#theta^{*}  (#theta^{*}_{pMiss} - #theta^{*}_{ZDC}) vs #Delta#phi^{*} (#phi^{*}_{pMiss} - #phi^{*}_{ZDC}) Reconstructed (Q^{2} Cuts only, ZDC  n events only); #Delta#theta^{*} (Deg); #Delta#phi^{*} (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);

      TH1D* h1_Q2_ZDCReco = new TH1D("h1_Q2_ZDCReco", "Q^{2} Reconstructed (ZDC n events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_tBABE_ZDCReco = new TH1D("h1_tBABE_ZDCReco", "-t_{BABE} Reconstructed (ZDC n events only); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teX_ZDCReco = new TH1D("h1_teX_ZDCReco", "-t_{eX} Reconstructed (ZDC n events only); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXPT_ZDCReco = new TH1D("h1_teXPT_ZDCReco", "-t_{eXPT} Reconstructed (ZDC n events only); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXBABE_ZDCReco = new TH1D("h1_teXBABE_ZDCReco", "-t_{eXBABE} Reconstructed (ZDC n events only); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_ZDCReco = new TH1D("h1_W_ZDCReco", "W Reconstructed (ZDC n events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_ZDCReco = new TH1D("h1_eps_ZDCReco", "#epsilon Reconstructed (ZDC n events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_ZDCReco = new TH1D("h1_y_ZDCReco", "y_{DA} Reconstructed (ZDC n events only); y_{DA}; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_x_ZDCReco = new TH1D("h1_x_ZDCReco", "x_{DA} Reconstructed (ZDC n events only); x_{DA}; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_DeltaTheta_ZDCReco = new TH1D("h1_DeltaTheta_ZDCReco", "#Delta#theta (#theta_{pMiss} - #theta_{ZDC}) Reconstructed (ZDC n events only); #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
      TH1D* h1_DeltaPhi_ZDCReco = new TH1D("h1_DeltaPhi_ZDCReco", "#Delta#phi (#phi_{pMiss} - #phi_{ZDC}) Reconstructed (ZDC n events only); #Delta#phi (Deg); Rate/bin (Hz)", 200, -100, 100);
      TH1D* h1_MissMass_ZDCReco = new TH1D("h1_MissMass_ZDCReco", "Missing Mass Distribution, ZDC n events only; Missing Mass (GeV/c^{2}); Rate/bin (Hz)", 100, -25, 25);
      TH2D* h2_Q2tBABE_ZDCReco = new TH2D("h2_Q2tBABE_ZDCReco", "Q^{2} vs -t_{BABE} Reconstructed (ZDC n events only); Q^{2} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teX_ZDCReco = new TH2D("h2_Q2teX_ZDCReco", "Q^{2} vs -t_{eX} Reconstructed (ZDC n events only); Q^{2} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXPT_ZDCReco = new TH2D("h2_Q2teXPT_ZDCReco", "Q^{2} vs -t_{eXPT} Reconstructed (ZDC n events only); Q^{2} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXBABE_ZDCReco = new TH2D("h2_Q2teXBABE_ZDCReco", "Q^{2} vs -t_{eXBABE} Reconstructed (ZDC n events only);  Q^{2} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_ZDCReco = new TH2D("h2_WQ2_ZDCReco", "W vs Q^{2} Reconstructed (ZDC n events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      TH2D* h2_DeltaThetaPhi_ZDCReco = new TH2D("h2_DeltaThetaPhi_ZDCReco", "#Delta#theta  (#theta_{pMiss} - #theta_{ZDC}) vs #Delta#phi (#phi_{pMiss} - #phi_{ZDC}) Reconstruted (ZDC, n events only); #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);
      TH2D* h2_DeltaRotThetaRotPhi_ZDCReco = new TH2D("h2_DeltaRotThetaRotPhi_ZDCReco", "#Delta#theta^{*}  (#theta^{*}_{pMiss} - #theta^{*}_{ZDC}) vs #Delta#phi^{*} (#phi^{*}_{pMiss} - #phi^{*}_{ZDC}); #Delta#theta^{*} (Deg); #Delta#phi^{*} (Deg); Rate/bin (Hz)", 100, -1, 1, 200, -100, 100);
      gDirectory->cd("../../../");
    }
  }
  
  if (ZDC == kTRUE){
    gDirectory->cd("ZDCDists/MC");
    TH2D* h2_n_pTheta_MCAcceptZDC_NoAB = new TH2D("h2_n_pTheta_MCAcceptZDC_NoAB", "Neutron MC Truth Accepted (ZDC), No Cuts, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCAcceptZDC = new TH2D("h2_n_pTheta_MCAcceptZDC", "Neutron MC Truth Accepted (ZDC); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));

    TH2D* h2_eSc_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB = new TH2D("h2_eSc_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB", "e' MC Truth DEMP Accepted (ZDC), No Cuts, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB = new TH2D("h2_Pi_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB", "#pi MC Truth DEMP Accepted (ZDC), No Cuts, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB = new TH2D("h2_n_pTheta_MCDEMPAcceptZDC_NoCuts_NoAB", "Neutron MC Truth DEMP Accepted (ZDC), No Cuts, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_eSc_pTheta_MCDEMPAcceptZDC_NoCuts = new TH2D("h2_eSc_pTheta_MCDEMPAcceptZDC_NoCuts", "e' MC Truth DEMP Accepted (ZDC), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_MCDEMPAcceptZDC_NoCuts = new TH2D("h2_Pi_pTheta_MCDEMPAcceptZDC_NoCuts", "#pi MC Truth DEMP Accepted (ZDC), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_MCDEMPAcceptZDC_NoCuts = new TH2D("h2_n_pTheta_MCDEMPAcceptZDC_NoCuts", "Neutron MC Truth DEMP Accepted (ZDC), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));

    TH2D* h2_eSc_pTheta_MCDEMPAcceptZDC_NoAB = new TH2D("h2_eSc_pTheta_MCDEMPAcceptZDC_NoAB", "e' MC Truth DEMP Accepted (ZDC), No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_MCDEMPAcceptZDC_NoAB = new TH2D("h2_Pi_pTheta_MCDEMPAcceptZDC_NoAB", "#pi MC Truth DEMP Accepted (ZDC), No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_MCDEMPAcceptZDC_NoAB = new TH2D("h2_n_pTheta_MCDEMPAcceptZDC_NoAB", "Neutron MC Truth DEMP Accepted (ZDC), No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_eSc_pTheta_MCDEMPAcceptZDC = new TH2D("h2_eSc_pTheta_MCDEMPAcceptZDC", "e' MC Truth DEMP Accepted (ZDC); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_MCDEMPAcceptZDC = new TH2D("h2_Pi_pTheta_MCDEMPAcceptZDC", "#pi MC Truth DEMP Accepted (ZDC); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_MCDEMPAcceptZDC = new TH2D("h2_n_pTheta_MCDEMPAcceptZDC", "Neutron MC Truth DEMP Accepted (ZDC); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    gDirectory->cd("../../");
    
    gDirectory->cd("ZDCDists/Reco");
    TH2D* h2_eSc_pTheta_RecoDEMPAcceptZDC_NoCuts = new TH2D("h2_eSc_pTheta_RecoDEMPAcceptZDC_NoCuts", "e' Reconstructed DEMP Accepted (ZDC), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_RecoDEMPAcceptZDC_NoCuts = new TH2D("h2_Pi_pTheta_RecoDEMPAcceptZDC_NoCuts", "#pi Reconstructed DEMP Accepted (ZDC), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_RecoDEMPAcceptZDC_NoCuts = new TH2D("h2_n_pTheta_RecoDEMPAcceptZDC_NoCuts", "Neutron Reconstructed DEMP Accepted (ZDC), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_eSc_pTheta_RecoDEMPAcceptZDC = new TH2D("h2_eSc_pTheta_RecoDEMPAcceptZDC", "e' Reconstructed DEMP Accepted (ZDC); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_RecoDEMPAcceptZDC = new TH2D("h2_Pi_pTheta_RecoDEMPAcceptZDC", "#pi Reconstructed DEMP Accepted (ZDC); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_RecoDEMPAcceptZDC = new TH2D("h2_n_pTheta_RecoDEMPAcceptZDC", "Neutron Reconstructed DEMP Accepted (ZDC); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_XY_Reco = new TH2D("h2_n_XY_Reco", "Neutron reconstructed XY position at ZDC;x (mm) ;y (mm); Rate/bin (Hz)", 150,-1200,-600,150,-300,300);
    TH2D* h2_n_XY_RecoAccept = new TH2D("h2_n_XY_RecoAccept", "Neutron reconstructed XY position at ZDC;x (mm) ;y (mm); Rate/bin (Hz)", 150,-1200,-600,150,-300,300); 
    TH2D* h2_nRot_XY_Reco = new TH2D("h2_nRot_XY_Reco", "Neutron reconstructed (Rotated 25 mrad) XY position at ZDC;x (mm) ;y (mm); Rate/bin (Hz)", 100,-200,200,100,-200,200);
    TH2D* h2_nRot_XY_RecoAccept = new TH2D("h2_nRot_XY_RecoAccept", "Neutron reconstructed (Rotated 25 mrad) XY position at ZDC;x (mm) ;y (mm); Rate/bin (Hz)", 100,-200,200,100,-200,200);
    TH2D* h2_n_pTheta_RecoAcceptZDC = new TH2D("h2_n_pTheta_RecoAcceptZDC", "ZDC Reconstructed;#theta (Deg); p (GeV/c); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_nRot_pTheta_RecoAcceptoZDC = new TH2D("h2_nRot_pTheta_RecoAcceptZDC", "ZDC Reconstructed (Rotated 25 mrad);#theta (Deg); p (GeV/c); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_XY_10m_RecoDEMPAcceptZDC_NoCuts = new TH2D("h2_n_XY_10m_RecoDEMPAcceptZDC_NoCuts", "Neutron Reconstructed XY position (@10m, n in ZDC only); x (mm); y (mm); Rate/bin (hz)", 250,-500,0,200,-200,200);
    TH2D* h2_n_XY_10m_RecoDEMPAcceptZDC = new TH2D("h2_n_XY_10m_RecoDEMPAcceptZDC", "Neutron Reconstructed XY position (@10m, n in ZDC only); x (mm); y (mm); Rate/bin (hz)", 250,-500,0,200,-200,200);
    gDirectory->cd("../../");
  }
  
  if (B0 == kTRUE){
    gDirectory->cd("B0Dists/MC");
    TH2D* h2_n_pTheta_MCAcceptB0 = new TH2D("h2_n_pTheta_MCAcceptB0", "Neutron MC Truth Accepted (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCAcceptB0_NoAB = new TH2D("h2_n_pTheta_MCAcceptB0_NoAb", "Neutron MC Truth Accepted (B0), No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_eSc_pTheta_MCDEMPAcceptB0_NoCuts_NoAB = new TH2D("h2_eSc_pTheta_MCDEMPAcceptB0_NoCuts_NoAB", "e' MC Truth DEMP Accepted (B0), No Cuts, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_MCDEMPAcceptB0_NoCuts_NoAB = new TH2D("h2_Pi_pTheta_MCDEMPAcceptB0_NoCuts_NoAB", "#pi MC Truth DEMP Accepted (B0), No Cuts, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_MCDEMPAcceptB0_NoCuts_NoAB = new TH2D("h2_n_pTheta_MCDEMPAcceptB0_NoCuts_NoAB", "Neutron MC Truth DEMP Accepted (B0), No Cuts, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_eSc_pTheta_MCDEMPAcceptB0_NoCuts = new TH2D("h2_eSc_pTheta_MCDEMPAcceptB0_NoCuts", "e' MC Truth DEMP Accepted (B0), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_MCDEMPAcceptB0_NoCuts = new TH2D("h2_Pi_pTheta_MCDEMPAcceptB0_NoCuts", "#pi MC Truth DEMP Accepted (B0), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_MCDEMPAcceptB0_NoCuts = new TH2D("h2_n_pTheta_MCDEMPAcceptB0_NoCuts", "Neutron MC Truth DEMP Accepted (B0), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    
    TH2D* h2_eSc_pTheta_MCDEMPAcceptB0_NoAB = new TH2D("h2_eSc_pTheta_MCDEMPAcceptB0_NoAB", "e' MC Truth DEMP Accepted (B0), No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_MCDEMPAcceptB0_NoAB = new TH2D("h2_Pi_pTheta_MCDEMPAcceptB0_NoAB", "#pi MC Truth DEMP Accepted (B0), No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_MCDEMPAcceptB0_NoAB = new TH2D("h2_n_pTheta_MCDEMPAcceptB0_NoAB", "Neutron MC Truth DEMP Accepted (B0), No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_eSc_pTheta_MCDEMPAcceptB0 = new TH2D("h2_eSc_pTheta_MCDEMPAcceptB0", "e' MC Truth DEMP Accepted (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_MCDEMPAcceptB0 = new TH2D("h2_Pi_pTheta_MCDEMPAcceptB0", "#pi MC Truth DEMP Accepted (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_MCDEMPAcceptB0 = new TH2D("h2_n_pTheta_MCDEMPAcceptB0", "Neutron MC Truth DEMP Accepted (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_B0_XY_MCAccept = new TH2D("h2_B0_XY_MCAccept", "B0 MC Accepted XY Hit Position; x (mm); y(mm); Rate/bin (Hz)", 75, -325, -25, 75, -150, 150);
    gDirectory->cd("../../");

    gDirectory->cd("B0Dists/Reco");
    TH1D* h1_B0_nClusters = new TH1D("h1_B0_nClusters", "B0 Hit Multiplicity; N_{Clus}", 30, 0, 30);
    TH2D* h2_B0_XY_Raw = new TH2D("h2_B0_XY_Raw", "B0 XY Hit Position, raw all clusters; x (mm); y(mm)", 75, -325, -25, 75, -150, 150);
    TH2D* h2_B0_XY_Raw_EWeight = new TH2D("h2_B0_XY_Raw_EWeight", "B0 XY Hit Position, raw all clusters, energy weighted; x (mm); y(mm)", 75, -325, -25, 75, -150, 150);
    TH1D* h1_B0_nClusters_AcceptRaw = new TH1D("h1_B0_nClusters_AcceptRaw", "B0 Hit Multiplicity, number of clusters in event; N_{Clus}", 30, 0, 30);
    TH1D* h1_B0_nClusters_Accept = new TH1D("h1_B0_nClusters_Accept", "B0 Hit Multiplicity, number of accepted cluters; N_{Clus}", 30, 0, 30);
    TH2D* h2_B0_XY_Accept = new TH2D("h2_B0_XY_Accept", "B0 Reconstructed XY Hit Position; x (mm); y(mm)", 75, -325, -25, 75, -150, 150);
    TH2D* h2_B0_XY_AcceptWeighted = new TH2D("h2_B0_XY_AcceptWeighted", "B0 Reconstructed XY Hit Position; x (mm); y(mm); Rate/bin (Hz)", 75, -325, -25, 75, -150, 150);
    TH2D* h2_n_ETheta_RecoAcceptB0 = new TH2D("h2_n_ETheta_RecoAcceptB0", "B0 Reconstructed;#theta (Deg); E (GeV)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_RecoAcceptB0 = new TH2D("h2_n_pTheta_RecoAcceptB0", "B0 Reconstructed;#theta (Deg); p (GeV/c); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_nRot_pTheta_RecoAcceptB0 = new TH2D("h2_nRot_pTheta_RecoAcceptB0", "B0 Reconstructed (Rotated 25 mrad);#theta (Deg); p (GeV/c); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_eSc_pTheta_RecoDEMPAcceptB0_NoCuts = new TH2D("h2_eSc_pTheta_RecoDEMPAcceptB0_NoCuts", "e' Reconstructed DEMP Accepted (B0), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_RecoDEMPAcceptB0_NoCuts = new TH2D("h2_Pi_pTheta_RecoDEMPAcceptB0_NoCuts", "#pi Reconstructed DEMP Accepted (B0), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_RecoDEMPAcceptB0_NoCuts = new TH2D("h2_n_pTheta_RecoDEMPAcceptB0_NoCuts", "Neutron Reconstructed DEMP Accepted (B0), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_eSc_pTheta_RecoDEMPAcceptB0 = new TH2D("h2_eSc_pTheta_RecoDEMPAcceptB0", "e' Reconstructed DEMP Accepted (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_RecoDEMPAcceptB0 = new TH2D("h2_Pi_pTheta_RecoDEMPAcceptB0", "#pi Reconstructed DEMP Accepted (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_RecoDEMPAcceptB0 = new TH2D("h2_n_pTheta_RecoDEMPAcceptB0", "Neutron Reconstructed DEMP Accepted (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_XY_10m_RecoDEMPAcceptB0_NoCuts = new TH2D("h2_n_XY_10m_RecoDEMPAcceptB0_NoCuts", "Neutron Reconstructed XY position (@10m, n in B0 only); x (mm); y (mm); Rate/bin (hz)",250,-500,0,200,-200,200);
    TH2D* h2_n_XY_10m_RecoDEMPAcceptB0 = new TH2D("h2_n_XY_10m_RecoDEMPAcceptB0", "Neutron Reconstructed XY position (@10m, n in B0 only); x (mm); y (mm); Rate/bin (hz)",250,-500,0,200,-200,200);
    gDirectory->cd("../../");     
  }
  
  if (QA == kTRUE){
    gDirectory->cd("QADists/Kin");
    TH1D* h1_tBABE_Res_QA = new TH1D("h1_tBABE_Res_QA", "-t_{BABE} Resolution (%); (t_{BABE} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
    TH1D* h1_teX_Res_QA = new TH1D("h1_teX_Res_QA", "-t_{eX} Resolution (%); (t_{eX} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
    TH1D* h1_teXPT_Res_QA = new TH1D("h1_teXPT_Res_QA", "-t_{eXPT} Resolution (%); (t_{eXPT} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
    TH1D* h1_teXBABE_Res_QA = new TH1D("h1_teXBABE_Res_QA", "-t_{eXBABE} Resolution (%); (t_{eXBABE} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
    TH1D* h1_Q2_Res_QA = new TH1D("h1_Q2_Res_QA", "Q^{2} Resolution (%); (Q^{2} - Q^{2}_{MC})/Q^{2}_{MC} (%); Rate/1% bin (Hz)", 60, -30, 30);
    TH1D* h1_W_Res_QA = new TH1D("h1_W_Res_QA", "W Resolution (%); (W - W_{MC})/W_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
    if (ZDC == kTRUE){
      TH1D* h1_tBABE_Res_QA_ZDC = new TH1D("h1_tBABE_Res_QA_ZDC", "-t_{BABE} Resolution (%), n ZDC Hits Only; (t_{BABE} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
      TH1D* h1_teX_Res_QA_ZDC = new TH1D("h1_teX_Res_QA_ZDC", "-t_{eX} Resolution (%), n ZDC Hits Only; (t_{eX} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
      TH1D* h1_teXPT_Res_QA_ZDC = new TH1D("h1_teXPT_Res_QA_ZDC", "-t_{eXPT} Resolution (%), n ZDC Hits Only; (t_{eXPT} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
      TH1D* h1_teXBABE_Res_QA_ZDC = new TH1D("h1_teXBABE_Res_QA_ZDC", "-t_{eXBABE} Resolution (%), n ZDC Hits Only; (t_{eXBABE} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
      TH1D* h1_Q2_Res_QA_ZDC = new TH1D("h1_Q2_Res_QA_ZDC", "Q^{2} Resolution (%), n ZDC Hits Only; (Q^{2} - Q^{2}_{MC})/Q^{2}_{MC} (%); Rate/1% bin (Hz)", 60, -30, 30);
      TH1D* h1_W_Res_QA_ZDC = new TH1D("h1_W_Res_QA_ZDC", "W Resolution (%), n ZDC Hits Only; (W - W_{MC})/W_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
    }
    if (B0 == kTRUE){
      TH1D* h1_tBABE_Res_QA_B0 = new TH1D("h1_tBABE_Res_QA_B0", "-t_{BABE} Resolution (%), n B0 Hits Only; (t_{BABE} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
      TH1D* h1_teX_Res_QA_B0 = new TH1D("h1_teX_Res_QA_B0", "-t_{eX} Resolution (%), n B0 Hits Only; (t_{eX} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
      TH1D* h1_teXPT_Res_QA_B0 = new TH1D("h1_teXPT_Res_QA_B0", "-t_{eXPT} Resolution (%), n B0 Hits Only; (t_{eXPT} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
      TH1D* h1_teXBABE_Res_QA_B0 = new TH1D("h1_teXBABE_Res_QA_B0", "-t_{eXBABE} Resolution (%), n B0 Hits Only; (t_{eXBABE} - t_{MC})/t_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
      TH1D* h1_Q2_Res_QA_B0 = new TH1D("h1_Q2_Res_QA_B0", "Q^{2} Resolution (%), n B0 Hits Only; (Q^{2} - Q^{2}_{MC})/Q^{2}_{MC} (%); Rate/1% bin (Hz)", 600, -30, 30);
      TH1D* h1_W_Res_QA_B0 = new TH1D("h1_W_Res_QA_B0", "W Resolution (%), n B0 Hits Only; (W - W_{MC})/W_{MC} (%); Rate/1% bin (Hz)", 400, -200, 200);
    }
    gDirectory->cd("../../");
    gDirectory->cd("QADists/PartRes");
    TH1D* h1_eSc_p_Res_QA = new TH1D("h1_eSc_p_Res_QA", "e' Track Momentum Resolution (%); (P_{Rec} - P_{MC})/P_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
    TH1D* h1_Pi_p_Res_QA = new TH1D("h1_Pi_p_Res_QA", "#pi Track Momentum Resolution (%); (P_{Rec} - P_{MC})/P_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
    TH1D* h1_n_p_Res_QA = new TH1D("h1_n_p_Res_QA", "n Track Momentum Resolution (%); (P_{Rec} - P_{MC})/P_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
    TH1D* h1_n_Theta_Res_QA = new TH1D("h1_n_Theta_Res_QA", "n #theta Resolution (%); (#theta_{Rec} - #theta_{MC})/#theta_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
    TH1D* h1_n_Phi_Res_QA = new TH1D("h1_n_Phi_Res_QA", "n #phi Resolution (%); (#phi_{Rec} - #phi_{MC})/#phi_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
    if (ZDC == kTRUE){
      TH1D* h1_eSc_p_Res_QA_ZDC = new TH1D("h1_eSc_p_Res_QA_ZDC", "e' Track Momentum Resolution, ZDC n Hits Only (%), (P_{Rec} - P_{MC})/P_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
      TH1D* h1_Pi_p_Res_QA_ZDC = new TH1D("h1_Pi_p_Res_QA_ZDC", "#pi Track Momentum Resolution, ZDC n Hits Only (%), (P_{Rec} - P_{MC})/P_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
      TH1D* h1_n_p_Res_QA_ZDC = new TH1D("h1_n_p_Res_QA_ZDC", "n Track Momentum Resolution, ZDC n Hits Only (%), (P_{Rec} - P_{MC})/P_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
      TH1D* h1_n_Theta_Res_QA_ZDC = new TH1D("h1_n_Theta_Res_QA_ZDC", "n #theta Resolution, ZDC n Hits Only (%), (#theta_{Rec} - #theta_{MC})/#theta_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
      TH1D* h1_n_Phi_Res_QA_ZDC = new TH1D("h1_n_Phi_Res_QA_ZDC", "n #phi Resolution, ZDC n Hits Only (%), (#phi_{Rec} - #phi_{MC})/#phi_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
    }
    if (B0 == kTRUE){
      TH1D* h1_eSc_p_Res_QA_B0 = new TH1D("h1_eSc_p_Res_QA_B0", "e' Track Momentum Resolution, B0 n Hits Only (%), (P_{Rec} - P_{MC})/P_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
      TH1D* h1_Pi_p_Res_QA_B0 = new TH1D("h1_Pi_p_Res_QA_B0", "#pi Track Momentum Resolution, B0 n Hits Only (%), (P_{Rec} - P_{MC})/P_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
      TH1D* h1_n_p_Res_QA_B0 = new TH1D("h1_n_p_Res_QA_B0", "n Track Momentum Resolution, B0 n Hits Only (%), (P_{Rec} - P_{MC})/P_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
      TH1D* h1_n_Theta_Res_QA_B0 = new TH1D("h1_n_Theta_Res_QA_B0", "n #theta Resolution, B0 n Hits Only (%), (#theta_{Rec} - #theta_{MC})/#theta_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
      TH1D* h1_n_Phi_Res_QA_B0 = new TH1D("h1_n_Phi_Res_QA_B0", "n #phi Resolution, B0 n Hits Only (%), (#phi_{Rec} - #phi_{MC})/#phi_{MC} (%); Rate/1% Bin (Hz)", 100, -50, 50);
    }
    gDirectory->cd("../../");
    gDirectory->cd("QADists/Efficiencies");
    TH1D* h1_eSc_eta_eff_Raw = new TH1D("h1_eSc_eta_eff_Raw", "e' #eta, Raw; #eta; Rate/0.05 bin (Hz)", 80, -4, 0);
    TH1D* h1_eSc_eta_eff_Accept = new TH1D("h1_eSc_eta_eff_Accept", "e' #eta, Accepted; #eta; Rate/0.05 bin (Hz)", 80, -4, 0);
    TH1D* h1_eSc_eta_eff_DEMPAccept = new TH1D("h1_eSc_eta_eff_DEMPAccept", "e' #eta, DEMP Accepted; #eta; Rate/0.05 bin (Hz)", 80, -4, 0);
    TH1D* h1_eSc_eta_eff_DEMPCut = new TH1D("h1_eSc_eta_eff_DEMPCut", "e' #eta, DEMP Cut Accepted; #eta; Rate/0.05 bin (Hz)", 80, -4, 0);
    TH1D* h1_eSc_eta_eff = new TH1D("h1_eSc_eta_eff", "e' #eta Detction Efficiency; #eta; Efficiency", 80, -4, 0);
    TH1D* h1_eSc_eta_effDEMP = new TH1D("h1_eSc_eta_effDEMP", "e' #eta Detection Efficiency, DEMP Accepted; #eta; Efficiency", 80, -4, 0);
    TH1D* h1_eSc_eta_effDEMPCut = new TH1D("h1_eSc_eta_effDEMPCut", "e' #eta Detection, DEMP Cut Accepted; #eta; Efficiency", 80, -4, 0);
    TH1D* h1_eSc_p_eff_Raw = new TH1D("h1_eSc_p_eff_Raw", "e' P, Raw; P (GeV/C); Rate/bin (Hz)", NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH1D* h1_eSc_p_eff_Accept = new TH1D("h1_eSc_p_eff_Accept", "e' P, Accepted; P (GeV/C); Rate/bin (Hz)", NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH1D* h1_eSc_p_eff_DEMPAccept = new TH1D("h1_eSc_p_eff_DEMPAccept", "e' P, DEMP Accepted; P (GeV/C); Rate/bin (Hz)", NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH1D* h1_eSc_p_eff_DEMPCut = new TH1D("h1_eSc_p_eff_DEMPCut", "e' P, DEMP Cut Accepted; P (GeV/C); Rate/bin (Hz)", NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH1D* h1_eSc_p_eff = new TH1D("h1_eSc_p_eff", "e' P Detction Efficiency; P (GeV/C); Efficiency", NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH1D* h1_eSc_p_effDEMP = new TH1D("h1_eSc_p_effDEMP", "e' P Detection Efficiency, DEMP Accepted; P (GeV/C); Efficiency", NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH1D* h1_eSc_p_effDEMPCut = new TH1D("h1_eSc_p_effDEMPCut", "e' P Detection, DEMP Cut Accepted; P (GeV/C); Efficiency", NBins_Energy, ElecBeamE-1, ElecBeamE+2);

    TH1D* h1_Pi_eta_eff_Raw = new TH1D("h1_Pi_eta_eff_Raw", "#pi #eta, Raw; #eta; Rate/0.05 bin (Hz)", 120, -1, 5);
    TH1D* h1_Pi_eta_eff_Accept = new TH1D("h1_Pi_eta_eff_Accept", "#pi #eta, Accepted; #eta; Rate/0.05 bin (Hz)", 120, -1, 5);
    TH1D* h1_Pi_eta_eff_DEMPAccept = new TH1D("h1_Pi_eta_eff_DEMPAccept", "#pi #eta, DEMP Accepted; #eta; Rate/0.05 bin (Hz)", 120, -1, 5);
    TH1D* h1_Pi_eta_eff_DEMPCut = new TH1D("h1_Pi_eta_eff_DEMPCut", "#pi #eta, DEMP Cut Accepted; #eta; Rate/0.05 bin (Hz)", 120, -1, 5);
    TH1D* h1_Pi_eta_eff = new TH1D("h1_Pi_eta_eff", "#pi #eta Detction Efficiency; #eta; Efficiency", 120, -1, 5);
    TH1D* h1_Pi_eta_effDEMP = new TH1D("h1_Pi_eta_effDEMP", "#pi #eta Detection Efficiency, DEMP Accepted; #eta; Efficiency", 120, -1, 5);
    TH1D* h1_Pi_eta_effDEMPCut = new TH1D("h1_Pi_eta_effDEMPCut", "#pi #eta Detection, DEMP Cut Accepted; #eta; Efficiency", 120, -1, 5);
    TH1D* h1_Pi_p_eff_Raw = new TH1D("h1_Pi_p_eff_Raw", "#pi P, Raw; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, 100);
    TH1D* h1_Pi_p_eff_Accept = new TH1D("h1_Pi_p_eff_Accept", "#pi P, Accepted; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, 100);
    TH1D* h1_Pi_p_eff_DEMPAccept = new TH1D("h1_Pi_p_eff_DEMPAccept", "#pi P, DEMP Accepted; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, 100);
    TH1D* h1_Pi_p_eff_DEMPCut = new TH1D("h1_Pi_p_eff_DEMPCut", "#pi P, DEMP Cut Accepted; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, 100);
    TH1D* h1_Pi_p_eff = new TH1D("h1_Pi_p_eff", "#pi P Detction Efficiency; P (GeV/C); Efficiency", NBins_Energy, 0, 100);
    TH1D* h1_Pi_p_effDEMP = new TH1D("h1_Pi_p_effDEMP", "#pi P Detection Efficiency, DEMP Accepted; P (GeV/C); Efficiency", NBins_Energy, 0, 100);
    TH1D* h1_Pi_p_effDEMPCut = new TH1D("h1_Pi_p_effDEMPCut", "#pi P Detection, DEMP Cut Accepted; P (GeV/C); Efficiency", NBins_Energy, 0, 100);
    
    TH1D* h1_n_eta_eff_Raw = new TH1D("h1_n_eta_eff_Raw", "n #eta, Raw; #eta; Rate/0.05 bin (Hz)", 60, 3, 6);
    TH1D* h1_n_eta_eff_Accept = new TH1D("h1_n_eta_eff_Accept", "n #eta, Accepted; #eta; Rate/0.05 bin (Hz)", 60, 3, 6);
    TH1D* h1_n_eta_eff_DEMPAccept = new TH1D("h1_n_eta_eff_DEMPAccept", "n #eta, DEMP Accepted; #eta; Rate/0.05 bin (Hz)", 60, 3, 6);
    TH1D* h1_n_eta_eff_DEMPCut = new TH1D("h1_n_eta_eff_DEMPCut", "n #eta, DEMP Cut Accepted; #eta; Rate/0.05 bin (Hz)", 60, 3, 6);
    TH1D* h1_n_eta_eff = new TH1D("h1_n_eta_eff", "n #eta Detction Efficiency; #eta; Efficiency", 60, 3, 6);
    TH1D* h1_n_eta_effDEMP = new TH1D("h1_n_eta_effDEMP", "n #eta Detection Efficiency, DEMP Accepted; #eta; Efficiency", 60, 3, 6);
    TH1D* h1_n_eta_effDEMPCut = new TH1D("h1_n_eta_effDEMPCut", "n #eta Detection, DEMP Cut Accepted; #eta; Efficiency", 60, 3, 6);
    TH1D* h1_n_p_eff_Raw = new TH1D("h1_n_p_eff_Raw", "n P, Raw; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH1D* h1_n_p_eff_Accept = new TH1D("h1_n_p_eff_Accept", "n P, Accepted; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH1D* h1_n_p_eff_DEMPAccept = new TH1D("h1_n_p_eff_DEMPAccept", "n P, DEMP Accepted; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH1D* h1_n_p_eff_DEMPCut = new TH1D("h1_n_p_eff_DEMPCut", "n P, DEMP Cut Accepted; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH1D* h1_n_p_eff = new TH1D("h1_n_p_eff", "n P Detction Efficiency; P (GeV/C); Efficiency", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH1D* h1_n_p_effDEMP = new TH1D("h1_n_p_effDEMP", "n P Detection Efficiency, DEMP Accepted; P (GeV/C); Efficiency", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH1D* h1_n_p_effDEMPCut = new TH1D("h1_n_p_effDEMPCut", "n P Detection, DEMP Cut Accepted; P (GeV/C); Efficiency", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));

    TH2D* h2_Q2t_eff_Raw = new TH2D("h2_Q2t_eff_Raw", "Q^{2} vs -t, Raw; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2t_eff_DEMPAccept = new TH2D("h2_Q2t_eff_DEMPAccept", "Q^{2} vs -t, DEMP Accepted; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2t_eff_DEMPCut = new TH2D("h2_Q2t_eff_DEMPCut", "Q^{2} vs -t, DEMP Cut; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2t_effDEMP = new TH2D("h2_Q2t_effDEMP", "Q^{2} vs -t Efficiency, DEMP Accpeted; Q^{2} (GeV^{2}); -t (GeV^{2}); Efficiency", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2t_effDEMPCut = new TH2D("h2_Q2t_effDEMPCut", "Q^{2} vs -t Efficiency, DEMP Cut; Q^{2} (GeV^{2}); -t (GeV^{2}); Efficiency", 40, 0, 40, 40, 0, 1.6);

    if (ZDC == kTRUE){
      TH1D* h1_n_eta_eff_AcceptZDC = new TH1D("h1_n_eta_eff_AcceptZDC", "n #eta, Accepted, n in ZDC; #eta; Rate/0.05 bin (Hz)", 60, 3, 6);
      TH1D* h1_n_eta_eff_DEMPAcceptZDC = new TH1D("h1_n_eta_eff_DEMPAcceptZDC", "n #eta, DEMP Accepted, n in ZDC; #eta; Rate/0.05 bin (Hz)", 60, 3, 6);
      TH1D* h1_n_eta_eff_DEMPCutZDC = new TH1D("h1_n_eta_eff_DEMPCutZDC", "n #eta, DEMP Cut Accepted, n in ZDC; #eta; Rate/0.05 bin (Hz)", 60, 3, 6);
      TH1D* h1_n_eta_eff_ZDC = new TH1D("h1_n_eta_eff_ZDC", "n #eta Detction Efficiency, n in ZDC; #eta; Efficiency", 60, 3, 6);
      TH1D* h1_n_eta_effDEMP_ZDC = new TH1D("h1_n_eta_effDEMP_ZDC", "n #eta Detection Efficiency, n in ZDC, DEMP Accepted; #eta; Efficiency", 60, 3, 6);
      TH1D* h1_n_eta_effDEMPCut_ZDC = new TH1D("h1_n_eta_effDEMPCut_ZDC", "n #eta Detection, DEMP Cut Accepted, n in ZDC; #eta; Efficiency", 60, 3, 6);
      TH1D* h1_n_p_eff_AcceptZDC = new TH1D("h1_n_p_eff_AcceptZDC", "n P, Accepted, n in ZDC; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH1D* h1_n_p_eff_DEMPAcceptZDC = new TH1D("h1_n_p_eff_DEMPAcceptZDC", "n P, DEMP Accepted, n in ZDC; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH1D* h1_n_p_eff_DEMPCutZDC = new TH1D("h1_n_p_eff_DEMPCutZDC", "n P, DEMP Cut Accepted, n in ZDC; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH1D* h1_n_p_eff_ZDC = new TH1D("h1_n_p_eff_ZDC", "n P Detction Efficiency, n in ZDC; P (GeV/C); Efficiency", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH1D* h1_n_p_effDEMP_ZDC = new TH1D("h1_n_p_effDEMP_ZDC", "n P Detection Efficiency, DEMP Accepted, n in ZDC; P (GeV/C); Efficiency", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH1D* h1_n_p_effDEMPCut_ZDC = new TH1D("h1_n_p_effDEMPCut_ZDC", "n P Detection, DEMP Cut Accepted, n in ZDC; P (GeV/C); Efficiency", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH2D* h2_Q2t_eff_DEMPAcceptZDC = new TH2D("h2_Q2t_eff_DEMPAcceptZDC", "Q^{2} vs -t, DEMP Accepted, n in ZDC; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2t_eff_DEMPCutZDC = new TH2D("h2_Q2t_eff_DEMPCutZDC", "Q^{2} vs -t, DEMP Cut,  n in ZDC; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2t_effDEMP_ZDC = new TH2D("h2_Q2t_effDEMP_ZDC", "Q^{2} vs -t Efficiency, DEMP Accpeted,  n in ZDC; Q^{2} (GeV^{2}); -t (GeV^{2}); Efficiency", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2t_effDEMPCut_ZDC = new TH2D("h2_Q2t_effDEMPCut_ZDC", "Q^{2} vs -t Efficiency, DEMP Cut,  n in ZDC; Q^{2} (GeV^{2}); -t (GeV^{2}); Efficiency", 40, 0, 40, 40, 0, 1.6);
    }
    if (B0 == kTRUE){
      TH1D* h1_n_eta_eff_AcceptB0 = new TH1D("h1_n_eta_eff_AcceptB0", "n #eta, Accepted, n in B0; #eta; Rate/0.05 bin (Hz)", 60, 3, 6);
      TH1D* h1_n_eta_eff_DEMPAcceptB0 = new TH1D("h1_n_eta_eff_DEMPAcceptB0", "n #eta, DEMP Accepted, n in B0; #eta; Rate/0.05 bin (Hz)", 60, 3, 6);
      TH1D* h1_n_eta_eff_DEMPCutB0 = new TH1D("h1_n_eta_eff_DEMPCutB0", "n #eta, DEMP Cut Accepted, n in B0; #eta; Rate/0.05 bin (Hz)", 60, 3, 6);
      TH1D* h1_n_eta_eff_B0 = new TH1D("h1_n_eta_eff_B0", "n #eta Detction Efficiency, n in B0; #eta; Efficiency", 60, 3, 6);
      TH1D* h1_n_eta_effDEMP_B0 = new TH1D("h1_n_eta_effDEMP_B0", "n #eta Detection Efficiency, n in B0, DEMP Accepted; #eta; Efficiency", 60, 3, 6);
      TH1D* h1_n_eta_effDEMPCut_B0 = new TH1D("h1_n_eta_effDEMPCut_B0", "n #eta Detection, DEMP Cut Accepted, n in B0; #eta; Efficiency", 60, 3, 6  );
      TH1D* h1_n_p_eff_AcceptB0 = new TH1D("h1_n_p_eff_AcceptB0", "n P, Accepted, n in B0; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH1D* h1_n_p_eff_DEMPAcceptB0 = new TH1D("h1_n_p_eff_DEMPAcceptB0", "n P, DEMP Accepted, n in B0; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH1D* h1_n_p_eff_DEMPCutB0 = new TH1D("h1_n_p_eff_DEMPCutB0", "n P, DEMP Cut Accepted, n in B0; P (GeV/C); Rate/bin (Hz)", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH1D* h1_n_p_eff_B0 = new TH1D("h1_n_p_eff_B0", "n P Detction Efficiency, n in B0; P (GeV/C); Efficiency", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH1D* h1_n_p_effDEMP_B0 = new TH1D("h1_n_p_effDEMP_B0", "n P Detection Efficiency, DEMP Accepted, n in B0; P (GeV/C); Efficiency", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH1D* h1_n_p_effDEMPCut_B0 = new TH1D("h1_n_p_effDEMPCut_B0", "n P Detection, DEMP Cut Accepted, n in B0; P (GeV/C); Efficiency", NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
      TH2D* h2_Q2t_eff_DEMPAcceptB0 = new TH2D("h2_Q2t_eff_DEMPAcceptB0", "Q^{2} vs -t, DEMP Accepted, n in B0; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2t_eff_DEMPCutB0 = new TH2D("h2_Q2t_eff_DEMPCutB0", "Q^{2} vs -t, DEMP Cut,  n in B0; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2t_effDEMP_B0 = new TH2D("h2_Q2t_effDEMP_B0", "Q^{2} vs -t Efficiency, DEMP Accpeted,  n in B0; Q^{2} (GeV^{2}); -t (GeV^{2}); Efficiency", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2t_effDEMPCut_B0 = new TH2D("h2_Q2t_effDEMPCut_B0", "Q^{2} vs -t Efficiency, DEMP Cut,  n in B0; Q^{2} (GeV^{2}); -t (GeV^{2}); Efficiency", 40, 0, 40, 40, 0, 1.6);

    }   
    gDirectory->cd("../../");
    gDirectory->cd("QADists/tComp");
    TH2D* h2_tBABEComp = new TH2D("h2_tBABEComp", "-t_{BABE} vs -t_{MC}; -t_{BABE} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 40, 0, 1.6, 40, 0, 1.6);
    TH2D* h2_teXComp = new TH2D("h2_teXComp", "-t_{eX} vs -t_{MC}; -t_{eX} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 40, 0, 1.6, 40, 0, 1.6);
    TH2D* h2_teXPTComp = new TH2D("h2_teXPTComp", "-t_{eXPT} vs -t_{MC}; -t_{eXPT} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 40, 0, 1.6, 40, 0, 1.6);
    TH2D* h2_teXBABECompAlt = new TH2D("h2_teXBABECompAlt", "-t_{eXBABE} vs -t_{MC}; -t_{eXBABE} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 50, 0, 0.5, 50, 0, 0.5);
    if(ZDC == kTRUE){
      TH2D* h2_tBABEComp_ZDC = new TH2D("h2_tBABEComp_ZDC", "-t_{BABE} vs -t_{MC}, n ZDC Hits; -t_{BABE} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 40, 0, 1.6, 40, 0, 1.6);
      TH2D* h2_teXComp_ZDC = new TH2D("h2_teXComp_ZDC", "-t_{eX} vs -t_{MC}, n ZDC Hits; -t_{eX} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 40, 0, 1.6, 40, 0, 1.6);
      TH2D* h2_teXPTComp_ZDC = new TH2D("h2_teXPTComp_ZDC", "-t_{eXPT} vs -t_{MC}, n ZDC Hits; -t_{eXPT} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 40, 0, 1.6, 40, 0, 1.6);
      TH2D* h2_teXBABEComp_ZDC = new TH2D("h2_teXBABEComp_ZDC", "-t_{eXBABE} vs -t_{MC}, n ZDC Hits; -t_{eXBABE} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 40, 0, 1.6, 40, 0, 1.6);
      TH2D* h2_teXBABECompAlt_ZDC = new TH2D("h2_teXBABECompAlt_ZDC", "-t_{eXBABE} vs -t_{MC}, n ZDC Hits; -t_{eXBABE} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 50, 0, 0.5, 50, 0, 0.5);
    }
    if(B0 == kTRUE){
      TH2D* h2_tBABEComp_B0 = new TH2D("h2_tBABEComp_B0", "-t_{BABE} vs -t_{MC}, n B0 Hits; -t_{BABE} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 40, 0, 1.6, 40, 0, 1.6);
      TH2D* h2_teXComp_B0 = new TH2D("h2_teXComp_B0", "-t_{eX} vs -t_{MC}, n B0 Hits; -t_{eX} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 40, 0, 1.6, 40, 0, 1.6);
      TH2D* h2_teXPTComp_B0 = new TH2D("h2_teXPTComp_B0", "-t_{eXPT} vs -t_{MC}, n B0 Hits; -t_{eXPT} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 40, 0, 1.6, 40, 0, 1.6);
      TH2D* h2_teXBABEComp_B0 = new TH2D("h2_teXBABEComp_B0", "-t_{eXBABE} vs -t_{MC}, n B0 Hits; -t_{eXBABE} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 40, 0, 1.6, 40, 0, 1.6);
      TH2D* h2_teXBABECompAlt_B0 = new TH2D("h2_teXBABECompAlt_B0", "-t_{eXBABE} vs -t_{MC}, n B0 Hits; -t_{eXBABE} (GeV/c); -t_{MC} (GeV/c); Rate/bin (Hz)", 50, 0, 0.5, 50, 0, 0.5);
    }
    gDirectory->cd("../../");
    gDirectory->cd("QADists/Q2_Alt");
    TH1D* h1_QA_Q2Rec = new TH1D("h1_QA_Q2Rec", "Q^{2}_{Rec} Distribution;Q^{2}_{Rec} (GeV/c^{2});Rate/bin(Hz) ", 100, 0, 50);
    TH1D* h1_QA_Q2JB = new TH1D("h1_QA_Q2JB", "Q^{2}_{JB} Distribution;Q^{2}_{JB} (GeV/c^{2});Rate/bin(Hz) ", 100, 0, 50);
    TH1D* h1_QA_Q2DA = new TH1D("h1_QA_Q2DA", "Q^{2}_{DA} Distribution;Q^{2}_{DA} (GeV/c^{2});Rate/bin(Hz) ", 100, 0, 50);
    TH1D* h1_QA_Q2Sig = new TH1D("h1_QA_Q2Sig", "Q^{2}_{Sig} Distribution;Q^{2}_{Sig} (GeV/c^{2});Rate/bin(Hz) ", 100, 0, 50);
    TH1D* h1_QA_yRec = new TH1D("h1_QA_yRec", "y_{Rec} Distribution;y_{Rec};Rate/bin(Hz) ", 100, 0, 1);
    TH1D* h1_QA_yJB = new TH1D("h1_QA_yJB", "y_{JB} Distribution;y_{JB};Rate/bin(Hz) ", 100, 0, 1);
    TH1D* h1_QA_yDA = new TH1D("h1_QA_yDA", "y_{DA} Distribution;y_{DA};Rate/bin(Hz) ", 100, 0, 1);
    TH1D* h1_QA_ySig = new TH1D("h1_QA_ySig", "y_{Sig} Distribution;y_{Sig};Rate/bin(Hz) ", 100, 0, 1);
    TH1D* h1_QA_xRec = new TH1D("h1_QA_xRec", "x_{Rec} Distribution;x_{Rec};Rate/bin(Hz) ", 100, 0, 1);
    TH1D* h1_QA_xJB = new TH1D("h1_QA_xJB", "x_{JB} Distribution;x_{JB};Rate/bin(Hz) ", 100, 0, 1);
    TH1D* h1_QA_xDA = new TH1D("h1_QA_xDA", "x_{DA} Distribution;x_{DA};Rate/bin(Hz) ", 100, 0, 1);
    TH1D* h1_QA_xSig = new TH1D("h1_QA_xSig", "x_{Sig} Distribution;x_{Sig};Rate/bin(Hz) ", 100, 0, 1);
    TH1D* h1_QA_Q2Rec_Res = new TH1D("h1_QA_Q2Rec_Res", "Q^{2}_{Rec} Resolution;100*(Q^{2}_{Rec}-Q^{2}_{MC})/Q^{2}_{MC};Rate/bin(Hz) ", 200, -100, 100);
    TH1D* h1_QA_Q2JB_Res = new TH1D("h1_QA_Q2JB_Res", "Q^{2}_{JB} Resolution;100*(Q^{2}_{JB}-Q^{2}_{MC})/Q^{2}_{MC};Rate/bin(Hz) ", 200, -100, 100);
    TH1D* h1_QA_Q2DA_Res = new TH1D("h1_QA_Q2DA_Res", "Q^{2}_{DA} Resolution;100*(Q^{2}_{DA}-Q^{2}_{MC})/Q^{2}_{MC};Rate/bin(Hz) ", 200, -100, 100);
    TH1D* h1_QA_Q2Sig_Res = new TH1D("h1_QA_Q2Sig_Res", "Q^{2}_{Sig} Resolution;100*(Q^{2}_{Sig}-Q^{2}_{MC})/Q^{2}_{MC};Rate/bin(Hz) ", 200, -100, 100);
    TH1D* h1_QA_yRec_Res = new TH1D("h1_QA_yRec_Res", "y_{Rec} Resolution;100*(y_{Rec}-y_{MC})/y_{MC};Rate/bin(Hz) ", 200, -100, 100);
    TH1D* h1_QA_yJB_Res = new TH1D("h1_QA_yJB_Res", "y_{JB} Resolution;100*(y_{JB}-y_{MC})/y_{MC};Rate/bin(Hz) ", 200, -100, 100);
    TH1D* h1_QA_yDA_Res = new TH1D("h1_QA_yDA_Res", "y_{DA} Resolution;100*(y_{DA}-y_{MC})/y_{MC};Rate/bin(Hz) ", 200, -100, 100);
    TH1D* h1_QA_ySig_Res = new TH1D("h1_QA_ySig_Res", "y_{Sig} Resolution;100*(y_{Sig}-y_{MC})/y_{MC};Rate/bin(Hz) ", 200, -100, 100);
    TH2D* h2_QA_Q2Rec_Q2MC = new TH2D("h2_QA_Q2Rec_Q2MC","Q^{2}_{Rec} vs Q^{2}_{MC}; Q^{2}_{Rec} (GeV/c^{2}); Q^{2}_{MC} (GeV/c^{2}); Rate/bin(Hz)", 100, 0, 50, 100, 0, 50);
    TH2D* h2_QA_Q2DA_Q2MC = new TH2D("h2_QA_Q2DA_Q2MC","Q^{2}_{DA} vs Q^{2}_{MC}; Q^{2}_{DA} (GeV/c^{2}); Q^{2}_{MC} (GeV/c^{2}); Rate/bin(Hz)", 100, 0, 50, 100, 0, 50);
    TH2D* h2_QA_Q2Sig_Q2MC = new TH2D("h2_QA_Q2Sig_Q2MC","Q^{2}_{Sig} vs Q^{2}_{MC}; Q^{2}_{Sig} (GeV/c^{2}); Q^{2}_{MC} (GeV/c^{2}); Rate/bin(Hz)", 100, 0, 50, 100, 0, 50);
    TH2D* h2_QA_Q2Rec_Q2Res = new TH2D("h2_QA_Q2Rec_Q2Res","Q^{2}_{Rec} vs Q^{2}_{Res}; Q^{2}_{Rec} (GeV/c^{2}); 100*(Q^{2}_{Rec}-Q^{2}_{MC})/Q^{2}_{MC}; Rate/bin(Hz)", 100, 0, 50, 200, -100, 100);
    TH2D* h2_QA_Q2DA_Q2Res = new TH2D("h2_QA_Q2DA_Q2Res","Q^{2}_{DA} vs Q^{2}_{Res}; Q^{2}_{DA} (GeV/c^{2}); 100*(Q^{2}_{DA}-Q^{2}_{MC})/Q^{2}_{MC}; Rate/bin(Hz)", 100, 0, 50, 200, -100, 100);
    TH2D* h2_QA_Q2Sig_Q2Res = new TH2D("h2_QA_Q2Sig_Q2Res","Q^{2}_{Sig} vs Q^{2}_{Res}; Q^{2}_{Sig} (GeV/c^{2}); 100*(Q^{2}_{Sig}-Q^{2}_{MC})/Q^{2}_{MC}; Rate/bin(Hz)", 100, 0, 50, 200, -100, 100);

    TH2D* h2_QA_yRec_yMC = new TH2D("h2_QA_yRec_yMC","y_{Rec} vs y_{MC}; y_{Rec}; y_{MC}; Rate/bin(Hz)", 100, 0, 1, 100, 0, 0.1);
    TH2D* h2_QA_yDA_yMC = new TH2D("h2_QA_yDA_yMC","y_{DA} vs y_{MC}; y_{DA}; y_{MC}; Rate/bin(Hz)", 100, 0, 1, 100, 0, 0.1);
    TH2D* h2_QA_ySig_yMC = new TH2D("h2_QA_ySig_yMC","y_{Sig} vs y_{MC}; y_{Sig}; y_{MC}; Rate/bin(Hz)", 100, 0, 1, 100, 0, 0.1);
    TH2D* h2_QA_xRec_xMC = new TH2D("h2_QA_xRec_xMC","x_{Rec} vs x_{MC}; x_{Rec}; x_{MC}; Rate/bin(Hz)", 100, 0, 1, 100, 0, 1);
    TH2D* h2_QA_xDA_xMC = new TH2D("h2_QA_xDA_xMC","x_{DA} vs x_{MC}; x_{DA}; x_{MC}; Rate/bin(Hz)", 100, 0, 1, 100, 0, 1);
    TH2D* h2_QA_xSig_xMC = new TH2D("h2_QA_xSig_xMC","x_{Sig} vs x_{MC}; x_{Sig}; x_{MC}; Rate/bin(Hz)", 100, 0, 1, 100, 0, 1);
    
    gDirectory->cd("../../");
  }
  if (Results == kTRUE){
    gDirectory->cd("ResultsDists");
    /* TH1D* h1_tResult[8]; */
    /* TH1D* h1_Q2Result[8]; */
    /* TH1D* h1_WResult[8]; */
    /* TH1D* h1_tResult_ZDC[8]; */
    /* TH1D* h1_Q2Result_ZDC[8]; */
    /* TH1D* h1_WResult_ZDC[8];    */
    /* TH1D* h1_tResult_B0[8]; */
    /* TH1D* h1_Q2Result_B0[8]; */
    /* TH1D* h1_WResult_B0[8]; */
   
    /* h1_tResult[0] = new TH1D("h1_tResult_0", "-t_{eXBABE}, DEMP Events with Cuts, 5 < Q^{2} < 35; -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", 40, 0, 1.6); */
    /* h1_Q2Result[0] = new TH1D("h1_Q2Result_0", "Q^{2}, DEMP Events with Cuts, 5 < Q^{2} < 35; Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", 60, 5, 35); */
    /* h1_WResult[0] = new TH1D("h1_WResult_0", "W, DEMP Events with Cuts, 5 < Q^{2} < 35; W (GeV); Rate/(0.5 GeV) (Hz)", 80, -10, 30); */

    /* if(ZDC == kTRUE){ */
    /*   h1_tResult_ZDC[0] = new TH1D("h1_tResult_ZDC_0", "-t_{eXBABE}, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in ZDC only) ; -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", 40, 0, 1.6); */
    /*   h1_Q2Result_ZDC[0] = new TH1D("h1_Q2Result_ZDC_0", "Q^{2}, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in ZDC only); Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", 60, 5, 35); */
    /*   h1_WResult_ZDC[0] = new TH1D("h1_WResult_ZDC_0", "W, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in ZDC only); W (GeV); Rate/(0.5 GeV) (Hz)", 80, -10, 30); */
    /* } */
    /* if (B0 == kTRUE){ */
    /*   h1_tResult_B0[0] = new TH1D("h1_tResult_B0_0", "-t_{eXBABE}, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in B0 only) ; -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", 40, 0, 1.6); */
    /*   h1_Q2Result_B0[0] = new TH1D("h1_Q2Result_B0_0", "Q^{2}, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in B0 only); Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", 60, 5, 35); */
    /*   h1_WResult_B0[0] = new TH1D("h1_WResult_B0_0", "W, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in B0 only); W (GeV); Rate/(0.5 GeV) (Hz)", 80, -10, 30); */
    /* } */

    /* for(Int_t i = 0; i < 7; i++){ */
    /*   h1_tResult[i+1] = new TH1D(Form("h1_tResult_%i", i+1), Form("-t_{eXBABE}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f; -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 40, 0, 1.6); */
    /*   h1_Q2Result[i+1] = new TH1D(Form("h1_Q2Result_%i", i+1), Form("Q^{2}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f; Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 60, 5, 35); */
    /*   h1_WResult[i+1] = new TH1D(Form("h1_WResult_%i", i+1), Form("W, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f; W (GeV); Rate/(0.5 GeV) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, -10, 30); */
    /*   if(ZDC == kTRUE){ */
    /* 	h1_tResult_ZDC[i+1] = new TH1D(Form("h1_tResult_ZDC_%i", i+1), Form("-t_{eXBABE}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in ZDC only); -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 40, 0, 1.6); */
    /* 	h1_Q2Result_ZDC[i+1] = new TH1D(Form("h1_Q2Result_ZDC_%i", i+1), Form("Q^{2}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in ZDC only); Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 60, 5, 35); */
    /* 	h1_WResult_ZDC[i+1] = new TH1D(Form("h1_WResult_ZDC_%i", i+1), Form("W, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in ZDC only); W (GeV); Rate/(0.5 GeV) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, -10, 30); */
    /* } */
    /*   if(B0 == kTRUE){ */
    /* 	h1_tResult_B0[i+1] = new TH1D(Form("h1_tResult_B0_%i", i+1), Form("-t_{eXBABE}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in B0 only); -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 40, 0, 1.6); */
    /* 	h1_Q2Result_B0[i+1] = new TH1D(Form("h1_Q2Result_B0_%i", i+1), Form("Q^{2}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in B0 only); Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 60, 5, 35); */
    /* 	h1_WResult_B0[i+1] = new TH1D(Form("h1_WResult_B0_%i", i+1), Form("W, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in B0 only); W (GeV); Rate/(0.5 GeV) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, -10, 30); */
    /*   } */
    /* } */
    TH1D* h1_tResult[31];
    TH1D* h1_Q2Result[31];
    TH1D* h1_WResult[31];
    TH1D* h1_tResult_ZDC[31];
    TH1D* h1_Q2Result_ZDC[31];
    TH1D* h1_WResult_ZDC[31];
    TH1D* h1_tResult_B0[31];
    TH1D* h1_Q2Result_B0[31];
    TH1D* h1_WResult_B0[31];
   
    h1_tResult[0] = new TH1D("h1_tResult_0", "-t_{eXBABE}, DEMP Events with Cuts, 5 < Q^{2}_{DA} < 35; -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", 40, 0, 1.6);
    h1_Q2Result[0] = new TH1D("h1_Q2Result_0", "Q^{2}_{DA}, DEMP Events with Cuts, 5 < Q^{2}_{DA} < 35; Q^{2}_{DA} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", 60, 5, 35);
    h1_WResult[0] = new TH1D("h1_WResult_0", "W, DEMP Events with Cuts, 5 < Q^{2}_{DA} < 35; W (GeV); Rate/(0.5 GeV) (Hz)", 80, -10, 30);

    if(ZDC == kTRUE){
      h1_tResult_ZDC[0] = new TH1D("h1_tResult_ZDC_0", "-t_{eXBABE}, DEMP Events with Cuts, 5 < Q^{2}_{DA} < 35, (n in ZDC only) ; -t_{eXBABE} (GeV^{2}); Rate/(0.02 GeV^{2}) (Hz)", 80, 0, 1.6);
      h1_Q2Result_ZDC[0] = new TH1D("h1_Q2Result_ZDC_0", "Q^{2}_{DA}, DEMP Events with Cuts, 5 < Q^{2}_{DA} < 35, (n in ZDC only); Q^{2}_{DA} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", 60, 5, 35);
      h1_WResult_ZDC[0] = new TH1D("h1_WResult_ZDC_0", "W, DEMP Events with Cuts, 5 < Q^{2}_{DA} < 35, (n in ZDC only); W (GeV); Rate/(0.5 GeV) (Hz)", 80, -10, 30);
    }
    if (B0 == kTRUE){
      h1_tResult_B0[0] = new TH1D("h1_tResult_B0_0", "-t_{eXBABE}, DEMP Events with Cuts, 5 < Q^{2}_{DA} < 35, (n in B0 only) ; -t_{eXBABE} (GeV^{2}); Rate/(0.02 GeV^{2}) (Hz)", 80, 0, 1.6);
      h1_Q2Result_B0[0] = new TH1D("h1_Q2Result_B0_0", "Q^{2}_{DA}, DEMP Events with Cuts, 5 < Q^{2}_{DA} < 35, (n in B0 only); Q^{2}_{DA} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", 60, 5, 35);
      h1_WResult_B0[0] = new TH1D("h1_WResult_B0_0", "W, DEMP Events with Cuts, 5 < Q^{2}_{DA} < 35, (n in B0 only); W (GeV); Rate/(0.5 GeV) (Hz)", 80, -10, 30);
    }

    for(Int_t i = 0; i < 30; i++){
      h1_tResult[i+1] = new TH1D(Form("h1_tResult_%i", i+1), Form("-t_{eXBABE}, DEMP Events with Cuts, %2.1f < Q^{2}_{DA} < %2.1f; -t_{eXBABE} (GeV^{2}); Rate/(0.02 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, 0, 1.6);
      h1_Q2Result[i+1] = new TH1D(Form("h1_Q2Result_%i", i+1), Form("Q^{2}_{DA}, DEMP Events with Cuts, %2.1f < Q^{2}_{DA} < %2.1f; Q^{2}_{DA} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 60, 5, 35);
      h1_WResult[i+1] = new TH1D(Form("h1_WResult_%i", i+1), Form("W, DEMP Events with Cuts, %2.1f < Q^{2}_{DA} < %2.1f; W (GeV); Rate/(0.5 GeV) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, -10, 30);
      if(ZDC == kTRUE){
	h1_tResult_ZDC[i+1] = new TH1D(Form("h1_tResult_ZDC_%i", i+1), Form("-t_{eXBABE}, DEMP Events with Cuts, %2.1f < Q^{2}_{DA} < %2.1f, (n in ZDC only); -t_{eXBABE} (GeV^{2}); Rate/(0.02 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, 0, 1.6);
	h1_Q2Result_ZDC[i+1] = new TH1D(Form("h1_Q2Result_ZDC_%i", i+1), Form("Q^{2}_{DA}, DEMP Events with Cuts, %2.1f < Q^{2}_{DA} < %2.1f, (n in ZDC only); Q^{2}_{DA} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 60, 5, 35);
	h1_WResult_ZDC[i+1] = new TH1D(Form("h1_WResult_ZDC_%i", i+1), Form("W, DEMP Events with Cuts, %2.1f < Q^{2}_{DA} < %2.1f, (n in ZDC only); W (GeV); Rate/(0.5 GeV) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, -10, 30);
    }
      if(B0 == kTRUE){
	h1_tResult_B0[i+1] = new TH1D(Form("h1_tResult_B0_%i", i+1), Form("-t_{eXBABE}, DEMP Events with Cuts, %2.1f < Q^{2}_{DA} < %2.1f, (n in B0 only); -t_{eXBABE} (GeV^{2}); Rate/(0.02 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, 0, 1.6);
	h1_Q2Result_B0[i+1] = new TH1D(Form("h1_Q2Result_B0_%i", i+1), Form("Q^{2}_{DA}, DEMP Events with Cuts, %2.1f < Q^{2}_{DA} < %2.1f, (n in B0 only); Q^{2}_{DA} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 60, 5, 35);
	h1_WResult_B0[i+1] = new TH1D(Form("h1_WResult_B0_%i", i+1), Form("W, DEMP Events with Cuts, %2.1f < Q^{2}_{DA} < %2.1f, (n in B0 only); W (GeV); Rate/(0.5 GeV) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, -10, 30);
      }
    }
    gDirectory->cd("../");
    gDirectory->cd("ResultsDists/Exclusive_Paper_Plots");
    // Set of kinematics plots
    TH1D* h1_Result_DEMPQ2_MC = new TH1D("h1_Result_DEMPQ2_MC", "Q^{2} DEMP, MC Truth;Q^{2}_{MC} (GeV/c^{2});Rate/(0.25 GeV/c^{2}) (Hz)", 200, 0, 50);
    TH1D* h1_Result_DEMPQ2_Rec = new TH1D("h1_Result_DEMPQ2_Rec", "Q^{2} DEMP, Rec (DA);Q^{2}_{RecDA} (GeV/c^{2});Rate/(0.25 GeV/c^{2}) (Hz)", 200, 0, 50);
    TH1D* h1_Result_DEMPx_MC = new TH1D("h1_Result_DEMPx_MC", "x DEMP, MC Truth;x_{MC};Rate/(0.005) (Hz)", 200, 0, 1);
    TH1D* h1_Result_DEMPx_Rec = new TH1D("h1_Result_DEMPx_Rec", "x DEMP, Rec (DA);x_{RecDA};Rate/(0.005) (Hz)", 200, 0, 1);
    TH1D* h1_Result_DEMPy_MC = new TH1D("h1_Result_DEMPy_MC", "y DEMP, MC Truth;y_{MC};Rate/(0.005) (Hz)", 40, 0, 0.2);
    TH1D* h1_Result_DEMPy_Rec = new TH1D("h1_Result_DEMPy_Rec", "y DEMP, Rec (DA);y_{RecDA};Rate/(0.005) (Hz)", 40, 0, 0.2);
    TH1D* h1_Result_DEMP_dQ2 = new TH1D("h1_Result_DEMP_dQ2", "DEMP dQ2; (Q^{2}_{RecDA} - Q^{2}_{MC})/Q^{2}_{MC}; Rate (Hz)", 200, -2, 2);
    TH1D* h1_Result_DEMP_dx = new TH1D("h1_Result_DEMP_dx", "DEMP dx; (x_{RecDA} - x_{MC})/x_{MC}; Rate (Hz)", 200, -2, 2);
    TH1D* h1_Result_DEMP_dy = new TH1D("h1_Result_DEMP_dy", "DEMP dy; (y_{RecDA} - y_{MC})/y_{MC}; Rate (Hz)", 200, -2, 2);
    // Particle distribution plots
    TH1D* h1_Result_DEMP_eScTheta_MC = new TH1D("h1_Result_DEMP_eScTheta_MC", "DEMP #theta_{e'MC};#theta_{e'MC} (Deg); Rate/(0.25^{#circ}) (Hz) ", NBins_Theta, 130, 180);
    TH1D* h1_Result_DEMP_eScTheta_Rec = new TH1D("h1_Result_DEMP_eScTheta_Rec", "DEMP #theta_{e'Rec};#theta_{e'Rec} (Deg); Rate/(0.25^{#circ}) (Hz) ", NBins_Theta, 130, 180);
    TH1D* h1_Result_DEMP_eScE_MC = new TH1D("h1_Result_DEMP_eScE_MC", "DEMP E_{e'MC};E_{e'MC} (GeV); Rate/(0.02 GeV)) (Hz) ", NBins_Energy, ElecBeamE-2, ElecBeamE+2);
    TH1D* h1_Result_DEMP_eScE_Rec = new TH1D("h1_Result_DEMP_eScE_Rec", "DEMP E_{e'Rec};E_{e'Rec} (GeV); Rate/(0.02 GeV) (Hz) ", NBins_Energy, ElecBeamE-2, ElecBeamE+2);
    TH1D* h1_Result_DEMP_piEPz_MC = new TH1D("h1_Result_DEMP_piEPz_MC", "DEMP E - P_{z} (#pi, MC); E_{#piMC} - P_{z#piMC}; Rate/0.01 (Hz)", 200, -1, 1);
    TH1D* h1_Result_DEMP_piEPz_Rec = new TH1D("h1_Result_DEMP_piEPz_Rec", "DEMP E - P_{z} (#pi, Rec); E_{#piRec} - P_{z#piRec}; Rate/0.01 (Hz)", 200, -1, 1);
    TH1D* h1_Result_DEMP_nEPz_MC = new TH1D("h1_Result_DEMP_nEPz_MC", "DEMP E - P_{z} (n, MC); E_{nMC} - P_{z nMC}; Rate/0.01 (Hz)", 200, -1, 1);
    TH1D* h1_Result_DEMP_nEPz_Rec = new TH1D("h1_Result_DEMP_nEPz_Rec", "DEMP E - P_{z} (n, Rec); E_{nRec} - P_{z nRec}; Rate/0.01 (Hz)", 200, -1, 1);
    TH1D* h1_Result_DEMP_piPt_MC = new TH1D("h1_Result_DEMP_piPt_MC", "DEMP P_{T} (#pi, MC); p_{T#piMC}; Rate/0.05 (Hz)", 200, 0, 10);
    TH1D* h1_Result_DEMP_piPt_Rec = new TH1D("h1_Result_DEMP_piPt_Rec", "DEMP P_{T} (#pi, Rec); p_{T#piRec}; Rate/0.05 (Hz)", 200, 0, 10);
    TH1D* h1_Result_DEMP_nPt_MC = new TH1D("h1_Result_DEMP_nPt_MC", "DEMP P_{T} (n, MC); p_{TnMC}; Rate/0.05 (Hz)", 200, 0, 10);
    TH1D* h1_Result_DEMP_nPt_Rec = new TH1D("h1_Result_DEMP_nPt_Rec", "DEMP P_{T} (n, Rec); p_{TnRec}; Rate/0.05 (Hz)", 200, 0, 10);
    // -t comparison plots
    TH1D* h1_Result_DEMP_tMC = new TH1D("h1_Result_DEMP_tMC", "DEMP -t (MC); -t_{MC} (GeV^{2}); Rate/0.01 GeV^{2} (Hz) ", 150, 0, 1.5);
    TH1D* h1_Result_DEMP_tRec = new TH1D("h1_Result_DEMP_tRec", "DEMP -t (eXBABE) ;-t_{eXBABE} (GeV^{2}); Rate/0.01 GeV^{2} (Hz)", 150, 0, 1.5);
    // E - Pz (sum) plots - Could (and probably should) introduce a form command to determine size of bins here.
    // This sum, sigma, should be equal to ~ 2EBeamE if no initial state radiation (ISR) was present
    TH1D* h1_Result_DEMP_EPz_MC = new TH1D("h1_Result_DEMP_EPz_MC", "DEMP E - P_{z} (MC, all final state partcles);E_{MC}-P_{zMC};Rate (Hz)", 200, 1.8*ElecBeamE , 2.2*ElecBeamE);
    TH1D* h1_Result_DEMP_EPz_Rec = new TH1D("h1_Result_DEMP_EPz_Rec", "DEMP E - P_{z} (Rec, all final state partcles);E_{Rec}-P_{zRec};Rate (Hz)", 200, 1.8*ElecBeamE , 2.2*ElecBeamE);
    // 2D plots
    TH2D* h2_Result_DEMPQ2 = new TH2D("h2_Result_DEMPQ2", "DEMP Q^{2} Response; Q^{2}_{MC} (GeV/c^{2}); Q^{2}_{DA} (GeV/c^{2}); Rate (Hz)", 200, 0, 50, 200, 0, 50);
    TH2D* h2_Result_DEMPx = new TH2D("h2_Result_DEMPx", "DEMP x Response; x_{MC}; x_{DA}; Rate (Hz)", 200, 0, 1, 200, 0, 1);
    TH2D* h2_Result_DEMPy = new TH2D("h2_Result_DEMPy", "DEMP x Response; y_{MC}; y_{DA}; Rate (Hz)", 200, 0, 0.11, 200, 0, 0.11);
    TH2D* h2_Result_DEMPt = new TH2D("h2_Result_DEMPt", "DEMP x Response; t_{MC} (GeV^{2}); t_{eXBABE}(GeV^{2}); Rate (Hz)", 150, 0, 1.5, 150, 0, 1.5);
    TH2D* h2_Result_DEMP_eScTheta = new TH2D("h2_Result_DEMP_eScTheta", "DEMP e' #theta; #theta_{e'MC} (Deg); #theta_{e'Rec} (Deg); Rate (Hz)", NBins_Theta, 130, 180, NBins_Theta, 130, 180);
    TH2D* h2_Result_DEMP_eScE = new TH2D("h2_Result_DEMP_eScE", "DEMP e' Energy; E_{e'MC} (GeV); E_{e'Rec} (GeV); Rate (Hz)", NBins_Energy, ElecBeamE-2, ElecBeamE+2, NBins_Energy, ElecBeamE-2, ElecBeamE+2);
    TH2D* h2_Result_DEMP_piEPz = new TH2D("h2_Result_DEMP_piEPz", "DEMP #pi E - P_{z}; (E - P_{z})_{#piMC}; (E - P_{z})_{#piRec}; Rate (Hz)", 200, -1, 1, 200, -1, 1);
    TH2D* h2_Result_DEMP_piPt = new TH2D("h2_Result_DEMP_piPt", "DEMP #pi P_{T}; P_{T#piMC}; P_{T#piRec}; Rate (Hz)", 200, 0, 10, 200, 0, 10);
    TH2D* h2_Result_DEMP_nEPz = new TH2D("h2_Result_DEMP_nEPz", "DEMP n E - P_{z}; (E - P_{z})_{nMC}; (E - P_{z})_{nRec}; Rate (Hz)", 200, -0.2, 0.2, 200, -0.2, 0.2);
    TH2D* h2_Result_DEMP_nPt = new TH2D("h2_Result_DEMP_nPt", "DEMP n P_{T}; P_{TnMC}; P_{TnRec}; Rate (Hz)", 200, 0, 10, 200, 0, 10);
    TH2D* h2_Result_DEMP_EPz = new TH2D("h2_Result_DEMP_EPz", "DEMP E - P_{z}; (E - P_{z})_{MC}; (E - P_{z})_{Rec}; Rate (Hz)", 200, 1.8*ElecBeamE , 2.2*ElecBeamE, 200, 1.8*ElecBeamE , 2.2*ElecBeamE);
    gDirectory->cd("../../");
  }  
}

// Histogram filling functions, avoids needing histograms defined in main file. Additionally, makes it so the main code doesn't actually care if the histogram is defined or not. If it doesn't exist, nothing happens
void FillHist1D(TString Histname, Double_t Value){
  if(gDirectory->FindObject(Histname) != 0){ // Check histogram exists, if it does, fill it
    ((TH1D*)gDirectory->FindObject(Histname))->Fill(Value);
  }
}

void FillHist1D(TString Histname, Double_t Value, Double_t W){
  if(gDirectory->FindObject(Histname) != 0){ // Check histogram exists, if it does, fill it
    ((TH1D*)gDirectory->FindObject(Histname))->Fill(Value, W);
  }
}

void FillHist2D(TString Histname, Double_t Value, Double_t Value2){
  if(gDirectory->FindObject(Histname) != 0){ // Check histogram exists, if it does, fill it
    ((TH2D*)gDirectory->FindObject(Histname))->Fill(Value, Value2);
  }
}
void FillHist2D(TString Histname, Double_t Value, Double_t Value2, Double_t W){
  if(gDirectory->FindObject(Histname) != 0){ // Check histogram exists, if it does, fill it
    ((TH2D*)gDirectory->FindObject(Histname))->Fill(Value, Value2, W);
  }
}
void DivideHists1D(TString ResHistname, TString Histname1, TString Histname2){
  if(gDirectory->FindObject(ResHistname) != 0 && gDirectory->FindObject(Histname1) != 0 && gDirectory->FindObject(Histname2) != 0){ // Check histograms exist, if they do, do our division
    ((TH1D*)gDirectory->FindObject(ResHistname))->Divide(((TH1D*)gDirectory->FindObject(Histname1)), ((TH1D*)gDirectory->FindObject(Histname2)), 1, 1, "b");
  }
  else{
    cerr << "Warning, tried to divide " << Histname1 << " by " << Histname2 << " to make " << ResHistname << " ,but one of these doesn't exist, check input histogram name strings or directory" << endl;
  }
}
void DivideHists2D(TString ResHistname, TString Histname1, TString Histname2){
  if(gDirectory->FindObject(ResHistname) != 0 && gDirectory->FindObject(Histname1) != 0 && gDirectory->FindObject(Histname2) != 0){ // Check histograms exist, if they do, do our division
    ((TH2D*)gDirectory->FindObject(ResHistname))->Divide(((TH2D*)gDirectory->FindObject(Histname1)), ((TH2D*)gDirectory->FindObject(Histname2)), 1, 1, "b");
  }
  else{
    cerr << "Warning, tried to divide " << Histname1 << " by " << Histname2 << " to make " << ResHistname << " ,but one of these doesn't exist, check input histogram name strings or directory" << endl;
  }
}
