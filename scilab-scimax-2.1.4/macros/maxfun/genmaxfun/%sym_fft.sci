function c=%sym_fft(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('fft',a,b)

endfunction
