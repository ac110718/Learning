// notice use of className and htmlFor due to conflicts with class and for in js

import { useEffect, useState } from "react";
import Pet from "./Pet";
import useBreedList from "./useBreedList";
import Results from "./Results";
const ANIMALS = ["bird", "cat", "dog", "rabbit", "reptile"];

const SearchParams = () => {
    //return current value of state and function to update
    //when onChange calls updateLocation (on every keystroke), state has been modified and react will re-render
    const [pets, setPets] = useState([]);
    const [location, updateLocation] = useState("Seattle, WA");
    const [animal, updateAnimal] = useState("");
    const [breed, updateBreed] = useState("");
    const [breeds] = useBreedList(animal)];

    // useEffect allows you to say "do a render of this component first so the user can see something then as soon as the render is done, then do something (the something here being an effect.)
    
    useEffect(() => {
        requestPets();
    }, []); 
    
    // [] is where you declare data dependencies and when to run again..
    // blank would assume anytime ANY hook changes.. but this func calls setPets and would re-run again
    // in infinite loop. [] says run it just once on creation

    async function requestPets() {
        const res = await fetch(`http://pets-v2.dev-apis.com/pets?animal=${animal}&location=${location}&breed=${breed}`);
        const json = await res.json();
        setPets(json.pets);
    }

    return (
        <div className="search-params">
            <form
                onSubmit={e => {
                    e.preventDefault();
                    requestPets();
                }}
            >
                <label htmlFor="location">
                    location
                    <input 
                        id="location" 
                        value={location} 
                        placeholder="Location"
                        onChange={(e) => updateLocation(e.target.value)}
                    />
                </label>
                <label htmlFor="animal">
                    animal
                    <select
                        id="animal"
                        value={animal}
                        onChange={(e) => updateAnimal(e.target.value)}
                        onBlur={(e) => updateAnimal(e.target.value)}
                    >
                        <option />
                        {ANIMALS.map((animal) => (
                            <option key={animal} value={animal}>
                                {animal}
                            </option>
                        ))}
                    </select>
                </label>
                <label htmlFor="breed">
                    Breed
                    <select
                        disabled={!breeds.length}
                        id="breed"
                        value={breed}
                        onChange={(e) => updateBreed(e.target.value)}
                        onBlur={(e) => updateBreed(e.target.value)}
                    >
                        <option />
                        {breeds.map((breed) => (
                            <option key={breed} value={breed}>
                                {breed}
                            </option>
                        ))}
                    </select>
                </label>
                <button>Submit</button>
            </form>
            <Results pets = {pets} />
        </div>
    );
};

export default SearchParams;

// without state, typing into text box will not do anything because react thinks something changed when you hit a key, but the data to re-render is static
// must be explicit in how you handle your data

// a hook gets caught every time the render function is called
// never put hooks inside if statements or loops
// React relies on useState to be called in strictly the same order every time so it can give you the same piece of state.