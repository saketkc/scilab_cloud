function a=%sym_eval()

if argn(2)~=0 then error(42), end
a=maxevalf('eval')

endfunction
