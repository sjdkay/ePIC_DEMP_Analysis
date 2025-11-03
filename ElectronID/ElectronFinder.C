// Data model headers
#include "edm4eic/ReconstructedParticleCollection.h"
#include "edm4hep/MCParticleCollection.h"
#include "edm4hep/utils/vector_utils.h"
#include "edm4hep/utils/kinematics.h"
#include "edm4eic/ClusterCollection.h"
#include "edm4eic/MCRecoParticleAssociationCollection.h"
#include "podio/Frame.h"
// #include "podio/ROOTFrameReader.h" -- for simulation campaign before March 2023 with eic-shell 25.03.2
#include "podio/ROOTReader.h"

// ROOT headers
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TVector3.h"
#include "TLorentzVector.h"

// Analysis headers
#include "ElectronFinder.h"

// This is a modified, slimmed down version which only tries to identify electrons in the event. It does NOT do any kinematic calculations or apply any selection cuts. If you feed in a file with 1000 events, you should get an output with 1000 events too. You could then compare this in parallel with the original file and only select out events with good e'
void ElectronFinder(double Ee = 0, double Eh = 0, TString OutStr = ""){

  // Set beam energy defaults if not specified
  if(Ee == 0){
    cout << "Electron beam energy not specified, defaulting to 10 GeV" << endl;
    Ee = 10;
  }
  if(Eh == 0){
    cout << "Ion beam energy not specified, defaulting to 130 GeV" << endl;
    Eh = 130;
  }
  if(OutStr == ""){
    OutStr = "ElectronFinder_Out";
  }
  // Set what electron ID to use
  //int eID_type = truthID;
  int eID_type = 0;

  // access local file
  //vector<std::string> inFiles = {"pythia8NCDIS_10x100_minQ2=10_beamEffects_xAngle=-0.025_hiDiv_1.0001.eicrecon.tree.edm4eic.root"};

  // access remote file
  vector<std::string> inFiles = {"root://dtn-rucio.jlab.org:1094//volatile/eic/EPIC/RECO/25.05.0/epic_craterlake/DIS/NC/10x100/minQ2=1/pythia8NCDIS_10x100_minQ2=1_beamEffects_xAngle=-0.025_hiDiv_1.0000.eicrecon.edm4eic.root"};

    // auto reader = podio::ROOTFrameReader();
  auto reader = podio::ROOTReader();
  reader.openFiles(inFiles);

  // setup eid
  ElectronID* eFinder = new ElectronID(Ee, Eh);

  // setup output file and histograms
  TString outFileName = Form("%s_%.0fx%.0fGeV.root", OutStr.Data(), Ee, Eh);
  CreateOutputTree(outFileName);

  cout << "Processing - " << reader.getEntries("events") << " events" << endl;
  
  // loop events
  for(size_t ev = 0; ev < reader.getEntries("events"); ev++) {

    if ( ev % ( reader.getEntries("events") / 20 ) == 0 ){
      cout << "Processed " << setw(4) << ceil(((1.0*ev)/(1.0*reader.getEntries("events")))*100.0) << " % of events - " << ev << endl;
    }
    ResetVariables();

    const auto event = podio::Frame(reader.readNextEntry("events"));
    eFinder->SetEvent(&event);

    edm4hep::MCParticleCollection e_mc = eFinder->GetMCElectron();

    // Skip events without scattered MC electron - All should have a scattered MC electron
    if(e_mc.size() == 0) 
      continue;

    // Set boost and get incoming particles
    TLorentzVector in_e;
    TLorentzVector in_n;
    LorentzRotation boost;
    eFinder->GetBeam(boost, in_e, in_n);
    in_e = boost(in_e);
    in_n =boost(in_n);

    // Calculate kinematic variables using MC electron
    TLorentzVector kprime;
    kprime.SetXYZM(e_mc[0].getMomentum().x, e_mc[0].getMomentum().y, e_mc[0].getMomentum().z, Me);
    TLorentzVector true_e_lab = kprime;
    kprime = boost(kprime); // boost back to head-on frame

    // Get momentum vector elements from MC electron
    mc_p = edm4hep::utils::magnitude(e_mc[0].getMomentum());
    mc_eta = edm4hep::utils::eta(e_mc[0].getMomentum());
    mc_phi = edm4hep::utils::angleAzimuthal(e_mc[0].getMomentum());

    // Find scattered electrons using mc association
    auto e_truth = eFinder->GetTruthReconElectron();

    // Find scattered electrons using detector information
    auto e_candidates = eFinder->FindScatteredElectron();
    edm4eic::ReconstructedParticle e_rec;	

    // If there are multiple candidates, select one with highest pT
    if(e_candidates.size() > 0) {
      positive_eID = 1;			
      e_rec = eFinder->SelectHighestPT(e_candidates);
    }

    // select which eID we are using
    PxPyPzEVector scat_ele(0, 0, 0, -1);
    if ( eID_type == truthID ) {
      if(e_truth.size() < 1) 
	continue;			
      scat_ele.SetPxPyPzE(e_truth[0].getMomentum().x, e_truth[0].getMomentum().y, e_truth[0].getMomentum().z, e_truth[0].getEnergy());
    }
    else if ( eID_type == mcID ) {
      scat_ele = true_e_lab;
    }
    else {
      if(!positive_eID)
	continue;
      scat_ele.SetPxPyPzE(e_rec.getMomentum().x, e_rec.getMomentum().y, e_rec.getMomentum().z, e_rec.getEnergy());
    }

    PxPyPzEVector rec_e_lab = scat_ele;
    if( eID_type!=2 ){
      // Calculate kinematics using track info only
      kprime.SetXYZM(rec_e_lab.Px(), rec_e_lab.Py(), rec_e_lab.Pz(), Me);
      TLorentzVector track_kprime = kprime;

      // Calculate kinematics using track + cluster energy
      TVector3 e3v = kprime.Vect();

      double track_clust_E;
      if ( eID_type == truthID )
	track_clust_E = eFinder->GetCalorimeterEnergy(e_truth[0]);
      else if ( eID_type == mcID )  
	track_clust_E = e_mc[0].getEnergy();
      else
	track_clust_E = eFinder->GetCalorimeterEnergy(e_rec);

      e3v.SetMag(track_clust_E);
      kprime.SetVectM(e3v, Me);
	
      TLorentzVector calo_kprime = kprime;

      // 	// // cut example
      // 	// if ( algorithm[MC].Q2 > 100 )
      // 	// 	scat_ele = calo_kprime;
    }

    scat_ele = boost(scat_ele);
    float theta = scat_ele.Theta();
    float E = scat_ele.E();	
	
    //if ( E > 0 )
    //algorithm[EL].save_variables(calc_elec_method(E, theta, pt_had, sigma_h, Ee, Eh), Mp);
    outTree->Fill(); // Fill for all events
    // }

  }
  
  outFile->cd();
  outTree->Write(outTree->GetName(), 2);
  outFile->Close();

  return;
}

void ResetVariables() {

  positive_eID = 0;

  for ( auto &v : algorithm )
    v.reset();

  mc_p = -999;
  mc_eta = -999;
  mc_phi = -999;
  
  track_p = -999;
  track_eta = -999;
  track_phi = -999;
}

void CreateOutputTree(TString outFileName) {

  outFile = new TFile(outFileName, "RECREATE");
  outTree = new TTree("T", "Reconstructed and generated information from EICRecon");

  outTree->Branch("positive_eID",		&positive_eID);
  outTree->Branch("mc_p",			&mc_p);
  outTree->Branch("mc_eta",		&mc_eta);
  outTree->Branch("mc_phi",		&mc_phi);

  outTree->Branch("track_p",		&track_p);	
  outTree->Branch("track_eta",	&track_eta);	
  outTree->Branch("track_phi",	&track_phi);
}

TLorentzVector GetHadronBeam(double fEh) {
 
  TLorentzVector hadron_beam;
  hadron_beam.SetX(fEh*sin(crossing_angle));
  hadron_beam.SetY(0.);
  hadron_beam.SetZ(fEh*cos(crossing_angle));
  hadron_beam.SetE(std::hypot(fEh, Mp));
  return hadron_beam;
}
