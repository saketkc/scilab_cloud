function c=poly_buchberger(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('poly_buchberger',a,b)

endfunction
