function d=pdf_continuous_uniform(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('pdf_continuous_uniform',a,b,c)

endfunction
