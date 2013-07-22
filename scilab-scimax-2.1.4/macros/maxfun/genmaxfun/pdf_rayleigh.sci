function c=pdf_rayleigh(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('pdf_rayleigh',a,b)

endfunction
