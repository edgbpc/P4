Global

to create executable:
make or make statSem

To run program:
statSem <testfile>
statSem < <testFile>.<fileExt>

To enter free form text entering mode
statSem

I did attempt the local option and I did manage the creation of the stack and wrote functions necessary to support it. Where I got hung up and stopped was keeping track of the number of variables in the "block" node.

I cleaned up the try creation by explictly make some returns nulls instead of just undefined. I found that random addresses were getting populated into the unused nodes when examining in the debugger.
Otherwise, functions the same as P2.




