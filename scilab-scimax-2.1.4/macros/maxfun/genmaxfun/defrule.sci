function d=defrule(a,b,c)

if argn(2)~=3 then error(42), end
d=maxevalf('defrule',a,b,c)

endfunction
