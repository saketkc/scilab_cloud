function a=gnuplot_restart()

if argn(2)~=0 then error(42), end
a=maxevalf('gnuplot_restart')

endfunction
