#include "FinalStateFiller.h"

int main()
{
  mAIDA::FinalStateFiller fsf("out.root","fs");
  fsf.AddFile("../IMLA/data/ttbar0/*.root");
  fsf.Make_ssdilepton();
  fsf.Loop();
  return 0;
}
