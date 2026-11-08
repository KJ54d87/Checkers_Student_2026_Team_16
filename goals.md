Goals for the first submission:

For the first submission, we want to do a basic implmentation of monte carlo 
trees. Well use a simple heuristic to judge wins/losses.

So what I think needs implementing is:
A node class, stores wins, losses and can generate children.
A monte carlo class
     -construct (beginning node)
     -explore (n_trials, exploration_factor) //conducts a random trials
     -decide //using current tree, make a decision.
