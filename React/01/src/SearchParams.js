// notice use of className and htmlFor due to conflicts with class and for in js

import { useState } from "react";
const ANIMALS = ["bird", "cat", "dog", "rabbit", "reptile"];

const SearchParams = () => {
    //return current value of state and function to update
    //when onChange calls updateLocation (on every keystroke), state has been modified and react will re-render
    const [location, updateLocation] = useState("Seattle, WA");
    const [animal, updateAnimal] = useState("");
    const [breed, updateBreed] = useState("");
    const breeds = [];

    return (
        <div className="search-params">
            <form>
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
        </div>
    );
};

export default SearchParams;

// without state, typing into text box will not do anything because react thinks something changed when you hit a key, but the data to re-render is static
// must be explicit in how you handle your data

// a hook gets caught every time the render function is called
// never put hooks inside if statements or loops
// React relies on useState to be called in strictly the same order every time so it can give you the same piece of state.