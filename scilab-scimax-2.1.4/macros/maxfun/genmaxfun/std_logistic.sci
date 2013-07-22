function c=std_logistic(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('std_logistic',a,b)

endfunction
