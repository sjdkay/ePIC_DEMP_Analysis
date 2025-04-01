// Stephen JD Kay - University of York
// Stephen.Kay@york.ac.uk
// 28/03/25
// Header file for new DEMP Analysis script

// Input file naming, hardcoded assuming certain convention, change as needed
TString InFilePath = "/home/sjdkay/Work/ePIC_EIC/DEMP/Love_DEMP_Pion_Analysis/InputFiles";
string ConstructFileName(TString InBeamE, TString Inpart, TString In_Q2, TString InBeamConfig, TString InDate){
  string FileName = Form("%s/EICreconOut_%s_ip6_%s_q2_%s_%s_Combined_%s_Pruned.root", InFilePath.Data(), InBeamE.Data(), Inpart.Data(), In_Q2.Data(), InBeamConfig.Data(), InDate.Data());
  
  return FileName;
}

Bool_t Good_eSc_Track, Good_Pi_Track, Good_nRec;
Double_t ThetaStar_Max, n_Emin, DeltaTheta_Min, DeltaTheta_Max, DeltaPhi_Min, DeltaPhi_Max, MissingMass_Tol, W_Tol, B0_ECut, B0_XYTol;

//Defining the four vectors
PxPyPzEVector Vec_eSc_MC;
PxPyPzEVector Vec_eSc_MC_NoAB;
PxPyPzEVector Vec_Pi_MC;
PxPyPzEVector Vec_Pi_MC_NoAB;
PxPyPzEVector Vec_n_MC;
PxPyPzEVector Vec_n_MC_NoAB;
RotationY rot; // initialized rotation vector
rot.SetAngle(0.025);
PxPyPzEVector Vec_nRot_MC;
PxPyPzEVector Vec_nRot_MC_NoAB;

PxPyPzEVector Vec_e_beam; // initialized the 4 vector for electron beam */
PxPyPzEVector Vec_p_beam; // initialized the 4 vector for proton beam */
PxPyPzEVector Vec_e_beam_NoAB; // initialized the 4 vector for proton beam for nbf */
PxPyPzEVector Vec_p_beam_NoAB; // initialized the 4 vector for proton beam for nbf */

PxPyPzEVector Vec_eSc_Rec;
PxPyPzEVector Vec_Pi_Rec;
PxPyPzEVector Vec_n_Rec;
PxPyPzEVector Vec_nRot_Rec;
PxPyPzEVector Vec_n_RecCorr;
PxPyPzEVector Vec_nRot_RecCorr;
XYZVector Vec_n_Vertex;

PxPyPzEVector Vec_Q_MC;
PxPyPzEVector Vec_Q_MC_NoAB;
PxPyPzEVector Vec_t_MC;
PxPyPzEVector Vec_t_MC_NoAB;

/* PxPyPzEVector virtphoton_nbftruth; // intialized the 4 vector for truth virtual photon for nbf */
/* PxPyPzEVector tnbftruth; // intialized the 4 vector for ttruth (-t)from first loop for nbf */
/* PxPyPzEVector tnbfalttruth; // intialized the 4 vector for ttruth (-t)from first loop for nbf */

/* PxPyPzEVector elec_rec; // initialized the 4 vector for reconstructed electron */
/* PxPyPzEVector pi_rec; // initialized the 4 vector for reconstructed pion */
/* PxPyPzEVector neut_rec; // initialized the 4 vector for reconstructed neutron */
/* PxPyPzEVector neut_rot_rec; // initialized the 4 vector for reconstructed neutron with a rotation of 25 mrad */

/* PxPyPzEVector virtphoton_truth; // intialized the 4 vector for truth virtual photon */
/* PxPyPzEVector ttruth; // intialized the 4 vector for ttruth (-t)from first loop */
/* PxPyPzEVector talttruth; // intialized the 4 vector for talttruth(-t) from second loop */

