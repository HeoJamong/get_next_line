char	*get_next_line(int fd)
{
	static char    *result;
    char	*str;
	int		buf;
	int		point

	buf = 1;
	while (0 <= fd <= 1024 || buf != 0)
	{
		buf = read(fd, str, BUFFER_SIZE);
		if (buf == -1)
			return ;
		strjoin(result, str);
		if (strchr(result, "\n"))
		{
			
			// 개행 문자 추가해야함
			return (str)
		}
	}
}
