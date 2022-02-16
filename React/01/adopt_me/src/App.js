//component can have multiple children with array of elements
// props are variables passed down from the parent
const Pet = (props) => {
    return React.createElement("div", {}, [
        React.createElement("h1", {}, props.name),
        React.createElement("h2", {}, props.animal),
        React.createElement("h2", {}, props.breed),
    ]);
};

const App = () => {
    return React.createElement(
        "div", // DOM tag of HTML element
        {}, // attributes within element like id: "my-brand"
        [
            React.createElement("h1", {}, "Adopt Me!"), // what you want inside
            // in this case, pass props object with name, animal, breed attributes
            React.createElement(Pet, {name: "Luna", animal: "Dog", breed: "Havanese"}),
            React.createElement(Pet, {name: "Pepper", animal: "Bird", breed: "Cockatiel"}),
            React.createElement(Pet, {name: "Gerry", animal: "Cat", breed: "Mix"}),
    ]);
};
// render inside of root div
// App is a class of components, createElement makes an instance of the class

ReactDOM.render(React.createElement(App), document.getElementById("root"));