/* PxPyPzEVector virtphoton_rec; //intialized the 4 vector for reconstructed virtual photon */
/* PxPyPzEVector trec; // intialized the 4 vector for trec (-t)from first loop */
/* PxPyPzEVector taltrec; // intialized the 4 vector for taltrec(-t) from second loop */
/* PxPyPzEVector trecpT; // intialized the 4 vector for trecpT(-t) */
/* PxPyPzEVector trecpT_rot; // intialized the 4 vector for trecpT(-t) with a rotation of 25 mrad */
/* PxPyPzEVector p_miss_rec;  //intialized the 4 vector for missing momentum */
/* PxPyPzEVector p_miss_rot_rec; //intialized the 4 vector for missing momentum with a rotation of 25 mrad */
/* PxPyPzMVector neut_corr; // intialized the 4 vector for reconstructed corrected neutron */
/* PxPyPzEVector treccorr; // intialized the 4 vector for trecpT(-t) */

/* XYZVector neut_pos_hcal; // initialized the 3 vector for zdc position */
/* PxPyPzEVector neut_rec_hcal; // initialized the 4 vector for reconstructed neutorn in hcal */
/* PxPyPzEVector neut_rot_rec_hcal; // initialized the 4 vector for reconstructed neutron with a rotation of 25 mrad in hcal */
  
PxPyPzEVector cons_check;

int hcal_clus_size;
double neut_rec_p_hcal;
  
double neutMass = 0.93965420;
double eMass = 0.000510998950; //electron beam
double pMass = 0.93827208816; // proton beam
double PartE, NoABPartE; // Energy of the MC particles 
int eSc_Index, pi_Index, n_Index;

Double_t Q2_MC, t_MC, W_MC, y_MC, eps_MC;
Double_t Q2_MC_NoAB, t_MC_NoAB, W_MC_NoAB, y_MC_NoAB, eps_MC_NoAB;

/* double Q2_truth, W_truth, y_truth, t_truth, t_alttruth; // Truth kinematic variables */
/* double Q2_rec, W_rec, y_rec, t_rec, t_altrec, t_recpT, t_reccorr; // Reconstructed kinematic variables */
/* double neutPosX, neutPosY; // neutron position */
/* double nTheta_Diff, nPhi_Diff; */
/* double Q2_low, Q2_high, Pmiss; */
/* double t_nbftruth, t_nbfalttruth; */
  
/* //----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* // Defining initial colliding beams */
/* double eEng = 10; */
/* double e_pmag = sqrt(pow(eEng,2)-pow(eMass,2)); */
/* double e_p1 = 0.; */
/* double e_p2 = 0.; */
/* double e_p3 = -1*e_pmag; */
               
/* double pEng = 130; //change */
/* double p_pmag = sqrt(pow(pEng,2)-pow(pMass,2)); */
/* double c_a = 0.025; */
/* double p_p1 = -p_pmag*sin(c_a); */
/* double p_p2 = 0.; */
/* double p_p3 = p_pmag*cos(c_a); */

// Check files exist, can be opened and contain a relevant tree
Bool_t CheckFiles(TString Files[3]){
  Bool_t FileCheck = kTRUE;
  for (unsigned int i = 0;  i < 3; i++){
    if (gSystem->AccessPathName(Files[i]) == kTRUE){
      FileCheck = kFALSE;
      cout << "Input file - " << Files[i] << " not found." << endl;
      cout << "Check pathing and edit input arguments/DEMP_Analysis.h as needed!" << endl;
    }
    else{ // File exists, try to open it!
      TFile *tmpfile = TFile::Open(Files[i]);
      if (tmpfile && !tmpfile->IsZombie()) {
	TTree *tmptree = (TTree*)tmpfile->Get("events");
	// Ensure the file also contains a valid tree
	if (!tmptree) {
	  cout << "Tree 'events' not found in file: " << Files[i] << endl;
	  FileCheck = kFALSE;
	}
	tmpfile->Close();  // Close the file
	delete tmpfile;    // Delete the file pointer
      }
      else {
	cout << "Failed to open file: " << Files[i] <<endl;
	FileCheck = kFALSE;
	if (tmpfile) {
	  tmpfile->Close();  // Close the file if it was partially opened
	  delete tmpfile;    // Delete the file pointer
	}
      }
    }
  }
  return FileCheck;
}

