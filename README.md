# SEIRepi
Simple SEIR (and waning addition) code

Modelled on:

https://www.cse-lab.ethz.ch/wp-content/uploads/2013/02/aron_schwartz_seasonality_pdblng_epidemic_model_JTB1984.pdf

# Regression checks:

1) reproduce paper figure 6b) as paper-fig6.pdf

g++ seir.cc -UCOVID_PARAMS -o seir_paper

./seir_paper > paper.data

gnuplot paper-fig6.gnu

2) edit seir.cc and set beta_1 line 93 to zero
Predicted steady state (no-seasonality) is an algebraic prediction, printed as S0, E0, I0 etc...

This is reproduced.

# Predictions:

3) Add 6 months waning and set to my best guess at COVID epi params: produces covid.pdf

g++ seir.cc -DCOVID_PARAMS -o seir_covid

./seir_covid > coid.data

gnuplot covid.gnu


