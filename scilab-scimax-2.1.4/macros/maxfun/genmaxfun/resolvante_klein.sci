function c=resolvante_klein(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('resolvante_klein',a,b)

endfunction
