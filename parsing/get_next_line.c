#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


#define BUFFER_SIZE 128

char	*ft_cherche(char *str, char c)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char **s1, char *s2, int j)
{
	int len1;
	int len2;
	int i;
	char *str;

	i = 0;
	len1 = ft_strlen(*s1);
	len2 = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (i < len1)
	{
		str[i] = *s1[i];
		i++;
	}
	len1 = 0;
	while (len1 < len2)
	{
		str[i] = s2[len1];
		len1++;
		i++;
	}
	str[i] = '\0';
	if (j > 0)
		free(*s1);
	return (str);
}

int get_next_line(int fd, char **line)
{
	static char buffer[BUFFER_SIZE + 1];
	int			i;
	int			j;
	int			k;
	char 		*ptr;

	if (fd < 0 || !(line) || BUFFER_SIZE <= 0)
		return (-1);
	*line = "";
	j = 0;
	while (1)
	{
		if (buffer[0] == '\0')
		{
			k = read(fd, buffer, BUFFER_SIZE);
			if (k < 0)
				return (-1);
			else if (k == 0)
				return (0);
			else
				buffer[k] = '\0';
		}
		if ((ptr = ft_cherche(buffer, '\n')))
			*ptr = '\0';
		if(!(*line = ft_strjoin(line, buffer, j)))
			return (-1);
		i = 0;
		if (ptr)
		{
			ptr++;
			while (*ptr)
			{	
				buffer[i] = *ptr;
				i++;
				ptr++;
			}
			buffer[i] = '\0';
			return (1);
		}
		else
			buffer[0] = '\0';
	}
	j++;
}
/*
int main(void)
{
	int fd;
	char *line = "";

	fd = open("some_bs.txt", O_RDWR);
	get_next_line(fd, &line);
	printf("Line: %s\n", line);
	get_next_line(fd, &line);
	printf("Line: %s\n", line);
	get_next_line(fd, &line);
	printf("Line: %s\n", line);
	get_next_line(fd, &line);
	printf("Line: %s\n", line);
	free(line);
	return (0);
}*/
