function d=%sym_e(a,b,c)
rhs=argn(2)
if rhs==2
d=mlist(['sym','t','rep'],'M',b.rep(a))
else
d=mlist(['sym','t','rep'],'M',c.rep(a,b))
end
endfunction
