void sidis_5on41()
{

  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Enable this block when you process xrdfs files from collabration
  // Set up input file chain
  TChain *mychain = new TChain("events");

  std::ofstream error_file;
  error_file.open("error_file.txt", std::ios::trunc);
  if (!error_file.is_open()) {
    std::cerr << "Failed to open error log file!" << std::endl;
    return; // Exit the function if the file couldn't be opened
  }

  TString filepath;
  unsigned int nFiles = 0;  // Initialize the total files counter
  unsigned int nEntries;            // Variable to hold the number of entries in the tree

  // Loop through the specified ranges
  for (unsigned int i = 0; i < 3; i++) { //3
    for (unsigned int j = 0; j < 828; j++) { //828
      // Construct the file path
      filepath = Form("root://dtn-eic.jlab.org//work/eic2/EPIC/RECO/24.12.0/epic_craterlake/DIS/NC/5x41/minQ2=100/pythia8NCDIS_5x41_minQ2=100_beamEffects_xAngle=-0.025_hiDiv_%i.%04i.eicrecon.tree.edm4eic.root", i + 1, j);
      // Try opening the file to check if it's valid and then add to the TChain
      TFile *file = TFile::Open(filepath);
      if (file && !file->IsZombie()) {
	TTree *tree = (TTree*)file->Get("events");

	// Ensure the tree is valid before getting entries
	if (tree) {
	  nEntries = tree->GetEntries();
	  // std::cout << "nEntries = " << nEntries << std::endl;

	  if (nEntries == 1206) {
	    nFiles++;
	    mychain->Add(filepath);  // Add valid file to the chain
	  } else {
	    error_file << "Unexpected number of entries: " << nEntries << " in file: " << filepath << std::endl;
	  }
	} else {
	  error_file << "Tree 'events' not found in file: " << filepath << std::endl;
	}

	file->Close();  // Close the file
	delete file;    // Delete the file pointer
      } else {
	// If the file fails to open, log the error to the txt file
	error_file << "Failed to open file: " << filepath << std::endl;
	if (file) {
	  file->Close();  // Close the file if it was partially opened
	  delete file;    // Delete the file pointer
	}
	continue; // Skip further processing if the file could not be opened
      }
    }
  }

  error_file.close();  // Close the error log file
  unsigned int count2 = 0; // counter on neutrons within 4 mrad
  
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Enable this block when you process the files from Love Preet
  /*TChain *mychain = new TChain("events");
    unsigned int count1 = 0; // Counter for the number of files successfully added
    unsigned int count2 = 0; // Counter for neutrons within 4 mrad

    unsigned int nFiles1 = 1; // Number of iterations for the first loop // 3
    unsigned int nFiles2 = 100; // Number of iterations for the second loop // 950
    unsigned int nFiles; // Total number of files to process

    for (unsigned int i = 0; i < nFiles1; i++) {
    // if(i == 0) {nFiles2 = 40;}
    // else if(i == 1) {nFiles2 = 80;}
    // else if(i == 2) {nFiles2 = 91;}
  
    for (unsigned int j = 0; j < nFiles2; j++) {
    count1++;

    // Construct file name
    // TString fileName = Form("Test_5on41_pi+_Reco_AllEvents_%i_%i.root", 2 + i, 5000 + j * 5000);
        
    //Files from Jlab server
    //TString fileName = Form("/volatile/eic/preet/reco_simulation_output/Nov2024_Files/pi+/5on41/Test_5on41_pi+_Reco_AllEvents_%i_%i.root", 1 + i, 5000 + j * 5000);
    TString fileName = Form("/volatile/eic/preet/reco_simulation_output/Dec2024_Files/pi+/5on41/Test_5on41_pi+_Reco_AllEvents_%i_%i.root", 1 + i, 5000 + j * 5000);
      
    // Check if the file exists
    if (gSystem->AccessPathName(fileName) == kFALSE) {
    mychain->Add(fileName); // Add file to the TChain
    } 
    else {
    std::cerr << "Warning: File not found -> " << fileName << std::endl;
    std::cerr << "Terminating execution." << std::endl;
    std::exit(EXIT_FAILURE); // Exit with an error status
    }
    }
    }
    nFiles = count1;*/

  /* TChain *mychain = new TChain("events");
     unsigned int count1 = 0; // Counter for the number of files successfully added
     unsigned int count2 = 0; // Counter for neutrons within 4 mrad

     unsigned int nFiles1 = 1; // Number of iterations for the first loop // 1
     unsigned int nFiles2 = 1; // Number of iterations for the second loop // 828
     unsigned int nFiles; // Total number of files to process
     unsigned int nEntries;            // Variable to hold the number of entries in the tree
   
     for (unsigned int i = 0; i < nFiles1; i++) {
     for (unsigned int j = 0; j < nFiles2; j++) {
     count1++;
        
     // TString filePath = Form("root://dtn-eic.jlab.org//work/eic2/EPIC/RECO/24.12.0/epic_craterlake/DIS/NC/5x41/minQ2=100/pythia8NCDIS_5x41_minQ2=100_beamEffects_xAngle=-0.025_hiDiv_%i.%04i.eicrecon.tree.edm4eic.root", i + 1, j);
        
     TString filePath = Form("pythia8NCDIS_5x41_minQ2=100_beamEffects_xAngle=-0.025_hiDiv_%i.%04i.eicrecon.tree.edm4eic.root", i + 1, j);
        
     mychain->Add(filePath);
     nEntries = mychain->GetEntries();
     std::cout << "nEntries = " << nEntries << std::endl;
     } // for loop over j
     } // for loop over i
     nFiles = count1;*/
   
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Set output file for the histograms
  TFile *ofile = TFile::Open("sidis_hist_5on41.root","RECREATE");

  // Initialize reader
  TTreeReader tree_reader(mychain);

  // Get weight information
  TTreeReaderArray<std::vector<std::string>> weight_map(tree_reader, "GPStringValues");

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
  TTreeReaderArray<float> neutEng(tree_reader, "ReconstructedFarForwardZDCNeutrons.energy");
  TTreeReaderArray<float> neutMomX(tree_reader, "ReconstructedFarForwardZDCNeutrons.momentum.x");
  TTreeReaderArray<float> neutMomY(tree_reader, "ReconstructedFarForwardZDCNeutrons.momentum.y");
  TTreeReaderArray<float> neutMomZ(tree_reader, "ReconstructedFarForwardZDCNeutrons.momentum.z");
  TTreeReaderArray<unsigned int> neutClus(tree_reader, "ReconstructedFarForwardZDCNeutrons.clusters_end");

  // ZDC SiPM-on-tile HCal
  TTreeReaderArray<float> neutPosX_hcal(tree_reader, "HcalFarForwardZDCClusters.position.x");
  TTreeReaderArray<float> neutPosY_hcal(tree_reader, "HcalFarForwardZDCClusters.position.y");
  TTreeReaderArray<float> neutPosZ_hcal(tree_reader, "HcalFarForwardZDCClusters.position.z");
  TTreeReaderArray<float> neutEng_hcal(tree_reader, "HcalFarForwardZDCClusters.energy");
  
  // Get Before Afterburned information
  TTreeReaderArray<int>    nbfpartGenStat(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.generatorStatus"); //nbf stands for no beam effects
  TTreeReaderArray<float>  nbfpartMomX(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.x");
  TTreeReaderArray<float>  nbfpartMomY(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.y");
  TTreeReaderArray<float>  nbfpartMomZ(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.z");
  TTreeReaderArray<int>    nbfpartPdg(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.PDG");
  TTreeReaderArray<double> nbfpartMass(tree_reader,"MCParticlesHeadOnFrameNoBeamFX.mass");
  
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Define Histograms
  TH2* enbfTruthw_Thetap = new TH2D("enbfTruthw_Thethap","e' truth no beam effects #theta vs P; #theta (deg); P (GeV/c); Rate/bin (Hz)",100,0,180,100,4.0,30.0);
  TH2* pinbfTruthw_Thetap = new TH2D("pinbfTruthw_Thethap","#pi^{+} truth no beam effects #theta vs P; #theta (deg); P (GeV/c); Rate/bin (Hz)",100,0,180,100,0,30); //change
  TH2* nnbfTruthw_Thetap  = new TH2D("nnbfTruthw_Thethap","n truth no beam effects #theta vs P; #theta (Deg); P (GeV/c); Rate/bin (Hz)",100,0.0,180.0,100,0,40); //change 
  
  TH2* eTruthw_Thetap  = new TH2D("eTruthw_Thethap","e' truth #theta vs P; #theta (deg); P (GeV/c); Rate/bin (Hz)",100,10,180,100,4.0,30);
  TH2* piTruthw_Thetap = new TH2D("piTruthw_Thethap","#pi^{+} truth #theta vs P; #theta (deg); P (GeV/c); Rate/bin (Hz)",100,0,180,100,0,30); //change
  TH2* nTruthw_Thetap  = new TH2D("nTruthw_Thethap","n truth #theta vs P; #theta (Deg); P (GeV/c); Rate/bin (Hz)",100,0.0,180,100,0,40); //change 
  TH2* nTruthw_Thetaphi  = new TH2D("nTruthw_Thethaphi","n truth #theta vs #phi; #theta (mRad); #phi (deg); Rate/bin (Hz)",100,0.0,3500,100,-200,200); //change
  TH2* nTruthw_rot_Thetap  = new TH2D("nTruthw_rot_Thethap","n truth #theta* vs P around p axis; #theta* (Deg); P (GeV/c); Rate/bin (Hz)",100,0.0,180,100,0.0,40); //change
  TH2* nTruthw_rot_Thetaphi  = new TH2D("nTruthw_rot_Thethaphi","n truth #theta* vs #phi* around p axis; #theta* (mRad); #phi* (deg); Rate/bin (Hz)",100,0.0,3500,100,-200,200); //change

  TH2* eRecw_Thetap  = new TH2D("eRecw_Thethap","e' rec #theta vs P; #theta (deg); P (GeV/c); Rate/bin (Hz)",100,0,180,100,0.0,40);
  TH2* eRecw_Thetaphi  = new TH2D("eRecw_Thethaphi","e' rec #theta vs #phi; #theta (deg); P (GeV/c); Rate/bin (Hz)",100,0,180,100,-200,200);
  TH2* piRecw_Thetap = new TH2D("piRecw_Thethap","#pi^{+} rec #theta vs P; #theta (deg); P (GeV/c); Rate/bin (Hz)",100,0,180,100,0,40); //change
  TH2* piRecw_Thetaphi  = new TH2D("piRecw_Thethaphi","#pi^{+} rec #theta vs #phi; #theta (deg); Rate/bin (Hz); P (GeV/c)",100,0,180,100,-200,200); //change
  //TH2* eRecw_Thetap  = new TH2D("eRecw_Thethap","e^{+}' rec #theta vs P; #theta (deg); P (GeV/c)",100,0,60,100,0,15);  // positron
  //TH2* piRecw_Thetap = new TH2D("piRecw_Thethap","#pi^{-} rec #theta vs P; #theta (deg); P (GeV/c)",100,130,170,100,0,10); // pion -
  TH2* nRecw_Thetap  = new TH2D("nRecw_Thethap","n rec #theta vs P for all clusters; #theta (Deg); P (GeV/c); Rate/bin (Hz)",100,0.8,2.0,100,0.0,60); //change
  TH2* nRecw_rot_Thetap  = new TH2D("nRecw_rot_Thethap","n rec #theta* vs P around p axis for all clusters ( rec #theta* < 4.0 mRad, E > 10 GeV ); #theta* (mRad); P (GeV/c); Rate/bin (Hz)",100,0.0,4.5,100,0,60); //change
  TH2* nRecw_Thetaphi  = new TH2D("nRecw_Thethaphi","n rec #theta vs #phi for all clusters; #theta (mRad); #phi (deg); Rate/bin (Hz)",100,15.0,35.0,100,-200,200); 
  TH2* nRecw_rot_Thetaphi  = new TH2D("nRecw_rot_Thethaphi","n rec #theta* vs #phi* around p axis for all clusters; #theta* (mRad); #phi* (deg); Rate/bin (Hz)",100,0.0,12.0,100,-200,200);
  TH2* nRecw_rot_PosXY  = new TH2D("nRecw_rot_PosXY","n X vs Y around proton axis at Z = 35 m for all clusters ( rec #theta* < 4.0 mRad, E > 40 GeV ); x (mm); y (mm); Rate/bin (Hz)",100,-200,200,100,-200,200);


  TH1* nRec_en = new TH1D("nRec_en", "n rec E for all clusters ( rec #theta* < 4.0 mRad ); E (GeV); Rate (Hz)", 100, 0.0, 60); //change
  nRec_en->SetLineWidth(2);
  TH1* nRec_clus = new TH1D("nRec_clus", "n all clusters ( rec #theta* < 4.0 mRad )", 100, 0.0, 8.0);
  nRec_clus->SetLineWidth(2);

  // Neutron theta-phi plots 
  TH1* n_ThetaDiff = new TH1D("n_ThetaDiff", "#theta*_{pMiss_rec} - #theta*_{ZDC}; #theta*_{pMiss_rec} - #theta*_{ZDC}(Deg); Rate (Hz)", 100, -0.3, 1.5);
  n_ThetaDiff->SetLineWidth(2);
  TH1* n_PhiDiff = new TH1D("n_PhiDiff", " #phi*_{pMiss_rec} - #phi*_{ZDC}; #phi*_{pMiss_rec} - #phi*_{ZDC}(Deg); Rate (Hz)", 100, -100, 100);
  n_PhiDiff->SetLineWidth(2);
  TH2* n_ThetaPhiDiff = new TH2D("n_ThetaPhiDiff", "#theta*_{pMiss_rec} - #theta*_{ZDC} vs #phi*_{pMiss_rec} - #phi*_{ZDC}; #theta*_{pMiss_rec} - #theta*_{ZDC} (Deg); #phi*_{pMiss_rec} - #phi*_{ZDC} (Deg); Rate/bin (Hz)",100, -1.0, 1.0, 100, -75, 75);
  TH2* pMissRecw_Thetaphi = new TH2D("pMissRecw_Thetaphi", "pMiss rec #theta vs #phi; #theta (mRad); #phi (deg); Rate/bin (Hz)",100,15.0,35.0,100,-200,200);
  TH2* pMissRecw_rot_Thetaphi = new TH2D("pMissRecw_rot_Thetaphi", "pMiss rec  #theta* vs #phi* around p axis; #theta* (mRad); #phi* (deg); Rate/bin (Hz)",100,0.0,15.0,100,-200,200);
  TH2* n_TruthRecw_ThetaPhiDiff = new TH2D("n_TruthRecw_ThetaPhiDiff", " #theta*_{n_MC} - #theta*_{n_rec} vs #phi*_{n_MC} - #phi*_{n_rec}; #theta*_{n_MC} - #theta*_{n_rec} (Deg); #phi*_{n_MC} - #phi*_{n_rec} (Deg); Rate/bin (Hz)",100, -0.2, 0.2, 100, -25, 25);

  // Absolute difference -t plots //no change
  TH1* htw_t1 = new TH1D("htw_t1", "-t_{rec, alt_rec, rec_pT, rec_corr} - -t_{alt_truth} Distribution; #Delta -t (GeV^{2}); Rate (Hz) ", 100, -0.2,0.3);
  htw_t1->SetLineColor(kBlue); htw_t1->SetLineWidth(2);
  TH1* htw_t2 = new TH1D("htw_t2", "-t_{rec, alt_rec, rec_pT, rec_corr} - -t_{alt_truth} Distribution; #Delta -t (GeV^{2}); Rate (Hz) ", 100, -0.2,0.3);
  htw_t2->SetLineColor(kRed);  htw_t2->SetLineWidth(2);
  TH1* htw_t3 = new TH1D("htw_t3", "-t_{rec, alt_rec, rec_pT, rec_corr} - -t_{alt_truth} Distribution; #Delta -t (GeV^{2}); Rate (Hz) ", 100, -0.2,0.3);
  htw_t3->SetLineColor(kMagenta+1); htw_t3->SetLineWidth(2);
  TH1* htw_t4 = new TH1D("htw_t4", "-t_{rec, alt_rec, rec_pT, rec_corr} - -t_{alt_truth} Distribution; #Delta -t (GeV^{2}); Rate (Hz) ", 100, -0.2,0.3);
  htw_t4->SetLineColor(kGreen+2); htw_t4->SetLineWidth(2);

  // -t reconstruction plots //no change
  TH2* htw_rec1 = new TH2D("htw_rec1", "-t rec vs -t truth Distribution; -t_{rec} (GeV^{2});-t_{truth}(GeV^{2}); Rate/bin (Hz)", 100, 0.0,2.0,100, 0.0,1.5);
  TH2* htwz_rec1 = new TH2D("htwz_rec1", "-t rec vs -t truth Distribution; -t_{rec} (GeV^{2});-t_{truth}(GeV^{2}); Rate/bin (Hz)", 100, 0.0,0.2,100, 0.0,0.2); // zoomed version
  TH2* htw_rec2 = new TH2D("htw_rec2", "-t alt_rec vs -t truth Distribution; -t_{alt_rec} (GeV^{2});-t_{truth}(GeV^{2}); Rate/bin (Hz)", 100, 0.0,2.0,100, 0.0,1.5);
  TH2* htwz_rec2 = new TH2D("htwz_rec2", "-t alt_rec vs -t truth Distribution; -t_{alt_rec} (GeV^{2});-t_{truth}(GeV^{2}); Rate/bin (Hz)", 100, 0.0,0.2,100, 0.0,0.2); // zoomed version
  TH2* htw_rec3 = new TH2D("htw_rec3", "-t rec_pT vs -t truth Distribution; -t_{rec_Test_5on41_pi+_Reco_AllEvents_2_*.rootpT} (GeV^{2});-t_{truth}(GeV^{2}); Rate/bin (Hz)", 100, 0.0,2.0,100, 0.0,1.5);
  TH2* htwz_rec3 = new TH2D("htwz_rec3", "-t rec_pT vs -t truth Distribution; -t_{rec_pT} (GeV^{2});-t_{truth}(GeV^{2}); Rate/bin (Hz)", 100, 0.0,0.2,100, 0.0,0.2); // zoomed version
  TH2* htw_rec4 = new TH2D("htw_rec4", "-t rec_corr vs -t truth Distribution; -t_{rec_corr} (GeV^{2});-t_{truth}(GeV^{2}); Rate/bin (Hz)", 100, 0.0,2.0,100, 0.0,1.5);
  TH2* htwz_rec4 = new TH2D("htwz_rec4", "-t rec_corr vs -t truth Distribution; -t_{rec_corr} (GeV^{2});-t_{truth}(GeV^{2}); Rate/bin (Hz)", 100, 0.0,0.2,100, 0.0,0.2); // zoomed version

  // Resolution plots 
  TH1* htw_res_e = new TH1D("htw_res_e", "e' Track Momentum Resolution Distribution (%); (P_{rec} - P_{MC})/P_{MC} (%); Rate (Hz)", 100, -20, 20);
  htw_res_e->SetLineWidth(2);
  TH1* htw_res_pi = new TH1D("htw_res_pi", "#pi^{+} Track Momentum Resolution Distribution (%); (P_{rec} - P_{MC})/P_{MC} (%); Rate (Hz)", 100, -15, 15);
  htw_res_pi->SetLineWidth(2);
  TH1* htw_res_n1 = new TH1D("htw_res_n1", "n Track Momentum Resolution Distribution (%); (P_{rec} - P_{MC})/P_{MC} (%); Rate (Hz)", 100, -60, 60);
  htw_res_n1->SetLineWidth(2);
  TH1* htw_res_n2 = new TH1D("htw_res_n2", "n Track #theta* Resolution Distribution (%); (#theta*_{rec} - #theta*_{MC})/#theta*_{MC} (%); Rate (Hz)", 100, -50, 50);
  htw_res_n2->SetLineWidth(2);
  TH1* htw_res_n3 = new TH1D("htw_res_n3", "n Track #phi* Resolution Distribution (%); (#phi*_{rec} - #phi*_{MC})/#phi*_{MC} (%); Rate (Hz)", 100, -50, 50);
  htw_res_n3->SetLineWidth(2);
  TH1* htw_res_n4 = new TH1D("htw_res_n4", "n Track Momentum Resolution Distribution (%); (P_{rec_corr} - P_{MC})/P_{MC} (%); Rate (Hz)", 100, -3, 3);
  htw_res_n4->SetLineWidth(2);

  TH1* htw_res1 = new TH1D("htw_res1", "-t Resolution Distribution (%); (t_{rec} - t_{truth})/t_{truth} (%); Rate (Hz)", 100, -200, 200);
  htw_res1->SetLineWidth(2);
  TH1* htw_res2 = new TH1D("htw_res2", "-t Resolution Distribution (%); (t_{alt_rec} - t_{truth})/t_{truth} (%); Rate (Hz)", 100, -110, 310);
  htw_res2->SetLineWidth(2);
  TH1* htw_res3 = new TH1D("htw_res3", "-t Resolution Distribution (%); (t_{rec_pT} - t_{truth})/t_{truth} (%); Rate (Hz)", 100, -110, 210);
  htw_res3->SetLineWidth(2);
  TH1* htw_res4 = new TH1D("htw_res4", "-t Resolution Distribution (%); (t_{rec_corr} - t_{truth})/t_{truth} (%); Rate (Hz)", 100, -100, 100);
  htw_res4->SetLineWidth(2);
  TH1* htw_res5 = new TH1D("htw_res5", "Q^{2} Resolution Distribution (%); (Q^{2}_{rec} - Q^{2}_{truth})/Q^{2}_{truth} (%); Rate (Hz)", 100, -20, 20);
  htw_res5->SetLineWidth(2);
  TH1* htw_res6 = new TH1D("htw_res6", "W Resolution Distribution (%); (W_{rec} - W_{truth})/W_{truth} (%); Rate (Hz)", 100, -100, 150); //change
  htw_res6->SetLineWidth(2);

  // Effeciency plots
  TH2* Q2_t_DetEff_Uncut = new TH2F("Q2_t_DetEff_Uncut", "Q^{2}_{truth} vs -t_{alt_truth} for thrown events; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 25, 0, 0.5);
  TH2* Q2_t_DetEff_Cut = new TH2F("Q2_t_DetEff_Cut", "Q^{2}_{truth} vs -t_{alt_truth} for detected events; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 25, 0, 0.5);
  TH2* Q2_t_DetEff = new TH2F("Q2_t_DetEff", "Q^{2}_{truth} vs -t_{alt_truth} detected/thrown ratio; Q^{2} (GeV^{2}); -t (GeV^{2})", 40, 0, 40, 25, 0, 0.5); //20, 0, 40, 30, 0, 1.5

  TH1* eTruthw_Eta_Uncut = new TH1D("eTruthw_Eta_Uncut", "e' #eta for thrown events; #eta; Rate (Hz)",100,-3,0);
  eTruthw_Eta_Uncut->SetLineWidth(2);
  TH1* eRecw_Eta_Cut = new TH1D("eRecw_Eta_Cut", "e' #eta for detected events; #eta; Rate (Hz)",100,-3,0);
  eRecw_Eta_Cut->SetLineWidth(2);
  TH1* eEff_Eta = new TH1D("eEff_Eta", "e' Tracking efficiency as fn of #eta; #eta; Eff", 100,-3,0);
  eEff_Eta->SetLineWidth(2);

  TH1* piTruthw_Eta_Uncut = new TH1D("piTruthw_Eta_Uncut", "#pi^{+} #eta for thrown events; #eta; Rate (Hz)",100,-1,6); //change
  piTruthw_Eta_Uncut->SetLineWidth(2);
  TH1* piRecw_Eta_Cut = new TH1D("piRecw_Eta_Cut", "#pi^{+} #eta for detected events; #eta; Rate (Hz)",100,-1,6); //change
  piRecw_Eta_Cut->SetLineWidth(2);
  TH1* piEff_Eta = new TH1D("piEff_Eta", "#pi^{+} Tracking efficiency as fn of #eta; #eta; Eff",100,-1,6); //change
  piEff_Eta->SetLineWidth(2);

  TH1* eTruthw_P_Uncut = new TH1D("eTruthw_P_Uncut", "e' P for thrown events; P (GeV/c); Rate (Hz)",100,4.0,7.0);
  eTruthw_P_Uncut->SetLineWidth(2);
  TH1* eRecw_P_Cut = new TH1D("eRecw_P_Cut", "e' P for detected events; P (GeV/c); Rate (Hz)",100,4.0,7.0);
  eRecw_P_Cut->SetLineWidth(2);
  TH1* eEff_P = new TH1D("eEff_P", "e' Tracking efficiency as fn of P; P (GeV/c); Eff", 100,4.0,7.0);
  eEff_P->SetLineWidth(2);

  TH1* piTruthw_P_Uncut = new TH1D("piTruthw_P_Uncut", "#pi^{+} P for thrown events; P (GeV/c); Rate (Hz)",100,0,30); //change
  piTruthw_P_Uncut->SetLineWidth(2);
  TH1* piRecw_P_Cut = new TH1D("piRecw_P_Cut", "#pi^{+} P for detected events; P (GeV/c); Rate (Hz)",100,0,30); //change
  piRecw_P_Cut->SetLineWidth(2);
  TH1* piEff_P = new TH1D("piEff_P", "#pi^{+} Tracking efficiency as fn of P; P (GeV/c); Eff",100,0,30); //change
  piEff_P->SetLineWidth(2);

  // Neutrons in HCal
  TH2* nRecw_Thetap_hcal  = new TH2D("nRecw_Thethap_hcal","n rec #theta vs P for 1 cluster events; #theta (Deg); P (GeV/c); Rate/bin (Hz)",100,0.8,2.0,100,0.0,40); //change
  TH2* nRecw_rot_Thetap_hcal  = new TH2D("nRecw_rot_Thethap_hcal","n rec #theta* vs P around p axis for 1 cluster events ( rec #theta* < 4.0 mRad, E > 10 GeV ); #theta* (mRad); P (GeV/c); Rate/bin (Hz)",100,0,4.5,100,10,40); //change
    
  // y plot 
  TH1* htw_Truth_y = new TH1D("htw_Truth_y", "y truth Distribution; y; Rate (Hz) ", 100,-0.4,0.4);
  htw_Truth_y->SetLineWidth(2);
  TH1* htw_Rec_y = new TH1D("htw_Rec_y", "y rec Distribution; y; Rate (Hz) ", 100,-0.4,0.4);
  htw_Rec_y->SetLineWidth(2);
  TH1* htw_Truth_t = new TH1D("htw_Truth_t", "-t truth Distribution; -t (GeV^{2}); Rate (Hz) ", 100,-0.1,1.4);
  htw_Truth_t->SetLineWidth(2);
    
  // Physics results //no change
  double Q2BinVal[8] = {5.0, 7.5, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0}; 
    
  TH1* htw_t_cut_result[8];
  TH1* htw_Q2_cut_result[8];
  TH1* htw_W_cut_result[8];
  
  for(unsigned int A = 0; A <8; A++) {
    if (A==0){
      htw_t_cut_result[A] = new TH1D(Form("t_Result_Q2_%i", A), Form("-t dist w/ %2.1f < Q^{2} < %2.1f, -t, #theta_{diff} , #phi_{diff}, W cuts; -t_{rec_corr} (GeV^{2}); Rate(Hz)", 		Q2BinVal[0],Q2BinVal[7]), 10, 0, 0.4);
      htw_Q2_cut_result[A] = new TH1D(Form("Q2_Result_Q2_%i", A), Form("Q^{2} dist w/ %2.1f < Q^{2} < %2.1f, -t, #theta_{diff} , #phi_{diff}, W cuts; Q^{2} (GeV^{2}); Rate(Hz)", 		Q2BinVal[0],Q2BinVal[7]), 25, Q2BinVal[0], Q2BinVal[7]);
      htw_W_cut_result[A] = new TH1D(Form("W_Result_Q2_%i", A), Form("W dist w/ %2.1f < Q^{2} < %2.1f, -t, #theta_{diff} , #phi_{diff}, W cuts; W (GeV); Rate(Hz)", 		Q2BinVal[0],Q2BinVal[7]), 40, 0, 20);
    }
    
    else {
      htw_t_cut_result[A] = new TH1D(Form("t_Result_Q2_%i", A), Form("-t dist w/ %2.1f < Q^{2} < %2.1f, -t, #theta_{diff} , #phi_{diff}, W cuts; -t_{rec_corr} (GeV^{2}); Rate(Hz)", Q2BinVal[A-1],Q2BinVal[A]), 10, 0, 0.4);
      htw_Q2_cut_result[A] = new TH1D(Form("Q2_Result_Q2_%i", A), Form("Q^{2} dist w/ %2.1f < Q^{2} < %2.1f, -t, #theta_{diff} , #phi_{diff}, W cuts; Q^{2} (GeV^{2}); Rate(Hz)", Q2BinVal[A-1],Q2BinVal[A]), 25, Q2BinVal[A-1]-5, Q2BinVal[A]+5);
      htw_W_cut_result[A] = new TH1D(Form("W_Result_Q2_%i", A), Form("W dist w/ %2.1f < Q^{2} < %2.1f, -t, #theta_{diff} , #phi_{diff}, W cuts; W (GeV); Rate(Hz)", Q2BinVal[A-1],Q2BinVal[A]), 40, 0, 20);
    }
    
    htw_t_cut_result[A]->SetLineWidth(2);
    htw_Q2_cut_result[A]->SetLineWidth(2);
    htw_W_cut_result[A]->SetLineWidth(2);
  }
  
  // Q2 plots
  TH2* h2Truthw_W_Q2  = new TH2D("h2Truthw_W_Q2","W vs Q^{2} truth distribution; W (GeV); Q^{2} (GeV^{2}); Rate/bin (Hz)",100,0.0,11.0,100,0,40);
  TH2* h2Recw_W_Q2  = new TH2D("h2Recw_W_Q2","W vs Q^{2} rec distribution; W (GeV); Q^{2} (GeV^{2})",100,-100,100,100,0,40);
  
  TH2* h2Truthw_t_Q2  = new TH2D("h2Truthw_t_Q2","-t_{truth} vs Q^{2} truth distribution; -t_{truth} (GeV^{2}); Q^{2} (GeV^{2}); Rate/bin (Hz)",100,0.0,1.5,100,0,40);
  TH2* h2Recw_t1_Q2  = new TH2D("h2Recw_t1_Q2","-t_{rec} vs Q^{2} rec distribution; -t_{rec} (GeV^{2}); Q^{2} (GeV^{2}); Rate/bin (Hz)",100,0.0,2.0,100,0,40);
  TH2* h2Recw_t2_Q2  = new TH2D("h2Recw_t2_Q2","-t_{alt_rec} vs Q^{2} rec distribution; -t_{alt_rec} (GeV^{2}); Q^{2} (GeV^{2}); Rate/bin (Hz)",100,0.0,1.0,100,0,40);
  TH2* h2Recw_t3_Q2  = new TH2D("h2Recw_t3_Q2","-t_{rec_pT} vs Q^{2} rec distribution; -t_{rec_pT} (GeV^{2}); Q^{2} (GeV^{2}); Rate/bin (Hz)",100,0.0,1.0,100,0,40);
  TH2* h2Recw_t4_Q2  = new TH2D("h2Recw_t4_Q2","-t_{rec_corr} vs Q^{2} rec distribution; -t_{rec_corr} (GeV^{2}); Q^{2} (GeV^{2}); Rate/bin (Hz)",100,0.0,1.0,100,0,40);
  
  //-t plots
  TH1* htw_t_1 = new TH1D("htw_t_1", " -t_{alt} Distribution; -t_{alt} (GeV^{2}); Rate (Hz) ", 100, -0.1,1);
  htw_t_1->SetLineColor(kBlack); htw_t_1->SetLineWidth(2);
  TH1* htw_t_2 = new TH1D("htw_t_2", "-t_{alt} Distribution; -t_{alt} (GeV^{2}); Rate (Hz) ", 100, -0.1,1);
  htw_t_2->SetLineColor(kBlue);  htw_t_2->SetLineWidth(2);
  TH1* htw_t_3 = new TH1D("htw_t_3", "-t_{alt} Distribution; -t_{alt} (GeV^{2}); Rate (Hz) ", 100, -0.1,1);
  htw_t_3->SetLineColor(kGreen+2);  htw_t_3->SetLineWidth(2);
  
  //w plot
  TH1* htw_Rec_w = new TH1D("htw_Rec_w", "w rec Distribution w/ 5 < Q^{2} < 35; W (GeV)", 100,-150,100);
  htw_Rec_w->SetLineWidth(2);
 
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //Defining the four vectors
  ROOT::Math::PxPyPzEVector elec_beam; // initialized the 4 vector for electron beam
  ROOT::Math::PxPyPzEVector prot_beam; // initialized the 4 vector for proton beam
  ROOT::Math::PxPyPzEVector prot_nbfbeam; // initialized the 4 vector for proton beam for nbf

  ROOT::Math::PxPyPzEVector elec_nbfmc; // initialized the 4 vector for truth nbf electron
  ROOT::Math::PxPyPzEVector pi_nbfmc; // initialized the 4 vector for truth nbf pion
  ROOT::Math::PxPyPzEVector neut_nbfmc; // initialized the 4 vector for truth nbf neutron
  
  ROOT::Math::PxPyPzEVector virtphoton_nbftruth; // intialized the 4 vector for truth virtual photon for nbf
  ROOT::Math::PxPyPzEVector tnbftruth; // intialized the 4 vector for ttruth (-t)from first loop for nbf
  ROOT::Math::PxPyPzEVector tnbfalttruth; // intialized the 4 vector for ttruth (-t)from first loop for nbf
   
  ROOT::Math::PxPyPzEVector elec_mc; // initialized the 4 vector for truth electron
  ROOT::Math::PxPyPzEVector pi_mc; // initialized the 4 vector for truth pion
  ROOT::Math::PxPyPzEVector neut_mc; // initialized the 4 vector for truth neutron
  ROOT::Math::PxPyPzEVector neut_rot_mc; // initialized the 4 vector for truth neutron with a rotation of 25 mrad

  ROOT::Math::RotationY rot; // initialized rotation vector
  rot.SetAngle(0.025);

  ROOT::Math::PxPyPzEVector elec_rec; // initialized the 4 vector for reconstructed electron
  ROOT::Math::PxPyPzEVector pi_rec; // initialized the 4 vector for reconstructed pion
  ROOT::Math::PxPyPzEVector neut_rec; // initialized the 4 vector for reconstructed neutron
  ROOT::Math::PxPyPzEVector neut_rot_rec; // initialized the 4 vector for reconstructed neutron with a rotation of 25 mrad

  ROOT::Math::PxPyPzEVector virtphoton_truth; // intialized the 4 vector for truth virtual photon
  ROOT::Math::PxPyPzEVector ttruth; // intialized the 4 vector for ttruth (-t)from first loop
  ROOT::Math::PxPyPzEVector talttruth; // intialized the 4 vector for talttruth(-t) from second loop

  ROOT::Math::PxPyPzEVector virtphoton_rec; //intialized the 4 vector for reconstructed virtual photon
  ROOT::Math::PxPyPzEVector trec; // intialized the 4 vector for trec (-t)from first loop
  ROOT::Math::PxPyPzEVector taltrec; // intialized the 4 vector for taltrec(-t) from second loop
  ROOT::Math::PxPyPzEVector trecpT; // intialized the 4 vector for trecpT(-t)
  ROOT::Math::PxPyPzEVector trecpT_rot; // intialized the 4 vector for trecpT(-t) with a rotation of 25 mrad
  ROOT::Math::PxPyPzEVector p_miss_rec;  //intialized the 4 vector for missing momentum
  ROOT::Math::PxPyPzEVector p_miss_rot_rec; //intialized the 4 vector for missing momentum with a rotation of 25 mrad
  ROOT::Math::PxPyPzMVector neut_corr; // intialized the 4 vector for reconstructed corrected neutron
  ROOT::Math::PxPyPzEVector treccorr; // intialized the 4 vector for trecpT(-t)

  ROOT::Math::XYZVector neut_pos_hcal; // initialized the 3 vector for zdc position
  ROOT::Math::PxPyPzEVector neut_rec_hcal; // initialized the 4 vector for reconstructed neutorn in hcal
  ROOT::Math::PxPyPzEVector neut_rot_rec_hcal; // initialized the 4 vector for reconstructed neutron with a rotation of 25 mrad in hcal
  
  int hcal_clus_size;
  double neut_rec_p_hcal;
  
  double neutMass = 0.93965420;
  double weight, partEng, nbfpartEng; // weight and energy of the particles
  double Q2_truth, W_truth, y_truth, t_truth, t_alttruth; // Truth kinematic variables
  double Q2_rec, W_rec, y_rec, t_rec, t_altrec, t_recpT, t_reccorr; // Reconstructed kinematic variables
  double neutPosX, neutPosY; // neutron position
  double nTheta_Diff, nPhi_Diff;
  double ThetaDiff_Cut_Low = - 0.1; // change based on the reconstructed plots of neutron theta vs phi 
  double ThetaDiff_Cut_High = 0.2;
  double PhiDiff_Cut = 55.0;
  double Q2_low, Q2_high, Pmiss;
  double t_nbftruth, t_nbfalttruth;
  
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Defining initial colliding beams
  double eMass = 0.000510998950; //electron beam
  double eEng = 5;
  double e_pmag = sqrt(pow(eEng,2)-pow(eMass,2));
  double e_p1 = 0.;
  double e_p2 = 0.;
  double e_p3 = -1*e_pmag;
  elec_beam.SetPxPyPzE(e_p1, e_p2, e_p3, eEng); 
 
              
  double pMass = 0.93827208816; // proton beam
  double pEng = 41; //change
  double p_pmag = sqrt(pow(pEng,2)-pow(pMass,2));
  double c_a = 0.025;
  double p_p1 = -p_pmag*sin(c_a);
  double p_p2 = 0.;
  double p_p3 = p_pmag*cos(c_a);
  prot_beam.SetPxPyPzE(p_p1, p_p2, p_p3, pEng);
  
  prot_nbfbeam.SetPxPyPzE(0., 0., p_pmag, pEng); // calculate -t from second vertex for nbf 
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  bool x,y,z; // x,y, and z are for reconstructed electron, pion, and neutron
 
  while(tree_reader.Next()) { // Loop over events
 
    x = false, y = false, z = false;
 
    std::vector<std::string> weight_value = weight_map[0];
    weight = std::stod(weight_value[0]);
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
    for(unsigned int i=0; i<nbfpartGenStat.GetSize(); i++) { // Loop over thrown nbf particles
      nbfpartEng = sqrt(pow(nbfpartMomX[i],2) + pow(nbfpartMomY[i],2) + pow(nbfpartMomZ[i],2) + pow(nbfpartMass[i],2)); // Energy of all Truth nbf  Monte Carlo particles
		
      if(nbfpartGenStat[i] == 1 && nbfpartPdg[i] == 11) { // Select stable thrown nbf particles and look at electron
	elec_nbfmc.SetPxPyPzE(nbfpartMomX[i], nbfpartMomY[i], nbfpartMomZ[i], nbfpartEng);
	enbfTruthw_Thetap -> Fill(elec_nbfmc.Theta()*TMath::RadToDeg(), elec_nbfmc.P(), weight);
      }
      
      if(nbfpartGenStat[i] == 1 && nbfpartPdg[i] == 211) { // Look at pion
	pi_nbfmc.SetPxPyPzE(nbfpartMomX[i], nbfpartMomY[i], nbfpartMomZ[i], nbfpartEng);
	pinbfTruthw_Thetap -> Fill(pi_nbfmc.Theta()*TMath::RadToDeg(), pi_nbfmc.P(), weight);
      }
 
      if(nbfpartGenStat[i] == 1 && nbfpartPdg[i] == 2112) { // Look at neutron
	neut_nbfmc.SetPxPyPzE(nbfpartMomX[i], nbfpartMomY[i], nbfpartMomZ[i], nbfpartEng);
	nnbfTruthw_Thetap -> Fill(neut_nbfmc.Theta()*TMath::RadToDeg(), neut_nbfmc.P(), weight);
      }
    
    } // for over thrown nbf particles
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
    for(unsigned int i=0; i<partGenStat.GetSize(); i++) { // Loop over thrown particles
      partEng = sqrt(pow(partMomX[i],2) + pow(partMomY[i],2) + pow(partMomZ[i],2) + pow(partMass[i],2)); // Energy of all Monte Carlo particles
		
      if(partGenStat[i] == 1 && partPdg[i] == 11) { // Select stable thrown particles and look at electron
	elec_mc.SetPxPyPzE(partMomX[i],partMomY[i],partMomZ[i], partEng);
	eTruthw_Thetap -> Fill(elec_mc.Theta()*TMath::RadToDeg(), elec_mc.P(), weight);
	eTruthw_Eta_Uncut -> Fill(elec_mc.Eta(), weight);
	eTruthw_P_Uncut -> Fill(elec_mc.P(), weight);
      }
 
      if(partGenStat[i] == 1 && partPdg[i] == 211) { // Look at pion
	pi_mc.SetPxPyPzE(partMomX[i],partMomY[i],partMomZ[i], partEng);
	piTruthw_Thetap -> Fill(pi_mc.Theta()*TMath::RadToDeg(), pi_mc.P(), weight);
	piTruthw_Eta_Uncut -> Fill(pi_mc.Eta(), weight);
	piTruthw_P_Uncut -> Fill(pi_mc.P(), weight);
      }
 
      if(partGenStat[i] == 1 && partPdg[i] == 2112) { // Look at neutron
	neut_mc.SetPxPyPzE(partMomX[i],partMomY[i],partMomZ[i], partEng);
	nTruthw_Thetap -> Fill(neut_mc.Theta()*TMath::RadToDeg(), neut_mc.P(), weight);
	nTruthw_Thetaphi -> Fill(neut_mc.Theta()*1000., neut_mc.Phi()*TMath::RadToDeg(), weight);
 
	neut_rot_mc = rot*neut_mc;  // rotate w.r.t to proton axis
	nTruthw_rot_Thetap -> Fill(neut_rot_mc.Theta()*TMath::RadToDeg(), neut_rot_mc.P(), weight);
	nTruthw_rot_Thetaphi -> Fill(neut_rot_mc.Theta()*1000., neut_rot_mc.Phi()*TMath::RadToDeg(), weight);
      }			           
 
    } // for over thrown particles
 
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
    for(unsigned int i=0; i<trackPdg.GetSize(); i++) { // Loop over reconstructed particles 
      if(trackPdg[i] == 11) { // Look at electron
	//if(trackCharge[i] == -1 && trackMomZ[i] < 0) { 
	x = true;
	elec_rec.SetPxPyPzE(trackMomX[i],trackMomY[i],trackMomZ[i], trackEng[i]);
	eRecw_Thetap -> Fill(elec_rec.Theta()*TMath::RadToDeg(), elec_rec.P(), weight);
	eRecw_Thetaphi -> Fill(elec_rec.Theta()*TMath::RadToDeg(), elec_rec.Phi()*TMath::RadToDeg(), weight);
	eRecw_Eta_Cut -> Fill(elec_mc.Eta(), weight);
	eRecw_P_Cut -> Fill(elec_mc.P(), weight);
      }
 
      if(trackPdg[i] == 211) { // Look at pion
	//if(trackCharge[i] == +1 && trackMomZ[i] > 0) {
	y = true;
	pi_rec.SetPxPyPzE(trackMomX[i],trackMomY[i],trackMomZ[i], trackEng[i]);
	piRecw_Thetap -> Fill(pi_rec.Theta()*TMath::RadToDeg(), pi_rec.P(), weight);
	piRecw_Thetaphi ->  Fill(pi_rec.Theta()*TMath::RadToDeg(), pi_rec.Phi()*TMath::RadToDeg(), weight);
	piRecw_Eta_Cut -> Fill(pi_mc.Eta(), weight);
	piRecw_P_Cut -> Fill(pi_mc.P(), weight);
      }
 
    }// for over reconstructed particles

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    for(unsigned int i=0; i<neutEng.GetSize(); i++) { // Loop over zdc neutrons
 
      neut_rec.SetPxPyPzE(neutMomX[i],neutMomY[i],neutMomZ[i], neutEng[i]);
      nRecw_Thetap -> Fill(neut_rec.Theta()*TMath::RadToDeg(), neut_rec.P(), weight);
      nRecw_Thetaphi -> Fill(neut_rec.Theta()*1000., neut_rec.Phi()*TMath::RadToDeg(), weight);
    
      neut_rot_rec = rot*neut_rec; // rotate w.r.t to proton axis
      nRecw_rot_Thetaphi -> Fill(neut_rot_rec.Theta()*1000., neut_rot_rec.Phi()*TMath::RadToDeg(), weight);
      
      if(neut_rot_rec.Theta()*1000. < 4.0){ // acceptance of the zdc
        nRec_clus -> Fill(neutClus[i]);
	nRec_en -> Fill(neut_rot_rec.E(), weight);
	
   	if(neut_rot_rec.E()>10.0){ // neutron energy cut //change
	  z = true;
	  nRecw_rot_Thetap -> Fill(neut_rot_rec.Theta()*1000., neut_rot_rec.P(), weight);
	  
	  neutPosX = 35000 * sin(neut_rot_rec.Theta()) * cos(neut_rot_rec.Phi()); // neutron position at r = z = 35 m
      	  neutPosY = 35000 * sin(neut_rot_rec.Theta()) * sin(neut_rot_rec.Phi());
          nRecw_rot_PosXY -> Fill(neutPosX, neutPosY, weight);
	}
 
      }
 
    }// for over zdc neutrons
 
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    for(unsigned int i=0; i<neutEng.GetSize(); i++) { // Loop over zdc neutrons in HCal
 
      hcal_clus_size = neutEng_hcal.GetSize(); // ZDC HCal cluster size -> No. of clusters in ZDC
 
      if(hcal_clus_size > 0 && hcal_clus_size ==1 ){ // Selected the events correspond to one clusters
 
	neut_pos_hcal.SetXYZ(neutPosX_hcal[0], neutPosY_hcal[0], neutPosZ_hcal[0]);
        //cout<<"  "<<neut_pos_hcal.R()<<endl;       
	neut_rec_p_hcal = std::sqrt(pow(neutEng_hcal[0],2)- pow(neutMass,2)); // neutrons momentum
						
	neut_rec_hcal.SetPxPyPzE(neut_rec_p_hcal * sin(neut_pos_hcal.Theta()) * cos(neut_pos_hcal.Phi()), 
				 neut_rec_p_hcal * sin(neut_pos_hcal.Theta()) * sin(neut_pos_hcal.Phi()),   
				 neut_rec_p_hcal * cos(neut_pos_hcal.Theta()),
				 neutEng_hcal[0]);
	nRecw_Thetap_hcal -> Fill(neut_rec_hcal.Theta()*TMath::RadToDeg(), neut_rec_hcal.P(), weight);					    

	neut_rot_rec_hcal = rot*neut_rec_hcal; // rotate w.r.t to proton axis						
 
	if(neut_rot_rec_hcal.Theta()*1000. < 4.0 && neut_rot_rec_hcal.E()> 10.0){ //change
	  nRecw_rot_Thetap_hcal -> Fill(neut_rot_rec_hcal.Theta()*1000., neut_rot_rec_hcal.P(), weight);
	}
      }
 
    }// for over zdc neutrons in HCal
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Truth kinematic variables

    virtphoton_truth = (elec_beam - elec_mc);
    Q2_truth = -1*(virtphoton_truth.mag2());
    W_truth = ((virtphoton_truth + prot_beam).mag());
    y_truth = (prot_beam.Dot(virtphoton_truth))/(prot_beam.Dot(elec_beam)); // Energy Loss y 
    
    ttruth = (virtphoton_truth - pi_mc); 
    t_truth = -1*(ttruth.mag2()); // ttruth is the -t from the first loop
                                 
    talttruth = (prot_beam - neut_mc); 
    t_alttruth = -1*(talttruth.mag2()); // t_alttruth is the -t from the second loop
 
    /*virtphoton_nbftruth = (elec_beam - elec_nbfmc); // Turned it off as it didn't give expected results
      tnbftruth = (virtphoton_nbftruth - pi_nbfmc); 
      t_nbftruth = -1*(tnbftruth.mag2()); // ttruth is the -t from the first loop for nbf
      htw_t_1->Fill(t_nbftruth, weight);*/
    
    tnbfalttruth = (prot_nbfbeam - neut_nbfmc); 
    t_nbfalttruth = -1*(tnbfalttruth.mag2()); // t_alttruth is the -t from the second loop for nbf
    
    htw_Truth_t -> Fill(t_nbfalttruth, weight);
    // Efficiency plots
    if(neut_rot_mc.Theta()*1000. < 4.0){
      count2++; // truth neutrons
      if(Q2_truth > 5 && Q2_truth < 35){
        t_truth = t_nbfalttruth;
	Q2_t_DetEff_Uncut -> Fill(Q2_truth, t_truth, weight);
	htw_Truth_y -> Fill(y_truth, weight);
	h2Truthw_W_Q2 -> Fill(W_truth, Q2_truth, weight); 
	h2Truthw_t_Q2 -> Fill(t_truth, Q2_truth, weight);
      }
    }
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Reconstructed kinematic variables

    if (x == true && y == true && z == true ){ // if e', pi, and neutron are in coincidence
 
      virtphoton_rec = (elec_beam - elec_rec);
      Q2_rec = -1*(virtphoton_rec.mag2()); 
      W_rec = ((virtphoton_rec + prot_beam).mag()); 
      y_rec =  (prot_beam.Dot(virtphoton_rec))/(prot_beam.Dot(elec_beam)); // Energy Loss y

      if(Q2_rec > 5 && Q2_rec < 35){ // Q2 Cut 
	t_truth = t_nbfalttruth;
	// t-method plots
	trec = (virtphoton_rec - pi_rec); // First method to reconstruct -t // No change in values after rotation.
	t_rec = -1*(trec.mag2()); // t_rec is the -t from the first loop 
	htw_rec1 -> Fill(t_rec, t_truth, weight); 
	htwz_rec1 -> Fill(t_rec, t_truth, weight); // zoomed version
                                 
	taltrec = (prot_beam - neut_rec); // Second method to reconstruct -t // No change in values after rotation.
	t_altrec = -1*(taltrec.mag2()); // t_altrec is the -t from the second loop
	htw_rec2 -> Fill(t_altrec, t_truth, weight); 
	htwz_rec2 -> Fill(t_altrec, t_truth, weight); // zoomed version
 
	trecpT = (elec_rec +  pi_rec); // Third method to reconstruct -t // Values changed after rotation.
	trecpT_rot = rot*trecpT;
	t_recpT = trecpT_rot.Perp2();
	htw_rec3 -> Fill(t_recpT, t_truth, weight); 
	htwz_rec3 -> Fill(t_recpT, t_truth, weight); // zoomed version
 
	p_miss_rec = (elec_beam + prot_beam) - (elec_rec + pi_rec) ; // Defined missing momentum information -> Fourth method to reconstruct -t
	pMissRecw_Thetaphi -> Fill(p_miss_rec.Theta()*1000., p_miss_rec.Phi()*TMath::RadToDeg(), weight);
	
	p_miss_rot_rec = rot*p_miss_rec; // rotate p_miss_rec w.r.t to proton axis
	pMissRecw_rot_Thetaphi -> Fill(p_miss_rot_rec.Theta()*1000., p_miss_rot_rec.Phi()*TMath::RadToDeg(), weight);
	
        neut_corr.SetCoordinates( p_miss_rec.P() * sin(neut_rec.Theta()) * cos(neut_rec.Phi()), // Corrected neutron using missing momentum and neutron angles information 
				  p_miss_rec.P() * sin(neut_rec.Theta()) * sin(neut_rec.Phi()), 
				  p_miss_rec.P() * cos(neut_rec.Theta()),
				  neutMass );
 
	treccorr = (prot_beam - neut_corr); // No change in values after rotation.
	t_reccorr = -1*(treccorr.mag2());
	htw_rec4 -> Fill(t_reccorr, t_truth, weight); 
	htwz_rec4 -> Fill(t_reccorr, t_truth, weight); // zoomed version
 
	/*// Absolute difference -t plots
	  htw_t1 -> Fill(t_rec - t_truth);
	  htw_t2 -> Fill(t_altrec - t_truth);
	  htw_t3 -> Fill(t_recpT - t_truth);
	  htw_t4 -> Fill(t_reccorr - t_truth);*/
	
	// Neutron theta-phi plots 
	nTheta_Diff = p_miss_rot_rec.Theta() - neut_rot_rec.Theta();
	nPhi_Diff   = p_miss_rot_rec.Phi() - neut_rot_rec.Phi();
	n_ThetaDiff -> Fill(nTheta_Diff*TMath::RadToDeg(), weight);
	n_PhiDiff -> Fill(nPhi_Diff*TMath::RadToDeg(), weight);
	n_ThetaPhiDiff -> Fill(nTheta_Diff*TMath::RadToDeg(), nPhi_Diff*TMath::RadToDeg(), weight);
	n_TruthRecw_ThetaPhiDiff -> Fill((neut_rot_mc.Theta() - neut_rot_rec.Theta())*TMath::RadToDeg(), (neut_rot_mc.Phi() - neut_rot_rec.Phi())*TMath::RadToDeg(), weight); 
 
	// Resolution plots
	htw_res_e -> Fill((elec_rec.P() - elec_mc.P())/(elec_mc.P())*100, weight); 
	htw_res_pi -> Fill((pi_rec.P() - pi_mc.P())/(pi_mc.P())*100, weight);
	htw_res_n1 -> Fill((neut_rot_rec.P() - neut_rot_mc.P())/(neut_rot_mc.P())*100, weight);
	//htw_res_n4 -> Fill((neut_corr.P() - neut_mc.P())/(neut_mc.P())*100, weight);
	htw_res_n2 -> Fill((neut_rot_rec.Theta() - neut_rot_mc.Theta())/(neut_rot_mc.Theta())*100, weight);
	htw_res_n3 -> Fill((neut_rot_rec.Phi() - neut_rot_mc.Phi())/(neut_rot_mc.Phi())*100, weight);
	
	htw_res1 -> Fill((t_rec - t_truth)/(t_truth)*100, weight); 
	htw_res2 -> Fill((t_altrec - t_truth)/(t_truth)*100, weight);
	htw_res3 -> Fill((t_recpT - t_truth)/(t_truth)*100, weight);
	htw_res4 -> Fill((t_reccorr - t_truth)/(t_truth)*100, weight);
	htw_res5 -> Fill((Q2_rec - Q2_truth)/(Q2_truth)*100, weight);
	htw_res6 -> Fill((W_rec - W_truth)/(W_truth)*100, weight);
 	
	// y plots
	htw_Rec_y -> Fill(y_rec,weight);
	
	// Q2 plots
	h2Recw_W_Q2 -> Fill(W_rec, Q2_rec, weight); 
	h2Recw_t1_Q2 -> Fill(t_rec, Q2_rec, weight);
	h2Recw_t2_Q2 -> Fill(t_altrec, Q2_rec, weight);
	h2Recw_t3_Q2 -> Fill(t_recpT, Q2_rec, weight);
	h2Recw_t4_Q2 -> Fill(t_reccorr, Q2_rec, weight);
	
	// -t plots
	htw_t_1->Fill(t_nbfalttruth, weight);
        htw_t_2->Fill(t_alttruth, weight);
	htw_t_3->Fill(t_reccorr, weight);
	
	//w plot
	htw_Rec_w -> Fill(W_rec, weight);
      } //Q2 cut
      
      // Physics results
      for(Int_t B = 0; B < 8; B++){
      
	if(B == 0){ 
	  Q2_low = Q2BinVal[0];
	  Q2_high = Q2BinVal[7];
	}
	else {
	  Q2_low = Q2BinVal[B-1];
	  Q2_high = Q2BinVal[B];
	}
      
	if ( Q2_rec > Q2_low && Q2_rec < Q2_high){
	  if((t_reccorr < 0.4) && (nTheta_Diff*TMath::RadToDeg() > ThetaDiff_Cut_Low) && (nTheta_Diff*TMath::RadToDeg() < ThetaDiff_Cut_High) && (abs(nPhi_Diff*TMath::RadToDeg())) < PhiDiff_Cut /*&& W_rec < 41.0*/){
            htw_t_cut_result[B] -> Fill(t_reccorr, weight);
	    htw_Q2_cut_result[B] -> Fill(Q2_rec, weight);
	    htw_W_cut_result[B] -> Fill(W_rec, weight);
            if(B==0) { 
	      t_truth = t_nbfalttruth; 
            
	      //effeciency plot
	      Q2_t_DetEff_Cut -> Fill(Q2_truth, t_truth, weight);
            
	      // Absolute difference -t plots
	      htw_t1 -> Fill(t_rec - t_truth, weight);
	      htw_t2 -> Fill(t_altrec - t_truth, weight);
	      htw_t3 -> Fill(t_recpT - t_truth, weight);
	      htw_t4 -> Fill(t_reccorr - t_truth, weight);
	    
	      //neutron momemtum resolution
	      htw_res_n4 -> Fill((neut_corr.P() - neut_mc.P())/(neut_mc.P())*100, weight);
	  
	    } // Efficiency plots
	  }// if statement over all cuts
	} // if statement over Q2
      } // for loop over B
   
    } // if over x,y, and z
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  
  } // End of event loop (while loop)
  
  // Efficiency plots
  Q2_t_DetEff -> Divide(Q2_t_DetEff_Cut, Q2_t_DetEff_Uncut, 1, 1, "b");
  eEff_Eta -> Divide(eRecw_Eta_Cut, eTruthw_Eta_Uncut, 1, 1, "b");
  piEff_Eta -> Divide(piRecw_Eta_Cut, piTruthw_Eta_Uncut, 1, 1, "b");
  eEff_P -> Divide(eRecw_P_Cut, eTruthw_P_Uncut, 1, 1, "b");
  piEff_P -> Divide(piRecw_P_Cut, piTruthw_P_Uncut, 1, 1, "b");
  
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // gStyle->SetOptStat(0);
  // gStyle->SetOptTitle(0);
  gStyle->SetPadRightMargin(0.125); // left space on right side
  gStyle->SetPadLeftMargin(0.12); // right space on right side
  gStyle->SetStatX(0.895); // move the stat bax on left or right side
  gStyle->SetStatY(0.90); // move the stat bax on up or down side
  gStyle->SetPalette(55);
  gStyle->SetLineStyleString(2,"[12 12]");
  gStyle->SetHistLineWidth(2);
  
  TCanvas *c1a = new TCanvas("c1a"); //truth nbf information     
  c1a->SetLogz(); 
  enbfTruthw_Thetap->Scale(1.0/nFiles); 
  enbfTruthw_Thetap->Draw("colz");
  
  TCanvas *c2a = new TCanvas("c2a");
  c2a->SetLogz();
  pinbfTruthw_Thetap->Scale(1.0/nFiles);
  pinbfTruthw_Thetap->Draw("colz");
  
  TCanvas *c3_a = new TCanvas("c3_a"); 
  c3_a->SetLogz();
  nnbfTruthw_Thetap->Scale(1.0/nFiles);
  nnbfTruthw_Thetap->Draw("colz");  
  
  TCanvas *c1 = new TCanvas("c1"); //truth information     
  c1->SetLogz(); 
  eTruthw_Thetap->Scale(1.0/nFiles); 
  eTruthw_Thetap->Draw("colz");
  
  TCanvas *c2 = new TCanvas("c2");
  c2->SetLogz();
  piTruthw_Thetap->Scale(1.0/nFiles);
  piTruthw_Thetap->Draw("colz");
  
  TCanvas *c3 = new TCanvas("c3");
  c3->SetLogz();
  nTruthw_Thetaphi->Scale(1.0/nFiles);
  nTruthw_Thetaphi->Draw("colz");
  
  TCanvas *c3a = new TCanvas("c3a");
  c3a->SetLogz();
  nTruthw_rot_Thetaphi->Scale(1.0/nFiles);
  nTruthw_rot_Thetaphi->Draw("colz");
  
  TCanvas *c3b = new TCanvas("c3b"); 
  c3b->SetLogz();
  nTruthw_Thetap->Scale(1.0/nFiles);
  nTruthw_Thetap->Draw("colz");  
  
  TCanvas *c3c = new TCanvas("c3c"); 
  c3c->SetLogz();
  nTruthw_rot_Thetap->Scale(1.0/nFiles);
  nTruthw_rot_Thetap->Draw("colz");  
  
  TCanvas *c4 = new TCanvas("c4"); //reconstructed information
  c4->SetLogz();
  eRecw_Thetap->Scale(1.0/nFiles);
  eRecw_Thetap->Draw("colz");
  
  TCanvas *c4a = new TCanvas("c4a"); 
  c4a->SetLogz();
  eRecw_Thetaphi->Scale(1.0/nFiles);
  eRecw_Thetaphi->Draw("colz");
  
  TCanvas *c5 = new TCanvas("c5");
  c5->SetLogz();
  piRecw_Thetap->Scale(1.0/nFiles);
  piRecw_Thetap->Draw("colz");
  
  TCanvas *c5_a = new TCanvas("c5_a");
  c5_a->SetLogz();
  piRecw_Thetaphi->Scale(1.0/nFiles);
  piRecw_Thetaphi->Draw("colz");
  
  TCanvas *c5a = new TCanvas("c5a"); // rec neutrons
  c5a->SetLogz();
  nRecw_Thetap_hcal->Scale(1.0/nFiles);
  nRecw_Thetap_hcal->Draw("colz");
  
  TCanvas *c5b = new TCanvas("c5b");
  c5b->SetLogz();
  nRecw_rot_Thetap_hcal->Scale(1.0/nFiles);
  nRecw_rot_Thetap_hcal->Draw("colz");
  
  TCanvas *c5c = new TCanvas("c5c"); 
  c5c->SetLogz();
  nRecw_Thetaphi->Scale(1.0/nFiles);
  nRecw_Thetaphi->Draw("colz");
  
  TCanvas *c5d = new TCanvas("c5d");
  c5d->SetLogz();
  nRecw_rot_Thetaphi->Scale(1.0/nFiles);
  nRecw_rot_Thetaphi->Draw("colz");
  
  TCanvas *c6a = new TCanvas("c6a");
  nRec_en->Scale(1.0/nFiles);
  nRec_en->Draw("HIST");
  
  TCanvas *c6b = new TCanvas("c6b");
  nRec_clus->Draw();
  
  TCanvas *c7 = new TCanvas("c7");
  c7->SetLogz();
  nRecw_Thetap->Scale(1.0/nFiles);
  nRecw_Thetap->Draw("colz");
  
  TCanvas *c7a = new TCanvas("c7a");
  c7a->SetLogz();
  nRecw_rot_Thetap->Scale(1.0/nFiles);
  nRecw_rot_Thetap->Draw("colz");
  
  TCanvas *c7b = new TCanvas("c7b");
  c7b->SetLogz();
  nRecw_rot_PosXY->Scale(1.0/nFiles);
  nRecw_rot_PosXY->Draw("colz");
  
  TEllipse *ellipse = new TEllipse(0.0, 0.0, 140);
  ellipse->SetFillStyle(0); // No fill
  ellipse->SetLineColor(kBlack);
  ellipse->SetLineWidth(3);
  ellipse->Draw("SAMEP");
  
  TCanvas *c8 = new TCanvas("c8"); // -t reconstruction plots
  c8->SetLogz();
  htw_rec1->Scale(1.0/nFiles);
  htw_rec1->Draw("colz");
  
  TCanvas *c8a = new TCanvas("c8a");
  c8a->SetLogz();
  htwz_rec1->Scale(1.0/nFiles);
  htwz_rec1->Draw("colz");
  
  TCanvas *c9 = new TCanvas("c9");
  c9->SetLogz();
  htw_rec2->Scale(1.0/nFiles);
  htw_rec2->Draw("colz");
  
  TCanvas *c9a = new TCanvas("c9a");
  c9a->SetLogz();
  htwz_rec2->Scale(1.0/nFiles);
  htwz_rec2->Draw("colz");
  
  TCanvas *c10 = new TCanvas("c10");
  c10->SetLogz();
  htw_rec3->Scale(1.0/nFiles);
  htw_rec3->Draw("colz");
  
  TCanvas *c10a = new TCanvas("c10a");
  c10a->SetLogz();
  htwz_rec3->Scale(1.0/nFiles);
  htwz_rec3->Draw("colz");
  
  TCanvas *c11 = new TCanvas("c11");
  c11->SetLogz();
  htw_rec4->Scale(1.0/nFiles);
  htw_rec4->Draw("colz");
  
  TCanvas *c11a = new TCanvas("c11a");
  c11a->SetLogz();
  htwz_rec4->Scale(1.0/nFiles);
  htwz_rec4->Draw("colz");
  
  TCanvas *c12 = new TCanvas("c12"); // Resolution plots
  htw_res_e->Scale(1.0/nFiles);
  htw_res_e->Draw("HIST");
  
  TCanvas *c13 = new TCanvas("c13");
  htw_res_pi->Scale(1.0/nFiles);
  htw_res_pi->Draw("HIST");
  
  TCanvas *c14a = new TCanvas("c14a");
  htw_res_n1->Scale(1.0/nFiles);
  htw_res_n1->Draw("HIST");
  
  TCanvas *c14b = new TCanvas("c14b");
  htw_res_n2->Scale(1.0/nFiles);
  htw_res_n2->Draw("HIST");
  
  TCanvas *c14c = new TCanvas("c14c");
  htw_res_n3->Scale(1.0/nFiles);
  htw_res_n3->Draw("HIST");
  
  TCanvas *c14d = new TCanvas("c14d");
  htw_res_n4->Scale(1.0/nFiles);
  htw_res_n4->Draw("HIST");
  
  TCanvas *c15a = new TCanvas("c15a"); //t-resoutions
  htw_res1->Scale(1.0/nFiles);
  htw_res1->Draw("HIST");
  
  TCanvas *c15b = new TCanvas("c15b");
  htw_res2->Scale(1.0/nFiles);
  htw_res2->Draw("HIST");
  
  TCanvas *c15c = new TCanvas("c15c");
  htw_res3->Scale(1.0/nFiles);
  htw_res3->Draw("HIST");
  
  TCanvas *c15d = new TCanvas("c15d");
  htw_res4->Scale(1.0/nFiles);
  htw_res4->Draw("HIST");
  
  TCanvas *c15e = new TCanvas("c15e");
  htw_res5->Scale(1.0/nFiles);
  htw_res5->Draw("HIST");
  
  TCanvas *c15f = new TCanvas("c15f");
  htw_res6->Scale(1.0/nFiles);
  htw_res6->Draw("HIST");
  
  TCanvas *c16a = new TCanvas("c16a"); // Neutron theta-phi plots
  n_ThetaDiff->Scale(1.0/nFiles);
  n_ThetaDiff->Draw("HIST");
  
  TCanvas *c16b = new TCanvas("c16b");
  n_PhiDiff->Scale(1.0/nFiles);
  n_PhiDiff->Draw("HIST");
  
  TCanvas *c16c = new TCanvas("c16c");
  c16c->SetLogz();
  n_ThetaPhiDiff->Scale(1.0/nFiles);
  n_ThetaPhiDiff->Draw("colz");
  
  TCanvas *c16d = new TCanvas("c16d");
  c16d->SetLogz();
  pMissRecw_Thetaphi->Scale(1.0/nFiles);
  pMissRecw_Thetaphi->Draw("colz");
  
  TCanvas *c16e = new TCanvas("c16e");
  c16e->SetLogz();
  pMissRecw_rot_Thetaphi->Scale(1.0/nFiles);
  pMissRecw_rot_Thetaphi->Draw("colz");
  
  TCanvas *c16f = new TCanvas("c16f");
  c16f->SetLogz();
  n_TruthRecw_ThetaPhiDiff->Scale(1.0/nFiles);
  n_TruthRecw_ThetaPhiDiff->Draw("colz");
  
  TCanvas *c17 = new TCanvas("c17"); // Absolute difference -t plots
  htw_t1->Scale(1.0/nFiles), htw_t2->Scale(1.0/nFiles), htw_t3->Scale(1.0/nFiles), htw_t4->Scale(1.0/nFiles);
  htw_t4->Draw("HIST");
  htw_t3->Draw("HIST SAME");
  htw_t2->Draw("HIST SAME");
  htw_t1->Draw("HIST SAME");
  
  TLegend *leg17 = new TLegend (0.8,0.4,0.6,0.7); //2 sapce between them,3 more on left,4 on downside 
  leg17->SetBorderSize(0);leg17->SetFillStyle(0); 
  leg17->AddEntry(htw_t1,"t_{rec} - t_{alt_truth}","l");
  leg17->AddEntry(htw_t2,"t_{alt_rec} - t_{alt_truth}","l");
  leg17->AddEntry(htw_t3,"t_{recpT} - t_{alt_truth}","l");
  leg17->AddEntry(htw_t4,"t_{rec_corr} - t_{alt_truth}","l");
  leg17->Draw();
  
  TCanvas *c18 = new TCanvas("c18"); // Efficiency plots
  Q2_t_DetEff-> GetZaxis()->SetRangeUser(0.0,1.0);
  Q2_t_DetEff->Draw("colz");
  
  TCanvas *c18a = new TCanvas("c18a"); 
  Q2_t_DetEff_Cut->Scale(1.0/nFiles);
  Q2_t_DetEff_Cut->Draw("colz");
  
  TCanvas *c18b = new TCanvas("c18b"); 
  Q2_t_DetEff_Uncut->Scale(1.0/nFiles);
  Q2_t_DetEff_Uncut->Draw("colz"); 
 
  TCanvas *c19 = new TCanvas("c19"); // elec eta eff.
  eEff_Eta->Draw("HIST");
  
  TCanvas *c19a = new TCanvas("c19a"); 
  eTruthw_Eta_Uncut->Scale(1.0/nFiles);
  eTruthw_Eta_Uncut->Draw("HIST");
  
  TCanvas *c19b = new TCanvas("c19b"); 
  eRecw_Eta_Cut->Scale(1.0/nFiles);
  eRecw_Eta_Cut->Draw("HIST");
  
  TCanvas *c20 = new TCanvas("c20");  // elec mom eff.
  eEff_P->Draw("HIST");
  
  TCanvas *c20a = new TCanvas("c20a"); 
  eTruthw_P_Uncut->Scale(1.0/nFiles);
  eTruthw_P_Uncut->Draw("HIST");
  
  TCanvas *c20b = new TCanvas("c20b"); 
  eRecw_P_Cut->Scale(1.0/nFiles);
  eRecw_P_Cut->Draw("HIST");
  
  TCanvas *c21 = new TCanvas("c21"); // pi eta eff.
  piEff_Eta->Draw("HIST");
  
  TCanvas *c21a = new TCanvas("c21a"); 
  piTruthw_Eta_Uncut->Scale(1.0/nFiles);
  piTruthw_Eta_Uncut->Draw("HIST");
  
  TCanvas *c21b = new TCanvas("c21b"); 
  piRecw_Eta_Cut->Scale(1.0/nFiles);
  piRecw_Eta_Cut->Draw("HIST");
  
  TCanvas *c22 = new TCanvas("c22"); // pi mom eff.
  piEff_P->Draw("HIST");
  
  TCanvas *c22a = new TCanvas("c22a"); 
  piTruthw_P_Uncut->Scale(1.0/nFiles);
  piTruthw_P_Uncut->Draw("HIST");
  
  TCanvas *c22b = new TCanvas("c22b"); 
  piRecw_P_Cut->Scale(1.0/nFiles);
  piRecw_P_Cut->Draw("HIST");
  
  TCanvas *c23a = new TCanvas("c23a"); // y plot
  htw_Truth_y->Scale(1.0/nFiles);
  htw_Truth_y->Draw("HIST");
  
  TCanvas *c23b = new TCanvas("c23b"); 
  htw_Rec_y->Scale(1.0/nFiles);
  htw_Rec_y->Draw("HIST");
  
  TCanvas *c23c = new TCanvas("c23c"); // -t plot
  htw_Truth_t->Scale(1.0/nFiles);
  htw_Truth_t->Draw("HIST");
  
  TCanvas *c24[8]; // tplots
  for(int C = 0; C < 8; C++) {
    c24[C] = new TCanvas(Form("c24%d", C));
    htw_t_cut_result[C]->Scale(1.0/nFiles);
    htw_t_cut_result[C]->Draw();
  }
  TCanvas *c25[8]; // Q2plots
  for(int C = 0; C < 8; C++) {
    c25[C] = new TCanvas(Form("c25%d", C));
    htw_Q2_cut_result[C]->Scale(1.0/nFiles);
    htw_Q2_cut_result[C]->Draw();
  }

  TCanvas *c26[8]; // Q2plots
  for(int C = 0; C < 8; C++) {
    c26[C] = new TCanvas(Form("c26%d", C));
    htw_W_cut_result[C]->Scale(1.0/nFiles);
    htw_W_cut_result[C]->Draw();
  }
  
  TCanvas *c27a = new TCanvas("c27a"); 
  c27a->SetLogz();
  h2Truthw_W_Q2->Scale(1.0/nFiles);
  h2Truthw_W_Q2->Draw("colz");
  
  TCanvas *c27b = new TCanvas("c27b"); 
  c27b->SetLogz();
  h2Recw_W_Q2->Scale(1.0/nFiles);
  h2Recw_W_Q2->Draw("colz");
  
  TCanvas *c28a = new TCanvas("c28a"); 
  c28a->SetLogz();
  h2Truthw_t_Q2->Scale(1.0/nFiles);
  h2Truthw_t_Q2->Draw("colz");
  
  TCanvas *c28b = new TCanvas("c28b"); 
  c28b->SetLogz();
  h2Recw_t1_Q2->Scale(1.0/nFiles);
  h2Recw_t1_Q2->Draw("colz");
  
  TCanvas *c28c = new TCanvas("c28c");
  c28c->SetLogz(); 
  h2Recw_t2_Q2->Scale(1.0/nFiles);
  h2Recw_t2_Q2->Draw("colz");
  
  TCanvas *c28d = new TCanvas("c28d");
  c28d->SetLogz();
  h2Recw_t3_Q2->Scale(1.0/nFiles);
  h2Recw_t3_Q2->Draw("colz");
  
  TCanvas *c28e = new TCanvas("c28e"); 
  c28e->SetLogz();
  h2Recw_t4_Q2->Scale(1.0/nFiles);
  h2Recw_t4_Q2->Draw("colz");
  
  TCanvas *c29 = new TCanvas("c29");
  htw_t_1->Scale(1.0/nFiles), htw_t_2->Scale(1.0/nFiles),  htw_t_3->Scale(1.0/nFiles);
  htw_t_2->Draw("HIST");
  htw_t_1->Draw("HIST SAME");
  htw_t_3->Draw("HIST SAME");
  TLegend *leg29 = new TLegend (0.8,0.45,0.5,0.7); //1 more on left, 2 sapce between them,3 more on rightor size, 4 on downside 
  leg29->SetBorderSize(0);leg29->SetFillStyle(0); 
  leg29->AddEntry(htw_t_1,"t_{alt_truth} (no beam effects)","l");
  leg29->AddEntry(htw_t_2,"t_{alt_truth} (with beam effects)","l");
  leg29->AddEntry(htw_t_3,"t_{rec_corr}","l");
  leg29->Draw();
  
  TCanvas *c30a = new TCanvas("c30a"); 
  c30a->SetLogy();
  htw_Rec_w->Scale(1.0/nFiles);
  htw_Rec_w->Draw("HIST");
  
  c1a->Print("sidis_reco_5on41.pdf[");
  c1a->Print("sidis_reco_5on41.pdf");
  c2a->Print("sidis_reco_5on41.pdf");
  c3_a->Print("sidis_reco_5on41.pdf");
  c1->Print("sidis_reco_5on41.pdf");
  c2->Print("sidis_reco_5on41.pdf");
  c3b->Print("sidis_reco_5on41.pdf");
  c3->Print("sidis_reco_5on41.pdf");
  c3a->Print("sidis_reco_5on41.pdf");
  c3c->Print("sidis_reco_5on41.pdf");
  c4->Print("sidis_reco_5on41.pdf");
  c4a->Print("sidis_reco_5on41.pdf");
  c5->Print("sidis_reco_5on41.pdf");
  c5_a->Print("sidis_reco_5on41.pdf");
  c5a->Print("sidis_reco_5on41.pdf");
  c5b->Print("sidis_reco_5on41.pdf");
  c5c->Print("sidis_reco_5on41.pdf");
  c5d->Print("sidis_reco_5on41.pdf");
  c6b->Print("sidis_reco_5on41.pdf");
  c6a->Print("sidis_reco_5on41.pdf");
  c7->Print("sidis_reco_5on41.pdf");
  c7a->Print("sidis_reco_5on41.pdf");
  c7b->Print("sidis_reco_5on41.pdf");
  c8->Print("sidis_reco_5on41.pdf");
  c8a->Print("sidis_reco_5on41.pdf");
  c9->Print("sidis_reco_5on41.pdf");
  c9a->Print("sidis_reco_5on41.pdf");
  c10->Print("sidis_reco_5on41.pdf");
  c10a->Print("sidis_reco_5on41.pdf");
  c11->Print("sidis_reco_5on41.pdf");
  c11a->Print("sidis_reco_5on41.pdf");
  c12->Print("sidis_reco_5on41.pdf");
  c13->Print("sidis_reco_5on41.pdf");
  c14a->Print("sidis_reco_5on41.pdf");
  c14b->Print("sidis_reco_5on41.pdf");
  c14c->Print("sidis_reco_5on41.pdf");
  c14d->Print("sidis_reco_5on41.pdf");
  c15a->Print("sidis_reco_5on41.pdf");
  c15b->Print("sidis_reco_5on41.pdf");
  c15c->Print("sidis_reco_5on41.pdf");
  c15d->Print("sidis_reco_5on41.pdf");
  c15e->Print("sidis_reco_5on41.pdf");
  c15f->Print("sidis_reco_5on41.pdf");
  c16f->Print("sidis_reco_5on41.pdf");
  c16d->Print("sidis_reco_5on41.pdf");
  c16e->Print("sidis_reco_5on41.pdf");
  c16a->Print("sidis_reco_5on41.pdf");
  c16b->Print("sidis_reco_5on41.pdf");
  c16c->Print("sidis_reco_5on41.pdf");
  c17->Print("sidis_reco_5on41.pdf");
  c18b->Print("sidis_reco_5on41.pdf");
  c18a->Print("sidis_reco_5on41.pdf");
  c18->Print("sidis_reco_5on41.pdf");
  c19a->Print("sidis_reco_5on41.pdf");
  c19b->Print("sidis_reco_5on41.pdf");
  c19->Print("sidis_reco_5on41.pdf");
  c20a->Print("sidis_reco_5on41.pdf");
  c20b->Print("sidis_reco_5on41.pdf");
  c20->Print("sidis_reco_5on41.pdf");
  c21a->Print("sidis_reco_5on41.pdf");
  c21b->Print("sidis_reco_5on41.pdf");
  c21->Print("sidis_reco_5on41.pdf");
  c22a->Print("sidis_reco_5on41.pdf");
  c22b->Print("sidis_reco_5on41.pdf");
  c22->Print("sidis_reco_5on41.pdf");
  c23a->Print("sidis_reco_5on41.pdf");
  c23b->Print("sidis_reco_5on41.pdf");
  c23c->Print("sidis_reco_5on41.pdf");
  for(int D = 0; D <8; D++) { 
    c24[D]->Print("sidis_reco_5on41.pdf"); }
  for(int D = 0; D <8; D++) {
    c25[D]->Print("sidis_reco_5on41.pdf");};
  for(int D = 0; D <8; D++) {
    c26[D]->Print("sidis_reco_5on41.pdf");};
  c27a->Print("sidis_reco_5on41.pdf");
  c27b->Print("sidis_reco_5on41.pdf");
  c28a->Print("sidis_reco_5on41.pdf");
  c28b->Print("sidis_reco_5on41.pdf");
  c28c->Print("sidis_reco_5on41.pdf");
  c28d->Print("sidis_reco_5on41.pdf");
  c28e->Print("sidis_reco_5on41.pdf");
  c29->Print("sidis_reco_5on41.pdf");
  c30a->Print("sidis_reco_5on41.pdf");
  c1a->Print("sidis_reco_5on41.pdf]");
  
  htw_Rec_w->SetOption("HIST");
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Saving the physics result parameters in the .csv file
  ofstream myfile;
  myfile.open("parameters_5on41.csv", std::ios::trunc);
  TString header = "nominal mean Q^2,mean Q^2,mean Q^2 error,mean W,mean W error,-t (bin center),Rate (Hz), Rate (Hz) error";
  myfile << header << "\n\n";

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == 0) {
        myfile << (Q2BinVal[i] + Q2BinVal[i+1])/2 << ",";
        myfile << htw_Q2_cut_result[i+1]->GetMean() << ",";
        myfile << htw_Q2_cut_result[i+1]->GetMeanError() << ",";
        myfile << htw_W_cut_result[i+1]->GetMean() << ",";
        myfile << htw_W_cut_result[i+1]->GetMeanError() << ",";
      } else {
        myfile << ",,,,,";
      }
      myfile << htw_t_cut_result[i+1]->GetXaxis()->GetBinCenter(htw_t_cut_result[i+1]->FindFixBin(0.02 + j * 0.04)) << ",";
      myfile << htw_t_cut_result[i+1]->GetBinContent(htw_t_cut_result[i+1]->FindFixBin(0.02 + j * 0.04)) << ",";
      myfile << htw_t_cut_result[i+1]->GetBinError(htw_t_cut_result[i+1]->FindFixBin(0.02 + j * 0.04)) << "\n";
    }
    myfile << "\n";
  }
  myfile<<"truth_neutron ( #theta* < 4.0 mRad ) = "<<count2<<",";
  myfile<<"nFiles = "<<nFiles;
  myfile.close();
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  ofile->Write(); // Write histograms to file
  ofile->Close(); // Close output file
    
}
