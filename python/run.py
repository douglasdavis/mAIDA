#!/usr/bin/env python

import subprocess
import sys

def f():
    subprocess.call("bin/mAIDA.exe -f -d ../IMLA/data/ttbar0 -o ttbar0f.root --ssdilepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d ../IMLA/data/ttbarW -o ttbarWf.root --ssdilepton",shell=True)
    subprocess.call("bin/mAIDA.exe -f -d ../IMLA/data/ttbarZ -o ttbarZf.root --ssdilepton",shell=True)

def v():
    subprocess.call("bin/mAIDA.exe -v -i ttbar0f.root -o ttbar0v.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i ttbarWf.root -o ttbarWv.root",shell=True)
    subprocess.call("bin/mAIDA.exe -v -i ttbarZf.root -o ttbarZv.root",shell=True)

def main():
    if sys.argv[1] == '-f':
        f()
    if sys.argv[1] == '-v':
        v()
    if sys.argv[1] == '-fv':
        f()
        v()

if __name__ == '__main__':
    main()
