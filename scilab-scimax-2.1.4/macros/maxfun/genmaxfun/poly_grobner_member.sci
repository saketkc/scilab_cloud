function d=poly_grobner_member(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('poly_grobner_member',a,b,c)

endfunction
