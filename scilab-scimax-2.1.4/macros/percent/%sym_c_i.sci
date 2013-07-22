function c=%sym_c_i(a,b)
c=sym(b)
c=mlist(['sym','t','rep'],'M',[a.rep,c.rep])
endfunction
