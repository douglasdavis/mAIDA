#!/usr/bin/env python

import subprocess
import sys

def zz():
    subprocess.call("bin/mAIDA.exe -f -d data/ttbar0 -o rootfiles/zz_ttbar0_ssdilepton.root --ssdilepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarW -o rootfiles/zz_ttbarW_ssdilepton.root --ssdilepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarZ -o rootfiles/zz_ttbarZ_ssdilepton.root --ssdilepton",shell=True)

    subprocess.call("bin/mAIDA.exe -f -d data/ttbar0 -o rootfiles/zz_ttbar0_osdilepton.root --osdilepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarW -o rootfiles/zz_ttbarW_osdilepton.root --osdilepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarZ -o rootfiles/zz_ttbarZ_osdilepton.root --osdilepton",shell=True)

    subprocess.call("bin/mAIDA.exe -f -d data/ttbar0 -o rootfiles/zz_ttbar0_trilepton.root --trilepton",  shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarW -o rootfiles/zz_ttbarW_trilepton.root --trilepton",  shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarZ -o rootfiles/zz_ttbarZ_trilepton.root --trilepton",  shell=True)

    subprocess.call("bin/mAIDA.exe -f -d data/ttbar0 -o rootfiles/zz_ttbar0_fourlepton.root --fourlepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarW -o rootfiles/zz_ttbarW_fourlepton.root --fourlepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarZ -o rootfiles/zz_ttbarZ_fourlepton.root --fourlepton",shell=True)

def v():
    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbar0_ssdilepton.root -o rootfiles/ttbar0ssdilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbarW_ssdilepton.root -o rootfiles/ttbarWssdilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbarZ_ssdilepton.root -o rootfiles/ttbarZssdilepton.root",shell=True)

    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbar0_osdilepton.root -o rootfiles/ttbar0osdilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbarW_osdilepton.root -o rootfiles/ttbarWosdilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbarZ_osdilepton.root -o rootfiles/ttbarZosdilepton.root",shell=True)

    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbar0_trilepton.root -o rootfiles/ttbar0trilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbarW_trilepton.root -o rootfiles/ttbarWtrilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbarZ_trilepton.root -o rootfiles/ttbarZtrilepton.root",shell=True)
    
    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbar0_fourlepton.root -o rootfiles/ttbar0fourlepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbarW_fourlepton.root -o rootfiles/ttbarWfourlepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i rootfiles/zz_ttbarZ_fourlepton.root -o rootfiles/ttbarZfourlepton.root",shell=True)

def main():
    if sys.argv[1] == '-zz':
        zz()
    if sys.argv[1] == '-v':
        v()
    if sys.argv[1] == '-zzv':
        zz()
        v()

if __name__ == '__main__':
    main()
