# Memory Hungry

**Time Limit: 2 seconds, Memory Limit: 1024 MB**

You're yet another inconspicuous AI startup with a tight budget. You've
invented a new LLM model that you think will outperform all the leading models
on the market. Unfortunately, your server consists of a 12-year-old ThinkPad
laptop running CentOS that you dug out of a dumpster, and you don't have any
kidneys to spare for extra RAM, so you need to run this model in an optimal way
such as to reduce memory usage while keeping the LLM running for all three of
your customers.

Your agent reads $N$ messages in order. Message $i$ has length $S_i$ tokens,
and each $S_i$ is a multiple of $K$. The agent stores all messages received so
far in the order given. At all points in time, a (potentially empty) prefix of
messages is reduced, while a (potentially empty) suffix of messages is not
reduced. The length of a reduced message is $\frac{S_i}{K}$ tokens,
instead of $S_i$.

<!--
The agent has an internal buffer called its context window. Every message that
arrives increases the size of the context window by $S_i$. If $C$ is the size
of the current context window, the cost for storing it in memory after that
message arrives is $C$.
-->

After every message arrives, the agent can _reduce_ a prefix of
messages that is not yet reduced. The cost of reducing messages with
lengths $S_i, S_{i+1}, ..., S_p$ is \[64 + \sum_{n=i}^p 2S_i\]

The agent may perform any number of reduce operations between receiving
messages. After every message arrival, the total context length must be at most
$W$ tokens.

Among all ways to reduce messages, find the one with minimum total cost,
where the total length never exceeds $W$ at any point in time. If this is
impossible, instead output `DOWNLOAD MORE RAM`.

## Input

The first line of input contains an integer $t\ (1\leq t \leq 10000)$, the number of test cases.
Each test case contains two lines.
The first line of each test case contains 3 integers $N\ (1\leq N\leq10^5)$, $W\ (1\leq W\leq 10^{18})$, and $K\ (2\leq K\leq 100)$.
The second line contains N integers $S_1, S_2, \dots, S_N$, the lengths of the messages in the order they arrive. It is guaranteed that $S_i \equiv 0\pmod{K}$. In other words, $S_i$ is a multiple of $K$, and $\frac{S_i}{K}$ is therefore always an integer.

## Output

For each test case, print an integer: the minimum possible cost if it reduces messages optimally. If it is impossible to do this without exceeding $W$, output `DOWNLOAD MORE RAM`.

| Sample Input | Sample Output |
| --- | --- |
| ```[input]``` | ```[output]``` |
