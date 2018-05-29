open Rover;

let rover = {coordinate: (0, 0), direction: N};

rover
|> logRover
|> executeCommands([|R, F, R, L, R, F, F, F, F, L, F, F, F|]);

ReactDOMRe.renderToElementWithId(<ReactRover />, "main");
