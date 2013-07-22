function c=mat_function(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('mat_function',a,b)

endfunction
