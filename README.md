# LANSpan
### A bridge network minimum spanning tree implementation

## What works
From walking through the algorithm as presented in class, on the slides, and
working the example provided in the textbook, I believe this produces the
correct output for the given sample input file.

## Output notation
The output displayed is comprised of the following:

1. Sequence of actions (messages sends/receives) and appropriate actions taken by each bridge upon processing a message
2. Output of the network state at the end of the sending sequence. The output is as follows:

```
  id = <Bridge ID>
      Link1 (best config) [STATUS]
      Link2 (best config) [STATUS]
      ...
      LinkN (best config) [STATUS]
  id = <Bridge ID>
      ...
```
The [STATUS] after each link's best config indicates the status of that link
after executing all sends/receives. If the link is closed after execution, it
will be denoted with a [CLOSED] status. If the link remains open after
execution, the status will be blank.

## Limitations
In the implementation, what I feel is a limitation is that in order to get
around the problem of the bridges immediately connected to LANs around the root
node from disabling their links back to the root node when the root sends a
second configuration message, I had to add an explicit check in
src/bridge.cpp for if the message was sent from the root node, don't close
any links. I'm not sure if this generalizes well to other sample inputs.

## Building and running the code
The general steps to build and run the code are as follows:

1. `cd /path/to/unzipped/directory`
2. `cd src/`
3. `make`
4. `./myprogram <inputfile> <send order separated by spaces>`
