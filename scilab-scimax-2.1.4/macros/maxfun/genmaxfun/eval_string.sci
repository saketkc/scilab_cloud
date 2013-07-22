function b=eval_string(a)

if argn(2)~=1 then error(42), end
b=maxevalf('eval_string',a)

endfunction
