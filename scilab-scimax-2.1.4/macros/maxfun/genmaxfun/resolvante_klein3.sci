function c=resolvante_klein3(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('resolvante_klein3',a,b)

endfunction
