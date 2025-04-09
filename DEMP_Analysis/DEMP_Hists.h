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
    gDirectory->cd("../../");
  }
  
  if (Kinematics == kTRUE){
    gDirectory->cd("KinematicDists/MC");
    TH1D* h1_Q2_MC = new TH1D("h1_Q2_MC", "Q^{2} MC Truth; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MC = new TH1D("h1_t_MC", "-t MC Truth; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MC = new TH1D("h1_W_MC", "W MC Truth; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MC = new TH1D("h1_eps_MC", "#epsilon MC Truth; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_MC = new TH1D("h1_y_MC", "y MC Truth; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MC = new TH2D("h2_Q2t_MC", "Q^{2} vs -t MC Truth; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MC = new TH2D("h2_WQ2_MC", "W vs Q^{2} MC Truth; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

    TH1D* h1_Q2_MC_NoAB = new TH1D("h1_Q2_MC_NoAB", "Q^{2} MC Truth, No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MC_NoAB = new TH1D("h1_t_MC_NoAB", "-t MC Truth, No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MC_NoAB = new TH1D("h1_W_MC_NoAB", "W MC Truth, No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MC_NoAB = new TH1D("h1_eps_MC_NoAB", "#epsilon MC Truth, No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_MC_NoAB = new TH1D("h1_y_MC_NoAB", "y MC Truth, No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MC_NoAB = new TH2D("h2_Q2t_MC_NoAB", "Q^{2} vs -t MC Truth, No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MC_NoAB = new TH2D("h2_WQ2_MC_NoAB", "W vs Q^{2} MC Truth, No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

    TH1D* h1_Q2_MCDEMPAccept_NoCuts = new TH1D("h1_Q2_MCDEMPAccept_NoCuts", "Q^{2} MC Truth DEMP Accepted, No Cuts; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MCDEMPAccept_NoCuts = new TH1D("h1_t_MCDEMPAccept_NoCuts", "-t MC Truth DEMP Accepted, Q^{2} Cut Only; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MCDEMPAccept_NoCuts = new TH1D("h1_W_MCDEMPAccept_NoCuts", "W MC Truth DEMP Accepted, No Cuts; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MCDEMPAccept_NoCuts = new TH1D("h1_eps_MCDEMPAccept_NoCuts", "#epsilon MC Truth DEMP Accepted, No Cuts; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_MCDEMPAccept_NoCuts = new TH1D("h1_y_MCDEMPAccept_NoCuts", "y MC Truth DEMP Accepted, No Cuts; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MCDEMPAccept_NoCuts = new TH2D("h2_Q2t_MCDEMPAccept_NoCuts", "Q^{2} vs -t MC Truth DEMP Accepted, Q^{2} Cut Only; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MCDEMPAccept_NoCuts = new TH2D("h2_WQ2_MCDEMPAccept_NoCuts", "W vs Q^{2} MC Truth DEMP Accepted, No Cuts; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

    TH1D* h1_Q2_MCDEMPAccept_NoCuts_NoAB = new TH1D("h1_Q2_MCDEMPAccept_NoCuts_NoAB", "Q^{2} MC Truth DEMP Accepted, No Cuts, No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MCDEMPAccept_NoCuts_NoAB = new TH1D("h1_t_MCDEMPAccept_NoCuts_NoAB", "-t MC Truth DEMP Accepted, Q^{2} Cut Only, No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MCDEMPAccept_NoCuts_NoAB = new TH1D("h1_W_MCDEMPAccept_NoCuts_NoAB", "W MC Truth DEMP Accepted, No Cuts, No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MCDEMPAccept_NoCuts_NoAB = new TH1D("h1_eps_MCDEMPAccept_NoCuts_NoAB", "#epsilon MC Truth DEMP Accepted, No Cuts, No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_MCDEMPAccept_NoCuts_NoAB = new TH1D("h1_y_MCDEMPAccept_NoCuts_NoAB", "y MC Truth DEMP Accepted, No Cuts, No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MCDEMPAccept_NoCuts_NoAB = new TH2D("h2_Q2t_MCDEMPAccept_NoCuts_NoAB", "Q^{2} vs -t MC Truth DEMP Accepted, Q^{2} Cut Only, No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MCDEMPAccept_NoCuts_NoAB = new TH2D("h2_WQ2_MCDEMPAccept_NoCuts_NoAB", "W vs Q^{2} MC Truth DEMP Accepted, No Cuts, No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

    TH1D* h1_Q2_MCDEMPAccept = new TH1D("h1_Q2_MCDEMPAccept", "Q^{2} MC Truth DEMP Accepted; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MCDEMPAccept = new TH1D("h1_t_MCDEMPAccept", "-t MC Truth DEMP Accepted; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MCDEMPAccept = new TH1D("h1_W_MCDEMPAccept", "W MC Truth DEMP Accepted; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MCDEMPAccept = new TH1D("h1_eps_MCDEMPAccept", "#epsilon MC Truth DEMP Accepted; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_MCDEMPAccept = new TH1D("h1_y_MCDEMPAccept", "y MC Truth DEMP Accepted; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MCDEMPAccept = new TH2D("h2_Q2t_MCDEMPAccept", "Q^{2} vs -t MC Truth DEMP Accepted; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MCDEMPAccept = new TH2D("h2_WQ2_MCDEMPAccept", "W vs Q^{2} MC Truth DEMP Accepted; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

    TH1D* h1_Q2_MCDEMPAccept_NoAB = new TH1D("h1_Q2_MCDEMPAccept_NoAB", "Q^{2} MC Truth DEMP Accepted, No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_t_MCDEMPAccept_NoAB = new TH1D("h1_t_MCDEMPAccept_NoAB", "-t MC Truth DEMP Accepted, No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_MCDEMPAccept_NoAB = new TH1D("h1_W_MCDEMPAccept_NoAB", "W MC Truth DEMP Accepted, No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_MCDEMPAccept_NoAB = new TH1D("h1_eps_MCDEMPAccept_NoAB", "#epsilon MC Truth DEMP Accepted, No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_MCDEMPAccept_NoAB = new TH1D("h1_y_MCDEMPAccept_NoAB", "y MC Truth DEMP Accepted, No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH2D* h2_Q2t_MCDEMPAccept_NoAB = new TH2D("h2_Q2t_MCDEMPAccept_NoAB", "Q^{2} vs -t MC Truth DEMP Accepted, No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_MCDEMPAccept_NoAB = new TH2D("h2_WQ2_MCDEMPAccept_NoAB", "W vs Q^{2} MC Truth DEMP Accepted, No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
    gDirectory->cd("../../");

    gDirectory->cd("KinematicDists/Reco");
    TH1D* h1_Q2_Reco_NoCuts = new TH1D("h1_Q2_Reco_NoCuts", "Q^{2} Reconstructed (No Cuts); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_tBABE_Reco_NoCuts = new TH1D("h1_tBABE_Reco_NoCuts", "-t_{BABE} Reconstructed (Q^{2} Cut Only); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teX_Reco_NoCuts = new TH1D("h1_teX_Reco_NoCuts", "-t_{eX} Reconstructed (Q^{2} Cut Only); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teXPT_Reco_NoCuts = new TH1D("h1_teXPT_Reco_NoCuts", "-t_{eXPT} Reconstructed (Q^{2} Cut Only); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teXBABE_Reco_NoCuts = new TH1D("h1_teXBABE_Reco_NoCuts", "-t_{eXBABE} Reconstructed (Q^{2} Cut Only); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_Reco_NoCuts = new TH1D("h1_W_Reco_NoCuts", "W Reconstructed (No Cuts); W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_Reco_NoCuts = new TH1D("h1_eps_Reco_NoCuts", "#epsilon Reconstructed (No Cuts); #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_Reco_NoCuts = new TH1D("h1_y_Reco_NoCuts", "y Reconstructed (No Cuts); y; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_DeltaTheta_Reco_NoCuts = new TH1D("h1_DeltaTheta_Reco_NoCuts", "#Delta#theta (#theta_{pMiss} - #theta_{ZDC/B0}) Reconstructed (Q^{2} Cut Only); #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
    TH1D* h1_DeltaPhi_Reco_NoCuts = new TH1D("h1_DeltaPhi_Reco_NoCuts", "#Delta#phi (#phi_{pMiss} - #phi_{ZDC/B0}) Reconstructed (Q^{2} Cut Only); #Delta#phi (Deg); Rate/bin (Hz)", 200, -100, 100);
    TH2D* h2_Q2tBABE_Reco_NoCuts = new TH2D("h2_Q2tBABE_Reco_NoCuts", "Q^{2} vs -t_{BABE} Reconstructed (Q^{2} Cut Only); Q^{2} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teX_Reco_NoCuts = new TH2D("h2_Q2teX_Reco_NoCuts", "Q^{2} vs -t_{eX} Reconstructed (Q^{2} Cut Only); Q^{2} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teXPT_Reco_NoCuts = new TH2D("h2_Q2teXPT_Reco_NoCuts", "Q^{2} vs -t_{eXPT} Reconstructed (Q^{2} Cut Only); Q^{2} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teXBABE_Reco_NoCuts = new TH2D("h2_teXBABEQ2_Reco_NoCuts", "Q^{2} vs -t_{eXBABE} Reconstructed (Q^{2} Cut Only);  Q^{2} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_Reco_NoCuts = new TH2D("h2_WQ2_Reco_NoCuts", "W vs Q^{2} Reconstructed (No Cuts); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
    TH2D* h2_DeltaThetaPhi_Reco_NoCuts = new TH2D("h2_DeltaThetaPhi_Reco_NoCuts", "#Delta#theta  (#theta_{pMiss} - #theta_{ZDC/B0}) vs #Delta#phi (#phi_{pMiss} - #phi_{ZDC/B0}) Reconstructed (Q^{2} Cuts only); #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 200, -1, 1, 200, -100, 100);
    
    TH1D* h1_Q2_Reco = new TH1D("h1_Q2_Reco", "Q^{2} Reconstructed; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
    TH1D* h1_tBABE_Reco = new TH1D("h1_tBABE_Reco", "-t_{BABE} Reconstructed; -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teX_Reco = new TH1D("h1_teX_Reco", "-t_{eX} Reconstructed; -t_{eX} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teXPT_Reco = new TH1D("h1_teXPT_Reco", "-t_{eXPT} Reconstructed; -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_teXBABE_Reco = new TH1D("h1_teXBABE_Reco", "-t_{eXBABE} Reconstructed; -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
    TH1D* h1_W_Reco = new TH1D("h1_W_Reco", "W Reconstructed; W (GeV); Rate/bin (Hz)", 150, -50, 100);
    TH1D* h1_eps_Reco = new TH1D("h1_eps_Reco", "#epsilon Reconstructed; #epsilon; Rate/bin (Hz)", 100, 0, 1);
    TH1D* h1_y_Reco = new TH1D("h1_y_Reco", "y Reconstructed; y; Rate/bin (Hz)", 120, -0.2, 1);
    TH1D* h1_DeltaTheta_Reco = new TH1D("h1_DeltaTheta_Reco", "#Delta#theta (#theta_{pMiss} - #theta_{ZDC/B0}) Reconstructed; #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
    TH1D* h1_DeltaPhi_Reco = new TH1D("h1_DeltaPhi_Reco", "#Delta#phi (#phi_{pMiss} - #phi_{ZDC/B0}) Reconstructed; #Delta#phi (Deg); Rate/bin (Hz)", 200, -100, 100);
    TH2D* h2_Q2tBABE_Reco = new TH2D("h2_Q2tBABE_Reco", "Q^{2} vs -t_{BABE} Reconstructed; Q^{2} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teX_Reco = new TH2D("h2_Q2teX_Reco", "Q^{2} vs -t_{eX} Reconstructed; Q^{2} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teXPT_Reco = new TH2D("h2_Q2teXPT_Reco", "Q^{2} vs -t_{eXPT} Reconstructed; Q^{2} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_Q2teXBABE_Reco = new TH2D("h2_Q2teXBABE_Reco", "Q^{2} vs -t_{eXBABE} Reconstructed;  Q^{2} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
    TH2D* h2_WQ2_Reco = new TH2D("h2_WQ2_Reco", "W vs Q^{2} Reconstructed; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
    TH2D* h2_DeltaThetaPhi_Reco = new TH2D("h2_DeltaThetaPhi_Reco", "#Delta#theta  (#theta_{pMiss} - #theta_{ZDC/B0}) vs #Delta#phi (#phi_{pMiss} - #phi_{ZDC/B0}) Recostructed; #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 200, -1, 1, 200, -100, 100);
    gDirectory->cd("../../");
    
    if (B0 == kTRUE){
      gDirectory->cd("KinematicDists/MC/B0");
      TH1D* h1_Q2_MCAcceptB0 = new TH1D("h1_Q2_MCAcceptB0", "Q^{2} MC Truth Accepted (B0 events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCAcceptB0 = new TH1D("h1_t_MCAcceptB0", "-t MC Truth Accepted (B0 events only); -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCAcceptB0 = new TH1D("h1_W_MCAcceptB0", "W MC Truth Accepted (B0 events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCAcceptB0 = new TH1D("h1_eps_MCAcceptB0", "#epsilon MC Truth Accepted (B0 events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCAcceptB0 = new TH1D("h1_y_MCAcceptB0", "y MC Truth Accepted (B0 events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCAcceptB0 = new TH2D("h2_Q2t_MCAcceptB0", "Q^{2} vs -t MC Truth Accepted (B0 events only); Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCAcceptB0 = new TH2D("h2_WQ2_MCAcceptB0", "W vs Q^{2} MC Truth Accepted (B0 events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCAcceptB0_NoAB = new TH1D("h1_Q2_MCAcceptB0_NoAB", "Q^{2} MC Truth Accepted (B0 events only), No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCAcceptB0_NoAB = new TH1D("h1_t_MCAcceptB0_NoAB", "-t MC Truth Accepted (B0 events only), No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCAcceptB0_NoAB = new TH1D("h1_W_MCAcceptB0_NoAB", "W MC Truth Accepted (B0 events only), No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCAcceptB0_NoAB = new TH1D("h1_eps_MCAcceptB0_NoAB", "#epsilon MC Truth Accepted (B0 events only), No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCAcceptB0_NoAB = new TH1D("h1_y_MCAcceptB0_NoAB", "y MC Truth Accepted (B0 events only), No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCAcceptB0_NoAB = new TH2D("h2_Q2t_MCAcceptB0_NoAB", "Q^{2} vs -t MC Truth Accepted (B0 events only), No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCAcceptB0_NoAB = new TH2D("h2_WQ2_MCAcceptB0_NoAB", "W vs Q^{2} MC Truth Accepted (B0 events only), No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptB0_NoCuts = new TH1D("h1_Q2_MCDEMPAcceptB0_NoCuts", "Q^{2} MC Truth DEMP Accepted (B0 Events only), No Cuts; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptB0_NoCuts = new TH1D("h1_t_MCDEMPAcceptB0_NoCuts", "-t MC Truth DEMP Accepted (B0 Events only), Q^{2} Cut Only; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptB0_NoCuts = new TH1D("h1_W_MCDEMPAcceptB0_NoCuts", "W MC Truth DEMP Accepted (B0 Events only), No Cuts; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptB0_NoCuts = new TH1D("h1_eps_MCDEMPAcceptB0_NoCuts", "#epsilon MC Truth DEMP Accepted (B0 Events only), No Cuts; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptB0_NoCuts = new TH1D("h1_y_MCDEMPAcceptB0_NoCuts", "y MC Truth DEMP Accepted (B0 Events only), No Cuts; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptB0_NoCuts = new TH2D("h2_Q2t_MCDEMPAcceptB0_NoCuts", "Q^{2} vs -t MC Truth DEMP Accepted (B0 Events only), Q^{2} Cut Only; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptB0_NoCuts = new TH2D("h2_WQ2_MCDEMPAcceptB0_NoCuts", "W vs Q^{2} MC Truth DEMP Accepted (B0 Events only), No Cuts; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptB0_NoCuts_NoAB = new TH1D("h1_Q2_MCDEMPAcceptB0_NoCuts_NoAB", "Q^{2} MC Truth DEMP Accepted (B0 Events only), No Cuts, No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptB0_NoCuts_NoAB = new TH1D("h1_t_MCDEMPAcceptB0_NoCuts_NoAB", "-t MC Truth DEMP Accepted (B0 Events only), Q^{2} Cut Only, No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptB0_NoCuts_NoAB = new TH1D("h1_W_MCDEMPAcceptB0_NoCuts_NoAB", "W MC Truth DEMP Accepted (B0 Events only), No Cuts, No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptB0_NoCuts_NoAB = new TH1D("h1_eps_MCDEMPAcceptB0_NoCuts_NoAB", "#epsilon MC Truth DEMP Accepted (B0 Events only), No Cuts, No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptB0_NoCuts_NoAB = new TH1D("h1_y_MCDEMPAcceptB0_NoCuts_NoAB", "y MC Truth DEMP Accepted (B0 Events only), No Cuts, No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptB0_NoCuts_NoAB = new TH2D("h2_Q2t_MCDEMPAcceptB0_NoCuts_NoAB", "Q^{2} vs -t MC Truth DEMP Accepted (B0 Events only), Q^{2} Cut Only, No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptB0_NoCuts_NoAB = new TH2D("h2_WQ2_MCDEMPAcceptB0_NoCuts_NoAB", "W vs Q^{2} MC Truth DEMP Accepted (B0 Events only), No Cuts, No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      
      TH1D* h1_Q2_MCDEMPAcceptB0 = new TH1D("h1_Q2_MCDEMPAcceptB0", "Q^{2} MC Truth DEMP Accepted (B0 events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptB0 = new TH1D("h1_t_MCDEMPAcceptB0", "-t MC Truth DEMP Accepted (B0 events only); -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptB0 = new TH1D("h1_W_MCDEMPAcceptB0", "W MC Truth DEMP Accepted (B0 events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptB0 = new TH1D("h1_eps_MCDEMPAcceptB0", "#epsilon MC Truth DEMP Accepted (B0 events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptB0 = new TH1D("h1_y_MCDEMPAcceptB0", "y MC Truth DEMP Accepted (B0 events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptB0 = new TH2D("h2_Q2t_MCDEMPAcceptB0", "Q^{2} vs -t MC Truth DEMP Accepted (B0 events only); Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptB0 = new TH2D("h2_WQ2_MCDEMPAcceptB0", "W vs Q^{2} MC Truth DEMP Accepted (B0 events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptB0_NoAB = new TH1D("h1_Q2_MCDEMPAcceptB0_NoAB", "Q^{2} MC Truth DEMP Accepted (B0 events only), No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptB0_NoAB = new TH1D("h1_t_MCDEMPAcceptB0_NoAB", "-t MC Truth DEMP Accepted (B0 events only), No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptB0_NoAB = new TH1D("h1_W_MCDEMPAcceptB0_NoAB", "W MC Truth DEMP Accepted (B0 events only), No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptB0_NoAB = new TH1D("h1_eps_MCDEMPAcceptB0_NoAB", "#epsilon MC Truth DEMP Accepted (B0 events only), No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptB0_NoAB = new TH1D("h1_y_MCDEMPAcceptB0_NoAB", "y MC Truth DEMP Accepted (B0 events only), No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptB0_NoAB = new TH2D("h2_Q2t_MCDEMPAcceptB0_NoAB", "Q^{2} vs -t MC Truth DEMP Accepted (B0 events only), No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptB0_NoAB = new TH2D("h2_WQ2_MCDEMPAcceptB0_NoAB", "W vs Q^{2} MC Truth DEMP Accepted (B0 events only), No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      gDirectory->cd("../../../");
      
      gDirectory->cd("KinematicDists/Reco/B0");
      TH1D* h1_Q2_B0Reco_NoCuts = new TH1D("h1_Q2_B0Reco_NoCuts", "Q^{2} Reconstructed (No Cuts, B0 n events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_tBABE_B0Reco_NoCuts = new TH1D("h1_tBABE_B0Reco_NoCuts", "-t_{BABE} Reconstructed (Q^{2} Cuts Only, B0 n events only); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teX_B0Reco_NoCuts = new TH1D("h1_teX_B0Reco_NoCuts", "-t_{eX} Reconstructed (Q^{2} Cuts Only, B0 n events only); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXPT_B0Reco_NoCuts = new TH1D("h1_teXPT_B0Reco_NoCuts", "-t_{eXPT} Reconstructed (Q^{2} Cuts Only, B0 n events only); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXBABE_B0Reco_NoCuts = new TH1D("h1_teXBABE_B0Reco_NoCuts", "-t_{eXBABE} Reconstructed (Q^{2} Cuts Only, B0 n events only); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_B0Reco_NoCuts = new TH1D("h1_W_B0Reco_NoCuts", "W Reconstructed (No Cuts, B0 n events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_B0Reco_NoCuts = new TH1D("h1_eps_B0Reco_NoCuts", "#epsilon Reconstructed (No Cuts, B0 n events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_B0Reco_NoCuts = new TH1D("h1_y_B0Reco_NoCuts", "y Reconstructed (No Cuts, B0 n events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_DeltaTheta_B0Reco_NoCuts = new TH1D("h1_DeltaTheta_B0Reco_NoCuts", "#Delta#theta (#theta_{pMiss} - #theta_{B0}) Reconstructed (Q^{2} Cuts Only, B0 n events only); #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
      TH1D* h1_DeltaPhi_B0Reco_NoCuts = new TH1D("h1_DeltaPhi_B0Reco_NoCuts", "#Delta#phi (#phi_{pMiss} - #phi_{B0}) Reconstructed (Q^{2} Cuts Only, B0 n events only); #Delta#phi (Deg); Rate/bin (Hz)", 200, -100, 100);
      TH2D* h2_Q2tBABE_B0Reco_NoCuts = new TH2D("h2_Q2tBABE_B0Reco_NoCuts", "Q^{2} vs -t_{BABE} Reconstructed (Q^{2} Cuts Only, B0 n events only); Q^{2} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teX_B0Reco_NoCuts = new TH2D("h2_Q2teX_B0Reco_NoCuts", "Q^{2} vs -t_{eX} Reconstructed (Q^{2} Cuts Only, B0 n events only); Q^{2} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXPT_B0Reco_NoCuts = new TH2D("h2_Q2teXPT_B0Reco_NoCuts", "Q^{2} vs -t_{eXPT} Reconstructed (Q^{2} Cuts Only, B0 n events only); Q^{2} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXBABE_B0Reco_NoCuts = new TH2D("h2_Q2teXBABE_B0Reco_NoCuts", "Q^{2} vs -t_{eXBABE} Reconstructed (Q^{2} Cuts Only, B0 n events only);  Q^{2} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_B0Reco_NoCuts = new TH2D("h2_WQ2_B0Reco_NoCuts", "W vs Q^{2} Reconstructed (No Cuts, B0 n events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      TH2D* h2_DeltaThetaPhi_B0Reco_NoCuts = new TH2D("h2_DeltaThetaPhi_B0Reco_NoCuts", "#Delta#theta  (#theta_{pMiss} - #theta_{B0}) vs #Delta#phi (#phi_{pMiss} - #phi_{B0}) Reconstructed (Q^{2} Cuts only, B0 n events only); #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 200, -1, 1, 200, -100, 100);

      TH1D* h1_Q2_B0Reco = new TH1D("h1_Q2_B0Reco", "Q^{2} Reconstructed (B0 n events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_tBABE_B0Reco = new TH1D("h1_tBABE_B0Reco", "-t_{BABE} Reconstructed (B0 n events only); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teX_B0Reco = new TH1D("h1_teX_B0Reco", "-t_{eX} Reconstructed (B0 n events only); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXPT_B0Reco = new TH1D("h1_teXPT_B0Reco", "-t_{eXPT} Reconstructed (B0 n events only); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXBABE_B0Reco = new TH1D("h1_teXBABE_B0Reco", "-t_{eXBABE} Reconstructed (B0 n events only); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_B0Reco = new TH1D("h1_W_B0Reco", "W Reconstructed (B0 n events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_B0Reco = new TH1D("h1_eps_B0Reco", "#epsilon Reconstructed (B0 n events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_B0Reco = new TH1D("h1_y_B0Reco", "y Reconstructed (B0 n events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_DeltaTheta_B0Reco = new TH1D("h1_DeltaTheta_B0Reco", "#Delta#theta (#theta_{pMiss} - #theta_{B0}) Reconstructed (B0 n events only); #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
      TH1D* h1_DeltaPhi_B0Reco = new TH1D("h1_DeltaPhi_B0Reco", "#Delta#phi (#phi_{pMiss} - #phi_{B0}) Reconstructed (B0 n events only); #Delta#phi (Deg); Rate/bin (Hz)", 200, -100, 100);
      TH2D* h2_Q2tBABE_B0Reco = new TH2D("h2_Q2tBABE_B0Reco", "Q^{2} vs -t_{BABE} Reconstructed (B0 n events only); Q^{2} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teX_B0Reco = new TH2D("h2_Q2teX_B0Reco", "Q^{2} vs -t_{eX} Reconstructed (B0 n events only); Q^{2} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXPT_B0Reco = new TH2D("h2_Q2teXPT_B0Reco", "Q^{2} vs -t_{eXPT} Reconstructed (B0 n events only); Q^{2} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXBABE_B0Reco = new TH2D("h2_Q2teXBABE_B0Reco", "Q^{2} vs -t_{eXBABE} Reconstructed (B0 n events only);  Q^{2} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_B0Reco = new TH2D("h2_WQ2_B0Reco", "W vs Q^{2} Reconstructed (B0 n events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      TH2D* h2_DeltaThetaPhi_B0Reco = new TH2D("h2_DeltaThetaPhi_B0Reco", "#Delta#theta  (#theta_{pMiss} - #theta_{B0}) vs #Delta#phi (#phi_{pMiss} - #phi_{B0}) Reconstruted (B0, n events only); #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 200, -1, 1, 200, -100, 100);
      gDirectory->cd("../../../");
    }
    
    if (ZDC == kTRUE){
      gDirectory->cd("KinematicDists/MC/ZDC");
      TH1D* h1_Q2_MCAcceptZDC = new TH1D("h1_Q2_MCAcceptZDC", "Q^{2} MC Truth Accepted (ZDC events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCAcceptZDC = new TH1D("h1_t_MCAcceptZDC", "-t MC Truth Accepted (ZDC events only); -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCAcceptZDC = new TH1D("h1_W_MCAcceptZDC", "W MC Truth Accepted (ZDC events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCAcceptZDC = new TH1D("h1_eps_MCAcceptZDC", "#epsilon MC Truth Accepted (ZDC events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCAcceptZDC = new TH1D("h1_y_MCAcceptZDC", "y MC Truth Accepted (ZDC events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCAcceptZDC = new TH2D("h2_Q2t_MCAcceptZDC", "Q^{2} vs -t MC Truth Accepted (ZDC events only); Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCAcceptZDC = new TH2D("h2_WQ2_MCAcceptZDC", "W vs Q^{2} MC Truth Accepted (ZDC events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCAcceptZDC_NoAB = new TH1D("h1_Q2_MCAcceptZDC_NoAB", "Q^{2} MC Truth Accepted (ZDC events only), No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCAcceptZDC_NoAB = new TH1D("h1_t_MCAcceptZDC_NoAB", "-t MC Truth Accepted (ZDC events only), No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCAcceptZDC_NoAB = new TH1D("h1_W_MCAcceptZDC_NoAB", "W MC Truth Accepted (ZDC events only), No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCAcceptZDC_NoAB = new TH1D("h1_eps_MCAcceptZDC_NoAB", "#epsilon MC Truth Accepted (ZDC events only), No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCAcceptZDC_NoAB = new TH1D("h1_y_MCAcceptZDC_NoAB", "y MC Truth Accepted (ZDC events only), No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCAcceptZDC_NoAB = new TH2D("h2_Q2t_MCAcceptZDC_NoAB", "Q^{2} vs -t MC Truth Accepted (ZDC events only), No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCAcceptZDC_NoAB = new TH2D("h2_WQ2_MCAcceptZDC_NoAB", "W vs Q^{2} MC Truth Accepted (ZDC events only), No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptZDC_NoCuts = new TH1D("h1_Q2_MCDEMPAcceptZDC_NoCuts", "Q^{2} MC Truth DEMP Accepted (ZDC Events only), No Cuts; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptZDC_NoCuts = new TH1D("h1_t_MCDEMPAcceptZDC_NoCuts", "-t MC Truth DEMP Accepted (ZDC Events only), Q^{2} Cut Only; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptZDC_NoCuts = new TH1D("h1_W_MCDEMPAcceptZDC_NoCuts", "W MC Truth DEMP Accepted (ZDC Events only), No Cuts; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptZDC_NoCuts = new TH1D("h1_eps_MCDEMPAcceptZDC_NoCuts", "#epsilon MC Truth DEMP Accepted (ZDC Events only), No Cuts; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptZDC_NoCuts = new TH1D("h1_y_MCDEMPAcceptZDC_NoCuts", "y MC Truth DEMP Accepted (ZDC Events only), No Cuts; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptZDC_NoCuts = new TH2D("h2_Q2t_MCDEMPAcceptZDC_NoCuts", "Q^{2} vs -t MC Truth DEMP Accepted (ZDC Events only), Q^{2} Cut Only; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptZDC_NoCuts = new TH2D("h2_WQ2_MCDEMPAcceptZDC_NoCuts", "W vs Q^{2} MC Truth DEMP Accepted (ZDC Events only), No Cuts; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptZDC_NoCuts_NoAB = new TH1D("h1_Q2_MCDEMPAcceptZDC_NoCuts_NoAB", "Q^{2} MC Truth DEMP Accepted (ZDC Events only), No Cuts, No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptZDC_NoCuts_NoAB = new TH1D("h1_t_MCDEMPAcceptZDC_NoCuts_NoAB", "-t MC Truth DEMP Accepted (ZDC Events only), Q^{2} Cut Only, No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptZDC_NoCuts_NoAB = new TH1D("h1_W_MCDEMPAcceptZDC_NoCuts_NoAB", "W MC Truth DEMP Accepted (ZDC Events only), No Cuts, No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptZDC_NoCuts_NoAB = new TH1D("h1_eps_MCDEMPAcceptZDC_NoCuts_NoAB", "#epsilon MC Truth DEMP Accepted (ZDC Events only), No Cuts, No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptZDC_NoCuts_NoAB = new TH1D("h1_y_MCDEMPAcceptZDC_NoCuts_NoAB", "y MC Truth DEMP Accepted (ZDC Events only), No Cuts, No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptZDC_NoCuts_NoAB = new TH2D("h2_Q2t_MCDEMPAcceptZDC_NoCuts_NoAB", "Q^{2} vs -t MC Truth DEMP Accepted (ZDC Events only), Q^{2} Cut Only, No Beam Effects; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptZDC_NoCuts_NoAB = new TH2D("h2_WQ2_MCDEMPAcceptZDC_NoCuts_NoAB", "W vs Q^{2} MC Truth DEMP Accepted (ZDC Events only), No Cuts, No Beam Effects; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      
      TH1D* h1_Q2_MCDEMPAcceptZDC = new TH1D("h1_Q2_MCDEMPAcceptZDC", "Q^{2} MC Truth DEMP Accepted (ZDC events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptZDC = new TH1D("h1_t_MCDEMPAcceptZDC", "-t MC Truth DEMP Accepted (ZDC events only); -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptZDC = new TH1D("h1_W_MCDEMPAcceptZDC", "W MC Truth DEMP Accepted (ZDC events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptZDC = new TH1D("h1_eps_MCDEMPAcceptZDC", "#epsilon MC Truth DEMP Accepted (ZDC events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptZDC = new TH1D("h1_y_MCDEMPAcceptZDC", "y MC Truth DEMP Accepted (ZDC events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH2D* h2_Q2t_MCDEMPAcceptZDC = new TH2D("h2_Q2t_MCDEMPAcceptZDC", "Q^{2} vs -t MC Truth DEMP Accepted (ZDC events only); Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_MCDEMPAcceptZDC = new TH2D("h2_WQ2_MCDEMPAcceptZDC", "W vs Q^{2} MC Truth DEMP Accepted (ZDC events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);

      TH1D* h1_Q2_MCDEMPAcceptZDC_NoAB = new TH1D("h1_Q2_MCDEMPAcceptZDC_NoAB", "Q^{2} MC Truth DEMP Accepted (ZDC events only), No Beam Effects; Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_t_MCDEMPAcceptZDC_NoAB = new TH1D("h1_t_MCDEMPAcceptZDC_NoAB", "-t MC Truth DEMP Accepted (ZDC events only), No Beam Effects; -t (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_MCDEMPAcceptZDC_NoAB = new TH1D("h1_W_MCDEMPAcceptZDC_NoAB", "W MC Truth DEMP Accepted (ZDC events only), No Beam Effects; W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_MCDEMPAcceptZDC_NoAB = new TH1D("h1_eps_MCDEMPAcceptZDC_NoAB", "#epsilon MC Truth DEMP Accepted (ZDC events only), No Beam Effects; #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_MCDEMPAcceptZDC_NoAB = new TH1D("h1_y_MCDEMPAcceptZDC_NoAB", "y MC Truth DEMP Accepted (ZDC events only), No Beam Effects; y; Rate/bin (Hz)", 120, -0.2, 1);
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
      TH1D* h1_y_ZDCReco_NoCuts = new TH1D("h1_y_ZDCReco_NoCuts", "y Reconstructed (No Cuts, ZDC n events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_DeltaTheta_ZDCReco_NoCuts = new TH1D("h1_DeltaTheta_ZDCReco_NoCuts", "#Delta#theta (#theta_{pMiss} - #theta_{ZDC}) Reconstructed (Q^{2} Cuts Only, ZDC n events only); #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
      TH1D* h1_DeltaPhi_ZDCReco_NoCuts = new TH1D("h1_DeltaPhi_ZDCReco_NoCuts", "#Delta#phi (#phi_{pMiss} - #phi_{ZDC}) Reconstructed (Q^{2} Cuts Only, ZDC n events only); #Delta#phi (Deg); Rate/bin (Hz)", 200, -100, 100);
      TH2D* h2_Q2tBABE_ZDCReco_NoCuts = new TH2D("h2_Q2tBABE_ZDCReco_NoCuts", "Q^{2} vs -t_{BABE} Reconstructed (Q^{2} Cuts Only, ZDC n events only); Q^{2} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teX_ZDCReco_NoCuts = new TH2D("h2_Q2teX_ZDCReco_NoCuts", "Q^{2} vs -t_{eX} Reconstructed (Q^{2} Cuts Only, ZDC n events only); Q^{2} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXPT_ZDCReco_NoCuts = new TH2D("h2_Q2teXPT_ZDCReco_NoCuts", "Q^{2} vs -t_{eXPT} Reconstructed (Q^{2} Cuts Only, ZDC n events only); Q^{2} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXBABE_ZDCReco_NoCuts = new TH2D("h2_Q2teXBABE_ZDCReco_NoCuts", "Q^{2} vs -t_{eXBABE} Reconstructed (Q^{2} Cuts Only, ZDC n events only);  Q^{2} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_ZDCReco_NoCuts = new TH2D("h2_WQ2_ZDCReco_NoCuts", "W vs Q^{2} Reconstructed (No Cuts, ZDC n events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      TH2D* h2_DeltaThetaPhi_ZDCReco_NoCuts = new TH2D("h2_DeltaThetaPhi_ZDCReco_NoCuts", "#Delta#theta  (#theta_{pMiss} - #theta_{ZDC}) vs #Delta#phi (#phi_{pMiss} - #phi_{ZDC}) Reconstructed (Q^{2} Cuts only, ZDC n events only); #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 200, -1, 1, 200, -100, 100);

      TH1D* h1_Q2_ZDCReco = new TH1D("h1_Q2_ZDCReco", "Q^{2} Reconstructed (ZDC n events only); Q^{2} (GeV^{2}); Rate/bin (Hz)", 160, 0, 40);
      TH1D* h1_tBABE_ZDCReco = new TH1D("h1_tBABE_ZDCReco", "-t_{BABE} Reconstructed (ZDC n events only); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teX_ZDCReco = new TH1D("h1_teX_ZDCReco", "-t_{eX} Reconstructed (ZDC n events only); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXPT_ZDCReco = new TH1D("h1_teXPT_ZDCReco", "-t_{eXPT} Reconstructed (ZDC n events only); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_teXBABE_ZDCReco = new TH1D("h1_teXBABE_ZDCReco", "-t_{eXBABE} Reconstructed (ZDC n events only); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 200, -0.5, 1.5);
      TH1D* h1_W_ZDCReco = new TH1D("h1_W_ZDCReco", "W Reconstructed (ZDC n events only); W (GeV); Rate/bin (Hz)", 150, -50, 100);
      TH1D* h1_eps_ZDCReco = new TH1D("h1_eps_ZDCReco", "#epsilon Reconstructed (ZDC n events only); #epsilon; Rate/bin (Hz)", 100, 0, 1);
      TH1D* h1_y_ZDCReco = new TH1D("h1_y_ZDCReco", "y Reconstructed (ZDC n events only); y; Rate/bin (Hz)", 120, -0.2, 1);
      TH1D* h1_DeltaTheta_ZDCReco = new TH1D("h1_DeltaTheta_ZDCReco", "#Delta#theta (#theta_{pMiss} - #theta_{ZDC}) Reconstructed (ZDC n events only); #Delta#theta (Deg); Rate/bin (Hz)", 180, -0.3, 1.5);
      TH1D* h1_DeltaPhi_ZDCReco = new TH1D("h1_DeltaPhi_ZDCReco", "#Delta#phi (#phi_{pMiss} - #phi_{ZDC}) Reconstructed (ZDC n events only); #Delta#phi (Deg); Rate/bin (Hz)", 200, -100, 100);
      TH2D* h2_Q2tBABE_ZDCReco = new TH2D("h2_Q2tBABE_ZDCReco", "Q^{2} vs -t_{BABE} Reconstructed (ZDC n events only); Q^{2} (GeV^{2}); -t_{BABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teX_ZDCReco = new TH2D("h2_Q2teX_ZDCReco", "Q^{2} vs -t_{eX} Reconstructed (ZDC n events only); Q^{2} (GeV^{2}); -t_{eX} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXPT_ZDCReco = new TH2D("h2_Q2teXPT_ZDCReco", "Q^{2} vs -t_{eXPT} Reconstructed (ZDC n events only); Q^{2} (GeV^{2}); -t_{eXPT} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_Q2teXBABE_ZDCReco = new TH2D("h2_Q2teXBABE_ZDCReco", "Q^{2} vs -t_{eXBABE} Reconstructed (ZDC n events only);  Q^{2} (GeV^{2}); -t_{eXBABE} (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 40, 0, 1.6);
      TH2D* h2_WQ2_ZDCReco = new TH2D("h2_WQ2_ZDCReco", "W vs Q^{2} Reconstructed (ZDC n events only); W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)", 150, -50, 100, 40, 0, 40);
      TH2D* h2_DeltaThetaPhi_ZDCReco = new TH2D("h2_DeltaThetaPhi_ZDCReco", "#Delta#theta  (#theta_{pMiss} - #theta_{ZDC}) vs #Delta#phi (#phi_{pMiss} - #phi_{ZDC}) Reconstruted (ZDC, n events only); #Delta#theta (Deg); #Delta#phi (Deg); Rate/bin (Hz)", 200, -1, 1, 200, -100, 100);
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
    TH2D* h2_n_pTheta_RecoAcceptZDC = new TH2D("h2_n_pTheta_RecoAcceptZDC", "ZDC Reconstructed;#theta (Deg); p (GeV/c)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_nRot_pTheta_RecoAcceptoZDC = new TH2D("h2_nRot_pTheta_RecoAcceptZDC", "ZDC Reconstructed (Rotated 25 mrad);#theta (Deg); p (GeV/c)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
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
    TH2D* h2_n_pTheta_RecoAcceptB0 = new TH2D("h2_n_pTheta_RecoAcceptB0", "B0 Reconstructed;#theta (Deg); p (GeV/c)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_nRot_pTheta_RecoAcceptB0 = new TH2D("h2_nRot_pTheta_RecoAcceptB0", "B0 Reconstructed (Rotated 25 mrad);#theta (Deg); p (GeV/c)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_eSc_pTheta_RecoDEMPAcceptB0_NoCuts = new TH2D("h2_eSc_pTheta_RecoDEMPAcceptB0_NoCuts", "e' Reconstructed DEMP Accepted (B0), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_RecoDEMPAcceptB0_NoCuts = new TH2D("h2_Pi_pTheta_RecoDEMPAcceptB0_NoCuts", "#pi Reconstructed DEMP Accepted (B0), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_RecoDEMPAcceptB0_NoCuts = new TH2D("h2_n_pTheta_RecoDEMPAcceptB0_NoCuts", "Neutron Reconstructed DEMP Accepted (B0), No Cuts; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_eSc_pTheta_RecoDEMPAcceptB0 = new TH2D("h2_eSc_pTheta_RecoDEMPAcceptB0", "e' Reconstructed DEMP Accepted (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_Pi_pTheta_RecoDEMPAcceptB0 = new TH2D("h2_Pi_pTheta_RecoDEMPAcceptB0", "#pi Reconstructed DEMP Accepted (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_n_pTheta_RecoDEMPAcceptB0 = new TH2D("h2_n_pTheta_RecoDEMPAcceptB0", "Neutron Reconstructed DEMP Accepted (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
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
  }
  
  if (Results == kTRUE){
    gDirectory->cd("ResultsDists");
    TH1D* h1_tResult[8];
    TH1D* h1_Q2Result[8];
    TH1D* h1_WResult[8];
    TH1D* h1_tResult_ZDC[8];
    TH1D* h1_Q2Result_ZDC[8];
    TH1D* h1_WResult_ZDC[8];   
    TH1D* h1_tResult_B0[8];
    TH1D* h1_Q2Result_B0[8];
    TH1D* h1_WResult_B0[8];
   
    h1_tResult[0] = new TH1D("h1_tResult_0", "-t_{eXBABE}, DEMP Events with Cuts, 5 < Q^{2} < 35; -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", 40, 0, 1.6);
    h1_Q2Result[0] = new TH1D("h1_Q2Result_0", "Q^{2}, DEMP Events with Cuts, 5 < Q^{2} < 35; Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", 60, 5, 35);
    h1_WResult[0] = new TH1D("h1_WResult_0", "W, DEMP Events with Cuts, 5 < Q^{2} < 35; W (GeV); Rate/(0.5 GeV) (Hz)", 80, -10, 30);

    if(ZDC == kTRUE){
      h1_tResult_ZDC[0] = new TH1D("h1_tResult_ZDC_0", "-t_{eXBABE}, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in ZDC only) ; -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", 40, 0, 1.6);
      h1_Q2Result_ZDC[0] = new TH1D("h1_Q2Result_ZDC_0", "Q^{2}, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in ZDC only); Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", 60, 5, 35);
      h1_WResult_ZDC[0] = new TH1D("h1_WResult_ZDC_0", "W, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in ZDC only); W (GeV); Rate/(0.5 GeV) (Hz)", 80, -10, 30);
    }
    if (B0 == kTRUE){
      h1_tResult_B0[0] = new TH1D("h1_tResult_B0_0", "-t_{eXBABE}, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in B0 only) ; -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", 40, 0, 1.6);
      h1_Q2Result_B0[0] = new TH1D("h1_Q2Result_B0_0", "Q^{2}, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in B0 only); Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", 60, 5, 35);
      h1_WResult_B0[0] = new TH1D("h1_WResult_B0_0", "W, DEMP Events with Cuts, 5 < Q^{2} < 35, (n in B0 only); W (GeV); Rate/(0.5 GeV) (Hz)", 80, -10, 30);
    }

    for(Int_t i = 0; i < 7; i++){
      h1_tResult[i+1] = new TH1D(Form("h1_tResult_%i", i+1), Form("-t_{eXBABE}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f; -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 40, 0, 1.6);
      h1_Q2Result[i+1] = new TH1D(Form("h1_Q2Result_%i", i+1), Form("Q^{2}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f; Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 60, 5, 35);
      h1_WResult[i+1] = new TH1D(Form("h1_WResult_%i", i+1), Form("W, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f; W (GeV); Rate/(0.5 GeV) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, -10, 30);
      if(ZDC == kTRUE){
	h1_tResult_ZDC[i+1] = new TH1D(Form("h1_tResult_ZDC_%i", i+1), Form("-t_{eXBABE}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in ZDC only); -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 40, 0, 1.6);
	h1_Q2Result_ZDC[i+1] = new TH1D(Form("h1_Q2Result_ZDC_%i", i+1), Form("Q^{2}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in ZDC only); Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 60, 5, 35);
	h1_WResult_ZDC[i+1] = new TH1D(Form("h1_WResult_ZDC_%i", i+1), Form("W, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in ZDC only); W (GeV); Rate/(0.5 GeV) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, -10, 30);
    }
      if(B0 == kTRUE){
	h1_tResult_B0[i+1] = new TH1D(Form("h1_tResult_B0_%i", i+1), Form("-t_{eXBABE}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in B0 only); -t_{eXBABE} (GeV^{2}); Rate/(0.04 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 40, 0, 1.6);
	h1_Q2Result_B0[i+1] = new TH1D(Form("h1_Q2Result_B0_%i", i+1), Form("Q^{2}, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in B0 only); Q^{2} (GeV^{2}); Rate/(0.5 GeV^{2}) (Hz)", Q2Vals[i], Q2Vals[i+1]), 60, 5, 35);
	h1_WResult_B0[i+1] = new TH1D(Form("h1_WResult_B0_%i", i+1), Form("W, DEMP Events with Cuts, %2.1f < Q^{2} < %2.1f, (n in B0 only); W (GeV); Rate/(0.5 GeV) (Hz)", Q2Vals[i], Q2Vals[i+1]), 80, -10, 30);
      }
    }
    gDirectory->cd("../");
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
