function b=%sym_asec(a)

if argn(2)~=1 then error(42), end
b=maxevalf('asec',a)

endfunction
