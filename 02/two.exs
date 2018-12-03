defmodule Main do
  def count_letters(string) do
    String.trim(string)
    |> String.codepoints()
    |> Enum.reduce(%{}, fn char, acc ->
      case Map.get(acc, char, 0) do
        0 -> Map.put(acc, char, 1)
        _ -> %{acc | char => acc[char] + 1}
      end
    end)
  end

  def part_one do
    filename = "../input/02-full.txt"
    opened_file = File.stream!(filename)

    checksum =
      Enum.map(opened_file, fn x -> count_letters(x) end)
      |> Enum.reduce(%{2 => 0, 3 => 0}, fn map, acc ->
        Map.keys(acc)
        |> Enum.reduce(acc, fn key, acc2 ->
          if Enum.any?(Map.values(map), fn val -> val == key end) do
            %{acc2 | key => acc2[key] + 1}
          else
            acc2
          end
        end)
      end)
      |> Enum.reduce(1, fn {_, v}, acc -> acc * v end)

    IO.puts("Checksum: #{checksum}")

    File.close(opened_file)
  end
end

Main.part_one()

#   def part_two do
#     filename = "../input/02-test-two.txt"
#     opened_file = File.stream!(filename)

#     box_ids =
#       Enum.map(opened_file, fn line -> String.trim(line) end)
#       |> Enum.sort()
#       |> Enum.with_index()

#     b =
#       Enum.map(box_ids, fn {str, index} ->
#         neighbor =
#           Enum.at(box_ids, index + 1)
#           |> Tuple.to_list()
#           |> List.first()
#           |> String.codepoints()

#         Enum.zip(String.codepoints(str), neighbor)
#       end)

#     IO.puts("Box IDs: #{inspect(b)}")

#     File.close(opened_file)
#   end
# end
