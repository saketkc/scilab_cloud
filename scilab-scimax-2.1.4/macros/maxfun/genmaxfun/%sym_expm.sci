function b=%sym_expm(a)

if argn(2)~=1 then error(42), end
b=maxevalf('__expm',a)

endfunction
