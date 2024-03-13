from __future__ import annotations

# Interface for Animal
class Animal:
    def accept(self, visitor: AnimalSoundVisitor):
        pass

# Interface for AnimalSoundVisitor
class AnimalSoundVisitor:
    def visit(self, animal: Animal):
        pass

# Concrete implementations of Animal Interface
class Goose(Animal):
    def accept(self, visitor):
        visitor.visit(self)

    def sound(self):
        return "Honk"

class Horse(Animal):
    def accept(self, visitor):
        visitor.visit(self)

    def sound(self):
        return "Neigh"

class Camel(Animal):
    def accept(self, visitor):
        visitor.visit(self)

    def sound(self):
        return "Grunt"

class Fox(Animal):
    def accept(self, visitor):
        visitor.visit(self)

    def sound(self):
        return "Wa-pow"

class Quokka(Animal):
    def accept(self, visitor):
        visitor.visit(self)

    def sound(self):
        return "Squeak"

# Concrete implementation of AnimalSoundVisitor
class MakeSoundVisitor(AnimalSoundVisitor):
    def visit(self, animal: Animal):
        print(f"{animal.__class__.__name__} says {animal.sound()}")

# Creating animals
animals = [Goose(), Horse(), Camel(), Fox(), Quokka()]

# Creating a visitor
sound_visitor = MakeSoundVisitor()

# Let's make some noise!
for animal in animals:
    animal.accept(sound_visitor)
