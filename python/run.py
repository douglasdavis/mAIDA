#!/usr/bin/env python

import subprocess
import sys

def zz():
    subprocess.call("bin/mAIDA.exe -f -d data/ttbar0 -o zz_ttbar0_ssdilepton.root --ssdilepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarW -o zz_ttbarW_ssdilepton.root --ssdilepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarZ -o zz_ttbarZ_ssdilepton.root --ssdilepton",shell=True)

    subprocess.call("bin/mAIDA.exe -f -d data/ttbar0 -o zz_ttbar0_osdilepton.root --osdilepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarW -o zz_ttbarW_osdilepton.root --osdilepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarZ -o zz_ttbarZ_osdilepton.root --osdilepton",shell=True)

    subprocess.call("bin/mAIDA.exe -f -d data/ttbar0 -o zz_ttbar0_trilepton.root --trilepton",  shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarW -o zz_ttbarW_trilepton.root --trilepton",  shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarZ -o zz_ttbarZ_trilepton.root --trilepton",  shell=True)

    subprocess.call("bin/mAIDA.exe -f -d data/ttbar0 -o zz_ttbar0_fourlepton.root --fourlepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarW -o zz_ttbarW_fourlepton.root --fourlepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d data/ttbarZ -o zz_ttbarZ_fourlepton.root --fourlepton",shell=True)

def v():
    subprocess.call("bin/mAIDA.exe -v -i zz_ttbar0_ssdilepton.root -o ttbar0ssdilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i zz_ttbarW_ssdilepton.root -o ttbarWssdilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i zz_ttbarZ_ssdilepton.root -o ttbarZssdilepton.root",shell=True)

    subprocess.call("bin/mAIDA.exe -v -i zz_ttbar0_osdilepton.root -o ttbar0osdilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i zz_ttbarW_osdilepton.root -o ttbarWosdilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i zz_ttbarZ_osdilepton.root -o ttbarZosdilepton.root",shell=True)

    subprocess.call("bin/mAIDA.exe -v -i zz_ttbar0_trilepton.root -o ttbar0trilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i zz_ttbarW_trilepton.root -o ttbarWtrilepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i zz_ttbarZ_trilepton.root -o ttbarZtrilepton.root",shell=True)
    
    subprocess.call("bin/mAIDA.exe -v -i zz_ttbar0_fourlepton.root -o ttbar0fourlepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i zz_ttbarW_fourlepton.root -o ttbarWfourlepton.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i zz_ttbarZ_fourlepton.root -o ttbarZfourlepton.root",shell=True)

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
