function d=linear_program(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('linear_program',a,b,c)

endfunction
