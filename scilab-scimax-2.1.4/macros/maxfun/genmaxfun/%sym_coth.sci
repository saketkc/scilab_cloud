function b=%sym_coth(a)

if argn(2)~=1 then error(42), end
b=maxevalf('coth',a)

endfunction
