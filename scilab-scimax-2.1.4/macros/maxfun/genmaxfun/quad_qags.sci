function g=quad_qags(a,b,c,d,e,f)

if argn(2)~=6 then error(42), end
g=maxevalf('quad_qags',a,b,c,d,e,f)

endfunction