void CalculateKinematicsMC(PxPyPzEVector eSc_MC, PxPyPzEVector pi_MC, PxPyPzEVector n_MC, PxPyPzEVector EBeam, PxPyPzEVector HBeam){
  Vec_Q_MC = (EBeam - eSc_MC); // Virtual photon beam vector
  Q2_MC = -1*(Vec_Q_MC.mag2());
  Vec_t_MC = (Vec_Q_MC - pi_MC);
  t_MC = -1*(Vec_t_MC.mag2());
  W_MC = (Vec_Q_MC + HBeam).mag();
  y_MC =(HBeam.Dot(Vec_Q_MC))/(HBeam.Dot(EBeam)); 
  eps_MC = (2*(1-y_MC))/(1+(pow(1-y_MC,2)));
}

void CalculateKinematicsMCNoAB(PxPyPzEVector eSc_MC, PxPyPzEVector pi_MC, PxPyPzEVector n_MC, PxPyPzEVector EBeam, PxPyPzEVector HBeam){
  Vec_Q_MC_NoAB = (EBeam - eSc_MC);
  Q2_MC_NoAB = -1*(Vec_Q_MC_NoAB.mag2());
  Vec_t_MC_NoAB = (Vec_Q_MC_NoAB - pi_MC);
  t_MC_NoAB = -1*(Vec_t_MC_NoAB.mag2());
  W_MC_NoAB = (Vec_Q_MC_NoAB + HBeam).mag();
  y_MC_NoAB =(HBeam.Dot(Vec_Q_MC_NoAB))/(HBeam.Dot(EBeam)); 
  eps_MC_NoAB = (2*(1-y_MC_NoAB))/(1+(pow(1-y_MC_NoAB,2)));
}

// Define set of cut values, check input and return appropriate cut values
void SetCutVals(Double_t Hadron_Beam_E){
  Double_t ExpectedVals[5]={41,100,130,250,275};
  
  // Check hadron beam input value, set to closest if not exactly equal. Forces sensible values
  if(Hadron_Beam_E != 41 | Hadron_Beam_E != 100 | Hadron_Beam_E != 130 | Hadron_Beam_E != 250 | Hadron_Beam_E != 275 ){
    Double_t tmpE = ExpectedVals[0];
    Double_t diff = abs(Hadron_Beam_E - tmpE);
    for(Int_t i = 0; i < 5; i++){
      Double_t tmp_diff = abs(Hadron_Beam_E-ExpectedVals[i]);
      if(tmp_diff < diff){
	tmpE = ExpectedVals[i];
	diff = tmp_diff;
      }
    }
    Hadron_Beam_E = tmpE;
  }

  ThetaStar_Max = 4.0;
  B0_ECut = 0.25;
  B0_XYTol = 50;
  
  if(Hadron_Beam_E == 41){
    n_Emin = 10;
    DeltaTheta_Min = -0.1;
    DeltaTheta_Max = 0.2;
    DeltaPhi_Min = 55;
    DeltaPhi_Max = 55;
    MissingMass_Tol= 0;
    W_Tol = 0;
  }
  else if(Hadron_Beam_E == 100){
    n_Emin =40;
    DeltaTheta_Min = -0.09;
    DeltaTheta_Max = 0.14;
    DeltaPhi_Min = 45;
    DeltaPhi_Max = 45;
    MissingMass_Tol=0 ;
    W_Tol = 0;
  }
  else if(Hadron_Beam_E == 130){
    n_Emin =40;
    DeltaTheta_Min = -0.09;
    DeltaTheta_Max = 0.14;
    DeltaPhi_Min = 45;
    DeltaPhi_Max = 45;
    MissingMass_Tol=0 ;
    W_Tol = 0;
  }
  else if(Hadron_Beam_E == 250){
    n_Emin = 120;
    DeltaTheta_Min = -0.07;
    DeltaTheta_Max = 0.17;
    DeltaPhi_Min = 80;
    DeltaPhi_Max = 80;
    MissingMass_Tol= 0;
    W_Tol = 0;
  }
  else if(Hadron_Beam_E == 275){
    n_Emin = 120;
    DeltaTheta_Min = -0.07;
    DeltaTheta_Max = 0.17;
    DeltaPhi_Min = 80;
    DeltaPhi_Max = 80;
    MissingMass_Tol= 0;
    W_Tol = 0;
  }
}

