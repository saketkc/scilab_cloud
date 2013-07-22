function d=solve_rec_rat(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('solve_rec_rat',a,b,c)

endfunction
