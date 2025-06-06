# ePIC DEMP Analysis

Analysis and scripts for the anlysis of Deep Exclusive Meson Production (DEMP) events in the ePIC detector at the EIC.

This repository is based upon earlier work by Love Preet at the University of Regina - https://github.com/Lovepreet6/DEMP_pion_analysis

Currently, the main analysis script works for DEMP pion events. In future, the capability to analyse DEMP kaon events will be added.

The main script is the DEMP_Analysis.C script. Instructions on running this script are provided upon executin via -

root -l DEMP_Analysis.C

Note that this script looks for input files under "InputFiles" in this directory. The intention is that this is a sym link to a folder containing your files -

ln -s YOUR_DIRECTORY_PATH InputFiles