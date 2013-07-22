function d=pdf_logistic(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('pdf_logistic',a,b,c)

endfunction
