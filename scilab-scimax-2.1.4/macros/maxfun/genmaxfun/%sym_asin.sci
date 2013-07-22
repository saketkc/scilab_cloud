function b=%sym_asin(a)

if argn(2)~=1 then error(42), end
b=maxevalf('asin',a)

endfunction
