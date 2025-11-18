// Stephen JD Kay - University of York
// Stephen.Kay@york.ac.uk
// 28/03/25
// Header file for new DEMP Analysis script

// Input file naming, hardcoded assuming certain convention, change as needed

TString InFilePath = Form("%s/InputFiles", gSystem->pwd());

string ConstructFileName(TString InBeamE, TString Inpart, TString In_Q2, TString InBeamConfig, TString InDate){
  string FileName = Form("%s/EICreconOut_%s_ip6_%s_q2_%s_%s_Combined_%s_Pruned.root", InFilePath.Data(), InBeamE.Data(), Inpart.Data(), In_Q2.Data(), InBeamConfig.Data(), InDate.Data());  
  return FileName;
}

Bool_t CampaignFiles, Good_eSc_Clust, Good_FECal_Clust, Good_BECal_Clust, Good_eSc_Track, Good_Pi_Track, Good_nRec, nZDCHit, nB0Hit, DEMP_PassCuts;
Double_t ThetaStar_Max, n_Emin, ZDCDeltaTheta_Min, ZDCDeltaTheta_Max, ZDCDeltaPhi_Min, ZDCDeltaPhi_Max, B0DeltaTheta_Min, B0DeltaTheta_Max, B0DeltaPhi_Min, B0DeltaPhi_Max, MissingMass_Tol, W_Tol, W_High, B0_ECut, B0_XYTol, SigmaEPzTol_Low, SigmaEPzTol_High;

int nEntries = 0;
int EventCounter = 0;

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

PxPyPzEVector Vec_tmp;
//PxPyPzEVector Vec_eSc_Rec;
PtEtaPhiMVector Vec_eSc_Rec;
PxPyPzEVector Vec_Pi_Rec;
PxPyPzEVector Vec_n_Rec;
PxPyPzEVector Vec_nRot_Rec;
PxPyPzEVector Vec_n_RecCorr;
PxPyPzEVector Vec_PMiss_Rec;
PxPyPzEVector Vec_PMissRot_Rec;
PxPyPzEVector Vec_PMiss_DEMP_Rec;

XYZVector Vec_n_Vertex;

PxPyPzEVector Vec_Q_MC;
PxPyPzEVector Vec_Q_MC_NoAB;
PxPyPzEVector Vec_t_MC;
PxPyPzEVector Vec_t_MC_NoAB;
PxPyPzEVector Vec_Q_Rec;
PxPyPzEVector Vec_t_BABE;
PxPyPzEVector Vec_t_eX;
PxPyPzEVector Vec_t_eXPT;
PxPyPzEVector Vec_t_eXBABE;

int hcal_clus_size;
double neut_rec_p_hcal;
  
double neutMass = 0.93965420;
double eMass = 0.000510998950; //electron beam
double pMass = 0.93827208816; // proton beam
double PartE, NoABPartE; // Energy of the MC particles 
double ClusE, eSc_P, EpRatio;
int eSc_Index, pi_Index, n_Index, MaxClusIndex, MaxBClusIndex;

