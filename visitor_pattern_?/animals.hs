-- Define the Animal data type with different animals as constructors
data Animal = Goose | Horse | Camel | Fox | Quokka deriving (Show)

-- Function to get the sound of an animal
sound :: Animal -> String
sound Goose = "Honk"
sound Horse = "soundeigh"
sound Camel = "Grunt"
sound Fox = "Wa-pow"
sound Quokka = "Squeak"

-- Example usage: print the sound of each animal
main :: IO ()
main = do
  let animals = [Goose, Horse, Camel, Fox, Quokka]
  mapM_ (\animal -> putStrLn $ "(haskell) " ++ show animal ++ " says " ++ sound animal) animals
