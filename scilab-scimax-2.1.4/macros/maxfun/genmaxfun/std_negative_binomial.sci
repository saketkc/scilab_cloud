function c=std_negative_binomial(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('std_negative_binomial',a,b)

endfunction
