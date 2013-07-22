function b=%sym_acoth(a)

if argn(2)~=1 then error(42), end
b=maxevalf('acoth',a)

endfunction
