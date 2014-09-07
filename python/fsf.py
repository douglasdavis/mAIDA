import ROOT
ROOT.gSystem.Load('lib/libmAIDA')
from ROOT import mAIDA

fsf = mAIDA.FinalStateFiller('out.root','fs');
fsf.AddFile('../IMLA/data/ttbarW/*.root');
fsf.Make_osdilepton()
fsf.Loop();
