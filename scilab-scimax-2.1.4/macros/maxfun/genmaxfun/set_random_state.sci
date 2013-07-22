function b=set_random_state(a)

if argn(2)~=1 then error(42), end
b=maxevalf('set_random_state',a)

endfunction
