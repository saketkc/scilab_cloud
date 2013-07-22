function e=augmented_lagrangian_method(a,b,c,d)

if argn(2)~=4 then error(42), end
e=maxevalf('augmented_lagrangian_method',a,b,c,d)

endfunction
