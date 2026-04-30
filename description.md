# Problem Description

Context Window => ______

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

The agent has an internal buffer called its context window. Every message that
arrives increases the size of the context window by $S_i$. If $C$ is the size
of the current context window, the cost for storing it in memory after that
message arrives is $C$.

After every message arrives, the agent can _reduce_ a prefix of
messages that is not yet reduced. The cost of reducing messages with
lengths $S_i, S_{i+1}, ..., S_p$ is \[64 + \sum_{n=i}^p 2S_i\]

The agent may perform any number of reduce operations between receiving
messages. After every message arrival, the total context length must be at most
$W$ tokens.

Among all ways to reduce messages, find the one with minimum total cost,
where the total length never exceeds $W$ at any point in time. If this is
impossible, instead output `IMPOSSIBLE`.

## Input
K input, integer
N messages, each has size S_i, that is multiple of K
Maximum capacity C, can't exceed

