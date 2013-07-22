function b=%sym_rank(a)

if argn(2)~=1 then error(42), end
b=maxevalf('rank',a)

endfunction
