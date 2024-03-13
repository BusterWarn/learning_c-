// Define an enum with different animal variants
#[derive(Debug)]
enum Animal {
    Goose,
    Horse,
    Camel,
    Fox,
    Quokka,
}

// Function that returns the sound of an animal
fn animal_sound(animal: &Animal) -> &str {
    match animal {
        Animal::Goose => "Honk",
        Animal::Horse => "Neigh",
        Animal::Camel => "Grunt",
        Animal::Fox => "Wa-pow",
        Animal::Quokka => "Squeak",
    }
}

fn main() {
    // Create a vector of animals
    let animals = vec![Animal::Goose, Animal::Horse, Animal::Camel, Animal::Fox, Animal::Quokka];

    // Iterate over the animals and print their sounds
    for animal in animals {
        println!("(rust) {:?} says {}", animal, animal_sound(&animal));
    }
}
