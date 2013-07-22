function d=pdf_beta(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('pdf_beta',a,b,c)

endfunction
