function c=%sym_f_i(a,b)
c=sym(b)
c=mlist(['sym','t','rep'],'M',[a.rep;c.rep])
endfunction
