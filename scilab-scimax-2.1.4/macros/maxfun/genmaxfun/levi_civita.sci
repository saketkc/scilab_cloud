function b=levi_civita(a)

if argn(2)~=1 then error(42), end
b=maxevalf('levi_civita',a)

endfunction
