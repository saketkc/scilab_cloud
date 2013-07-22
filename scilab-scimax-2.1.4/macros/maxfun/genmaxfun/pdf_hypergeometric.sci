function e=pdf_hypergeometric(a,b,c,d)

if argn(2)~=4 then error(42), end
e=maxevalf('pdf_hypergeometric',a,b,c,d)

endfunction
