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

### Day 5

1. I wish I had known that there are methods for `isLower` and
   `downcase` in the standard library.
1. The functions that work on pointers to strings are kind of blowing
   my mind.
1. My memory management is really going to bite me soon.

### Day 6

This one was a bit of a challenge. I think it could've been a lot
smoother. I liked being able to write more functions. I still really
want to figure out how to pull the file reading thing out into a
function. And I need to get my head around things like `qsort`,
because that is going to be better than my manual methods.

1. I *really* wanted to be able to look into using Voronoi diagrams to
   determine the edges of each region, but I don't think that would've
   been useful for part 2, so I guess it's best I didn't spend time to
   implement that algorithm.
