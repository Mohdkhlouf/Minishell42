#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
    size_t len;
    char *dup;

    if (!s)
        return NULL;
    len = ft_strnlen(s, n);
    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;
    ft_strncpy(dup, s, len);
    dup[len] = '\0';
    return (dup);
}