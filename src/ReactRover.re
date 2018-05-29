type state = {
  rover: Rover.rover,
  error: option(string),
};

let make = _children => {
  ...ReasonReact.reducerComponent("ReactRover"),
  initialState: () => {
    rover: {
      coordinate: (0, 0),
      direction: N,
    },
    error: None,
  },
  reducer: (action, state) => {
    let rover = Rover.run(action, state.rover);
    /*
      try (Rover.run(action, state.rover)) {
         | Invalid_argument(error) =>
           ReasonReact.Update({rover: state.rover, error: "oops"})
         };
     */
    ReasonReact.Update({...state, rover});
  },
  render: self =>
    <div>
      <pre>
        (
          self.state.rover
          |> Rover.rover_to_grid
          |> Rover.grid_to_string
          |> ReasonReact.string
        )
      </pre>
      (
        switch (self.state.error) {
        | Some(error) => <p> (error |> ReasonReact.string) </p>
        | None => ReasonReact.null
        }
      )
      <div>
        <button onClick=(_ev => self.send(Rover.L))>
          ({j|↶|j} |> ReasonReact.string)
        </button>
        <button onClick=(_ev => self.send(Rover.F))>
          ({j|⬆|j} |> ReasonReact.string)
        </button>
        <button onClick=(_ev => self.send(Rover.R))>
          ({j|↷|j} |> ReasonReact.string)
        </button>
      </div>
    </div>,
};
