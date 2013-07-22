function c=resolvante_produit_sym(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('resolvante_produit_sym',a,b)

endfunction
