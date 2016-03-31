# ofxLSystemGrammar

This addon implements most of the grammars described in "The Algorithimic Beauty of Plants", a book written by Lyndenmayer and Prusinkiewicz, free available online at this [URL](http://algorithmicbotany.org/papers/#abop). This addon can be used to draw L-System plants or fractals. Although in the examples you can see some 2D graphic interpretation of this grammars, this addon takes care only of the strings generation.
If you need a turtle graphic interpretation of the grammars generated with ofxLSystemGrammar, in 3D, have a look at [ofxLSystem](/edap/ofxLSystem) to see which kind of meshes it is possible to draw using this addon.

An [L-System](https://en.wikipedia.org/wiki/L-system) is composed by an axiom and rules. The axiom is the seed, the initial brick of the structure that we want to create, the rules are instructions about how this seed will reproduce itself. The simplest class of L-System, those which are deterministic and context-free, are called DOLsystems. Let's see an easy example:
- Assume that our string is composed by 2 "words", `A` and `B`.
- Each letter is associated with a rewriting rule:  `A` becomes `AB`, and `B` becomes `A`
- The rewriting process starts from a string called "axiom". In this example, let declare as axiom the "word" `B`
- The first five derivations of the described DOLsystem will be these string:

![DOL](img/DOL.png)

You can use this addon to produce them:

```cpp
vector<string> rules {"A -> AB", "B -> A"};
auto result = ofxLSystemGrammar::buildSentences(rules, 5, "B");
```

It will give as result a `vector<string>` containing:
```
vector<string> result{
    "B",
    "A",
    "AB",
    "ABA",
    "ABAAB",
    "ABAABABA",
};
```

## Interface
In this example you have seen the small interface of ofxLSystemGrammar. This addon has only one public method `buildSentences` that returns a `vector<string>`. This is the signature of this method:

```cpp
static const vector<string> buildSentences(vector<string> _rules, const unsigned int _n_steps, string _axiom, map<string,float> _constants = Constants());
```

- `_rules` are the reproduction rules, in the example `{"A -> AB", "B -> A"};`
- `_n_steps` is an integer that defines how many times the axiom will be rewritten, in the example `5`
- `_axiom` is the initial "seed", that will be rewritten, in the example `B`
- `_constant` Constants is a user defined type `typedef map<string,float> Constants;` and it is empty by default. There is some example later that shows how to use it.

## Turtle Graphics
Adding a [turtle graphic](https://en.wikipedia.org/wiki/Turtle_graphics) interpretation of these sentences, allow us to draw fractals and L-System plants.
A turtle graphic interpretation can take as input the result of this operation:

```cpp
vector<string> rules {"F -> F − F + F + FF − F − F + F"};
auto result = ofxLSystemGrammar::buildSentences(rules, 4, "F");
```

An draw something like this:
![turtle](img/turtle.png)

For the sake of clarity, there is a picture containing a turtle interpretation for each of the following examples.

## Bracketed Edge Rewriting

A bracketed L-System contains square brackets `[ ]` that are used by the turtle to mark a position, go forth and come back to the marked position. Bracketd L-System allows branching needed in producing weeds, bushes and trees.
Edge-rewriting means that productions rules substitute figures for polygon *edges*

```cpp
vector<string> rule {"F->F[+F]F[-F][F]"};
auto result = ofxLSystemGrammar::buildSentences(rule, 4, "F");
```

![Bracketed Edge Rewriting](img/bracketed_edge_rew.png)

## Bracketed Node Rewriting

In node rewriting, productions operate on polygon *vertices*. That means that after each rewriting we can define vertices that will become branches.

```cpp
vector<string> rules {"X->F[+X][-X]FX", "F->FF"};
auto result = ofxLSystemGrammar::buildSentences(rules, 6, "X");
```

![Bracketed Node Rewriting](img/bracketed_node_rew.png)

## Parametric Grammar

*note* the actual implementation does not support nested operations like `(x+(y-2))`, but just single plain operation like `(x+2)`. The current supported operators are `+`, `-`, `*`, `/`.

## Parametric Grammar with constants

## Stochastic Grammar










Currently it supports:

- DOL system (DOL-system.png)
- Bracketed Edge rewriting
- Bracketed Node rewriting
- Parametric Grammar
- Stochastic Grammar
