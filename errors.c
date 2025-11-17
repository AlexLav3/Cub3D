#include "cub3D.h"

//we can add a check for missing configs and colors 
int	is_config_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (
		ft_strncmp(line, "NO ", 3) == 0 ||
		ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 ||
		ft_strncmp(line, "EA ", 3) == 0 ||
		ft_strncmp(line, "F ", 2) == 0 ||
		ft_strncmp(line, "D ", 2) == 0 ||
		ft_strncmp(line, "C ", 2) == 0);
}

static int	valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\n' || c == '\t' || c == 'D'); //D for Doors
}

int	map_error(int fd)
{
	char	*line;
	int		i;
	int		error;

	error = 0;
	line = config_l(fd);
	while ((line = get_next_line(fd)))
	{
		i = 0;
		while (line[i])
		{
			if (!valid_map_char(line[i]))
				error = 1;
			i++;
		}
		free(line);
	}
	if(close(fd))
		perror("close");
	if (error)
		return (printf("wrong char in file\n"), 1);
	return (0);
}

int	arg_error(int argc, char **argv)
{
	int		fd;
	char	*point;

	if (argc != 2)
		return (printf("wrong number of args\n"), 1);
	point = ft_strrchr(argv[1], '.');
	if (!point || ft_strncmp(point, ".cub", 4) != 0)
		return (printf("wrong extension\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("could not open file\n"), 1);
	if (map_error(fd))
		return (1);
	return (0);
}
