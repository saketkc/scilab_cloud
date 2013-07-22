exec loader.sce
Syms xv Qf Qo Cf Co V Qw Kv t s
Qo=Qw+Qf;
// rate of salt inflow
mi=Qf*Cf;
// rate of salt outflow
mo=Qo*Co;
// rate of salt accumulation
ma=diff(V*Co,t);
mi=ma+mo;
Qf*Cf=V*diff(Co,t)+Qo*Co;
Qf=Kv*xv;
K=Cf*Kv/Qo;
G=V/Qo;
G*diff(Co,t)+Co=K*xv;
// taking laplace
G*s*Co+Co=K*xv;
// transfer function= Co/xv
Co/xv=K/(G*s+1);
quit();

//s=%s;
//Syms k
//H=syslin('c',(k*(s+1)*(s+2))/(s*(s+3)*(s+4)));
//evans(H,5)
//printf("There are three branches of root locus starting with K=0 and poles s=0,-3,-4.")
//printf("As k increases two branches terminate at zeros s=-1,-2 and one at infinity")
quit;
