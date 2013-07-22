function d=pdf_negative_binomial(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('pdf_negative_binomial',a,b,c)

endfunction
