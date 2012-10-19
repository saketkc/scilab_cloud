import subprocess
import os
sciLabProcess = subprocess.Popen('"/usr/bin/scilab-cli " ')
    #bufsize=0, 
    #executable=None, 
    #stdin=None, 
    #stdout=None, 
    #stderr=None, 
    #preexec_fn=None, 
    #close_fds=False, 
    #shell=False, 
    #cwd=None, 
    #env=None, 
    #universal_newlines=False, 
    #startupinfo=None, 
    #creationflags=0)
     
# wait for process to exit, or terminate it
while sciLabProcess.poll() is None:
    print 'still running'
    reply = raw_input("Kill process ? (type yes) ")
    if reply.strip()=='yes':
        sciLabProcess.terminate()
