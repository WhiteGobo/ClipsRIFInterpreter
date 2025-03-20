from rdflib import *
import argparse

def parse_args():
    parser = argparse.ArgumentParser(
                    prog='helper',
                    description='filter rdf graph for certain namespaces')
    parser.add_argument('inputgraph', type=argparse.FileType('r'))
    parser.add_argument('namespaces', nargs='+')
    args = parser.parse_args()
    return args.inputgraph, args.namespaces

def rdf_filter(g_out):
    t = True
    while t:
        t = False
        for s, _, o in g_out.triples((None, RDF.rest, None)):
            q = g_out.triples((None, None, s))
            if not next(q, False):
                g_out.remove((s, RDF.rest, o))
                elem = g_out.value(subject=s, predicate=RDF.first)
                g_out.remove((s, RDF.first, elem))
                t = True
                break;
    return g_out


def main(inputgraph, namespaces):
    g_in = Graph().parse(inputgraph)
    g_out = Graph()
    namespaces = [Namespace(ns) for ns in namespaces]
    for s,p,o in g_in:
        if any((
                any(p in ns for ns in namespaces),
                p == RDF.type and any(o in ns for ns in namespaces),
                p in [RDF.first, RDF.rest],
                )):
            g_out.add((s, p, o))
    rdf_filter(g_out)
    print(g_out.serialize())

if __name__=="__main__":
    args = parse_args()
    main(*args)
