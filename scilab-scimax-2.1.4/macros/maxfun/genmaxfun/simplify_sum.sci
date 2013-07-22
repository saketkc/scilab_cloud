function b=simplify_sum(a)

if argn(2)~=1 then error(42), end
b=maxevalf('simplify_sum',a)

endfunction
