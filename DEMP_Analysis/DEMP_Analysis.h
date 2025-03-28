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
  
//Defining the four vectors
ROOT::Math::PxPyPzEVector Vec_eSc_MC;
ROOT::Math::PxPyPzEVector Vec_eSc_MC_NoAb;
ROOT::Math::PxPyPzEVector Vec_Pi_MC;
ROOT::Math::PxPyPzEVector Vec_Pi_MC_NoAb;
ROOT::Math::PxPyPzEVector Vec_n_MC;
ROOT::Math::PxPyPzEVector Vec_n_MC_NoAb;
ROOT::Math::RotationY rot; // initialized rotation vector
rot.SetAngle(0.025);
ROOT::Math::PxPyPzEVector Vec_nRot_MC;
ROOT::Math::PxPyPzEVector Vec_nRot_MC_NoAb;

/*ROOT::Math::PxPyPzEVector elec_beam; // initialized the 4 vector for electron beam */
/* ROOT::Math::PxPyPzEVector prot_beam; // initialized the 4 vector for proton beam */
/* ROOT::Math::PxPyPzEVector prot_nbfbeam; // initialized the 4 vector for proton beam for nbf */

/* ROOT::Math::PxPyPzEVector elec_nbfmc; // initialized the 4 vector for truth nbf electron */
/* ROOT::Math::PxPyPzEVector pi_nbfmc; // initialized the 4 vector for truth nbf pion */
/* ROOT::Math::PxPyPzEVector neut_nbfmc; // initialized the 4 vector for truth nbf neutron */
  
/* ROOT::Math::PxPyPzEVector virtphoton_nbftruth; // intialized the 4 vector for truth virtual photon for nbf */
/* ROOT::Math::PxPyPzEVector tnbftruth; // intialized the 4 vector for ttruth (-t)from first loop for nbf */
/* ROOT::Math::PxPyPzEVector tnbfalttruth; // intialized the 4 vector for ttruth (-t)from first loop for nbf */
   
/* ROOT::Math::PxPyPzEVector elec_mc; // initialized the 4 vector for truth electron */
/* ROOT::Math::PxPyPzEVector pi_mc; // initialized the 4 vector for truth pion */
/* ROOT::Math::PxPyPzEVector neut_mc; // initialized the 4 vector for truth neutron */
/* ROOT::Math::PxPyPzEVector neut_rot_mc; // initialized the 4 vector for truth neutron with a rotation of 25 mrad */

/* ROOT::Math::PxPyPzEVector elec_rec; // initialized the 4 vector for reconstructed electron */
/* ROOT::Math::PxPyPzEVector pi_rec; // initialized the 4 vector for reconstructed pion */
/* ROOT::Math::PxPyPzEVector neut_rec; // initialized the 4 vector for reconstructed neutron */
/* ROOT::Math::PxPyPzEVector neut_rot_rec; // initialized the 4 vector for reconstructed neutron with a rotation of 25 mrad */

/* ROOT::Math::PxPyPzEVector virtphoton_truth; // intialized the 4 vector for truth virtual photon */
/* ROOT::Math::PxPyPzEVector ttruth; // intialized the 4 vector for ttruth (-t)from first loop */
/* ROOT::Math::PxPyPzEVector talttruth; // intialized the 4 vector for talttruth(-t) from second loop */

/* ROOT::Math::PxPyPzEVector virtphoton_rec; //intialized the 4 vector for reconstructed virtual photon */
/* ROOT::Math::PxPyPzEVector trec; // intialized the 4 vector for trec (-t)from first loop */
/* ROOT::Math::PxPyPzEVector taltrec; // intialized the 4 vector for taltrec(-t) from second loop */
/* ROOT::Math::PxPyPzEVector trecpT; // intialized the 4 vector for trecpT(-t) */
/* ROOT::Math::PxPyPzEVector trecpT_rot; // intialized the 4 vector for trecpT(-t) with a rotation of 25 mrad */
/* ROOT::Math::PxPyPzEVector p_miss_rec;  //intialized the 4 vector for missing momentum */
/* ROOT::Math::PxPyPzEVector p_miss_rot_rec; //intialized the 4 vector for missing momentum with a rotation of 25 mrad */
/* ROOT::Math::PxPyPzMVector neut_corr; // intialized the 4 vector for reconstructed corrected neutron */
/* ROOT::Math::PxPyPzEVector treccorr; // intialized the 4 vector for trecpT(-t) */

/* ROOT::Math::XYZVector neut_pos_hcal; // initialized the 3 vector for zdc position */
/* ROOT::Math::PxPyPzEVector neut_rec_hcal; // initialized the 4 vector for reconstructed neutorn in hcal */
/* ROOT::Math::PxPyPzEVector neut_rot_rec_hcal; // initialized the 4 vector for reconstructed neutron with a rotation of 25 mrad in hcal */
  
ROOT::Math::PxPyPzEVector cons_check;

int hcal_clus_size;
double neut_rec_p_hcal;
  
double neutMass = 0.93965420;
double eMass = 0.000510998950; //electron beam
double pMass = 0.93827208816; // proton beam
double PartEng, NoAbPartEng; // Energy of the MC particles 
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

