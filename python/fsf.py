import ROOT
ROOT.gSystem.Load('lib/libmAIDA')
from ROOT import mAIDA

fsf = mAIDA.FinalStateFiller('out.root','fs');
fsf.AddFile('../IMLA/data/ttbar0/*.root');
fsf.Make_ssdilepton()
fsf.Loop();
