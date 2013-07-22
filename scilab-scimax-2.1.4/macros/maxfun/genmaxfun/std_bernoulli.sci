function b=std_bernoulli(a)

if argn(2)~=1 then error(42), end
b=maxevalf('std_bernoulli',a)

endfunction
