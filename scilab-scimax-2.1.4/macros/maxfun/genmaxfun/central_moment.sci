function c=central_moment(a,b)

if argn(2)~=2 then error(42), end
c=maxevalf('central_moment',a,b)

endfunction
