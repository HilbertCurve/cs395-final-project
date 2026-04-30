# Things that didn't make it into the final problem, but were considered.

## Cost for maintaining values in memory.

## Polynomial summarization cost.
>>>>>> \sum L_i => \sum f(L_i), where f is polynomial input
>>>>>> $f <= a_0 + a_1 x + a_2 x^2 + \dots + a_n x^n$ (represented as
>>>>>> individual $a_i$): $max\{f\}$

C = 100 + \sum L_i => 100 + f(\sum L_i)



Potential idea: 100 + \sum L_i => C + \max {L_i} (Low prio, could be in report)
