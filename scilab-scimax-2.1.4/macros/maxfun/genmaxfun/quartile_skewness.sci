function b=quartile_skewness(a)

if argn(2)~=1 then error(42), end
b=maxevalf('quartile_skewness',a)

endfunction
