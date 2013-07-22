function d=fourier(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('fourier',a,b,c)

endfunction
