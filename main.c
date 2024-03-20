#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int BUFFER_SIZE = 3;

char	*ft_strdup(const char *s)
{
  char	*arr;
  int		num;

  num = 0;
  while (s[num])
    num++;
  arr = (char *)malloc(sizeof(char) * (num + 1));
  if (arr == 0)
    return (0);
  num = 0;
  while (s[num])
  {
    arr[num] = s[num];
    num++;
  }
  arr[num] = '\0';
  return (arr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
  size_t	src_len;
  size_t	i;

  src_len = 0;
  while (src[src_len])
    src_len++;
  if (size == 0)
    return (src_len);
  i = 0;
  while (i < size - 1 && src[i])
  {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0';
  return (src_len);
}

char *ft_strchr(const char *s, int c) {
  int i;

  i = 0;
  if (s == 0)
    return (0);
  if (c == '\0') {
    while (s[i])
      i++;
    return ((char *)&s[i]);
  }
  i = 0;
  while (s[i]) {
    if (s[i] == c)
      return ((char *)&s[i]);
    i++;
  }
  return (0);
}

size_t ft_strlen(const char *s) {
  int len;

  len = 0;
  while (s[len])
    len++;
  return (len);
}

char *ft_strjoin(char *s1, char *s2) {
  int s1_len;
  int s2_len;
  int i;
  char *arr;

  if (s1 == 0)
  {
    s1 = (char *)malloc(sizeof(char) * 1);
    if (!s1)
      return (NULL);
    s1[0] = '\0';
  }
  if (!s1 || !s2)
    return (0);
  i = -1;
  s1_len = ft_strlen(s1);
  s2_len = ft_strlen(s2);
  arr = (char *)malloc((s1_len + s2_len + 1) * (sizeof(char)));
  if (arr == 0)
    return (0);
  while (++i < s1_len)
    arr[i] = s1[i];
  i = -1;
  while (++i < s2_len)
    arr[s1_len + i] = s2[i];
  arr[s1_len + i] = '\0';
  return (arr);
}

char *sum_line(int fd, char *line) {
  char *buf;
  int cnt;

  buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
  if (!buf)
    return (NULL);
  cnt = 1;
  while (!(ft_strchr(line, '\n')) && cnt != 0) {
    cnt = read(fd, buf, BUFFER_SIZE);
    if (cnt == -1) {
      free(buf);
      return (NULL);
    }
    if (cnt == 0)
      break;
    buf[cnt] = '\0';
    line = ft_strjoin(line, buf);
  }
  free(buf);
  return (line);
}

char *get_next_line(int fd) {
    static char *remainder ;
    char *newline;
    char *result;

    if (fd < 0 || BUFFER_SIZE <= 0) return (NULL);

    remainder = sum_line(fd, remainder);

    if (remainder) {
        newline = strchr(remainder, '\n');
        if (newline) {
            size_t len = newline - remainder + 1;
            result = (char *)malloc(len + 1);
            ft_strlcpy(result, remainder, len);
            result[len] = '\0';
            char *temp = ft_strdup(newline + 1);
            remainder = temp; 
        } else {
            result = ft_strdup(remainder);
            remainder = NULL;
        }
    }

    return result;
}
