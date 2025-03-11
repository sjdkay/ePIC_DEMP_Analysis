void test_b0_10on100(){

  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Enable this block when you process xrdfs files from collabration
  // Set up input file chain
  /*TChain *mychain = new TChain("events");

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
    for (unsigned int i = 10; i < 19; i++) { //19
    for (unsigned int j = 0; j < 1921; j++) { //1921
    // Construct the file path
    if (j < 10) {
    filepath = Form("root://dtn-eic.jlab.org//work/eic2/EPIC/RECO/24.09.0/epic_craterlake/EXCLUSIVE/DEMP/DEMPgen-1.2.0/10x100/pi+/DEMPgen-1.2.0_10x100_pi+_%i.000%i.eicrecon.tree.edm4eic.root", i, j);
    } else if (j < 100) {
    filepath = Form("root://dtn-eic.jlab.org//work/eic2/EPIC/RECO/24.09.0/epic_craterlake/EXCLUSIVE/DEMP/DEMPgen-1.2.0/10x100/pi+/DEMPgen-1.2.0_10x100_pi+_%i.00%i.eicrecon.tree.edm4eic.root", i, j);
    } else if (j < 1000) {
    filepath = Form("root://dtn-eic.jlab.org//work/eic2/EPIC/RECO/24.09.0/epic_craterlake/EXCLUSIVE/DEMP/DEMPgen-1.2.0/10x100/pi+/DEMPgen-1.2.0_10x100_pi+_%i.0%i.eicrecon.tree.edm4eic.root", i, j);
    } else {
    filepath = Form("root://dtn-eic.jlab.org//work/eic2/EPIC/RECO/24.09.0/epic_craterlake/EXCLUSIVE/DEMP/DEMPgen-1.2.0/10x100/pi+/DEMPgen-1.2.0_10x100_pi+_%i.%i.eicrecon.tree.edm4eic.root", i, j);
    }
    // Try opening the file to check if it's valid and then add to the TChain
    TFile *file = TFile::Open(filepath);
    if (file && !file->IsZombie()) {
    TTree *tree = (TTree*)file->Get("events");

    // Ensure the tree is valid before getting entries
    if (tree) {
    nEntries = tree->GetEntries();
    // std::cout << "nEntries = " << nEntries << std::endl;

    if (nEntries == 1259) {
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
    unsigned int count2 = 0; // counter on neutrons within 4 mrad*/
  
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Enable this block when you process the files from Love Preet
  TChain *mychain = new TChain("events");
  unsigned int count1 = 0; // Counter for the number of files successfully added
  unsigned int count2 = 0; // Counter for neutrons within 4 mrad

  unsigned int nFiles1 = 4; // Number of iterations for the first loop //4
  unsigned int nFiles2 = 484; // Number of iterations for the second loop //484
  unsigned int nFiles; // Total number of files to process

  for (unsigned int i = 0; i < nFiles1; i++) {
    /*if(i == 0) {nFiles2 = 40;}
      else if(i == 1) {nFiles2 = 80;}
      else if(i == 2) {nFiles2 = 91;}*/
  
    for (unsigned int j = 0; j < nFiles2; j++) {
      count1++;

      // Construct file name
     // TString fileName = Form("Test_10on100_pi+_Reco_AllEvents_%i_%i.root", 1 + i, 5000 + j * 5000);
        
      //Files from Jlab server
      //TString fileName = Form("/volatile/eic/preet/reco_simulation_output/Nov2024_Files/pi+/10on100/Test_10on100_pi+_Reco_AllEvents_%i_%i.root", 1 + i, 5000 + j * 5000);
      TString fileName = Form("/volatile/eic/preet/reco_simulation_output/Dec2024_Files/pi+/10on100/Test_10on100_pi+_Reco_AllEvents_%i_%i.root", 1 + i, 5000 + j * 5000);
      
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
  nFiles = count1;

  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Set output file for the histograms
  TFile *ofile = TFile::Open("pion_hist_test_10on100.root","RECREATE");
   
  // Initialize reader
  TTreeReader tree_reader(mychain);

  // Get weight information
  TTreeReaderArray<std::vector<std::string>> weight_map(tree_reader, "GPStringValues");
  
  // Get Before Afterburned information
  TTreeReaderArray<int>    nbfpartGenStat(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.generatorStatus"); //nbf stands for no beam effects
  TTreeReaderArray<float>  nbfpartMomX(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.x");
  TTreeReaderArray<float>  nbfpartMomY(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.y");
  TTreeReaderArray<float>  nbfpartMomZ(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.momentum.z");
  TTreeReaderArray<int>    nbfpartPdg(tree_reader, "MCParticlesHeadOnFrameNoBeamFX.PDG");
  TTreeReaderArray<double> nbfpartMass(tree_reader,"MCParticlesHeadOnFrameNoBeamFX.mass");
  
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
  
  // B0ECalClusters
  TTreeReaderArray<float> neutPosX_b0(tree_reader, "B0ECalClusters.position.x");
  TTreeReaderArray<float> neutPosY_b0(tree_reader, "B0ECalClusters.position.y");
  TTreeReaderArray<float> neutPosZ_b0(tree_reader, "B0ECalClusters.position.z");
  TTreeReaderArray<float> neutEng_b0(tree_reader, "B0ECalClusters.energy");
 
  //----------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   
  // Define Histograms for B0 neutrons
  
  TH1* nb0_clus = new TH1D("nb0_clus", "B0 n all clusters", 100, 0.0, 10.0);
  nb0_clus->SetLineWidth(2);
  
  TH2* nb0w_PosXY  = new TH2D("nb0w_PosXY","n B0 X vs Y for all clusters; x (mm); y (mm); Rate/bin (Hz)",100,-350,0,100,-200,200);
  TH2* nb0w_rot_PosXY  = new TH2D("nb0w_rot_PosXY","n B0 X* vs Y* around proton axis at Z = 6.8 m for all clusters; x (mm); y (mm); Rate/bin (Hz)",100,-200,200,100,-200,200);
  
  TH2* nb0_ClusE  = new TH2D("nb0_ClusE","b0 n all clusters vs Energy; No. of Clusters; E (GeV)",100,0.0,10.0,100,0.0,100.0);
  TH2* nb0w_rot_Thetaphi  = new TH2D("nb0w_rot_Thetaphi","n B0 #theta* vs #phi* for all clusters; #theta* (mRad); #phi* (deg); Rate/bin (Hz)",100,0.0,25.0,100,-200,200); 
  
  // 1 cluster
  TH2* nb0w_PosXY_clus1  = new TH2D("nb0w_PosXY_clus1","n B0 X vs Y for 1 cluster; x (mm); y (mm); Rate/bin (Hz)",100,-350,0,100,-200,200);
  
  // 2 clusters
  TH2* nb0E_Clus2  = new TH2D("nb0E_Clus2","b0 n cluster 2 E_H vs E_L; E_H (GeV); E_L (GeV)",100,0.0,60,100,0.0,3.0);
  TH2* nb0w_PosXY_clus2  = new TH2D("nb0w_PosXY_clus2","n B0 X vs Y for 2 cluster; x (mm); y (mm); Rate/bin (Hz)",100,-350,0,100,-200,200);
  
  // 3 clusters
  TH1* nb0EH_clus3 = new TH1D("nb0EH_clus3", "B0 n 3 Cluster EH", 100, 0.0, 70.0);
  TH1* nb0EM_clus3 = new TH1D("nb0EM_clus3", "B0 n 3 Cluster EM", 100, 0.0, 7.0);
  TH1* nb0EL_clus3 = new TH1D("nb0EL_clus3", "B0 n 3 Cluster EL", 100, 0.0, 5.0);
  TH2* nb0w_PosXY_clus3  = new TH2D("nb0w_PosXY_clus3","n B0 X vs Y for 3 cluster; x (mm); y (mm); Rate/bin (Hz)",100,-350,0,100,-200,200);
  
  // 4 clusters
  TH1* nb0EH_clus4 = new TH1D("nb0EH_clus4", "B0 n 4 Cluster EH", 100, 0.0, 60.0);
  TH1* nb0EM1_clus4 = new TH1D("nb0EM1_clus4", "B0 n 4 Cluster EM1", 100, 0.0, 5.0);
  TH1* nb0EM2_clus4 = new TH1D("nb0EM2_clus4", "B0 n 4 Cluster EM2", 100, 0.0, 5.0);
  TH1* nb0EL_clus4 = new TH1D("nb0EL_clus4", "B0 n 4 Cluster EL", 100, 0.0, 5.0);
  TH2* nb0w_PosXY_clus4  = new TH2D("nb0w_PosXY_clus4","n B0 X vs Y for 4 cluster; x (mm); y (mm); Rate/bin (Hz)",100,-350,0,100,-200,200);
  
  // 5 clusters
  TH1* nb0EH_clus5 = new TH1D("nb0EH_clus4", "B0 n 5 Cluster EH", 100, 0.0, 40.0);
  TH1* nb0EM1_clus5 = new TH1D("nb0EM1_clus4", "B0 n 5 Cluster EM1", 100, 0.0, 5.0);
  TH1* nb0EM2_clus5 = new TH1D("nb0EM2_clus4", "B0 n 5 Cluster EM2", 100, 0.0, 5.0);
  TH1* nb0EM3_clus5 = new TH1D("nb0EM3_clus4", "B0 n 5 Cluster EM3", 100, 0.0, 5.0);
  TH1* nb0EL_clus5 = new TH1D("nb0EL_clus4", "B0 n 5 Cluster EL", 100, 0.0, 5.0);
  TH2* nb0w_PosXY_clus5  = new TH2D("nb0w_PosXY_clus5","n B0 X vs Y for 5 cluster; x (mm); y (mm); Rate/bin (Hz)",100,-350,0,100,-200,200);
  
  // 6 clusters
  TH1* nb0EH_clus6 = new TH1D("nb0EH_clus6", "B0 n 6 Cluster EH", 100, 0.0, 30.0);
  TH1* nb0EM1_clus6 = new TH1D("nb0EM1_clus6", "B0 n 6 Cluster EM1", 100, 0.0, 5.0);
  TH1* nb0EM2_clus6 = new TH1D("nb0EM2_clus6", "B0 n 6 Cluster EM2", 100, 0.0, 5.0);
  TH1* nb0EM3_clus6 = new TH1D("nb0EM3_clus6", "B0 n 6 Cluster EM3", 100, 0.0, 5.0);
  TH1* nb0EM4_clus6 = new TH1D("nb0EM4_clus6", "B0 n 6 Cluster EM4", 100, 0.0, 5.0);
  TH1* nb0EL_clus6 = new TH1D("nb0EL_clus6", "B0 n 6 Cluster EL", 100, 0.0, 5.0);
  TH2* nb0w_PosXY_clus6  = new TH2D("nb0w_PosXY_clus6","n B0 X vs Y for 6 cluster; x (mm); y (mm); Rate/bin (Hz)",100,-350,0,100,-200,200);
  
  // All clusters
  TH2* nb0w_rot_Thetaphi_clus  = new TH2D("nb0w_rot_Thetaphi_clus","n B0 #theta* vs #phi* for clusters 1 - 6; #theta* (mRad); #phi* (deg); Rate/bin (Hz)",100,0.0,25.0,100,-200,200); 
  TH2* nb0w_rot_PosXY_clus  = new TH2D("nb0w_rot_PosXY_clus","n B0 X* vs Y* around proton axis at Z = 6.8 m for clusters 1 - 6; x (mm); y (mm); Rate/bin (Hz)",100,-200,200,100,-200,200);
  
  // Analysis
  TH2* nb0w_treccorr= new TH2D("nb0w_treccorr", "B0 -t rec_corr vs -t truth Distribution w/ 5 < Q^{2} < 35, 6 < #theta* < 12 cuts; -t_{rec_corr} (GeV^{2});-t_{truth}(GeV^{2}); Rate/bin (Hz)", 100, 0.0,2.0,100, 0.0,1.5);
  
  TH1* nb0w_treccorrdiff = new TH1D("nb0w_treccorrdiff", "-t_{rec_corr} - -t_{alt_truth} Distribution w/ 5 < Q^{2} < 35, 6 < #theta* < 12 cuts; #Delta -t (GeV^{2}); Rate (Hz) ", 100, -0.5,0.6);
  nb0w_treccorrdiff->SetLineColor(kGreen+2); nb0w_treccorrdiff->SetLineWidth(2);
  
  TH2* nb0_ThetaPhiDiff = new TH2D("nb0_ThetaPhiDiff", "#theta*_{pMiss_rec} - #theta*_{B0} vs #phi*_{pMiss_rec} - #phi*_{B0} w/ 5 < Q^{2} < 35, 6 < #theta* < 12 cuts; #theta*_{pMiss_rec} - #theta*_{B0} (Deg); #phi*_{pMiss_rec} - #phi*_{B0} (Deg); Rate/bin (Hz)",100, -1.0, 1.5, 100, -75, 75);
  
  // Analysis -> All cuts
  TH2* nb0wcut_treccorr= new TH2D("nb0wcut_treccorr", "B0 -t rec_corr vs -t truth Distribution w/ 5 < Q^{2} < 35, 6 < #theta* < 12, #theta_{diff} , #phi_{diff} cuts; -t_{rec_corr} (GeV^{2});-t_{truth}(GeV^{2}); Rate/bin (Hz)", 100, 0.0,2.0,100, 0.0,1.5);
  TH1* nb0wcut_treccorrdiff = new TH1D("nb0wcut_treccorrdiff", "-t_{rec_corr} - -t_{alt_truth} Distribution w/ 5 < Q^{2} < 35, 6 < #theta* < 12, #theta_{diff} , #phi_{diff} cuts; #Delta -t (GeV^{2}); Rate (Hz) ", 100, -0.5,0.6);
  nb0wcut_treccorrdiff->SetLineColor(kGreen+2); nb0wcut_treccorrdiff->SetLineWidth(2);
  
  // Physics results //no change
  double Q2BinVal[8] = {5.0, 7.5, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0}; 
    
  TH1* htw_t_cut_result[8];
  TH1* htw_Q2_cut_result[8];
  TH1* htw_W_cut_result[8];
  
  for(unsigned int A = 0; A <8; A++) {
    if (A==0){
      htw_t_cut_result[A] = new TH1D(Form("t_Result_Q2_%i", A), Form("-t dist w/ %2.1f < Q^{2} < %2.1f, #theta_{diff} , #phi_{diff} cuts; -t_{rec_corr} (GeV^{2}); Rate(Hz)", 		Q2BinVal[0],Q2BinVal[7]), 25, 0.3, 1.3); //10, 0, 0.4
      htw_Q2_cut_result[A] = new TH1D(Form("Q2_Result_Q2_%i", A), Form("Q^{2} dist w/ %2.1f < Q^{2} < %2.1f, #theta_{diff} , #phi_{diff} cuts; Q^{2} (GeV^{2}); Rate(Hz)", 		Q2BinVal[0],Q2BinVal[7]), 25, Q2BinVal[0], Q2BinVal[7]);
      htw_W_cut_result[A] = new TH1D(Form("W_Result_Q2_%i", A), Form("W dist w/ %2.1f < Q^{2} < %2.1f, #theta_{diff} , #phi_{diff} cuts; W (GeV); Rate(Hz)", 		Q2BinVal[0],Q2BinVal[7]), 40, 0, 20);
    }
    
    else {
      htw_t_cut_result[A] = new TH1D(Form("t_Result_Q2_%i", A), Form("-t dist w/ %2.1f < Q^{2} < %2.1f, #theta_{diff} , #phi_{diff} cuts; -t_{rec_corr} (GeV^{2}); Rate(Hz)", Q2BinVal[A-1],Q2BinVal[A]), 25, 0.3, 1.3);
      htw_Q2_cut_result[A] = new TH1D(Form("Q2_Result_Q2_%i", A), Form("Q^{2} dist w/ %2.1f < Q^{2} < %2.1f, #theta_{diff} , #phi_{diff} cuts; Q^{2} (GeV^{2}); Rate(Hz)", Q2BinVal[A-1],Q2BinVal[A]), 25, Q2BinVal[A-1]-5, Q2BinVal[A]+5);
      htw_W_cut_result[A] = new TH1D(Form("W_Result_Q2_%i", A), Form("W dist w/ %2.1f < Q^{2} < %2.1f, #theta_{diff} , #phi_{diff} cuts; W (GeV); Rate(Hz)", Q2BinVal[A-1],Q2BinVal[A]), 40, 0, 20);
    }
    
    htw_t_cut_result[A]->SetLineWidth(2);
    htw_Q2_cut_result[A]->SetLineWidth(2);
    htw_W_cut_result[A]->SetLineWidth(2);
  }
   
  // Effeciency plots
  TH2* Q2_t_DetEff_Uncut = new TH2F("Q2_t_DetEff_Uncut", "Q^{2}_{truth} vs -t_{alt_truth} for thrown events; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 50, 0.3, 1.3);
  TH2* Q2_t_DetEff_Cut = new TH2F("Q2_t_DetEff_Cut", "Q^{2}_{truth} vs -t_{alt_truth} for detected events; Q^{2} (GeV^{2}); -t (GeV^{2}); Rate/bin (Hz)", 40, 0, 40, 50, 0.3, 1.3);
  TH2* Q2_t_DetEff = new TH2F("Q2_t_DetEff", "Q^{2}_{truth} vs -t_{alt_truth} detected/thrown ratio; Q^{2} (GeV^{2}); -t (GeV^{2})", 40, 0, 40, 50, 0.3, 1.3); //20, 0, 40, 30, 0, 1.5
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  //Defining the four vectors
  ROOT::Math::PxPyPzEVector elec_beam; // initialized the 4 vector for electron beam
  ROOT::Math::PxPyPzEVector prot_beam; // initialized the 4 vector for proton beam
  ROOT::Math::PxPyPzEVector prot_nbfbeam; // initialized the 4 vector for proton beam for nbf

  ROOT::Math::PxPyPzEVector elec_nbfmc; // initialized the 4 vector for truth nbf electron
  ROOT::Math::PxPyPzEVector pi_nbfmc; // initialized the 4 vector for truth nbf pion
  ROOT::Math::PxPyPzEVector neut_nbfmc; // initialized the 4 vector for truth nbf neutron
  
  ROOT::Math::PxPyPzEVector elec_mc; // initialized the 4 vector for truth electron
  ROOT::Math::PxPyPzEVector pi_mc; // initialized the 4 vector for truth pion
  ROOT::Math::PxPyPzEVector neut_mc; // initialized the 4 vector for truth neutron
  ROOT::Math::PxPyPzEVector neut_rot_mc; // initialized the 4 vector for truth neutron with a rotation of 25 mrad
  
  ROOT::Math::PxPyPzEVector elec_rec; // initialized the 4 vector for reconstructed electron
  ROOT::Math::PxPyPzEVector pi_rec; // initialized the 4 vector for reconstructed pion
  
  ROOT::Math::RotationY rot; // initialized rotation vector
  rot.SetAngle(0.025);
  
  ROOT::Math::XYZVector neut_pos_b0; // initialized the 3 vector for B0 position
  ROOT::Math::XYZVector neut_rot_pos_b0; // initialized the 4 vector for reconstructed neutron with a rotation of 25 mrad in B0
  ROOT::Math::PxPyPzMVector neut_corr_b0; // intialized the 4 vector for reconstructed corrected neutron in B0
  ROOT::Math::PxPyPzEVector treccorr_b0; // intialized the 4 vector for trecpT(-t) in B0
  
  ROOT::Math::XYZVector neut_pos_b0_clus; // initialized the 3 vector for B0 position
  ROOT::Math::XYZVector neut_rot_pos_b0_clus; // initialized the 4 vector for reconstructed neutron with a rotation of 25 mrad in B0
  
  ROOT::Math::PxPyPzEVector virtphoton_nbftruth; // intialized the 4 vector for truth virtual photon for nbf
  ROOT::Math::PxPyPzEVector tnbftruth; // intialized the 4 vector for ttruth (-t)from first loop for nbf
  ROOT::Math::PxPyPzEVector tnbfalttruth; // intialized the 4 vector for ttruth (-t)from second loop for nbf
  
  ROOT::Math::PxPyPzEVector virtphoton_truth; // intialized the 4 vector for truth virtual photon
  ROOT::Math::PxPyPzEVector ttruth; // intialized the 4 vector for ttruth (-t)from first loop
  ROOT::Math::PxPyPzEVector talttruth; // intialized the 4 vector for ttruth (-t)from second loop for nbf
  
  ROOT::Math::PxPyPzEVector virtphoton_rec; //intialized the 4 vector for reconstructed virtual photon
  ROOT::Math::PxPyPzEVector p_miss_rec;  //intialized the 4 vector for missing momentum
  ROOT::Math::PxPyPzEVector p_miss_rot_rec;
  
  double  weight, partEng,t_truth, t_alttruth, nbfpartEng, t_nbftruth, t_nbfalttruth;
  
  int ecal_clus_size_b0; // B0 Neutrons
  double neutb0PosX, neutb0PosY,t_reccorr_b0;
  double neutb0PosX_clus, neutb0PosY_clus;
  double Q2_truth, Q2_rec, W_rec, y_rec;
  double nTheta_Diff_b0, nPhi_Diff_b0;
  
  double ThetaDiff_Cut_Low_b0 = - 0.26; // change based on the reconstructed plots of neutron theta vs phi 
  double ThetaDiff_Cut_High_b0 = 0.17;
  double PhiDiff_Cut_b0 = 30.0;
  double Q2_low, Q2_high;
  
  float E_H, E_M, E_L, posX_H, posX_M, posX_L, posY_H, posY_M, posY_L, posZ_H, posZ_M, posZ_L, en_clus, posX_clus, posY_clus, posZ_clus;
  float E_M1, E_M2, E_M3, E_M4, posX_M1, posX_M2, posX_M3, posX_M4, posY_M1, posY_M2, posY_M3, posY_M4, posZ_M1, posZ_M2, posZ_M3, posZ_M4;
  
  float en_cut = 0.25;
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  // Defining initial colliding beams
  double eMass = 0.000510998950; //electron beam
  double eEng = 10;
  double e_pmag = sqrt(pow(eEng,2)-pow(eMass,2));
  double e_p1 = 0.;
  double e_p2 = 0.;
  double e_p3 = -1*e_pmag;
  elec_beam.SetPxPyPzE(e_p1, e_p2, e_p3, eEng);
  
  double pMass = 0.93827208816; // proton beam
  double pEng = 100; //change
  double p_pmag = sqrt(pow(pEng,2)-pow(pMass,2));
  double c_a = 0.025;
  double p_p1 = -p_pmag*sin(c_a);
  double p_p2 = 0.;
  double p_p3 = p_pmag*cos(c_a);
  prot_beam.SetPxPyPzE(p_p1, p_p2, p_p3, pEng);
  
  prot_nbfbeam.SetPxPyPzE(0., 0., p_pmag, pEng); // calculate -t from second vertex for nbf MCparticles with zero crossing angle
  
  double neutMass = 0.93965420;
  
  unsigned int cnt1 = 0;
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  bool x,y,z; // x,y, and z are for reconstructed electron, pion, and neutron
  bool clus1, clus2, clus3, clus4, clus5, clus6, z1;
  
  while(tree_reader.Next()) { // Loop over events
 
    x = false, y = false, z = false;
    clus1 = false, clus2 = false, clus3 = false, clus4 = false, clus5 = false, clus6 = false, z1 = false;
    
    std::vector<std::string> weight_value = weight_map[0];
    weight = std::stod(weight_value[0]);
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
    for(unsigned int i=0; i<nbfpartGenStat.GetSize(); i++) { // Loop over thrown nbf particles
      nbfpartEng = sqrt(pow(nbfpartMomX[i],2) + pow(nbfpartMomY[i],2) + pow(nbfpartMomZ[i],2) + pow(nbfpartMass[i],2)); // Energy of all Truth nbf  Monte Carlo particles
		
      if(nbfpartGenStat[i] == 1 && nbfpartPdg[i] == 11) { // Select stable thrown nbf particles and look at electron
	elec_nbfmc.SetPxPyPzE(nbfpartMomX[i], nbfpartMomY[i], nbfpartMomZ[i], nbfpartEng);
      }
      
      if(nbfpartGenStat[i] == 1 && nbfpartPdg[i] == 211) { // Look at pion
	pi_nbfmc.SetPxPyPzE(nbfpartMomX[i], nbfpartMomY[i], nbfpartMomZ[i], nbfpartEng);
      }
 
      if(nbfpartGenStat[i] == 1 && nbfpartPdg[i] == 2112) { // Look at neutron
	neut_nbfmc.SetPxPyPzE(nbfpartMomX[i], nbfpartMomY[i], nbfpartMomZ[i], nbfpartEng);
      }
    
    } // for over thrown nbf particles
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    for(unsigned int i=0; i<partGenStat.GetSize(); i++) { // Loop over thrown particles
      partEng = sqrt(pow(partMomX[i],2) + pow(partMomY[i],2) + pow(partMomZ[i],2) + pow(partMass[i],2)); // Energy of all Monte Carlo particles
		
      if(partGenStat[i] == 1 && partPdg[i] == 11) { // Select stable thrown particles and look at electron
	elec_mc.SetPxPyPzE(partMomX[i],partMomY[i],partMomZ[i], partEng);
      }
 
      if(partGenStat[i] == 1 && partPdg[i] == 211) { // Look at pion
	pi_mc.SetPxPyPzE(partMomX[i],partMomY[i],partMomZ[i], partEng);
      }
      
      if(partGenStat[i] == 1 && partPdg[i] == 2112) { // Look at neutron
	neut_mc.SetPxPyPzE(partMomX[i],partMomY[i],partMomZ[i], partEng);\
	neut_rot_mc = rot*neut_mc;  // rotate w.r.t to proton axis
      }
 
   
    } // for over thrown particles
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
    for(unsigned int i=0; i<trackPdg.GetSize(); i++) { // Loop over reconstructed particles 
      //if(trackPdg[i] == 11) { // Look at electron
      if(trackCharge[i] == -1 && trackMomZ[i] < 0) { 
	x = true;
	elec_rec.SetPxPyPzE(trackMomX[i],trackMomY[i],trackMomZ[i], trackEng[i]);
      }
 
      //if(trackPdg[i] == 211) { // Look at pion
      if(trackCharge[i] == +1 && trackMomZ[i] > 0) {
	y = true;
	pi_rec.SetPxPyPzE(trackMomX[i],trackMomY[i],trackMomZ[i], trackEng[i]);
      }
 
    }// for over reconstructed particles

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    ecal_clus_size_b0 = neutEng_b0.GetSize(); // B0 ECal cluster size -> No. of clusters in B0
    
    for(unsigned int i=0; i<neutEng_b0.GetSize(); i++) { // Loop over neutrons in B0 ECal
      z= true;
      // ecal_clus_size_b0 = neutEng_b0.GetSize(); // B0 ECal cluster size -> No. of clusters in B0
      //cout<<"clus =  "<<ecal_clus_size_b0<<", weight =  "<<weight<<endl;
      nb0_clus->Fill(ecal_clus_size_b0); // plot of no. of clusters in B0
      
      nb0w_PosXY -> Fill(neutPosX_b0[i], neutPosY_b0[i], weight);
      
      if(ecal_clus_size_b0 >0 ){
        
	neut_pos_b0.SetXYZ(neutPosX_b0[i], neutPosY_b0[i], neutPosZ_b0[i]);
	neut_rot_pos_b0 = rot*neut_pos_b0; // rotate w.r.t to proton axis
     
        nb0w_rot_Thetaphi -> Fill(neut_rot_pos_b0.Theta()*1000., neut_rot_pos_b0.Phi()*TMath::RadToDeg(), weight);
	  
        neutb0PosX = 6800 * sin(neut_rot_pos_b0.Theta()) * cos(neut_rot_pos_b0.Phi()); // b0 neutron position at r = z = 6.8 m
	neutb0PosY = 6800 * sin(neut_rot_pos_b0.Theta()) * sin(neut_rot_pos_b0.Phi());
	  
	nb0w_rot_PosXY -> Fill(neutb0PosX, neutb0PosY, weight);
        nb0_ClusE -> Fill(ecal_clus_size_b0, neutEng_b0[i]); 
      }
	
    }// for over neutrons in B0 ECal

    //--------------------------------------------------------------------------------------------------------------------------------------
    // Combining all the clusters............................
    //--------------------------------------------------------------------------------------------------------------------------------------

    if (ecal_clus_size_b0 == 1) {
      if (neutEng_b0[0] >= en_cut){
	clus1 = true;
	posX_clus = neutPosX_b0[0];
	posY_clus = neutPosY_b0[0];
	posZ_clus = neutPosZ_b0[0];
       
	nb0w_PosXY_clus1 -> Fill(posX_clus, posY_clus, weight);
      
	neut_pos_b0_clus.SetXYZ(posX_clus, posY_clus, posZ_clus);
      }
    }
     
    //--------------------------------------------------------------------------------------------------------------------------------------
    if (ecal_clus_size_b0 == 2) {
  
      // Use std::array to store energy and positions separately
      std::array<std::array<float, 4>, 2> energyPosition = {{
	  {neutEng_b0[0], neutPosX_b0[0], neutPosY_b0[0], neutPosZ_b0[0]},
	  {neutEng_b0[1], neutPosX_b0[1], neutPosY_b0[1], neutPosZ_b0[1]}
	}};
    
      // Sort the array based on energy in descending order
      std::sort(energyPosition.begin(), energyPosition.end(), [](const std::array<float, 4>& a, const std::array<float, 4>& b){
	  if (a[0] != b[0]) {
	    return a[0] > b[0];  // Sort by energy descending
	  }
              
	  return false;  // Keep order unchanged when energies are equal
	});
    
      // Assign the sorted values
      E_H = energyPosition[0][0];   
      posX_H = energyPosition[0][1]; 
      posY_H = energyPosition[0][2]; 
      posZ_H = energyPosition[0][3]; 
    
      E_L = energyPosition[1][0];   
      posX_L = energyPosition[1][1]; 
      posY_L = energyPosition[1][2]; 
      posZ_L = energyPosition[1][3]; 
   
      nb0E_Clus2 -> Fill(E_H, E_L, weight);
  
      // Print the values
      // cout << "E_H = " << E_H << ", E_L = " << E_L << ", posX_H = " << posX_H << ", posX_L = " << posX_L << endl;
   
      if (E_H >= en_cut) {
	clus2 = true;
	if (E_L >= en_cut) {
	  en_clus = E_H + E_L;
	  posX_clus = (posX_H * E_H + posX_L * E_L) / en_clus; // Weighted average
	  posY_clus = (posY_H * E_H + posY_L * E_L) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_L * E_L) / en_clus;
	} 
	else {
	  en_clus = E_H;
	  posX_clus = posX_H; 
	  posY_clus = posY_H;
	  posZ_clus = posZ_H;
	}
      
	nb0w_PosXY_clus2 -> Fill(posX_clus, posY_clus, weight);
        
	neut_pos_b0_clus.SetXYZ(posX_clus, posY_clus, posZ_clus);
      }
    }

    //--------------------------------------------------------------------------------------------------------------------------------------
    if (ecal_clus_size_b0 == 3) {
  
      // Use std::array to store energy and positions separately
      std::array<std::array<float, 4>, 3> energyPosition = {{
	  {neutEng_b0[0], neutPosX_b0[0], neutPosY_b0[0], neutPosZ_b0[0]},
	  {neutEng_b0[1], neutPosX_b0[1], neutPosY_b0[1], neutPosZ_b0[1]},
	  {neutEng_b0[2], neutPosX_b0[2], neutPosY_b0[2], neutPosZ_b0[2]}
	}};
    
      // Sort the array based on energy (first element), in descending order
      std::sort(energyPosition.begin(), energyPosition.end(),
		[](const std::array<float, 4>& a, const std::array<float, 4>& b) {
		  if (a[0] != b[0]) {
		    return a[0] > b[0];  
		  }
                  return false; 
		});
    
      // Assign the sorted values
      E_H = energyPosition[0][0];   
      posX_H = energyPosition[0][1]; 
      posY_H = energyPosition[0][2];
      posZ_H = energyPosition[0][3]; 
    
      E_M = energyPosition[1][0];   
      posX_M = energyPosition[1][1]; 
      posY_M = energyPosition[1][2]; 
      posZ_M = energyPosition[1][3]; 
    
      E_L = energyPosition[2][0];   
      posX_L = energyPosition[2][1]; 
      posY_L = energyPosition[2][2];
      posZ_L = energyPosition[2][3]; 
   
      nb0EH_clus3->Fill(E_H, weight);
      nb0EM_clus3->Fill(E_M, weight);
      nb0EL_clus3->Fill(E_L, weight);
  
      // Print the values
      // cout << "E_H = " << E_H << ", E_M = " << E_M << ", E_L = " << E_L << ", posX_H = " << posX_H << ", posX_L = " << posX_L << endl;
   
      if (E_H >= en_cut) {
	clus3 = true;
        if (E_M >= en_cut && E_L >= en_cut) {
	  en_clus = E_H + E_M + E_L;
	  posX_clus = (posX_H * E_H + posX_M * E_M + posX_L * E_L) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M * E_M + posY_L * E_L) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M * E_M + posZ_L * E_L) / en_clus;
        } 
        else if (E_M >= en_cut && E_L < en_cut) {
	  en_clus = E_H + E_M;
	  posX_clus = (posX_H * E_H + posX_M * E_M) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M * E_M) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M * E_M) / en_clus;
        } 
        else if (E_M < en_cut && E_L < en_cut) {
	  en_clus = E_H;
	  posX_clus = posX_H;
	  posY_clus = posY_H;
	  posZ_clus = posZ_H;
        }

        nb0w_PosXY_clus3->Fill(posX_clus, posY_clus, weight);
        
        neut_pos_b0_clus.SetXYZ(posX_clus, posY_clus, posZ_clus);
      }
    }
    //--------------------------------------------------------------------------------------------------------------------------------------
 
    if (ecal_clus_size_b0 == 4) {
  
      // Use std::array to store energy and positions separately
      std::array<std::array<float, 4>, 4> energyPosition = {{
	  {neutEng_b0[0], neutPosX_b0[0], neutPosY_b0[0], neutPosZ_b0[0]},
	  {neutEng_b0[1], neutPosX_b0[1], neutPosY_b0[1], neutPosZ_b0[1]},
	  {neutEng_b0[2], neutPosX_b0[2], neutPosY_b0[2], neutPosZ_b0[2]},
	  {neutEng_b0[3], neutPosX_b0[3], neutPosY_b0[3], neutPosZ_b0[3]}
	}};
    
      // Sort the array based on energy (first element), in descending order
      std::sort(energyPosition.begin(), energyPosition.end(),
		[](const std::array<float, 4>& a, const std::array<float, 4>& b) {
		  if (a[0] != b[0]) {
		    return a[0] > b[0];  
		  }
                  return false; 
		});
    
      // Assign the sorted values
      E_H = energyPosition[0][0];   
      posX_H = energyPosition[0][1]; 
      posY_H = energyPosition[0][2];
      posZ_H = energyPosition[0][3]; 
    
      E_M1 = energyPosition[1][0];   
      posX_M1 = energyPosition[1][1]; 
      posY_M1 = energyPosition[1][2]; 
      posZ_M1 = energyPosition[1][3]; 
    
      E_M2 = energyPosition[2][0];   
      posX_M2 = energyPosition[2][1]; 
      posY_M2 = energyPosition[2][2]; 
      posZ_M2 = energyPosition[2][3]; 
    
      E_L = energyPosition[3][0];   
      posX_L = energyPosition[3][1]; 
      posY_L = energyPosition[3][2];
      posZ_L = energyPosition[3][3]; 
      
      nb0EH_clus4->Fill(E_H, weight);
      nb0EM1_clus4->Fill(E_M1, weight);
      nb0EM2_clus4->Fill(E_M2, weight);
      nb0EL_clus4->Fill(E_L, weight);
   
      // Print the values
      // cout << "E_H = " << E_H << ", E_M1 = " << E_M1 << ", E_M2 = " << E_M2 << ", E_L = " << E_L << ", posX_H = " << posX_H << ", posX_L = " << posX_L << endl;
   
      if (E_H >= en_cut) {
	clus4 = true;
        if (E_M1 >= en_cut && E_M2 >= en_cut && E_L >= en_cut) {
	  en_clus = E_H + E_M1 + E_M2 + E_L;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1 + posX_M2 * E_M2 + posX_L * E_L) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1 + posY_M2 * E_M2 + posY_L * E_L) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1 + posZ_M2 * E_M2 + posZ_L * E_L) / en_clus;
        } 
        else if (E_M1 >= en_cut && E_M2 >= en_cut && E_L < en_cut) {
	  en_clus = E_H + E_M1 + E_M2;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1 + posX_M2 * E_M2) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1 + posY_M2 * E_M2) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1 + posZ_M2 * E_M2) / en_clus;
        } 
        else if (E_M1 >= en_cut && E_M2 < en_cut && E_L < en_cut) {
	  en_clus = E_H + E_M1;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1) / en_clus;
        } 
        else if (E_M1 < en_cut && E_M2 < en_cut && E_L < en_cut) {
	  en_clus = E_H;
	  posX_clus = posX_H;
	  posY_clus = posY_H;
	  posZ_clus = posZ_H;
        }

        nb0w_PosXY_clus4->Fill(posX_clus, posY_clus, weight);
        
        neut_pos_b0_clus.SetXYZ(posX_clus, posY_clus, posZ_clus);
      }
    }
 
    //--------------------------------------------------------------------------------------------------------------------------------------
    
    if (ecal_clus_size_b0 == 5) {
  
      // Use std::array to store energy and positions separately
      std::array<std::array<float, 4>, 5> energyPosition = {{
	  {neutEng_b0[0], neutPosX_b0[0], neutPosY_b0[0], neutPosZ_b0[0]},
	  {neutEng_b0[1], neutPosX_b0[1], neutPosY_b0[1], neutPosZ_b0[1]},
	  {neutEng_b0[2], neutPosX_b0[2], neutPosY_b0[2], neutPosZ_b0[2]},
	  {neutEng_b0[3], neutPosX_b0[3], neutPosY_b0[3], neutPosZ_b0[3]},
	  {neutEng_b0[4], neutPosX_b0[4], neutPosY_b0[4], neutPosZ_b0[4]}
	}};
    
      // Sort the array based on energy (first element), in descending order
      std::sort(energyPosition.begin(), energyPosition.end(),
		[](const std::array<float, 4>& a, const std::array<float, 4>& b) {
		  if (a[0] != b[0]) {
		    return a[0] > b[0];  
		  }
                  return false; 
		});
    
      // Assign the sorted values
      E_H = energyPosition[0][0];   
      posX_H = energyPosition[0][1]; 
      posY_H = energyPosition[0][2];
      posZ_H = energyPosition[0][3]; 
    
      E_M1 = energyPosition[1][0];   
      posX_M1 = energyPosition[1][1]; 
      posY_M1 = energyPosition[1][2]; 
      posZ_M1 = energyPosition[1][3]; 
    
      E_M2 = energyPosition[2][0];   
      posX_M2 = energyPosition[2][1]; 
      posY_M2 = energyPosition[2][2]; 
      posZ_M2 = energyPosition[2][3]; 
      
      E_M3 = energyPosition[3][0];   
      posX_M3 = energyPosition[3][1]; 
      posY_M3 = energyPosition[3][2]; 
      posZ_M3 = energyPosition[3][3];
    
      E_L = energyPosition[4][0];   
      posX_L = energyPosition[4][1]; 
      posY_L = energyPosition[4][2];
      posZ_L = energyPosition[4][3]; 
      
      nb0EH_clus5->Fill(E_H, weight);
      nb0EM1_clus5->Fill(E_M1, weight);
      nb0EM2_clus5->Fill(E_M2, weight);
      nb0EM3_clus5->Fill(E_M3, weight);
      nb0EL_clus5->Fill(E_L, weight);
   
      // Print the values
      // cout << "E_H = " << E_H << ", E_M1 = " << E_M1 << ", E_M2 = " << E_M2 << ", E_M3 = " << E_M3 << ", E_L = " << E_L << ", posX_H = " << posX_H << ", posX_L = " << posX_L << endl;
   
      if (E_H >= en_cut) {
      	clus5 = true;
        if (E_M1 >= en_cut && E_M2 >= en_cut && E_M3 >= en_cut && E_L >= en_cut) {
	  en_clus = E_H + E_M1 + E_M2 + E_M3 + E_L;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1 + posX_M2 * E_M2 + posX_M3 * E_M3 + posX_L * E_L) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1 + posY_M2 * E_M2 + posY_M3 * E_M3 + posY_L * E_L) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1 + posZ_M2 * E_M2 + posZ_M3 * E_M3 + posZ_L * E_L) / en_clus;
        } 
        else if (E_M1 >= en_cut && E_M2 >= en_cut && E_M3 >= en_cut && E_L < en_cut) {
	  en_clus = E_H + E_M1 + E_M2 + E_M3;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1 + posX_M2 * E_M2 + posX_M3 * E_M3) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1 + posY_M2 * E_M2 + posY_M3 * E_M3) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1 + posZ_M2 * E_M2 + posZ_M3 * E_M3) / en_clus;
        } 
        else if (E_M1 >= en_cut && E_M2 >= en_cut && E_M3 < en_cut && E_L < en_cut) {
	  en_clus = E_H + E_M1 + E_M2;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1 + posX_M2 * E_M2) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1 + posY_M2 * E_M2) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1 + posZ_M2 * E_M2) / en_clus;
        } 
        else if (E_M1 >= en_cut && E_M2 < en_cut && E_M3 < en_cut && E_L < en_cut) {
	  en_clus = E_H + E_M1;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1) / en_clus;
        } 
        else if (E_M1 < en_cut && E_M2 < en_cut && E_M3 < en_cut && E_L < en_cut) {
	  en_clus = E_H;
	  posX_clus = posX_H;
	  posY_clus = posY_H;
	  posZ_clus = posZ_H;
        }

        nb0w_PosXY_clus5->Fill(posX_clus, posY_clus, weight);
        
        neut_pos_b0_clus.SetXYZ(posX_clus, posY_clus, posZ_clus);
      }
    }
 
    //--------------------------------------------------------------------------------------------------------------------------------------
    
    if (ecal_clus_size_b0 == 6) {
  
      // Use std::array to store energy and positions separately
      std::array<std::array<float, 4>, 6> energyPosition = {{
	  {neutEng_b0[0], neutPosX_b0[0], neutPosY_b0[0], neutPosZ_b0[0]},
	  {neutEng_b0[1], neutPosX_b0[1], neutPosY_b0[1], neutPosZ_b0[1]},
	  {neutEng_b0[2], neutPosX_b0[2], neutPosY_b0[2], neutPosZ_b0[2]},
	  {neutEng_b0[3], neutPosX_b0[3], neutPosY_b0[3], neutPosZ_b0[3]},
	  {neutEng_b0[4], neutPosX_b0[4], neutPosY_b0[4], neutPosZ_b0[4]},
	  {neutEng_b0[5], neutPosX_b0[5], neutPosY_b0[5], neutPosZ_b0[5]}
	}};
    
      // Sort the array based on energy (first element), in descending order
      std::sort(energyPosition.begin(), energyPosition.end(),
		[](const std::array<float, 4>& a, const std::array<float, 4>& b) {
		  if (a[0] != b[0]) {
		    return a[0] > b[0];  
		  }
                  return false; 
		});
    
      // Assign the sorted values
      E_H = energyPosition[0][0];   
      posX_H = energyPosition[0][1]; 
      posY_H = energyPosition[0][2];
      posZ_H = energyPosition[0][3]; 
    
      E_M1 = energyPosition[1][0];   
      posX_M1 = energyPosition[1][1]; 
      posY_M1 = energyPosition[1][2]; 
      posZ_M1 = energyPosition[1][3]; 
    
      E_M2 = energyPosition[2][0];   
      posX_M2 = energyPosition[2][1]; 
      posY_M2 = energyPosition[2][2]; 
      posZ_M2 = energyPosition[2][3]; 
      
      E_M3 = energyPosition[3][0];   
      posX_M3 = energyPosition[3][1]; 
      posY_M3 = energyPosition[3][2]; 
      posZ_M3 = energyPosition[3][3];
    
      E_M4 = energyPosition[4][0];   
      posX_M4 = energyPosition[4][1]; 
      posY_M4 = energyPosition[4][2];
      posZ_M4 = energyPosition[4][3]; 
      
      E_L = energyPosition[5][0];   
      posX_L = energyPosition[5][1]; 
      posY_L = energyPosition[5][2];
      posZ_L = energyPosition[5][3]; 
      
      nb0EH_clus6->Fill(E_H, weight);
      nb0EM1_clus6->Fill(E_M1, weight);
      nb0EM2_clus6->Fill(E_M2, weight);
      nb0EM3_clus6->Fill(E_M3, weight);
      nb0EM4_clus6->Fill(E_M4, weight);
      nb0EL_clus6->Fill(E_L, weight);
   
      // Print the values
      // cout << "E_H = " << E_H << ", E_M1 = " << E_M1 << ", E_M2 = " << E_M2 << ", E_M3 = " << E_M3 << ", E_L = " << E_L << ", posX_H = " << posX_H << ", posX_L = " << posX_L << endl;
   
      if (E_H >= en_cut) {
      	clus6 = true;
        if (E_M1 >= en_cut && E_M2 >= en_cut && E_M3 >= en_cut && E_M4 >= en_cut && E_L >= en_cut) {
	  en_clus = E_H + E_M1 + E_M2 + E_M3 + E_M4 + E_L;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1 + posX_M2 * E_M2 + posX_M3 * E_M3 + posX_M4 * E_M4 + posX_L * E_L) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1 + posY_M2 * E_M2 + posY_M3 * E_M3 + posY_M4 * E_M4 + posY_L * E_L) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1 + posZ_M2 * E_M2 + posZ_M3 * E_M3 + posZ_M4 * E_M4 + posZ_L * E_L) / en_clus;
        } 
        else if (E_M1 >= en_cut && E_M2 >= en_cut && E_M3 >= en_cut && E_M4 >= en_cut && E_L < en_cut) {
	  en_clus = E_H + E_M1 + E_M2 + E_M3 + E_M4;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1 + posX_M2 * E_M2 + posX_M3 * E_M3 + posX_M4 * E_M4) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1 + posY_M2 * E_M2 + posY_M3 * E_M3 + posY_M4 * E_M4) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1 + posZ_M2 * E_M2 + posZ_M3 * E_M3 + posZ_M4 * E_M4) / en_clus;
        } 
        else if (E_M1 >= en_cut && E_M2 >= en_cut && E_M3 >= en_cut && E_M4 < en_cut && E_L < en_cut) {
	  en_clus = E_H + E_M1 + E_M2 + E_M3;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1 + posX_M2 * E_M2 + posX_M3 * E_M3) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1 + posY_M2 * E_M2 + posY_M3 * E_M3) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1 + posZ_M2 * E_M2 + posZ_M3 * E_M3) / en_clus;
        }
        else if (E_M1 >= en_cut && E_M2 >= en_cut && E_M3 < en_cut && E_M4 < en_cut && E_L < en_cut) {
	  en_clus = E_H + E_M1 + E_M2;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1 + posX_M2 * E_M2) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1 + posY_M2 * E_M2) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1 + posZ_M2 * E_M2) / en_clus;
        } 
        else if (E_M1 >= en_cut && E_M2 < en_cut && E_M3 < en_cut && E_M4 < en_cut && E_L < en_cut) {
	  en_clus = E_H + E_M1;
	  posX_clus = (posX_H * E_H + posX_M1 * E_M1) / en_clus;
	  posY_clus = (posY_H * E_H + posY_M1 * E_M1) / en_clus;
	  posZ_clus = (posZ_H * E_H + posZ_M1 * E_M1) / en_clus;
        } 
        else if (E_M1 < en_cut && E_M2 < en_cut && E_M3 < en_cut && E_M4 < en_cut && E_L < en_cut) {
	  en_clus = E_H;
	  posX_clus = posX_H;
	  posY_clus = posY_H;
	  posZ_clus = posZ_H;
        }

        nb0w_PosXY_clus6->Fill(posX_clus, posY_clus, weight);
        
        neut_pos_b0_clus.SetXYZ(posX_clus, posY_clus, posZ_clus);
      }
    }
 
    //--------------------------------------------------------------------------------------------------------------------------------------
 
    if (clus1 == true || clus2 == true || clus3 == true || clus4 == true || clus5 == true || clus6 == true) {
       
      neut_rot_pos_b0_clus = rot*neut_pos_b0_clus; // rotate w.r.t to proton axis
      nb0w_rot_Thetaphi_clus -> Fill(neut_rot_pos_b0_clus.Theta()*1000., neut_rot_pos_b0_clus.Phi()*TMath::RadToDeg(), weight);
        
      neutb0PosX_clus = 6800 * sin(neut_rot_pos_b0_clus.Theta()) * cos(neut_rot_pos_b0_clus.Phi()); // b0 neutron position at r = z = 6.8 m
      neutb0PosY_clus = 6800 * sin(neut_rot_pos_b0_clus.Theta()) * sin(neut_rot_pos_b0_clus.Phi());
	  
      nb0w_rot_PosXY_clus -> Fill(neutb0PosX_clus, neutb0PosY_clus, weight);
	
      if((neut_rot_pos_b0_clus.Theta()*1000.) > 6.0 && (neut_rot_pos_b0_clus.Theta()*1000.) < 12.0){ //change
	z1= true;
	
      }
        
    }
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
     
    virtphoton_nbftruth = (elec_beam - elec_nbfmc); //virtualphoton for nbf
    tnbftruth = (virtphoton_nbftruth - pi_nbfmc); 
    t_nbftruth = -1*(tnbftruth.mag2()); // ttruth is the -t from the first loop for nbf
    
    
    tnbfalttruth = (prot_nbfbeam - neut_nbfmc); 
    t_nbfalttruth = -1*(tnbfalttruth.mag2()); // t_alttruth is the -t from the second loop for nbf
   
    
    virtphoton_truth = (elec_beam - elec_mc); //virtualphoton for MCParticles
    Q2_truth = -1*(virtphoton_truth.mag2());
    ttruth = (virtphoton_truth - pi_mc); 
    t_truth = -1*(ttruth.mag2());// ttruth is the -t from the first loop
   
    
    talttruth = (prot_beam - neut_mc); 
    t_alttruth = -1*(talttruth.mag2()); // t_alttruth is the -t from the second loop
   
    
    if((neut_rot_mc.Theta()*1000.)>6.0 && (neut_rot_mc.Theta()*1000.)<12.0){
      count2++; // truth neutrons
      if(Q2_truth > 5 && Q2_truth < 35){
	t_truth = t_nbfalttruth;
	Q2_t_DetEff_Uncut -> Fill(Q2_truth, t_truth, weight);
      }
    }
    
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    if (x == true && y == true && z1 == true ){ // if e', pi, and neutron in B0 are in coincidence
      t_truth = t_nbfalttruth;
      virtphoton_rec = (elec_beam - elec_rec);
      Q2_rec = -1*(virtphoton_rec.mag2()); 
      W_rec = ((virtphoton_rec + prot_beam).mag());
      y_rec = (prot_beam.Dot(virtphoton_rec))/(prot_beam.Dot(elec_beam)); // Energy Loss y
      
      if(Q2_rec > 5 && Q2_rec < 35){ // Q2 Cut 
       
        p_miss_rec = (elec_beam + prot_beam) - (elec_rec + pi_rec) ; // Defined missing momentum information -> Fourth method to reconstruct -t
        p_miss_rot_rec = rot*p_miss_rec; // rotate p_miss_rec w.r.t to proton axis
        
	neut_corr_b0.SetCoordinates( p_miss_rec.P() * sin(neut_pos_b0_clus.Theta()) * cos(neut_pos_b0_clus.Phi()), // Corrected neutron using missing momentum and angles information 
				     p_miss_rec.P() * sin(neut_pos_b0_clus.Theta()) * sin(neut_pos_b0_clus.Phi()), 
				     p_miss_rec.P() * cos(neut_pos_b0_clus.Theta()),
				     neutMass );
 
        // -t plot from second vertex using neutron corrected information
	treccorr_b0 = (prot_beam - neut_corr_b0);
	t_reccorr_b0 = -1*(treccorr_b0.mag2());
	nb0w_treccorr  -> Fill(t_reccorr_b0, t_truth, weight);
	nb0w_treccorrdiff -> Fill(t_reccorr_b0 - t_truth, weight);
	
	
	// Neutron theta-phi plots 
	nTheta_Diff_b0 = p_miss_rot_rec.Theta() - neut_rot_pos_b0_clus.Theta(); 
	nPhi_Diff_b0   = p_miss_rot_rec.Phi() - neut_rot_pos_b0_clus.Phi();
	nb0_ThetaPhiDiff -> Fill(nTheta_Diff_b0*TMath::RadToDeg(), nPhi_Diff_b0*TMath::RadToDeg(), weight);

      } // if statement over Q2 cut
	 
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
	if((nTheta_Diff_b0*TMath::RadToDeg() > ThetaDiff_Cut_Low_b0)  && (nTheta_Diff_b0*TMath::RadToDeg() < ThetaDiff_Cut_High_b0) && (abs(nPhi_Diff_b0*TMath::RadToDeg()))){
	
	htw_t_cut_result[B] -> Fill(t_reccorr_b0, weight);
	htw_Q2_cut_result[B] -> Fill(Q2_rec, weight);
        htw_W_cut_result[B] -> Fill(W_rec, weight);
	
	if(B==0) {
	
	nb0wcut_treccorr  -> Fill(t_reccorr_b0, t_truth, weight);
	nb0wcut_treccorrdiff -> Fill(t_reccorr_b0 - t_truth, weight);
	
	//effeciency plot
	Q2_t_DetEff_Cut -> Fill(Q2_truth, t_truth, weight);
	
	}
	
	}// if statement over all cuts
	} // if statement over Q2
	} // for loop over B
	
    } // if statement over coincidence particles
    
  } //End while loop
  
  // Efficiency plots
  Q2_t_DetEff -> Divide(Q2_t_DetEff_Cut, Q2_t_DetEff_Uncut, 1, 1, "b");
 //cout<<"  "<<cnt1<<endl;
  //----------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
   
  gStyle->SetPadRightMargin(0.125); // left space on right side
  gStyle->SetPadLeftMargin(0.12); // right space on right side
  gStyle->SetStatX(0.895); // move the stat bax on left or right side
  gStyle->SetStatY(0.90); // move the stat bax on up or down side
  gStyle->SetPalette(55);
  gStyle->SetLineStyleString(2,"[12 12]");
  gStyle->SetHistLineWidth(2);
  
  TCanvas *c1a = new TCanvas("c1a");
  c1a->SetLogy();
  nb0_clus->Draw("HIST");
  
  TCanvas *c1b = new TCanvas("c1b");
  c1b->SetLogz();
  nb0w_PosXY->Scale(1.0/nFiles); 
  nb0w_PosXY->Draw("colz");
  
  TCanvas *c1c = new TCanvas("c1c");
  c1c->SetLogz();
  nb0w_rot_PosXY->Scale(1.0/nFiles); 
  nb0w_rot_PosXY->Draw("colz");
  
  TCanvas *c1d = new TCanvas("c1d");
  c1d->SetLogz();
  nb0_ClusE->Draw("colz");
    
  TCanvas *c1e = new TCanvas("c1e");
  c1e->SetLogz();
  nb0w_rot_Thetaphi->Scale(1.0/nFiles); 
  nb0w_rot_Thetaphi->Draw("colz");
  
  TCanvas *c1f = new TCanvas("c1f");
  c1f->SetLogz();
  nb0w_PosXY_clus1->Scale(1.0/nFiles); 
  nb0w_PosXY_clus1->Draw("colz");
 
  TCanvas *c2a = new TCanvas("c2a"); // 2 clusters
  c2a->SetLogz();
  nb0E_Clus2->Scale(1.0/nFiles); 
  nb0E_Clus2->Draw("colz");
  
  TCanvas *c2b = new TCanvas("c2b");
  c2b->SetLogz();
  nb0w_PosXY_clus2->Scale(1.0/nFiles); 
  nb0w_PosXY_clus2->Draw("colz");
  
  TCanvas *c3a = new TCanvas("c3a"); // 3 clusters
  c3a->SetLogy();
  nb0EH_clus3->Scale(1.0/nFiles); 
  nb0EH_clus3->Draw("HIST"); 
  
  TCanvas *c3b = new TCanvas("c3b"); 
  c3b->SetLogy();
  nb0EM_clus3->Scale(1.0/nFiles); 
  nb0EM_clus3->Draw("HIST"); 
  
  TCanvas *c3c = new TCanvas("c3c");
  c3c->SetLogy();
  nb0EL_clus3->Scale(1.0/nFiles); 
  nb0EL_clus3->Draw("HIST"); 
  
  TCanvas *c3d = new TCanvas("c3d");
  c3d->SetLogz();
  nb0w_PosXY_clus3->Scale(1.0/nFiles); 
  nb0w_PosXY_clus3->Draw("colz");
  
  TCanvas *c7a = new TCanvas("c7a"); // 4 clusters
  c7a->SetLogy();
  nb0EH_clus4->Scale(1.0/nFiles); 
  nb0EH_clus4->Draw("HIST"); 
  
  TCanvas *c7b = new TCanvas("c7b");
  c7b->SetLogy();
  nb0EM1_clus4->Scale(1.0/nFiles); 
  nb0EM1_clus4->Draw("HIST"); 
  
  TCanvas *c7c = new TCanvas("c7c");
  c7c->SetLogy();
  nb0EM2_clus4->Scale(1.0/nFiles); 
  nb0EM2_clus4->Draw("HIST"); 
  
  TCanvas *c7d = new TCanvas("c7d");
  c7d->SetLogy();
  nb0EL_clus4->Scale(1.0/nFiles); 
  nb0EL_clus4->Draw("HIST"); 
  
  TCanvas *c7e = new TCanvas("c7e");
  c7e->SetLogz();
  nb0w_PosXY_clus4->Scale(1.0/nFiles); 
  nb0w_PosXY_clus4->Draw("colz");
  
  TCanvas *c8a = new TCanvas("c8a"); // 5 clusters
  c8a->SetLogy();
  nb0EH_clus5->Scale(1.0/nFiles); 
  nb0EH_clus5->Draw("HIST"); 
  
  TCanvas *c8b = new TCanvas("c8b");
  c8b->SetLogy();
  nb0EM1_clus5->Scale(1.0/nFiles); 
  nb0EM1_clus5->Draw("HIST"); 
  
  TCanvas *c8c = new TCanvas("c8c");
  c8c->SetLogy();
  nb0EM2_clus5->Scale(1.0/nFiles); 
  nb0EM2_clus5->Draw("HIST"); 
  
  TCanvas *c8d = new TCanvas("c8d");
  c8d->SetLogy();
  nb0EM3_clus5->Scale(1.0/nFiles); 
  nb0EM3_clus5->Draw("HIST"); 
  
  TCanvas *c8e = new TCanvas("c8e");
  c8e->SetLogy();
  nb0EL_clus5->Scale(1.0/nFiles); 
  nb0EL_clus5->Draw("HIST");
  
  TCanvas *c8f = new TCanvas("c8f");
  c8f->SetLogz();
  nb0w_PosXY_clus5->Scale(1.0/nFiles); 
  nb0w_PosXY_clus5->Draw("colz");
  
  TCanvas *c9a = new TCanvas("c9a"); // 6 clusters
  c9a->SetLogy();
  nb0EH_clus6->Scale(1.0/nFiles); 
  nb0EH_clus6->Draw("HIST"); 
  
  TCanvas *c9b = new TCanvas("c9b");
  c9b->SetLogy();
  nb0EM1_clus6->Scale(1.0/nFiles); 
  nb0EM1_clus6->Draw("HIST"); 
  
  TCanvas *c9c = new TCanvas("c9c");
  c9c->SetLogy();
  nb0EM2_clus6->Scale(1.0/nFiles); 
  nb0EM2_clus6->Draw("HIST"); 
  
  TCanvas *c9d = new TCanvas("c9d");
  c9d->SetLogy();
  nb0EM3_clus6->Scale(1.0/nFiles); 
  nb0EM3_clus6->Draw("HIST"); 
  
  TCanvas *c9e = new TCanvas("c9e");
  c9e->SetLogy();
  nb0EM4_clus6->Scale(1.0/nFiles); 
  nb0EM4_clus6->Draw("HIST");
  
  TCanvas *c9f = new TCanvas("c9f");
  c9f->SetLogy();
  nb0EL_clus6->Scale(1.0/nFiles); 
  nb0EL_clus6->Draw("HIST");
  
  TCanvas *c9g = new TCanvas("c9g");
  c9g->SetLogz();
  nb0w_PosXY_clus6->Scale(1.0/nFiles); 
  nb0w_PosXY_clus6->Draw("colz");
  
  TCanvas *c4a = new TCanvas("c4a");
  c4a->SetLogz();
  nb0w_rot_Thetaphi_clus->Scale(1.0/nFiles); 
  nb0w_rot_Thetaphi_clus->Draw("colz");
  
  TCanvas *c4b = new TCanvas("c4b");
  c4b->SetLogz();
  nb0w_rot_PosXY_clus->Scale(1.0/nFiles); 
  nb0w_rot_PosXY_clus->Draw("colz");
  
  TCanvas *c5a = new TCanvas("c5a");
  c5a->SetLogz();
  nb0w_treccorr->Scale(1.0/nFiles); 
  nb0w_treccorr->Draw("colz"); 
  
  TCanvas *c5b = new TCanvas("c5b");
  c5b->SetLogz();
  nb0w_treccorrdiff->Scale(1.0/nFiles); 
  nb0w_treccorrdiff->Draw("HIST");
  
  TCanvas *c5c = new TCanvas("c5c");
  c5c->SetLogz();
  nb0_ThetaPhiDiff->Scale(1.0/nFiles);
  nb0_ThetaPhiDiff->Draw("colz"); 
  
  TCanvas *c5d = new TCanvas("c5d");
  c5d->SetLogz();
  nb0wcut_treccorr->Scale(1.0/nFiles); 
  nb0wcut_treccorr->Draw("colz");
  
  TCanvas *c5e = new TCanvas("c5e");
  c5e->SetLogz();
  nb0wcut_treccorrdiff->Scale(1.0/nFiles); 
  nb0wcut_treccorrdiff->Draw("HIST");
  
  TCanvas *c18 = new TCanvas("c18"); // Efficiency plots
  Q2_t_DetEff-> GetZaxis()->SetRangeUser(0.0,1.0);
  Q2_t_DetEff->Draw("colz");
  
  TCanvas *c18a = new TCanvas("c18a"); 
  Q2_t_DetEff_Cut->Scale(1.0/nFiles);
  Q2_t_DetEff_Cut->Draw("colz");
  
  TCanvas *c18b = new TCanvas("c18b"); 
  Q2_t_DetEff_Uncut->Scale(1.0/nFiles);
  Q2_t_DetEff_Uncut->Draw("colz"); 
  
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
  
  c1a->Print("DEMP_reco_test_10on100.pdf[");
  c1a->Print("DEMP_reco_test_10on100.pdf");
  c1b->Print("DEMP_reco_test_10on100.pdf");
  c1c->Print("DEMP_reco_test_10on100.pdf");
  c1d->Print("DEMP_reco_test_10on100.pdf");
  c1e->Print("DEMP_reco_test_10on100.pdf");
  c1f->Print("DEMP_reco_test_10on100.pdf");
  c2a->Print("DEMP_reco_test_10on100.pdf");
  c2b->Print("DEMP_reco_test_10on100.pdf");
  c3a->Print("DEMP_reco_test_10on100.pdf");
  c3b->Print("DEMP_reco_test_10on100.pdf");
  c3c->Print("DEMP_reco_test_10on100.pdf");
  c3d->Print("DEMP_reco_test_10on100.pdf");
  c7a->Print("DEMP_reco_test_10on100.pdf");
  c7b->Print("DEMP_reco_test_10on100.pdf");
  c7c->Print("DEMP_reco_test_10on100.pdf");
  c7d->Print("DEMP_reco_test_10on100.pdf");
  c7e->Print("DEMP_reco_test_10on100.pdf");
  c8a->Print("DEMP_reco_test_10on100.pdf");
  c8b->Print("DEMP_reco_test_10on100.pdf");
  c8c->Print("DEMP_reco_test_10on100.pdf");
  c8d->Print("DEMP_reco_test_10on100.pdf");
  c8e->Print("DEMP_reco_test_10on100.pdf");
  c8f->Print("DEMP_reco_test_10on100.pdf");
  c9a->Print("DEMP_reco_test_10on100.pdf");
  c9b->Print("DEMP_reco_test_10on100.pdf");
  c9c->Print("DEMP_reco_test_10on100.pdf");
  c9d->Print("DEMP_reco_test_10on100.pdf");
  c9e->Print("DEMP_reco_test_10on100.pdf");
  c9f->Print("DEMP_reco_test_10on100.pdf");
  c9g->Print("DEMP_reco_test_10on100.pdf");
  c4a->Print("DEMP_reco_test_10on100.pdf");
  c4b->Print("DEMP_reco_test_10on100.pdf");
  c5a->Print("DEMP_reco_test_10on100.pdf");
  c5b->Print("DEMP_reco_test_10on100.pdf");
  c5c->Print("DEMP_reco_test_10on100.pdf");
  c5d->Print("DEMP_reco_test_10on100.pdf");
  c5e->Print("DEMP_reco_test_10on100.pdf");
  c18b->Print("DEMP_reco_test_10on100.pdf");
  c18a->Print("DEMP_reco_test_10on100.pdf");
  c18->Print("DEMP_reco_test_10on100.pdf");
  for(int D = 0; D <8; D++) { 
    c24[D]->Print("DEMP_reco_test_10on100.pdf"); }
  for(int D = 0; D <8; D++) {
    c25[D]->Print("DEMP_reco_test_10on100.pdf");};
  for(int D = 0; D <8; D++) {
    c26[D]->Print("DEMP_reco_test_10on100.pdf");};
  c1a->Print("DEMP_reco_test_10on100.pdf]");
 
  //----------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
  ofile->Write(); // Write histograms to file
  ofile->Close(); // Close output file
}
