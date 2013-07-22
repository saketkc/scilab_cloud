function b=airy_bi(a)

if argn(2)~=1 then error(42), end
b=maxevalf('airy_bi',a)

endfunction
