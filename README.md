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
