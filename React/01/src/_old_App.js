import React from "react";
import ReactDOM from "react-dom";
import Pet from "./Pet";

// two packages needed.. one for React interface, and one for DOM render.. ReactDOM (there are others for native, VR, etc)

// first argument is DOM tag for HTML element
// second argument is object for holding attributes like {id: "my-brand"}
// last argument is what you want to render inside the element
// multiple elements can be passed via array
// props object passes down arguments from the parent

/* put into Pet.js
const Pet = (props) => {
    return React.createElement("div", {}, [
      React.createElement("h1", {}, props.name),
      React.createElement("h2", {}, props.animal),
      React.createElement("h2", {}, props.breed),
    ]);
  };
*/

// function that returns an element
const App = () => {
    return React.createElement("div", {}, [
      React.createElement("h1", {}, "Adopt Me!"),
      React.createElement(Pet, {
        name: "Luna",
        animal: "Dog",
        breed: "Havanese",
      }),
      React.createElement(Pet, {
        name: "Pepper",
        animal: "Bird",
        breed: "Cockatiel",
      }),
      React.createElement(Pet, { name: "Doink", animal: "Cat", breed: "Mix" }),
    ]);
};

// renders an actual instance of element via createElement function
// render at "root" div
ReactDOM.render(React.createElement(App), document.getElementById("root"));