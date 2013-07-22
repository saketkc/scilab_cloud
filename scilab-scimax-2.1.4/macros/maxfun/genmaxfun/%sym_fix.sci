function b=%sym_fix(a)

if argn(2)~=1 then error(42), end
b=maxevalf('fix',a)

endfunction