void DefHists(TString InBeamE, Bool_t EventDists, Bool_t Kinematics, Bool_t ZDC, Bool_t B0, Bool_t Tracking, Bool_t QA, Bool_t Results){

  // Fix number of energy, theta and phi bins in subsequent plots
  Int_t NBins_Energy = 200;
  Int_t NBins_Theta = 200;
  Int_t NBins_Phi = 200;

  Double_t ElecBeamE = ((TObjString *)((InBeamE.Tokenize("on"))->At(0)))->String().Atof();
  Double_t HadBeamE = ((TObjString *)((InBeamE.Tokenize("on"))->At(1)))->String().Atof();

  if (EventDists == kTRUE){
    TH2D* h2_eSc_pTheta_MC_NoAB = new TH2D("h2_eSc_pTheta_MC_NoAB", "e' MC Truth, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCMatched_NoAB = new TH2D("h2_eSc_pTheta_MCMatched_NoAB", "e' MC Truth (matched track), No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCAccept_NoAB = new TH2D("h2_eSc_pTheta_MCAccept_NoAB", "e' MC Truth Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MC = new TH2D("h2_eSc_pTheta_MC", "e' MC Truth; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCMatched = new TH2D("h2_eSc_pTheta_MCMatched", "e' MC Truth (matched track); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_MCAccept = new TH2D("h2_eSc_pTheta_MCAccept", "e' MC Truth Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_Reco = new TH2D("h2_eSc_pTheta_Reco", "e' Reconstructed ; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
    TH2D* h2_eSc_pTheta_RecoAccept = new TH2D("h2_eSc_pTheta_RecoAccept", "e' Reconstructed Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 120, 180, NBins_Energy, ElecBeamE-1, ElecBeamE+2);
  
    TH2D* h2_Pi_pTheta_MC_NoAB = new TH2D("h2_Pi_pTheta_MC_NoAB", "#pi MC Truth, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCMatched_NoAB = new TH2D("h2_Pi_pTheta_MCMatched_NoAB", "#pi MC Truth (matched track), No Beam Effets; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCAccept_NoAB = new TH2D("h2_Pi_pTheta_MCAccept_NoAB", "#pi MC Truth Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MC = new TH2D("h2_Pi_pTheta_MC", "#pi MC Truth; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCMatched = new TH2D("h2_Pi_pTheta_MCMatched", "#pi MC Truth (matched track); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_MCAccept = new TH2D("h2_Pi_pTheta_MCAccept", "#pi MC Truth Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_Reco = new TH2D("h2_Pi_pTheta_Reco", "#pi Reconstructed; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);
    TH2D* h2_Pi_pTheta_RecoAccept = new TH2D("h2_Pi_pTheta_RecoAccept", "#pi Reconstructed Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 60, NBins_Energy, 0, 100);

    // Hard coding the +50 here is a bit odd, should maybe re-define this in terms of bin widths
    TH2D* h2_n_pTheta_MC_NoAB = new TH2D("h2_n_pTheta_MC_NoAB", "Neutron MC Truth, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCAccept_NoAB = new TH2D("h2_n_pTheta_MCAccept_NoAB", "Neutron MC Truth Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MC = new TH2D("h2_n_pTheta_MC", "Neutron MC Truth; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCAccept = new TH2D("h2_n_pTheta_MCAccept", "Neutron MC Truth Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_Reco = new TH2D("h2_n_pTheta_Reco", "Neutron Reconstructed ; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_RecoAccept = new TH2D("h2_n_pTheta_RecoAccept", "Neutron Reconstructed Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_nRot_pTheta_Reco = new TH2D("h2_nRot_pTheta_Reco", "Neutron Reconstructed (Rotated 25 mrad); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_nRot_pTheta_RecoAccept = new TH2D("h2_nRot_pTheta_RecoAccept", "Neutron Reconstructed (Rotated 25 mrad) Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
  }
  
  if (Kinematics == kTRUE){
  }
  
  if (ZDC == kTRUE){
    TH2D* h2_n_XY_Reco = new TH2D("h2_n_XY_Reco", "Neutron reconstructed XY position at ZDC;x (mm) ;y (mm); Rate/bin (Hz)", 150,-1200,-600,150,-300,300);
    TH2D* h2_n_XY_RecoAccept = new TH2D("h2_n_XY_RecoAccept", "Neutron reconstructed XY position at ZDC;x (mm) ;y (mm); Rate/bin (Hz)", 150,-1200,-600,150,-300,300); 
    TH2D* h2_nRot_XY_Reco = new TH2D("h2_nRot_XY_Reco", "Neutron reconstructed (Rotated 25 mrad) XY position at ZDC;x (mm) ;y (mm); Rate/bin (Hz)", 100,-200,200,100,-200,200);
    TH2D* h2_nRot_XY_RecoAccept = new TH2D("h2_nRot_XY_RecoAccept", "Neutron reconstructed (Rotated 25 mrad) XY position at ZDC;x (mm) ;y (mm); Rate/bin (Hz)", 100,-200,200,100,-200,200); 
  }
  if (B0 == kTRUE){
    TH1D* h1_B0_nClusters = new TH1D("h1_B0_nClusters", "B0 Hit Multiplicity; N_{Clus}", 30, 0, 30);
    TH2D* h2_B0_XY_Raw = new TH2D("h2_B0_XY_Raw", "B0 XY Hit Position, raw all clusters; x (mm); y(mm)", 75, -325, -25, 75, -150, 150);
    TH2D* h2_B0_XY_Raw_EWeight = new TH2D("h2_B0_XY_Raw_EWeight", "B0 XY Hit Position, raw all clusters, energy weighted; x (mm); y(mm)", 75, -325, -25, 75, -150, 150);
    TH1D* h1_B0_nClusters_AcceptRaw = new TH1D("h1_B0_nClusters_AcceptRaw", "B0 Hit Multiplicity, number of clusters in event; N_{Clus}", 30, 0, 30);
    TH1D* h1_B0_nClusters_Accept = new TH1D("h1_B0_nClusters_Accept", "B0 Hit Multiplicity, number of accepted cluters; N_{Clus}", 30, 0, 30);
    TH2D* h2_B0_XY_Accept = new TH2D("h2_B0_XY_Accept", "B0 Reconstructed XY Hit Position; x (mm); y(mm)", 75, -325, -25, 75, -150, 150);
    TH2D* h2_B0_XY_AcceptWeighted = new TH2D("h2_B0_XY_AcceptWeighted", "B0 Reconstructed XY Hit Position; x (mm); y(mm); Rate/bin (Hz)", 75, -325, -25, 75, -150, 150);
    TH2D* h2_n_ETheta_RecAccept_B0 = new TH2D("h2_n_ETheta_RecAccept_B0", "B0 Reconstructed;#theta (Deg); E (GeV)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_RecAccept_B0 = new TH2D("h2_n_pTheta_RecAccept_B0", "B0 Reconstructed;#theta (Deg); p (GeV/c)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_nRot_pTheta_RecAccept_B0 = new TH2D("h2_nRot_pTheta_RecAccept_B0", "B0 Reconstructed (Rotated 25 mrad);#theta (Deg); p (GeV/c)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    
    TH2D* h2_n_pTheta_MC_B0 = new TH2D("h2_n_pTheta_MC_B0", "Neutron MC Truth (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCAccept_B0 = new TH2D("h2_n_pTheta_MCAccept_B0", "Neutron MC Truth Accepted (B0); #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_B0_XY_MCAccept = new TH2D("h2_B0_XY_MCAccept", "B0 MC Accepted XY Hit Position; x (mm); y(mm); Rate/bin (Hz)", 75, -325, -25, 75, -150, 150);
        
  }
  if (Tracking == kTRUE){
  }
  if (QA == kTRUE){
  }
  if (Results == kTRUE){
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
