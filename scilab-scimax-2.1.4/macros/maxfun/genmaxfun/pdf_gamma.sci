function d=pdf_gamma(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('pdf_gamma',a,b,c)

endfunction
