function b=geometric_mean(a)

if argn(2)~=1 then error(42), end
b=maxevalf('geometric_mean',a)

endfunction
