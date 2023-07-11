#include "../headers/minishell.h"

t_block *new_block_on_pipe_list(t_shell **shell, t_block *block_current)
{
    t_block *pipe_block;

    pipe_block = (t_block *)ft_calloc(1, sizeof(t_block));
    pipe_block->set = 1;
    (*shell)->pipelist_n += 1;
    if (block_current)
    {
        pipe_block->fd[0] = block_current->pipe[0];
        block_current->next = pipe_block;
    }
    else if (!block_current)
        (*shell)->pipelist = pipe_block;
    return (pipe_block);
}
