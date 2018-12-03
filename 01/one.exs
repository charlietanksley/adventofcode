defmodule FrequencyChange do
  defstruct [:direction, :size]
end

defmodule Main do
  def read_change(line) do
    %FrequencyChange{
      direction: String.first(line),
      size: String.slice(line, 1..-2) |> String.to_integer()
    }
  end

  def perform_offset(change, acc) do
    case change.direction do
      "+" -> acc + change.size
      "-" -> acc - change.size
    end
  end

  def final_offset(changes) do
    Enum.reduce(changes, 0, fn change, acc -> perform_offset(change, acc) end)
  end

  def first_repeat_offset(changes) do
    cycled_changes = Stream.cycle(changes)

    Enum.reduce_while(
      cycled_changes,
      {0, MapSet.new()},
      fn change, {offset, results} ->
        new_offset = perform_offset(change, offset)

        if MapSet.member?(results, new_offset) do
          {:halt, new_offset}
        else
          {:cont, {new_offset, MapSet.put(results, new_offset)}}
        end
      end
    )
  end

  def main do
    filename = "../input/01-01.txt"
    opened_file = File.stream!(filename)
    processed = Enum.map(opened_file, fn x -> read_change(x) end)
    File.close(opened_file)

    IO.puts("Part 1: #{final_offset(processed)}")
    IO.puts("Part 2: #{inspect(first_repeat_offset(processed))}")
  end
end

Main.main()
