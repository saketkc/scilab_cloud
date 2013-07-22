function e=jacobi_p(a,b,c,d)

if argn(2)~=4 then error(42), end
e=maxevalf('jacobi_p',a,b,c,d)

endfunction
