#!/usr/bin/env python

import subprocess
import sys

subprocess.call("mAIDA.exe -v -i final_state_files/os/fs_tt0_os.root.1 -o var_files/os/tt0_os.root.1",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/os/fs_tt0_os.root.2 -o var_files/os/tt0_os.root.2",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/os/fs_tt0_os.root.3 -o var_files/os/tt0_os.root.3",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/os/fs_tt0_os.root.4 -o var_files/os/tt0_os.root.4",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/os/fs_tt0_os.root.5 -o var_files/os/tt0_os.root.5",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/os/fs_ttW_os.root.1 -o var_files/os/ttW_os.root.1",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/os/fs_ttZ_os.root.1 -o var_files/os/ttZ_os.root.1",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/os/fs_ttZ_os.root.2 -o var_files/os/ttZ_os.root.2",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/os/fs_ttZ_os.root.3 -o var_files/os/ttZ_os.root.3",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/os/fs_WZ_os.root.1  -o var_files/os/WZ_os.root.1", shell=True)

subprocess.call("mAIDA.exe -v -i final_state_files/ss/fs_tt0_ss.root.1 -o var_files/ss/tt0_ss.root.1",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/ss/fs_tt0_ss.root.2 -o var_files/ss/tt0_ss.root.2",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/ss/fs_tt0_ss.root.3 -o var_files/ss/tt0_ss.root.3",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/ss/fs_tt0_ss.root.4 -o var_files/ss/tt0_ss.root.4",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/ss/fs_tt0_ss.root.5 -o var_files/ss/tt0_ss.root.5",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/ss/fs_ttW_ss.root.1 -o var_files/ss/ttW_ss.root.1",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/ss/fs_ttZ_ss.root.1 -o var_files/ss/ttZ_ss.root.1",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/ss/fs_ttZ_ss.root.2 -o var_files/ss/ttZ_ss.root.2",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/ss/fs_ttZ_ss.root.3 -o var_files/ss/ttZ_ss.root.3",shell=True)
subprocess.call("mAIDA.exe -v -i final_state_files/ss/fs_WZ_ss.root.1  -o var_files/ss/WZ_ss.root.1", shell=True)

