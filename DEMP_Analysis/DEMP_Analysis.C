// Stephen JD Kay - University of York
// Stephen.Kay@york.ac.uk
// 28/03/25
// New DEMP Analysis script based upon Love's earlier work, segmented code out into functions and tried to make it more generic

#include "TString.h"
#include "DEMP_Analysis.h"

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
  TTreeReaderArray<int>    partGenStat(tree_reader, "MCParticles.generatorStatus");
  TTreeReaderArray<float>  partMomX(tree_reader, "MCParticles.momentum.x");
  TTreeReaderArray<float>  partMomY(tree_reader, "MCParticles.momentum.y");
  TTreeReaderArray<float>  partMomZ(tree_reader, "MCParticles.momentum.z");
  TTreeReaderArray<int>    partPdg(tree_reader, "MCParticles.PDG");
  TTreeReaderArray<double> partMass(tree_reader,"MCParticles.mass");
  // Get Reconstructed Track Information
  TTreeReaderArray<float> trackMomX(tree_reader,"ReconstructedChargedParticles.momentum.x"); 
  TTreeReaderArray<float> trackMomY(tree_reader,"ReconstructedChargedParticles.momentum.y");
  TTreeReaderArray<float> trackMomZ(tree_reader,"ReconstructedChargedParticles.momentum.z");
  TTreeReaderArray<float> trackEng(tree_reader,"ReconstructedChargedParticles.energy");
  TTreeReaderArray<int>   trackPdg(tree_reader,"ReconstructedChargedParticles.PDG");
  TTreeReaderArray<float> trackMass(tree_reader,"ReconstructedChargedParticles.mass");
  TTreeReaderArray<float> trackCharge(tree_reader,"ReconstructedChargedParticles.charge");
  // ZDC Neutrons
  TTreeReaderArray<float> neutEng(tree_reader, "ReconstructedFarForwardZDCNeutrals.energy");
  TTreeReaderArray<float> neutMomX(tree_reader, "ReconstructedFarForwardZDCNeutrals.momentum.x");
  TTreeReaderArray<float> neutMomY(tree_reader, "ReconstructedFarForwardZDCNeutrals.momentum.y");
  TTreeReaderArray<float> neutMomZ(tree_reader, "ReconstructedFarForwardZDCNeutrals.momentum.z");
  TTreeReaderArray<unsigned int> neutClus(tree_reader, "ReconstructedFarForwardZDCNeutrals.clusters_end");
  // ZDC SiPM-on-tile HCal
  TTreeReaderArray<float> neutPosX_hcal(tree_reader, "HcalFarForwardZDCClusters.position.x");
  TTreeReaderArray<float> neutPosY_hcal(tree_reader, "HcalFarForwardZDCClusters.position.y");
  TTreeReaderArray<float> neutPosZ_hcal(tree_reader, "HcalFarForwardZDCClusters.position.z");
  TTreeReaderArray<float> neutEng_hcal(tree_reader, "HcalFarForwardZDCClusters.energy");
  // Get Before Afterburned information
  TTreeReaderArray<int>    NoAbpartGenStat(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.generatorStatus");
  TTreeReaderArray<float>  NoAbpartMomX(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.x");
  TTreeReaderArray<float>  NoAbpartMomY(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.y");
  TTreeReaderArray<float>  NoAbpartMomZ(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.z");
  TTreeReaderArray<int>    NoAbpartPdg(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.PDG");
  TTreeReaderArray<double> NoAbpartMass(tree_reader,"MCParticlesHeadOnFrameNoBeamFX.mass");
  // B0ECalClusters
  TTreeReaderArray<float> neutPosX_b0(tree_reader, "B0ECalClusters.position.x");
  TTreeReaderArray<float> neutPosY_b0(tree_reader, "B0ECalClusters.position.y");
  TTreeReaderArray<float> neutPosZ_b0(tree_reader, "B0ECalClusters.position.z");
  TTreeReaderArray<float> neutEng_b0(tree_reader, "B0ECalClusters.energy");

  TFile *ofile = TFile::Open(Form("%s_%s_OutputHists.root", part.Data(), BeamE.Data()),"RECREATE");

  Double_t ElecE = ((TObjString *)((BeamE.Tokenize("on"))->At(0)))->String().Atof();
  Double_t HadE = ((TObjString *)((BeamE.Tokenize("on"))->At(1)))->String().Atof();
  
  Bool_t EventDistPlots = kTRUE;
  Bool_t KinPlots = kTRUE;
  Bool_t ZDCPlots = kTRUE;
  Bool_t B0Plots = kTRUE;
  Bool_t TrackingPlots = kTRUE;
  Bool_t QAPlots = kTRUE;
  Bool_t ResultsPlots = kTRUE;
  
  //Define histograms using BeamE value and series of true false flags
  DefHists(BeamE, EventDistPlots, KinPlots, ZDCPlots, B0Plots, TrackingPlots, QAPlots, ResultsPlots);
 
  while(tree_reader.Next()) { // Loop over all events

    for(unsigned int i=0; i<NoAbpartGenStat.GetSize(); i++) { // Loop over thrown nbf particles
      NoAbPartEng = sqrt(pow(NoAbpartMomX[i],2) + pow(NoAbpartMomY[i],2) + pow(NoAbpartMomZ[i],2) + pow(NoAbpartMass[i],2)); // Energy of all Truth NoAb  Monte Carlo particles
      if(NoAbpartGenStat[i] == 1 && NoAbpartPdg[i] == 11) { // Select stable thrown NoAb particles and look at electro
	Vec_eSc_MC_NoAb.SetPxPyPzE(NoAbpartMomX[i], NoAbpartMomY[i], NoAbpartMomZ[i], NoAbPartEng);
	FillHist2D("h2_eSc_pTheta_MC_NoAB", Vec_eSc_MC_NoAb.Theta()*TMath::RadToDeg(), Vec_eSc_MC_NoAb.P(), weight[0]);
      }
    }	
  }

  ofile->Write(); // Write histograms to file
  ofile->Close(); // Close output file

  // Function to write rates to csv file, enale/disable as needed
  //WriteCSV();
  
}

    // for(unsigned int i=0; i<nbfpartGenStat.GetSize(); i++) { // Loop over thrown nbf particles
    //   nbfpartEng = 
    //   if(partGenStat[i] == 4 && partPdg[i] == 2212) { prot_nbfbeam.SetPxPyPzE(nbfpartMomX[i],nbfpartMomY[i],nbfpartMomZ[i], nbfpartEng); }
		
    //   if(nbfpartGenStat[i] == 1 && nbfpartPdg[i] == 11) { // Select stable thrown nbf particles and look at electron
    // 	elec_nbfmc.SetPxPyPzE(nbfpartMomX[i], nbfpartMomY[i], nbfpartMomZ[i], nbfpartEng);
    // 	enbfTruthw_Thetap -> Fill(elec_nbfmc.Theta()*TMath::RadToDeg(), elec_nbfmc.P(), weightNorm);
    //   }
      
    //   if(nbfpartGenStat[i] == 1 && nbfpartPdg[i] == 211) { // Look at pion
    // 	pi_nbfmc.SetPxPyPzE(nbfpartMomX[i], nbfpartMomY[i], nbfpartMomZ[i], nbfpartEng);
    // 	pinbfTruthw_Thetap -> Fill(pi_nbfmc.Theta()*TMath::RadToDeg(), pi_nbfmc.P(), weightNorm);
    //   }
 
    //   if(nbfpartGenStat[i] == 1 && nbfpartPdg[i] == 2112) { // Look at neutron
    // 	neut_nbfmc.SetPxPyPzE(nbfpartMomX[i], nbfpartMomY[i], nbfpartMomZ[i], nbfpartEng);
    // 	nnbfTruthw_Thetap -> Fill(neut_nbfmc.Theta()*TMath::RadToDeg(), neut_nbfmc.P(), weightNorm);
    //   }
    
    // } // for over thrown nbf particles
