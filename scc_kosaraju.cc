// For each vertex u of the graph, mark u as unvisited. Let L be empty.
// For each vertex u of the graph do Visit(u), where Visit(u) is the recursive subroutine:
// If u is unvisited then:
// Mark u as visited.
// For each out-neighbour v of u, do Visit(v).
// Prepend u to L.
// Otherwise do nothing.
// For each element u of L in order, do Assign(u,u) where Assign(u,root) is the recursive subroutine:
// If u has not been assigned to a component then:
// Assign u as belonging to the component whose root is root.
// For each in-neighbour v of u, do Assign(v,root).
// Otherwise do nothing.
