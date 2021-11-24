#ifndef TIMING_CUBE_H
#define TIMING_CUBE_H

#include <TGo4EventProcessor.h>
#include <TROOT.h>
#include <THnSparse.h>


///*************************************added by MR, Nov 2021***********
//
//  Class which provides a method to add a THnSparse histogram to
//  a TGo4EventProcessor class instance.
//  This type of cube can be used to make memory efficient cubes of
//  gamma-gamma-dt data for example for fast timing analysis.
//
//  Include this class header in the header file of the respective class,
//  like EventUnpackProc, and assign a THnSparseD pointer there. E.g.:
//
//    "
//    double ggtarray[3]; //Will be needed for filling the cube.
//    THnSparseD *ggt;
//    "
//
//  Then add the following lines to the method where the histograms
//  are initialised (example is a typical a 3d gamma-gamma-time cube):
//
//    "
//    TimingCube *tc = new TimingCube(this);  //using the "this" symbol to point to it's own instance
//    int bins[3] = {1000,1000,1600};
//    double xmin[3] = {0,0,-20000};
//    double xmax[3] = {2000,2000,20000};
//    ggt = tc->MakeHnSparse ("foldername", "histname", "histtitle",
//                             3, bins, xmin, xmax);
//    "
//
//  The cube can now be incremented where the histograms are filled.
//  For example in a double loop for an asymmetric GCD cube:
//    "
//    if (ID_i < ID_j) {
//      ggtarray[0] = E_i;
//      ggtarray[0] = E_j;
//      ggtarray[0] = T_i - Tj;
//      ggt->Fill(lltarray);
//    }
//    "
//
//  The cube will not be added to the "Histograms" folder, but to the
//  "UserObjects" folder in the final go4 root file.
//  When using batch processing, like for example with the a
//  Cluster-Submission, hadd will work on these as expected.
//
//  Some useful operations for analysing a THnSparse:
//  ggt->Projection(0)->Draw() will draw first energy axis
//  ggt->Projection(0,1)->Draw("colz") will draw TH2 of axes 0 and 1
//  ggt->GetAxis(0)->SetRangeUser(330,350) to set a gate on axis 0
//  ggt->Projection(2)->Clone("gated_et") will create a TH2D called "gated_et"
//                                          of the 1,2 projection with any gate
//                                          set on axis 0 and 1
///*****************************************************************

class TimingCube {
private:
        TGo4EventProcessor *evp;
public:
        TimingCube(TGo4EventProcessor *evp);
        ~TimingCube(){};
        THnSparseD* MakeHnSparse(const char* foldername, const char* name, const char* title,
                                 int dim, int *bins, double *xmin, double *xmax);
};
#endif
