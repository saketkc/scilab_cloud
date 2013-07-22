function b=%sym_mean(a)

if argn(2)~=1 then error(42), end
b=maxevalf('mean',a)

endfunction
