function b=%sym_floor(a)

if argn(2)~=1 then error(42), end
b=maxevalf('floor',a)

endfunction
