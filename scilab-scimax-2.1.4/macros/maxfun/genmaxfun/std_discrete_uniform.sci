function b=std_discrete_uniform(a)

if argn(2)~=1 then error(42), end
b=maxevalf('std_discrete_uniform',a)

endfunction
