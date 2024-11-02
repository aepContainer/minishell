#include "../../inc/minishell.h"

void init_pipes(t_mshell *mshell)
{
    if (!mshell)
        return;
    mshell->active_pipe[0] = -1;
    mshell->active_pipe[1] = -1;
    mshell->old_pipe[0] = -1;
    mshell->old_pipe[1] = -1;
}

bool create_pipe(t_mshell *mshell)
{
    if (!mshell)
        return (false);
        
    // Aktif pipe'ı temizle
    if (mshell->active_pipe[0] != -1 || mshell->active_pipe[1] != -1)
    {
        perror("minishell: pipe warning");
        close_active_pipe(mshell);
    }
    
    // Yeni pipe oluştur
    if (pipe(mshell->active_pipe) == -1)
    {
        perror("minishell: pipe error");
        return (false);
    }
    return (true);
}
// Parent process için pipe yönetimi
void handle_pipes_parent(t_mshell *mshell)
{
    if (!mshell)
        return;
        
    // Write ucunu kapat
    if (mshell->active_pipe[1] != -1)
    {
        if (close(mshell->active_pipe[1]) == -1)
            perror("minishell: close error");
        mshell->active_pipe[1] = -1;
    }
    // Eski pipe'ın read ucunu yenisiyle değiştir   
    if (mshell->old_pipe[0] != -1)
    {
        if (close(mshell->old_pipe[0]) == -1)
            perror("minishell: close error");
    }
    mshell->old_pipe[0] = mshell->active_pipe[0];
    mshell->active_pipe[0] = -1;
}

void handle_pipes_child(t_mshell *mshell)
{
    if (!mshell)
        return;
        
    if (mshell->active_pipe[0] != -1)
    {
        if (close(mshell->active_pipe[0]) == -1)
            perror("minishell: close error");
        mshell->active_pipe[0] = -1;
    }
    
    if (mshell->old_pipe[1] != -1)
    {
        if (close(mshell->old_pipe[1]) == -1)
            perror("minishell: close error");
    }
    mshell->old_pipe[1] = mshell->active_pipe[1];
    mshell->active_pipe[1] = -1;
}

void close_active_pipe(t_mshell *mshell)
{
    if (!mshell)
        return;
        
    if (mshell->active_pipe[0] != -1)
    {
        if (close(mshell->active_pipe[0]) == -1)
            perror("minishell: close error");
        mshell->active_pipe[0] = -1;
    }
    if (mshell->active_pipe[1] != -1)
    {
        if (close(mshell->active_pipe[1]) == -1)
            perror("minishell: close error");
        mshell->active_pipe[1] = -1;
    }
}

void close_all_pipes(t_mshell *mshell)
{
    if (!mshell)
        return;
        
    close_active_pipe(mshell);
    
    if (mshell->old_pipe[0] != -1)
    {
        if (close(mshell->old_pipe[0]) == -1)
            perror("minishell: close error");
        mshell->old_pipe[0] = -1;
    }
    if (mshell->old_pipe[1] != -1)
    {
        if (close(mshell->old_pipe[1]) == -1)
            perror("minishell: close error");
        mshell->old_pipe[1] = -1;
    }
}
