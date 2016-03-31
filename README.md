# ofxLSystemGrammar

This addon implements most of the grammars described in "The Algorithimic Beauty of Plants", a book written by Lyndenmayer and Prusinkiewicz, free available online at this [URL](http://algorithmicbotany.org/papers/#abop). This addon can be used to draw L-System plants or fractals. Although in the examples you can see some 2D graphic interpretation of this grammars, this addon takes care only of the strings generation.
If you need a turtle graphic interpretation of the grammars generated with ofxLSystemGrammar, in 3D, have a look at [ofxLSystem](/edap/ofxLSystem) to see which kind of meshes it is possible to draw using this addon.

An [L-System](https://en.wikipedia.org/wiki/L-system) is composed by an axiom and rules. The axiom is the seed, the initial brick of the structure that we want to create, the rules are instructions about how this seed will reproduce itself. The simplest class of L-System, those which are deterministic and context-free, are called DOLsystems. Let's see an easy example:
- Assume that our string is composed by 2 "words", `A` and `B`.
- Each letter is associated with a rewriting rule:  A becomes AB, and B becomes A
- The rewriting process starts from a string called "axiom". In this example,
  let declare as axiome the "word" `B`
- The first five derivations of the described DOLsystem will be these:

![DOL](img/DOL.png)

Currently it supports:

- DOL system (DOL-system.png)
- Bracketed Edge rewriting
- Bracketed Node rewriting
- Parametric Grammar
- Stochastic Grammar