void DefHists(TString InBeamE, Bool_t EventDists, Bool_t Kinematics, Bool_t ZDC, Bool_t B0, Bool_t Tracking, Bool_t QA, Bool_t Results){

  // Fix number of energy, theta and phi bins in subsequent plots
  Int_t NBins_Energy = 200;
  Int_t NBins_Theta = 200;
  Int_t NBins_Phi = 200;

  Double_t ElecBeamE = ((TObjString *)((InBeamE.Tokenize("on"))->At(0)))->String().Atof();
  Double_t HadBeamE = ((TObjString *)((InBeamE.Tokenize("on"))->At(1)))->String().Atof();

  if (EventDists == kTRUE){
    TH2D* h2_eSc_pTheta_MC_NoAB = new TH2D("h2_eSc_pTheta_MC_NoAB", "e' MC Truth, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 130, 180, NBins_Energy, ElecBeamE-0.5, ElecBeamE+1.5);
    TH2D* h2_eSc_pTheta_MC = new TH2D("h2_eSc_pTheta_MC", "e' MC Truth; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 130, 180, NBins_Energy, ElecBeamE-0.5, ElecBeamE+1.5);
    TH2D* h2_eSc_pTheta_MCAccept_NoAB = new TH2D("h2_eSc_pTheta_MCAccept_NoAB", "e' MC Truth Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 130, 180, NBins_Energy, ElecBeamE-0.5, ElecBeamE+1.5);
    TH2D* h2_eSc_pTheta_MCAccept = new TH2D("h2_eSc_pTheta_MCAccept", "e' MC Truth Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 130, 180, NBins_Energy, ElecBeamE-0.5, ElecBeamE+1.5);
    TH2D* h2_eSc_pTheta_Reco = new TH2D("h2_eSc_pTheta_Reco", "e' Reconstructed ; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 130, 180, NBins_Energy, ElecBeamE-0.5, ElecBeamE+1.5);
    TH2D* h2_eSc_pTheta_RecoAccept = new TH2D("h2_eSc_pTheta_RecoAccept", "e' Reconstructed Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 130, 180, NBins_Energy, ElecBeamE-0.5, ElecBeamE+1.5);
    
    TH2D* h2_pi_pTheta_MC_NoAB = new TH2D("h2_pi_pTheta_MC_NoAB", "#pi MC Truth, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 50, NBins_Energy, 0, 100);
    TH2D* h2_pi_pTheta_MC = new TH2D("h2_pi_pTheta_MC", "#pi MC Truth; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 50, NBins_Energy, 0, 100);
    TH2D* h2_pi_pTheta_MCAccept_NoAB = new TH2D("h2_pi_pTheta_MCAccept_NoAB", "#pi MC Truth Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 50, NBins_Energy, 0, 100);
    TH2D* h2_pi_pTheta_MCAccept = new TH2D("h2_pi_pTheta_MCAccept", "#pi MC Truth Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 50, NBins_Energy, 0, 100);
    TH2D* h2_pi_pTheta_Reco = new TH2D("h2_pi_pTheta_Reco", "#pi Reconstructed; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 50, NBins_Energy, 0, 100);
    TH2D* h2_pi_pTheta_RecoAccept = new TH2D("h2_pi_pTheta_RecoAccept", "#pi Reconstructed Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta, 0, 50, NBins_Energy, 0, 100);

    // Hard coding the +50 here is a bit odd, should maybe re-define this in terms of bin widths
    TH2D* h2_n_pTheta_MC_NoAB = new TH2D("h2_n_pTheta_MC_NoAB", "Neutron MC Truth, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MC = new TH2D("h2_n_pTheta_MC", "Neutron MC Truth; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCAccept_NoAB = new TH2D("h2_n_pTheta_MCAccept_NoAB", "Neutron MC Truth Accepted, No Beam Effects; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_MCAccept = new TH2D("h2_n_pTheta_MCAccept", "Neutron MC Truth Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_Reco = new TH2D("h2_n_pTheta_Reco", "Neutron Reconstructed ; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
    TH2D* h2_n_pTheta_RecoAccept = new TH2D("h2_n_pTheta_RecoAccept", "Neutron  Reconstructed Accepted; #theta (deg); P(GeV/C); Rate/bin (Hz)", NBins_Theta+50, 0, 2.5, NBins_Energy, 0, HadBeamE+(0.2*HadBeamE));
  }
  
  if (Kinematics == kTRUE){
  }
  if (ZDC == kTRUE){
  }
  if (B0 == kTRUE){
  }
  if (Tracking == kTRUE){
  }
  if (QA == kTRUE){
  }
  if (Results == kTRUE){
  }
  
}

// Histogram filling functions, avoids needing histograms defined in main file. Additionally, makes it so the main code doesn't actually care if the histogram is defined or not. If it doesn't exist, nothing happens
void FillHist1D(TString Histname, Double_t Value, Double_t W){
  if(gDirectory->FindObject(Histname) != 0){ // Check histogramexists, if it does, fill it
    ((TH1D*)gDirectory->FindObject(Histname))->Fill(Value, W);
  }
}

void FillHist2D(TString Histname, Double_t Value, Double_t Value2, Double_t W){
  if(gDirectory->FindObject(Histname) != 0){ // Check histogram exists, if it does, fill it
    ((TH2D*)gDirectory->FindObject(Histname))->Fill(Value, Value2, W);
  }
}
