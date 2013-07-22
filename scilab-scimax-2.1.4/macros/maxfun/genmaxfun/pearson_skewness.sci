function b=pearson_skewness(a)

if argn(2)~=1 then error(42), end
b=maxevalf('pearson_skewness',a)

endfunction
