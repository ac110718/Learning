import { render } from "react-dom";
import SearchParams from "./SearchParams";
import Pet from "./SearchParams";

const App = () => {
  return (
    <div>
      <h1>Adopt Me!</h1>
        <SearchParams />
    </div>
  );
};

render(<App />, document.getElementById("root"));

// <Pet name="Luna" animal="dog" breed="Havanese" />
//       <Pet name="Pepper" animal="bird" breed="Cockatiel" />
//       <Pet name="Doink" animal="cat" breed="Mix" />