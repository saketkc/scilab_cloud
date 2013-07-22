function d=pdf_gumbel(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('pdf_gumbel',a,b,c)

endfunction
