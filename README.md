# ClipsRIFInterpreter

## TODO

There is no test for memory leaks yet.

## Basic usage.

As Anchorpoint you use a \ref clips_graph_container, for nearly every
method in this framework.
At the start you have to generate a new one with \ref init_graph.
You'll have to dispose of this at the end via \ref close_graph.

In the graph facts are stored
as triples or quads (subject, predicate, object, context).
Each of these terms is identified with a utf8 string as defined in rdf.
To add a single fact use \ref assert_fact.
Asserted facts and produced facts can be retrieved via \ref get_facts.

For example you have the information (ex:Tim rdf:type foaf:Person.)

```C
struct clips_graph_container graph = init_graph();
//namespaces ex, rdf and foaf are extended
string tim = "http://example.com/Tim";
string typeof = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
string person = "http://xmlns.com/foaf/0.1/Person";
assert_fact(graph, tim, typeof, person, NULL)

struct TriplesLinkedList facts = get_facts(graph, NULL, typeof, NULL);
//facts: [(ex:Tim, rdf:type, foafPerson)]
close_graph(graph);
```

## Creating and running rules

To load logic, you have to have this logic in clips rules format. But in this
package there is already logic implemented to create logic in clips format
from OWL, RDFS and (?). See eg in \ref hello_test.cc under BasicOwlLogic.


## Configuration of logic

You can directly load logic via clips own loading function. You can load a file
with \ref load_config.

```C
struct clips_graph_container graph = init_graph();
RET_LOADCONFIG err = load_config(graph, "path/to/config.clp");
if (err == CTC_LC_NO_ERROR){...}
close_graph(graph)
```

## BUILDING

cmake cache variables:

* `ASSETPATH_CLIPSSCRIPTS`: determine where default scripts are saved to.
  if not absolute will be overriden to `binary_dir/ASSETPATH_CLIPSSCRIPTS`
  for example: `-D ASSETPATH_CLIPSSCRIPTS=brubru/`

## Testing

see \ref BasicFactTest for more information

### using make

To use a specific test use variable `TESTFILTER`, eg:

```
env TESTFILTER=CORE_PET_Assert make test
```

## node notation in clips

In Clips we will only use strings and symbols as representation of any Node 
(URI, Literal, Blank Node).
URIs will always be in anglebrack-notation (`<some://uri>`) and saved as symbol.
Blank Node will always start with `_:` and saved as symbol.
Strings will start with `L:`, escape any special symbol and saved as string.
Language will be separated to the value by `@@` and datatype by `^^`.
The datatype will be in anglebrack-notation.
with `@@` and 


# Notes on function

Apparently test in rules will accept a void pointer as truth value.
Need an educated way to use test in rules with this in mind.






# notes

add time date library maybe? `https://github.com/TimSC/iso8601lib/tree/master`_
