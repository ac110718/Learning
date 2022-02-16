/* Use JSX instead

import React from "react";

//unpack the props object
function Pet({ name, animal, breed }) {
    return React.createElement("div", {}, [
        React.createElement("h1", {}, name),
        React.createElement("h2", {}, animal),
        React.createElement("h2", {}, breed),
    ]);
};

export default Pet;

*/

//anything inside { } will be considered javascript
// no import needed with JSX

const Pet = (props) => {
    return (
        <div>
            <h1>{props.name}</h1> 
            <h2>{props.animal}</h2>
            <h2>{props.breed}</h2>
        </div>
    );
};

export default Pet;