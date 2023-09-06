import Control.Monad (replicateM)
import Data.Char (isDigit, toLower)
import Control.Monad (guard)
import Data.Maybe (catMaybes)

type FirstName = String
type LastName = String

data Person = Person String

people :: [Person]
people = 
    [ Person "my name"
    , Person "carl christian"
    , Person "Elon1 musk"
    , Person "Mary"
    , Person "Alice Wonderland"
    , Person "Robert Downey"
    , Person "Chandler Bing"
    , Person "Joey"
    , Person "Clark Kent"
    , Person "John Doe"
    ]

splitName :: String -> Maybe (FirstName, Maybe LastName)
splitName name =
    case words name of
        [first, last] -> Just (first, Just last)
        _ -> Nothing

toLowercase :: String -> Maybe String
toLowercase s = do
    guard $ all (\c -> not (isDigit c)) s
    return $ map toLower s

toSnakeCase :: FirstName -> Maybe LastName -> Maybe String
toSnakeCase first Nothing = Just first
toSnakeCase first (Just last) = Just $ first ++ "_" ++ last

addCoolPrefix :: String -> Maybe String
addCoolPrefix s = do
    guard (head s /= 'c')
    return $ "cool_" ++ s

coolName :: Person -> Maybe String
coolName (Person full) = do
    (first, maybeLast) <- splitName full
    firstNameLowerCase <- toLowercase first
    lastNameLowerCase <- sequence $ toLowercase <$> maybeLast
    asSnakeCase <- toSnakeCase firstNameLowerCase lastNameLowerCase
    addCoolPrefix asSnakeCase

main :: IO ()
main = do
  putStrLn . unlines . catMaybes . (map coolName) $ people