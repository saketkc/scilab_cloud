function b=%sym_median(a)

if argn(2)~=1 then error(42), end
b=maxevalf('median',a)

endfunction
