open Rover;

let rover = {coordinate: (0, 0), direction: N};

rover |> rover_to_string |> Js.log;
rover |> rover_to_grid |> print_grid;

rover |> executeCommands([|R, F, R, L, R, F, F, F, F, L, F, F, F|]);

ReactDOMRe.renderToElementWithId(<ReactRover />, "main");
