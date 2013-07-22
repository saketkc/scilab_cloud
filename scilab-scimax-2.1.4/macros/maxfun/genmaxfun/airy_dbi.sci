function b=airy_dbi(a)

if argn(2)~=1 then error(42), end
b=maxevalf('airy_dbi',a)

endfunction
