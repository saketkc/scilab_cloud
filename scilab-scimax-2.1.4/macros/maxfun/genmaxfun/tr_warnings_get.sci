function a=tr_warnings_get()

if argn(2)~=0 then error(42), end
a=maxevalf('tr_warnings_get')

endfunction
