function a=gnuplot_close()

if argn(2)~=0 then error(42), end
a=maxevalf('gnuplot_close')

endfunction
