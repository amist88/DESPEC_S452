#include "TimingCube.h"

TimingCube::TimingCube (TGo4EventProcessor *evp)
{
        this->evp = evp;
}


THnSparseD* TimingCube::MakeHnSparse(const char* foldername, const char* name, const char* title,
                                          int dim, int *bins, double *xmin, double *xmax)
{
  THnSparseD* smat = new THnSparseD(name, title, dim, bins, xmin, xmax);
  evp->AddObject(smat, foldername);
  return smat;
}