Double_t Q2_MC, t_MC, W_MC, y_MC, x_MC, eps_MC;
Double_t Q2_MC_NoAB, t_MC_NoAB, W_MC_NoAB, y_MC_NoAB, x_MC_NoAB, eps_MC_NoAB;
Double_t Q2_Rec, W_Rec, y_Rec, x_Rec, eps_Rec, t_BABE, t_eX, t_eXPT, t_eXBABE; // Add other methods if needed
Double_t nTheta_Diff, nPhi_Diff, MMiss, MMiss2, nRotTheta_Diff, nRotPhi_Diff, SigmaEPz;
//Double_t Q2Vals[8]={5, 7.5, 10, 15, 20, 25, 30, 35};
Double_t Q2Vals[31]={5, 6, 7, 8 ,9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

Double_t Q2_JB, y_JB, x_JB, Q2_DA, y_DA, x_DA, Q2_Sig, y_Sig, x_Sig, delta_h, pt2_h, alpha_e, alpha_h, eps_DA;

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
	nEntries+=tmptree->GetEntries();
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

// Add details for an ePIC plot
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

// Check files exist, can be opened and contain a relevant tree
Bool_t CheckFile(TString File){
  Bool_t FileCheck = kTRUE;
  if (gSystem->AccessPathName(File) == kTRUE){
    FileCheck = kFALSE;
    cout << "Input file - " << File << " not found." << endl;
    cout << "Check pathing and edit input arguments/DEMP_Analysis.h as needed!" << endl;
  }
  else{ // File exists, try to open it!
    TFile *tmpfile = TFile::Open(File);
    if (tmpfile && !tmpfile->IsZombie()) {
      TTree *tmptree = (TTree*)tmpfile->Get("events");
      // Ensure the file also contains a valid tree
      if (!tmptree) {
	cout << "Tree 'events' not found in file: " << File << endl;
	FileCheck = kFALSE;
      }
      nEntries+=tmptree->GetEntries();
      tmpfile->Close();  // Close the file
      delete tmpfile;    // Delete the file pointer
    }
    else {
      cout << "Failed to open file: " << File <<endl;
      FileCheck = kFALSE;
      if (tmpfile) {
	tmpfile->Close();  // Close the file if it was partially opened
	delete tmpfile;    // Delete the file pointer
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
  x_MC = Q2_MC/(4*EBeam.E()*HBeam.E()*y_MC);  
  eps_MC = (2*(1-y_MC))/(1+(pow(1-y_MC,2)));
}

void CalculateKinematicsMCNoAB(PxPyPzEVector eSc_MC, PxPyPzEVector pi_MC, PxPyPzEVector n_MC, PxPyPzEVector EBeam, PxPyPzEVector HBeam){
  Vec_Q_MC_NoAB = (EBeam - eSc_MC);
  Q2_MC_NoAB = -1*(Vec_Q_MC_NoAB.mag2());
  Vec_t_MC_NoAB = (Vec_Q_MC_NoAB - pi_MC);
  t_MC_NoAB = -1*(Vec_t_MC_NoAB.mag2());
  W_MC_NoAB = (Vec_Q_MC_NoAB + HBeam).mag();
  y_MC_NoAB =(HBeam.Dot(Vec_Q_MC_NoAB))/(HBeam.Dot(EBeam)); 
  x_MC_NoAB = Q2_MC_NoAB/(4*EBeam.E()*HBeam.E()*y_MC_NoAB);  
  eps_MC_NoAB = (2*(1-y_MC_NoAB))/(1+(pow(1-y_MC_NoAB,2)));
}

void CalculateBasicKinematics_DEMPRec(PtEtaPhiMVector eSc_Rec, PxPyPzEVector pi_Rec, PxPyPzEVector EBeam, PxPyPzEVector HBeam){
  Vec_Q_Rec = (EBeam - eSc_Rec);
  Q2_Rec = -1*(Vec_Q_Rec.mag2());
  W_Rec = (Vec_Q_Rec + HBeam).mag();
  y_Rec =(HBeam.Dot(Vec_Q_Rec))/(HBeam.Dot(EBeam));
  x_Rec = Q2_Rec/(4*EBeam.E()*HBeam.E()*y_Rec);
  eps_Rec = (2*(1-y_Rec))/(1+(pow(1-y_Rec,2)));
}

void CalculateKinematics_Q2Alt_DEMPRec(PtEtaPhiMVector eSc_Rec, PxPyPzEVector pi_Rec, PxPyPzEVector n_Rec, PxPyPzEVector EBeam, PxPyPzEVector HBeam){
  delta_h = (pi_Rec.E() + n_Rec.E()) - (pi_Rec.Pz() + n_Rec.Pz());
  pt2_h = (pow((pi_Rec.Px()+n_Rec.Px()),2))+(pow((pi_Rec.Py()+n_Rec.Py()),2));
  alpha_e = tan((eSc_Rec.Theta()/2));
  alpha_h = delta_h/(sqrt(pt2_h));
  y_JB = delta_h/(2*EBeam.E());
  Q2_JB = pt2_h/(1-y_JB);
  x_JB = Q2_JB/(4*EBeam.E()*HBeam.E()*y_JB);
  y_DA = (alpha_h)/(alpha_e + alpha_h);
  Q2_DA = (4*EBeam.E()*EBeam.E())/(alpha_e*(alpha_e +alpha_h));
  x_DA = Q2_DA/(4*EBeam.E()*HBeam.E()*y_DA);
  eps_DA = (2*(1-y_DA))/(1+(pow(1-y_DA,2)));
  y_Sig = delta_h/(delta_h + (eSc_Rec.E()*(1-cos(eSc_Rec.Theta()))));
  Q2_Sig = (pow(eSc_Rec.E(),2)*pow(sin(eSc_Rec.Theta()),2))/(1-y_Sig);
  x_Sig = Q2_Sig/(4*EBeam.E()*HBeam.E()*y_Sig);
}

void CorrectNeutronTrack(PtEtaPhiMVector eSc_Rec, PxPyPzEVector pi_Rec, PxPyPzEVector n_Rec, PxPyPzEVector EBeam, PxPyPzEVector HBeam){
  Vec_PMiss_Rec = (EBeam + HBeam) - (eSc_Rec + pi_Rec);
  Vec_PMissRot_Rec = rot*Vec_PMiss_Rec;
  Vec_n_RecCorr.SetPxPyPzE(Vec_PMiss_Rec.P()*sin(n_Rec.Theta())*cos(n_Rec.Phi()), Vec_PMiss_Rec.P()*sin(n_Rec.Theta())*sin(n_Rec.Phi()), Vec_PMiss_Rec.P()*cos(n_Rec.Theta()), sqrt(pow(Vec_PMiss_Rec.P(),2)+(pow(neutMass,2))));
  Vec_PMiss_DEMP_Rec = (EBeam + HBeam) - (eSc_Rec + pi_Rec + Vec_n_RecCorr);
}

void Calculate_t_DEMPRec(PtEtaPhiMVector eSc_Rec, PxPyPzEVector pi_Rec, PxPyPzEVector n_Rec, PxPyPzEVector n_RecCorr, PxPyPzEVector EBeam, PxPyPzEVector HBeam){
  Vec_t_BABE = (HBeam - n_Rec);
  Vec_t_eX = ((EBeam - eSc_Rec) - pi_Rec);
  Vec_t_eXPT = rot*(eSc_Rec + pi_Rec); // Rotate vetors prior to getting perpendicular component
  Vec_t_eXBABE = (HBeam - n_RecCorr);
  t_BABE = -1*(Vec_t_BABE.mag2());
  t_eX = -1*(Vec_t_eX.mag2());
  t_eXPT = Vec_t_eXPT.Perp2();
  t_eXBABE = -1*(Vec_t_eXBABE.mag2());
}

// Define set of cut values, check input and return appropriate cut values
void SetCutVals(Double_t Elec_Beam_E, Double_t Hadron_Beam_E){

  Double_t EExpectedVals[3]={5,10,18};
  Double_t HExpectedVals[5]={41,100,130,250,275};
  
  // Check electron beam input value, set to closest if not exactly equal. Forces sensible values
  if(Elec_Beam_E != 5 | Elec_Beam_E != 10 | Elec_Beam_E != 18 ){
    Double_t tmpE = EExpectedVals[0];
    Double_t diff = abs(Elec_Beam_E - tmpE);
    for(Int_t i = 0; i < 5; i++){
      Double_t tmp_diff = abs(Elec_Beam_E-EExpectedVals[i]);
      if(tmp_diff < diff){
	tmpE = EExpectedVals[i];
	diff = tmp_diff;
      }
    }
    Elec_Beam_E = tmpE;
  }
  
  // Check hadron beam input value, set to closest if not exactly equal. Forces sensible values
  if(Hadron_Beam_E != 41 | Hadron_Beam_E != 100 | Hadron_Beam_E != 130 | Hadron_Beam_E != 250 | Hadron_Beam_E != 275 ){
    Double_t tmpE = HExpectedVals[0];
    Double_t diff = abs(Hadron_Beam_E - tmpE);
    for(Int_t i = 0; i < 5; i++){
      Double_t tmp_diff = abs(Hadron_Beam_E-HExpectedVals[i]);
      if(tmp_diff < diff){
	tmpE = HExpectedVals[i];
	diff = tmp_diff;
      }
    }
    Hadron_Beam_E = tmpE;
  }

  SigmaEPzTol_Low = 1.8*Elec_Beam_E;
  SigmaEPzTol_High = 2.2*Elec_Beam_E;
  ThetaStar_Max = 4.0;
  B0_ECut = 0.25;
  B0_XYTol = 50;
  
  if(Hadron_Beam_E == 41){
    n_Emin = 10;
    ZDCDeltaTheta_Min = -0.1;
    ZDCDeltaTheta_Max = 0.2;
    ZDCDeltaPhi_Min = -55;
    ZDCDeltaPhi_Max = 55;
    B0DeltaTheta_Min = -0.2;
    B0DeltaTheta_Max = 0.2;
    B0DeltaPhi_Min = -25;
    B0DeltaPhi_Max = 25;
    MissingMass_Tol= 0;
    W_Tol = 0;
    W_High = 15;
  }
  else if(Hadron_Beam_E == 100){
    n_Emin =40;
    ZDCDeltaTheta_Min = -0.09;
    ZDCDeltaTheta_Max = 0.14;
    ZDCDeltaPhi_Min = -55;
    ZDCDeltaPhi_Max = 55;
    B0DeltaTheta_Min = -0.8;
    B0DeltaTheta_Max = 0.7;
    B0DeltaPhi_Min = -30;
    B0DeltaPhi_Max = 30;
    MissingMass_Tol=0 ;
    W_Tol = 0;
    W_High = 15;
  }
  else if(Hadron_Beam_E == 130){
    n_Emin =40;
    ZDCDeltaTheta_Min = -0.09;
    ZDCDeltaTheta_Max = 0.14;
    ZDCDeltaPhi_Min = -55;
    ZDCDeltaPhi_Max = 55;
    B0DeltaTheta_Min = -0.8;
    B0DeltaTheta_Max = 0.7;
    B0DeltaPhi_Min = -30;
    B0DeltaPhi_Max = 30;
    MissingMass_Tol=0 ;
    W_Tol = 0;
    W_High = 15;
  }
  else if(Hadron_Beam_E == 250){
    n_Emin = 120;
    ZDCDeltaTheta_Min = -0.07;
    ZDCDeltaTheta_Max = 0.17;
    ZDCDeltaPhi_Min = -80;
    ZDCDeltaPhi_Max = 80;
    B0DeltaTheta_Min = -0.07;
    B0DeltaTheta_Max = 0.17;
    B0DeltaPhi_Min = -80;
    B0DeltaPhi_Max = 80;
    MissingMass_Tol= 0;
    W_Tol = 0;
    W_High = 20;
  }
  else if(Hadron_Beam_E == 275){
    n_Emin = 120;
    ZDCDeltaTheta_Min = -0.07;
    ZDCDeltaTheta_Max = 0.17;
    ZDCDeltaPhi_Min = -80;
    ZDCDeltaPhi_Max = 80;
    B0DeltaTheta_Min = -0.07;
    B0DeltaTheta_Max = 0.17;
    B0DeltaPhi_Min = -80;
    B0DeltaPhi_Max = 80;
    MissingMass_Tol= 0;
    W_Tol = 0;
    W_High = 25;
  }
}

void SetDirectories(Bool_t EventDist, Bool_t Kin, Bool_t ZDC, Bool_t B0, Bool_t QA, Bool_t Results){
  if(EventDist == kTRUE){
    gDirectory->mkdir("EventDists");
    gDirectory->mkdir("EventDists/MC");
    gDirectory->mkdir("EventDists/Reco");
  }
  if(Kin == kTRUE){
    gDirectory->mkdir("KinematicDists");
    gDirectory->mkdir("KinematicDists/MC");
    gDirectory->mkdir("KinematicDists/Reco");
    if(ZDC == kTRUE){
      gDirectory->mkdir("KinematicDists/MC/ZDC");
      gDirectory->mkdir("KinematicDists/Reco/ZDC");
    }
    if(B0 == kTRUE){
      gDirectory->mkdir("KinematicDists/MC/B0");
      gDirectory->mkdir("KinematicDists/Reco/B0");
    }
  }
  if(ZDC == kTRUE){
    gDirectory->mkdir("ZDCDists");
    gDirectory->mkdir("ZDCDists/MC");
    gDirectory->mkdir("ZDCDists/Reco");
  }
  if(B0 == kTRUE){
    gDirectory->mkdir("B0Dists");
    gDirectory->mkdir("B0Dists/MC");
    gDirectory->mkdir("B0Dists/Reco");
  }
  if(QA == kTRUE){
    gDirectory->mkdir("QADists");
    gDirectory->mkdir("QADists/Kin");
    gDirectory->mkdir("QADists/PartRes");
    gDirectory->mkdir("QADists/Efficiencies");
    gDirectory->mkdir("QADists/tComp");
    gDirectory->mkdir("QADists/Q2_Alt");
  }
  if(Results == kTRUE){
    gDirectory->mkdir("ResultsDists");
    gDirectory->mkdir("ResultsDists/Exclusive_Paper_Plots");
    gDirectory->mkdir("ResultsDists/tEff_Plots");
  }
}

void WriteResultsPDF(TString OutDir, TString InBeamE, TString InDate, TString InBeamConfig, TString Inpart, Bool_t Results){

  if (Results == kTRUE){
    TH1D* tmpHist1D;
    TH1D* tmpHist1D_2;
    TH2D* tmpHist2D;
    TString Outpdf = Form("%s/%s_Results_Plots.pdf", OutDir.Data(), InBeamE.Data());
  
    gDirectory->cd("ResultsDists/Exclusive_Paper_Plots");

    TCanvas* c_Q2_Result = new TCanvas("c_Q2_Result", "Q2 MC vs Reco", 100, 0, 2560, 1920);
    c_Q2_Result->Divide(2,2);
    c_Q2_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMPQ2_MC"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_Q2_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMPQ2_Rec"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_Q2_Result->cd(3);
    tmpHist1D->Draw("HISTERR");
    tmpHist1D_2->Draw("SAMEHISTERR");
    c_Q2_Result->cd(4);
    TLegend *Q2_Legend = new TLegend(0.1, 0.1, 0.9, 0.9);
    Q2_Legend->SetTextSize(0.05);
    Q2_Legend->AddEntry(tmpHist1D, "MC Truth", "l");
    Q2_Legend->AddEntry(tmpHist1D_2, "Rec (DA)", "l");
    Q2_Legend->Draw();
    c_Q2_Result->Print(Outpdf + "(" ); // First print command
  
    TCanvas* c_x_Result = new TCanvas("c_x_Result", "x MC vs Rec", 100, 0, 2560, 1920);
    c_x_Result->Divide(2,2);
    c_x_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMPx_MC"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_x_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMPx_Rec"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_x_Result->cd(3);
    tmpHist1D->Draw("HISTERR");
    tmpHist1D_2->Draw("SAMEHISTERR");
    c_x_Result->cd(4);
    TLegend *x_Legend = new TLegend(0.1, 0.1, 0.9, 0.9);
    x_Legend->SetTextSize(0.05);
    x_Legend->AddEntry(tmpHist1D, "MC Truth", "l");
    x_Legend->AddEntry(tmpHist1D_2, "Rec (DA)", "l");
    x_Legend->Draw();
    c_x_Result->Print(Outpdf);

    TCanvas* c_y_Result = new TCanvas("c_y_Result", "y MC vs Rec", 100, 0, 2560, 1920);
    c_y_Result->Divide(2,2);
    c_y_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMPy_MC"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_y_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMPy_Rec"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_y_Result->cd(3);
    tmpHist1D->Draw("HISTERR");
    tmpHist1D_2->Draw("SAMEHISTERR");
    c_y_Result->cd(4);
    TLegend *y_Legend = new TLegend(0.1, 0.1, 0.9, 0.9);
    y_Legend->SetTextSize(0.05);
    y_Legend->AddEntry(tmpHist1D, "MC Truth", "l");
    y_Legend->AddEntry(tmpHist1D_2, "Rec (DA)", "l");
    y_Legend->Draw();
    c_y_Result->Print(Outpdf);

    TCanvas* c_Delta_Result = new TCanvas("c_Delta_Result", "dQ2/dx/dy", 100, 0, 2560, 1920);
    c_Delta_Result->Divide(2,2);
    c_Delta_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_dQ2"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_Delta_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_dx"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_Delta_Result->cd(3);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_dy"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_Delta_Result->Print(Outpdf);// Last print command

    TCanvas* c_eScTheta_Result = new TCanvas("c_eScTheta_Result", "eSc Theta MC vs Rec", 100, 0, 2560, 1920);
    c_eScTheta_Result->Divide(2,2);
    c_eScTheta_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_eScTheta_MC"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_eScTheta_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_eScTheta_Rec"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_eScTheta_Result->cd(3);
    tmpHist1D->Draw("HISTERR");
    tmpHist1D_2->Draw("SAMEHISTERR");
    c_eScTheta_Result->cd(4);
    TLegend *eSc_Theta_Legend = new TLegend(0.1, 0.1, 0.9, 0.9);
    eSc_Theta_Legend->SetTextSize(0.05);
    eSc_Theta_Legend->AddEntry(tmpHist1D, "MC Truth", "l");
    eSc_Theta_Legend->AddEntry(tmpHist1D_2, "Rec", "l");
    eSc_Theta_Legend->Draw();
    c_eScTheta_Result->Print(Outpdf);

    TCanvas* c_eScE_Result = new TCanvas("c_eScE_Result", "eSc E MC vs Rec", 100, 0, 2560, 1920);
    c_eScE_Result->Divide(2,2);
    c_eScE_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_eScE_MC"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_eScE_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_eScE_Rec"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_eScE_Result->cd(3);
    tmpHist1D->Draw("HISTERR");
    tmpHist1D_2->Draw("SAMEHISTERR");
    c_eScE_Result->cd(4);
    TLegend *eSc_E_Legend = new TLegend(0.1, 0.1, 0.9, 0.9);
    eSc_E_Legend->SetTextSize(0.05);
    eSc_E_Legend->AddEntry(tmpHist1D, "MC Truth", "l");
    eSc_E_Legend->AddEntry(tmpHist1D_2, "Rec", "l");
    eSc_E_Legend->Draw();
    c_eScE_Result->Print(Outpdf);

    TCanvas* c_piEPz_Result = new TCanvas("c_piEPz_Result", "Pi E-Pz MC vs Rec", 100, 0, 2560, 1920);
    c_piEPz_Result->Divide(2,2);
    c_piEPz_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_piEPz_MC"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_piEPz_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_piEPz_Rec"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_piEPz_Result->cd(3);
    tmpHist1D->Draw("HISTERR");
    tmpHist1D_2->Draw("SAMEHISTERR");
    c_piEPz_Result->cd(4);
    TLegend *Pi_EPz_Legend = new TLegend(0.1, 0.1, 0.9, 0.9);
    Pi_EPz_Legend->SetTextSize(0.05);
    Pi_EPz_Legend->AddEntry(tmpHist1D, "MC Truth", "l");
    Pi_EPz_Legend->AddEntry(tmpHist1D_2, "Rec", "l");
    Pi_EPz_Legend->Draw();
    c_piEPz_Result->Print(Outpdf);

    TCanvas* c_piPt_Result = new TCanvas("c_piPt_Result", "Pi E-Pz MC vs Rec", 100, 0, 2560, 1920);
    c_piPt_Result->Divide(2,2);
    c_piPt_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_piPt_MC"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_piPt_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_piPt_Rec"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_piPt_Result->cd(3);
    tmpHist1D->Draw("HISTERR");
    tmpHist1D_2->Draw("SAMEHISTERR");
    c_piPt_Result->cd(4);
    TLegend *Pi_Pt_Legend = new TLegend(0.1, 0.1, 0.9, 0.9);
    Pi_Pt_Legend->SetTextSize(0.05);
    Pi_Pt_Legend->AddEntry(tmpHist1D, "MC Truth", "l");
    Pi_Pt_Legend->AddEntry(tmpHist1D_2, "Rec", "l");
    Pi_Pt_Legend->Draw();
    c_piPt_Result->Print(Outpdf);

    TCanvas* c_nEPz_Result = new TCanvas("c_nEPz_Result", "n E-Pz MC vs Rec", 100, 0, 2560, 1920);
    c_nEPz_Result->Divide(2,2);
    c_nEPz_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_nEPz_MC"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_nEPz_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_nEPz_Rec"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_nEPz_Result->cd(3);
    tmpHist1D->Draw("HISTERR");
    tmpHist1D_2->Draw("SAMEHISTERR");
    c_nEPz_Result->cd(4);
    TLegend *n_EPz_Legend = new TLegend(0.1, 0.1, 0.9, 0.9);
    n_EPz_Legend->SetTextSize(0.05);
    n_EPz_Legend->AddEntry(tmpHist1D, "MC Truth", "l");
    n_EPz_Legend->AddEntry(tmpHist1D_2, "Rec", "l");
    n_EPz_Legend->Draw();
    c_nEPz_Result->Print(Outpdf);

    TCanvas* c_nPt_Result = new TCanvas("c_nPt_Result", "n E-Pz MC vs Rec", 100, 0, 2560, 1920);
    c_nPt_Result->Divide(2,2);
    c_nPt_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_nPt_MC"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_nPt_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_nPt_Rec"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_nPt_Result->cd(3);
    tmpHist1D->Draw("HISTERR");
    tmpHist1D_2->Draw("SAMEHISTERR");
    c_nPt_Result->cd(4);
    TLegend *n_Pt_Legend = new TLegend(0.1, 0.1, 0.9, 0.9);
    n_Pt_Legend->SetTextSize(0.05);
    n_Pt_Legend->AddEntry(tmpHist1D, "MC Truth", "l");
    n_Pt_Legend->AddEntry(tmpHist1D_2, "Rec", "l");
    n_Pt_Legend->Draw();
    c_nPt_Result->Print(Outpdf);
    
    TCanvas* c_t_Result = new TCanvas("c_t_Result", "-t MC vs Rec", 100, 0, 2560, 1920);
    c_t_Result->Divide(2,2);
    c_t_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_tMC"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_t_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_tRec"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_t_Result->cd(3);
    tmpHist1D->Draw("HISTERR");
    tmpHist1D_2->Draw("SAMEHISTERR");
    c_t_Result->cd(4);
    TLegend *t_Legend = new TLegend(0.1, 0.1, 0.9, 0.9);
    t_Legend->SetTextSize(0.05);
    t_Legend->AddEntry(tmpHist1D, "MC Truth", "l");
    t_Legend->AddEntry(tmpHist1D_2, "Rec (tEXBABE)", "l");
    t_Legend->Draw();
    c_t_Result->Print(Outpdf);

    TCanvas* c_EPz_Result = new TCanvas("c_EPz_Result", "E-Pz MC vs Rec", 100, 0, 2560, 1920);
    c_EPz_Result->Divide(2,2);
    c_EPz_Result->cd(1);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_EPz_MC"));
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_EPz_Result->cd(2);
    tmpHist1D_2=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_EPz_Rec"));
    tmpHist1D_2->SetLineColor(2);
    tmpHist1D_2->SetTitle("");
    tmpHist1D_2->GetXaxis()->SetTitleOffset(1);
    tmpHist1D_2->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D_2->Draw("HISTER");
    c_EPz_Result->cd(3);
    tmpHist1D->Draw("HISTERR");
    tmpHist1D_2->Draw("SAMEHISTERR");
    c_EPz_Result->cd(4);
    TLegend *EPz_Legend = new TLegend(0.1, 0.1, 0.9, 0.9);
    EPz_Legend->SetTextSize(0.05);
    EPz_Legend->AddEntry(tmpHist1D, "MC Truth", "l");
    EPz_Legend->AddEntry(tmpHist1D_2, "Rec", "l");
    EPz_Legend->Draw();
    c_EPz_Result->Print(Outpdf);
    
    TCanvas* c_Q2MC_Result = new TCanvas("c_Q2MC_Result", "Q2 MC", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMPQ2_MC"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_Q2MC_Result->Print(Outpdf);
    TCanvas* c_Q2Rec_Result = new TCanvas("c_Q2Rec_Result", "Q2 Rec", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMPQ2_Rec"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_Q2Rec_Result->Print(Outpdf);
    TCanvas* c_xMC_Result = new TCanvas("c_xMC_Result", "x MC", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMPx_MC"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_xMC_Result->Print(Outpdf);
    TCanvas* c_xRec_Result = new TCanvas("c_xRec_Result", "x Rec", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMPx_Rec"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_xRec_Result->Print(Outpdf);
    TCanvas* c_yMC_Result = new TCanvas("c_yMC_Result", "y MC", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMPy_MC"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_yMC_Result->Print(Outpdf);
    TCanvas* c_yRec_Result = new TCanvas("c_yRec_Result", "y Rec", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMPy_Rec"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_yRec_Result->Print(Outpdf);
    TCanvas* c_dQ2_Result = new TCanvas("c_dQ2_Result", "dQ2", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_dQ2"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_dQ2_Result->Print(Outpdf);
    TCanvas* c_dx_Result = new TCanvas("c_dx_Result", "dx", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_dx"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_dx_Result->Print(Outpdf);
    TCanvas* c_dy_Result = new TCanvas("c_dy_Result", "dy", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_dy"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_dy_Result->Print(Outpdf);
    TCanvas* c_eScThetaMC_Result = new TCanvas("c_eScThetaMC_Result", "e' Theta MC ", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_eScTheta_MC"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_eScThetaMC_Result->Print(Outpdf);
    TCanvas* c_eScThetaRec_Result = new TCanvas("c_eScThetaRec_Result", "e' Theta Rec ", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_eScTheta_Rec"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_eScThetaRec_Result->Print(Outpdf);
    TCanvas* c_eScEMC_Result = new TCanvas("c_eScEMC_Result", "e' E MC ", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_eScE_MC"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_eScEMC_Result->Print(Outpdf);
    TCanvas* c_eScERec_Result = new TCanvas("c_eScERec_Result", "e' E Rec ", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_eScE_Rec"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_eScERec_Result->Print(Outpdf);
    TCanvas* c_PiEPzMC_Result = new TCanvas("c_PiEPzMC_Result", "pi E - Pz MC", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_piEPz_MC"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_PiEPzMC_Result->Print(Outpdf);
    TCanvas* c_PiEPzRec_Result = new TCanvas("c_PiEPzRec_Result", "pi E - Pz Rec", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_piEPz_Rec"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_PiEPzRec_Result->Print(Outpdf);
    TCanvas* c_nEPzMC_Result = new TCanvas("c_nEPzMC_Result", "n E - Pz MC", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_nEPz_MC"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_nEPzMC_Result->Print(Outpdf);
    TCanvas* c_PiPtMC_Result = new TCanvas("c_PiPtMC_Result", "pi Pt MC", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_piPt_MC"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_PiPtMC_Result->Print(Outpdf);
    TCanvas* c_PiPtRec_Result = new TCanvas("c_PiPtRec_Result", "pi Pt Rec", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_piPt_Rec"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_PiPtRec_Result->Print(Outpdf);
    TCanvas* c_nPtMC_Result = new TCanvas("c_nPtMC_Result", "n Pt MC", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_nPt_MC"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_nPtMC_Result->Print(Outpdf);
    TCanvas* c_nPtRec_Result = new TCanvas("c_nPtRec_Result", "n Pt Rec", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_nPt_Rec"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_nPtRec_Result->Print(Outpdf);
    TCanvas* c_tMC_Result = new TCanvas("c_tMC_Result", "t MC", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_tMC"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_tMC_Result->Print(Outpdf);
    TCanvas* c_tRec_Result = new TCanvas("c_tRec_Result", "teXBABE", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_tRec"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_tRec_Result->Print(Outpdf);
    TCanvas* c_EPzMC_Result = new TCanvas("c_EPzMC_Result", "E - Pz (all particles, MC)", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_EPz_MC"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_EPzMC_Result->Print(Outpdf);
    TCanvas* c_EPzRec_Result = new TCanvas("c_EPzRec_Result", "E - Pz (all particles, Rec)", 100, 0, 2560, 1920);
    tmpHist1D=((TH1D*)gDirectory->FindObject("h1_Result_DEMP_EPz_Rec"));
    tmpHist1D->GetXaxis()->SetTitleOffset(1);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.5);
    tmpHist1D->Draw("HISTER");
    c_EPzRec_Result->Print(Outpdf);
    TCanvas* c_Q2_Result_2D = new TCanvas("c_Q2_Result_2D", "Q2 2D", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMPQ2"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    c_Q2_Result_2D->Print(Outpdf);
    TCanvas* c_x_Result_2D = new TCanvas("c_x_Result_2D", "x 2D", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMPx"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    c_x_Result_2D->Print(Outpdf);
    TCanvas* c_y_Result_2D = new TCanvas("c_y_Result_2D", "y 2D", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMPy"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    c_y_Result_2D->Print(Outpdf);
    TCanvas* c_t_Result_2D = new TCanvas("c_t_Result_2D", "t 2D", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMPt"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    c_t_Result_2D->Print(Outpdf);
    TCanvas* c_eScTheta_Result_2D = new TCanvas("c_eScTheta_Result_2D", "eScTheta 2D", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMP_eScTheta"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    c_eScTheta_Result_2D->Print(Outpdf);
    TCanvas* c_eScE_Result_2D = new TCanvas("c_eScE_Result_2D", "eScE 2D", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMP_eScE"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    c_eScE_Result_2D->Print(Outpdf);
    TCanvas* c_piEPz_Result_2D = new TCanvas("c_piEPz_Result_2D", "piEPz 2D", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMP_piEPz"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    c_piEPz_Result_2D->Print(Outpdf);
    TCanvas* c_piPt_Result_2D = new TCanvas("c_piPt_Result_2D", "piPt 2D", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMP_piPt"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    c_piPt_Result_2D->Print(Outpdf);
    TCanvas* c_nEPz_Result_2D = new TCanvas("c_nEPz_Result_2D", "nEPz 2D", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMP_nEPz"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    c_nEPz_Result_2D->Print(Outpdf);
    TCanvas* c_nPt_Result_2D = new TCanvas("c_nPt_Result_2D", "nPt 2D", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMP_nPt"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    c_nPt_Result_2D->Print(Outpdf);
    TCanvas* c_EPz_Result_2D = new TCanvas("c_EPz_Result_2D", "EPz 2D", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMP_EPz"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    c_EPz_Result_2D->Print(Outpdf + ")");
    
    gDirectory->cd("../../"); 
  }  
}

void WritePlots(TString OutDir, TString InBeamE, TString InDate, TString InBeamConfig, TString Inpart, Bool_t EventDists, Bool_t Kin, Bool_t ZDC, Bool_t B0, Bool_t QA, Bool_t Results){

  TH1D* tmpHist1D;
  TH2D* tmpHist2D;
  if(EventDists == kTRUE){
    gDirectory->cd("EventDists/MC");
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_eSc_pTheta_MC"));
    TCanvas* c_eSc_pTheta_MC = new TCanvas("c_eSc_pTheta_MC", "e' p vs #theta", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_eSc_pTheta_MC->SetLogz();
    c_eSc_pTheta_MC->Print(Form("%s/%s_eSc_Truth_pTheta.png", OutDir.Data(), InBeamE.Data()));
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_Pi_pTheta_MC"));
    TCanvas* c_Pi_pTheta_MC = new TCanvas("c_Pi_pTheta_MC", "e' p vs #theta", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_Pi_pTheta_MC->SetLogz();
    c_Pi_pTheta_MC->Print(Form("%s/%s_Pi_Truth_pTheta.png", OutDir.Data(), InBeamE.Data()));
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_n_pTheta_MC"));
    TCanvas* c_n_pTheta_MC = new TCanvas("c_n_pTheta_MC", "e' p vs #theta", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_n_pTheta_MC->SetLogz();
    c_n_pTheta_MC->Print(Form("%s/%s_n_Truth_pTheta.png", OutDir.Data(), InBeamE.Data()));
    gDirectory->cd("../../");
    gDirectory->cd("EventDists/Reco");
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_eSc_pTheta_RecoAccept"));
    TCanvas* c_eSc_pTheta_RecoAccept = new TCanvas("c_eSc_pTheta_RecoAccept", "e' p vs #theta", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_eSc_pTheta_RecoAccept->SetLogz();
    c_eSc_pTheta_RecoAccept->Print(Form("%s/%s_eSc_Rec_pTheta.png", OutDir.Data(), InBeamE.Data()));
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_Pi_pTheta_RecoAccept"));
    TCanvas* c_Pi_pTheta_RecoAccept = new TCanvas("c_Pi_pTheta_RecoAccept", "e' p vs #theta", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_Pi_pTheta_RecoAccept->SetLogz();
    c_Pi_pTheta_RecoAccept->Print(Form("%s/%s_Pi_Rec_pTheta.png", OutDir.Data(), InBeamE.Data()));
    gDirectory->cd("../../");
  }
}

void WritePlotsKin(TString OutDir, TString InBeamE, TString InDate, TString InBeamConfig, TString Inpart, Bool_t EventDists, Bool_t Kin, Bool_t ZDC, Bool_t B0, Bool_t QA, Bool_t Results){
  TH1D* tmpHist1D;
  TH2D* tmpHist2D;
  if(Kin == kTRUE){
    gDirectory->cd("KinematicDists/Reco/");
    tmpHist1D = (TH1D*)gDirectory->FindObject("h1_MissMass_NoCuts");
    TCanvas* c_MissMass_NoCuts = new TCanvas("c_MissMass_NoCuts", "Missing Mass, No Cuts", 100, 0, 2560, 1920);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("hist");
    c_MissMass_NoCuts->SetLogz();
    c_MissMass_NoCuts->Print(Form("%s/%s_MissMass_NoCuts.png", OutDir.Data(), InBeamE.Data()));

    tmpHist1D = (TH1D*)gDirectory->FindObject("h1_MissMass_NoCuts");
    TCanvas* c_MissMass_NoCuts_v2 = new TCanvas("c_MissMass_NoCuts_v2", "Missing Mass, No Cuts", 100, 0, 2560, 1920);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("hist");
    gPad->Update();
    TLine *MissMassHigh = new TLine(0.75, 0, 0.75, gPad->GetUymax());
    MissMassHigh->SetLineColor(kRed);
    MissMassHigh->SetLineWidth(5);
    MissMassHigh->SetLineStyle(kDashed);
    MissMassHigh->Draw("same");
    c_MissMass_NoCuts_v2->Print(Form("%s/PaperPlots/%s_MissMass.png", OutDir.Data(), InBeamE.Data()));
    tmpHist1D = (TH1D*)gDirectory->FindObject("h1_MissMass2_NoCuts");
    TCanvas* c_MissMass2_NoCuts = new TCanvas("c_MissMass2_NoCuts", "(Missing Mass)^{2}, No Cuts", 100, 0, 2560, 1920);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("hist");
    gPad->Update();
    TLine *MissMass2Low = new TLine(-1, 0, -1, gPad->GetUymax());
    MissMass2Low->SetLineColor(kRed);
    MissMass2Low->SetLineWidth(5);
    MissMass2Low->SetLineStyle(kDashed);
    MissMass2Low->Draw("same");
    c_MissMass2_NoCuts->Print(Form("%s/PaperPlots/%s_MissMass2.png", OutDir.Data(), InBeamE.Data()));
    
    tmpHist1D = (TH1D*)gDirectory->FindObject("h1_MissMass");
    TCanvas* c_MissMass = new TCanvas("c_MissMass", "Missing Mass, No Cuts", 100, 0, 2560, 1920);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("hist");
    c_MissMass->SetLogz();
    c_MissMass->Print(Form("%s/%s_MissMass.png", OutDir.Data(), InBeamE.Data()));
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_DeltaRotThetaRotPhi_Reco_NoCuts"));
    TCanvas* c_DeltaRotThetaRotPhi_NoCuts = new TCanvas("c_DeltaRotThetaRotPhi_NoCuts", "#Delta#theta^{*} vs #Delta#phi^{*} No Cuts", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_DeltaRotThetaRotPhi_NoCuts->SetLogz();
    c_DeltaRotThetaRotPhi_NoCuts->Print(Form("%s/%s_DeltaRotThetaRotPhi_NoCuts.png", OutDir.Data(), InBeamE.Data()));

    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_DeltaRotThetaRotPhi_Reco_NoCuts"));
    TCanvas* c_DeltaRotThetaRotPhi_NoCuts_v2 = new TCanvas("c_DeltaRotThetaRotPhi_NoCuts_v2", "#Delta#theta^{*} vs #Delta#phi^{*} No Cuts", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    TLine *ThetaLow = new TLine(ZDCDeltaTheta_Min, -100, ZDCDeltaTheta_Min, 100);
    ThetaLow->SetLineColor(kRed);
    ThetaLow->SetLineWidth(5);
    ThetaLow->SetLineStyle(kDashed);
    ThetaLow->Draw("same");
    TLine *ThetaHigh = new TLine(ZDCDeltaTheta_Max, -100, ZDCDeltaTheta_Max, 100);
    ThetaHigh->SetLineColor(kRed);
    ThetaHigh->SetLineWidth(5);
    ThetaHigh->SetLineStyle(kDashed);
    ThetaHigh->Draw("same");
    TLine *PhiLow = new TLine(-1, ZDCDeltaPhi_Min, 1, ZDCDeltaPhi_Min);
    PhiLow->SetLineColor(kRed);
    PhiLow->SetLineWidth(5);
    PhiLow->SetLineStyle(kDashed);
    PhiLow->Draw("same");
    TLine *PhiHigh = new TLine(-1, ZDCDeltaPhi_Max, 1, ZDCDeltaPhi_Max);
    PhiHigh->SetLineColor(kRed);
    PhiHigh->SetLineWidth(5) ;
    PhiHigh->SetLineStyle(kDashed);
    PhiHigh->Draw("same");
    ePIC_Plot(0.18, 0.88, 0.65, 0.8, InBeamE);   
    c_DeltaRotThetaRotPhi_NoCuts_v2->Print(Form("%s/PaperPlots/%s_DeltaRotThetaRotPhi_NoCuts.png", OutDir.Data(), InBeamE.Data()));
    
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_DeltaRotThetaRotPhi_Reco"));
    TCanvas* c_DeltaRotThetaRotPhi = new TCanvas("c_DeltaRotThetaRotPhi", "#Delta#theta^{*} vs #Delta#phi^{*}", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_DeltaRotThetaRotPhi->SetLogz();
    c_DeltaRotThetaRotPhi->Print(Form("%s/%s_DeltaRotThetaRotPhi.png", OutDir.Data(), InBeamE.Data()));
    gDirectory->cd("../../");
    if(ZDC == kTRUE){
      gDirectory->cd("KinematicDists/Reco/ZDC");
      tmpHist1D = (TH1D*)gDirectory->FindObject("h1_MissMass_ZDCReco_NoCuts");
      TCanvas* c_MissMass_ZDCReco_NoCuts = new TCanvas("c_MissMass_ZDCReco_NoCuts", "Missing Mass, n in ZDC No Cuts", 100, 0, 2560, 1920);
      tmpHist1D->SetTitle("");
      tmpHist1D->Draw("hist");
      c_MissMass_ZDCReco_NoCuts->SetLogz();
      c_MissMass_ZDCReco_NoCuts->Print(Form("%s/%s_MissMass_ZDCReco_NoCuts.png", OutDir.Data(), InBeamE.Data()));
      tmpHist1D = (TH1D*)gDirectory->FindObject("h1_MissMass_ZDCReco");
      TCanvas* c_MissMass_ZDCReco = new TCanvas("c_MissMass_ZDCReco", "Missing Mass, n in ZDC No Cuts", 100, 0, 2560, 1920);
      tmpHist1D->SetTitle("");
      tmpHist1D->Draw("hist");
      c_MissMass_ZDCReco->SetLogz();
      c_MissMass_ZDCReco->Print(Form("%s/%s_MissMass_ZDCReco.png", OutDir.Data(), InBeamE.Data()));
      tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_DeltaRotThetaRotPhi_ZDCReco_NoCuts"));
      TCanvas* c_ZDC_DeltaRotThetaRotPhi_NoCuts = new TCanvas("c_ZDC_DeltaRotThetaRotPhi_NoCuts", "#Delta#theta^{*} vs #Delta#phi^{*}, n in ZDC No Cuts", 100, 0, 2560, 1920);
      tmpHist2D->SetTitle("");
      tmpHist2D->Draw("colz");
      c_ZDC_DeltaRotThetaRotPhi_NoCuts->SetLogz();
      c_ZDC_DeltaRotThetaRotPhi_NoCuts->Print(Form("%s/%s_ZDC_DeltaRotThetaRotPhi_NoCuts.png", OutDir.Data(), InBeamE.Data()));
      tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_DeltaRotThetaRotPhi_ZDCReco"));
      TCanvas* c_ZDC_DeltaRotThetaRotPhi = new TCanvas("c_ZDC_DeltaRotThetaRotPhi", "#Delta#theta^{*} vs #Delta#phi^{*}, n in ZDC", 100, 0, 2560, 1920);
      tmpHist2D->SetTitle("");
      tmpHist2D->Draw("colz");
      c_ZDC_DeltaRotThetaRotPhi->SetLogz();
      c_ZDC_DeltaRotThetaRotPhi->Print(Form("%s/%s_ZDC_DeltaRotThetaRotPhi.png", OutDir.Data(), InBeamE.Data()));
      tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_DeltaThetaPhi_ZDCReco_NoCuts"));
      TCanvas* c_ZDC_DeltaThetaDeltaPhi = new TCanvas("c_ZDC_DeltaThetaDeltaPhi", "ZDC #Delta#theta vs #Delta#phi", 100, 0, 2560, 1920);
      tmpHist2D->SetTitle("");
      tmpHist2D->Draw("colz");
      c_ZDC_DeltaThetaDeltaPhi->SetLogz();
      c_ZDC_DeltaThetaDeltaPhi->Print(Form("%s/%s_ZDC_DeltaThetaDeltaPhi.png", OutDir.Data(), InBeamE.Data()));
      gDirectory->cd("../../../");
    }
    if(B0 == kTRUE){
      gDirectory->cd("KinematicDists/Reco/B0");
      tmpHist1D = (TH1D*)gDirectory->FindObject("h1_MissMass_B0Reco_NoCuts");
      TCanvas* c_MissMass_B0Reco_NoCuts = new TCanvas("c_MissMass_B0Reco_NoCuts", "Missing Mass, n in B0 No Cuts", 100, 0, 2560, 1920);
      tmpHist1D->SetTitle("");
      tmpHist1D->Draw("hist");
      c_MissMass_B0Reco_NoCuts->SetLogz();
      c_MissMass_B0Reco_NoCuts->Print(Form("%s/%s_MissMass_B0Reco_NoCuts.png", OutDir.Data(), InBeamE.Data()));
      tmpHist1D = (TH1D*)gDirectory->FindObject("h1_MissMass_B0Reco");
      TCanvas* c_MissMass_B0Reco = new TCanvas("c_MissMass_B0Reco", "Missing Mass, n in B0 No Cuts", 100, 0, 2560, 1920);
      tmpHist1D->SetTitle("");
      tmpHist1D->Draw("hist");
      c_MissMass_B0Reco->SetLogz();
      c_MissMass_B0Reco->Print(Form("%s/%s_MissMass_B0Reco.png", OutDir.Data(), InBeamE.Data()));
      tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_DeltaRotThetaRotPhi_B0Reco_NoCuts"));
      TCanvas* c_B0_DeltaRotThetaRotPhi_NoCuts = new TCanvas("c_B0_DeltaRotThetaRotPhi_NoCuts", "#Delta#theta^{*} vs #Delta#phi^{*}, n in B0 No Cuts", 100, 0, 2560, 1920);
      tmpHist2D->SetTitle("");
      tmpHist2D->Draw("colz");
      c_B0_DeltaRotThetaRotPhi_NoCuts->SetLogz();
      c_B0_DeltaRotThetaRotPhi_NoCuts->Print(Form("%s/%s_B0_DeltaRotThetaRotPhi_NoCuts.png", OutDir.Data(), InBeamE.Data()));
      tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_DeltaRotThetaRotPhi_B0Reco"));
      TCanvas* c_B0_DeltaRotThetaRotPhi = new TCanvas("c_B0_DeltaRotThetaRotPhi", "#Delta#theta^{*} vs #Delta#phi^{*}, n in B0", 100, 0, 2560, 1920);
      tmpHist2D->SetTitle("");
      tmpHist2D->Draw("colz");
      c_B0_DeltaRotThetaRotPhi->SetLogz();
      c_B0_DeltaRotThetaRotPhi->Print(Form("%s/%s_B0_DeltaRotThetaRotPhi.png", OutDir.Data(), InBeamE.Data()));
      tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_DeltaThetaPhi_B0Reco_NoCuts"));
      TCanvas* c_B0_DeltaThetaDeltaPhi = new TCanvas("c_B0_DeltaThetaDeltaPhi", "B0 #Delta#theta vs #Delta#phi", 100, 0, 2560, 1920);
      tmpHist2D->SetTitle("");
      tmpHist2D->Draw("colz");
      c_B0_DeltaThetaDeltaPhi->SetLogz();
      c_B0_DeltaThetaDeltaPhi->Print(Form("%s/%s_B0_DeltaThetaDeltaPhi.png", OutDir.Data(), InBeamE.Data()));
      gDirectory->cd("../../../");
    }
  }
  if(ZDC == kTRUE){
    gDirectory->cd("ZDCDists/Reco");
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_n_XY_Reco"));
    TCanvas* c_ZDC_XY = new TCanvas("c_ZDC_XY", "ZDC X vs Y Accepted", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_ZDC_XY->SetLogz();
    c_ZDC_XY->Print(Form("%s/%s_ZDC_XY.png", OutDir.Data(), InBeamE.Data()));
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_n_pTheta_RecoAcceptZDC"));
    TCanvas* c_n_pTheta_RecoAcceptZDC = new TCanvas("c_n_pTheta_RecoAcceptZDC", "n p vs #theta", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_n_pTheta_RecoAcceptZDC->SetLogz();
    c_n_pTheta_RecoAcceptZDC->Print(Form("%s/%s_n_Rec_pThetaZDC.png", OutDir.Data(), InBeamE.Data()));
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_n_XY_10m_RecoDEMPAcceptZDC"));
    TCanvas* c_n_XY_10m_RecoDEMPAcceptZDC = new TCanvas("c_n_XY_10m_RecoDEMPAcceptZDC", "n XY at 10m, ZDC n only", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_n_XY_10m_RecoDEMPAcceptZDC->SetLogz();
    c_n_XY_10m_RecoDEMPAcceptZDC->Print(Form("%s/%s_n_Rec_XY_10m_ZDC.png", OutDir.Data(), InBeamE.Data()));
    gDirectory->cd("../../");
  }
  if(B0 == kTRUE){
    gDirectory->cd("B0Dists/Reco");
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_B0_XY_AcceptWeighted"));
    TCanvas* c_B0_XY = new TCanvas("c_B0_XY", "B0 X vs Y Accepted", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_B0_XY->SetLogz();
    c_B0_XY->Print(Form("%s/%s_B0_XY.png", OutDir.Data(), InBeamE.Data()));
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_n_pTheta_RecoAcceptB0"));
    TCanvas* c_n_pTheta_RecoAcceptB0 = new TCanvas("c_n_pTheta_RecoAcceptB0", "n p vs #theta", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_n_pTheta_RecoAcceptB0->SetLogz();
    c_n_pTheta_RecoAcceptB0->Print(Form("%s/%s_n_Rec_pThetaB0.png", OutDir.Data(), InBeamE.Data()));
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_n_XY_10m_RecoDEMPAcceptB0"));
    TCanvas* c_n_XY_10m_RecoDEMPAcceptB0 = new TCanvas("c_n_XY_10m_RecoDEMPAcceptB0", "n XY at 10m, B0 n only", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->Draw("colz");
    c_n_XY_10m_RecoDEMPAcceptB0->SetLogz();
    c_n_XY_10m_RecoDEMPAcceptB0->Print(Form("%s/%s_n_Rec_XY_10m_B0.png", OutDir.Data(), InBeamE.Data()));
    gDirectory->cd("../../");
  }
}

void WritePlotsQA(TString OutDir, TString InBeamE, TString InDate, TString InBeamConfig, TString Inpart, Bool_t EventDists, Bool_t Kin, Bool_t ZDC, Bool_t B0, Bool_t QA, Bool_t Results){
       
  TH1D* tmpHist1D;
  TH2D* tmpHist2D;
  if(QA == kTRUE){
    gDirectory->cd("QADists/Efficiencies");
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_Q2t_effDEMPCut"));
    TCanvas* c_Q2t_effDEMPCut = new TCanvas("c_Q2t_effDEMPCut", "Q^{2} vs -t Efficiency", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->GetZaxis()->SetRangeUser(0.0, 1.0);
    tmpHist2D->Draw("colz");
    c_Q2t_effDEMPCut->Print(Form("%s/%s_Q2t_DetEff.png", OutDir.Data(), InBeamE.Data()));
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_Q2t_effDEMPCut_ZDC"));
    TCanvas* c_Q2t_effDEMPCut_ZDC = new TCanvas("c_Q2t_effDEMPCut_ZDC", "Q^{2} vs -t Efficiency", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->GetZaxis()->SetRangeUser(0.0, 1.0);
    tmpHist2D->Draw("colz");
    c_Q2t_effDEMPCut_ZDC->Print(Form("%s/%s_Q2t_DetEff_ZDC.png", OutDir.Data(), InBeamE.Data()));
    tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_Q2t_effDEMPCut_B0"));
    TCanvas* c_Q2t_effDEMPCut_B0 = new TCanvas("c_Q2t_effDEMPCut_B0", "Q^{2} vs -t Efficiency", 100, 0, 2560, 1920);
    tmpHist2D->SetTitle("");
    tmpHist2D->GetZaxis()->SetRangeUser(0.0, 1.0);
    tmpHist2D->Draw("colz");
    c_Q2t_effDEMPCut_B0->Print(Form("%s/%s_Q2t_DetEff_B0.png", OutDir.Data(), InBeamE.Data()));
    gDirectory->cd("../../");

    gDirectory->cd("QADists/Kin");
    TLegend* Leg_tComp = new TLegend (0.6, 0.72, 0.85, 0.9);
    Leg_tComp->SetBorderSize(0);Leg_tComp->SetFillStyle(0); 
    TCanvas* c_tComp = new TCanvas("c_tComp", "-t Reconsturction method comparison", 100, 0, 2560, 1920);
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_teXBABE_Res_QA_ZDC"));
    tmpHist1D->SetFillColorAlpha(kP6Violet, 0.8);
    tmpHist1D->GetXaxis()->SetTitle("(t - t_{MC})/t_{MC} (%)");
    tmpHist1D->GetXaxis()->SetTitleOffset(1.3);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.4);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("HIST");
    Leg_tComp->AddEntry(tmpHist1D, "t_{eXBABE}");
    /* tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_teXPT_Res_QA_ZDC")); */
    /* tmpHist1D->SetFillColorAlpha(kP6Red, 0.3); */
    /* tmpHist1D->SetTitle(""); */
    /* tmpHist1D->Draw("SAMEHIST"); */
    /* Leg_tComp->AddEntry(tmpHist1D, "t_{eXPT}"); */
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_teX_Res_QA_ZDC"));
    tmpHist1D->SetFillColorAlpha(kP6Yellow, 0.8);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("SAMEHIST");
    Leg_tComp->AddEntry(tmpHist1D, "t_{eX}");
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_tBABE_Res_QA_ZDC"));
    tmpHist1D->SetFillColorAlpha(kP6Red, 0.8);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("SAMEHIST");
    Leg_tComp->AddEntry(tmpHist1D, "t_{BABE}");
    Leg_tComp->Draw("SAME");
    ePIC_Plot(0.18, 0.88, 0.85, 0.8, InBeamE);
    c_tComp->Print(Form("%s/PaperPlots/%s_tComp.png", OutDir.Data(), InBeamE.Data()));
    TLegend* Leg_tComp_Abs = new TLegend (0.6, 0.72, 0.85, 0.9);
    Leg_tComp_Abs->SetBorderSize(0);Leg_tComp_Abs->SetFillStyle(0); 
    TCanvas* c_tComp_Abs = new TCanvas("c_tComp_Abs", "-t Reconsturction method comparison", 100, 0, 2560, 1920);
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_teXBABE_Res_Abs_QA_ZDC"));
    tmpHist1D->SetFillColorAlpha(kP6Violet, 0.8);
    tmpHist1D->GetXaxis()->SetTitle("(t - t_{MC}) (GeV^{2})");
    tmpHist1D->GetXaxis()->SetTitleOffset(1.3);
    tmpHist1D->GetYaxis()->SetTitleOffset(1.4);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("HIST");
    Leg_tComp_Abs->AddEntry(tmpHist1D, "t_{eXBABE}");
    /* tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_teXPT_Res_Abs_QA_ZDC"));
    tmpHist1D->SetFillColorAlpha(kP6Red, 0.3);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("SAMEHIST");
    Leg_tComp_Abs->AddEntry(tmpHist1D, "t_{eXPT}"); */
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_teX_Res_Abs_QA_ZDC"));
    tmpHist1D->SetFillColorAlpha(kP6Yellow, 0.8);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("SAMEHIST");
    Leg_tComp_Abs->AddEntry(tmpHist1D, "t_{eX}");
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_tBABE_Res_Abs_QA_ZDC"));
    tmpHist1D->SetFillColorAlpha(kP6Red, 0.8);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("SAMEHIST");
    Leg_tComp_Abs->AddEntry(tmpHist1D, "t_{BABE}");
    Leg_tComp_Abs->Draw("SAME");
    ePIC_Plot(0.18, 0.88, 0.85, 0.8, InBeamE);
    c_tComp_Abs->Print(Form("%s/PaperPlots/%s_tComp_Abs.png", OutDir.Data(), InBeamE.Data()));
    gDirectory->cd("../../");

    gDirectory->cd("QADists/Q2_Alt");
    TLegend* Leg_Q2Comp = new TLegend (0.525,0.7,0.725,0.9); 
    Leg_Q2Comp->SetBorderSize(0);Leg_Q2Comp->SetFillStyle(0); 
    TCanvas* c_Q2Comp = new TCanvas("c_Q2Comp", "Q^{2} Reconsturction method comparison", 100, 0, 2560, 1920);
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_QA_Q2DA_Res"));
    tmpHist1D->SetFillColorAlpha(kP6Violet, 0.8);
    tmpHist1D->GetXaxis()->SetTitle("(Q^{2} - Q^{2}_{MC})/Q^{2}_{MC} (%)");
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("HIST");
    Leg_Q2Comp->AddEntry(tmpHist1D, "DA Method");
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_QA_Q2JB_Res"));
    tmpHist1D->SetFillColorAlpha(kP6Red, 0.8);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("SAMEHIST");
    Leg_Q2Comp->AddEntry(tmpHist1D, "JB Method");
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_QA_Q2Rec_Res"));
    tmpHist1D->SetFillColorAlpha(kP6Yellow, 0.8);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("SAMEHIST");
    Leg_Q2Comp->AddEntry(tmpHist1D, "Electron Method");
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_QA_Q2Sig_Res"));
    tmpHist1D->SetFillColorAlpha(kP6Blue, 0.8);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("SAMEHIST");
    Leg_Q2Comp->AddEntry(tmpHist1D, "Sigma Method");
    Leg_Q2Comp->Draw("SAME");
    ePIC_Plot(0.18, 0.88, 0.85, 0.8, InBeamE);
    c_Q2Comp->Print(Form("%s/PaperPlots/%s_Q2Comp.png", OutDir.Data(), InBeamE.Data()));
    TLegend* Leg_Q2Comp_Abs = new TLegend (0.525,0.7,0.725,0.9); 
    Leg_Q2Comp_Abs->SetBorderSize(0);Leg_Q2Comp_Abs->SetFillStyle(0); 
    TCanvas* c_Q2Comp_Abs = new TCanvas("c_Q2Comp_Abs", "Q^{2} Reconsturction method comparison", 100, 0, 2560, 1920);
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_QA_Q2DA_Res_Abs"));
    tmpHist1D->SetFillColorAlpha(kP6Violet, 0.8);
    tmpHist1D->GetXaxis()->SetTitle("(Q^{2} - Q^{2}_{MC})/Q^{2}_{MC} (%)");
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("HIST");
    Leg_Q2Comp_Abs->AddEntry(tmpHist1D, "DA Method");
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_QA_Q2JB_Res_Abs"));
    tmpHist1D->SetFillColorAlpha(kP6Red, 0.8);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("SAMEHIST");
    Leg_Q2Comp_Abs->AddEntry(tmpHist1D, "JB Method");
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_QA_Q2Rec_Res_Abs"));
    tmpHist1D->SetFillColorAlpha(kP6Yellow, 0.8);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("SAMEHIST");
    Leg_Q2Comp_Abs->AddEntry(tmpHist1D, "Electron Method");
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_QA_Q2Sig_Res_Abs"));
    tmpHist1D->SetFillColorAlpha(kP6Blue, 0.8);
    tmpHist1D->SetTitle("");
    tmpHist1D->Draw("SAMEHIST");
    Leg_Q2Comp_Abs->AddEntry(tmpHist1D, "Sigma Method");
    Leg_Q2Comp_Abs->Draw("SAME");
    ePIC_Plot(0.18, 0.88, 0.85, 0.8, InBeamE);
    c_Q2Comp_Abs->Print(Form("%s/PaperPlots/%s_Q2Comp_Abs.png", OutDir.Data(), InBeamE.Data()));    
    gDirectory->cd("../../");
    
    if(ZDC == kTRUE){
      gDirectory->cd("QADists/tComp");
      tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_teXBABEComp_ZDC"));
      TCanvas* c_teXBABEComp_ZDC = new TCanvas("c_teXBABEComp_ZDC", "t_{eXBABE} vs t_{MC}", 100, 0, 2560, 1920);
      tmpHist2D->SetTitle("");
      tmpHist2D->Draw("colz");
      c_teXBABEComp_ZDC->SetLogz();
      c_teXBABEComp_ZDC->Print(Form("%s/%s_tComp_ZDC.png", OutDir.Data(), InBeamE.Data()));      
      tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_teXBABECompAlt_ZDC"));
      TCanvas* c_teXBABECompAlt_ZDC = new TCanvas("c_teXBABECompAlt_ZDC", "t_{eXBABE} vs t_{MC}", 100, 0, 2560, 1920);
      tmpHist2D->SetTitle("");
      tmpHist2D->Draw("colz");
      c_teXBABECompAlt_ZDC->SetLogz();
      c_teXBABECompAlt_ZDC->Print(Form("%s/%s_tCompAlt_ZDC.png", OutDir.Data(), InBeamE.Data()));      
      gDirectory->cd("../../");
    }
    if(B0 == kTRUE){
      gDirectory->cd("QADists/tComp");
      tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_teXBABEComp_B0"));
      TCanvas* c_teXBABEComp_B0 = new TCanvas("c_teXBABEComp_B0", "t_{eXBABE} vs t_{MC}", 100, 0, 2560, 1920);
      tmpHist2D->SetTitle("");
      tmpHist2D->Draw("colz");
      c_teXBABEComp_B0->SetLogz();
      c_teXBABEComp_B0->Print(Form("%s/%s_tComp_B0.png", OutDir.Data(), InBeamE.Data()));
      tmpHist2D = ((TH2D*)gDirectory->FindObject("h2_teXBABECompAlt_B0"));
      TCanvas* c_teXBABECompAlt_B0 = new TCanvas("c_teXBABECompAlt_B0", "t_{eXBABE} vs t_{MC}", 100, 0, 2560, 1920);
      tmpHist2D->SetTitle("");
      tmpHist2D->Draw("colz");
      c_teXBABECompAlt_B0->SetLogz();
      c_teXBABECompAlt_B0->Print(Form("%s/%s_tCompAlt_B0.png", OutDir.Data(), InBeamE.Data()));
      gDirectory->cd("../../");
    }
  }
  if(Results == kTRUE){
    gDirectory->cd("ResultsDists/");
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_tResult_ZDC_1"));
    TCanvas* c_tResult_ZDC_1 = new TCanvas("c_tResult_ZDC_1", "-t, 5 < Q^{2} < 6", 100, 0, 2560, 1920);
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetRangeUser(0, 0.5);
    tmpHist1D->SetLineWidth(3);
    tmpHist1D->Draw("histerr");
    c_tResult_ZDC_1->Print(Form("%s/%s_tResult_Q2_5_6.png", OutDir.Data(), InBeamE.Data()));
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_tResult_ZDC_13"));
    TCanvas* c_tResult_ZDC_13 = new TCanvas("c_tResult_ZDC_13", "-t, 17 < Q^{2} < 18", 100, 0, 2560, 1920);
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetRangeUser(0, 0.5);
    tmpHist1D->SetLineWidth(3);
    tmpHist1D->Draw("histerr");
    c_tResult_ZDC_13->Print(Form("%s/%s_tResult_Q2_17_18.png", OutDir.Data(), InBeamE.Data()));
    tmpHist1D = ((TH1D*)gDirectory->FindObject("h1_tResult_ZDC_28"));
    TCanvas* c_tResult_ZDC_28 = new TCanvas("c_tResult_ZDC_28", "-t, 32 < Q^{2} < 33", 100, 0, 2560, 1920);
    tmpHist1D->SetTitle("");
    tmpHist1D->GetXaxis()->SetRangeUser(0, 0.5);
    tmpHist1D->SetLineWidth(3);
    tmpHist1D->Draw("histerr");
    c_tResult_ZDC_28->Print(Form("%s/%s_tResult_Q2_32_33.png", OutDir.Data(), InBeamE.Data()));
    TCanvas* c_WResults[3];
    TString StampPDF = Form("%s/PaperPlots/%s_WResult_StampCollection.pdf", OutDir.Data(), InBeamE.Data());
    for(int i =0; i<3; i++){
      c_WResults[i] = new TCanvas(Form("c_WResults_%i", i+1), Form("W Results Page %i", 1+1), 100, 0, 2560, 1920);
      c_WResults[i]->Divide(5,2);
      for (int j = 0; j < 10; j++){
	c_WResults[i]->cd(j+1);
	tmpHist1D = ((TH1D*)gDirectory->FindObject(Form("h1_WResult_ZDC_%i", (i*10)+(j+1))));
	tmpHist1D->SetTitle("");
	tmpHist1D->SetLineWidth(3);
	tmpHist1D->Draw("histerr");
      }
      if(i == 0){
	c_WResults[i]->Print(StampPDF +"(");
      }
      else if(i == 2){
	c_WResults[i]->Print(StampPDF + ")");
      }
      else{
	c_WResults[i]->Print(StampPDF);
      }
    }
    gDirectory->cd("../");

    gDirectory->cd("ResultsDists/Exclusive_Paper_Plots");
    // Add Q2 and -t plots, limit to 0 to 40 and 0 to 0.6. Add ePIC style elements, log Z scales
    TCanvas* c_Q2_Result_2D_v2 = new TCanvas("c_Q2_Result_2D_v2", "Q2 2D v2", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMPQ2"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetXaxis()->SetRangeUser(0, 40);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetYaxis()->SetRangeUser(0, 40);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->Draw("colz");
    ePIC_Plot(0.18, 0.88, 0.65, 0.8, InBeamE);
    c_Q2_Result_2D_v2->Print(Form("%s/PaperPlots/%s_Q2_Comp_2D.png", OutDir.Data(), InBeamE.Data()));
    TCanvas* c_t_Result_2D_v2 = new TCanvas("c_t_Result_2D_v2", "t 2D v2", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMPt"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetXaxis()->SetRangeUser(0, 0.6);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetYaxis()->SetRangeUser(0, 0.6);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->GetZaxis()->SetTitleOffset(1.4);
    tmpHist2D->Draw("colz");
    ePIC_Plot(0.18, 0.88, 0.65, 0.8, InBeamE);
    c_t_Result_2D_v2->Print(Form("%s/PaperPlots/%s_t_Comp_2D.png", OutDir.Data(), InBeamE.Data()));
    TCanvas* c_t_Result_2D_Q2_1 = new TCanvas("c_t_Result_2D_Q2_1", "t 2D Q2 1", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMPt_Q2_1"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetXaxis()->SetRangeUser(0, 0.6);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetYaxis()->SetRangeUser(0, 0.6);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->GetZaxis()->SetTitleOffset(1.4);
    tmpHist2D->Draw("colz");
    ePIC_Plot(0.18, 0.88, 0.65, 0.8, InBeamE);
    c_t_Result_2D_Q2_1->Print(Form("%s/PaperPlots/%s_t_Comp_2D_Q2_5_10.png", OutDir.Data(), InBeamE.Data()));
    TCanvas* c_t_Result_2D_Q2_2 = new TCanvas("c_t_Result_2D_Q2_2", "t 2D Q2 2", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMPt_Q2_2"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetXaxis()->SetRangeUser(0, 0.6);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetYaxis()->SetRangeUser(0, 0.6);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->GetZaxis()->SetTitleOffset(1.4);
    tmpHist2D->Draw("colz");
    ePIC_Plot(0.18, 0.88, 0.65, 0.8, InBeamE);
    c_t_Result_2D_Q2_2->Print(Form("%s/PaperPlots/%s_t_Comp_2D_Q2_10_20.png", OutDir.Data(), InBeamE.Data()));
    TCanvas* c_t_Result_2D_Q2_3 = new TCanvas("c_t_Result_2D_Q2_3", "t 2D Q2 3", 100, 0, 2560, 1920);
    tmpHist2D=((TH2D*)gDirectory->FindObject("h2_Result_DEMPt_Q2_3"));
    tmpHist2D->GetXaxis()->SetTitleOffset(1);
    tmpHist2D->GetXaxis()->SetRangeUser(0, 0.6);
    tmpHist2D->GetYaxis()->SetTitleOffset(1.1);
    tmpHist2D->GetYaxis()->SetRangeUser(0, 0.6);
    tmpHist2D->GetZaxis()->SetLabelSize(0.04);
    tmpHist2D->GetZaxis()->SetTitleOffset(1.4);
    tmpHist2D->Draw("colz");
    ePIC_Plot(0.18, 0.88, 0.65, 0.8, InBeamE);
    c_t_Result_2D_Q2_3->Print(Form("%s/PaperPlots/%s_t_Comp_2D_Q2_20_35.png", OutDir.Data(), InBeamE.Data()));
    gDirectory->cd("../../");
  }
}

void WriteCSV(TString OutDir, TString InBeamE, TString InDate, TString InBeamConfig, TString Inpart, Bool_t ZDC, Bool_t B0){
  ofstream csvfile;
  gDirectory->cd("ResultsDists");
  csvfile.open(Form("%s/%s_%s_%s_%s_Rates.csv", OutDir.Data(), Inpart.Data(), InBeamE.Data(), InBeamConfig.Data(), InDate.Data()), std::ios::trunc);
  TString CSV_Header = "Nominal mean Q^2,Mean Q^2,Mean Q^2 error,Mean W,Mean W error,-t (bin centre),Rate (Hz), Rate (Hz) error";
  csvfile << CSV_Header << "\n\n";
  // If B0 enabled, use ZDC (if they exist), if not, use default
  for (int i = 0; i < 30; i++) {
    for (int j = 0; j < 20; j++) {
      if (j == 0) {
	// If B0 enabled, use ZDC (if they exist), if not, use default
	if( B0 == kTRUE && ZDC == kTRUE){
	  csvfile << (Q2Vals[i] + Q2Vals[i+1])/2 << ",";
	  csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_Q2Result_ZDC_%i", i+1)))->GetMean() << ",";
	  csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_Q2Result_ZDC_%i", i+1)))->GetMeanError() << ",";
	  csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_WResult_ZDC_%i", i+1)))->GetMean() << ",";
	  csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_WResult_ZDC_%i", i+1)))->GetMeanError() << ",";
	}
	else{
	  csvfile << (Q2Vals[i] + Q2Vals[i+1])/2 << ",";
	  csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_Q2Result_%i", i+1)))->GetMean() << ",";
	  csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_Q2Result_%i", i+1)))->GetMeanError() << ",";
	  csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_WResult_%i", i+1)))->GetMean() << ",";
	  csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_WResult_%i", i+1)))->GetMeanError() << ",";
	}
      }
      else {
	csvfile << ",,,,,";
      }
      if( B0 == kTRUE && ZDC == kTRUE){
	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->GetXaxis()->GetBinCenter(((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->FindFixBin(0.01 + j * 0.02)) << ",";
	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->GetBinContent(((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->FindFixBin(0.01 + j * 0.02)) << ",";
	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->GetBinError(((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->FindFixBin(0.01 + j * 0.02)) << "\n";
      }
      else{
	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->GetXaxis()->GetBinCenter(((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->FindFixBin(0.01 + j * 0.02)) << ",";
	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->GetBinContent(((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->FindFixBin(0.01 + j * 0.02)) << ",";
	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->GetBinError(((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->FindFixBin(0.01 + j * 0.02)) << "\n";
      }
      /* if( B0 == kTRUE && ZDC == kTRUE){ */
      /* 	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->GetXaxis()->GetBinCenter(((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->FindFixBin(0.0 + j * 0.04)) << ","; */
      /* 	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->GetBinContent(((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->FindFixBin(0.02 + j * 0.04)) << ","; */
      /* 	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->GetBinError(((TH1D*)gDirectory->FindObject(Form("h1_tResult_ZDC_%i", i+1)))->FindFixBin(0.02 + j * 0.04)) << "\n"; */
      /* } */
      /* else{ */
      /* 	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->GetXaxis()->GetBinCenter(((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->FindFixBin(0.02 + j * 0.04)) << ","; */
      /* 	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->GetBinContent(((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->FindFixBin(0.02 + j * 0.04)) << ","; */
      /* 	csvfile << ((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->GetBinError(((TH1D*)gDirectory->FindObject(Form("h1_tResult_%i", i+1)))->FindFixBin(0.02 + j * 0.04)) << "\n"; */
      /* } */
    } // End loop over bins (j)
    csvfile << "\n";
  } // End loop over Q2 ranges/plots (i)
  csvfile.close();
  gDirectory->cd("../");
}
