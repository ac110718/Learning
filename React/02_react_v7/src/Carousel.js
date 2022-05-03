import { Component } from "react";

class Carousel extends Component {
  constructor(props) {
    super(props);
    // or use a fat arrow function to fix the context issue
    this.handleIndexClick = this.handleIndexClick.bind(this);
    this.state = {
      active: 0,
    };
  }

  static defaultProps = {
    images: ["http://pets-images.dev-apis.com/pets/none.jpg"],
  };

  handleIndexClick(event) {
    this.setState({
      active: +event.target.dataset.index, // convert string to number
    });
  }

  render() {
    const { active } = this.state;
    const { images } = this.props;
    return (
      <div className="carousel">
        <img src={images[active]} alt="animal" />
        <div className="carousel-smaller">
          {images.map((photo, index) => (
            <img
              onClick={this.handleIndexClick}
              key={photo}
              src={photo}
              data-index={index}
              className={index === active ? "active" : ""}
              alt="animal thumbnail"
            />
          ))}
        </div>
      </div>
    );
  }
}

export default Carousel;
