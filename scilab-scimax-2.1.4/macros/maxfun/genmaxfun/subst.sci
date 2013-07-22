function d=subst(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('subst',a,b,c)

endfunction
