function b=%sym_diag(a)

if argn(2)~=1 then error(42), end
b=maxevalf('diag',a)

endfunction
