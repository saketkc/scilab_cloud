function e=%p_i_sym(a,b,c,d)
rhs=argn(2)
if rhs==3
e=sym(b)
c.rep(a)=e.rep
e=c
else
e=sym(c)
d.rep(a,b)=e.rep
e=d
end
endfunction
