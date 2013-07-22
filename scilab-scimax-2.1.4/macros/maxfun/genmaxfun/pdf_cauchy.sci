function d=pdf_cauchy(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('pdf_cauchy',a,b,c)

endfunction
