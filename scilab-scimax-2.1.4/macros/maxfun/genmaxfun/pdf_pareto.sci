function d=pdf_pareto(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('pdf_pareto',a,b,c)

endfunction
