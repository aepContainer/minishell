#ifndef ERROR_H
# define ERROR_H

# include "errno.h"

# define ERR_CMD 10
# define ERR_ALLOC 11
// Böyle birçok tanımlama yap

void	print_err(const char *error, char err_no);

#endif
