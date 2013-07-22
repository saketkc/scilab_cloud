function c=noncentral_moment(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('noncentral_moment',a,b)

endfunction
