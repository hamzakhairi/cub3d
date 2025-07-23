
#include "../cub.h"

char	*ft_other_strdup(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(s);
	if (j == 1)
		return (NULL);
	str = (char *)malloc(sizeof(*str) * (j + 1));
	if (!str)
		return (NULL);
	while (i < j)
	{
        if (s[i] != '\n')
		{
            str[i] = s[i];
		    i++;
        }
        else
            break;
	}
	str[i] = '\0';
	return (str);
}
