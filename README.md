# SEIRepi
Simple SEIR (and waning addition) code

Modelled on:

https://www.cse-lab.ethz.ch/wp-content/uploads/2013/02/aron_schwartz_seasonality_pdblng_epidemic_model_JTB1984.pdf

# Regression checks:

1) reproduce paper figure 6b) as paper-fig6.pdf

```
g++ seir.cc -UCOVID_PARAMS -o seir_paper

./seir_paper > paper.data

gnuplot paper-fig6.gnu
```

The code runs for 1000 years, then prints the time evolution for 40 years.

Figure 6b) is a limit cycle of the the SEIR system, a repeating pattern it falls into
after long time evolution (1000 years is enough for early transient initial to die away).

The 'orbit' in Infected vs Susceptible is complicated, but repeats itself periodically with
several period doublings. This process of period doubling bifurcation
up to a limit where chaos sets in a common attribute of chaotic systems.

2) edit seir.cc and set beta_1 line 93 to zero
Predicted steady state (no-seasonality) is an algebraic prediction, printed as S0, E0, I0 etc...

This is reproduced.

# Predictions:

3) Add 6 months waning and set to my best guess at COVID epi params: produces covid.pdf

```
g++ seir.cc -DCOVID_PARAMS -o seir_covid

./seir_covid > coid.data

gnuplot covid.gnu
```

I increased beta_1 all the way to 1 without seeing period doubling for waning time constants at 3 months, 6 months, 12 months.

Good news: no evidence of chaos with reasonable covid waning

Bad news: this looks to be because waning is so fast there is always a reasonable pool of susceptible and persistent rates of infection.

Note: waning time is an input to the model. Garbage in garbage out caveats apply, but immunity waning is now established.


