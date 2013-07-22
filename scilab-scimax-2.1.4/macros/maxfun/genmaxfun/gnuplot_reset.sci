function a=gnuplot_reset()

if argn(2)~=0 then error(42), end
a=maxevalf('gnuplot_reset')

endfunction
