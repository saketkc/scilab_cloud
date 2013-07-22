function e=lsquares_residual_mse(a,b,c,d)

if argn(2)~=4 then error(42), end
e=maxevalf('lsquares_residual_mse',a,b,c,d)

endfunction
