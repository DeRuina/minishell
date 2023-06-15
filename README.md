# minishell

- Main calls ft_env to store the environment variables into and key value pair array.
- Minishell parses the arguments into nodes that will be executed by the ft_executor.

```mermaid
flowchart TD
    A --- |Copies the env| B[ft_copyenv]
    A[Main] --- |Passes the env to minishell| C[minishell]
    C --- |parse_args returns nodes| D[parse_args]
    D --- |Seperates the string inputted by the user to tokens|E[ft_cmd_trim]
    D --- |Expands environment variables|F[ft_expand]
    D --- |Splits the tokens if there are operators attached together|G[ft_split_operators]
    D --- |Trims any unnecessary quotes|H[ft_str_trim]
    D --- |Recursively assigns all necessary variables to each node|I[new_node]
    C --- |Nodes are passed to ft_executor| J[ft_executor]
```
