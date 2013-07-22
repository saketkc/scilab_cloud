function e=implicit_derivative(a,b,c,d)

if argn(2)~=4 then error(42), end
e=maxevalf('implicit_derivative',a,b,c,d)

endfunction
