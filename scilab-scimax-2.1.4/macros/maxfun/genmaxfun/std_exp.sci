function b=std_exp(a)

if argn(2)~=1 then error(42), end
b=maxevalf('std_exp',a)

endfunction
