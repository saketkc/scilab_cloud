function d=residue(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('residue',a,b,c)

endfunction
