#ifdef __cplusplus
extern "C" {
#endif
#include <mex.h> 
#include <sci_gateway.h>
#include <api_scilab.h>
#include <MALLOC.h>
static int direct_gateway(char *fname,void F(void)) { F();return 0;};
extern Gatefunc sci_maxinit;
extern Gatefunc sci_maxkill;
extern Gatefunc sci_maxevalf;
extern Gatefunc sci_maxevalfl;
extern Gatefunc sci_maxprint;
extern Gatefunc sci_sym;
extern Gatefunc sci_Matrix;
extern Gatefunc sci_symnp;
extern Gatefunc sci_defmf;
extern Gatefunc sci_Syms;
extern Gatefunc sci_latex;
extern Gatefunc sci_mathml;
extern Gatefunc sci_answer;
extern Gatefunc sci_noanswer;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
extern Gatefunc sci_maxevalop;
static GenericTable Tab[]={
  {(Myinterfun)sci_gateway,sci_maxinit,"maxinit"},
  {(Myinterfun)sci_gateway,sci_maxkill,"maxkill"},
  {(Myinterfun)sci_gateway,sci_maxevalf,"maxevalf"},
  {(Myinterfun)sci_gateway,sci_maxevalfl,"maxevalfl"},
  {(Myinterfun)sci_gateway,sci_maxprint,"%sym_p"},
  {(Myinterfun)sci_gateway,sci_sym,"sym"},
  {(Myinterfun)sci_gateway,sci_Matrix,"Matrix"},
  {(Myinterfun)sci_gateway,sci_symnp,"symnp"},
  {(Myinterfun)sci_gateway,sci_defmf,"defmf"},
  {(Myinterfun)sci_gateway,sci_Syms,"Syms"},
  {(Myinterfun)sci_gateway,sci_latex,"latex"},
  {(Myinterfun)sci_gateway,sci_mathml,"mathml"},
  {(Myinterfun)sci_gateway,sci_answer,"answer"},
  {(Myinterfun)sci_gateway,sci_noanswer,"noanswer"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopA"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopB"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopC"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopD"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopE"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopF"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopG"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopH"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopI"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopJ"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopK"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopL"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopM"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopN"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopO"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopP"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopQ"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopR"},
  {(Myinterfun)sci_gateway,sci_maxevalop,"maxevalopS"},
};
 
int C2F(libmaxima)()
{
  Rhs = Max(0, Rhs);
  if (*(Tab[Fin-1].f) != NULL) 
  {
     if(pvApiCtx == NULL)
     {
       pvApiCtx = (StrCtx*)MALLOC(sizeof(StrCtx));
     }
     pvApiCtx->pstName = (char*)Tab[Fin-1].name;
    (*(Tab[Fin-1].f))(Tab[Fin-1].name,Tab[Fin-1].F);
  }
  return 0;
}
#ifdef __cplusplus
}
#endif
