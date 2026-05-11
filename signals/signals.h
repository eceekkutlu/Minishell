#ifndef SIGNALS_H
# define SIGNALS_H

/*
** signals/signals.c            (YAZILACAK)
**
**   setup_signals()
**     — Ana dongu icin:
**         SIGINT  -> prompt'u temizle, yeni satir yaz
**         SIGQUIT -> yoksay (SIG_IGN)
**
**   setup_signals_child()
**     — fork() sonrasi child surec icin:
**         SIGINT  -> varsayilan (SIG_DFL)
**         SIGQUIT -> varsayilan (SIG_DFL)
**
**   reset_signals()
**     — Heredoc okuma sirasinda ozel davranis.
*/
void	setup_signals(void);
void	setup_signals_child(void);
void	reset_signals(void);

#endif
