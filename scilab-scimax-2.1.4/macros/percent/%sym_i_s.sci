function e=%sym_i_s(a,b,c,d)
rhs=argn(2)
if rhs==3
e=sym(c)
e.rep(a)=b.rep
else
e=sym(d)
e.rep(a,b)=c.rep
end
endfunction
