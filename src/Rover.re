type coordinate = (int, int);
let coordinate_to_string = ((x, y): coordinate) => {j|[$x, $y]|j};

type direction =
  | N
  | E
  | S
  | W;
let direction_to_string = direction =>
  switch (direction) {
  | N => "N"
  | E => "E"
  | S => "S"
  | W => "W"
  };

type rover = {
  coordinate,
  direction,
};

let rover_to_string = ({direction, coordinate}) =>
  "Rover: "
  ++ (direction |> direction_to_string)
  ++ " @"
  ++ (coordinate |> coordinate_to_string);

let left = rover =>
  switch (rover.direction) {
  | N => {...rover, direction: W}
  | W => {...rover, direction: S}
  | S => {...rover, direction: E}
  | E => {...rover, direction: N}
  };

let right = rover =>
  switch (rover.direction) {
  | N => {...rover, direction: E}
  | E => {...rover, direction: S}
  | S => {...rover, direction: W}
  | W => {...rover, direction: N}
  };

let forward = rover =>
  switch (rover) {
  | {direction: N, coordinate: (x, y)} when y > 0 => {
      ...rover,
      coordinate: (x, y - 1),
    }
  | {direction: E, coordinate: (x, y)} when x < 9 => {
      ...rover,
      coordinate: (x + 1, y),
    }
  | {direction: S, coordinate: (x, y)} when y < 9 => {
      ...rover,
      coordinate: (x, y + 1),
    }
  | {direction: W, coordinate: (x, y)} when x > 0 => {
      ...rover,
      coordinate: (x - 1, y),
    }
  | rover => Invalid_argument(rover_to_string(rover)) |> raise
  };

type command =
  | F
  | L
  | R
  | Nothing;

let command_to_string = command =>
  switch (command) {
  | F => "forwards"
  | L => "left"
  | R => "right"
  | Nothing => "nothing"
  };

let rover_to_grid = rover => {
  let {direction, coordinate: (x, y)} = rover;
  let grid = Array.make_matrix(10, 10, {j|⭕️|j});
  grid[y][x] = (
    switch (direction) {
    | N => {j|⬆️|j}
    | E => {j|➡️|j}
    | S => {j|⬇️|j}
    | W => {j|⬅️|j}
    }
  );
  grid;
};

let grid_to_string = (grid: array(array(string))) =>
  grid |> Js.Array.map(Js.Array.joinWith("")) |> Js.Array.joinWith("\n");

let print_grid = grid =>
  Js.log2("%c" ++ grid_to_string(grid), "font-family: monospace");

let run = (command, rover) =>
  switch (command) {
  | F => rover |> forward
  | L => rover |> left
  | R => rover |> right
  | Nothing => rover
  };

[@bs.val] external consoleGroup : string => unit = "console.group";
[@bs.val] external consoleGroupEnd : unit => unit = "console.groupEnd";

let logRover = (~command=Nothing, rover) => {
  rover |> rover_to_string |> consoleGroup;
  command |> command_to_string |> Js.log2("command");
  rover |> rover_to_grid |> print_grid;
  consoleGroupEnd();
  rover;
};

let runAndLogGrid = (command, rover) =>
  run(command, rover) |> logRover(~command);

let executeCommands = (commands, rover) =>
  Js.Array.reduce(
    (rover, command) => runAndLogGrid(command, rover),
    rover,
    commands,
  );
