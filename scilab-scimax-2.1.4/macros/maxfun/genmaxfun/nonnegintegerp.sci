function b=nonnegintegerp(a)

if argn(2)~=1 then error(42), end
b=maxevalf('nonnegintegerp',a)

endfunction
