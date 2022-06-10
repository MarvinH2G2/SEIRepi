// @MarvinH2_G2, following
// https://www.cse-lab.ethz.ch/wp-content/uploads/2013/02/aron_schwartz_seasonality_pdblng_epidemic_model_JTB1984.pdf

#include <stdio.h>
#include <math.h>
#include <unistd.h>

class SEIR
{
public:
  double eps;
  double dt;

  double mu;
  double alpha;
  double beta_0;
  double beta_1;
  double gamma;
  double rho;
  
  double S;
  double E;
  double I;
  double R;
  double t;
  double T;

  SEIR(long seed,double _eps,double _dt,double _mu,double _alpha,double _beta_0,double _gamma,double _beta_1,double _rho)
    : eps(_eps), dt(_dt), mu(_mu), alpha(_alpha), beta_0(_beta_0), beta_1(_beta_1), gamma(_gamma), rho(_rho)
  {
    srand48(seed);

    t=0;

    T=1; // Forcing period: units of time are 1 = year

    double patientzero=0.1; // Initial infected

    // Initial epidemic
    I=patientzero;
    S=1-patientzero;
    E=0;
    R=0;
  }
  double uniform(void)
  {
    return drand48();
  }
  double Beta(void) { return beta_0*(1.0 + beta_1*cos(2*M_PI*t) + eps*uniform());}
  void step(double delta_t,int print)
  {
    // Simple dumb integrator. Just use a small timestep
    double tt=t+delta_t;
    printf("#t S E I R Beta(t) \n");
    while ( t< tt) {
      double b = Beta();
      double Rt = b *alpha/(mu+alpha)/(mu+gamma);
      double BSI = b*S*I;
      double dS = mu - BSI - mu * S + rho*R;
      double dE = BSI - (mu+alpha)*E;
      double dI = alpha*E - (mu+gamma)*I;
      S=S+dS*dt;
      E=E+dE*dt;
      I=I+dI*dt;
      R=1.0-S-E-I;
      t=t+dt;
      if(print) printf("%le %le %le %le %le %le\n",t,S,E,I,R,Rt);
    }
  }
};

int main(int argc, char **argv)
{
  long seed = 2000;
  double eps = 0.0;      // Can add a small amount of noise if desired
  double dt  = 0.01/365.0;// 0.1 day timestep
#ifdef COVID_PARAMS
  //  suspect "mean" in paper is exponential lifetime sense given the ODEs
  double  mu = 0.02;     // birth/death rate: reciprocal mean life span 1/0.015 = 50 years; 
  double alpha= 180.0;   // 1/alpha is mean latent period ; 2 days = 180 ;
  double gamma= 60.0; // 1/gamma is mean infectious period 365/75 = 5 days
  double rho  = 2;    // 1/rho   is mean waning time, 1/2 year

  double R0=10.0; // R0 value
  double beta_0 = R0 *(mu+alpha)*(mu+gamma)/alpha;
  double beta_1=0.2;
#else
  double  mu = 0.02;     // birth/death rate: reciprocal mean life span 1/0.015 = 50 years; 
  double alpha= 35.84;   // 1/alpha is mean latent period ; 2 days = 180 ;
  double gamma= 100; // 1/gamma is mean infectious period 365/75 = 5 days
  double rho  = 0;    // 1/rho   is mean waning time, 1/4 year
  double beta_0 = 1800;
  double R0= beta_0*alpha/(mu+alpha)/(mu+gamma);
  double beta_1=.2685;
#endif
  printf("# mu    = %le\n",mu);
  printf("# alpha = %le\n",alpha);
  printf("# beta_0  = %le\n",beta_0);
  printf("# gamma = %le\n",gamma);
  printf("# beta_1= %le\n",beta_1);
  printf("# R0    = %le\n",R0);
  double S0= (mu+alpha)*(mu+gamma)/alpha/beta_0;
  double I0= mu*(R0-1)/beta_0;
  double E0= (mu+gamma)/alpha*I0;
  printf("# Steady state : S0 %le E0 %le I0 %le R %le ",S0,E0,I0,1.0-S0-E0-I0);
  SEIR model(seed,eps,dt,mu,alpha,beta_0,gamma,beta_1,rho);
  model.step(1000.0,0);// let it settle 
  model.step(40.0,1);
}
