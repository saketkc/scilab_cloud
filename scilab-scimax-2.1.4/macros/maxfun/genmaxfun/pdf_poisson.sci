function c=pdf_poisson(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('pdf_poisson',a,b)

endfunction
