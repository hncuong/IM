Pruned Monte-Carlo Simulations
========================

This is a fast and accurate algorithm for the influence maximization problem under the independent cascade model.

## Usage
Given a graph with edge probabilities, it selects a seed set of a given size.

    $ make
    $ ./benchmark graph k R
* graph: input file (see below)
* k: the seed set size
* R: the number of random graphs (larger = more accurate)

### Example

    $ make
    $ ./benchmark ./sample_graph.tsv 5 200
    0-th seed =     4
    1-th seed =     0
    2-th seed =     2
    3-th seed =     3
    4-th seed =     1

### Format of the input graph:
    u_1	v_1	p_1
    ...
    u_i	v_i	p_i
    ...
    u_m	v_m	p_m
* The i-th line means an directed edge (u_i, v_i) with propagation probability p_i (see `sample_graph.tsv`).
* Vertices should be described by integers starting from zero.

## References

* Naoto Ohsaka, Takuya Akiba, Yuichi Yoshida, and Ken-ichi Kawarabayashi. **[Fast and Accurate Influence Maximization on Large Networks with Pruned Monte-Carlo Simulations](http://www.aaai.org/ocs/index.php/AAAI/AAAI14/paper/view/8455/8411)**.
In AAAI-14, pages 138--144, 2014.
