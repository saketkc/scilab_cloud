function d=resolvante_unitaire(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('resolvante_unitaire',a,b,c)

endfunction
