//contextwindow.cpp -- NAC 2026 Challenge
//problem: Context Window (linear)
//04-10-2026
//comments intentionally removed for this assignment

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const long long INF = 1e18;

// Using a dynamic programming technique that maintains two sliding windows,
// compute the minimum required cost needed to summarize the LLM's context
// window in keep the window under a maximum size.
void solve()
{
    long long N, W;
    cin >> N >> W;

    // Read in the message length in tokens.
    vector<long long> L(N + 1, 0);

    // Compute the prefix sum on this list. This will be used to efficiently
    // compute sums of arbitrary ranges in the list of tokens.
    vector<long long> P(N + 1, 0);
    for (long long i = 1; i <= N; i++)
    {
        cin >> L[i];
        P[i] = P[i - 1] + L[i];
    }

    // dp holds the number of times the context window needed to be summarized
    // In short, consider a position i in the stream of token message lengths.
    // If you absolutely cannot fit every message without summarizing every
    // token before the i'th position, dp[i] is the number of times you'd need
    // to compress it.
    vector<long long> dp(N + 1, INF);
    dp[0] = 0;

    // dq usually holds up to 2 values at a time, representing the index range
    // of the current context window that has not been summarized.
    deque<int> dq;
    dq.push_back(0);

    long long j_min = 0;

    // Main yield: compute dp. This is accomplished by maintaining a sliding
    // window over the list of message lengths. The window grows as far as it
    // can before needing summarization; once that's needed, the left bar shifts
    // to the right only as much as needed to make the context window shorter
    // and a summarization event is recorded in dp.
    // Then, one of two things happens:
    // - If we couldn't summarize enough, then j_min == i and we've failed, a
    //   condition that propagates through the full code by emptying dq.
    // - We maintain an end value `end` that increments along with i.
    // - We maintain a minimum value `begin` that marks how much extra we could
    //   summarize from the previous window before needing another summarization
    //   event.
    // - If the window didn't shrink, set dp[i] to the number of summarizations
    //   needed for dp[begin] plus one.
    // - We maintain a value `end` which always updates to i if the solution is
    //   not intractable.
    for (long long i = 1; i <= N; i++)
    {
        // Increment j_min while the sum of the tokens between j_min and i is
        // below the maximum context window length.
        // Note that the following expressions are equivalent:
        // - $9 * P[j_min] < 10 * (P[i] - W)$
        // - $10 * (P[i] - P[j_min] - W) + P[j_min] > 0$
        // - $(P[i] - P[j_min] - W) + P[j_min] / 10 > 0$
        // - $(P[i] - P[j_min] + P[j_min] / 10) - W > 0$
        // Effectively, the algorithm marches j_min forward ONLY as far as
        // necessary to ensure the total token cost doesn't exceed W. It is
        // rephrased to reduce the number of operations needed.
        while (j_min < i && 9 * P[j_min] < 10 * (P[i] - W)) {
            j_min++;
        }

        // If j_min was updated, clear out first entries of dq until a value
        // greater than j_min is found. This effectively amounts to putting the
        // second value in the dq into the first slot. If j_min == i, meaning no
        // summarization can be done before adding P[i] to the context window
        // without extending past W, then the dq is emptied.
        // NOTABLY this only occurs when j_min extends past where i was first
        // inserted, that is, if a new summarization event needs to take place
        // or if the previous one could be "modified" to summarize more than
        // what was locally minimum at the time.
        while (!dq.empty() && dq.front() < j_min)
        {
            dq.pop_front();
        }

        // If the dq is emptied, we've failed. Otherwise, increase the minimum
        // number of times needed to summarize if we need to summarize before
        // the i'th position.
        if (!dq.empty())
        {
            dp[i] = dp[dq.front()] + 1;
        }
        else
        {
            dp[i] = INF;
        }

        // If we haven't failed, shift right position in dq to the right. This
        // amounts to increasing the current window one can acquire in the
        // context window that hasn't been summarized yet.
        if (dp[i] != INF)
        {
            dq.push_back(i);
        }
    }

    // Determine the minimum number of elements that need summarization for the
    // stream of messages.
    long long final_j_min = 0;
    while (final_j_min <= N && 9 * P[final_j_min] < 10 * (P[N] - W))
    {
        final_j_min++;
    }

    long long min_total_cost = INF;

    // Compute the cost based on the minimum number of times needed to summarize
    // every element before final_j_min as computed above.
    if (final_j_min <= N && dp[final_j_min] != INF)
        min_total_cost = 100LL * dp[final_j_min] + P[final_j_min];

    // Output one line per test case.
    if (min_total_cost == INF)
        cout << "IMPOSSIBLE\n";
    else
        cout << min_total_cost << "\n";
}

int main()
{
    int t;
    cin >> t;

    // Run all t test cases.
    for (int tc = 0; tc < t; ++tc)
    {
        solve();
    }
    return 0;
}

