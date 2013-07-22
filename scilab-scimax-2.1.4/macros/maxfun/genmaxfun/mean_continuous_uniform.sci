function c=mean_continuous_uniform(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('mean_continuous_uniform',a,b)

endfunction
