# Advent Of Code 2018

## Things I learned

### Day 1

1. I had no idea that `scanf("%d"...` in C (or Elixir though IDK how I
   didn't see it in that case) would give you a positive integer for
   `"+1"` and a negative integer for `"-1"`. That would've *really*
   simplified things for me (not passing around structs).
1. Using an array scan to track whether we've seen a value is so
   slow. I knew it would be, but I didn't realize just how slow until
   I implemented this in C doing it the slow way and then in Elixir
   using a set (well, a `MapSet`).
1. I have a lot to learn but it's all really interesting.

### Day 3

1. I should probably abstract the file reading out now that I'm doing
   that every time.
1. The nested loop over all the coordinates with `< 1` hit for _each_
   of the coordinates in an elf's claim was so costly. Had I not
   otherwise been short on time I might've gone ahead and tried to
   'write' (that is, copy) either a binary tree or linked list to use
   as something like a set. That will probably have to happen soonish.

### Day 4

This one really killed me. The `C` got over my head _fast_ but even
once I switched to Python it was hard for me. I just don't think I
really conceptualized the problem well. For the next one I want to try
to get really clear on the expected inputs and outputs before I start
coding.
