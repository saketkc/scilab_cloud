function a=gnuplot_start()

if argn(2)~=0 then error(42), end
a=maxevalf('gnuplot_start')

endfunction
