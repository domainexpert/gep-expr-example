# gep-expr-example
Example analysis in reading operands of constant expression GEP

Includes an example example.c which, when compiled into LLVM produces a store instruction whose pointer operand is a bitcast of getelementptr expression. Usually you would only need to do: `make` to build the analysis and run it on the example.
